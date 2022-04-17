#include "Stdafx.h"
#include "TurnSystem.h"
#include "IsometricMap.h"

HRESULT TurnSystem::init(void)
{
	_startPt = PointMake(0, 0);
	_mapSize = _map->getMapSize();
	_isCharacterMove = _map->getIsCharacterMove();
	_isRunnigBehavior = _map->getIsRunningBehavior();
	
	_isCharacterSelect = false; 
	_selectedCharRange = 0;
	_playerCharSize = 0;
	_okBtnState = EOkBtnState::Nomal;
	_controlState = EControl_State::Map_Cursor;

	characterWindowSetup();
	turnWindowSetup();
	_charCreateWindow = new CWindowUI;
	_charCreateWindow->init(300, 4, 80, EWindow_Align::WINDOW_LEFTTOP);

	_infoUI = new CharInfoUI;
	_infoUI->init();
	
	CALLBACKFUNCTION turnEnd = [this](void)->void
	{
		_isPlayerTrunStart = false;
		_map->TurnEnd(TurnSubject::PLAYER);
		_map->StartEnemyTrun();
	};

	_turnStateUI = new TurnStateUI;
	_turnStateUI->init(turnEnd);

	_charStatusUI = new CharStatusUI;
	_charStatusUI->init(40, 5);
	_charStatusUI->setIsActive(false);

	_battleUi[UI_MAPSIGN] = new GameMapUI;
	_battleUi[UI_MAPSIGN]->init("mapSign", PointMake(5, 5), _map->getcoordinateToPoint(5, 5), ZIndexType_MapUI);
	_battleUi[UI_MAPSIGN]->setIsActive(true);

	_battleUi[UI_BLUESIGN] = new GameMapUI;
	_battleUi[UI_BLUESIGN]->init("blueSign", PointMake(0, 0), _map->getcoordinateToPoint(5, 5), PointMake(0, -70), ZIndexType_BlueUI);
	_battleUi[UI_BLUESIGN]->setIsActive(true);

	_battleUi[UI_BattleStartObj] = new GameMapUI;
	_battleUi[UI_BattleStartObj]->init("battleStartObject", _startPt, _map->getcoordinateToPoint(_startPt), ZIndexType_MapUI);
	_battleUi[UI_BattleStartObj]->setIsActive(true);

	CAMERA->setCameraPoint(_battleUi[UI_MAPSIGN]->getPointAddress());
	_vPlayerChar = *GAMEMANAGER->getAllPlayerUnits();

	return S_OK; 
}

void TurnSystem::release(void)
{
	_vPlayerChar.clear();

	_charStatusUI->release();
	_battleUi[UI_MAPSIGN]->release();
	_battleUi[UI_BattleStartObj]->release();
	_battleUi[UI_BLUESIGN]->release();
	_charBehaviorWindow->release();
	_turnWindow->release();
	_infoUI->release();
	_turnStateUI->release();
	_charCreateWindow->release();


	SAFE_DELETE(_charStatusUI);
	SAFE_DELETE(_battleUi[UI_MAPSIGN]);
	SAFE_DELETE(_battleUi[UI_BLUESIGN]);
	SAFE_DELETE(_battleUi[UI_BattleStartObj]);
	SAFE_DELETE(_charBehaviorWindow);
	SAFE_DELETE(_turnWindow);
	SAFE_DELETE(_infoUI);
	SAFE_DELETE(_turnStateUI);
	SAFE_DELETE(_charCreateWindow);
}

