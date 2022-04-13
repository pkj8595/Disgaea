#include "Stdafx.h"
#include "DamageMeter.h"

DamageMeter::DamageMeter()
{
}

DamageMeter::~DamageMeter()
{
}

HRESULT DamageMeter::init(void)
{
	_imageKeyname = "Number";
	return S_OK;
}

void DamageMeter::release(void)
{
	_viterDamage = _vDamage.begin();
	for (; _viterDamage != _vDamage.end(); ++_viterDamage)
	{
		(*_viterDamage)->release();
		SAFE_DELETE(*_viterDamage);
	}
	_vDamage.clear();
}

void DamageMeter::update(void)
{
	_viterDamage = _vDamage.begin();
	for (; _viterDamage != _vDamage.end(); ++_viterDamage)
	{
		if ((*_viterDamage)->getIsActive())
		{
			(*_viterDamage)->update();
		}
		else
		{
			(*_viterDamage)->release();
			SAFE_DELETE(*_viterDamage);
			_vDamage.erase(_viterDamage);
			break;
		}
	}
}

void DamageMeter::render(void)
{
	_viterDamage = _vDamage.begin();
	for (; _viterDamage != _vDamage.end(); ++_viterDamage)
	{
		(*_viterDamage)->render();
	}
}

void DamageMeter::setImageKeyName(string keyName)
{
	_imageKeyname = keyName;
}

void DamageMeter::createDamageEffect(POINT point, int num)
{
	DamageEffectNum* temp = new DamageEffectNum;
	temp->init(_imageKeyname, point, num);
	_vDamage.push_back(temp);
}

