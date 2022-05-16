#include "Stdafx.h"
#include "PortraitAnimation.h"

HRESULT PortraitAnimation::init(void)
{
	_portraitImg = IMAGEMANAGER->findImage("BattleFaceS");
	_stayStartTime = 0;
	return S_OK;
}

void PortraitAnimation::release(void)
{

}

void PortraitAnimation::update(void)
{
	if (!_isActive) return;

	_viterPort = _vPortrait.begin();
	for (; _viterPort != _vPortrait.end(); ++_viterPort)
	{
		if (TIMEMANAGER->getWorldTime() < (*_viterPort)->startTime) continue;
	
		if ((*_viterPort)->isUp)
		{
			(*_viterPort)->pt.y -= 20;
			if ((*_viterPort)->pt.y < 0)
			{
				(*_viterPort)->pt.y = 0;
				(*_viterPort)->isUp = false;
				_stayStartTime = TIMEMANAGER->getWorldTime();
			}
		}
		else
		{
			if (TIMEMANAGER->getWorldTime() > _stayStartTime + STAY_TIME)
			{
				(*_viterPort)->pt.x -= 20;
				if ((*_viterPort)->pt.x < -90)
				{
					CAMERA->removeZData((*_viterPort)->zData);
					SAFE_DELETE((*_viterPort)->zData);
					SAFE_DELETE((*_viterPort));
					_vPortrait.erase(_viterPort);
					break;
				}
			}
		}
		(*_viterPort)->rc = RectMake((*_viterPort)->pt.x, (*_viterPort)->pt.y, _portraitImg->getFrameWidth(), _portraitImg->getFrameHeight());
	}

	if (_isActive && _vPortrait.size() <= 0)
	{
		_isActive = false;
	}


}

void PortraitAnimation::render(void)
{
	/*if (!_isActive) return;
	_viterPort = _vPortrait.begin();
	for (; _viterPort != _vPortrait.end(); ++_viterPort)
	{
		_portraitImg->frameRender(getMemDC(), _viterPort->rc.left, _viterPort->rc.top, _viterPort->portraitFrameIndex, 0);
	}*/

}

void PortraitAnimation::StartAnimation(void)
{
	int count = 0;
	_isActive = true;

	_viterPort = _vPortrait.begin();
	for (; _viterPort != _vPortrait.end(); ++_viterPort)
	{
		(*_viterPort)->startTime = TIMEMANAGER->getWorldTime() + (count*OFFSET_TIME);
		count++;
	}
}

void PortraitAnimation::setPortraitAnimation(int portraitIndex)
{
	ZorderData* temp = new ZorderData;
	temp->isUp = true;
	temp->portraitFrameIndex = portraitIndex;
	temp->pt = PointMake(STANDARD_X+(80*(_vPortrait.size())), STANDARD_Y);
	temp->rc = RectMake(temp->pt.x, temp->pt.y, _portraitImg->getFrameWidth(), _portraitImg->getFrameHeight());

	temp->zData = new ZOrderData;
	temp->zData->setRenderData(&temp->rc, nullptr, &_portraitImg, portraitIndex, 0);

	CAMERA->registerZData(ZIndexType::ZIndexType_Portrait, temp->zData);
	_vPortrait.push_back(temp);
}
