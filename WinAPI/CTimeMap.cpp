#include "Stdafx.h"
#include "CTimeMap.h"

HRESULT CTimeMap::init(void)
{
	return S_OK;
}

HRESULT CTimeMap::init(int arrSize, int rcSize)
{
	_arrSize = arrSize;
	_rcSize = rcSize;
	_curTileType = TileAstarType::NONE;

	for (int i = 0; i < _arrSize; i++)
	{
		for (int j = 0; j < _arrSize; j++)
		{
			CTileObject* temp = new CTileObject;
			temp->init();
			temp->setCoordinate(POINT{ j,i });
			temp->setRect(RectMake(j*_rcSize + TILE_START_X, i*_rcSize + TILE_START_Y, _rcSize, _rcSize));
			_vTileRow.push_back(temp);
		}
		_vTotalTile.push_back(_vTileRow);
		_vTileRow.clear();
	}
	cout << "_arrSize :"<< _arrSize <<", _rcSize :"<< _rcSize << endl;
	return S_OK;
}

void CTimeMap::release(void)
{
	for (vector<CTileObject*> vrow : _vTotalTile)
	{
		for (CTileObject* tile : vrow)
		{
			tile->release();
			SAFE_DELETE(tile);
		}
	}
	_vTotalTile.clear();
}

void CTimeMap::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (vector<CTileObject*> vrow : _vTotalTile)
		{
			for (CTileObject* tile : vrow)
			{
				if (PtInRect(&tile->getRect(), _ptMouse))
				{
					tile->setTileType(_curTileType);

					break;
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		startPathPinding();
	}
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_curTileType = TileAstarType::START;
		cout << "_curTileType = START" << endl;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_curTileType = TileAstarType::TARGET;
		cout << "_curTileType = TARGET" << endl;
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_curTileType = TileAstarType::WALL;
		cout << "_curTileType = WALL" << endl;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		reset();
	}
}

void CTimeMap::render(void)
{
	for (vector<CTileObject*> vrow : _vTotalTile)
	{
		for (CTileObject* tile : vrow)
		{
			tile->render();
		}
	}
}

void CTimeMap::reset(void)
{
	for (vector<CTileObject*> vrow : _vTotalTile)
	{
		for (CTileObject* tile : vrow)
		{
			tile->setParentTile(nullptr);
			tile->setTileType(TileAstarType::NONE);
			tile->setHCost(0);
			tile->setGCost(0);
			tile->setFCost(0);
		}
	}
}

void CTimeMap::startPathPinding(void)
{
	priority_queue< CTileObject*, vector<CTileObject*>, cmp> pqMinOpenList;

	CTileObject* start = nullptr;
	CTileObject* target = nullptr;
	CTileObject* currentTile = nullptr;

	for (vector<CTileObject*> vrow : _vTotalTile)
	{
		for (CTileObject* tile : vrow)
		{
			if (tile->getTileType() == TileAstarType::START)
			{
				start = tile;
			}
			else if (tile->getTileType() == TileAstarType::TARGET)
			{
				target = tile;
			}
		}
	}
	
	start->getComputeFCost(target);
	currentTile = start;
	while (true)
	{
		currentTile->setTileType(TileAstarType::CLOSE);
		//8방향 계산
		//int comparedFcost =0;
		for (int i = 0; i < 9; i++)
		{
			if (i==4) continue;
			int yRange = currentTile->getCoordinate().y + ((i / 3) - 1);
			int xRange = currentTile->getCoordinate().x + ((i % 3) - 1);
			if ( yRange < 0 || yRange > _arrSize-1 || xRange < 0 || xRange > _arrSize - 1)
			{
				continue;
			}

			CTileObject* selectTile;
			selectTile = _vTotalTile[yRange][xRange];
			
			if (selectTile->getTileType() == TileAstarType::NONE ||
				selectTile->getTileType() == TileAstarType::TARGET||
				selectTile->getTileType() == TileAstarType::OPEN)
			{
				selectTile->setParentTile(currentTile);
				selectTile->getComputeFCost(target);
				
				selectTile->setTileType(TileAstarType::OPEN);
				pqMinOpenList.push(selectTile);
			}
		}

		if (currentTile == target)
		{
			cout << "end" << endl;
			currentTile->setTileType(TileAstarType::ASTAR_END);
			CTileObject* parentTile = currentTile->getParentTile();
			while (true)
			{
				parentTile->setTileType(TileAstarType::ASTAR_END);
				if (parentTile == start)break;
				parentTile = parentTile->getParentTile();
			}
			break;
		}

		if (!pqMinOpenList.empty())
		{
			currentTile = pqMinOpenList.top();
			pqMinOpenList.pop();
		}
		else
		{
			cout << "pqMinOpenList.empty" << endl;
			break;
		}
		
	}

}

