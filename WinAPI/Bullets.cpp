#include "Stdafx.h"
#include "Bullets.h"

//=============================================
// ### Bullet ###
//=============================================

HRESULT Bullet::init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;
	return S_OK;
}

void Bullet::release(void)
{
	_vBullet.clear();
}

void Bullet::update(void)
{
	move();

}

void Bullet::render(void)
{
	draw();
}

void Bullet::fire(float x, float y, float angle, float speed)
{
	//최대 발사갯수 막는다.
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());

	_vBullet.push_back(bullet);
}

void Bullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet) 
	{
		_viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void Bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();) 
	{
		_viBullet->x += cosf(_viBullet->angle)*_viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle)*_viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getWidth(), _viBullet->img->getHeight());
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;

	}
}

void Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

//=============================================
// ### Missile ###
//=============================================

HRESULT Missile::init(int bulletMax, float range)
{
	_range = range;
	for (int i = 0; i < bulletMax; i++) 
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));

		bullet.img = new my::Image;
		bullet.img->init("Resource/Images/Rocket/Missile.BMP", 0.0f, 0.0f, 416 , 64 , 13 , 1 , true, RGB(255, 0, 255));
		bullet.fire = false;
		bullet.speed = 5.0f;

		_vBullet.push_back(bullet);
	}
	return S_OK;
}

void Missile::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet) 
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void Missile::update(void)
{
	move();
}

void Missile::render(void)
{
	draw();
}

void Missile::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		break;
	}

}

void Missile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet) 
	{
		if (!_viBullet->fire) continue;
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		_viBullet->count++;
		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void Missile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y)) 
		{
			_viBullet->fire = false;
		}

	}

	/*
		//flame
		if (FLAME_COUNT + _viBullet->flameTick <= GetTickCount())
		{
			_viBullet->flameTick = GetTickCount();
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->img->getFrameWidth(),
				_viBullet->img->getFrameHeight());
		}

		//isfire
		if ((_viBullet->y + _viBullet->img->getFrameHeight()) < 0)
		{
			cout << "fire : false" << endl;
			_viBullet->fire = false;
		}
		*/
}




//=============================================
// ### MissileM1 ###
//=============================================

HRESULT MissileM1::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	
	return S_OK;
}

void MissileM1::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet) 
	{
		SAFE_DELETE(_viBullet->img);
	}
	_vBullet.clear();
}

void MissileM1::update(void)
{
	move();
}

void MissileM1::render(void)
{
	draw();
}

void MissileM1::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size())return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = new my::Image;
	bullet.img->init("Resource/Images/Rocket/Missile.BMP", 0.0f, 0.0f, 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet.speed = 4.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);
}

void MissileM1::draw(void)
{
	/*
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
	*/

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		_viBullet->count++;
		if (_viBullet->count % 3 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}

}

void MissileM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y+100))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}

	/*
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//flame
		if (FLAME_COUNT + _viBullet->flameTick<= GetTickCount())
		{
			_viBullet->flameTick = GetTickCount();
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);

			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->img->getFrameWidth(),
				_viBullet->img->getFrameHeight());
		}

		//isfire
		if ((_viBullet->y + _viBullet->img->getFrameHeight()) < 0)
		{
			cout << "MissileM1::fire = false" << endl;
			_viBullet->fire = false;
			SAFE_DELETE(_viBullet->img);
			_vBullet.erase(_viBullet);
			break;
		}
	}

	*/
}

void MissileM1::removeBullet(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].img);
	_vBullet.erase(_vBullet.begin() + arrNum);
}


//==================================
// ### Beam ###
//==================================
HRESULT Beam::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	return S_OK;
}

void Beam::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void Beam::update(void)
{
	move();
}

void Beam::render(void)
{
	draw();
}

void Beam::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size())return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = new my::Image;
	bullet.img->init("Resource/Images/Rocket/Beam.bmp", 0.0f, 0.0f, 412, 801, 4, 1, true, RGB(255, 0, 255));
	bullet.speed = 0.1f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
	_vBullet.push_back(bullet);

}

void Beam::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		_viBullet->count++;
		if (_viBullet->count % 3 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void Beam::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		cout << getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y) << endl;

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}


//=============================================
// ### AMissile ###
//=============================================

HRESULT AMissile::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void AMissile::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE((*_viBullet)->img);
	}
	_vBullet.clear();
}

