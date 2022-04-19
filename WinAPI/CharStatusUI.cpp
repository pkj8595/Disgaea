#include "Stdafx.h"
#include "CharStatusUI.h"


CharStatusUI::CharStatusUI() :_iconImg(nullptr),
							_lineImg{ nullptr },
							_boldLineImg{nullptr},
							_statStr{""},
							_statNum{""},
							_itemName{""}
{
}

CharStatusUI::~CharStatusUI()
{
}

HRESULT CharStatusUI::init(int x, int y)
{
	_x = x; 
	_y = y;
	_isActive = false;
	_width = 120;
	_headerHight = 17;
	_contentHight = 154;
	_headerRc = RectMake(_x, _y, _width, _headerHight);
	_cententRc = RectMake(_x, _headerRc.bottom, _width, _contentHight);
	_iconIndex = 0;

	_lineImg[E_OutLine_Left] = new my::Image;
	_lineImg[E_OutLine_Top] = new my::Image;
	_lineImg[E_OutLine_Right] = new my::Image;
	_lineImg[E_OutLine_Bottom] = new my::Image;

	_boldLineImg[E_OutLine_Left] = new my::Image;
	_boldLineImg[E_OutLine_Top] = new my::Image;
	_boldLineImg[E_OutLine_Right] = new my::Image;
	_boldLineImg[E_OutLine_Bottom] = new my::Image;

	_boldLineImg[E_OutLine_Center] = new my::Image;
	_lineImg[E_OutLine_Center] = new my::Image;

	_backColorImg = new my::Image;
	_backColorImg->init("Resource/Images/Disgaea/UI/WBG03.bmp",_width, 7,false);

	_lineImg[E_OutLine_Left]->init("Resource/Images/Disgaea/UI/window/left.bmp", 3, _contentHight, false);
	_lineImg[E_OutLine_Top]->init("Resource/Images/Disgaea/UI/window/top.bmp", _width, 3, false);
	_lineImg[E_OutLine_Right]->init("Resource/Images/Disgaea/UI/window/right.bmp", 3, _contentHight, false);
	_lineImg[E_OutLine_Bottom]->init("Resource/Images/Disgaea/UI/window/bottom.bmp", _width, 3, false);

	_lineImg[E_OutLine_LeftTop] = IMAGEMANAGER->findImage("selectWindow_outline_LT");
	_lineImg[E_OutLine_RightTop] = IMAGEMANAGER->findImage("selectWindow_outline_RT");
	_lineImg[E_OutLine_LeftBottom] = IMAGEMANAGER->findImage("selectWindow_outline_LB");
	_lineImg[E_OutLine_RightBottom] = IMAGEMANAGER->findImage("selectWindow_outline_RB");

	_boldLineImg[E_OutLine_Left]->init("Resource/Images/Disgaea/UI/window/WAKU02_01_04.bmp", 7, _headerHight, false);
	_boldLineImg[E_OutLine_Top]->init("Resource/Images/Disgaea/UI/window/WAKU02_01_02.bmp", _width, 7, false);
	_boldLineImg[E_OutLine_Right]->init("Resource/Images/Disgaea/UI/window/WAKU02_01_06.bmp", 7, _headerHight, false);
	_boldLineImg[E_OutLine_Bottom]->init("Resource/Images/Disgaea/UI/window/WAKU02_01_08.bmp", _width, 7, false);

	_boldLineImg[E_OutLine_LeftTop] = IMAGEMANAGER->findImage("bold_outline_LT");
	_boldLineImg[E_OutLine_RightTop] = IMAGEMANAGER->findImage("bold_outline_RT");
	_boldLineImg[E_OutLine_LeftBottom] = IMAGEMANAGER->findImage("bold_outline_LB");
	_boldLineImg[E_OutLine_RightBottom] = IMAGEMANAGER->findImage("bold_outline_RB");

	_boldLineImg[E_OutLine_Center]->init("Resource/Images/Disgaea/UI/WBG02.bmp", _width, _headerHight);
	_lineImg[E_OutLine_Center]->init("Resource/Images/Disgaea/UI/WBG01.bmp", _width, _contentHight);

	_iconImg = IMAGEMANAGER->findImage("CharacterIcon");
	_iconRc = RectMake(_x + 5, _y + _headerHight + 5, _iconImg->getWidth(), _iconImg->getHeight());

	_statStr[E_Stat_Lv] = "Lv";
	_statStr[E_Stat_Mv] = "Mv";
	_statStr[E_Stat_Counter] = "Counter";
	_statStr[E_Stat_JM] = "Jm";
	_statStr[E_Stat_HP] = "Hp";
	_statStr[E_Stat_SP] = "Sp";
	_statStr[E_Stat_Atk] = "Atk";
	_statStr[E_Stat_Def] = "Def";
	_statStr[E_Stat_Int] = "Int";
	_statStr[E_Stat_Speed] = "Spd";
	_statStr[E_Stat_Hit] = "Hit";
	_statStr[E_Stat_Res] = "Res";
	_statStr[E_Stat_Exp] = "Exp";
	_statStr[E_Stat_Next] = "Next";

	_statRc[E_Stat_Name]	=RectMake(_x+8,_y+3,50,17);
	_statRc[E_Stat_Title]	=RectMake(_x+46,_y+22, 70, 13);
	_statRc[E_Stat_Lv]		=RectMake(_x+46,_y+37,69,9);
	_statRc[E_Stat_Counter]	=RectMake(_x+46,_y+45,69,9);
	_statRc[E_Stat_Mv]		=RectMake(_x+46,_y+53,34,9);
	_statRc[E_Stat_JM]		=RectMake(_x+82,_y+53,33,9);
	_statRc[E_Stat_HP]		=RectMake(_x+5,_y+62,110,7);
	_statRc[E_Stat_SP]		=RectMake(_x+5,_y+69,110,7);
	_statRc[E_Stat_Atk]		=RectMake(_x+5,_y+76,52,7);
	_statRc[E_Stat_Int]		=RectMake(_x+60,_y+76,55,7);
	_statRc[E_Stat_Def]		=RectMake(_x+5,_y+83,52,7);
	_statRc[E_Stat_Speed]	=RectMake(_x+60,_y+83,55,7);
	_statRc[E_Stat_Hit]		=RectMake(_x+5,_y+90,52,7);
	_statRc[E_Stat_Res]		=RectMake(_x+60,_y+90,55,7);
	_statRc[E_Stat_Exp]		=RectMake(_x+5,_y+97,110,7);
	_statRc[E_Stat_Next]	=RectMake(_x+5,_y+104,110,7);

	_itemRc[E_Equipment_Item::Equipment_Weapon] = RectMake(_x + 5, _y + 111, 110, 14);
	_itemRc[E_Equipment_Item::Equipment_Slot1] = RectMake(_x + 5, _y + 125, 110, 14);
	_itemRc[E_Equipment_Item::Equipment_Slot2] = RectMake(_x + 5, _y + 139, 110, 14);
	_itemRc[E_Equipment_Item::Equipment_Slot3] = RectMake(_x + 5, _y + 153, 110, 14);

	

	return S_OK;
}

