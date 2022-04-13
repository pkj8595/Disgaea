#include "Stdafx.h"
#include "GameUI.h"

GameMapUI::GameMapUI()
{
}

GameMapUI::~GameMapUI()
{
}

HRESULT GameMapUI::init(void)
{
	return S_OK;
}

HRESULT GameMapUI::init(string imgkey, POINT coordinate, POINT point, ZIndexType zIndex)
{
	_img = IMAGEMANAGER->findImage(imgkey);
	_coor = coordinate;
	_point = point;
	_rc = RectMakeCenter(_point.x, _point.y, _img->getWidth(), _img->getHeight());
	_isActive = false;
	_zData = new ZOrderData;
	_zData->setRenderData(&_rc, nullptr, &_img,&_isActive);
	_correctionPt = PointMake(0, 0);
	CAMERA->registerZData(zIndex, _zData);
	return S_OK;
}

HRESULT GameMapUI::init(string imgkey, POINT coordinate, POINT point, POINT correctionPt, ZIndexType zIndex)
{
	_img = IMAGEMANAGER->findImage(imgkey);
	_coor = coordinate;
	_point = point;
	_correctionPt = correctionPt;
	_rc = RectMakeCenter(_point.x+ _correctionPt.x, _point.y+ _correctionPt.y, _img->getWidth(), _img->getHeight());
	_isActive = false;
	_zData = new ZOrderData;
	_zData->setRenderData(&_rc, nullptr, &_img, &_isActive);
	CAMERA->registerZData(zIndex, _zData);
	return S_OK;
}

void GameMapUI::release(void)
{
	CAMERA->removeZData(_zData);
	SAFE_DELETE(_zData);
}

void GameMapUI::update(void)
{
	_rc = RectMakeCenter(_point.x + _correctionPt.x, _point.y + _correctionPt.y, _img->getWidth(), _img->getHeight());
}

void GameMapUI::render(void)
{
	//_img->render(getMemDC(), _rc.left - CAMERA->getLeft(), _rc.top - CAMERA->getTop());
}

