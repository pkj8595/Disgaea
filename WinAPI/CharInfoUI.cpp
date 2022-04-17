#include "Stdafx.h"
#include "CharInfoUI.h"

HRESULT CharInfoUI::init(void)
{
	_img[ECharInfo_Back] = new my::Image;
	_img[ECharInfo_Back]->init("Resource/Images/Disgaea/black.bmp", 140, 60, false);
	_img[ECharInfo_Level] = IMAGEMANAGER->findImage("nLV");
	_img[ECharInfo_HP] = IMAGEMANAGER->findImage("nHP");
	_img[ECharInfo_SP] = IMAGEMANAGER->findImage("nSP");
	_img[ECharInfo_MV] = IMAGEMANAGER->findImage("nMV");
	_img[ECharInfo_JM] = IMAGEMANAGER->findImage("nJM");
	_img[ECharInfo_Redline] = IMAGEMANAGER->findImage("red");
	_img[ECharInfo_ProgressBar] = IMAGEMANAGER->findImage("progress");
	_img[ECharInfo_Icon] = IMAGEMANAGER->findImage("CharacterIcon");

	_standardPt = PointMake(25,165);

	_rc[ECharInfo_Level] = RectMake(_standardPt.x+46, _standardPt.y+19, _img[ECharInfo_Level]->getWidth(), _img[ECharInfo_Level]->getHeight());
	_rc[ECharInfo_HP] = RectMake(_standardPt.x+46, _standardPt.y+29, _img[ECharInfo_HP]->getWidth(), _img[ECharInfo_HP]->getHeight());
	_rc[ECharInfo_SP] = RectMake(_standardPt.x+46, _standardPt.y+39, _img[ECharInfo_SP]->getWidth(), _img[ECharInfo_SP]->getHeight());
	_rc[ECharInfo_MV] = RectMake(_standardPt.x+46, _standardPt.y+49, _img[ECharInfo_MV]->getWidth(), _img[ECharInfo_MV]->getHeight());
	_rc[ECharInfo_JM] = RectMake(_standardPt.x+88, _standardPt.y+49, _img[ECharInfo_JM]->getWidth(), _img[ECharInfo_JM]->getHeight());
	_rc[ECharInfo_Back] = RectMake(_standardPt.x, _standardPt.y, _img[ECharInfo_Back]->getWidth(), _img[ECharInfo_Back]->getHeight());
	_rc[ECharInfo_Redline] = RectMake(_standardPt.x+3, _standardPt.y+16, _img[ECharInfo_Redline]->getWidth(), _img[ECharInfo_Redline]->getHeight());
	_rc[ECharInfo_ProgressBar] = RectMake(_standardPt.x, _standardPt.y, _img[ECharInfo_ProgressBar]->getWidth(), _img[ECharInfo_ProgressBar]->getHeight());
	_rc[ECharInfo_Icon] = RectMake(_standardPt.x+3, _rc[ECharInfo_Back].bottom - 41, _img[ECharInfo_Icon]->getFrameWidth(), _img[ECharInfo_Icon]->getFrameHeight());

	_nameRect = RectMake(_standardPt.x+3, _standardPt.y, 60,30);

	_infoRc[LEVEL] = RectMake(_standardPt.x + 65, _standardPt.y + 19, 40, 10);
	_infoRc[HP] = RectMake(_standardPt.x + 65, _standardPt.y + 29, 40, 10);
	_infoRc[SP] = RectMake(_standardPt.x + 65, _standardPt.y + 39, 40, 10);
	_infoRc[MOVE] = RectMake(_standardPt.x + 65, _standardPt.y + 49, 40, 10);
	_infoRc[JM] = RectMake(_standardPt.x + 105, _standardPt.y + 49, 40, 10);
	for (int i = 0; i < E_InfoText_End; i++)
	{
		_infoNum[i] = 0;
	}
	_iconIndex=0;
	_name="¶óÇÏ¸£";
	_maxHp=0;
	_maxSp=0;
	_move=0;
	_isActive = false;

	_hpProgressBar = new ProgressBar;
	_hpProgressBar->init("Resource/Images/Disgaea/UI/battleUI/progress.bmp","Resource/Images/Disgaea/black.bmp", _infoRc[HP].left, _infoRc[HP].top+3, 60, 3, false, true);

	_spProgressBar = new ProgressBar;
	_spProgressBar->init("Resource/Images/Disgaea/UI/battleUI/progress.bmp","Resource/Images/Disgaea/black.bmp", _infoRc[SP].left, _infoRc[SP].top+3, 60, 3, false, true);
	return S_OK;
}

void CharInfoUI::release(void)
{
	_spProgressBar->release();
	_hpProgressBar->release();

	SAFE_DELETE(_img[ECharInfo_Back]);
	SAFE_DELETE(_spProgressBar);
	SAFE_DELETE(_hpProgressBar);
}

void CharInfoUI::update(void)
{
	if (!_isActive) return;
	_hpProgressBar->update();
	_hpProgressBar->setGauge((float)_infoNum[HP],(float)_maxHp);
	_spProgressBar->update();
	_spProgressBar->setGauge((float)_infoNum[SP], (float)_maxSp);

}

void CharInfoUI::render(void)
{
	if (!_isActive) return;

	_img[ECharInfo_Back]->alphaRender(getMemDC(), _rc[ECharInfo_Back].left, _rc[ECharInfo_Back].top,150);
	_hpProgressBar->render();
	_spProgressBar->render();
	for (int i = 0; i < ECharInfo_End-3; i++)
	{
		_img[i]->render(getMemDC(), _rc[i].left, _rc[i].top);
	}

	_img[ECharInfo_Icon]->frameRender(getMemDC(), _rc[ECharInfo_Icon].left, _rc[ECharInfo_Icon].top, (int)_iconIndex % 10, (int)_iconIndex / 10);
	FONTMANAGER->drawText(getMemDC(), _nameRect, "³ª´®°íµñ Bold", 16, 60, _name, RGB(255, 255, 255), true);
	for (int i = 0; i < E_InfoText_End; i++)
	{
		FONTMANAGER->drawText(getMemDC(), _infoRc[i], "³ª´®°íµñ Bold",10, 60, to_string(_infoNum[i]), RGB(255, 255, 255), true);
	}
	
}

void CharInfoUI::infoCharater(GameCharacter* gameCharacter)
{
	_name = gameCharacter->getName();
	_iconIndex = gameCharacter->getIconIndex();
	_maxHp = gameCharacter->getCharicterAllStats()->_maxHp;
	_maxSp = gameCharacter->getCharicterAllStats()->_maxSp;
	_infoNum[LEVEL] = gameCharacter->getCharicterAllStats()->_level;
	_infoNum[HP] = gameCharacter->getCharicterAllStats()->_hp;
	_infoNum[SP] = gameCharacter->getCharicterAllStats()->_sp;
	_infoNum[MOVE] = gameCharacter->getCharicterAllStats()->_move;
	_infoNum[JM] = gameCharacter->getCharicterAllStats()->_jump;

}
