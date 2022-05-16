#include "Stdafx.h"
#include "CSkill.h"

CSkill::CSkill()
{
}

CSkill::~CSkill()
{
}


HRESULT CSkill::init(string skillName,POINT coorPoint, float damageCalculation, int skillRange, int sp)
{
	_name = skillName;
	_coorPoint = coorPoint;
	_damageCalculation = damageCalculation;
	_skillRange = skillRange;
	_sp = sp;

	return S_OK;
}

