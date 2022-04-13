#pragma once
#include "IsometricTile.h"
class BehaviorList
{
private:
	typedef list<pair<IsometricTile*, list<IsometricTile*>>>::iterator mAttackListIter;
	typedef pair<IsometricTile*, list<IsometricTile*>> mAttackPair;
	list<pair<IsometricTile*, list<IsometricTile*>>> _behaviorList;

public:
	void init(void);
	void release(void);
	void setBehaviorList(IsometricTile* excute, IsometricTile* target);
	void setFrontPushBehaviorList(IsometricTile* excute, IsometricTile* target);
	void setBehaviorList(IsometricTile* excute, list<IsometricTile*> targetlist);
	pair<IsometricTile*, list<IsometricTile*>> getAndPopFrontBehaviorList();
	bool cancelBehavior(IsometricTile* excute);
	void removeBehavior(IsometricTile* removeObject);
	bool removeSamefirstObject(pair< IsometricTile*, list<IsometricTile*>>& object, IsometricTile* compareObject);
	pair<IsometricTile*, list<IsometricTile*>>* front(void);
	bool empty(void);
	void pop_front(void);
	void clear(void);
	int size(void);
	void confirmSecond(void);
	

	BehaviorList() {}
	~BehaviorList() {}
};

