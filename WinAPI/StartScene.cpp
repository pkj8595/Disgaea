#include "Stdafx.h"
#include "StartScene.h"


HRESULT StartScene::init(void)
{
	IMAGEMANAGER->addImage("시작화면", "Resource/Images/Background/backgroundSample3.bmp", WINSIZE_X, WINSIZE_Y);
	//IMAGEMANAGER->addImage("텍스트알파", "Resource/Images/Object/startButton.bmp", 600, 100, true, RGB(255, 0, 255));
	wsprintf(_text, "Start Scene");


	return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) 
	{
		SCENEMANAGER->changeScene("슈팅");
	}
}

void StartScene::render()
{
	IMAGEMANAGER->render("리듬게임배경", getMemDC());

	TextOut(getMemDC(), CENTER_X, CENTER_Y, _text, strlen(_text));

	LPCWSTR script = L"PLEASE PRESS ENTER";
	FONTMANAGER->drawText(getMemDC(), 55, 100, "Kostar", 25, 700, script, wcslen(script), RGB(255, 255, 255));
}
