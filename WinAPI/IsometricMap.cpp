#include "Stdafx.h"
#include "IsometricMap.h"
#include "Laharl.h"
#include "Etna.h"
#include "Vyers.h"
#include "Flonne.h"
#include "Ghost.h"

IsometricMap::IsometricMap():_currentCharacter(nullptr),
							_behaviorList(nullptr),
							_portait(nullptr),
							_damageMeter(nullptr),
							_effectManager(nullptr)
{
}

IsometricMap::~IsometricMap()
{
}


HRESULT IsometricMap::init(void)
{
	return S_OK;
}

HRESULT IsometricMap::init(int mapsizeX, int mapsizeY, bool isshowTileImg, string tileStr)
{
	//todo 맵 데이터, 플레어어 캐릭터, 적 정보를 입력받아서 화면에 뿌린다.
	_currentType = IsoTileType::NONE;

	_behaviorList = new BehaviorList;
	_behaviorList->init();

	_portait = new PortraitAnimation;
	_portait->init();

	_damageMeter = new DamageMeter;
	_damageMeter->init();

	_effectManager = new EffectManager;
	_effectManager->init();

	_mapSize.x = mapsizeX;
	_mapSize.y = mapsizeY;
	_tileAlpha = 100;
	for (int y = 0; y < _mapSize.y; y++)
	{
		vector< IsometricTile* > vXTile;
		for (int x = 0; x < _mapSize.x; x++)
		{
			IsometricTile* tile = new IsometricTile;
			tile->init(
				x, y,
				(_mapSize.y*(RECTANGLE_X*0.5)) + ((x - y)*(RECTANGLE_X*0.5)),
				TILE_START_Y + ((x + y)*(RECTANGLE_Y*0.5)),
				RECTANGLE_X, RECTANGLE_Y);
			tile->setAlpha(&_tileAlpha);
			tile->setIsShowTileImg(isshowTileImg);
			tile->setTileImg(tileStr);
			vXTile.push_back(tile);
		}
		_vTiles.push_back(vXTile);
	}

	_isCharacterMoving = false;
	_onceTileMoveCount = 0;

	_linearStartPoint = PointMake(0, 0);
	_collaborationStartPoint = PointMake(0, 0);
	_isTileAlphaIncrease = true;
	_isRunnigBehavior = false;
	_isRunnigBehaviorSetting = false;
	_thisTurn = TurnSubject::PLAYER;
	_isRunningBeAttackedAnimation = false;
	_isCurrentCharAttacked = true;
	_isPortaitEnd = false;
	_skillMeteoAni = new SkillMeteoAnimation;
	_skillMeteoAni->init();

	return S_OK;
}

void IsometricMap::release(void)
{
	for (vector< IsometricTile* > vXTile : _vTiles)
	{
		for (IsometricTile* tile : vXTile)
		{
			tile->release();
			SAFE_DELETE(tile);
		}
	}
	_vTiles.clear();

	list<GameCharacter*>::iterator _vIterCharList = _characterList.begin();
	for (; _vIterCharList != _characterList.end(); ++_vIterCharList)
	{
		if ((*_vIterCharList)->getUnitType() == E_UnitType::Monster)
		{
			(*_vIterCharList)->release();
			SAFE_DELETE(*_vIterCharList);
		}
		else
		{
			cout << "IsometricMap::release >> (*_vIterCharList)->unregisterZData() start" << endl;
			(*_vIterCharList)->unregisterZData();
			cout << "IsometricMap::release >> (*_vIterCharList)->unregisterZData() end" << endl;
		}
	}
	_characterList.clear();

	_skillMeteoAni->release();
	SAFE_DELETE(_skillMeteoAni);

	_effectManager->release();
	SAFE_DELETE(_effectManager);
	_damageMeter->release();
	SAFE_DELETE(_damageMeter);
	_behaviorList->release();
	SAFE_DELETE(_behaviorList);
}

