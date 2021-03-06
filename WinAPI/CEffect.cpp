#include "Stdafx.h"
#include "CEffect.h"


CEffect::CEffect(void) :_rc(RectMake(0, 0, 0, 0)),
_currentFrame(0),
_x(0.0f),
_y(0.0f),
_alphaOffset(0.0f),
_offsetTimeCount(0.0f),
_worldTimeCount(0.0f),
_maxFrameX(0),
_maxFrameY(0),
_alpha(0),
_endAlpha(0),
_useAlphaFrame(false),
_isAlphaChange(false),
_isAlphaIncrease(false)
{
}

CEffect::~CEffect(void) {
}

HRESULT CEffect::init(void)
{
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_isActive = true;

	_maxFrameX = _image->getMaxFrameX();
	_maxFrameY = _image->getMaxFrameY();
	CALLBACKFUNCTION renderCallback = [this](void)->void
	{
		draw();
	};

	_zData = new ZOrderData;
	_zData->setRenderCallback(&_rc, renderCallback);
	CAMERA->registerZData(ZIndexType_Effect, _zData);
	return S_OK;
}

HRESULT CEffect::init(const char* imageName, RECT rc)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_offsetTimeCount = RND->getFromFloatTo(0.04f, 0.08f);
	_image = IMAGEMANAGER->findImage(imageName);
	_x = rc.left + (rc.right - rc.left) / 2;
	_y = rc.top;
	
	_alpha = 255;
	_useAlphaFrame = false;

	init();
	return S_OK;
}

HRESULT CEffect::init(const char* imageName, POINT pt)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_offsetTimeCount = RND->getFromFloatTo(0.04f, 0.08f);
	_image = IMAGEMANAGER->findImage(imageName);
	_x = pt.x;
	_y = pt.y;
	
	_alpha = 255;
	_useAlphaFrame = false;
	init();
	return S_OK;
}


HRESULT CEffect::init(const char* imageName, POINT pt, int FPS)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_offsetTimeCount = 1.0f / static_cast<float>(FPS);
	_image = IMAGEMANAGER->findImage(imageName);
	_x = pt.x;
	_y = pt.y;
	
	_alpha = 255;
	_useAlphaFrame = false;
	init();
	return S_OK;
}

HRESULT CEffect::init(const char * imageName, POINT pt, int FPS, BYTE alpha)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_offsetTimeCount = 1.0f / static_cast<float>(FPS);
	_image = IMAGEMANAGER->findImage(imageName);
	_x = pt.x;
	_y = pt.y;

	_alpha = alpha;
	_useAlphaFrame = true;
	init();
	return S_OK;
}

HRESULT CEffect::init(const char* imageName, POINT pt, int FPS, bool isAlphaIncrease, BYTE startAlpha, BYTE endAlpha, float alphaOffset)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_offsetTimeCount = 1.0f / static_cast<float>(FPS);
	_image = IMAGEMANAGER->findImage(imageName);
	_x = pt.x;
	_y = pt.y;

	_useAlphaFrame = true;
	_isAlphaChange = true;
	_isAlphaIncrease = isAlphaIncrease;
	_alpha = startAlpha;
	_endAlpha = endAlpha;
	_alphaOffset = alphaOffset;

	init();
	return S_OK;
}

void CEffect::release(void)
{
	CAMERA->removeZData(_zData);
	SAFE_DELETE(_zData);
}

void CEffect::update(void)
{
	animation();
	if (_isAlphaChange) alphaChange();
}

void CEffect::render(void)
{
	//draw();
}

void CEffect::draw(void)
{
	if (_useAlphaFrame)
	{
		_image->alphaFrameRender(getMemDC(), _rc.left-CAMERA->getLeft(), _rc.top- CAMERA->getTop(), (int)_currentFrame %_maxFrameX, (int)_currentFrame / _maxFrameX,_alpha);
	}
	else
	{
		_image->frameRender(getMemDC(), _rc.left - CAMERA->getLeft(), _rc.top - CAMERA->getTop(), (int)_currentFrame %_maxFrameX ,  (int)_currentFrame/ _maxFrameX );
	}
}

void CEffect::animation(void)
{
	if (_offsetTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrame++;
		if (((_maxFrameX + 1) * (_maxFrameY + 1)) -1 < _currentFrame)
		{
			_isActive = false;
		}
	}
}

void CEffect::alphaChange(void)
{
	if (_isAlphaIncrease)
	{
		if(_endAlpha > _alpha)
			_alpha += (BYTE)_alphaOffset;
		else _alpha = _endAlpha;
	}
	else 
	{
		if (_endAlpha < _alpha)
			_alpha -= (BYTE)_alphaOffset;
		else _alpha = _endAlpha;
	}

}

