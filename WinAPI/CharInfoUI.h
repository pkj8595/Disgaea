#pragma once
#include "GameNode.h"
#include "GameCharacter.h"
#include "ProgressBar.h"

class CharInfoUI : public GameNode
{
public:
	enum E_CharInfoImgType
	{
		ECharInfo_Level,
		ECharInfo_HP,
		ECharInfo_SP,
		ECharInfo_MV,
		ECharInfo_JM,
		ECharInfo_Redline,
		ECharInfo_ProgressBar,
		ECharInfo_Back,
		ECharInfo_Icon,
		ECharInfo_End
	};

	enum E_InfoText
	{
		HP,
		SP,
		MOVE,
		JM,
		LEVEL,
		E_InfoText_End	
	};
private:
	my::Image*	_img[ECharInfo_End];
	POINT		_standardPt;
	RECT		_rc[ECharInfo_End];
	int			_iconIndex;

	RECT		_nameRect;
	string		_name;
	RECT		_infoRc[E_InfoText_End];
	int			_infoNum[E_InfoText_End];



	int			_maxHp;
	int			_maxSp;
	int			_move;
	bool		_isActive;

	ProgressBar* _hpProgressBar;
	ProgressBar* _spProgressBar;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void infoCharater(GameCharacter* gameCharacter);
	void setIsActive(bool active) { _isActive = active; }

	CharInfoUI() {}
	~CharInfoUI() {}
};

