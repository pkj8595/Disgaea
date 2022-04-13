#include "Stdafx.h"
#include "CButtonState.h"

CButtonState::CButtonState():_callbackFunction(nullptr)
{
}

CButtonState::~CButtonState()
{
}


HRESULT CButtonState::init(const char* imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CBUTTONSTATE_ALIGN align)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_x = x;
	_y = y;
	_btnDownFramePoint = btnDownFramePoint;
	_btnUpFramePoint = btnUpFramePoint;
	_isbtnDown = false;
	if (align == CBUTTONSTATE_ALIGN::BUTTON_LEFTTOP)
	{
		_rc = RectMake(x, y, _image->getFrameWidth(), _image->getFrameHeight());
	}
	else if(align == CBUTTONSTATE_ALIGN::BUTTON_CENTER)
	{
		_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());
	}
	_direction= BUTTON_DIRECTION_NULL;
	return S_OK;
}

HRESULT CButtonState::init(const char* imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACKFUNCTION cbFunction, CBUTTONSTATE_ALIGN align)
{
	_callbackFunction = static_cast<CALLBACKFUNCTION>(cbFunction);
	this->init(imageName,x,y, btnDownFramePoint, btnUpFramePoint, align);

	return S_OK;
}

void CButtonState::release(void)
{
}

void CButtonState::update(void)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		_direction = BUTTON_DIRECTION_UP;
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) 
		{
			_direction = BUTTON_DIRECTION_DOWN; 
			_isbtnDown = true;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON) && _isbtnDown)
		{
			excute();
			_isbtnDown = false;
		}
	}
	else
	{
		_isbtnDown = false;
		_direction = BUTTON_DIRECTION_NULL;
	}

}

void CButtonState::render(void)
{
	switch (_direction)
	{
	case BUTTON_DIRECTION_NULL: case BUTTON_DIRECTION_UP:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _btnDownFramePoint.x, _btnDownFramePoint.y);
		break;
	case BUTTON_DIRECTION_DOWN:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _btnUpFramePoint.x, _btnUpFramePoint.y);
		break;
	}
}

void CButtonState::excute(void)
{
	if (_callbackFunction != nullptr) _callbackFunction();
}

