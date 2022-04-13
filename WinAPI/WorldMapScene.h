#pragma once
#include "GameNode.h"
#include "CWindowUI.h"

/*
1. 백그라운드 이미지 
2. window UI 

maptype이 바뀌면 이미지와 windowUI가 바뀐다. 

*/



enum class E_WorldMapType
{
	HOME,
	STAGE1,
	STAGE2
};
class WorldMapScene : public GameNode
{
private:
	E_WorldMapType	_mapType;
	my::Image*		_backImg;
	RECT			_backRc;
	CWindowUI*		_currentUI;

	bool			_isExcuteChangeScene;

	int				_stageMainNum;
	int				_stageSubNum;

	vector<pair< E_WorldMapType,CWindowUI*>> _stageList;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void stageSetup();
	void changeWorldMapType(E_WorldMapType mapType);

	WorldMapScene():_currentUI(nullptr),
					_backImg(nullptr)
	{
	}
	~WorldMapScene() {}
};

