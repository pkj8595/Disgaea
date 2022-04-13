#pragma once
#include "GameCharacter.h"

class Laharl : public GameCharacter
{
private:

public:
	virtual HRESULT init(void);
	virtual HRESULT init(string fileName, int x, int y, int coorX, int coorY, E_UnitType type, int imgCorrectionX = 0, int imgCorrectionY = 0);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	Laharl();
	~Laharl();
};

