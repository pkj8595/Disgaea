#pragma once
#include "GameNode.h"
#include "IRectObserved.h"

#define FLAME_COUNT		4.0f

struct tagBullet 
{
	my::Image* img;
	RECT rc;
	int radius;
	int count;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;
};


class tagCBullet :public IRectObserved
{
public:
	ObservedType type;
	my::Image* img;
	RECT rc;
	int radius;
	int count;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;

	void init(void);
	void release(void);
	virtual STObservedData getRectUpdate();
	virtual void collideObject();

};


/*
실습 겸 과제 1. 로켓 무장 변경추가
f1 : 일반 미사일
f2 : 산탄
f3 : 미니 로켓 생성
f4 : 실드
f5 : 유도미사일
f6 : 레이저
f7 : 블랙홀

과제 2 적 움직임 구현
-각각의 객체가 전부 다르게 움직여야 한다.
*/

//배열처럼 미리 정전해두고 발사
class Missile : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	int _bulletMax;
	float _range;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	Missile() {}
	~Missile() {}
};

//쏠때마다 만들고 삭제
class MissileM1 : public GameNode
{	
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }
	void removeBullet(int arrNum);

	MissileM1() {}
	~MissileM1() {}
};

class Beam : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	typedef vector<tagBullet>::iterator iterBullet;

	float _range;
	int _bulletMax;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }

	Beam() {}
	~Beam() {}
};

//공용총알
class Bullet : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	int _bulletMax;
	float _range;

public:
	HRESULT init(const char*imageName,int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);
	vector<tagBullet> getBullet(void) {return _vBullet;}

	Bullet() {}
	virtual ~Bullet() {}
};


//추상 미사일
class AMissile : public GameNode
{
protected:
	vector<tagCBullet*> _vBullet;
	vector<tagCBullet*>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void fire(float x, float y);
	virtual void draw(void);
	virtual void move(void);
	virtual void isRange(void);
	virtual void CheckFire(void);

	AMissile() {}
	virtual ~AMissile() {}
};

class CaseShotMissile : public AMissile
{
private:
	int _bulletCount;
	float _firstAngle;
	const float _offsetAngle = 0.1f;

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void move(void);
	virtual void fire(float x, float y);
};


class BlackholeMissile : public AMissile 
{
private:
	
public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void move(void);
	virtual void fire(float x, float y);
};