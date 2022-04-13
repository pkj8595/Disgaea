#pragma once
#include "GameNode.h"


enum class IsoTileType
{
	NONE = 0,
	OPEN,
	CLOSE,
	WALL,
	TARGET,
	START,
	ASTAR_END,
};

class GameCharacter;
class IsometricTile : public GameNode
{
private:
	IsometricTile* _parentTile;
	GameCharacter* _tileUnit;
	IsoTileType _type;
	my::Image* _redTileImg;
	my::Image* _blueTileImg;
	my::Image* _tileImg;

	POINT _tileCoordinate;
	POINT _point;
	RECT _rc;
	POINT _isoPoint[4];
	int _G, _H, _F;
	int* _alpha;
	bool _isShowRange;
	bool _isSelectAble;

public:
	HRESULT init(int coordinateX,int coordinateY,int x , int y, int wight,int height);
	void release(void);
	void update(void);
	void render(void);

	void setParentTile(IsometricTile* parentTile)
	{_parentTile = parentTile; }
	IsometricTile* getParentTile(){ return _parentTile; }

	int getCoordinateX() { return _tileCoordinate.x; }
	int getCoordinateY() { return _tileCoordinate.y; }
	int getX() { return _point.x; }
	int getY() { return _point.y; }

	POINT getCoorPoint() { return _tileCoordinate; }
	POINT getPoint() { return _point; }
	void setAlpha(int* alpha) { _alpha = alpha; }

	int getG() { return _G; }
	int getH() { return _H; }
	int getF() { return _F; }
	IsoTileType getTileType(){return _type; }

	void setG(int num) { _G=num; }
	void setH(int num) { _H=num; }
	void setF(int num) { _F=num; }
	void setTileType(IsoTileType type){_type = type;}

	void setCoorPoint(POINT coor) {_tileCoordinate = coor; }
	void setPoint(POINT point) { _point = point; }

	void AstarDataReset(void);
	GameCharacter* getTileGameCharacter() { return _tileUnit; }
	void setTileGameCharacter(GameCharacter* character) { _tileUnit = character; }

	void showTileRange(bool isshow) { _isShowRange = isshow; }
	bool getShowTileRange() { return _isShowRange; }
	void setSelectAbleTile(bool able) { _isSelectAble = able; }
	bool getSelectAbleTile(void) { return _isSelectAble; }

	IsometricTile();
	~IsometricTile();

	class isocmp
	{
	public:
		bool operator()(IsometricTile* a, IsometricTile* b)
		{
			return a->getF() > b->getF();
		}
	};
};

