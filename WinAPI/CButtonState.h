#pragma once
#include "GameNode.h"

//���̵� ������ �ʿ� -> ��ư�� �⺻������ 3���� ���� 
//2�� down up , ȣ�� ,
//������ ��������, ȣ��, 

enum class CBUTTONSTATE_ALIGN
{
	BUTTON_LEFTTOP,
	BUTTON_CENTER
};
//��ư�� �������� private���� ���� ������ �����.
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

