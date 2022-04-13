#pragma once
#include "Stdafx.h"

enum class ObservedType
{
	ROCKET = 0,
	ROCKET_MISSILE,
	MINION,
	MINION_MISSILE
};

typedef struct tagObservedInfo
{
	ObservedType* typeKey;
	RECT* rc;
	bool* isActive;	//적이 충졸했을때 
}STObservedData;

class IRectObserved 
{
public:
	virtual STObservedData getRectUpdate() = 0;
	virtual void collideObject() = 0;

	IRectObserved() {}
	virtual ~IRectObserved() {}
};

/*
가상 함수 테이블 

옵저버는 일 대 다 의존성관계
주제(일)가 있고 >> 옵버 (다)

로켓 많고 
미사일 많고



*/