void TurnSystem::update(void)
{
	_infoUI->update();
	_turnStateUI->update();
	_charStatusUI->update();
	_charCreateWindow->update();

	_battleUi[UI_MAPSIGN]->update();
	_battleUi[UI_BLUESIGN]->update();
	_battleUi[UI_BattleStartObj]->update();
	_charBehaviorWindow->update();
	_turnWindow->update();
	if (*_isCharacterMove || *_isRunnigBehavior || _map->getTurnSubject() == TurnSubject::ENUMY) 
	{
		_battleUi[UI_MAPSIGN]->setIsActive(false);
		_battleUi[UI_BLUESIGN]->setIsActive(false);
		_infoUI->setIsActive(false);
		_charStatusUI->setIsActive(false);
		return;
	}
	else
	{
		_battleUi[UI_MAPSIGN]->setIsActive(true);
		_battleUi[UI_BLUESIGN]->setIsActive(true);
	}

	if (!_isPlayerTrunStart)
	{
		_isPlayerTrunStart = true;
		CAMERA->moveToTarget(_battleUi[UI_MAPSIGN]->getPointAddress(), UI_CAMERA_MOVEING_SPEED);
		_turnStateUI->StartTurnStateAnimation(true);
	}
	
	switch (_controlState)
	{
	case EControl_State::Map_Cursor:
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			if (CAMERA->getIsFollowingCameraToTarget()) { break; }
			if (CAMERA->getCameraPoint() == _battleUi[UI_MAPSIGN]->getPointAddress())
			{
				CAMERA->setMoveStartPoint(_battleUi[UI_MAPSIGN]->getPoint());
			}
			_battleUi[UI_MAPSIGN]->setCoordinateY(correctionYIndex(_battleUi[UI_MAPSIGN]->getCoordinateY() - 1));
			updateBattleUI();

			CAMERA->moveToTarget(_battleUi[UI_MAPSIGN]->getPointAddress(), UI_CAMERA_MOVEING_SPEED);
			GameCharacter* thisCoorCharacter = _map->getCharacter(_battleUi[UI_MAPSIGN]->getCoorPoint());
			if (thisCoorCharacter != nullptr)
			{
				_infoUI->setIsActive(true);
				_infoUI->infoCharater(thisCoorCharacter);
			}
			else
			{
				_charStatusUI->setIsActive(false);
				_infoUI->setIsActive(false);
			}
		}
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			if (CAMERA->getIsFollowingCameraToTarget()) { break; }
			if (CAMERA->getCameraPoint() == _battleUi[UI_MAPSIGN]->getPointAddress())
			{
				CAMERA->setMoveStartPoint(_battleUi[UI_MAPSIGN]->getPoint());
			}

			_battleUi[UI_MAPSIGN]->setCoordinateX(correctionXIndex(_battleUi[UI_MAPSIGN]->getCoordinateX() - 1));
			updateBattleUI();
			CAMERA->moveToTarget(_battleUi[UI_MAPSIGN]->getPointAddress(), UI_CAMERA_MOVEING_SPEED);
			GameCharacter* thisCoorCharacter = _map->getCharacter(_battleUi[UI_MAPSIGN]->getCoorPoint());
			if (thisCoorCharacter != nullptr)
			{
				_infoUI->setIsActive(true);
				_infoUI->infoCharater(thisCoorCharacter);
			}
			else
			{
				_charStatusUI->setIsActive(false);
				_infoUI->setIsActive(false);
			}
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			if (CAMERA->getIsFollowingCameraToTarget()) { break; }
			if (CAMERA->getCameraPoint() == _battleUi[UI_MAPSIGN]->getPointAddress())
			{
				CAMERA->setMoveStartPoint(_battleUi[UI_MAPSIGN]->getPoint());
			}

			_battleUi[UI_MAPSIGN]->setCoordinateY(correctionYIndex(_battleUi[UI_MAPSIGN]->getCoordinateY() + 1));
			updateBattleUI();
			CAMERA->moveToTarget(_battleUi[UI_MAPSIGN]->getPointAddress(), UI_CAMERA_MOVEING_SPEED);
			GameCharacter* thisCoorCharacter = _map->getCharacter(_battleUi[UI_MAPSIGN]->getCoorPoint());
			if (thisCoorCharacter != nullptr)
			{
				_infoUI->setIsActive(true);
				_infoUI->infoCharater(thisCoorCharacter);
			}
			else
			{
				_charStatusUI->setIsActive(false);
				_infoUI->setIsActive(false);
			}

		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			if (CAMERA->getIsFollowingCameraToTarget()) { break; }
			if (CAMERA->getCameraPoint() == _battleUi[UI_MAPSIGN]->getPointAddress())
			{
				CAMERA->setMoveStartPoint(_battleUi[UI_MAPSIGN]->getPoint());
			}

			_battleUi[UI_MAPSIGN]->setCoordinateX(correctionXIndex(_battleUi[UI_MAPSIGN]->getCoordinateX() + 1));
			updateBattleUI();
			CAMERA->moveToTarget(_battleUi[UI_MAPSIGN]->getPointAddress(), UI_CAMERA_MOVEING_SPEED);
			GameCharacter* thisCoorCharacter = _map->getCharacter(_battleUi[UI_MAPSIGN]->getCoorPoint());
			if (thisCoorCharacter != nullptr)
			{
				_infoUI->setIsActive(true);
				_infoUI->infoCharater(thisCoorCharacter);
			}
			else
			{
				_charStatusUI->setIsActive(false);
				_infoUI->setIsActive(false);
			}
		}
		break;
	case EControl_State::Character_BehaviorWindow:
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_charBehaviorWindow->selectUp();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_charBehaviorWindow->selectDown();
		}

		break;
	case EControl_State::Turn_Window:
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_turnWindow->selectUp();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_turnWindow->selectDown();
		}
		break;
	case EControl_State::Character_CreateWindow:
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_charCreateWindow->selectUp();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_charCreateWindow->selectDown();
		}
		break;
	}
	
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		switch (_controlState)
		{
		case EControl_State::Map_Cursor:
			switch (_okBtnState)
			{
			case EOkBtnState::Nomal:
				_isCharacterSelect = true;
				

				if (_map->selectCharacter(_battleUi[UI_MAPSIGN]->getCoorPoint()) != nullptr)
				{
					GameCharacter* tempCharacter = _map->getTile(_battleUi[UI_MAPSIGN]->getCoorPoint())->getTileGameCharacter();
					_charStatusUI->setGameCharacterInfo(tempCharacter);

					_charStatusUI->setIsActive(true);
					_infoUI->setIsActive(false);

					if (tempCharacter->getUnitType() == E_UnitType::Controllable)
					{
						if (tempCharacter->getCommandState(E_CommandFlag::moveFlag))
						{
							_charBehaviorWindow->setWindowValueState(0, EWindow_ValueState::WINDOW_NOT_SELECTABLE);
						}
						else
						{
							_charBehaviorWindow->setWindowValueState(0, EWindow_ValueState::WINDOW_DEFAULT);
						}

						if (tempCharacter->getCommandState(E_CommandFlag::behaviorFalg))
						{
							_charBehaviorWindow->setWindowValueState(1, EWindow_ValueState::WINDOW_NOT_SELECTABLE);
						}
						else
						{
							_charBehaviorWindow->setWindowValueState(1, EWindow_ValueState::WINDOW_DEFAULT);
						}

						_selectedCharRange = tempCharacter->getCharicterAllStats()->_move;
						_tileRangeStartPoint = _battleUi[UI_MAPSIGN]->getCoorPoint();
						
						_charBehaviorWindow->setIsActive(true);
						_controlState = EControl_State::Character_BehaviorWindow;
					}
					break;
				}
				if (IsSamePoint(_battleUi[UI_MAPSIGN]->getCoorPoint(), _startPt))
				{
					createCharacterWindowSetup();
					_charCreateWindow->setIsActive(true);
					_controlState = EControl_State::Character_CreateWindow;
				}
				break;

			case EOkBtnState::Move:
				//선택된 캐릭터 이동
				_tileRangeTargetPoint = _battleUi[UI_MAPSIGN]->getCoorPoint();

				if (_map->getTile(_tileRangeTargetPoint)->getSelectAbleTile())
				{
					_map->setAstarEndPoint(_tileRangeTargetPoint);
					_map->OnTriggerPathfinding();
					_map->resetTileRange();
					_map->getCurrentCharacter()->setCommandState(E_CommandFlag::moveFlag, true);
					_controlState = EControl_State::Map_Cursor;
					_okBtnState = EOkBtnState::Nomal;
					_isCharacterSelect = false;
					updateBattleUI();
				}
				else
				{
					//todo sound 
				}
				break;
			case EOkBtnState::Attack:
				//공격리스트 저장
				_tileRangeTargetPoint = _battleUi[UI_MAPSIGN]->getCoorPoint();
				if (_map->getTile(_tileRangeTargetPoint)->getSelectAbleTile() && 
					!(_tileRangeStartPoint.x == _tileRangeTargetPoint.x &&
					_tileRangeStartPoint.y == _tileRangeTargetPoint.y) )
				{
					_map->setBehaviorList(_map->getTile(_tileRangeStartPoint), _map->getTile(_tileRangeTargetPoint), E_BehaviorType::Attack);
					_map->resetTileRange();
					_map->getCurrentCharacter()->setCommandState(E_CommandFlag::behaviorFalg, true);
					_controlState = EControl_State::Map_Cursor;
					_okBtnState = EOkBtnState::Nomal;
					_isCharacterSelect = false;
					updateBattleUI();
				}
				else
				{
					//todo sound 
				}
				break;
			default:
				break;
			}
			
			break;
		case EControl_State::Character_BehaviorWindow:
			_charStatusUI->setIsActive(false);
			_charBehaviorWindow->excute();
			break;
		case EControl_State::Turn_Window:
			_turnWindow->excute();
			break;
		case EControl_State::Character_CreateWindow:
			_charCreateWindow->excute();
			break;
		}
	
		updateBattleUI();
	}
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (!_charBehaviorWindow->getIsActive())
		{
			if (_map->getBehaviorList()->empty())
			{
				_turnWindow->setWindowValueState(1, EWindow_ValueState::WINDOW_NOT_SELECTABLE);
			}
			else
			{
				_turnWindow->setWindowValueState(1, EWindow_ValueState::WINDOW_DEFAULT);
			}
			_turnWindow->setIsActive(true);
			_controlState = EControl_State::Turn_Window;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		_charStatusUI->setIsActive(false);
		switch (_controlState)
		{
		case EControl_State::Map_Cursor:
			switch (_okBtnState)
			{
			case EOkBtnState::Nomal:
				if (_map->selectCharacter(_battleUi[UI_MAPSIGN]->getCoorPoint()) != nullptr)
				{
					_map->resetCharacterMove();
					CAMERA->moveToTarget(_battleUi[UI_MAPSIGN]->getPointAddress(), UI_CAMERA_MOVEING_SPEED);
				}
				break;
			case EOkBtnState::Move:
				_map->resetTileRange();
				_controlState = EControl_State::Map_Cursor;
				_okBtnState = EOkBtnState::Nomal;
				_isCharacterSelect = false;
				break;
			case EOkBtnState::Attack:
				_map->resetTileRange();
				_controlState = EControl_State::Map_Cursor;
				_okBtnState = EOkBtnState::Nomal;
				_isCharacterSelect = false;
				break;
			default:
				break;
			}

			break;
		case EControl_State::Character_BehaviorWindow:
			_charBehaviorWindow->setIsActive(false);
			_controlState = EControl_State::Map_Cursor;
			break;
		case EControl_State::Turn_Window:
			_turnWindow->setIsActive(false);
			_controlState = EControl_State::Map_Cursor;
			break;
		case EControl_State::Character_CreateWindow:
			_charCreateWindow->setIsActive(false);
			_controlState = EControl_State::Map_Cursor;
			break;
		default:
			break;
		}
	}

}