void CharStatusUI::release(void)
{
	_lineImg[E_OutLine_Left]->release();
	_lineImg[E_OutLine_Top]->release();
	_lineImg[E_OutLine_Right]->release();
	_lineImg[E_OutLine_Bottom]->release();
	_lineImg[E_OutLine_Center]->release();
	_boldLineImg[E_OutLine_Left]->release();
	_boldLineImg[E_OutLine_Top]->release();
	_boldLineImg[E_OutLine_Right]->release();
	_boldLineImg[E_OutLine_Bottom]->release();
	_boldLineImg[E_OutLine_Center]->release();
	_backColorImg->release();

	SAFE_DELETE(_lineImg[E_OutLine_Left]);
	SAFE_DELETE(_lineImg[E_OutLine_Top]);
	SAFE_DELETE(_lineImg[E_OutLine_Right]);
	SAFE_DELETE(_lineImg[E_OutLine_Bottom]);
	SAFE_DELETE(_lineImg[E_OutLine_Center]);
	SAFE_DELETE(_boldLineImg[E_OutLine_Left]);
	SAFE_DELETE(_boldLineImg[E_OutLine_Top]);
	SAFE_DELETE(_boldLineImg[E_OutLine_Right]);
	SAFE_DELETE(_boldLineImg[E_OutLine_Bottom]);
	SAFE_DELETE(_boldLineImg[E_OutLine_Center]);
	SAFE_DELETE(_backColorImg);

}

