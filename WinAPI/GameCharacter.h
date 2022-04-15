#pragma once
#include "GameNode.h"
#include "Item.h"
#include "ProgressBar.h"

enum class E_UnitType
{
	Controllable=0,
	NPC,
	Monster
};

enum E_Equipment_Item
{
	Equipment_Weapon=0,
	Equipment_Slot1,
	Equipment_Slot2,
	Equipment_Slot3,
	Equipment_End
};

enum E_AniDirection
{
	Ani_Left_Bottom=0,
	Ani_Left_Top,
	Ani_Right_Top,
	Ani_Right_Bottom,
	E_AniDirection_end
};

enum E_AniBehavior
{
	Ani_idle=0,
	Ani_move,
	Ani_attack,
	Ani_be_Attacked,
	Ani_Jump,
	E_Behavior_end
};

enum E_CommandFlag
{
	moveFlag=0,
	behaviorFalg,
	reservationBehaviorFlag,
	LinerMoveFlag,
	E_CommandFlag_end
};
enum class E_BehaviorType
{
	Attack,
	UseItem,
	Skill,
	Sub2CollaboAttackStart,
	Sub2CollaboAttackEnd,
	Main2CollaboAttackStart,
	Main2CollaboAttackEnd,
	NONE
};

class ItemManager;

class GameCharacter : public GameNode
{
protected:
	my::Image*	_characterImg;
	my::Image*	_shadowImg;
	ZOrderData*	_zData;
	E_UnitType	_unitType;
	CharicterStats* _allStats;
	CharicterStats* _stats;
	Item*		_equipItem[Equipment_End];
	string		_name;
	string		_title;

	E_AniDirection	_dir;
	E_AniDirection	_beforeDir;
	E_AniBehavior	_behavior;
	E_AniBehavior	_beforeBehavior;
	E_AniBehavior	_reservationBehavior;
	E_BehaviorType	_behaviorType;

	Animation*	_currentAnimation;
	Animation*	_animation[E_AniDirection_end][E_Behavior_end];

	RECT		_rc;
	POINT		_coordinate;
	POINT		_beforeCoordinate;

	RECT		_shadowRc;

	POINT		_point;
	POINT		_LinerMoveEndPoint;
	POINT		_LinerMoveStartPoint;
	int			_moveCount;
	int			_inputCount;

	int			_imgCorrectionX, _imgCorrectionY;
	int			_attackRange;
	int			_iconIndex;
	int			_battleFaceIndex;

	bitset<static_cast<int>(E_CommandFlag_end)> _bsCommandState;

	bool		_isShaking;
	bool		_isShakingIncrease;
	float		_shakingStartTime;
	float		_shakingTime;
	POINT		_beforeShakingPt;
	int			_shakingOffsetCount;

	//½ºÅ³
	int			_attackIndex;
	bool		_isDie;

	ProgressBar*	_hpBar;

	//CALLBACKFUNCTION _callback;
	//float			 _callbackExcuteTime;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(string fileName,int x, int y,int coorX,int coorY,E_UnitType type,int imgCorrectionX=0, int imgCorrectionY =0);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	
	void unregisterZData(void);
	ZOrderData* getZData() { return _zData; }
	void registerProgressBarZData() { _hpBar->registerZData(); }

	void setReservationAniBehavior(E_AniBehavior behavior);
	bool IsAttackIndex(void);
	bool IsResetMoveIndex(void);
	int getX(){return _point.x;}
	int getY(){return _point.y;}
	void setX(int x){ _point.x = x; }
	void setY(int y){ _point.y = y; }
	void beAttacked(int damage);
	bool getIsDie(void) { return _isDie; }

	int getBattleFaceIndex() { return _battleFaceIndex; }
	int getIconIndex() { return _iconIndex; }

	int getCoorX(){return _coordinate.x;}
	int getCoorY(){return _coordinate.y;}
	void setCoorX(int coorx){ _coordinate.x = coorx; }
	void setCoorY(int coory){ _coordinate.y = coory; }

	int getAttackRange(){return _attackRange;}
	void setAttackRange(int range) { _attackRange = range; }

	POINT getCoorPoint() { return _coordinate; }
	POINT getBeforeCoorPoint() { return _beforeCoordinate; }
	void setBeforeCoorPoint(POINT beforeCoorPoint) { _beforeCoordinate = beforeCoorPoint; }
	POINT getPoint() { return _point; }
	POINT* getPointAddress() { return &_point; }
	string getName() { return _name; }
	void setName(string name) { _name = name; }
	string getTitle() { return _title; }
	void setTitle(string title) { _title = title; }

	void setCoorPoint(POINT coor) { _coordinate = coor; }
	void setPoint(POINT point) { _point = point; }

	Item* setEquipmentItem(E_Equipment_Item itemSlot, Item* item);
	Item* getEquipmentItem(E_Equipment_Item itemSlot);

	//void setCallback(float time, CALLBACKFUNCTION callback);

	E_AniDirection getAniDirecttion() { return _dir; }
	E_AniBehavior getAniBehavior() { return _behavior; }
	E_UnitType getUnitType() { return _unitType; }
	E_BehaviorType getBehaviorType() { return _behaviorType; }
	void setAniDirecttion(E_AniDirection dir){_dir = dir; }
	void setAniBehavior(E_AniBehavior behavior) {_behavior= behavior; }
	void setBehaviorType(E_BehaviorType type) { _behaviorType = type; }
	
	Animation* getCurrentAnimation() { return _currentAnimation; }

	CharicterStats* getCharicterStats() { computeStats(); return _allStats; }
	void computeStats();

	void setSkillMovePoint(POINT targetPoint, int inputCount) 
	{
		_bsCommandState.set(LinerMoveFlag, true);
		_LinerMoveEndPoint = targetPoint;
		_LinerMoveStartPoint = _point;
		_inputCount = inputCount;
	}

	void resetSkillMovePoint(int inputCount)
	{
		_bsCommandState.set(LinerMoveFlag, true);
		_LinerMoveEndPoint = _LinerMoveStartPoint;
		_LinerMoveStartPoint = _point;
		_inputCount = inputCount;
	}

	void setStats(CharicterStats stats) { _stats = &stats; }

	void setCommandState(E_CommandFlag type, bool state)
	{
		_bsCommandState.set(static_cast<int>(type), state);
	}
	bool getCommandState(E_CommandFlag type) { return _bsCommandState[static_cast<int>(type)]; }

	void TurnEnd(void);
	void shakeStart(float time);

	GameCharacter();
	virtual~GameCharacter();
};

