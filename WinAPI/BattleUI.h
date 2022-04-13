#pragma once
#include "GameUI.h"
class BattleUI : public GameMapUI
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


};

