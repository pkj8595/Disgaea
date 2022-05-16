#include "Stdafx.h"
#include "VictoryUI.h"

VictoryUI::VictoryUI() : _goldWindowUI(nullptr)
{
}

VictoryUI::~VictoryUI()
{
}

HRESULT VictoryUI::init(void)
{
	_goldWindowUI = new CWindowUI;
	_goldWindowUI->init(CAMERA->getCameraCenterX()-75, 120, 150, EWindow_Align::WINDOW_LEFTTOP, false);
	_goldWindowUI->setIsActive(true);

	_clearImg = IMAGEMANAGER->findImage("GameState");
	_brownBackImg = IMAGEMANAGER->findImage("brownBack");
	_isActive = false;
	_isWin = false;
	_brownBackAlpha = 0;
	_brownRect = RectMakeCenter(CAMERA->getCameraCenterX(), CAMERA->getCameraCenterY(), _brownBackImg->getWidth(), _brownBackImg->getHeight());
	
	return S_OK;
}

void VictoryUI::release(void)
{
	_goldWindowUI->release();
	SAFE_DELETE(_goldWindowUI);
}

void VictoryUI::update(void)
{
	if (!_isActive) return;
	_goldWindowUI->update();
	_brownBackAlpha += 2;
	if (_brownBackAlpha > 180)
	{
		_brownBackAlpha = 180;
	}
}

void VictoryUI::render(void)
{
	if (!_isActive) return;
	_brownBackImg->alphaRender(getMemDC(), _brownRect.left, _brownRect.top, _brownBackAlpha);

	if (_brownBackAlpha > 170)
	{
		_goldWindowUI->render();
		if (_isWin)
		{
			_clearImg->frameRender(getMemDC(), CAMERA->getCameraCenterX() - (_clearImg->getFrameWidth()*0.5), 30, 0, 0);
		}
		else
		{
			_clearImg->frameRender(getMemDC(), CAMERA->getCameraCenterX() - (_clearImg->getFrameWidth()*0.5), 30, 0, 8);
		}
	}
	

}

void VictoryUI::setGoldUI(int gold)
{
	char goldstr[32];
	sprintf(goldstr,"HEAL :  %d", gold);
	_goldWindowUI->setWindowValue(goldstr, 22, 22, nullptr);

}

void VictoryUI::setIsActive(bool active, bool isWin)
{
	_isActive = active;
	_isWin = isWin;
	_goldWindowUI->setIsActive(_isWin);
}

