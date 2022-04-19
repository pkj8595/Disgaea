#pragma once
#include "GameNode.h"
#include "CWindowUI.h"

class VictoryUI: public GameNode
{
private:
	CWindowUI* _goldWindowUI;
	my::Image* _clearImg;
	my::Image* _brownBackImg;
	BYTE _brownBackAlpha;
	RECT _brownRect;

	bool _isActive;
	bool _isWin;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setGoldUI(int gold);
	void setIsActive(bool active, bool isWin);
	
	bool getIsActive(void) { return _isActive; }
	bool getIsPlayerWin(void) { return _isWin; }

	VictoryUI();
	~VictoryUI();
};

