#include "Stdafx.h" 
#include "MainGame.h"
#include "GameManager.h"
#include "BattleScene.h"
#include "TitleScene.h"
#include "DataSetUp.h"
#include "WorldMapScene.h"


HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	GameManager::getSingleton()->init();

	_dataSetup = new DataSetUp;
	_dataSetup->init();

	SCENEMANAGER->addScene("TitleScene", new TitleScene);
	SCENEMANAGER->addScene("BattleScene", new BattleScene);
	SCENEMANAGER->addScene("WorldMapScene", new WorldMapScene);

	SCENEMANAGER->changeScene("TitleScene");

	_fadeImg = IMAGEMANAGER->findImage("black");

	return S_OK;
}

void MainGame::release(void)
{
	_dataSetup->release();
	SAFE_DELETE(_dataSetup);

	GameManager::getSingleton()->release();
	GameManager::getSingleton()->releaseSingleton();

	GameNode::release();
}

void MainGame::update(void)
{
	SCENEMANAGER->update();
	ANIMATIONMANAGER->update();
	CAMERA->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	SCENEMANAGER->render();

	if (CAMERA->getIsFadeStart())
	{
		_fadeImg->alphaRender(getMemDC(), CAMERA->getAlpha());
	}
	TIMEMANAGER->render(getMemDC());

	this->getBackBuffer()->render(getHDC());
}
