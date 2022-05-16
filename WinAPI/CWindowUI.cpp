#include "Stdafx.h"
#include "CWindowUI.h"


CWindowUI::CWindowUI() : _currentWindowValue(nullptr)
{
}

CWindowUI::~CWindowUI()
{
}


HRESULT CWindowUI::init(int x, int y, int width, EWindow_Align align, bool useSelectObject)
{
	_x = x;
	_y = y;
	_width = width;
	_rc = RectMake(x, y, width, 0);
	_textAlign = align;
	_isActive = false;
	_useSelectObject = useSelectObject;

	_leftOutLineImg = new my::Image;
	_topOutLineImg = new my::Image;
	_rightOutLineImg = new my::Image;
	_bottomOutLineImg = new my::Image;
	_centerLine._centerImg = new my::Image;

	_leftOutLineImg->init("Resource/Images/Disgaea/UI/window/left.bmp", 3, 0, false);
	_topOutLineImg->init("Resource/Images/Disgaea/UI/window/top.bmp", _width, 3, false);
	_rightOutLineImg->init("Resource/Images/Disgaea/UI/window/right.bmp", 3, 0, false);
	_bottomOutLineImg->init("Resource/Images/Disgaea/UI/window/bottom.bmp", _width, 3, false);
	_centerLine._centerImg->init("Resource/Images/Disgaea/UI/window/center.bmp", width, 3, false);

	_leftTopOutLineImg		= IMAGEMANAGER->findImage("selectWindow_outline_LT");
	_rightTopOutLineImg		= IMAGEMANAGER->findImage("selectWindow_outline_RT");
	_leftBottomOutLineImg	= IMAGEMANAGER->findImage("selectWindow_outline_LB");
	_rightbottomOutLineImg	= IMAGEMANAGER->findImage("selectWindow_outline_RB");

	_selectObject._img = IMAGEMANAGER->findImage("selectHand");
	_selectObject._rc = RectMake(x - _selectObject._img->getWidth(), y, _selectObject._img->getWidth(), _selectObject._img->getHeight());

	return S_OK;
}

void CWindowUI::release(void)
{
	vector< CWindowUIValue*>::iterator iter = _vWindowValue.begin();
	for (; iter != _vWindowValue.end(); ++iter)
	{
		(*iter)->release();
		SAFE_DELETE(*iter);
	}
	_vWindowValue.clear();

	_leftOutLineImg->release();
	_topOutLineImg->release();
	_rightOutLineImg->release();
	_bottomOutLineImg->release();
	_centerLine._centerImg->release();

	SAFE_DELETE(_leftOutLineImg);
	SAFE_DELETE(_topOutLineImg);
	SAFE_DELETE(_rightOutLineImg);
	SAFE_DELETE(_bottomOutLineImg);
	SAFE_DELETE(_centerLine._centerImg);
}

void CWindowUI::update(void)
{
	if (!_isActive) { return; }
	for (CWindowUIValue* window : _vWindowValue)
	{
		window->update();
	}
}

void CWindowUI::render(void)
{
	if (!_isActive) { return; }
	for (CWindowUIValue* window : _vWindowValue)
	{
		window->render();
	}

	//_centerInnerLineImg->render(getMemDC(), _rc.left, _rc.top);
	_leftOutLineImg->render(getMemDC(), _rc.left-3, _rc.top);
	_topOutLineImg->render(getMemDC(), _rc.left, _rc.top-3);
	_rightOutLineImg->render(getMemDC(), _rc.right, _rc.top);
	_bottomOutLineImg->render(getMemDC(), _rc.left, _rc.bottom);

	_leftTopOutLineImg->render(getMemDC(), _rc.left-3, _rc.top-3);
	_rightTopOutLineImg->render(getMemDC(), _rc.right, _rc.top-3);
	_leftBottomOutLineImg->render(getMemDC(), _rc.left-3, _rc.bottom);
	_rightbottomOutLineImg->render(getMemDC(), _rc.right, _rc.bottom);

	if (_useSelectObject)
	{
		_selectObject._img->render(getMemDC(), _selectObject._rc.left, _selectObject._rc.top);
	}
}

