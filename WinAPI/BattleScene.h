#pragma once
#include "GameNode.h"
#include "IsometricMap.h"
#include "TurnSystem.h"
#include "VictoryUI.h"


class GameManager;
class BattleScene : public GameNode
{
private:
	IsometricMap*	_map;
	TurnSystem*		_turnSystem;
	VictoryUI*		_gameEndUI;

	my::Image*		_backImg;
	my::Image*		_mapImg;
	RECT			_backRc;
	POINT			_backPoint;
	int				_beforeCharCount;
	string			_soundStr;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void JsonSetUpIsoMap();

	BattleScene() {}
	~BattleScene() {}
};

