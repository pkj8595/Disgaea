#pragma once
#include "GameNode.h"
#include "IsometricMap.h"
#include "TurnSystem.h"

#define TURN_OBJECT_SIZE	128

class GameManager;
class BattleScene : public GameNode
{
private:
	bitset<TURN_OBJECT_SIZE> _turnObjActive;
	IsometricMap* _map;
	TurnSystem* _turnSystem;

	my::Image*	_backImg;
	RECT		_backRc;
	POINT		_backPoint;

public:
	HRESULT init(void);
	void JsonSetUpIsoMap();
	void release(void);
	void update(void);
	void render(void);

	BattleScene() {}
	~BattleScene() {}
};

