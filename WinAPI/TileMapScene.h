#pragma once
#include "GameNode.h"
#include "CTimeMap.h"
#include "IsometricTile.h"

class TileMapScene : public GameNode
{
private:
	CTimeMap* _tileMap;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

