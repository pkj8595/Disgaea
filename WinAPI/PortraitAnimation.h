#pragma once
#include "GameNode.h"
/*
���� �ð����ٰ� �������� �������.
ù��° �ι�°�� �ణ�� ������ ������ �ö�´�. 
�ִϸ��̼��� ������ ���� �ִϸ��̼��� ���´�.

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