void IsometricMap::update(void)
{
	_damageMeter->update();
	_effectManager->update();
	_portait->update();
	_skillMeteoAni->update();

	if (_portait->getIsActive())
	{
		_isPortaitEnd = true;
		return;
	}
	else
	{
		if (_isPortaitEnd)
		{
			CAMERA->zoomIn();
			_isPortaitEnd = false;
		}
	}

	list<GameCharacter*>::iterator _vIterCharList = _characterList.begin();
	for (; _vIterCharList != _characterList.end(); ++_vIterCharList)
	{
		(*_vIterCharList)->update();
	}
	
	if (_skillMeteoAni->getIsActive()) return;

	if (_isTileAlphaIncrease) _tileAlpha++;
	else _tileAlpha--;
	if (_tileAlpha < 50 || _tileAlpha > 130) _isTileAlphaIncrease = !_isTileAlphaIncrease;

	//현재 캐릭터 움직일때 애니메이션
	if (_isCharacterMoving)
	{
		if (_vCMovePointsIter != _vCharMovePoints.end())
		{
			POINT linearPt = LinearMovePoint(getcoordinateToPoint(_linearStartPoint), getcoordinateToPoint(*_vCMovePointsIter), SPLIT_COUNT, _onceTileMoveCount);

			int compareX = _linearStartPoint.x - _vCMovePointsIter->x;
			int compareY = _linearStartPoint.y - _vCMovePointsIter->y;
			_currentCharacter->setAniBehavior(E_AniBehavior::Ani_move);

			currentCharacterDirCheck(compareX, compareY);

			_onceTileMoveCount++;
			_currentCharacter->setPoint(linearPt);
			
			if (_onceTileMoveCount >= SPLIT_COUNT)
			{
				_linearStartPoint = (*_vCMovePointsIter);
				++_vCMovePointsIter;
				_onceTileMoveCount = 0;
			}
		}
		else
		{
			_currentCharacter->setCoorPoint(*(_vCMovePointsIter - 1));
			_currentCharacter->setAniBehavior(E_AniBehavior::Ani_idle);
			_vCharMovePoints.clear();
			_isCharacterMoving = false;
			_onceTileMoveCount = 0;
			_linearStartPoint = PointMake(0, 0);
			_vTiles[_pathFindingStartPoint.y][_pathFindingStartPoint.x]->setTileGameCharacter(nullptr);
			_vTiles[_currentCharacter->getCoorPoint().y][_currentCharacter->getCoorPoint().x]->setTileGameCharacter(_currentCharacter);

			if (!(_currentCharacter->getCoorX()== _vTiles[_currentCharacter->getCoorPoint().y][_currentCharacter->getCoorPoint().x]->getCoordinateX() &&
				_currentCharacter->getCoorY() == _vTiles[_currentCharacter->getCoorPoint().y][_currentCharacter->getCoorPoint().x]->getCoordinateY()))
			{
				assert("타일과 캐릭터의 위치가 다름");
			}
		}
		return;
	}

	if (_isRunnigBehavior)
	{
		//행동 셋팅
		if (_isRunnigBehaviorSetting)
		{
			_currentCharacter = _behaviorList->front()->first->getTileGameCharacter();
			if (_currentCharacter->getBehaviorType() != E_BehaviorType::Main2CollaboAttackEnd)
			{
				if (CAMERA->getCameraPoint() == &_collaborationStartPoint)
				{
					CAMERA->setMoveStartPoint(_collaborationStartPoint);
				}
				_collaborationStartPoint = _currentCharacter->getPoint();
			}
			
			CAMERA->moveToTarget(&_collaborationStartPoint);

			POINT enemyPt=_behaviorList->front()->second.front()->getCoorPoint();
			
			int compareX = _currentCharacter->getCoorX() - enemyPt.x;
			int compareY = _currentCharacter->getCoorY() - enemyPt.y;

			currentCharacterDirCheck(compareX, compareY);

			if (_currentCharacter->getBehaviorType() == E_BehaviorType::Attack)
			{
				
				GameCharacter* subCharacter =  getNearSameTypeCharacter(_currentCharacter);

				if (subCharacter != nullptr)
				{
					if (IsSamePoint(enemyPt, subCharacter->getCoorPoint()))
						subCharacter = nullptr;
				}
				if (subCharacter == nullptr)
				{
					_currentCharacter->setAniBehavior(E_AniBehavior::Ani_attack);
					CAMERA->zoomIn();
				}
				else
				{
					//서브캐릭터가 있다면 행동리스트 가장 앞에 삽입
					setFrontPushBehaviorList(
						getTile(subCharacter->getCoorPoint()),
						getTile(_behaviorList->front()->second.front()->getCoorPoint()),
						E_BehaviorType::Sub2CollaboAttackStart);

					subCharacter->setAniDirecttion(_currentCharacter->getAniDirecttion());
					//현재 캐릭터 이동
					_collaborationStartPoint = _currentCharacter->getPoint();
					_currentCharacter->setBehaviorType(E_BehaviorType::Main2CollaboAttackStart);
					_currentCharacter->setSkillMovePoint(PointMake(_collaborationStartPoint.x, _collaborationStartPoint.y-120),10);
					_currentCharacter->setAniBehavior(E_AniBehavior::Ani_Jump);
					_currentCharacter->setReservationAniBehavior(E_AniBehavior::Ani_idle);

					_portait->setPortraitAnimation(_currentCharacter->getBattleFaceIndex());
					_portait->setPortraitAnimation(subCharacter->getBattleFaceIndex());
					_portait->StartAnimation();
				}
			}
			if (_currentCharacter->getBehaviorType() == E_BehaviorType::Skill)
			{
				
				list<pair<GameCharacter*, CSkill*>>::iterator skillIter=_lSavedSkill.begin();
				for (; skillIter != _lSavedSkill.end(); ++skillIter)
				{
					if ((*skillIter).first == _currentCharacter)
					{
						break;
					}
				}

				list<GameCharacter*> tempCharacterList;
				list<IsometricTile*>::iterator inIter = _behaviorList->front()->second.begin();
				int count = 0;
				for (; inIter != _behaviorList->front()->second.end(); ++inIter)
				{
					if ((*inIter)->getTileGameCharacter() != nullptr)
					{
						tempCharacterList.push_back((*inIter)->getTileGameCharacter());
						count++;
					}
				}
				cout <<" count : "<< count << endl;
				_skillMeteoAni->StartAnimation(_currentCharacter, tempCharacterList);
				//_currentCharacter->setAniBehavior(E_AniBehavior::Ani_attack);
			}

			//서브 캐릭터의 어택이 끝나면 현재 캐릭터의 위치를 리셋
			if (_currentCharacter->getBehaviorType() == E_BehaviorType::Main2CollaboAttackEnd)
			{
				_currentCharacter->resetSkillMovePoint(6);
			}
			_isCurrentCharAttacked = false;
			_isRunnigBehaviorSetting = false;

		}
		else
		{
			switch (_currentCharacter->getBehaviorType())
			{
		
			case E_BehaviorType::Sub2CollaboAttackEnd:
				if (!_currentCharacter->getCurrentAnimation()->isPlay())
				{
					_currentCharacter->resetSkillMovePoint(6);
					_currentCharacter->setAniBehavior(E_AniBehavior::Ani_idle);
					_currentCharacter->setBehaviorType(E_BehaviorType::Attack);

					_isRunningBeAttackedAnimation = false;

					if (!_behaviorList->empty())	_isRunnigBehaviorSetting = true;
					else
					{
						_isRunnigBehavior = false;
						_isRunnigBehaviorSetting = false;
					}
				}
				break;
			case E_BehaviorType::Main2CollaboAttackStart:
				if (!_currentCharacter->getCommandState(E_CommandFlag::LinerMoveFlag))
				{
					//점프가 끝났으면 행동 타입을 바꿔주고 서브캐릭터로 교체한다.
					_currentCharacter->setBehaviorType(E_BehaviorType::Main2CollaboAttackEnd);
					_currentCharacter = _behaviorList->front()->first->getTileGameCharacter();
					//서브 캐릭터 Attack
					_currentCharacter->setSkillMovePoint(_collaborationStartPoint, 12);
					_currentCharacter->setAniBehavior(E_AniBehavior::Ani_attack);
				}
				break;
			case E_BehaviorType::Main2CollaboAttackEnd:
				if (!_currentCharacter->getCommandState(E_CommandFlag::LinerMoveFlag))
				{
					//메인 캐릭터가 내려오면 공격 애니메이션을 실행한다.
					_currentCharacter->setBehaviorType(E_BehaviorType::Attack);
					_currentCharacter->setAniBehavior(E_AniBehavior::Ani_attack);
				}
				break;
			case E_BehaviorType::NONE:
				break;
			default:
				break;
			}
		
			//타격
			if (_currentCharacter->IsAttackIndex() && !_isCurrentCharAttacked||
				(_currentCharacter->getBehaviorType() == E_BehaviorType::Skill && !_skillMeteoAni->getIsActive()))
			{
				CAMERA->shakeStart(0.5f);
				_isCurrentCharAttacked = true;
				_startBeAttackedAnimationTime = TIMEMANAGER->getWorldTime();

				//공격당한 캐릭터의 애니메이션을 재생시킨다.
				while (!_behaviorList->front()->second.empty())
				{
					bool isRemoveCharacter = false;
					GameCharacter* attackedChar = _behaviorList->front()->second.front()->getTileGameCharacter();
					if (attackedChar != nullptr)
					{
						attackedChar->setAniBehavior(E_AniBehavior::Ani_be_Attacked);
						attackedChar->shakeStart(1.5f);

						int damage = 0;
						if (_currentCharacter->getBehaviorType() == E_BehaviorType::Skill)
						{
							damage = computeDamage(_currentCharacter, attackedChar);
							list<pair<GameCharacter*, CSkill*>>::iterator skillIter = _lSavedSkill.begin();
							for (; skillIter != _lSavedSkill.end(); ++skillIter)
							{
								if ((*skillIter).first == _currentCharacter)
								{
									break;
								}
							}
							damage *= (*skillIter).second->getDamageCalculation();
						}
						else
						{
							damage = computeDamage(_currentCharacter, attackedChar);
						}
						attackedChar->beAttacked(damage);

						//데미지 미터기
						_damageMeter->createDamageEffect(PointMake(attackedChar->getPoint().x, attackedChar->getPoint().y - 50), damage < 0 ? 1 : damage);

						_effectManager->createParticleEffect("particle", PointMake(attackedChar->getPoint().x, attackedChar->getPoint().y - 30), 8, false, 150, 20, 5, 60, 30);

						if (attackedChar->getIsDie() && _currentCharacter->getBehaviorType() != E_BehaviorType::Sub2CollaboAttackStart)
						{
							//레벨업을 하면 true를 반환한다.
							if (_currentCharacter->addExp(attackedChar->getCharicterAllStats()->_exp))
							{
								_effectManager->createEffect("LevelUp", PointMake(_currentCharacter->getPoint().x, _currentCharacter->getPoint().y - 30), 6, true, 100, 244, 10.0f);
							}
							_behaviorList->removeBehavior(getTile(attackedChar->getCoorPoint()));
							removeCharacter(attackedChar);
							isRemoveCharacter = true;
						}
					}
					
					if (!_behaviorList->front()->second.empty() && !isRemoveCharacter)
					{
						/*bool hasChar = _behaviorList->front()->second.front()->getTileGameCharacter() != nullptr;
						cout << "tile: " << _behaviorList->front()->second.front() << (hasChar? " true":" false") << endl;*/
						_behaviorList->front()->second.pop_front();
					}
				}
				if (!_behaviorList->empty()) _behaviorList->pop_front();

				switch (_currentCharacter->getBehaviorType())
				{
				case E_BehaviorType::Attack:
					_currentCharacter->setReservationAniBehavior(E_AniBehavior::Ani_idle);
					_currentCharacter->setBehaviorType(E_BehaviorType::Attack);
					_isRunningBeAttackedAnimation = true;
					break;
				case E_BehaviorType::Sub2CollaboAttackStart:
					_currentCharacter->setBehaviorType(E_BehaviorType::Sub2CollaboAttackEnd);
					break;
				case E_BehaviorType::Skill:
					_currentCharacter->setReservationAniBehavior(E_AniBehavior::Ani_idle);
					_currentCharacter->setBehaviorType(E_BehaviorType::Attack);
					_isRunningBeAttackedAnimation = true;
					break;
				}
			}   

			if (TIMEMANAGER->getWorldTime() > _startBeAttackedAnimationTime + 0.8f && _isRunningBeAttackedAnimation)
			{
				CAMERA->zoomReset();
				_isRunningBeAttackedAnimation = false;

				_behaviorList->confirmSecond();
				if (!_behaviorList->empty())
				{
					_isRunnigBehaviorSetting = true;
				}
				else
				{
					_isRunnigBehavior = false;
					_isRunnigBehaviorSetting = false;
				}
			}
		}
		return;
	}


	if (_thisTurn == TurnSubject::ENUMY)
	{
		if (!_isEnemyMoveEnd)
		{
			if (!_currentCharacter->getCommandState(E_CommandFlag::moveFlag))
			{
				IsometricTile* enmeyTargetPoint = computeEnemyMoveTargetTile(_currentCharacter);

				_currentCharacter->setCommandState(E_CommandFlag::moveFlag, true);
				if (enmeyTargetPoint != nullptr)
				{
					setAstarEndPoint(enmeyTargetPoint->getCoorPoint());
					OnTriggerPathfinding();
					CAMERA->moveToTarget(_currentCharacter->getPointAddress());
					CAMERA->zoomOut();
				}
			}
			else enemyNextMoveTurn();
		}
		else
		{
			CAMERA->zoomReset();
			for (GameCharacter* currentEnemy : _characterList)
			{
				if (currentEnemy->getUnitType() == E_UnitType::Monster &&
					!currentEnemy->getCommandState(E_CommandFlag::behaviorFalg))
				{
					IsometricTile* targetTile = computeEnemyAttackRangeInPlayerTile(currentEnemy);
					IsometricTile* enemyTile = getTile(currentEnemy->getCoorPoint());
					currentEnemy->setCommandState(E_CommandFlag::behaviorFalg, true);

					if (targetTile != nullptr)
					{
						setBehaviorList(enemyTile, targetTile,E_BehaviorType::Attack);
					}
				}
			}
			StartBehavior();
		}
	}

	CheckEnemyTurnEnd();

	
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_currentType = IsoTileType::WALL;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		resetTilesAstarData();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (vector< IsometricTile* > vXTile : _vTiles)
		{
			for (IsometricTile* tile : vXTile)
			{
				POINT target = PointMake(abs(_ptMouse.x - tile->getX()), abs(_ptMouse.y - tile->getY()));
				POINT p1 = PointMake(0, 0);
				POINT p2 = PointMake( RECTANGLE_X * 0.5, 0 );
				POINT p3 = PointMake( 0, RECTANGLE_Y * 0.5 );
				if (PointtInTriangle(target, p1, p2, p3))
				{
					tile->setTileType(_currentType);
					break;
				}
			}
		}
	}

	
}

