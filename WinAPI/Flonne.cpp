#include "Stdafx.h"
#include "Flonne.h"

Flonne::Flonne()
{
}

Flonne::~Flonne()
{
}

HRESULT Flonne::init(void)
{
	GameCharacter::init();

	return S_OK;
}

HRESULT Flonne::init(string fileName, int x, int y, int coorX, int coorY, E_UnitType type, int imgCorrectionX, int imgCorrectionY)
{
	GameCharacter::init(fileName, x, y, coorX, coorY, type, imgCorrectionX, imgCorrectionY);
	_stats->setStat(2, 6, 0, 20, 20, 10, 10, 5, 3, 0, 10, 60, 0, 0, 10);

	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Flonne_Idle_LB");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Flonne_move_LB");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Flonne_punch_LB");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Flonne_beAttacked_LB");

	_animation[Ani_Left_Top][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Flonne_Idle_LT");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Flonne_move_LT");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Flonne_punch_LT");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Flonne_beAttacked_LT");

	_animation[Ani_Right_Top][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Flonne_Idle_RT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Flonne_move_RT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Flonne_punch_RT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Flonne_beAttacked_RT");

	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Flonne_Idle_RB");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Flonne_move_RB");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Flonne_punch_RB");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Flonne_beAttacked_RB");

	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Flonne_jump_LB");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Flonne_jump_LT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Flonne_jump_RT");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Flonne_jump_RB");

	_currentAnimation = _animation[Ani_Right_Bottom][E_AniBehavior::Ani_idle];

	_iconIndex = 2;
	_battleFaceIndex = 2;

	return S_OK;
}

void Flonne::release(void)
{
	GameCharacter::release();
}

void Flonne::update(void)
{
	GameCharacter::update();
}

void Flonne::render(void)
{
	GameCharacter::render();
}
