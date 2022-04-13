#include "Stdafx.h"
#include "AniData.h"

void AniData::init(void)
{
	int i = 0;
	_keyStr[i] = "home_B_Dir"; i++;
	_keyStr[i] = "home_LB_Dir"; i++;
	_keyStr[i] = "home_L_Dir"; i++;
	_keyStr[i] = "home_LT_Dir"; i++;
	_keyStr[i] = "home_T_Dir"; i++;
	_keyStr[i] = "home_RT_Dir"; i++;
	_keyStr[i] = "home_R_Dir"; i++;
	_keyStr[i] = "home_RB_Dir"; i++;
	_keyStr[i] = "battle_beAttacked_LB"; i++;
	_keyStr[i] = "battle_beAttacked_LT"; i++;
	_keyStr[i] = "battle_beAttacked_RT"; i++;
	_keyStr[i] = "battle_beAttacked_RB"; i++;
	_keyStr[i] = "battle_victory_LB"; i++;
	_keyStr[i] = "battle_victory_LT"; i++;
	_keyStr[i] = "battle_victory_RT"; i++;
	_keyStr[i] = "battle_victory_RB"; i++;
	_keyStr[i] = "move_B_Start"; i++;
	_keyStr[i] = "move_B_End"; i++;
	_keyStr[i] = "move_LB_Start"; i++;
	_keyStr[i] = "move_LB_End"; i++;
	_keyStr[i] = "move_L_Start"; i++;
	_keyStr[i] = "move_L_End"; i++;
	_keyStr[i] = "move_LT_Start"; i++;
	_keyStr[i] = "move_LT_End"; i++;
	_keyStr[i] = "move_T_Start"; i++;
	_keyStr[i] = "move_T_End"; i++;
	_keyStr[i] = "move_RT_Start"; i++;
	_keyStr[i] = "move_RT_End"; i++;
	_keyStr[i] = "move_R_Start"; i++;
	_keyStr[i] = "move_R_End"; i++;
	_keyStr[i] = "move_RB_Start"; i++;
	_keyStr[i] = "move_RB_End"; i++;
	_keyStr[i] = "battle_idle_LB_Start"; i++;
	_keyStr[i] = "battle_idle_LB_End"; i++;
	_keyStr[i] = "battle_idle_LT_Start"; i++;
	_keyStr[i] = "battle_idle_LT_End"; i++;
	_keyStr[i] = "battle_idle_RT_Start"; i++;
	_keyStr[i] = "battle_idle_RT_End"; i++;
	_keyStr[i] = "battle_idle_RB_Start"; i++;
	_keyStr[i] = "battle_idle_RB_End"; i++;
	_keyStr[i] = "battle_collabo_LB_Start"; i++;
	_keyStr[i] = "battle_collabo_LB_End"; i++;
	_keyStr[i] = "battle_collabo_LT_Start"; i++;
	_keyStr[i] = "battle_collabo_LT_End"; i++;
	_keyStr[i] = "battle_collabo_RT_Start"; i++;
	_keyStr[i] = "battle_collabo_RT_End"; i++;
	_keyStr[i] = "battle_collabo_RB_Start"; i++;
	_keyStr[i] = "battle_collabo_RB_End"; i++;
	_keyStr[i] = "battle_kick_LB_Start"; i++;
	_keyStr[i] = "battle_kick_LB_End"; i++;
	_keyStr[i] = "battle_kick_LT_Start"; i++;
	_keyStr[i] = "battle_kick_LT_End"; i++;
	_keyStr[i] = "battle_kick_RT_Start"; i++;
	_keyStr[i] = "battle_kick_RT_End"; i++;
	_keyStr[i] = "battle_kick_RB_Start"; i++;
	_keyStr[i] = "battle_kick_RB_End"; i++;
	_keyStr[i] = "battle_Att_LB_Start"; i++;
	_keyStr[i] = "battle_Att_LB_End"; i++;
	_keyStr[i] = "battle_Att_LT_Start"; i++;
	_keyStr[i] = "battle_Att_LT_End"; i++;
	_keyStr[i] = "battle_Att_RT_Start"; i++;
	_keyStr[i] = "battle_Att_RT_End"; i++;
	_keyStr[i] = "battle_Att_RB_Start"; i++;
	_keyStr[i] = "battle_Att_RB_End"; i++;
	_keyStr[i] = "patheticFace_Start"; i++;
	_keyStr[i] = "patheticFace_End"; i++;
	_keyStr[i] = "sleep_Start"; i++;
	_keyStr[i] = "sleep_End"; i++;
	_keyStr[i] = "Look_Around_Start"; i++;
	_keyStr[i] = "Look_Around_End"; i++;
	_keyStr[i] = "wackUp_Start"; i++;
	_keyStr[i] = "wackUp_End"; i++;
	_keyStr[i] = "wink_eye_Start"; i++;
	_keyStr[i] = "wink_eye_End"; i++;
	_keyStr[i] = "laugh_Start"; i++;
	_keyStr[i] = "laugh_End"; i++;
	_keyStr[i] = "battle_PickUp_LB_Start"; i++;
	_keyStr[i] = "battle_PickUp_LB_End"; i++;
	_keyStr[i] = "battle_PickUp_LT_Start"; i++;
	_keyStr[i] = "battle_PickUp_LT_End"; i++;
	_keyStr[i] = "battle_PickUp_RT_Start"; i++;
	_keyStr[i] = "battle_PickUp_RT_End"; i++;
	_keyStr[i] = "battle_PickUp_RB_Start"; i++;
	_keyStr[i] = "battle_PickUp_RB_End"; i++;
	_keyStr[i] = "battle_Punching_LB_Start"; i++;
	_keyStr[i] = "battle_Punching_LB_End"; i++;
	_keyStr[i] = "battle_Punching_LT_Start"; i++;
	_keyStr[i] = "battle_Punching_LT_End"; i++;
	_keyStr[i] = "battle_Punching_RT_Start"; i++;
	_keyStr[i] = "battle_Punching_RT_End"; i++;
	_keyStr[i] = "battle_Punching_RB_Start"; i++;
	_keyStr[i] = "battle_Punching_RB_End"; i++;
	

	if (i != EJSON_ANIDATA::EJSON_ANIDATA_END)
	{
		assert("AniData::init() enum size != stringArr size");
	}
}
