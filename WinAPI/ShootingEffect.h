#pragma once
#include "GameNode.h"
/*
이펙트는 반드시 매니저가 필요하다.
*/
struct tagEffect 
{
	my::Image* img;
	RECT rc;
	int count;
	float x, y;
};

class BeamEffect :public GameNode
{
private:
	typedef vector<tagEffect> vEffect;
	typedef vector<tagEffect>::iterator vIEffect;

private:
	vEffect _vEffect;
	vIEffect _viEffect;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	BeamEffect() {}
	~BeamEffect() {}
};
class MissileEffect :public GameNode
{
private:
	typedef vector<tagEffect> vEffect;
	typedef vector<tagEffect>::iterator vIEffect;

private:
	vEffect _vEffect;
	vIEffect _viEffect;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void show(RECT rc);
	void draw(void);
	void removeEffect(int arrNum);

	MissileEffect() {}
	~MissileEffect() {}
};

