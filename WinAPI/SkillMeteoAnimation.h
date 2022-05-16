#pragma once
#include "GameNode.h"
#include "GameCharacter.h"

enum class E_SkillProcessState
{
	SKILL_START = 0,
	SKILL_IDLE,
	SKILL_FRAME1,
	SKILL_JUMP,
	SKILL_FRAME2,
	SKILL_FRAME3,
	SKILL_FRAME4,
	SKILL_END
};

class SkillMeteoAnimation : public GameNode
{
private:
	E_SkillProcessState		_skillState;
	E_SkillProcessState		_beforeSkillState;
	vector<GameCharacter*>	_lGameChar;
	GameCharacter*	_mainCharacter;

	my::Image*		_curFrameImg;
	my::Image*		_skillMap;
	my::Image*		_backImg;
	Animation*		_curAnimation;

	RECT			_frameRc;
	RECT			_skillMapRc;
	POINT			_beforePt;
	POINT			_basePt;

	POINT			_zoom;
	POINT			_jumpPoint;

	float			_time;
	float			_endtime;

	bool			_isActive;
	bool			_isPlayFrame;
	bool			_isFade;
	bool			_isbackRender;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void changeCharacterRender(bool isRender);
	void setIsActive(bool isActive) { _isActive = isActive; }
	bool getIsActive(void) { return _isActive; }

	void StartAnimation( GameCharacter* mainChar, vector<GameCharacter*> beAttackCharList);

	SkillMeteoAnimation();
	~SkillMeteoAnimation();
};

