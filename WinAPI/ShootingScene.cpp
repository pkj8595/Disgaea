#include "Stdafx.h"
#include "ShootingScene.h"


HRESULT ShootingScene::init(void)
{
	_isGameStop = false;
	IMAGEMANAGER->addImage("½´ÆÃ¸Ê", "Resource/Images/Rocket/battlefield.bmp", 600, 1830);

	_rocket = new Rocket;
	_rocket->init();

	_em = new EnemyManager;
	_em->init();

	_em->setRoketMemoryAddress(_rocket);
	_rocket->setEnemyManagerMemoryAddress(_em);

	_missileEffect = new MissileEffect;
	_missileEffect->init();

	_beamEffect = new BeamEffect;
	_beamEffect->init();

	_x = _y = 0.0f;

	//_tileMap = new Tilemap;
	//_tileMap->init(TILE_MAP_SIZE);
	wsprintf(_text, "ShootingScene");

	return S_OK;
}

void ShootingScene::release(void)
{

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SCENEMANAGER->changeScene("½ÃÀÛ");
	}

	_rocket->release();
	SAFE_DELETE(_rocket);
	_em->release();
	SAFE_DELETE(_em);

	_beamEffect->release();
	SAFE_DELETE(_beamEffect);

	_missileEffect->release();
	SAFE_DELETE(_missileEffect);

	//_tileMap->release();
}

void ShootingScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F10)) _isGameStop = !_isGameStop;
	if (_isGameStop) return;
	_rocket->update();
	_em->update();

	RECTOBSERVERMANAGER->getRectFromObserved();
	collision();

	_y -= 5;

	//_beamEffect->update();
	//_missileEffect->update();
	//_tileMap->update();
}

void ShootingScene::render(void)
{
	RECT rc = { 0,0,WINSIZE_X,WINSIZE_Y };
	IMAGEMANAGER->findImage("½´ÆÃ¸Ê")->loopRender(getMemDC(), &rc, _x, _y);

	//_tileMap->render();
	_rocket->render();
	_em->render();

	_beamEffect->render();
	_missileEffect->render();

	TextOut(getMemDC(), CENTER_X, CENTER_Y, _text, strlen(_text));
}


