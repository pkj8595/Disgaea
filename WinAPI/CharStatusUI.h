#pragma once
#include "GameNode.h"
#include "GameCharacter.h"

class CharStatusUI : public GameNode
{
private:
	enum E_Stat_Kinds
	{
		E_Stat_Lv=0,
		E_Stat_Mv,
		E_Stat_Counter,
		E_Stat_JM,
		E_Stat_HP,
		E_Stat_SP,
		E_Stat_Atk,
		E_Stat_Def,
		E_Stat_Int,
		E_Stat_Speed,
		E_Stat_Hit,
		E_Stat_Res,
		E_Stat_Exp,
		E_Stat_Next,
		E_Stat_Name,
		E_Stat_Title,
		E_Stat_Kinds_End,
	};
	enum E_OutLine_Kinds
	{
		E_OutLine_Left=0,
		E_OutLine_Top,
		E_OutLine_Right,
		E_OutLine_Bottom,
		E_OutLine_LeftTop,
		E_OutLine_RightTop,
		E_OutLine_LeftBottom,
		E_OutLine_RightBottom,
		E_OutLine_Center,
		E_OutLine_Kinds_End
	};
private:
	my::Image*	_lineImg[E_OutLine_Kinds_End];
	my::Image*	_boldLineImg[E_OutLine_Kinds_End];
	my::Image*	_iconImg;
	RECT		_iconRc;

	string		_statStr[E_Stat_Kinds_End-2];
	string		_statNum[E_Stat_Kinds_End];
	RECT		_statRc[E_Stat_Kinds_End];
	
	string		_itemName[E_Equipment_Item::Equipment_End];
	RECT		_itemRc[E_Equipment_Item::Equipment_End];

	RECT		_cententRc;
	RECT		_headerRc;
	int			_x, _y;
	int			_width, _headerHight, _contentHight;
	bool		_isActive;

	int			_iconIndex;

	my::Image*	_backColorImg;
	
public:
	virtual HRESULT init(int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	bool getIsActive() { return _isActive; }
	void setIsActive(bool isActive) { _isActive = isActive; }
	void setGameCharacterInfo(GameCharacter* gameChar);

	CharStatusUI();
	~CharStatusUI();
};

