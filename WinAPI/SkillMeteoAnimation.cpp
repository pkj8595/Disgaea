#include "Stdafx.h"
#include "SkillMeteoAnimation.h"

SkillMeteoAnimation::SkillMeteoAnimation() : _curFrameImg(nullptr),
_curAnimation(nullptr),
_mainCharacter(nullptr),
_skillMap(nullptr)
{
}

SkillMeteoAnimation::~SkillMeteoAnimation()
{
}

HRESULT SkillMeteoAnimation::init(void)
{
	_skillState = E_SkillProcessState::SKILL_START;
	_beforeSkillState = E_SkillProcessState::SKILL_END;

	_curFrameImg = IMAGEMANAGER->findImage("meteoFrame1");
	_curAnimation = ANIMATIONMANAGER->findAnimation("meteoFrame1");
	_skillMap = IMAGEMANAGER->findImage("meteoMap");
	_backImg = IMAGEMANAGER->findImage("black");

	_basePt = PointMake(0, 0);
	_beforePt = PointMake(0, 0);

	_frameRc = RectMakeCenter(_basePt.x, _basePt.y, _curFrameImg->getFrameWidth(), _curFrameImg->getFrameHeight());
	_skillMapRc = RectMakeCenter(_basePt.x, _basePt.y, _skillMap->getWidth(), _skillMap->getHeight());
	 
	_isActive = false;
	_isPlayFrame = false;
	_isFade = false;
	_zoom = PointMake(0,0);
	_isbackRender = false;
	return S_OK;
}

void SkillMeteoAnimation::release(void)
{
}

