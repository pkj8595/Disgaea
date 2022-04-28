#include "Stdafx.h"
#include "SkillMeteoAnimation.h"

SkillMeteoAnimation::SkillMeteoAnimation() : _curImg(nullptr),
_curAnimation(nullptr),
_mainCharacter(nullptr),
_skillMap(nullptr)
{
}

SkillMeteoAnimation::~SkillMeteoAnimation()
{
}
/*
meteoFrame1

meteoFrame2

meteoFrame3

meteoFrame4
*/
HRESULT SkillMeteoAnimation::init(void)
{
	_skillState = E_SkillProcessState::SKILL_START;
	_beforeSkillState = E_SkillProcessState::SKILL_END;

	_curImg = IMAGEMANAGER->findImage("meteoFrame1");
	_curAnimation = ANIMATIONMANAGER->findAnimation("meteoFrame1");
	_skillMap = IMAGEMANAGER->findImage("meteoMap");

	_basePt = PointMake(0, 0);
	_beforePt = PointMake(0, 0);

	_frameRc = RectMakeCenter(_basePt.x, _basePt.y, 480, 380);
	_skillMapRc = RectMakeCenter(_basePt.x, _basePt.y, _skillMap->getWidth(), _skillMap->getHeight());
	 
	_isActive = false;
	_isPlayFrame = false;
	_isFade = false;
	_zoom = PointMake(CAMERA->getCameraWidth(),CAMERA->getCameraHeight());

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
		cout << "SkillState " << static_cast<int>(_skillState) << endl;
		cout << "CAMEARA  L :" << CAMERA->getLeft() << " T :" << CAMERA->getTop() << endl;
		cout << "CAMEARA  R :" << CAMERA->getCameraRect().right << " B :" << CAMERA->getCameraRect().bottom << endl;

		cout << "FrameRC L :" << _frameRc.left << " T :" << _frameRc.top << endl;
		cout << "FrameRC R :" << _frameRc.right << " B :" << _frameRc.bottom << endl;

		_beforeSkillState = _skillState;
		switch (_skillState)
		{
		case E_SkillProcessState::SKILL_START:
			CAMERA->FadeStart(3.0f);
			_isFade = false;

			_frameRc = RectMakeCenter(_basePt.x, _basePt.y, _curImg->getFrameWidth(), _curImg->getFrameHeight());
			_skillMapRc = RectMakeCenter(_basePt.x, _basePt.y+100, _skillMap->getFrameWidth(), _skillMap->getFrameWidth());

			_time = TIMEMANAGER->getWorldTime();
			break;
		case E_SkillProcessState::SKILL_IDLE:

			break;
		case E_SkillProcessState::SKILL_FRAME1:
			//이미지랑 애니메이션 맞춰주고 끝났으면 맵 보여주기 
			_curImg = IMAGEMANAGER->findImage("meteoFrame1");
			_curAnimation = ANIMATIONMANAGER->findAnimation("meteoFrame1");
			_curAnimation->AniStart();
			_isPlayFrame = true;

			changeCharacterRender(false);

			break;
		case E_SkillProcessState::SKILL_JUMP:
			//점프 카메라 조정 
			_isPlayFrame = false;
			changeCharacterRender(true);
			break;
		case E_SkillProcessState::SKILL_FRAME2:
			//프레임 돌리기 
			changeCharacterRender(false);

			_curImg = IMAGEMANAGER->findImage("meteoFrame2");
			_curAnimation = ANIMATIONMANAGER->findAnimation("meteoFrame2");
			_curAnimation->AniStart();

			_isPlayFrame = true;
			break;
		case E_SkillProcessState::SKILL_FRAME3:
			//프레임이 끝나면 몬스터 이동
			changeCharacterRender(true);
			_curImg = IMAGEMANAGER->findImage("meteoFrame3");
			_curAnimation = ANIMATIONMANAGER->findAnimation("meteoFrame3");
			_curAnimation->AniStart();
			_isPlayFrame = true;
			break;
		case E_SkillProcessState::SKILL_FRAME4:
			//끝나면 페이스 인아웃 
			_curImg = IMAGEMANAGER->findImage("meteoFrame4");
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
		//3초후 다음 프레임으로 캐릭터랑 몬스터 render -> x
		if (TIMEMANAGER->getWorldTime() > _time + 4.0f)
		{
			_skillState = E_SkillProcessState::SKILL_FRAME1;
		}
		break;
	case E_SkillProcessState::SKILL_FRAME1:
		//이미지랑 애니메이션 맞춰주고 끝났으면 맵 보여주기 
		if (!_curAnimation->isPlay())
		{
			_skillState = E_SkillProcessState::SKILL_JUMP;
		}
		break;
	case E_SkillProcessState::SKILL_JUMP:
		//점프 카메라 조정 
		_mainCharacter->setSkillMovePoint(PointMake(_mainCharacter->getPoint().x, _mainCharacter->getPoint().y - 250), 50);
		_zoom = PointMake(_zoom.x + 3, _zoom.y + 3);
		//CAMERA->zoomChange(_zoom);
		if (_zoom.x > 900) _skillState = E_SkillProcessState::SKILL_FRAME2;
		break;
	case E_SkillProcessState::SKILL_FRAME2:
		//프레임 돌리기 
		if (!_curAnimation->isPlay())
		{
			_skillState = E_SkillProcessState::SKILL_FRAME3;
		}
		break;
	case E_SkillProcessState::SKILL_FRAME3:
		//프레임이 끝나면 몬스터 이동
		if (!_curAnimation->isPlay())
		{
			_mainCharacter->setPoint(PointMake(_beforePt.x, _beforePt.y - 200));

			list<GameCharacter*>::iterator iter = _lGameChar.begin();
			for (; iter != _lGameChar.end(); ++iter)
			{
				(*iter)->setPoint(PointMake((*iter)->getPoint().x, (*iter)->getPoint().y - 2000));
			}
			_lGameChar.size();
			_skillState = E_SkillProcessState::SKILL_FRAME4;
		}
		break;
	case E_SkillProcessState::SKILL_FRAME4:
		//끝나면 페이스 인아웃 
		if (!_curAnimation->isPlay())
		{
			_skillState = E_SkillProcessState::SKILL_END;
		}
		break;
	case E_SkillProcessState::SKILL_END:
		//페이드 인 아웃
		if (TIMEMANAGER->getWorldTime() > _endtime + 5.0f)
		{
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
					//아웃이 됐으면 캐릭터 이동 //맵 렌더
					_mainCharacter->setPoint(_basePt);

					list<GameCharacter*>::iterator iter = _lGameChar.begin();
					for (; iter != _lGameChar.end(); ++iter)
					{
						(*iter)->setPoint(PointMake((*iter)->getPoint().x, (*iter)->getPoint().y+2000));
					}
					CAMERA->setCameraPoint(&_basePt);
					CAMERA->zoomChange({460,250});
					_skillState = E_SkillProcessState::SKILL_IDLE;
				}
				break;
			case E_SkillProcessState::SKILL_END: 
				{
					CAMERA->setCameraPoint(&_beforePt);

					_mainCharacter->setSkillMovePoint(_beforePt,30);

				}
				break;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		cout << "SkillState " << static_cast<int>(_skillState) << endl;
		cout << "CAMEARA  L :" << CAMERA->getLeft() << " T :" << CAMERA->getTop() << endl;
		cout << "CAMEARA  R :" << CAMERA->getCameraRect().right << " B :" << CAMERA->getCameraRect().bottom << endl;

		cout << "FrameRC L :" << _frameRc.left << " T :" << _frameRc.top << endl;
		cout << "FrameRC R :" << _frameRc.right << " B :" << _frameRc.bottom << endl;
		
	}
	
	
}

