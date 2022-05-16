#pragma once
#include "GameNode.h"

class GameMapUI:public GameNode
{
protected:
	my::Image* _img;
	RECT _rc;
	POINT _coor;
	POINT _point;
	POINT _correctionPt;
	bool _isActive;
	ZOrderData* _zData;

public:
	HRESULT init(void);
	HRESULT init(string imgkey,POINT coordinate,POINT point, ZIndexType zIndex);
	HRESULT init(string imgkey,POINT coordinate,POINT point,POINT correctionPt, ZIndexType zIndex);
	void release(void);
	void update(void);
	void render(void);

	int getCoordinateX() { return _coor.x; }
	int getCoordinateY() { return _coor.y; }
	int getX() { return _point.x; }
	int getY() { return _point.y; }
	bool getIsActive() { return _isActive; }

	POINT getCoorPoint() { return _coor; }
	POINT getPoint() { return _point; }
	POINT* getPointAddress() { return &_point; }
	RECT getRect() { return _rc; }

	void setCoordinateX(int coorx) {  _coor.x = coorx; }
	void setCoordinateY(int coory) { _coor.y = coory; }
	void setX(int pointX) {  _point.x = pointX; }
	void setY(int pointY) {  _point.y = pointY; }
	void setIsActive(bool isActive) {  _isActive = isActive; }

	void setCoorPoint(POINT coordinate) {  _coor = coordinate; }
	void setPoint(POINT point) {  _point = point; }

	GameMapUI();
	~GameMapUI();
};