void IsometricMap::currentCharacterDirCheck(int compareX, int compareY)
{
	if (compareX >= 0 && compareY < 0)
	{
		_currentCharacter->setAniDirecttion(E_AniDirection::Ani_Left_Bottom);
	}
	else if (compareX > 0 && compareY >= 0)
	{
		_currentCharacter->setAniDirecttion(E_AniDirection::Ani_Left_Top);
	}
	else if (compareX <= 0 && compareY > 0)
	{
		_currentCharacter->setAniDirecttion(E_AniDirection::Ani_Right_Top);
	}
	else if (compareX < 0 && compareY <= 0)
	{
		_currentCharacter->setAniDirecttion(E_AniDirection::Ani_Right_Bottom);
	}
}

void IsometricMap::render(void)
{

	for (vector< IsometricTile* > vXTile : _vTiles) 
	{
		for (IsometricTile* tile : vXTile)
		{
			tile->render();
		}
	}
	
	/*for (GameCharacter* character : _characterList)
	{
		character->render();
	}*/
	_damageMeter->render();
	_effectManager->render();
	_skillMeteoAni->render();
}

void IsometricMap::removeCharacter(GameCharacter* character)
{
	cout << "IsometricMap::removeCharacter >>getTile(character->getCoorPoint()) : " << getTile(character->getCoorPoint()) << endl;
	getTile(character->getCoorPoint())->setTileGameCharacter(nullptr);
	
	list<GameCharacter*>::iterator iter = _characterList.begin();
	for (; iter != _characterList.end();)
	{
		if ((*iter) == character)
		{
			iter = _characterList.erase(iter);
		}
		else ++iter;
	}

	if (character->getUnitType() == E_UnitType::Monster)
	{
		character->release();
		SAFE_DELETE(character);
	}
	else
	{
		character->unregisterZData();
	}
	
}

