#include "Stdafx.h"
#include "Etna.h"


Etna::Etna()
{
}

Etna::~Etna()
{
}

HRESULT Etna::init(void)
{
	GameCharacter::init();

	return S_OK;
}

HRESULT Etna::init(string fileName, int x, int y, int coorX, int coorY, E_UnitType type, int imgCorrectionX, int imgCorrectionY)
{
	GameCharacter::init(fileName, x, y, coorX, coorY, type, imgCorrectionX, imgCorrectionY);
	_stats->setStat(2, 6, 0, 20, 20, 10, 10, 5, 3, 0, 10, 60, 0, 0, 10);

	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Etna_Idle_LB");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Etna_move_LB");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Etna_punch_LB");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Etna_beAttacked_LB");
	_animation[Ani_Left_Bottom][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Etna_jump_LB");

	_animation[Ani_Left_Top][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Etna_Idle_LT");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Etna_move_LT");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Etna_punch_LT");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Etna_beAttacked_LT");
	_animation[Ani_Left_Top][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Etna_jump_LT");
	
	_animation[Ani_Right_Top][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Etna_Idle_RT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Etna_move_RT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Etna_punch_RT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Etna_beAttacked_RT");
	_animation[Ani_Right_Top][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Etna_jump_RT");
	
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_idle] = ANIMATIONMANAGER->findAnimation("Etna_Idle_RB");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_move] = ANIMATIONMANAGER->findAnimation("Etna_move_RB");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_attack] = ANIMATIONMANAGER->findAnimation("Etna_punch_RB");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_be_Attacked] = ANIMATIONMANAGER->findAnimation("Etna_beAttacked_RB");
	_animation[Ani_Right_Bottom][E_AniBehavior::Ani_Jump] = ANIMATIONMANAGER->findAnimation("Etna_jump_RB");

	_currentAnimation = _animation[Ani_Right_Bottom][E_AniBehavior::Ani_idle];

	_iconIndex = 1;
	_battleFaceIndex = 1;
	_title = "∏∂ø’¿« ∞°Ω≈";

	return S_OK;
}

void Etna::release(void)
{
	GameCharacter::release();
}

void Etna::update(void)
{
	GameCharacter::update();
}

void Etna::render(void)
{
	GameCharacter::render();
}
