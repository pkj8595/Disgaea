#include "Stdafx.h"
#include "GameCharacter.h"
#include "ItemManager.h"

GameCharacter::GameCharacter() : _characterImg(nullptr),
								_currentAnimation(nullptr),
								_allStats(nullptr),
								_stats(nullptr),
								_equipItem{nullptr},
								_animation{nullptr},
								_hpBar(nullptr)

{
}

GameCharacter::~GameCharacter()
{
}


HRESULT GameCharacter::init(void)
{
	return S_OK;
}

HRESULT GameCharacter::init(string fileName, int x, int y, int coorX, int coorY, E_UnitType type, int imgCorrectionX, int imgCorrectionY)
{
	_name = fileName;
	_characterImg = IMAGEMANAGER->findImage(fileName);
	_unitType = type;
	_coordinate.x = coorX;
	_coordinate.y = coorY;
	_beforeCoordinate = PointMake(coorX, coorY);
	_point.x = x;
	_point.y = y;
	_imgCorrectionX = imgCorrectionX;
	_imgCorrectionY= imgCorrectionY;
	_rc = RectMakeCenter((int)_point.x- imgCorrectionX,(int) _point.y - imgCorrectionY, _characterImg->getFrameWidth(), _characterImg->getFrameHeight());

	_shadowImg = IMAGEMANAGER->findImage("shadow");

	_attackRange = 2;
	for (int i = 0; i < Equipment_End; i++)
	{
		_equipItem[i] = ItemManager::getSingleton()->getEmptyItem();
	}

	_dir = E_AniDirection::Ani_Right_Bottom;
	_behavior = E_AniBehavior::Ani_idle;
	_beforeDir = E_AniDirection::E_AniDirection_end;
	_beforeBehavior = E_AniBehavior::E_Behavior_end;
	_behaviorType = E_BehaviorType::NONE;

	_stats = new CharicterStats;
	_allStats = new CharicterStats;

	computeStats();

	_hpBar = new ProgressBar;
	if (_unitType == E_UnitType::Controllable)
	{
		_hpBar->init(_point.x,_point.y,37,3,true);
	}
	else if (_unitType == E_UnitType::Monster)
	{
		_hpBar->init(_point.x, _point.y, 37, 3, false);
	}
	//_hpBar->setZData();

	for (int i = 0; i < E_CommandFlag_end; i++)
	{
		_bsCommandState.set(i, false);
	}

	_isShaking = false;
	_isShakingIncrease = false;
	_shakingStartTime = 0.0f;
	_shakingTime = false;
	_beforeShakingPt = PointMake(0, 0);
	_currentAnimation = nullptr;
	_shakingOffsetCount = 0;
	_iconIndex = 0;
	_attackIndex = 3;
	_inputCount = 0;
	_moveCount = 0;
	_battleFaceIndex = 0;
	_LinerMoveEndPoint = PointMake(0, 0);
	_LinerMoveStartPoint = PointMake(0, 0);
	_reservationBehavior = E_AniBehavior::E_Behavior_end;
	_isDie = false;
	_isRender = true;

	_zData = new ZOrderData;
	//_zData->setRenderData(&_rc, &_currentAnimation, &_characterImg);
	_zData->setRenderCallback(&_rc, [this](void)-> void { render(); });
	_title = "";
	return S_OK;
}

void GameCharacter::release(void)
{
	CAMERA->removeZData(_zData);
	_hpBar->release();
	SAFE_DELETE(_hpBar);
	SAFE_DELETE(_zData);
	SAFE_DELETE(_stats);
	SAFE_DELETE(_allStats);

	while (!_vSkill.empty())
	{
		SAFE_DELETE(_vSkill.back());
		_vSkill.pop_back();
	}

}

void GameCharacter::update(void)
{
	if (_bsCommandState[LinerMoveFlag])
	{
		_moveCount++;
		_point = LinearMovePoint(_LinerMoveStartPoint, _LinerMoveEndPoint, _inputCount, _moveCount);

		if (_moveCount >= _inputCount)
		{
			_moveCount = 0;
			_bsCommandState.set(LinerMoveFlag, false);
		}
	}

	if (_bsCommandState[reservationBehaviorFlag])
	{
		if (!_currentAnimation->isPlay())
		{
			_behavior = _reservationBehavior;
			_bsCommandState.set(reservationBehaviorFlag, false);
			_reservationBehavior = E_AniBehavior::E_Behavior_end;
		}
	}

	//if (_bsCommandState[reservationCallback])
	//{
	//	if (TIMEMANAGER->getWorldTime() > _callbackExcuteTime)
	//	{
	//		_callback();
	//		_bsCommandState.set(reservationCallback, false);
	//	}
	//}
	if (_behavior == E_AniBehavior::Ani_idle && !_currentAnimation->isPlay())
	{
		_beforeBehavior = E_AniBehavior::E_Behavior_end;
	}

	if ((_dir != _beforeDir || _behavior != _beforeBehavior))
	{
		if (_currentAnimation == nullptr)
		{
			assert("GameCharacter::update >> Aniamtion nullptr");
		}
		_currentAnimation->AniStop();
		_beforeDir = _dir;
		_beforeBehavior = _behavior;

		_currentAnimation = _animation[_dir][_behavior];

		if (_currentAnimation == nullptr)
		{
			assert("GameCharacter::update >> Aniamtion nullptr");
		}
		_currentAnimation->AniStart();
	}

	if (_isShaking)
	{
		_shakingOffsetCount++;
		if (_shakingOffsetCount > 0)
		{
			_shakingOffsetCount = 0;
			_isShakingIncrease = !_isShakingIncrease;
			if (_isShakingIncrease) _point.y += 1;
			else _point.y -= 1;
		}

		if (TIMEMANAGER->getWorldTime() > _shakingStartTime + _shakingTime)
		{
			_isShaking = false;
			_shakingStartTime = 0;
			_shakingTime = 0;
			_point = _beforeShakingPt;
			if (_behavior == E_AniBehavior::Ani_be_Attacked)
			{
				_behavior = E_AniBehavior::Ani_idle;
			}
		}
	}
	_rc = RectMakeCenter((int)_point.x - _imgCorrectionX,(int) _point.y - _imgCorrectionY, _characterImg->getFrameWidth(), _characterImg->getFrameHeight());

	_shadowRc = RectMakeCenter((int)_point.x , (int)_point.y , _shadowImg->getWidth(), _shadowImg->getHeight());

	_hpBar->setPoint(_point);
	_hpBar->update();
}

