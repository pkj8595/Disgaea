#pragma once
#include "GameNode.h"

#define PLAYER_TURN_FRAME	6
#define ENEMY_TURN_FRAME	7
class TurnStateUI :public GameNode
{
	enum class E_AlphaState
	{
		INCREASE,
		STOP,
		DIMINISH
	};
private:
	my::Image*	_stateImg;
	RECT		_stateRc;
	POINT		_statePoint;

	my::Image*	_backImg;
	RECT		_backRc;
	POINT		_backPoint;

	float		_startTime;
	float		_stayStartTime;
	bool		_isPlayerTurn;
	bool		_isActive;
	E_AlphaState	_alphaState;

	BYTE		_backAlpha;
	CALLBACKFUNCTION	_function;
	
public:
	HRESULT init(CALLBACKFUNCTION function);
	void release(void);
	void update(void);
	void render(void);

	void StartTurnStateAnimation(bool isPlayerTurn);

	void setIsActive(bool isActive) { _isActive = isActive; }
	bool getIsActive(void) { return _isActive; }

	TurnStateUI();
	~TurnStateUI();
};

