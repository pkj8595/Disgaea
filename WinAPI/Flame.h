#pragma once
#include "GameNode.h"


#define FLAME_COUNT 4.0f

class Flame : public GameNode
{
private:
	RECT _rc;
	float* _x;
	float* _y;
	float _flameTick;
	my::Image* _image;

public:
	HRESULT init(const char* fileName, float* x,float*y);
	void release(void);
	void update(void);
	void render(void);

	RECT getRc() { return _rc; }
	void setRc(RECT rc) { _rc = rc; }

	Flame();
	~Flame();
};

