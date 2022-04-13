#include "Stdafx.h"
#include "TileMapScene.h"

HRESULT TileMapScene::init(void)
{
	_tileMap = new CTimeMap;
	_tileMap->init(10, 80);
	return S_OK;
}

void TileMapScene::release(void)
{
	_tileMap->release();
	SAFE_DELETE(_tileMap);
}

void TileMapScene::update(void)
{
	_tileMap->update();
}

void TileMapScene::render(void)
{
	_tileMap->render();
}
