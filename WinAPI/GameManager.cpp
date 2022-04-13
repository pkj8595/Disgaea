#include "Stdafx.h"
#include "GameManager.h"
#include "Laharl.h"

HRESULT GameManager::init(void)
{
	_itemManager = ItemManager::getSingleton();
	_itemManager->init();

	_stageIndex = 0;
	_DetailStageIndex = 0;


	return S_OK;
}

void GameManager::release(void)
{
	_itemManager->release();
	_itemManager->releaseSingleton();

}