void CWindowUI::excute(void)
{
	if (!_isActive || !_useSelectObject) { return; }
	_currentWindowValue->excute();
}

int CWindowUI::getIndex(void)
{
	return  _vWindowIter - _vWindowValue.begin();
}

void CWindowUI::setWindowValue(string valueName, int height, int fontSize, CALLBACKFUNCTION function)
{
	int allHeight =0;

	vector< CWindowUIValue*>::iterator iter = _vWindowValue.begin();
	for (; iter != _vWindowValue.end(); ++iter)
	{
		allHeight += (*iter)->getHeight();

	}

	CWindowUIValue* temp = new CWindowUIValue;
	temp->init(valueName, _x, _y + allHeight, _width, height, fontSize, _textAlign, function);
	_vWindowValue.push_back(temp);
	_vWindowIter = _vWindowValue.begin();
	_currentWindowValue = *_vWindowIter;
	allHeight += height;

	_leftOutLineImg->init("Resource/Images/Disgaea/UI/window/left.bmp", 3, allHeight, false);
	_rightOutLineImg->init("Resource/Images/Disgaea/UI/window/right.bmp", 3, allHeight, false);
	_topOutLineImg->init("Resource/Images/Disgaea/UI/window/top.bmp", _width,3, false);
	_bottomOutLineImg->init("Resource/Images/Disgaea/UI/window/bottom.bmp", _width, 3, false);

	_rc = RectMake(_x, _y, _width, allHeight);

}

void CWindowUI::removeValue(int index)
{
	_vWindowValue.at(index)->release();
	SAFE_DELETE(_vWindowValue.at(index));
	_vWindowValue.erase(_vWindowValue.begin() + index);
	_vWindowIter = _vWindowValue.begin();
}

void CWindowUI::resetValue(void)
{
	vector< CWindowUIValue*>::iterator iter = _vWindowValue.begin();
	for (; iter != _vWindowValue.end(); ++iter)
	{
		(*iter)->release();
		SAFE_DELETE(*iter);
	}
	_vWindowValue.clear();
}

void CWindowUI::selectUp(void)
{
	if (!_isActive) { return; }
	if (_vWindowIter == _vWindowValue.begin())
	{
		_vWindowIter = _vWindowValue.begin();
		_currentWindowValue = *_vWindowIter;
	}
	else
	{
		--_vWindowIter;
		_currentWindowValue = *_vWindowIter;
	}

	if (_useSelectObject)
	{
		_selectObject._rc = RectMake(_x - _selectObject._img->getWidth(), _currentWindowValue->getRect().top , _selectObject._img->getWidth(), _selectObject._img->getHeight());
	}
}

void CWindowUI::selectDown(void)
{
	if (!_isActive) { return; }

	++_vWindowIter;
	if (_vWindowIter != _vWindowValue.end())
	{
		_currentWindowValue = *_vWindowIter;
	}
	else
	{
		_vWindowIter = _vWindowValue.end()-1;
		_currentWindowValue = *_vWindowIter;
	}

	if (_useSelectObject)
	{
		_selectObject._rc = RectMake(_x - _selectObject._img->getWidth(), _currentWindowValue->getRect().top, _selectObject._img->getWidth(), _selectObject._img->getHeight());
	}
}

void CWindowUI::setWindowValueState(int index, EWindow_ValueState state)
{
	if (index > _vWindowValue.size()) index = _vWindowValue.size() - 1;
	_vWindowValue[index]->setWindowState(state);

}

EWindow_ValueState CWindowUI::getWindowValueState(int index)
{
	if (index > _vWindowValue.size()) index = _vWindowValue.size() - 1;
	
	return _vWindowValue[index]->getWindowState();
}