void SkillMeteoAnimation::update(void)
{
	if (!_isActive) return;

	if (_skillState != _beforeSkillState)
	{
		_beforeSkillState = _skillState;
		switch (_skillState)
		{
		case E_SkillProcessState::SKILL_START:
			CAMERA->FadeStart(3.0f);
			_isFade = false;

			_time = TIMEMANAGER->getWorldTime();
			break;
		case E_SkillProcessState::SKILL_IDLE:

			break;
		case E_SkillProcessState::SKILL_FRAME1:
			//이미지랑 애니메이션 맞춰주고 끝났으면 맵 보여주기 
			_curFrameImg = IMAGEMANAGER->findImage("meteoFrame1");
			_curAnimation = ANIMATIONMANAGER->findAnimation("meteoFrame1");
			_curAnimation->AniStart();
			_isPlayFrame = true;

			changeCharacterRender(false);

			break;
		case E_SkillProcessState::SKILL_JUMP:
			//점프 카메라 조정 
			_isPlayFrame = false;
			changeCharacterRender(true);
			CAMERA->moveToTarget(&_jumpPoint,20);
			break;
		case E_SkillProcessState::SKILL_FRAME2:
			//프레임 돌리기 
			changeCharacterRender(false);
			CAMERA->zoomChange({ 472,264 });
			CAMERA->setCameraPoint(&_basePt);

			_curFrameImg = IMAGEMANAGER->findImage("meteoFrame2");
			_curAnimation = ANIMATIONMANAGER->findAnimation("meteoFrame2");
			_curAnimation->AniStart();

			_isPlayFrame = true;
			break;
		case E_SkillProcessState::SKILL_FRAME3:
			//프레임이 끝나면 몬스터 이동
			changeCharacterRender(true);
			_curFrameImg = IMAGEMANAGER->findImage("meteoFrame3");
			_curAnimation = ANIMATIONMANAGER->findAnimation("meteoFrame3");
			_curAnimation->AniStart();
			_isPlayFrame = true;
			break;
		case E_SkillProcessState::SKILL_FRAME4:
			//끝나면 페이스 인아웃 
			_curFrameImg = IMAGEMANAGER->findImage("meteoFrame4");
			_curAnimation = ANIMATIONMANAGER->findAnimation("meteoFrame4");
			_curAnimation->AniStart();
			_isPlayFrame = true;
			break;
		case E_SkillProcessState::SKILL_END:
			//페이드 인 아웃
			_endtime = TIMEMANAGER->getWorldTime();
			CAMERA->FadeStart(3.0f);
			_isFade = false;
			break;
		default:
			break;
		}
	}


	switch (_skillState)
	{
	case E_SkillProcessState::SKILL_START:
		
		break;
	case E_SkillProcessState::SKILL_IDLE:
		if (TIMEMANAGER->getWorldTime() > _time + 4.0f)
		{
			_skillState = E_SkillProcessState::SKILL_FRAME1;
		}
		break;
	case E_SkillProcessState::SKILL_FRAME1:
		if (!_curAnimation->isPlay())
		{
			_skillState = E_SkillProcessState::SKILL_JUMP;
		}
		break;
	case E_SkillProcessState::SKILL_JUMP:
		_mainCharacter->setSkillMovePoint(PointMake(_mainCharacter->getPoint().x, _mainCharacter->getPoint().y - 250), 100);
		_zoom = PointMake(_zoom.x + 1, _zoom.y + 1);
		
		CAMERA->zoomChange(_zoom);
		if (_zoom.y > 320) _skillState = E_SkillProcessState::SKILL_FRAME2;
		break;
	case E_SkillProcessState::SKILL_FRAME2:
		if (!_curAnimation->isPlay())
		{
			_skillState = E_SkillProcessState::SKILL_FRAME3;
		}
		break;
	case E_SkillProcessState::SKILL_FRAME3:
		if (!_curAnimation->isPlay())
		{
			_mainCharacter->setPoint(PointMake(_beforePt.x, _beforePt.y - 200));

			vector<GameCharacter*>::iterator iter = _lGameChar.begin();
			for (; iter != _lGameChar.end(); ++iter)
			{
				(*iter)->setPoint(PointMake((*iter)->getPoint().x, (*iter)->getPoint().y - 2000));
			}
			_lGameChar.size();
			_skillState = E_SkillProcessState::SKILL_FRAME4;
		}
		break;
	case E_SkillProcessState::SKILL_FRAME4:
		if (!_curAnimation->isPlay())
		{
			_skillState = E_SkillProcessState::SKILL_END;
		}
		break;
	case E_SkillProcessState::SKILL_END:
		if (TIMEMANAGER->getWorldTime() > _endtime + 2.0f)
		{
			_isbackRender = false;
			_isPlayFrame = false;
			_isActive = false;
		}
		break;
	default:
		break;
	}

	if (CAMERA->getIsFadeStart())
	{
		if (!CAMERA->getIsFadeOut() && !_isFade)
		{
			_isFade = true;
			switch (_skillState)
			{
			case E_SkillProcessState::SKILL_START: 
				{
					_mainCharacter->setPoint(_basePt);

					vector<GameCharacter*>::iterator iter = _lGameChar.begin();
					for (; iter != _lGameChar.end(); ++iter)
					{
						(*iter)->setPoint(PointMake((*iter)->getPoint().x, (*iter)->getPoint().y+2000));
					}
					CAMERA->setCameraPoint(&_basePt);
					CAMERA->zoomChange({472,264});
					_zoom = PointMake(472, 264);
					
					_frameRc = RectMakeCenter(_basePt.x, _basePt.y, _curFrameImg->getFrameWidth(), _curFrameImg->getFrameHeight());
					_skillMapRc = RectMakeCenter(_basePt.x, _basePt.y + 50, _skillMap->getFrameWidth(), _skillMap->getFrameHeight());

					_skillState = E_SkillProcessState::SKILL_IDLE;
					_isbackRender = true;
				}
				break;
			case E_SkillProcessState::SKILL_END: 
				{
					CAMERA->setCameraPoint(&_beforePt);
					CAMERA->zoomReset();
					_mainCharacter->setSkillMovePoint(_beforePt,30);

				}
				break;
			}
		}
	}

}

void SkillMeteoAnimation::changeCharacterRender(bool isRender)
{
	_mainCharacter->setIsRender(isRender);

	vector<GameCharacter*>::iterator iter = _lGameChar.begin();
	for (; iter != _lGameChar.end(); ++iter)
	{
		(*iter)->setIsRender(isRender);
	}
}

void SkillMeteoAnimation::render(void)
{
	if (!_isActive) return;
	if(_isbackRender) _backImg->render(getMemDC());

	if (_isPlayFrame) 
	{
		//if(_curImg != nullptr && _curAnimation != nullptr)
		_curFrameImg->aniRender(getMemDC(), _frameRc.left - CAMERA->getLeft(), _frameRc.top - CAMERA->getTop(), _curAnimation);
	}
	else _skillMap->render(getMemDC(), _skillMapRc.left - CAMERA->getLeft(), _skillMapRc.top - CAMERA->getTop());
}

void SkillMeteoAnimation::StartAnimation(GameCharacter* mainChar, vector<GameCharacter*> beAttackCharList)
{
	_skillState = E_SkillProcessState::SKILL_START;
	_beforeSkillState = E_SkillProcessState::SKILL_END;
	_lGameChar = beAttackCharList;
	_mainCharacter = mainChar;
	_beforePt = mainChar->getPoint();
	_isActive = true;

	_basePt = PointMake(_mainCharacter->getPoint().x, _mainCharacter->getPoint().y + 2000);
	_jumpPoint = PointMake(_basePt.x, _basePt.y - 150);
}


