#include "Stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init(void)
{
	return S_OK;
}

void EffectManager::release(void)
{
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->release();
		SAFE_DELETE(*_viEffect);
	}
	_vEffect.clear();

}

void EffectManager::update(void)
{
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); )
	{
		(*_viEffect)->update();

		//CheckIsActive
		if (!(*_viEffect)->getIsActive())
		{
			(*_viEffect)->release();
			SAFE_DELETE(*_viEffect);
			_viEffect = _vEffect.erase(_viEffect);
		}
		else _viEffect++;
	}
}

void EffectManager::render(void)
{
	//save zorder
	/*_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->render();
	}*/
}

void EffectManager::createEffect(const char* fileName, RECT rc)
{
	CEffect* effect = new CEffect;
	effect->init(fileName, rc);
	_vEffect.push_back(effect);
}

void EffectManager::createEffect(const char* fileName, POINT point)
{
	CEffect* effect = new CEffect;
	effect->init(fileName, point);
	_vEffect.push_back(effect);
}

void EffectManager::createEffect(const char* fileName, POINT point, int FPS)
{
	CEffect* effect = new CEffect;
	effect->init(fileName, point, FPS);
	_vEffect.push_back(effect);
}

void EffectManager::createEffect(const char * fileName, POINT point, int FPS, BYTE alpha)
{
	CEffect* effect = new CEffect;
	effect->init(fileName, point, FPS, alpha);
	_vEffect.push_back(effect);
}

void EffectManager::createEffect(const char * fileName, POINT point, int FPS, bool isAlphaIncrease, BYTE startAlpha, BYTE endAlpha, float alphaOffset)
{
	CEffect* effect = new CEffect;
	effect->init(fileName, point, FPS, isAlphaIncrease, startAlpha,endAlpha,alphaOffset);
	_vEffect.push_back(effect);
}

void EffectManager::createParticleEffect(const char * fileName, POINT point, int FPS, bool isAlphaIncrease, BYTE startAlpha, BYTE endAlpha, float alphaOffset, int particleCount, int cRange)
{
	for (int i =0; i < particleCount; i++)
	{
		CEffect* effect = new CEffect;
		effect->init(fileName, CircleRandomPoint(point, cRange), RND->getFromIntTo(FPS-5, FPS +5), isAlphaIncrease, startAlpha, endAlpha, RND->getFromIntTo(alphaOffset-5, alphaOffset+5));
		_vEffect.push_back(effect);
	}
	
}

POINT EffectManager::CircleRandomPoint(POINT pt, int range)
{
	POINT temp;
	float r = range * RND->getFloat(1);
	float theta = RND->getFloat(1) * 2 * PI;

	temp.x = pt.x + r * cos(theta);
	temp.y = pt.y + r * sin(theta);
	return temp;
}