void CharStatusUI::update(void)
{
	if (!_isActive) return;
}

void CharStatusUI::render(void)
{
	if (!_isActive) return;
	_boldLineImg[E_OutLine_Center]->render(getMemDC(), _headerRc.left, _headerRc.top);
	_lineImg[E_OutLine_Center]->render(getMemDC(), _cententRc.left, _cententRc.top);

	_backColorImg->render(getMemDC(), _x, _statRc[E_Stat_HP].top);
	_backColorImg->render(getMemDC(), _x, _statRc[E_Stat_Atk].top);
	_backColorImg->render(getMemDC(), _x, _statRc[E_Stat_Hit].top);
	_backColorImg->render(getMemDC(), _x, _statRc[E_Stat_Next].top);

	_boldLineImg[E_OutLine_Left]->render(getMemDC(), _headerRc.left, _headerRc.top);
	_boldLineImg[E_OutLine_Top]->render(getMemDC(), _headerRc.left, _headerRc.top);
	_boldLineImg[E_OutLine_Right]->render(getMemDC(), _headerRc.right - 7, _headerRc.top);
	_boldLineImg[E_OutLine_Bottom]->render(getMemDC(), _headerRc.left, _headerRc.bottom - 7);
	_boldLineImg[E_OutLine_LeftTop]->render(getMemDC(), _headerRc.left, _headerRc.top);
	_boldLineImg[E_OutLine_RightTop]->render(getMemDC(), _headerRc.right - 7, _headerRc.top);
	_boldLineImg[E_OutLine_LeftBottom]->render(getMemDC(), _headerRc.left, _headerRc.bottom - 7);
	_boldLineImg[E_OutLine_RightBottom]->render(getMemDC(), _headerRc.right - 7, _headerRc.bottom - 7);

	_lineImg[E_OutLine_Left]->render(getMemDC(), _cententRc.left, _cententRc.top);
	_lineImg[E_OutLine_Top]->render(getMemDC(), _cententRc.left, _cententRc.top);
	_lineImg[E_OutLine_Right]->render(getMemDC(), _cententRc.right - 3, _cententRc.top);
	_lineImg[E_OutLine_Bottom]->render(getMemDC(), _cententRc.left, _cententRc.bottom - 3);

	_lineImg[E_OutLine_LeftTop]->render(getMemDC(), _cententRc.left, _cententRc.top);
	_lineImg[E_OutLine_RightTop]->render(getMemDC(), _cententRc.right - 3, _cententRc.top);
	_lineImg[E_OutLine_LeftBottom]->render(getMemDC(), _cententRc.left, _cententRc.bottom - 3);
	_lineImg[E_OutLine_RightBottom]->render(getMemDC(), _cententRc.right - 3, _cententRc.bottom - 3);

	
	_iconImg->frameRender(getMemDC(), _iconRc.left, _iconRc.top,_iconIndex%10, _iconIndex / 10);

	FONTMANAGER->drawText(getMemDC(), _statRc[E_Stat_Name], "³ª´®°íµñ Bold", 13, 30, _statNum[E_Stat_Name], RGB(255, 255, 255), true);
	FONTMANAGER->drawText(getMemDC(), _statRc[E_Stat_Title], "³ª´®°íµñ Bold", 13, 30, _statNum[E_Stat_Title], RGB(0, 0, 0), true);

	for (int i = 0; i < E_Stat_Kinds_End-2; i++)
	{
		FONTMANAGER->drawText(getMemDC(), _statRc[i], "³ª´®°íµñ Bold", 8, 30, _statStr[i], RGB(0, 0, 0), true);
	}
	for (int i = 0; i < E_Stat_Kinds_End-2; i++)
	{
		FONTMANAGER->drawText(getMemDC(), _statRc[i], "³ª´®°íµñ Bold", 8, 30, _statNum[i], RGB(0, 0, 0), false);
	}

	for (int i = 0; i < E_Equipment_Item::Equipment_End; i++)
	{
		if (_itemName[i] == "ºó Ä­")
		{
			FONTMANAGER->drawTextRectCenter(getMemDC(), _itemRc[i], "³ª´®°íµñ Bold", 13, 30, _itemName[i], RGB(70, 70, 70));
		}
		else
		{
			FONTMANAGER->drawTextRectCenter(getMemDC(), _itemRc[i], "³ª´®°íµñ Bold", 13, 30, _itemName[i], RGB(0, 0, 0));
		}
	}
	
}

