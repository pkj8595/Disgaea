#pragma once
#include "GameNode.h"
#include "CWindowUIValue.h"


struct ST_CenterLine
{
	my::Image* _centerImg;
	RECT _rc;
};
struct ST_SelectObject
{
	my::Image* _img;
	RECT _rc;
	int _x, _y;
};

class CWindowUI : public GameNode
{
private:
	my::Image* _leftOutLineImg;
	my::Image* _topOutLineImg;
	my::Image* _rightOutLineImg;
	my::Image* _bottomOutLineImg;

	my::Image* _leftTopOutLineImg;
	my::Image* _rightTopOutLineImg;
	my::Image* _leftBottomOutLineImg;
	my::Image* _rightbottomOutLineImg;

	ST_SelectObject _selectObject;

	ST_CenterLine _centerLine;
	vector< CWindowUIValue*> _vWindowValue;
	vector< CWindowUIValue*>::iterator _vWindowIter;
	CWindowUIValue* _currentWindowValue;
	EWindow_Align _textAlign;

	RECT _rc;
	float _x, _y, _width;
	bool _isActive;

public:
	virtual HRESULT init(int x, int y,int width,EWindow_Align align);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void excute(void);

	int getIndex(void);
	
	void setWindowValue(string valueName, int height, int fontSize, CALLBACKFUNCTION function);
	void selectUp(void);
	void selectDown(void);

	void setWindowValueState(int index, EWindow_ValueState state);
	virtual EWindow_ValueState getWindowValueState(int index);


	
	bool getIsActive() { return _isActive; }
	void setIsActive(bool isActive) { _isActive = isActive; }


	CWindowUI();
	~CWindowUI();
};

