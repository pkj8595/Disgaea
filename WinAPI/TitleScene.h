#pragma once
#include "GameNode.h"
#include "CWindowUI.h"

#define TITLE_SCENE_SIZE_X		485
#define TITLE_SCENE_SIZE_Y		270

class TitleScene :public GameNode
{
private:
	my::Image*	_titleImg;
	RECT		_titleRc;

	my::Image*	_laharlImg;
	RECT		_laharlRc;
	POINT		_laharlPt;
	bool		_isShowlagarlImg;

	CWindowUI*	_titleUI;

	my::Image*	_fadeImg;
	int			_alpha;
	int			_alphaOffset;
	bool		_isFadeOut;
	bool		_isFadeStart;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void TitleUISetUp();
	void StartFadeInOut(int offset);

	TitleScene() {}
	~TitleScene() {}
};

