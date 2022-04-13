#pragma once
#include "GameNode.h"
#include "CTileObject.h"
class CTimeMap : public GameNode
{
private:
	vector< vector<CTileObject*> > _vTotalTile;
	vector< vector<CTileObject*> >::iterator _viTile;
	vector< CTileObject* > _vTileRow;

	int _arrSize;
	int _rcSize;

	TileAstarType _curTileType;

public:
	HRESULT init(void);
	HRESULT init(int arrSize, int rcSize);
	void release(void);
	void update(void);
	void render(void);

	void reset(void);
	void startPathPinding(void);
	
};

