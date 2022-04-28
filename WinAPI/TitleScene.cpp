#include "Stdafx.h"
#include "TitleScene.h"
#include "Laharl.h"
#include "Flonne.h"
#include "Etna.h"

HRESULT TitleScene::init(void)
{
	CAMERA->setSceneType(Camera::SceneType::TitleScene);

	_titleImg = IMAGEMANAGER->findImage("TITLEBG");
	_titleRc = RectMakeCenter(TITLE_SCENE_SIZE_X*0.5, TITLE_SCENE_SIZE_Y*0.5, _titleImg->getWidth(), _titleImg->getHeight());

	_laharlImg = IMAGEMANAGER->findImage("TitleScene");
	_laharlPt = PointMake((TITLE_SCENE_SIZE_X - _laharlImg->getWidth())*0.5, 0);
	_laharlRc = RectMake(_laharlPt.x, _laharlPt.y, _laharlImg->getWidth(), _laharlImg->getHeight());
	_isShowlagarlImg = true;

	TitleUISetUp();
	 
	_fadeImg = IMAGEMANAGER->findImage("black");
	_isFadeStart = false;
	_alpha = 0;
	_alphaOffset = 0;



	SOUNDMANAGER->play("Title", 0.8f);
	return S_OK;
}


void TitleScene::release(void)
{
	_titleUI->release();
}

void TitleScene::update(void)
{
	//12초/에 페이드 아웃 인
	if (TIMEMANAGER->getWorldTime() > 10 &&!_isFadeStart)
	{
		StartFadeInOut( 1);
	}

	if (_isFadeStart)
	{
		if(_alpha > 255)
		{
			_alphaOffset = 0;
		}
		 _alpha += _alphaOffset;
	}

	if (_isShowlagarlImg)
	{
		if (_laharlRc.bottom > 270) 
		{
			_laharlPt.y--; 
		}
		else 
		{
			_isShowlagarlImg = false; 
		}

		_laharlRc = RectMake(_laharlPt.x, _laharlPt.y, _laharlImg->getWidth(), _laharlImg->getHeight());

		if(KEYMANAGER->isOnceKeyDown('K'))
		{
			_isFadeStart = true;
			_isShowlagarlImg = false;
		}
	}
	else
	{
		_titleUI->update();
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_titleUI->selectUp();
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_titleUI->selectDown();
		}
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			SOUNDMANAGER->play("OK", 1.0f);
			_titleUI->excute();
		}
	}
	

}

void TitleScene::render(void)
{
	if (_isShowlagarlImg)
	{
		_laharlImg->render(getMemDC(), _laharlRc.left, _laharlRc.top);
	}
	else
	{
		_titleImg->render(getMemDC(), _titleRc.left, _titleRc.top );
		_titleUI->render();
	}

	_fadeImg->alphaRender(getMemDC(), _alpha);
}

void TitleScene::StartFadeInOut(int offset)
{
	_isFadeStart = true;
	_alphaOffset = offset;
}


void TitleScene::TitleUISetUp()
{
	CALLBACKFUNCTION newGame = [this](void)->void
	{
		GAMEMANAGER->playerUnitClear();

		GameCharacter* laharl = new Laharl;
		laharl->init("laharl", 0, 0, 0, 0, E_UnitType::Controllable, 0, 20);
		laharl->setSkill("메테오 임펙트", PointMake(0, 0), 99.0f, 3, 5);
		(*GAMEMANAGER->getAllPlayerUnits()).push_back(laharl);

		GameCharacter* flonne = new Flonne;
		flonne->init("Flonne", 0, 0, 0, 0, E_UnitType::Controllable, 0, 20);
		(*GAMEMANAGER->getAllPlayerUnits()).push_back(flonne);

		GameCharacter* etna = new Etna;
		etna->init("Etna",0,0, 0, 0, E_UnitType::Controllable, 0, 20);
		(*GAMEMANAGER->getAllPlayerUnits()).push_back(etna);

		CAMERA->FadeStart(4);
		CAMERA->FadeChangeScenceName("WorldMapScene");
		SOUNDMANAGER->stop("Title");
	};
	CALLBACKFUNCTION exit = [this](void)->void
	{
		SendMessage(_hWnd, WM_DESTROY, 0, 0);
	};

	_titleUI = new CWindowUI;
	_titleUI->init((TITLE_SCENE_SIZE_X*0.5) - 30, (TITLE_SCENE_SIZE_Y*0.5) + 40, 90, EWindow_Align::WINDOW_LEFTTOP);
	_titleUI->setWindowValue("새 게임", 20, 20, newGame);
	_titleUI->setWindowValue("종료", 20, 20, exit);
	_titleUI->setIsActive(true);
}