void IsometricMap::setPlayerCharacter(GameCharacter* gameChar, int coorX, int coorY)
{
	gameChar->setCoorPoint(PointMake(coorX, coorY));
	gameChar->setPoint(getcoordinateToPoint(coorX, coorY));
	gameChar->setBeforeCoorPoint(PointMake(coorX, coorY));
	_vTiles[coorY][coorX]->setTileGameCharacter(gameChar);
	_characterList.push_back(gameChar);
	gameChar->registerZData();
}

void IsometricMap::setEnemyCharacter(E_ENEMY_CHARACTER enemy, int coorX, int coorY, int level, int move, int jump, int maxHp, int hp, int maxSp, int sp, int atk, int def, int mint, int speed, int hit, int res, int exp, int maxExp)
{
	GameCharacter* newCharacter = nullptr;
	switch (enemy)
	{
	case E_ENEMY_CHARACTER::Vyers:
		newCharacter = new Vyers;
		newCharacter->init("Vyers", getcoordinateToPoint(coorX, coorY).x, getcoordinateToPoint(coorX, coorY).y, coorX, coorY, E_UnitType::Monster, 0, 20);
		break;
	case E_ENEMY_CHARACTER::Ghost:
		newCharacter = new Ghost;
		newCharacter->init("Ghost", getcoordinateToPoint(coorX, coorY).x, getcoordinateToPoint(coorX, coorY).y, coorX, coorY, E_UnitType::Monster, 0, 20);
		break;
	default:
		assert("예상치 못한 인수");
		break;
	}
	newCharacter->getCharicterStats()->setStat(level, move, jump, maxHp, hp, maxSp, sp, atk, def, mint, speed, hit, res, exp, maxExp);

	_vTiles[coorY][coorX]->setTileGameCharacter(newCharacter);
	_characterList.push_back(newCharacter);
	newCharacter->registerZData();

}

