#include "Stdafx.h"
#include "IsometricTile.h"


IsometricTile::IsometricTile():_parentTile(nullptr),
								_tileUnit(nullptr),
								_alpha(nullptr)
{
}

IsometricTile::~IsometricTile()
{
}

HRESULT IsometricTile::init(int coordinateX, int coordinateY, int x, int y, int wight, int height)
{
	_tileCoordinate.x = coordinateX;
	_tileCoordinate.y = coordinateY;
	_point.x = x;
	_point.y = y;
	_G = _H = _F = 0;
	_rc = RectMakeCenter(x, y, wight, height);
	_type = IsoTileType::NONE;
	_parentTile = nullptr;
	
	_isoPoint[0] = PointMake( (_rc.left + _rc.right)*0.5, _rc.top );
	_isoPoint[1] = PointMake( _rc.right, (_rc.top + _rc.bottom)*0.5 );
	_isoPoint[2] = PointMake( (_rc.left + _rc.right)*0.5, _rc.bottom );
	_isoPoint[3] = PointMake( _rc.left, (_rc.top + _rc.bottom)*0.5 );

	_redTileImg = IMAGEMANAGER->findImage("RedTile");
	_blueTileImg = IMAGEMANAGER->findImage("BlueTile");
	_tileImg = IMAGEMANAGER->findImage("mapTile");

	_isShowRange = false;
	_isSelectAble = false; 

	return S_OK;
}

void IsometricTile::release(void)
{
}

void IsometricTile::update(void)
{
	
}

void IsometricTile::render(void)
{
	if (_type != IsoTileType::WALL)
	{
		_tileImg->render(getMemDC(), _rc.left-CAMERA->getLeft(), _rc.top - CAMERA->getTop());
	}

	if (KEYMANAGER->isToggleKey(VK_F2))
	{

		//RectangleMakeToRECT(getMemDC(), _rc);
		COLORREF color;
		switch (_type)
		{
			case IsoTileType::NONE:
				color = RGB(255, 255, 255);
				break;
			case IsoTileType::OPEN:
				color = RGB(0, 255, 0);
				break;
			case IsoTileType::CLOSE:
				color = RGB(255, 0, 0);
				break;
			case IsoTileType::WALL:
				color = RGB(150, 75, 0);
				break;
			case IsoTileType::TARGET:
				color = RGB(0, 0, 255);
				break;
			case IsoTileType::START:
				color = RGB(255, 255, 0);
				break;
			case IsoTileType::ASTAR_END:
				color = RGB(80, 188, 223);
				break;
		}

		HBRUSH brush = CreateSolidBrush(color);
		HBRUSH currentBrush = (HBRUSH)SelectObject(getMemDC(), brush);

		_isoPoint[0] = PointMake((_rc.left + _rc.right)*0.5 - CAMERA->getLeft(), _rc.top - CAMERA->getTop());
		_isoPoint[1] = PointMake(_rc.right - CAMERA->getLeft(), (_rc.top + _rc.bottom)*0.5 - CAMERA->getTop());
		_isoPoint[2] = PointMake((_rc.left + _rc.right)*0.5 - CAMERA->getLeft(), _rc.bottom - CAMERA->getTop());
		_isoPoint[3] = PointMake(_rc.left - CAMERA->getLeft(), (_rc.top + _rc.bottom)*0.5 - CAMERA->getTop());

		Polygon(getMemDC(), _isoPoint,4);

		SelectObject(getMemDC(), currentBrush);
		DeleteObject(brush);
	}


	if (_isShowRange)
	{
		if (_isSelectAble)
		{
			_blueTileImg->alphaRender(getMemDC(), _rc.left - CAMERA->getLeft(), _rc.top - CAMERA->getTop(), *_alpha);
		}
		else
		{
			_redTileImg->alphaRender(getMemDC(), _rc.left - CAMERA->getLeft(), _rc.top - CAMERA->getTop(), *_alpha);
		}
	}

	
	
}

void IsometricTile::AstarDataReset(void)
{
	_G = _H = _F = 0;
	_type = IsoTileType::NONE;
	_parentTile = nullptr;

}

