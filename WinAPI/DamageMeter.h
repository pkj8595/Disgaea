#pragma once
#include "GameNode.h"
#include "DamageEffectNum.h"


class DamageMeter : public GameNode
{
private:
	vector< DamageEffectNum* > _vDamage;
	vector< DamageEffectNum* >::iterator _viterDamage;
	string _imageKeyname;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void setImageKeyName(string keyName);
	void createDamageEffect(POINT point, int num);

	DamageMeter();
	~DamageMeter();
};