GameCharacter* IsometricMap::getNearSameTypeCharacter(GameCharacter* curCharacter)
{
	GameCharacter* returnCharacter = nullptr;
	startComputeTileRange(2, curCharacter->getCoorPoint(), false);
	while (!_vTileRange.empty())
	{
		if (_vTileRange.back()->getSelectAbleTile())
		{
			if (curCharacter != _vTileRange.back()->getTileGameCharacter())
			{
				if (curCharacter->getUnitType() ==
					_vTileRange.back()->getTileGameCharacter()->getUnitType())
				{
					returnCharacter = _vTileRange.back()->getTileGameCharacter();
				}
			}
		}
		_vTileRange.back()->setSelectAbleTile(false);
		_vTileRange.back()->showTileRange(false);
		_vTileRange.pop_back();
	}

	return returnCharacter;
}

void IsometricMap::resetTilesAstarData()
{
	for (vector< IsometricTile* > vXTile : _vTiles)
	{
		for (IsometricTile* tile : vXTile)
		{
			tile->AstarDataReset();
		}
	}
}

void IsometricMap::resetTilesAstarDataExceptWall(void)
{
	for (vector< IsometricTile* > vXTile : _vTiles)
	{
		for (IsometricTile* tile : vXTile)
		{
			if (tile->getTileType() == IsoTileType::WALL)
			{
				continue;
			}
			tile->AstarDataReset();
		}
	}
}

