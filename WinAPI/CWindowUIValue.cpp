#include "Stdafx.h"
#include "CWindowUIValue.h"


CWindowUIValue::CWindowUIValue() : _func(nullptr)
{
}

CWindowUIValue::~CWindowUIValue()
{
}


HRESULT CWindowUIValue::init(void)
{
	return S_OK;
}

HRESULT CWindowUIValue::init(string valueName, int x, int y, int width, int height, int fontSize, EWindow_Align textAlign, CALLBACKFUNCTION function)
{
	_rc = RectMake(x, y, width, height);
	_windowState = WINDOW_DEFAULT;
	_valueStr = valueName;
	_align = textAlign;
	_func = function;
	_fontSize = fontSize;
	_height = height;

	_img = new my::Image;
	_img->init("Resource/Images/Disgaea/UI/WBG01.bmp", width, height, false);
	_color = RGB(0, 0, 0);

	return S_OK;
}

void CWindowUIValue::release(void)
{
	_img->release();
	SAFE_DELETE(_img);
}

void CWindowUIValue::update(void)
{
	
}

void CWindowUIValue::render(void)
{
	_img->render(getMemDC(), _rc.left, _rc.top);
	FONTMANAGER->drawText(getMemDC(), _rc,"³ª´®°íµñ Bold", _fontSize, 30, _valueStr.c_str(), _color, static_cast<bool>(_align));

}

void CWindowUIValue::excute(void)
{
	if (_func != nullptr)
	{
		if (_windowState != WINDOW_NOT_SELECTABLE)
		{
			_func();
		}
	}
}

void CWindowUIValue::setWindowState(EWindow_ValueState state)
{
	_windowState = state;
	switch (_windowState)
	{
	case WINDOW_DEFAULT:
		_color = RGB(0, 0, 0);
		break;
	case WINDOW_NOT_SELECTABLE:
		_color = RGB(80, 80, 80);
		break;
	}
}
