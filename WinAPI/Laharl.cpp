#include "Stdafx.h"
#include "Laharl.h"


Laharl::Laharl()
{
}

Laharl::~Laharl()
{
}

HRESULT Laharl::init(void)
{
	GameCharacter::init();

	return S_OK;
}

HRESULT Laharl::init(string fileName, int x, int y, int coorX, int coorY, E_UnitType type, int imgCorrectionX, int imgCorrectionY)
{
	GameCharacter::init(fileName,x,y,coorX,coorY,type,imgCorrectionX,imgCorrectionY);
	_stats->setStat(2, 7, 0, 20, 20, 10, 10, 5, 3, 0, 10, 60, 0, 0, 10);

	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("battle_idle_LB_Start");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("move_LB_Start");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("battle_Punching_LB_Start");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("laharl_beAttacked_LB");

	_animation[Ani_Left_Top][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("battle_idle_LT_Start");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("move_LT_Start");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("battle_Punching_LT_Start");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("laharl_beAttacked_LT");

	_animation[Ani_Right_Top][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("battle_idle_RT_Start");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("move_RT_Start");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("battle_Punching_RT_Start");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("laharl_beAttacked_RT");

	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("battle_idle_RB_Start");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("move_RB_Start");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("battle_Punching_RB_Start");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("laharl_beAttacked_RB");

	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("laharl_jump_LB");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("laharl_jump_LT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("laharl_jump_RT");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("laharl_jump_RB");

	_currentAnimation = _animation[Ani_Right_Bottom][E_AniBehavior::Ani_idle];

	_iconIndex = 0;
	_battleFaceIndex = 0;

	_title = "������ �Ƶ�";
	return S_OK;
}

void Laharl::release(void)
{
	GameCharacter::release();
}

void Laharl::update(void)
{
	GameCharacter::update();

	/*if ((_dir != _beforeDir || _behavior != _beforeBehavior))
	{
		_currentAnimation->AniStop();
		_beforeDir = _dir;
		_beforeBehavior = _behavior;

		switch (_dir)
		{
		case E_AniDirection::Ani_Left_Bottom:

			switch (_behavior)
			{
			case E_AniBehavior::Ani_idle:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("battle_idle_LB_Start");
				break;
			case E_AniBehavior::move:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("move_LB_Start");
				break;
			case E_AniBehavior::Ani_attack:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("battle_Punching_LB_Start");
				break;
			case E_AniBehavior::Ani_be_Attacked:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("laharl_beAttacked_LB");
				break;
			}
			break;
		case E_AniDirection::Ani_Left_Top:
			switch (_behavior)
			{
			case E_AniBehavior::Ani_idle:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("battle_idle_LT_Start");
				break;
			case E_AniBehavior::move:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("move_LT_Start");
				break;
			case E_AniBehavior::Ani_attack:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("battle_Punching_LT_Start");
				break;
			case E_AniBehavior::Ani_be_Attacked:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("laharl_beAttacked_LT");
				break;
			}

			break;
		case E_AniDirection::Ani_Right_Top:
			switch (_behavior)
			{
			case E_AniBehavior::Ani_idle:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("battle_idle_RT_Start");
				break;
			case E_AniBehavior::move:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("move_RT_Start");
				break;
			case E_AniBehavior::Ani_attack:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("battle_Punching_RT_Start");
				break;
			case E_AniBehavior::Ani_be_Attacked:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("laharl_beAttacked_RT");
				break;
			}

			break;
		case E_AniDirection::Ani_Right_Bottom:
			switch (_behavior)
			{
			case E_AniBehavior::Ani_idle:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("battle_idle_RB_Start");
				break;
			case E_AniBehavior::move:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("move_RB_Start");
				break;
			case E_AniBehavior::Ani_attack:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("battle_Punching_RB_Start");
				break;
			case E_AniBehavior::Ani_be_Attacked:
				_currentAnimation = ANIMATIONMANAGER->findAnimation("laharl_beAttacked_RB");
				break;
			}
			break;
		}
		_currentAnimation->AniStart();
	}*/
	
}

void Laharl::render(void)
{
	GameCharacter::render();
}