void TurnSystem::render(void)
{
	_infoUI->render();
	//_battleUi[UI_MAPSIGN]->render();
	_charBehaviorWindow->render();
	_turnWindow->render();
	_charStatusUI->render();
	_turnStateUI->render();
	_charCreateWindow->render();
}

inline void TurnSystem::updateBattleUI()
{
	_battleUi[UI_MAPSIGN]->setPoint(_map->getcoordinateToPoint(_battleUi[UI_MAPSIGN]->getCoorPoint()));
	_battleUi[UI_BLUESIGN]->setPoint(_map->getcoordinateToPoint(_battleUi[UI_MAPSIGN]->getCoorPoint()));
}

bool TurnSystem::confimeAliveCharacter(void)
{
	_vIPlayerChar = _vPlayerChar.begin();
	for (; _vIPlayerChar != _vPlayerChar.end(); ++_vIPlayerChar)
	{
		if (!(*_vIPlayerChar)->getIsDie())
		{
			return true;
		}
	}
	return false;
}


void TurnSystem::setInitBattleUI(POINT point)
{
	_battleUi[UI_MAPSIGN]->setCoorPoint(correctionTileIndex(point));
	_battleUi[UI_BattleStartObj]->setCoorPoint(correctionTileIndex(point));
	updateBattleUI();
	_battleUi[UI_BattleStartObj]->setPoint(_map->getcoordinateToPoint(point));
	_startPt = point;
}

