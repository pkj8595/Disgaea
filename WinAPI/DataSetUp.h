#pragma once
#include "AniData.h"

#define ANI_FPS			6
#define ANI_ATTACK_FPS			8
#define ANI_Dialog		4

class DataSetUp
{
private:
	queue< AniData*> _qAniData;

public:
	void init(void);
	void release(void);
	void ImageClassInit();
	void AnimationClassInit();
	void AnimationJsonDataSetup();
	void SoundInit();

	queue<AniData*>* getAniData() { return &this->_qAniData; }
};

