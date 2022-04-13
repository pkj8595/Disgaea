#pragma once
#include "GameNode.h"

class PixelCollision : public GameNode
{
private:
	my::Image* _pixelTank;
	RECT _rc;
	int _probeY;
	float _x, _y;


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	PixelCollision() {}
	~PixelCollision() {}
};

