#pragma once

enum EJSON_ANIDATA
{
	home_B_Dir = 0,
	home_LB_Dir,
	home_L_Dir,
	home_LT_Dir,
	home_T_Dir,
	home_RT_Dir,
	home_R_Dir,
	home_RB_Dir,

	battle_beAttacked_LB,
	battle_beAttacked_LT,
	battle_beAttacked_RT,
	battle_beAttacked_RB,

	battle_victory_LB,
	battle_victory_LT,
	battle_victory_RT,
	battle_victory_RB,

	move_B_Start,
	move_B_End,
	move_LB_Start,
	move_LB_End,
	move_L_Start,
	move_L_End,
	move_LT_Start,
	move_LT_End,
	move_T_Start,
	move_T_End,
	move_RT_Start,
	move_RT_End,
	move_R_Start,
	move_R_End,
	move_RB_Start,
	move_RB_End,

	battle_idle_LB_Start,
	battle_idle_LB_End,
	battle_idle_LT_Start,
	battle_idle_LT_End,
	battle_idle_RT_Start,
	battle_idle_RT_End,
	battle_idle_RB_Start,
	battle_idle_RB_End,

	battle_collabo_LB_Start,
	battle_collabo_LB_End,
	battle_collabo_LT_Start,
	battle_collabo_LT_End,
	battle_collabo_RT_Start,
	battle_collabo_RT_End,
	battle_collabo_RB_Start,
	battle_collabo_RB_End,

	battle_kick_LB_Start,
	battle_kick_LB_End,
	battle_kick_LT_Start,
	battle_kick_LT_End,
	battle_kick_RT_Start,
	battle_kick_RT_End,
	battle_kick_RB_Start,
	battle_kick_RB_End,

	battle_Att_LB_Start,
	battle_Att_LB_End,
	battle_Att_LT_Start,
	battle_Att_LT_End,
	battle_Att_RT_Start,
	battle_Att_RT_End,
	battle_Att_RB_Start,
	battle_Att_RB_End,

	patheticFace_Start,
	patheticFace_End,

	sleep_Start,
	sleep_End,

	Look_Around_Start,
	Look_Around_End,

	wackUp_Start,
	wackUp_End,

	wink_eye_Start,
	wink_eye_End,

	laugh_Start,
	laugh_End,

	battle_PickUp_LB_Start,
	battle_PickUp_LB_End,
	battle_PickUp_LT_Start,
	battle_PickUp_LT_End,
	battle_PickUp_RT_Start,
	battle_PickUp_RT_End,
	battle_PickUp_RB_Start,
	battle_PickUp_RB_End,

	battle_Punching_LB_Start,
	battle_Punching_LB_End,
	battle_Punching_LT_Start,
	battle_Punching_LT_End,
	battle_Punching_RT_Start,
	battle_Punching_RT_End,
	battle_Punching_RB_Start,
	battle_Punching_RB_End,
	EJSON_ANIDATA_END



};

class AniData
{
private:
	string _name;
	string _keyStr[EJSON_ANIDATA_END];
	int _aniDataInt[EJSON_ANIDATA_END];

	//int* _aniData[EJSON_ANIDATA_END];
	//int _aniDataArrSize[EJSON_ANIDATA_END];
public:
	void init(void);

	string getName() { return _name; }
	void setName(string name) { _name = name; }

	string getKeyStr(EJSON_ANIDATA index) { return _keyStr[index]; }
	int getAniDataInt(EJSON_ANIDATA index) { return _aniDataInt[index]; }
	void setAniDataInt(EJSON_ANIDATA index, int value) { _aniDataInt[index] = value; }

	AniData() {}
	~AniData() {}
};

