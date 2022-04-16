#pragma once
#include "GameNode.h"
#include "BattleUI.h"
#include "CWindowUI.h"
#include "CharInfoUI.h"
#include "TurnStateUI.h"
#include "CharStatusUI.h"


#define UI_CAMERA_MOVEING_SPEED		10
enum EBATTLE_UI_TYPE
{
	UI_BLUESIGN = 0,
	UI_MAPSIGN,
	UI_BattleStartObj,
	EBATTLE_UI_TYPE_END
};

enum class EControl_State
{
	Map_Cursor,
	Character_BehaviorWindow,
	Turn_Window,
	Character_CreateWindow
};

enum class EOkBtnState
{
	Nomal,
	Move,
	Attack
};

class IsometricMap;
class TurnSystem :public GameNode
{
private:
	IsometricMap* _map;
	GameMapUI* _battleUi[EBATTLE_UI_TYPE_END];
	POINT* _mapSize;
	bool* _isCharacterMove;
	bool* _isRunnigBehavior;
	bool _isCharacterSelect;
	bool _isPlayerTrunStart;
	CWindowUI* _charBehaviorWindow;
	CWindowUI* _turnWindow;
	CWindowUI* _charCreateWindow;

	POINT _tileRangeTargetPoint;
	POINT _tileRangeStartPoint;
	int _selectedCharRange;

	EControl_State _controlState;
	EOkBtnState _okBtnState;
	CharInfoUI*	_infoUI;
	TurnStateUI* _turnStateUI;
	CharStatusUI* _charStatusUI;

	POINT	_startPt;
	vector<GameCharacter*> _vPlayerChar;
	vector<GameCharacter*>::iterator _vIPlayerChar;
	int	_playerCharSize;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void registerMapAddress(IsometricMap* isoMap) { _map = isoMap; }
	void setInitBattleUI(POINT point);

	POINT correctionTileIndex(POINT coordinate);
	int correctionXIndex(int xindex);
	int correctionYIndex(int yindex);

	void characterWindowSetup(void);
	void turnWindowSetup(void);
	void createCharacterWindowSetup(void);

	inline void updateBattleUI(void);

	TurnSystem() {}
	~TurnSystem() {}
};