void GameCharacter::render(void)
{
	if (!_isRender) return;

	_shadowImg->render(getMemDC(), _shadowRc.left-CAMERA->getLeft(), _shadowRc.top - CAMERA->getTop());
	_characterImg->aniRender(getMemDC(),_rc.left - CAMERA->getLeft(),_rc.top - CAMERA->getTop(), _currentAnimation);
	_hpBar->render();
}

void GameCharacter::unregisterZData(void)
{
	TurnEnd();
	CAMERA->removeZData(_zData);
	//_hpBar->removeZData();
}

void GameCharacter::registerZData()
{
	_rc = RectMakeCenter((int)_point.x - _imgCorrectionX, (int)_point.y - _imgCorrectionY, _characterImg->getFrameWidth(), _characterImg->getFrameHeight());
	CAMERA->registerZData(ZIndexType::ZIndexType_Character,_zData);
	//_hpBar->registerZData();
}

void GameCharacter::setReservationAniBehavior(E_AniBehavior behavior)
{
	_bsCommandState.set(reservationBehaviorFlag, true);
	_reservationBehavior = behavior;
}

bool GameCharacter::IsAttackIndex(void)
{
	if (_behavior == E_AniBehavior::Ani_attack)
	{
		if (_currentAnimation->getNowPlayIdx() == _attackIndex)
			return true;
	}
	return false;
}

bool GameCharacter::IsResetMoveIndex(void)
{
	if (_behavior == E_AniBehavior::Ani_attack)
	{
		if (_currentAnimation->getNowPlayIdx() == _attackIndex + 1)
			return true;
	}
	return false;
}

bool GameCharacter::addExp(int exp)
{
	_stats->_exp += exp;
	if (_stats->_exp > _stats->_maxExp)
	{
		while (_stats->_exp > _stats->_maxExp)
		{
			_stats->_level++;
			_stats->_atk += 5;
			_stats->_hp += 5;
			_stats->_maxHp += 5;
			_stats->_def += 5;
			_stats->_maxExp = _stats->_maxExp * 1.4;
		}
		return true;
	}
	return false;
}

void GameCharacter::beAttacked(int damage)
{
	if (damage < 1) damage = 1;
	_stats->_hp -= damage;
	if (_stats->_hp < 1)
	{
		_stats->_hp = 0;
		_isDie = true;
	}
	_hpBar->setGauge(_stats->_hp, _stats->_maxHp);
}

void GameCharacter::healCharacter(void)
{
	_stats->_hp = _stats->_maxHp;
	_stats->_sp = _stats->_maxSp;
	_isDie = false;
	_hpBar->setGauge(_stats->_hp, _stats->_maxHp);

}

void GameCharacter::setSkill(string skillName, POINT coorPoint, float damageCalculation, int skillRange, int sp)
{
	CSkill* tempSkill = new CSkill;
	tempSkill->init(skillName, coorPoint, damageCalculation, skillRange,sp);
	_vSkill.push_back(tempSkill);
}

Item* GameCharacter::setEquipmentItem(E_Equipment_Item itemSlot, Item* item)
{
	if (_equipItem[itemSlot] != nullptr)
	{
		Item* tempItem = _equipItem[itemSlot];
		_equipItem[itemSlot] = item;
		computeStats();
		return tempItem;
	}
	_equipItem[itemSlot] = ItemManager::getSingleton()->getEmptyItem();
	computeStats();

	return _equipItem[itemSlot];
}

Item* GameCharacter::getEquipmentItem(E_Equipment_Item itemSlot)
{
	return _equipItem[itemSlot];
}

//void GameCharacter::setCallback(float time, CALLBACKFUNCTION callback)
//{
//	_bsCommandState.set(reservationCallback, true);
//	_callbackExcuteTime = TIMEMANAGER->getWorldTime() + time;
//	_callback = callback;
//
//}


void GameCharacter::computeStats()
{
	CharicterStats temp;
	for (int i = 0; i < Equipment_End; i++)
	{
		if (_equipItem[i] != nullptr )
		{
			if (_equipItem[i] != ItemManager::getSingleton()->getEmptyItem())
			{
				temp = (*_allStats + _equipItem[i]->_stats);
			}
		}
	}
	*_allStats = (temp + *_stats);
}

void GameCharacter::TurnEnd(void)
{
	_bsCommandState.reset();
	_beforeCoordinate = _coordinate;
}

void GameCharacter::shakeStart(float time)
{
	_shakingStartTime = TIMEMANAGER->getWorldTime();
	_isShaking = true;
	_isShakingIncrease = true;
	_shakingTime = time;
	_beforeShakingPt = _point;
}
