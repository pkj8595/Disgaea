#pragma once
#include "Rocket.h"
#include "Tilemap.h"
#include "EnemyManager.h"
#include "ShootingEffect.h"

#define _USE_MATH_DEFINES
#include "math.h"

#define TILE_MAP_SIZE		25
class ShootingScene : public GameNode
{

private:
	Rocket* _rocket;
	EnemyManager* _em;
	//Tilemap* _tileMap;
	MissileEffect* _missileEffect;
	BeamEffect* _beamEffect;

	char _text[64];

	float _x, _y;

	bool _isGameStop;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void collision(void);

	ShootingScene() {}
	virtual~ShootingScene() {}
};

