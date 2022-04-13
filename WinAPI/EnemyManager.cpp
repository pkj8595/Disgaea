#include "Stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
#include "Rocket.h"

EnemyManager::EnemyManager(){
	//DO NOTTING
}

EnemyManager::~EnemyManager(){
	//DO NOTTING
}

HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("해파리", "Resource/Images/Rocket/jelly.bmp", 0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("적 미사일", "Resource/Images/Rocket/bullet.bmp", 7 , 7 , true, RGB(255, 0, 255));

	//미니언 생성
	setMinion();

	_bullet = new Bullet;
	_bullet->init("적 미사일",30,1000);

	return S_OK;
}

void EnemyManager::release(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion) 
	{
		//역참조하니까 되는 이유?
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}

	_bullet->release();
	SAFE_DELETE(_bullet);
}

void EnemyManager::update(void)
{
	_viMinion = _vMinion.begin();
	for (;_viMinion != _vMinion.end(); ++_viMinion) 
	{
		(*_viMinion)->update();
	}
	checkActive();

	minionBulletFire();
	_bullet->update();
	//collision();
}

void EnemyManager::render(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_bullet->render();
}

void EnemyManager::setMinion(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int  j = 0; j < 10; j++)
		{
			Enemy* jellyFish;
			jellyFish = new Minion;
			jellyFish->init("해파리", PointMake(50 + j * 50, 100 + i * 100));
			_vMinion.push_back(jellyFish);

		}
	}
}

//at는 순회하고 해당 인덱스를 반환
//[index]는 배열을 돌다가 인덱스에 접근하면 반환
void EnemyManager::removeMinion(int arrNum)
{
	_vMinion[arrNum]->release();
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

//리스너를 사용하는 것이 좋아보이긴한다. 
void EnemyManager::checkActive(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if (!(*_viMinion)->getIsActive()) 
		{
			(*_viMinion)->release();
			SAFE_DELETE(*_viMinion);
			_viMinion = _vMinion.erase(_viMinion);
			break;
		}
	}
}

void EnemyManager::minionBulletFire(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire()) 
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				getAngle(rc.left + (rc.right - rc.left) / 2,
						rc.bottom + (rc.top - rc.bottom) / 2,
						_rocket->getPosition().x,
						_rocket->getPosition().y),
				RND->getFromFloatTo(2.0f, 4.0f));

		}
	}
}

void EnemyManager::collision(void)
{
	for (int i = 0; i < _bullet->getBullet().size(); i++) 
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getBullet()[i].rc,
			&_rocket->getRect())) 
		{
			_bullet->removeBullet(i);
			_rocket->hitDamage(2.0f);
		}
	}
}

