#pragma once
#include "GameNode.h"
/*
위로 올가갔다가 왼쪽으로 사라진다.
첫번째 두번째는 약간의 간격을 가지고 올라온다. 
애니메이션이 실행할 때는 애니메이션을 막는다.

80
*/

#define	STAY_TIME	0.8f
#define	STANDARD_X	50
#define	STANDARD_Y	CAMERA->getCameraRect().bottom
#define	OFFSET_TIME 0.15f

class ZorderData
{
public:
	RECT rc;
	POINT pt;
	int portraitFrameIndex;
	bool isUp;
	float startTime;
	ZOrderData* zData;

	ZorderData()
	{
		rc = RectMake(0, 0, 0, 0);
		pt = POINT{ 0,0 };
		portraitFrameIndex = 0;
		isUp = false;
		startTime = 0.0f;
	}

};

class PortraitAnimation : public GameNode
{
private:
	vector<ZorderData*> _vPortrait;
	vector<ZorderData*>::iterator _viterPort;
	my::Image* _portraitImg;
	POINT _standardPt;
	float _stayStartTime;
	bool _isActive;
	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setIsActive(bool isActive) { _isActive = isActive; }
	bool getIsActive(void) { return _isActive; }
	
	void StartAnimation(void);

	void setPortraitAnimation(int portraitIndex);

};

