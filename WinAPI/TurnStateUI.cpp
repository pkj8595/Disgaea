#include "Stdafx.h"
#include "TurnStateUI.h"

TurnStateUI::TurnStateUI() :_stateImg(nullptr),
							  _backImg(nullptr)
{
}

TurnStateUI::~TurnStateUI()
{
}

HRESULT TurnStateUI::init(CALLBACKFUNCTION function)
{
	_stateImg = IMAGEMANAGER->findImage("GameState");
	_statePoint = PointMake(CAMERA->getCameraWidth(), CAMERA->getCameraCenterY() - (_stateImg->getFrameHeight()*0.5));
	_stateRc = RectMake(_statePoint.x, _statePoint.y, _stateImg->getFrameWidth(), _stateImg->getFrameHeight());

	_backImg = new my::Image;
	_backImg->init("Resource/Images/Disgaea/black.bmp", CAMERA->getCameraWidth()+20, 60, false);
	_backPoint = PointMake(CAMERA->getCameraCenterX(), CAMERA->getCameraCenterY());
	_backRc = RectMakeCenter(_backPoint.x, _backPoint.y, _backImg->getWidth(), _backImg->getHeight());


	_backAlpha = 0;
	_stayStartTime = 0.0f;  
	_startTime = 0.0f;
	_isPlayerTurn = false;
	_isActive = false;
	_alphaState = E_AlphaState::INCREASE;
	_function = function;
	return S_OK;
}

void TurnStateUI::release(void)
{
	_backImg->release();
	SAFE_DELETE(_backImg);
}

void TurnStateUI::update(void)
{
	if (!_isActive) return;

	switch (_alphaState)
	{
	case TurnStateUI::E_AlphaState::INCREASE:
		_backAlpha += 10;
		_statePoint.x -= 19;
		if (_backAlpha > 200)
		{
			_backAlpha = 200;
		}
		if (_statePoint.x < 30)
		{
			_stayStartTime = TIMEMANAGER->getWorldTime();
			_alphaState = E_AlphaState::STOP;
		}
		break;
	case TurnStateUI::E_AlphaState::STOP:
		if (TIMEMANAGER->getWorldTime() > _stayStartTime + 1.0f)
		{
			_alphaState = E_AlphaState::DIMINISH;
		}
		break;
	case TurnStateUI::E_AlphaState::DIMINISH:
		_statePoint.x -= 19;
		_backAlpha -= 10;
		if (_backAlpha < 13)
		{
			_isActive = false;
			_alphaState = E_AlphaState::INCREASE;
			_startTime = _stayStartTime = 0.0f;
			_backAlpha = 0;
			_statePoint.x = CAMERA->getCameraWidth();
			if (!_isPlayerTurn)
			{
				_function();
			}
		}
		break;
	default:
		break;
	}

	_stateRc = RectMake(_statePoint.x, _statePoint.y, _stateImg->getFrameWidth(), _stateImg->getFrameHeight());
	
}

void TurnStateUI::render(void)
{
	if (!_isActive) return;
	
	_backImg->alphaRender(getMemDC(), _backRc.left, _backRc.top, _backAlpha);
	_stateImg->frameRender(getMemDC(), _stateRc.left, _stateRc.top, 0, _isPlayerTurn? PLAYER_TURN_FRAME: ENEMY_TURN_FRAME);
}

void TurnStateUI::StartTurnStateAnimation(bool isPlayerTurn)
{
	_startTime = TIMEMANAGER->getWorldTime();
	_isPlayerTurn = isPlayerTurn;
	_alphaState = E_AlphaState::INCREASE;
	_isActive = true;
}
