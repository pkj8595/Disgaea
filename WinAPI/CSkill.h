#pragma once
#include "GameNode.h"

class CSkill
{
private:
	string		_name;
	POINT		_coorPoint;
	float		_damageCalculation;
	int			_skillRange;
	int			_sp;
	bool		_isActive;

public:
	HRESULT init(string skillName,POINT coorPoint, float damageCalculation,int skillRange, int sp);

	int getSkillRange(void) { return _skillRange; }
	bool getIsActive(void) { return _isActive; }
	string getName(void) { return _name; }
	POINT getCoorPoint(void) { return _coorPoint; }
	float getDamageCalculation(void) { return _damageCalculation; }
	int getSp(void) { return _sp; }

	CSkill();
	~CSkill();
};

