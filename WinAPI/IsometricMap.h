#pragma once
#include "GameNode.h"
#include "IsometricTile.h"
#include "AttackList.h"
#include "GameCharacter.h"
#include "PortraitAnimation.h"
#include "DamageMeter.h"
#include "EffectManager.h"
#include "SkillMeteoAnimation.h"

#define TILE_START_X			450
#define TILE_START_Y			15
#define RECTANGLE_X				60
#define RECTANGLE_Y				30
#define RECT_VECTOR_SIZE_X		13
#define RECT_VECTOR_SIZE_Y		15
#define SPLIT_COUNT				10

enum class TurnSubject
{
	PLAYER,
	ENUMY
};

enum class E_ENEMY_CHARACTER
{
	Vyers,
	Ghost,
};

class IsometricMap : public GameNode
{
private:
	vector< vector<IsometricTile*> > _vTiles;
	IsoTileType _currentType;

	list<GameCharacter*> _characterList;
	GameCharacter* _currentCharacter;

	list<pair<GameCharacter*, CSkill*>> _lSavedSkill;

	//astar move point
	vector<POINT> _vCharMovePoints;
	vector<POINT>::iterator _vCMovePointsIter;
	bool _isCharacterMoving;
	int _moveRangeCount;

	vector<IsometricTile*> _vTileRange;
	queue< pair <int,IsometricTile*>> _qBFSTile;

	BehaviorList* _behaviorList;
	bool _isRunnigBehavior;
	bool _isRunnigBehaviorSetting;
	float _startBeAttackedAnimationTime;
	bool _isRunningBeAttackedAnimation;

	POINT _mapSize;
	POINT _pathFindingStartPoint;
	POINT _pathFindingEndPoint;

	POINT _linearStartPoint;
	POINT _collaborationStartPoint;
	int _onceTileMoveCount;

	bool _isTileAlphaIncrease;
	int _tileAlpha;

	TurnSubject _thisTurn;
	bool _isEnemyMoveEnd;
	bool _isCurrentCharAttacked;

	PortraitAnimation* _portait;
	bool _isPortaitEnd;

	DamageMeter* _damageMeter;
	EffectManager* _effectManager;
	SkillMeteoAnimation* _skillMeteoAni;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(int mapsizeX, int mapsizeY, bool showTileImg, string tileStr);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	void currentCharacterDirCheck(int compareX, int compareY);
	list<GameCharacter*>* getCharacterList() { return &_characterList; }
	void removeCharacter(GameCharacter* character);
	void setPlayerCharacter(GameCharacter* gameChar, int coorX, int coorY);
	void setEnemyCharacter(E_ENEMY_CHARACTER enemy, int coorX, int coorY, int level, int move, int jump, int maxHp, int hp, int maxSp, int sp, int atk, int def, int mint, int speed, int hit, int res, int exp, int maxExp);
	GameCharacter* getNearSameTypeCharacter(GameCharacter* curCharacter);
	void resetTilesAstarData(void);
	void resetTilesAstarDataExceptWall(void);
	bool PointtInTriangle(POINT target, POINT p1, POINT p2, POINT p3);
	stack<POINT> startPathfinding(IsometricTile* start, IsometricTile* target);
	bool OnTriggerPathfinding(void);

	int computeGcost(IsometricTile* curTile, IsometricTile* targetTile);

	POINT* getMapSize() { return &_mapSize; }
	POINT getcoordinateToPoint(int coorx, int coory);
	POINT getcoordinateToPoint(POINT coordinate);

	void setAstarEndPoint(POINT EndPoint);
	void setAstarStartPoint(POINT StartPoint);
	void resetCharacterMove(void);

	bool* getIsCharacterMove() {return  &_isCharacterMoving; }
	bool* getIsRunningBehavior() {return  &_isRunnigBehavior; }
	TurnSubject getTurnSubject() { return _thisTurn; }
	IsometricTile* getTile(POINT coor);
	GameCharacter* selectCharacter(POINT coor);
	GameCharacter* getCurrentCharacter(){return _currentCharacter;}
	GameCharacter* getCharacter(POINT coorPt);

	BehaviorList* getBehaviorList(){return _behaviorList;}
	void setBehaviorList(IsometricTile* excuteUnitTile, IsometricTile* target, E_BehaviorType behavior);
	void setFrontPushBehaviorList(IsometricTile* excuteUnitTile, IsometricTile* target, E_BehaviorType behavior);
	void setBehaviorList(IsometricTile* excuteUnitTile, list<IsometricTile*> targetlist, E_BehaviorType behavior);
	void cancelBehavior(IsometricTile* excuteUnitTile);
	void StartBehavior(void);

	void TurnEnd(TurnSubject subject);

	void enemyNextMoveTurn(void);
	void StartEnemyTrun(void);

	void startComputeTileRange(int range, POINT startTilePoint, bool isMove, bool playerAroundSearch = false);
	void resetTileRange(void);

	bool IsEmptyPlayerCharacter(void);
	bool IsEmptyEnemyCharacter(void);

	GameCharacter* computeNearControlableCharacter(GameCharacter* curCharacter);
	IsometricTile* computeEnemyMoveTargetTile(GameCharacter* curCharacter);
	IsometricTile* computeEnemyAttackRangeInPlayerTile(GameCharacter* currentEnemy);

	void setBehaviorSkill(GameCharacter* Gchar, CSkill* skill);
	

private:
	void CheckEnemyTurnEnd(void);
	void computeTileRange(int range, IsometricTile* startTile , bool isMove, bool playerAroundSearch);
	float sign(POINT p1, POINT p2, POINT p3);
	void correctionTileIndex(int &coorx, int &coory);
	void correctionTileIndex(POINT &coordinate);
	int computeDamage(GameCharacter* subject, GameCharacter* beAttackChar);

public:
	IsometricMap();
	~IsometricMap();
};

