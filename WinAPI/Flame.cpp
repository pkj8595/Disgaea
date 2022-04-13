#include "Stdafx.h"
#include "Flame.h"

Flame::Flame(){
}

Flame::~Flame(){
}

HRESULT Flame::init(const char* fileName, float* x, float* y)
{
	//어디서 어떻게 그릴지 추상화하는게 맞음.
	_image = IMAGEMANAGER->addFrameImage("불꽃","Resource/Images/Rocket/Flame.BMP",437,297,9,1,true,RGB(255,0,255));
	_x = x;
	_y = y;
	_rc = RectMakeCenter((int)_x, (int)_y, _image->getFrameWidth(), _image->getMaxFrameY());
	_flameTick = 7.0f;

	return S_OK;
}

void Flame::release(void)
{
}

void Flame::update(void)
{

	if (FLAME_COUNT + _flameTick <= GetTickCount())
	{
		_flameTick = GetTickCount();
		_image->setFrameX(_image->getFrameX() + 1);

		if (_image->getFrameX() >= _image->getMaxFrameX())
		{
			_image->setFrameX(0);
		}
		_rc = RectMakeCenter(*_x-2, *_y + 180,
			_image->getFrameWidth(),
			_image->getFrameHeight());
	}

}

void Flame::render(void)
{
	_image->frameRender(getMemDC(), _rc.left,_rc.top, _image->getFrameX(), _image->getFrameY());
}