bool IsometricMap::PointtInTriangle(POINT target, POINT p1, POINT p2, POINT p3)
{
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(target, p1, p2);
	d2 = sign(target, p2, p3);
	d3 = sign(target, p3, p1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

float IsometricMap::sign(POINT p1, POINT p2, POINT p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

stack<POINT> IsometricMap::startPathfinding(IsometricTile* start, IsometricTile* target)
{
	priority_queue< IsometricTile*, vector<IsometricTile*>, IsometricTile::isocmp> pqOpenList;
	IsometricTile* currentTile = nullptr;
	IsometricTile* findTile = nullptr;

	currentTile = start;

	currentTile->setG(computeGcost(currentTile,target));
	currentTile->setH(0);
	currentTile->setF(currentTile->getG() + currentTile->getH());

	pqOpenList.push(currentTile);

	while (!pqOpenList.empty())
	{
		currentTile = pqOpenList.top();
		if (currentTile == target)
		{
			stack<POINT> coorPoint;
			coorPoint.push(currentTile->getCoorPoint());

			currentTile->setTileType(IsoTileType::ASTAR_END);
			IsometricTile* parentTile = currentTile->getParentTile();
			
			while (true)
			{
				coorPoint.push(parentTile->getCoorPoint());
				parentTile->setTileType(IsoTileType::ASTAR_END);
				if (parentTile == start)break;
				parentTile = parentTile->getParentTile();
			}
			return coorPoint;
		}
		currentTile->setTileType(IsoTileType::CLOSE);
		pqOpenList.pop();

		int cX = currentTile->getCoordinateX();
		int cY = currentTile->getCoordinateY();

		for (int i =0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
				if (cX - 1 < 0 || cX - 1 > _mapSize.x - 1) continue;
				findTile = _vTiles[cY][cX - 1];
				break;
			case 1:
				if (cX + 1 < 0 || cX + 1 > _mapSize.x - 1) continue;
				findTile = _vTiles[cY][cX + 1];
				break;
			case 2:
				if (cY - 1 < 0 || cY - 1 > _mapSize.y - 1) continue;
				findTile = _vTiles[cY - 1][cX];
				break;
			case 3:
				if (cY + 1 < 0 || cY + 1 > _mapSize.y - 1) continue;
				findTile = _vTiles[cY + 1][cX];
				break;
			}

			if ((findTile->getTileType() == IsoTileType::OPEN ||
				findTile->getTileType() == IsoTileType::NONE ||
				findTile->getTileType() == IsoTileType::TARGET)&&
				findTile->getTileGameCharacter() == nullptr)
			{
				findTile->setTileType(IsoTileType::OPEN);
				findTile->setParentTile(currentTile);
				findTile->setG(computeGcost(findTile, target));
				if (findTile->getParentTile() != nullptr)
				{
					findTile->setH(findTile->getParentTile()->getH() + 10);
				}
				findTile->setF(findTile->getG() + findTile->getH());
				pqOpenList.push(findTile);
			}
		}
	}

}

bool IsometricMap::OnTriggerPathfinding()
{
	resetTilesAstarDataExceptWall();
	setAstarStartPoint(_vTiles[_currentCharacter->getCoorY()][_currentCharacter->getCoorX()]->getCoorPoint());
	if (_currentCharacter == nullptr)
	{
		cout << "캐릭터 없음" << endl;
		return false;
	}
	else if (_pathFindingStartPoint.x == _pathFindingEndPoint.x && _pathFindingStartPoint.y == _pathFindingEndPoint.y)
	{
		cout << "스타트 지점과 시작지점이 같음" << endl;
		return false;
	}
	
	IsometricTile* start = _vTiles[_pathFindingStartPoint.y][_pathFindingStartPoint.x];
	IsometricTile* target = _vTiles[_pathFindingEndPoint.y][_pathFindingEndPoint.x];
	
	start->setTileType(IsoTileType::START);
	target->setTileType(IsoTileType::TARGET);

	if (target == nullptr)
	{
		cout << "target 없음" << endl;
		return false;
	}
	else if (target->getTileGameCharacter() != nullptr)
	{
		cout << "target 지점에 캐릭터가 있음" << endl;
		return false;
	}
	else if (start ==nullptr)
	{
		cout << "start 없음" << endl;
		return false;
	}

	stack<POINT> movePoints = startPathfinding(start, target);
	while (!movePoints.empty())
	{
		_vCharMovePoints.push_back(movePoints.top());
		movePoints.pop();
	}

	_isCharacterMoving = true;
	_vCMovePointsIter = _vCharMovePoints.begin();
	_linearStartPoint = (*_vCMovePointsIter);

}

int IsometricMap::computeGcost(IsometricTile* curTile, IsometricTile* targetTile)
{
	int gCost=0;
	int gx = abs(curTile->getCoordinateX() - targetTile->getCoordinateX());
	int gy = abs(curTile->getCoordinateY() - targetTile->getCoordinateY());

	//gcost compute
	if (gx > gy)
	{
		gCost = (gy * 14) + ((gx - gy) * 10);
	}
	else
	{
		gCost = (gx * 14) + ((gy - gx) * 10);
	}

	return gCost;
}

POINT IsometricMap::getcoordinateToPoint(int coorx, int coory)
{
	correctionTileIndex(coorx, coory);
	
	return _vTiles[coory][coorx]->getPoint();
}


POINT IsometricMap::getcoordinateToPoint(POINT coordinate)
{
	correctionTileIndex(coordinate);

	return _vTiles[coordinate.y][coordinate.x]->getPoint();
}


void IsometricMap::setAstarEndPoint(POINT EndPoint)
{
	correctionTileIndex(EndPoint);

	for (vector< IsometricTile* > vXTile : _vTiles)
	{
		for (IsometricTile* tile : vXTile)
		{
			if (tile->getTileType() == IsoTileType::TARGET)
			{
				tile->setTileType(IsoTileType::NONE);
			}
		}
	}

	_pathFindingEndPoint = EndPoint;

}

void IsometricMap::setAstarStartPoint(POINT StartPoint)
{
	correctionTileIndex(StartPoint);
	for (vector< IsometricTile* > vXTile : _vTiles)
	{
		for (IsometricTile* tile : vXTile)
		{
			if (tile->getTileType() == IsoTileType::START)
			{
				tile->setTileType(IsoTileType::NONE);
			}
		}
	}

	_pathFindingStartPoint = StartPoint;
}
void IsometricMap::resetCharacterMove(void)
{
	if (_currentCharacter->getCommandState(E_CommandFlag::behaviorFalg))
	{
		//todo 실행 실패 소리
	}
	else if(_currentCharacter->getCommandState(E_CommandFlag::moveFlag))
	{
		POINT beforePt = _currentCharacter->getBeforeCoorPoint();
		POINT currentPt = _currentCharacter->getCoorPoint();
		_vTiles[currentPt.y][currentPt.x]->setTileGameCharacter(nullptr);
		_currentCharacter->setCoorPoint(beforePt);
		_currentCharacter->setPoint(getcoordinateToPoint(beforePt));
		_vTiles[beforePt.y][beforePt.x]->setTileGameCharacter(_currentCharacter);
		_currentCharacter->setCommandState(E_CommandFlag::moveFlag, false);

	}
}

IsometricTile* IsometricMap::getTile(POINT coor)
{
	return 	_vTiles[coor.y][coor.x];
}

GameCharacter* IsometricMap::selectCharacter(POINT coor)
{
	if (_vTiles[coor.y][coor.x]->getTileGameCharacter() != nullptr)
	{
		for (GameCharacter* character : _characterList)
		{
			if (_vTiles[coor.y][coor.x]->getTileGameCharacter() == character)
			{
				_currentCharacter = character;
				return _currentCharacter;
			}
		}
	}

	_currentCharacter = nullptr;
	return nullptr;
}

GameCharacter* IsometricMap::getCharacter(POINT coorPt)
{
	list<GameCharacter*>::iterator iter = _characterList.begin();
	for (; iter != _characterList.end(); ++iter)
	{
		if ((*iter)->getCoorPoint().x == coorPt.x &&
			(*iter)->getCoorPoint().y == coorPt.y)
		{
			return *iter;
		}
	}

	return nullptr;
}


void IsometricMap::setBehaviorList(IsometricTile* excuteUnitTile, IsometricTile * target, E_BehaviorType behavior)
{
	excuteUnitTile->getTileGameCharacter()->setBehaviorType(behavior);
	_behaviorList->setBehaviorList(excuteUnitTile, target);
}

void IsometricMap::setFrontPushBehaviorList(IsometricTile * excuteUnitTile, IsometricTile * target, E_BehaviorType behavior)
{
	excuteUnitTile->getTileGameCharacter()->setBehaviorType(behavior);
	_behaviorList->setFrontPushBehaviorList(excuteUnitTile, target);
}

void IsometricMap::setBehaviorList(IsometricTile* excuteUnitTile, list<IsometricTile*> targetlist, E_BehaviorType behavior)
{
	excuteUnitTile->getTileGameCharacter()->setBehaviorType(behavior);
	_behaviorList->setBehaviorList(excuteUnitTile, targetlist);
}

void IsometricMap::cancelBehavior(IsometricTile* excuteUnitTile)
{
	excuteUnitTile->getTileGameCharacter()->setBehaviorType(E_BehaviorType::NONE);
	if (!_behaviorList->cancelBehavior(excuteUnitTile))
	{
		assert("IsometricMap::cancelBehavior -> fail");
	}
}

void IsometricMap::StartBehavior(void)
{
	if (!_behaviorList->empty())
	{
		_isRunnigBehavior = true;
		_isRunnigBehaviorSetting = true;
	}
	//타일에 캐릭터 
}

void IsometricMap::TurnEnd(TurnSubject subject)
{
	
	for (GameCharacter* tempChar : _characterList)
	{
		switch (subject)
		{
		case TurnSubject::PLAYER:
			_thisTurn = TurnSubject::ENUMY;
			if (tempChar->getUnitType() == E_UnitType::Controllable)
				tempChar->TurnEnd();
			break;
		case TurnSubject::ENUMY:
			_thisTurn = TurnSubject::PLAYER;
			if (tempChar->getUnitType() == E_UnitType::Monster)
				tempChar->TurnEnd();
			break;
		}
	}

	GameCharacter* tempChar = nullptr;
	while (!_behaviorList->empty())
	{
		tempChar = _behaviorList->front()->first->getTileGameCharacter();
		tempChar->setBehaviorType(E_BehaviorType::NONE);
		_behaviorList->pop_front();
	}
}

void IsometricMap::enemyNextMoveTurn(void)
{
	list<GameCharacter*>::iterator iter = _characterList.begin();
	for(; iter != _characterList.end(); ++iter)
	{
		if ((*iter)->getUnitType() == E_UnitType::Monster &&
			!(*iter)->getCommandState(E_CommandFlag::moveFlag))
		{
			_currentCharacter = (*iter);
			return;
		}
	}
	_isEnemyMoveEnd = true;
}

void IsometricMap::StartEnemyTrun(void)
{
	_thisTurn = TurnSubject::ENUMY;
	_isEnemyMoveEnd = false;
	enemyNextMoveTurn();
}

void IsometricMap::CheckEnemyTurnEnd(void)
{
	if (_thisTurn == TurnSubject::PLAYER) return;

	bool isMoveFinishOfAllCharacter = true;
	bool isBehaviorFinishOfAllCharacter = true;

	for (GameCharacter* tempChar : _characterList)
	{
		if (tempChar->getUnitType() == E_UnitType::Monster)
		{
			if (tempChar->getCommandState(E_CommandFlag::moveFlag) == false)
			{
				isMoveFinishOfAllCharacter = false;
			}
			if (tempChar->getCommandState(E_CommandFlag::behaviorFalg) == false)
			{
				isBehaviorFinishOfAllCharacter = false;
			}
		}
	}

	if (isMoveFinishOfAllCharacter && isBehaviorFinishOfAllCharacter && _behaviorList->empty())
	{
		TurnEnd(TurnSubject::ENUMY);
		cout << "IsometricMap::CheckEnemyTurnEnd >> turn end" << endl;
	}

}

void IsometricMap::computeTileRange(int range, IsometricTile* currentTile, bool isMove, bool playerAroundSearch)
{
	POINT cPoint = currentTile->getCoorPoint();

	if (range <= 0)return;
	else if (currentTile->getShowTileRange()) 
	{
		if (currentTile->getTileGameCharacter() == nullptr)
		{
			return; 
		}
	}
	else if (currentTile->getTileType() == IsoTileType::WALL) return;

	_vTileRange.push_back(currentTile);

	currentTile->showTileRange(true);
	if (currentTile->getTileGameCharacter() != nullptr)
	{
		if (isMove)
		{
			currentTile->setSelectAbleTile(false);
			if (!IsSamePoint(_currentCharacter->getCoorPoint(), cPoint)&& !playerAroundSearch)
			{
				return;
			}
		}
		else
			currentTile->setSelectAbleTile(true);
	}
	else
	{
		if (isMove)
			currentTile->setSelectAbleTile(true);
		else
			currentTile->setSelectAbleTile(false);
	}
	
	
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			if (cPoint.x - 1 < 0 || cPoint.x - 1 > _mapSize.x - 1) continue;
			_qBFSTile.push(make_pair(range - 1, _vTiles[cPoint.y][cPoint.x - 1]));
			break;
		case 1:
			if (cPoint.x + 1 < 0 || cPoint.x + 1 > _mapSize.x - 1) continue;
			_qBFSTile.push(make_pair(range - 1,  _vTiles[cPoint.y][cPoint.x + 1]));
			break;
		case 2:
			if (cPoint.y - 1 < 0 || cPoint.y - 1 > _mapSize.y - 1) continue;
			_qBFSTile.push(make_pair(range - 1, _vTiles[cPoint.y - 1][cPoint.x]));
			break;
		case 3:
			if (cPoint.y + 1 < 0 || cPoint.y + 1 > _mapSize.y - 1) continue;
			_qBFSTile.push(make_pair(range - 1, _vTiles[cPoint.y + 1][cPoint.x]));
			break;
		}
	}
	
}

