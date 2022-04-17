#pragma once
#include "GameNode.h"
#include "IsometricMap.h"
#include "TurnSystem.h"

class GameManager;
class BattleScene : public GameNode
{
private:
	IsometricMap*	_map;
	TurnSystem*		_turnSystem;

	my::Image*		_backImg;
	my::Image*		_mapImg;
	RECT			_backRc;
	POINT			_backPoint;
	int				_beforeCharCount;

public:
	HRESULT init(void);
	void JsonSetUpIsoMap();
	void release(void);
	void update(void);
	void render(void);

	BattleScene() {}
	~BattleScene() {}
};