POINT TurnSystem::correctionTileIndex(POINT coordinate)
{
	if (coordinate.x < 0) coordinate.x = 0;
	else if (coordinate.x > _mapSize->x - 1)
	{
		coordinate.x = _mapSize->x-1;
	}
	if (coordinate.y < 0) coordinate.y = 0;
	else if (coordinate.y > _mapSize->y - 1)
	{
		coordinate.y = _mapSize->y-1;
	}
	return coordinate;
}

int TurnSystem::correctionXIndex(int xindex)
{
	if (xindex < 0) xindex = 0;
	else if (xindex > _mapSize->x - 1)
	{
		xindex = _mapSize->x - 1;
	}
	return xindex;
}

int TurnSystem::correctionYIndex(int yindex)
{
	if (yindex < 0) yindex = 0;
	else if (yindex > _mapSize->y - 1)
	{
		yindex = _mapSize->y - 1;
	}
	return yindex;
}


void TurnSystem::characterWindowSetup()
{
	CALLBACKFUNCTION  moveCallback = [this](void)->void
	{
		_charBehaviorWindow->setIsActive(false);
		_controlState = EControl_State::Map_Cursor;
		_okBtnState = EOkBtnState::Move;
		_map->startComputeTileRange(_selectedCharRange, _tileRangeStartPoint,true);

	};
	CALLBACKFUNCTION  attackCallback = [this](void)->void
	{
		_charBehaviorWindow->setIsActive(false);
		_controlState = EControl_State::Map_Cursor;
		_okBtnState = EOkBtnState::Attack;
		_map->startComputeTileRange(_map->getCurrentCharacter()->getAttackRange(), _tileRangeStartPoint,false);
	};

	_charBehaviorWindow = new CWindowUI;
	_charBehaviorWindow->init(300, 4, 80, EWindow_Align::WINDOW_LEFTTOP);
	_charBehaviorWindow->setWindowValue("이동", 15, 15, moveCallback);
	_charBehaviorWindow->setWindowValue("공격", 15, 15, attackCallback);
}


