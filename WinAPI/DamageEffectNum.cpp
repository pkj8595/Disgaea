#include "Stdafx.h"
#include "DamageEffectNum.h"

HRESULT DamageEffectNum::init(string imgkeyName, POINT point, int number)
{
	_image = IMAGEMANAGER->findImage(imgkeyName);
	_point = point;
	_startPointY = _point.y;
	_num = number;
	_rc = RectMakeCenter(_point.x, _point.y, _image->getFrameWidth()*_vFrame.size(), _image->getFrameHeight());

	_isActive = true;
	_isIncrease = true;
	_alpha = 255;
	
	int count = 1;
	while (_num > 0)
	{
		ZOrderData* _zData = new ZOrderData;
		_zData->setRenderData(&_rc, nullptr, &_image, (_num % 10), (_image->getFrameWidth()*count), &_alpha);
		_vFrame.push_back(_zData);
		CAMERA->registerZData(ZIndexType_Damage,_zData);
		count++;
		_num = _num / 10;
	}

	return S_OK;
}

void DamageEffectNum::release(void)
{
	_viFrame = _vFrame.begin();
	for (; _viFrame != _vFrame.end(); ++_viFrame)
	{
		CAMERA->removeZData(*_viFrame);
		SAFE_DELETE(*_viFrame);
	}
	_vFrame.clear();
}

void DamageEffectNum::update(void)
{
	if (_alpha > 5)
	{
		_alpha -=5;
		if (_startPointY - 20 > _point.y) _isIncrease = false;

		if (_isIncrease) _point.y--;
		else _point.y += 2;
	}
	else _isActive = false;
	_rc = RectMakeCenter(_point.x, _point.y, _image->getFrameWidth()*_vFrame.size(), _image->getFrameHeight());

}

void DamageEffectNum::render(void)
{
	
}
