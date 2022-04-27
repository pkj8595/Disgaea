#include "Stdafx.h"
#include "AttackList.h"

void BehaviorList::init(void)
{
}

void BehaviorList::release(void)
{
	for (mAttackPair attack : _behaviorList)
	{
		attack.second.clear();
	}
	_behaviorList.clear();

}

void BehaviorList::setBehaviorList(IsometricTile* excute, IsometricTile * target)
{
	mAttackListIter iter = _behaviorList.begin();
	for (; iter != _behaviorList.end(); ++iter)
	{
		if (iter->first == excute)
		{
			iter->second.push_back(target);
			_behaviorList.push_back(*iter);
			return;
		}
	}
	
	mAttackPair tempPair;
	tempPair.first = excute;
	tempPair.second.push_back(target);
	_behaviorList.push_back(tempPair);

}

void BehaviorList::setFrontPushBehaviorList(IsometricTile * excute, IsometricTile * target)
{
	mAttackPair tempPair;
	tempPair.first = excute;
	tempPair.second.push_back(target);
	_behaviorList.push_front(tempPair);
}

void BehaviorList::setBehaviorList(IsometricTile* excute, list<IsometricTile*> targetlist)
{
	mAttackListIter iter = _behaviorList.begin();
	for (; iter != _behaviorList.end(); ++iter)
	{
		if (iter->first == excute)
		{
			iter->second = targetlist;
			_behaviorList.push_back(*iter);
			break;
		}
	}
	
	mAttackPair tempPair;
	tempPair.first = excute;
	tempPair.second = targetlist;
	_behaviorList.push_back(tempPair);
}

pair<IsometricTile*, list<IsometricTile*>> BehaviorList::getAndPopFrontBehaviorList()
{
	if (!_behaviorList.empty())
	{
		mAttackPair tempPair = _behaviorList.front();
		_behaviorList.pop_front();
		return tempPair;
	}
	return mAttackPair();
}

bool BehaviorList::cancelBehavior(IsometricTile* excute)
{
	mAttackListIter iter = _behaviorList.begin();
	for (; iter != _behaviorList.end(); ++iter)
	{
		if (iter->first == excute)
		{
			iter->second.clear();
			_behaviorList.erase(iter);
			return true;
			break;
		}
	}
	return false;
}

void BehaviorList::removeBehavior(IsometricTile* removeObject)
{
	mAttackListIter iter = _behaviorList.begin();
	for (; iter != _behaviorList.end(); ++iter)
	{
		if ((*iter).first == removeObject)
		{
			(*iter).second.clear();
		}
	}
	iter = _behaviorList.begin();
	for (; iter != _behaviorList.end(); ++iter)
	{
		list<IsometricTile*>::iterator subIter = (*iter).second.begin();
		for (; subIter != (*iter).second.end();)
		{
			if ((*subIter) == removeObject)
			{
				subIter = (*iter).second.erase(subIter);
			}
			else ++subIter;
		}

	}

}

bool BehaviorList::removeSamefirstObject(pair< IsometricTile*, list<IsometricTile*>>& object, IsometricTile* compareObject)
{
	return object.first == compareObject;
}

bool BehaviorList::empty(void)
{
	return _behaviorList.empty();
}

pair<IsometricTile*, list<IsometricTile*>>* BehaviorList::front(void)
{
	return &_behaviorList.front();
}

void BehaviorList::pop_front(void)
{
	return _behaviorList.pop_front();
}

void BehaviorList::clear(void)
{
	for (mAttackPair attack : _behaviorList)
	{
		attack.second.clear();
	}
	_behaviorList.clear();
}

int BehaviorList::size(void)
{
	return _behaviorList.size();
}

void BehaviorList::confirmSecond(void)
{
	mAttackListIter iter = _behaviorList.begin();
	for (; iter != _behaviorList.end();)
	{
		if ((*iter).second.size() == 0)
		{
			iter = _behaviorList.erase(iter);
		}
		else ++iter;
	}
}
