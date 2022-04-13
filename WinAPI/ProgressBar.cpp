#include "Stdafx.h"
#include "ProgressBar.h"

HRESULT ProgressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, width, height);
	_progressBarUp = IMAGEMANAGER->addImage("BarUp", "Resource/Images/Object/black.bmp", 0, 0, width, height, true, RGB(255, 0, 255));
	_progressBarDown = IMAGEMANAGER->addImage("BarDown", "Resource/Images/Object/gray.bmp", 0, 0, width, height, true, RGB(255, 0, 255));

	_width = _progressBarUp->getWidth();
	_newInit = false;

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
	return S_OK;
}

void ProgressBar::release(void)
{
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
	if (_alignLeft)
	{
		_progressBarDown->render(getMemDC(),
			_rc.left,
			_y + _progressBarDown->getHeight() / 2,
			0, 0,
			_progressBarDown->getWidth(),
			_progressBarDown->getHeight());

		_progressBarUp->render(getMemDC(),
			_rc.left,
			_y + _progressBarDown->getHeight() / 2,
			0, 0,
			_width, _progressBarDown->getHeight());
	}
	else
	{
		_progressBarDown->render(getMemDC(),
			_rc.left + _progressBarDown->getWidth() / 2,
			_y + _progressBarDown->getHeight() / 2,
			0, 0,
			_progressBarDown->getWidth(),
			_progressBarDown->getHeight());

		_progressBarUp->render(getMemDC(),
			_rc.left + _progressBarDown->getWidth() / 2,
			_y + _progressBarDown->getHeight() / 2,
			0, 0,
			_width, _progressBarDown->getHeight());
	}
}

void ProgressBar::setGauge(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressBarDown->getWidth();
}