void IsometricMap::startComputeTileRange(int range, POINT startTilePoint, bool isMove, bool playerAroundSearch)
{
	_qBFSTile.push(make_pair(range, _vTiles[startTilePoint.y][startTilePoint.x]));
	
	while (!_qBFSTile.empty())
	{
		computeTileRange(_qBFSTile.front().first, _qBFSTile.front().second,isMove, playerAroundSearch);
		_qBFSTile.pop();
	}

}

void IsometricMap::resetTileRange(void)
{
	while (!_vTileRange.empty())
	{
		_vTileRange.back()->setSelectAbleTile(false);
		_vTileRange.back()->showTileRange(false);
		_vTileRange.pop_back();
	}

}

bool IsometricMap::IsEmptyPlayerCharacter(void)
{
	list<GameCharacter*>::iterator iter = _characterList.begin();
	for (; iter != _characterList.end(); ++iter)
	{
		if ((*iter)->getUnitType() == E_UnitType::Controllable )
		{
			return false;
		}
	}
	return true;
}

bool IsometricMap::IsEmptyEnemyCharacter(void)
{
	list<GameCharacter*>::iterator iter = _characterList.begin();
	for (; iter != _characterList.end(); ++iter)
	{
		if ((*iter)->getUnitType() == E_UnitType::Monster)
		{
			return false;
		}
	}
	return true;
}