void CharStatusUI::setGameCharacterInfo(GameCharacter* gameChar)
{
	_statNum[E_Stat_Name]	=  gameChar->getName();
	_statNum[E_Stat_Title]	= gameChar->getTitle();
	_statNum[E_Stat_Lv]		= to_string(gameChar->getCharicterAllStats()->_level);
	_statNum[E_Stat_Mv]		= to_string(gameChar->getCharicterAllStats()->_move);
	_statNum[E_Stat_Counter] = "0";
	_statNum[E_Stat_JM]		= to_string(gameChar->getCharicterAllStats()->_jump);
	_statNum[E_Stat_Atk]	= to_string(gameChar->getCharicterAllStats()->_atk);
	_statNum[E_Stat_Def]	= to_string(gameChar->getCharicterAllStats()->_def);
	_statNum[E_Stat_Int]	= to_string(gameChar->getCharicterAllStats()->_int);
	_statNum[E_Stat_Speed]	= to_string(gameChar->getCharicterAllStats()->_speed);
	_statNum[E_Stat_Hit]	= to_string(gameChar->getCharicterAllStats()->_hit);
	_statNum[E_Stat_Res]	= to_string(gameChar->getCharicterAllStats()->_res);
	_statNum[E_Stat_Exp]	= to_string(gameChar->getCharicterAllStats()->_exp);

	_statNum[E_Stat_HP]		= to_string(gameChar->getCharicterAllStats()->_maxHp) + "/";
	_statNum[E_Stat_HP].append(to_string( gameChar->getCharicterAllStats()->_hp));

	_statNum[E_Stat_SP]		= to_string(gameChar->getCharicterAllStats()->_maxSp) + "/";
	_statNum[E_Stat_SP].append(to_string(gameChar->getCharicterAllStats()->_sp));
	_statNum[E_Stat_Next] = to_string(gameChar->getCharicterAllStats()->_maxExp - gameChar->getCharicterAllStats()->_exp);
	_iconIndex = gameChar->getIconIndex();

	_itemName[E_Equipment_Item::Equipment_Weapon] = gameChar->getEquipmentItem(E_Equipment_Item::Equipment_Weapon)->_name;
	_itemName[E_Equipment_Item::Equipment_Slot1] = gameChar->getEquipmentItem(E_Equipment_Item::Equipment_Slot1)->_name;
	_itemName[E_Equipment_Item::Equipment_Slot2] = gameChar->getEquipmentItem(E_Equipment_Item::Equipment_Slot2)->_name;
	_itemName[E_Equipment_Item::Equipment_Slot3] = gameChar->getEquipmentItem(E_Equipment_Item::Equipment_Slot3)->_name;
}
