#pragma once
#include "GameNode.h"

//보이드 포인터 필요 -> 버튼은 기본적으로 3가지 상태 
//2개 down up , 호버 ,
//렌더링 눌었을때, 호버, 

enum class CBUTTONSTATE_ALIGN
{
	BUTTON_LEFTTOP,
	BUTTON_CENTER
};
//버튼이 많아질때 private으로 쓰면 문제가 생긴다.
enum BUTTON_DIRECTION
{
	BUTTON_DIRECTION_NULL,
	BUTTON_DIRECTION_UP,
	BUTTON_DIRECTION_DOWN
};

class CButtonState :public GameNode
{
private:
	BUTTON_DIRECTION _direction;
	my::Image* _image;

	RECT _rc;
	float _x, _y;
	const char* _imageName;
	bool _isbtnDown;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	CALLBACKFUNCTION _callbackFunction;

	virtual HRESULT init(const char* imageName,int x,int y,POINT btnDownFramePoint,POINT btnUpFramePoint, CBUTTONSTATE_ALIGN align);
public:
	virtual HRESULT init(const char* imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint ,CALLBACKFUNCTION cbFunction, CBUTTONSTATE_ALIGN align = CBUTTONSTATE_ALIGN::BUTTON_LEFTTOP);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void excute(void);

	CButtonState();
	~CButtonState();
};

