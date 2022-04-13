#include "Stdafx.h"
#include "HpImgBar.h"

HRESULT HpImgBar::init(float* x, float* y, int* hp, int offsetX, int offsetY)
{
	/*_baseImage= IMAGEMANAGER->addImage("baseHp","Resource/Images/Rocket/HpBase.bmp", 53, 10, TRUE, RGB(255, 0, 255));
	_valImage = IMAGEMANAGER->addImage("valHp","Resource/Images/Rocket/HPValue.bmp", 53, 10, TRUE, RGB(255, 0, 255));*/
	_baseImage = new my::Image;
	_valImage = new my::Image;
	_baseImage->init("Resource/Images/Rocket/HpBase.bmp", 53, 10, TRUE, RGB(255, 0, 255));
	_valImage->init("Resource/Images/Rocket/HPValue.bmp", 53, 10, TRUE, RGB(255, 0, 255));

	_x = x;
	_y = y;
	_hp = hp;
	_maxHp = *hp;
	_offsetX = offsetX;
	_offsetY = offsetY;
	_rc = RectMakeCenter((int)*_x, (int)*_y, _baseImage->getWidth(), _baseImage->getHeight());

	return S_OK;
}

void HpImgBar::release(void)
{
	SAFE_DELETE(_baseImage);
	SAFE_DELETE(_valImage);
}

void HpImgBar::update(void)
{
	_rc = RectMakeCenter((int)*_x + _offsetX, (int)*_y + _offsetY, _baseImage->getWidth(), _baseImage->getHeight());
}

void HpImgBar::render(HDC hdc)
{
	float computeWidth = static_cast<float>(_valImage->getWidth())*
		(static_cast<float>(*_hp) / _maxHp);

	_baseImage->render(hdc, _rc.left, _rc.top,0,0, _baseImage->getWidth(),_baseImage->getHeight());
	_valImage->render(hdc, _rc.left, _rc.top,0,0, static_cast<int>(computeWidth), _valImage->getHeight());

}
