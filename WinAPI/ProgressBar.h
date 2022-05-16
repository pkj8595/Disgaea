#pragma once
#include "GameNode.h"
class ProgressBar : public GameNode
{
private:
	my::Image* _progressBarUp;
	my::Image* _progressBarDown;

	RECT	_rc;
	int		_x, _y;

	float	_width;
	bool	_alignLeft;
	bool	_newInit;

	ZOrderData*	_zUpData;
	ZOrderData*	_zDownData;
	bool		_useZdata;

public:
	HRESULT init(int x, int y, int width,int height, bool isGreen);
	HRESULT init(const char* barUpimg,const char* barDownimg, int x, int y, int width, int height,bool isTrans, bool alignLeft);
	void release(void);
	void update(void);
	void render(void);

	void setGauge(float currentScore, float MaxScore);
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	void setPoint(POINT position) { _x = (int)position.x; _y = (int)position.y; }

	void setZData(void);
	void registerZData(void);
	void removeZData(void);

	ProgressBar():_zUpData(nullptr),
					_zDownData(nullptr),
					_progressBarUp(nullptr),
					_progressBarDown(nullptr)
	{
	}
	virtual ~ProgressBar() {}
};

