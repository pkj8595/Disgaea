#pragma once
#include "SingletonBase.h"
#include "Animation.h"


class AnimationManager : public SingletonBase<AnimationManager>
{
private:
	typedef map<string, Animation*> mAnimationList;
	typedef map<string, Animation*>::iterator mapAnimationIter;

	mAnimationList _mAnimationList;


public:
	HRESULT init(void);
	void release(void);
	void update(void);

	Animation* findAnimation(string animationKeyName);
	bool deleteAniamation(string strKey);
	bool deleteAll();

	// �ִϸ��̼��� �ִ°� �����ͼ� �Լ� ���� ���

	void addAnimation(string animationKeyName, char* imageKeyName,int fps, bool reverse = false, bool loop = false);

	void addAnimation(string animationKeyName, char* imageKeyName, int start, int end,
		int fps, bool reverse = false, bool loop = false);


	void addAnimationArray(string animationKeyName, char* imageKeyName, int* playArr,int arrLen, int fps, bool loop = false);

	//void addAnimationList(string animationKeyName, char* imageKeyName,multimap<vector<int>, string, list<int>, string> temp,int listLen, int fps, bool loop = false);

	

	void PlayAnimation();
	
	AnimationManager() {}
	~AnimationManager() {}
};