void AMissile::update(void)
{
	move();
	isRange();
	CheckFire();
}

void AMissile::render(void)
{
	draw();
}

void AMissile::fire(float x, float y)
{
	
}

void AMissile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->img->frameRender(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);

		(*_viBullet)->count++;
		if ((*_viBullet)->count % 3 == 0)
		{
			(*_viBullet)->img->setFrameX((*_viBullet)->img->getFrameX() + 1);
			if ((*_viBullet)->img->getFrameX() >= (*_viBullet)->img->getMaxFrameX())
			{
				(*_viBullet)->img->setFrameX(0);
			}
			(*_viBullet)->count = 0;
		}
	}
}

void AMissile::move(void)
{
	//for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();++_viBullet)
	//{
	//	_viBullet->y -= _viBullet->speed;
	//	_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
	//		_viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
	//}
}

void AMissile::isRange()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();) 
	{
		//사거리 밖으로 나갔음
		if (_range < getDistance((*_viBullet)->fireX, (*_viBullet)->fireY, (*_viBullet)->x, (*_viBullet)->y + 100))
		{
			SAFE_DELETE((*_viBullet)->img);
			(*_viBullet)->fire = false;
			(*_viBullet)->release();
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
	
}

void AMissile::CheckFire()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();++_viBullet)
	{
		if (!(*_viBullet)->fire) 
		{
			SAFE_DELETE((*_viBullet)->img);
			(*_viBullet)->release();
			_viBullet = _vBullet.erase(_viBullet);
			break;
		}
	}
}

//==================================
// ### CaseShotMissile ###
//==================================

HRESULT CaseShotMissile::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	_bulletCount = 0;
	_firstAngle = (PI/2)+(static_cast<float>(bulletMax / 2)*_offsetAngle);
	return S_OK;
}

void CaseShotMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getFrameWidth(), (*_viBullet)->img->getFrameHeight());
	}
}

void CaseShotMissile::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size())return;

	for (int i = 0; i < _bulletMax; i++)
	{
		tagCBullet* bullet = new tagCBullet;
		bullet->img = new my::Image;
		bullet->img->init("Resource/Images/Rocket/Missile.BMP", 0.0f, 0.0f, 416, 64, 13, 1, true, RGB(255, 0, 255));
		bullet->type = ObservedType::ROCKET_MISSILE;
		bullet->speed = 4.0f;
		bullet->x = bullet->fireX = x;
		bullet->y = bullet->fireY = y;
		bullet->angle = _firstAngle - (_bulletCount*_offsetAngle);
		bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getFrameWidth(), bullet->img->getFrameHeight());
		bullet->fire = true;
		bullet->init();
		_vBullet.push_back(bullet);

		_bulletCount++;
	}
	_bulletCount = 0;
	
}

//==================================
// ### BlackholeMissile ###
//==================================
HRESULT BlackholeMissile::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	return S_OK;
}

void BlackholeMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();++_viBullet)
	{
		(*_viBullet)->y -= (*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getFrameWidth(), (*_viBullet)->img->getFrameHeight());
	}
}

void BlackholeMissile::fire(float x, float y)
{
	//최대 발사 갯수를 막는다.
	if (_bulletMax <= _vBullet.size())return;

	//메모리 블록 크기 만큼 
	tagCBullet* bullet= new tagCBullet;
	bullet->type = ObservedType::ROCKET_MISSILE;
	bullet->img = new my::Image;
	bullet->img->init("Resource/Images/Rocket/Missile.BMP", 0.0f, 0.0f, 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet->speed = 4.0f;
	bullet->x = bullet->fireX = x;
	bullet->y = bullet->fireY = y;
	bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getFrameWidth(), bullet->img->getFrameHeight());
	bullet->fire = true;
	bullet->init();

	_vBullet.push_back(bullet);
}

//==================================
// ### tagCBullet ###
//==================================
void tagCBullet::init(void)
{
	RECTOBSERVERMANAGER->registerObserved(this);
}

void tagCBullet::release(void)
{
	RECTOBSERVERMANAGER->removeObserved(this);
}

STObservedData tagCBullet::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &rc;
	temp.typeKey = &type;
	temp.isActive = &fire;
	return temp;
}

void tagCBullet::collideObject()
{
	fire = false;
}

