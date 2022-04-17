#pragma once
#include "GameNode.h"
#include "CWindowUI.h"

enum class E_WorldMapType
{
	HOME,
	STAGE1,
	STAGE2
};
class GameCharacter;
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

	float			_healStartTime;
	bool			_healTextActive;
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