void SkillMeteoAnimation::changeCharacterRender(bool isRender)
{
	_mainCharacter->setIsRender(isRender);

	list<GameCharacter*>::iterator iter = _lGameChar.begin();
	for (; iter != _lGameChar.end(); ++iter)
	{
		(*iter)->setIsRender(isRender);
	}
}

void SkillMeteoAnimation::render(void)
{
	if (!_isActive) return;

	if (_isPlayFrame) 
	{
		//if(_curImg != nullptr && _curAnimation != nullptr)
		_curImg->aniRender(getMemDC(), _frameRc.left - CAMERA->getLeft(), _frameRc.top - CAMERA->getTop(), _curAnimation);
	}
	else _skillMap->render(getMemDC(), _skillMapRc.left - CAMERA->getLeft(), _skillMapRc.top - CAMERA->getTop());
}

void SkillMeteoAnimation::StartAnimation(GameCharacter* mainChar, list<GameCharacter*> beAttackCharList)
{
	cout << beAttackCharList.size() << endl;
	_skillState = E_SkillProcessState::SKILL_START;
	_beforeSkillState = E_SkillProcessState::SKILL_END;
	_lGameChar = beAttackCharList;
	_mainCharacter = mainChar;
	_beforePt = mainChar->getPoint();
	_isActive = true;

	_basePt = PointMake(_mainCharacter->getPoint().x, _mainCharacter->getPoint().y + 2000);
	_frameRc = RectMakeCenter(_basePt.x, _basePt.y, 480, 380);
	_skillMapRc = RectMakeCenter(_basePt.x, _basePt.y, 480, 380);
}


