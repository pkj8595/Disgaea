#pragma once
#include "Stdafx.h"


class CharicterStats
{
public:
	int _level;
	int _move;
	int _jump;
	int _maxHp;
	int _hp;
	int _maxSp;
	int _sp;
	int _atk;
	int _def;
	int _int;
	int _speed;
	int _hit;
	int _res;
	int _exp;
	int _maxExp;

	void setStat(int level, int move, int jump, int maxHp, int hp, int maxSp, int sp, int atk, int def, int mint, int speed, int hit, int res, int exp, int maxExp)
	{
		_level=	level;
		_move=	move;
		_jump=	jump;
		_maxHp=	maxHp;
		_hp=	hp;
		_maxSp=	maxSp;
		_sp=	sp;
		_atk=	atk;
		_def=	def;
		_int=	mint;
		_speed=	speed;
		_hit=	hit;
		_res=	res;
		_exp=	exp;
		_maxExp = maxExp;
	}

	CharicterStats operator+(CharicterStats other)
	{
		CharicterStats temp;
		temp._level = _level + other._level;
		temp._move = _move + other._move;
		temp._jump = _jump + other._jump;
		temp._maxHp = _maxHp + other._maxHp;
		temp._hp = _hp + other._hp;
		temp._maxSp = _maxSp + other._maxSp;
		temp._sp = _sp + other._sp;
		temp._atk = _atk + other._atk;
		temp._def = _def + other._def;
		temp._int = _int + other._int;
		temp._speed = _speed + other._speed;
		temp._hit = _hit + other._hit;
		temp._res = _res + other._res;
		temp._exp = _exp + other._exp;
		temp._maxExp =_maxExp+ other._maxExp;
		return temp;
	}

	void operator=(CharicterStats other)
	{
		_level	=other._level;
		_move = other._move;
		_jump = other._jump;
		_maxHp = other._maxHp;
		_hp = other._hp;
		_maxSp = other._maxSp;
		_sp = other._sp;
		_atk = other._atk;
		_def = other._def;
		_int = other._int;
		_speed = other._speed;
		_hit = other._hit;
		_res = other._res;
		_exp = other._exp;
		_maxExp = other._maxExp;
	}


	CharicterStats():_level(0),
					_move(0),
					_jump(0),
					_maxHp(0),
					_hp(0),
					_maxSp(0),
					_sp(0),
					_atk(0),
					_def(0),
					_int(0),
					_speed(0),
					_hit(0),
					_res(0),
					_exp(0),
					_maxExp(0)
	{
	}
	~CharicterStats() {}
};

enum class EITEM_GRADE
{
	NOMAL = 0,
	RARE,
	LEGEND
};

enum class EITEM_TYPE
{
	WEAPON,
	AMMOR,
	BELT,
	POTION,
	GLASSES,
	ORB,
	SIMBOL,
	MUSCLE,
	SHOES,
	EMPTY
};


class Item
{
public:
	CharicterStats	_stats;
	EITEM_GRADE		_grade;
	EITEM_TYPE		_type;
	string			_name;
	int				_itemLevel;
	int				_rQrity;
	int				_price;
	int				_range;

	void operator=(Item other)
	{
		_grade	=other._grade;
		_type = other._type;
		_name = other._name;
		_price = other._price;
		_rQrity = other._rQrity;
		_itemLevel = other._itemLevel;
		_stats = other._stats;
	}

	Item() :_name(""),
			_price(0),
			_grade(EITEM_GRADE::NOMAL),
			_type(EITEM_TYPE::EMPTY),
			_itemLevel(0),
			_rQrity(0),
			_range(1)
	{
	}
	~Item() {}
};

