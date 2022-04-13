#include "Stdafx.h"
#include "WorldMapScene.h"

HRESULT WorldMapScene::init(void)
{
	CAMERA->setSceneType(Camera::SceneType::TitleScene);
	stageSetup();
	changeWorldMapType(E_WorldMapType::HOME);
	_currentUI = (*_stageList.begin()).second;
	_backRc = RectMakeCenter(CAMERA->getCameraCenterX(),CAMERA->getCameraCenterY(), _backImg->getWidth(), _backImg->getHeight());

	_isExcuteChangeScene = true;
	_stageMainNum = 0;
	_stageSubNum = 0;

	return S_OK;
}


void WorldMapScene::release(void)
{
	while (!_stageList.empty())
	{
		SAFE_DELETE(_stageList.back().second);
		_stageList.pop_back();
	}
}

void WorldMapScene::update(void)
{
	_currentUI->update();
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_currentUI->selectUp();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_currentUI->selectDown();
	}
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		switch (_mapType)
		{
		case E_WorldMapType::HOME:
			_mapType = static_cast<E_WorldMapType>(_currentUI->getIndex()+1);
			_isExcuteChangeScene = false;
			CAMERA->FadeStart(7);
			break;
		case E_WorldMapType::STAGE1:
		case E_WorldMapType::STAGE2:
			CAMERA->FadeStart(7);
			CAMERA->FadeChangeScenceName("BattleScene");
			GAMEMANAGER->setStageIndex(static_cast<int>(_mapType) - 1);
			GAMEMANAGER->setDetailStageIndex(_currentUI->getIndex());
			break;
		default:
			break;
		}
		
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		switch (_mapType)
		{
		case E_WorldMapType::HOME:
			//todo 마왕성씬으로 되돌아가기?
			break;
		case E_WorldMapType::STAGE1:
		case E_WorldMapType::STAGE2:
			_mapType = E_WorldMapType::HOME;
			_isExcuteChangeScene = false;
			CAMERA->FadeStart(7);
			break;
		default:
			break;
		}
	}

	if (CAMERA->getIsFadeStart())
	{
		if (!CAMERA->getIsFadeOut() && !_isExcuteChangeScene)
		{
			changeWorldMapType(_mapType);
			//todo 페이드 아웃을 실행할때 false setting
			_isExcuteChangeScene = true;
		}
	}

}

void WorldMapScene::render(void)
{
	_backImg->render(getMemDC(), _backRc.left, _backRc.top);
	_currentUI->render();
}

void WorldMapScene::changeWorldMapType(E_WorldMapType mapType)
{
	_mapType = mapType;
	vector<pair< E_WorldMapType, CWindowUI*>>::iterator iter = _stageList.begin();
	for (; iter != _stageList.end(); ++iter)
	{
		if (iter->first == _mapType)
		{
			iter->second->setIsActive(true);
			_currentUI = iter->second;
		}
		else
		{
			iter->second->setIsActive(false);
		}
	}

	switch (_mapType)
	{
	case E_WorldMapType::HOME:
		_backImg = IMAGEMANAGER->findImage("home");
		break;
	case E_WorldMapType::STAGE1:
		_backImg = IMAGEMANAGER->findImage("stage1");
		break;
	case E_WorldMapType::STAGE2:
		_backImg = IMAGEMANAGER->findImage("stage2");
		break;
	default:
		break;
	}

}

void WorldMapScene::stageSetup()
{
	pair< E_WorldMapType, CWindowUI*> home;
	home.first = E_WorldMapType::HOME;
	home.second = new CWindowUI;
	home.second->init(30, 200, 100, EWindow_Align::WINDOW_LEFTTOP);
	home.second->setIsActive(false);
	home.second->setWindowValue("연습용 맵", 20, 20, nullptr);
	home.second->setWindowValue("바이어스 성", 20, 20, nullptr);
	_stageList.push_back(home);

	pair< E_WorldMapType, CWindowUI*> stage1;
	stage1.first = E_WorldMapType::STAGE1;
	stage1.second = new CWindowUI;
	stage1.second->init(30, 200, 100, EWindow_Align::WINDOW_LEFTTOP);
	stage1.second->setIsActive(false);
	stage1.second->setWindowValue("연습용 맵", 20, 20, nullptr);
	stage1.second->setWindowValue("연습용 맵2", 20, 20, nullptr);
	_stageList.push_back(stage1);

	pair< E_WorldMapType, CWindowUI*> stage2;
	stage2.first = E_WorldMapType::STAGE2;
	stage2.second = new CWindowUI;
	stage2.second->init(30, 200, 100, EWindow_Align::WINDOW_LEFTTOP);
	stage2.second->setIsActive(false);
	stage2.second->setWindowValue("미의 관문", 20, 20, nullptr);
	stage2.second->setWindowValue("포옹의 방", 20, 20, nullptr);
	_stageList.push_back(stage2);

}