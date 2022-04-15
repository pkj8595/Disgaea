#include "Stdafx.h"
#include "BattleScene.h"
#include "GameManager.h"

HRESULT BattleScene::init(void)
{
	CAMERA->setIsBattleScene(true);
	CAMERA->setSceneType(Camera::SceneType::BattleScene);
	JsonSetUpIsoMap();

	_backImg = IMAGEMANAGER->findImage("battleBack");
	_backPoint = PointMake(CAMERA->getCameraWidth()*0.5, CAMERA->getCameraHeight()*0.5);
	_backRc = RectMakeCenter(_backPoint.x, _backPoint.y, _backImg->getWidth(), _backImg->getHeight());

	return S_OK;
}

void BattleScene::release(void)
{
	_map->release();
	SAFE_DELETE(_map);
	_turnSystem->release();
	SAFE_DELETE(_turnSystem);
}

void BattleScene::update(void)
{
	_map->update();
	_turnSystem->update();
}

void BattleScene::render(void)
{
	_backImg->render(getMemDC(), _backRc.left, _backRc.top);
	_map->render();

	sort(CAMERA->getVecZData()->begin(), CAMERA->getVecZData()->end(), ZOrderData::zcmp());

	vector<pair<ZIndexType, ZOrderData*>>::iterator ziter = CAMERA->getVecZData()->begin();
	ZOrderData* zData= nullptr;
	for (; ziter != CAMERA->getVecZData()->end(); ++ziter)
	{
		zData = (*ziter).second;
		if (zData->getIsActive())
		{
			switch ((*ziter).first)
			{
			case ZIndexType_BlueUI:
				(*zData->getImage())->render(getMemDC(),
					zData->getRECT()->left - CAMERA->getLeft(),
					zData->getRECT()->top - CAMERA->getTop());
				break;
			case ZIndexType_MapUI:
				(*zData->getImage())->render(getMemDC(),
					zData->getRECT()->left - CAMERA->getLeft(),
					zData->getRECT()->top - CAMERA->getTop());
				break;
			case ZIndexType_Character:
				(*zData->getImage())->aniRender(getMemDC(),
					zData->getRECT()->left - CAMERA->getLeft(),
					zData->getRECT()->top - CAMERA->getTop(),
					(*zData->getAnimation()));
				break;
			case ZIndexType_Damage:
				(*zData->getImage())->alphaFrameRender(getMemDC(), zData->getRECT()->right - zData->getFrameY() - CAMERA->getLeft(), zData->getRECT()->top - CAMERA->getTop(), zData->getFrameX(), 0, zData->getAlpha());
				break;
			case ZIndexType_Portrait:
				(*zData->getImage())->frameRender(getMemDC(), zData->getRECT()->left, zData->getRECT()->top, zData->getFrameX(), zData->getFrameY());
				break;
			default:
				break;
			}
		}

	}
	_turnSystem->render();

}

void BattleScene::JsonSetUpIsoMap()
{
	_map = new IsometricMap;
	Json::Value root = JSONDATAMANAGER->loadJsonFile("Map.json");
	Json::Value::iterator mapIter = root["Map"].begin();
	for (int i = 0; mapIter != root["Map"].end(); ++mapIter, i++)
	{
		if (i == GAMEMANAGER->getStageIndex()) break;
	}

	Json::Value::iterator stageIter = (*mapIter)["stage"].begin();
	for (int i = 0; stageIter != (*mapIter)["stage"].end(); ++stageIter, i++)
	{
		if (i == GAMEMANAGER->getDetailStageIndex()) break;
	}

	Json::Value jData = *stageIter;
	_map->init(jData["sizeX"].asInt(), jData["sizeY"].asInt());

	Json::Value::iterator enemyRoot = jData["Enemy"].begin();
	for (; enemyRoot != jData["Enemy"].end(); enemyRoot++)
	{
		_map->setEnemyCharacter(
			static_cast<E_ENEMY_CHARACTER>((*enemyRoot)["enemyType"].asInt()),
			(*enemyRoot)["Xcoordinate"].asInt(),
			(*enemyRoot)["Ycoordinate"].asInt(),
			(*enemyRoot)["_level"].asInt(),
			(*enemyRoot)["_move"].asInt(),
			(*enemyRoot)["_jump"].asInt(),
			(*enemyRoot)["_maxHp"].asInt(),
			(*enemyRoot)["_hp"].asInt(),
			(*enemyRoot)["_maxSp"].asInt(),
			(*enemyRoot)["_sp"].asInt(),
			(*enemyRoot)["_atk"].asInt(),
			(*enemyRoot)["_def"].asInt(),
			(*enemyRoot)["_mint"].asInt(),
			(*enemyRoot)["_speed"].asInt(),
			(*enemyRoot)["_hit"].asInt(),
			(*enemyRoot)["_res"].asInt(),
			(*enemyRoot)["_exp"].asInt(),
			(*enemyRoot)["_maxExp"].asInt()
		);
	}

	_turnSystem = new TurnSystem;
	_turnSystem->registerMapAddress(_map);
	_turnSystem->init();
	_turnSystem->setInitBattleUI(PointMake(jData["startPointX"].asInt(), jData["startPointY"].asInt()));
}