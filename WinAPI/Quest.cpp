#include "Stdafx.h"
#include "Quest.h"

void Quest::init(string name, int gold, int exp, string description, string item, int monster, string questCheck, string monsterName, string questStage)
{
	_exp			= exp;
	_gold			=gold;
	_monster		=monster;
	_name			=name;
	_item			=item;
	_description	=description;
	_questCheck		=questCheck;
	_monsterName	=monsterName;
	_questStage		=questStage;
}
