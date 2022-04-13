#pragma once
#include "GameNode.h"

enum class EWindow_Align
{
	WINDOW_CENTER,
	WINDOW_LEFTTOP
};

enum EWindow_ValueState
{
	WINDOW_DEFAULT,
	WINDOW_NOT_SELECTABLE,
};

class CWindowUIValue : public GameNode
{
private:
	my::Image* _img;
	EWindow_ValueState _windowState;
	EWindow_Align _align;
	RECT _rc;
	string _valueStr;
	CALLBACKFUNCTION _func;
	COLORREF _color;
	int _fontSize;
	int _height;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(string valueName, int x, int y,int width, int height, int fontSize, EWindow_Align align, CALLBACKFUNCTION function);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void excute(void);
	virtual void setCallbackFunction(CALLBACKFUNCTION function) { _func = function; }
	virtual int getHeight() { return _height; }

	virtual void setWindowState(EWindow_ValueState state);
	virtual EWindow_ValueState getWindowState() { return _windowState; }

	virtual RECT getRect() { return _rc; }

	CWindowUIValue();
	~CWindowUIValue();
};


