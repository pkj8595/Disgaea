#include "Stdafx.h"
#include "CTileObject.h"

HRESULT CTileObject::init(void)
{
	_tileImage = nullptr;
	_node = nullptr;
	_type = TileAstarType::NONE;
	_coordinate = PointMake(0, 0);
	_rc = RectMake(0,0,0,0);
	_gCost = 0;
	_hCost = 0;
	_fCost = 0;
	return S_OK;
}

void CTileObject::release(void)
{
	_node = nullptr;
	_tileImage = nullptr;
}

void CTileObject::update(void)
{
}

void CTileObject::render(void)
{
	COLORREF color = RGB(0, 0, 0);
	switch (_type)
	{
		case TileAstarType::NONE:
			color = RGB(255, 255, 255);
			break;
		case TileAstarType::OPEN:
			color = RGB(0, 255, 0);
			break;
		case TileAstarType::CLOSE:
			color = RGB(255, 0, 0);
			break;
		case TileAstarType::WALL:
			color = RGB(75, 75, 75);
			break;
		case TileAstarType::TARGET:
			color = RGB(0,0,255);
			break;
		case TileAstarType::START:
			color = RGB(255, 255, 0);
			break;
		case TileAstarType::ASTAR_END:
			color = RGB(80, 188, 223);
			break;
	}
	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	RectangleMakeToRECT(getMemDC(),_rc);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);

	char coordinateStr[64];
	sprintf(coordinateStr, "(%d, %d)", _coordinate.x, _coordinate.y);
	FONTMANAGER->drawTextRectCenter(getMemDC(), _rc, "µÕ±Ù¸ð²Ã", 15, 40, coordinateStr, strlen(coordinateStr), (RGB(0, 0, 0)));

	char costStr[64];
	sprintf(costStr, "G : %d\nH : %d\nF : %d", _gCost, _hCost, _fCost);
	FONTMANAGER->drawText(getMemDC(), _rc.left+10,_rc.top+20, "µÕ±Ù¸ð²Ã", 15, 40, costStr, strlen(costStr), (RGB(0, 0, 0)));

}


int CTileObject::computeHCost(CTileObject* target)
{
	int hx = abs(this->getCoordinate().x - target->getCoordinate().x);
	int hy = abs(this->getCoordinate().y - target->getCoordinate().y);
	if (hx > hy)
	{
		hx = hx - hy;
		_hCost = hy * 14;
		_hCost = _hCost + (hx * 10);
	}
	else
	{
		hy = hy - hx;
		_hCost = hx * 14;
		_hCost = _hCost +(hy * 10);
	}

	return _hCost;
}

int CTileObject::computeGCost()
{
	if (_node == nullptr)
	{
		_gCost = 0;
		return _gCost;
	}
	else
	{
		int gx = abs(this->getCoordinate().x - _node->getCoordinate().x);
		int gy = abs(this->getCoordinate().y - _node->getCoordinate().y);
		

		if (gx + gy > 2)
		{
			cout << "CTileObject::computeGCost() : "<< gx << " , "<< gy << endl;
		}
		else if (gx + gy > 1)
		{
			_gCost = _node->getGCost() + 14;
		}
		else
		{
			_gCost = _node->getGCost() + 10;
		}
	}
}

int CTileObject::getFCost()
{
	return _fCost;
}

int CTileObject::getComputeFCost(CTileObject* target)
{
	computeHCost(target);
	computeGCost();

	_fCost = _hCost + _gCost;
	return _fCost;
}