void TurnSystem::turnWindowSetup()
{
	CALLBACKFUNCTION nextTrunCallBack = [this](void)->void
	{
		_turnWindow->setIsActive(false);
		_controlState = EControl_State::Map_Cursor;
		_okBtnState = EOkBtnState::Nomal;
		_turnStateUI->StartTurnStateAnimation(false);
		
	};
	CALLBACKFUNCTION acttackExcuteCallBack = [this](void)->void
	{
		_map->StartBehavior();
		_turnWindow->setIsActive(false);
		_controlState = EControl_State::Map_Cursor;
		_okBtnState = EOkBtnState::Nomal;
		
	};
	CALLBACKFUNCTION exit = [this](void)->void
	{
		//todo
	};

	_turnWindow = new CWindowUI;
	_turnWindow->init(300, 4, 80, EWindow_Align::WINDOW_LEFTTOP);
	_turnWindow->setWindowValue("턴 종료", 15, 15, nextTrunCallBack);
	_turnWindow->setWindowValue("공격 개시", 15, 15, acttackExcuteCallBack);
	_turnWindow->setWindowValue("포기", 15, 15, exit);
}


void TurnSystem::createCharacterWindowSetup()
{
	if (_playerCharSize != _vPlayerChar.size())
	{
		if (_vPlayerChar.size() == 0)
		{
			_charCreateWindow->resetValue();
			_charCreateWindow->setWindowValue("0명", 20, 20, nullptr);
			_playerCharSize = _vPlayerChar.size();
		}
		else
		{
			_charCreateWindow->resetValue();
			CALLBACKFUNCTION createCharacter = [this](void)->void
			{
				_map->setPlayerCharacter(_vPlayerChar[_charCreateWindow->getIndex()], _startPt.x, _startPt.y);
				_vPlayerChar.erase(_vPlayerChar.begin() + _charCreateWindow->getIndex());
				_charCreateWindow->setIsActive(false);

				_controlState = EControl_State::Map_Cursor;
				_okBtnState = EOkBtnState::Nomal;
			};
			int count = 0;
			_vIPlayerChar = _vPlayerChar.begin();
			for (; _vIPlayerChar != _vPlayerChar.end(); ++_vIPlayerChar)
			{
				_charCreateWindow->setWindowValue((*_vIPlayerChar)->getName(), 20, 20, createCharacter);
				if (_vPlayerChar[count]->getIsDie())
				{
					_charCreateWindow->setWindowValueState(count, EWindow_ValueState::WINDOW_NOT_SELECTABLE);
				}
				count++;
			}
			_playerCharSize = _vPlayerChar.size();
		}
		
	}
}

