#include "Stdafx.h"
#include "Ghost.h"


Ghost::Ghost()
{
}

Ghost::~Ghost()
{
}

HRESULT Ghost::init(void)
{
	GameCharacter::init();

	return S_OK;
}

HRESULT Ghost::init(string fileName, int x, int y, int coorX, int coorY, E_UnitType type, int imgCorrectionX, int imgCorrectionY)
{
	GameCharacter::init(fileName, x, y, coorX, coorY, type, imgCorrectionX, imgCorrectionY);
	_stats->setStat(2, 5, 0, 10, 10, 10, 10, 5, 3, 0, 10, 60, 0, 0, 10);

	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Ghost_moveIdle_LB");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Ghost_moveIdle_LB");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Ghost_attack_LB");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Ghost_beAttacked_LB");

	_animation[Ani_Left_Top][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Ghost_moveIdle_LT");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Ghost_moveIdle_LT");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Ghost_attack_LT");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Ghost_beAttacked_LT");

	_animation[Ani_Right_Top][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Ghost_moveIdle_RT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Ghost_moveIdle_RT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Ghost_attack_RT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Ghost_beAttacked_RT");

	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Ghost_moveIdle_RB");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Ghost_moveIdle_RB");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Ghost_attack_RB");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Ghost_beAttacked_RB");

	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Ghost_jump_LB");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Ghost_jump_LT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Ghost_jump_RT");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Ghost_jump_RB");

	_currentAnimation = _animation[Ani_Right_Bottom][E_AniBehavior::Ani_idle];

	_iconIndex = 10;
	_battleFaceIndex = 3;
	_attackIndex = 7;

	return S_OK;
}

void Ghost::release(void)
{
	GameCharacter::release();
}

void Ghost::update(void)
{
	GameCharacter::update();
}

void Ghost::render(void)
{
	GameCharacter::render();
}
