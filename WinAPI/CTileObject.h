#pragma once
#include "GameNode.h"

#define TILE_START_X	100
#define TILE_START_Y	100



enum class TileAstarType
{
	NONE=0,
	OPEN,
	CLOSE,
	WALL,
	CLIFF,
	TARGET,
	START,
	ASTAR_END
};

class CTileObject : public GameNode
{
private:
	my::Image* _tileImage;

	CTileObject* _node;
	TileAstarType _type;
	POINT _coordinate;
	RECT _rc;
	int _gCost;		//시작점과의 거리(이동했던 경로거리)
	int _hCost;		//타겟과의 예상 거리
	int _fCost;		//위 두 값을 더한 값

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	int computeHCost(CTileObject* target);
	int computeGCost();
	int getFCost(void);
	void setFCost(int f) { _fCost = f; }
	int getComputeFCost(CTileObject* target);

	void setParentTile(CTileObject* node) { _node = node; }
	CTileObject* getParentTile() { return _node; }

	void setTileType(TileAstarType type) { _type = type; }
	TileAstarType getTileType() { return _type; }

	void setCoordinate(POINT coordinate) { _coordinate = coordinate; }
	POINT getCoordinate() { return _coordinate; }

	void setRect(RECT rc) { _rc = rc; }
	RECT getRect() { return _rc; }

	void setGCost(int gcost) { _gCost = gcost; }
	int getGCost() { return _gCost; }

	void setHCost(int hcost) { _hCost = hcost; }
	int getHCost() { return _hCost; }
};

class cmp
{
public:
	bool operator()(CTileObject* a, CTileObject* b)
	{
		return a->getFCost() > b->getFCost();
	}
};