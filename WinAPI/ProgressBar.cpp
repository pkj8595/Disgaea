#include "Stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(int x, int y, int width, int height, bool isGreen)
{
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, width, height);
	if (isGreen)
	{
		_progressBarUp = IMAGEMANAGER->addImage("BarUp", "Resource/Images/Disgaea/UI/battleUI/BattleHPBar.bmp", 0, 0, width, height, true, RGB(255, 0, 255));
	}
	else
	{
		_progressBarUp = IMAGEMANAGER->addImage("EBarUp", "Resource/Images/Disgaea/UI/battleUI/EnemyBattleHPBar.bmp", 0, 0, width, height, true, RGB(255, 0, 255));
	}
	_progressBarDown = IMAGEMANAGER->addImage("BarDown", "Resource/Images/Disgaea/black.bmp", 0, 0, width, height, true, RGB(255, 0, 255));

	_width = _progressBarUp->getWidth();
	_newInit = false;
	_useZdata = false;
	_alignLeft = false;

	return S_OK;
}

HRESULT ProgressBar::init(const char* barUpimg, const char* barDownimg, int x, int y, int width, int height, bool isTrans, bool alignLeft)
{
	_x = x;
	_y = y;
	_alignLeft = alignLeft;
	if (_alignLeft)
	{
		_rc = RectMake(_x, _y, width, height);
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, width, height);
	}
	_progressBarUp = new my::Image;
	_progressBarDown = new my::Image;

	_progressBarUp->init(barUpimg, 0, 0, width, height, 1, 1, isTrans, RGB(255, 0, 255));
	_progressBarDown->init(barDownimg, 0, 0, width, height, 1, 1, isTrans, RGB(255, 0, 255));

	_width = _progressBarUp->getWidth();
	_newInit = true;
	_useZdata = false;

	return S_OK;
}

void ProgressBar::release(void)
{
	if (_useZdata)
	{
		CAMERA->removeZData(_zUpData);
		CAMERA->removeZData(_zDownData);
	}
	if (_newInit)
	{
		_progressBarUp->release();
		SAFE_DELETE(_progressBarUp);
		_progressBarDown->release();
		SAFE_DELETE(_progressBarDown)
	}
}

void ProgressBar::update(void)
{

	if (_alignLeft)
	{
		_rc = RectMake(_x, _y, _progressBarDown->getWidth(), _progressBarDown->getHeight());
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(), _progressBarDown->getHeight());
	}
	
}

void ProgressBar::render(void)
{
	if (_useZdata) return;
	if (_alignLeft)
	{
		_progressBarDown->render(getMemDC(),
			_rc.left,
			_rc.top,
			0, 0,
			_progressBarDown->getWidth(),
			_progressBarDown->getHeight());

		_progressBarUp->render(getMemDC(),
			_rc.left,
			_rc.top,
			0, 0,
			_width, _progressBarDown->getHeight());
	}
	else
	{
		_progressBarDown->render(getMemDC(),
			_rc.left - CAMERA->getLeft(),
			_rc.top - CAMERA->getTop(),
			0, 0,
			_progressBarDown->getWidth(),
			_progressBarDown->getHeight());

		_progressBarUp->render(getMemDC(),
			_rc.left  - CAMERA->getLeft(),
			_rc.top -CAMERA->getTop(),
			0, 0,
			_width, _progressBarDown->getHeight());
	}
}

void ProgressBar::setGauge(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressBarDown->getWidth();
}

void ProgressBar::setZData(void)
{
	_useZdata = true;
	_zUpData = new ZOrderData;
	_zUpData->setRenderData(&_rc, &_progressBarUp, &_width);

	_zDownData = new ZOrderData;
	_zDownData->setRenderData(&_rc, &_progressBarDown, &_width);

}

void ProgressBar::registerZData(void)
{
	CAMERA->registerZData(ZIndexType_ProgressUpbar, _zUpData);
	CAMERA->registerZData(ZIndexType_ProgressDownbar, _zDownData);
}

void ProgressBar::removeZData(void)
{
	CAMERA->removeZData(_zUpData);
	CAMERA->removeZData(_zDownData);
}