GameCharacter* IsometricMap::computeNearControlableCharacter(GameCharacter* curCharacter)
{
	GameCharacter* returnCharacter = nullptr;
	float minDistance=10000.0f;
	float compareDistance = 0;
	for (GameCharacter* tempChar : _characterList)
	{
		if (tempChar->getUnitType() == E_UnitType::Controllable)
		{
			compareDistance = getDistance(curCharacter->getPoint().x, curCharacter->getPoint().y, tempChar->getPoint().x, tempChar->getPoint().y);
			if (minDistance > compareDistance)
			{
				minDistance = compareDistance;
				returnCharacter = tempChar;
			}
		}
	}

	return returnCharacter;
}

IsometricTile* IsometricMap::computeEnemyMoveTargetTile(GameCharacter* curCharacter)
{
	IsometricTile* returnTile = nullptr;
	IsometricTile* originTargetTile = nullptr;
	int minDistance = 10000;
	int compareDistance = 0;

	list<GameCharacter*>::iterator iter = _characterList.begin();
	for (; iter != _characterList.end();++iter)
	{
		if ((*iter)->getUnitType() == E_UnitType::Controllable)
		{
			startComputeTileRange(curCharacter->getAttackRange(), (*iter)->getCoorPoint(), true, true);
		}
	}

	while (!_vTileRange.empty())
	{
		if (_vTileRange.back()->getSelectAbleTile())
		{
			compareDistance = computeGcost(getTile(curCharacter->getCoorPoint()), _vTileRange.back());
			if (minDistance > compareDistance)
			{
				minDistance = compareDistance;
				originTargetTile = _vTileRange.back();
			}
		}

		_vTileRange.back()->setSelectAbleTile(false);
		_vTileRange.back()->showTileRange(false);
		_vTileRange.pop_back();
	}

	if (originTargetTile == nullptr)	return nullptr;

	startComputeTileRange(curCharacter->getCharicterAllStats()->_move, curCharacter->getCoorPoint(), true);
	minDistance = 10000;
	compareDistance = 0;


	while (!_vTileRange.empty())
	{
		if (_vTileRange.back()->getSelectAbleTile())
		{

			compareDistance = computeGcost(originTargetTile, _vTileRange.back());
			if (minDistance > compareDistance)
			{
				minDistance = compareDistance;
				returnTile = _vTileRange.back();
			}
		}

		_vTileRange.back()->setSelectAbleTile(false);
		_vTileRange.back()->showTileRange(false);
		_vTileRange.pop_back();
	}

	return returnTile;
}


IsometricTile* IsometricMap::computeEnemyAttackRangeInPlayerTile(GameCharacter* currentEnemy)
{
	IsometricTile* returnTile = nullptr;
	
	startComputeTileRange(currentEnemy->getAttackRange(), currentEnemy->getCoorPoint(), false);

	while (!_vTileRange.empty())
	{
		if (_vTileRange.back()->getSelectAbleTile() &&
			_vTileRange.back() != getTile(currentEnemy->getCoorPoint())&&
			_vTileRange.back()->getTileGameCharacter()->getUnitType() != currentEnemy->getUnitType())
		{
			returnTile = _vTileRange.back();
		}

		_vTileRange.back()->setSelectAbleTile(false);
		_vTileRange.back()->showTileRange(false);
		_vTileRange.pop_back();
	}

	return returnTile;
}

void IsometricMap::setBehaviorSkill(GameCharacter* Gchar, CSkill * skill)
{
	list<IsometricTile*> tempTileList;

	vector<IsometricTile*>::iterator iter = _vTileRange.begin();
	for (; iter != _vTileRange.end(); ++iter)
	{
		if (getTile(Gchar->getCoorPoint()) != *iter)
		{
			tempTileList.push_back(*iter);
		}
	}

	_lSavedSkill.push_back(make_pair( Gchar, skill));
	setBehaviorList(getTile(Gchar->getCoorPoint()), tempTileList, E_BehaviorType::Skill);
	resetTileRange();
}

//POINT IsometricMap::lerp(POINT start, POINT end, float percentage)
//{
//	if (0 > percentage) percentage = 0;
//	else if (percentage > 1) percentage = 1;
//	LONG x = start.x + ((end.x - start.x) * percentage);
//	LONG y = start.y + ((end.y - start.y) * percentage);
//
//	return { x,y };
//}


void IsometricMap::correctionTileIndex(int &coorx, int &coory)
{
	if (coorx < 0) coorx = 0;
	else if (coorx > _mapSize.x - 1)
	{
		coorx = _mapSize.x-1;
	}
	else if (coory < 0) coory = 0;
	else if (coory > _mapSize.y - 1)
	{
		coory = _mapSize.y-1;
	}
}

void IsometricMap::correctionTileIndex(POINT &coordinate)
{
	if (coordinate.x < 0) coordinate.x = 0;
	else if (coordinate.x > _mapSize.x - 1)
	{
		coordinate.x = _mapSize.x-1;
	}
	else if (coordinate.y < 0) coordinate.y = 0;
	else if (coordinate.y > _mapSize.y - 1)
	{
		coordinate.y = _mapSize.y-1;
	}
}

int IsometricMap::computeDamage(GameCharacter* subject, GameCharacter* beAttackChar)
{
	int att = subject->getCharicterAllStats()->_atk;
	int correction = (int)RND->getFloat(att * 0.30f);
	int def = beAttackChar->getCharicterAllStats()->_def * 0.5;

	if (RND->getInt(1) == 0) return att + correction - def;
	else return att - correction - def;
}

