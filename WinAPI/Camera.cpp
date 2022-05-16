#include "Stdafx.h"
#include "Camera.h"

HRESULT Camera::init(void)
{
	_currentCameraSize= PointMake(0, 0);
	_cameraRc = RectMake(0, 0, _currentCameraSize.x, _currentCameraSize.y);
	_moveToTargetStartPt = PointMake(0, 0);
	_moveCameraPt = PointMake(0, 0);

	_isFollowingCameraToTarget = false;
	_moveToTargetEndPt = nullptr;
	_cameraPt = nullptr;
	_isBattleScene = false;
	_inputCount = 10;
	_moveCount = 0;

	_isShaking = false;
	_isShakingIncrease = true;
	_shakingOffsetCount = 0;
	_beforeShakingPt = PointMake(0,0);
	_shakingStartTime = 0.0f;
	_shakingTime = 0.0f;

	_zoomStartPoint = PointMake(0, 0);
	_zoomEndPoint = PointMake(0, 0);
	_zommCount = 0;
	_isZoomChange = true;

	_isFadeStart = false;
	_isFadeOut = true;
	_alpha = 0;
	_alphaOffset = 0;

	_changeSceneName = "";

	return S_OK;
}

void Camera::release(void)
{
	_vZData.clear();
}

void Camera::FadeStart(int alphaOffset)
{
	_alpha = 0;
	_alphaOffset = alphaOffset;
	_isFadeStart = true;
	_isFadeOut = true;
}

void Camera::setSceneType(SceneType scene)
{
	_sceneType = scene;
	switch (_sceneType)
	{
	case Camera::SceneType::TitleScene:
		//SendMessage(_hWnd, WM_COMMAND, 0x0011, NULL);
		_currentCameraSize = _TitleSceneSize;
		break;
	case Camera::SceneType::HomeScene:
		//SendMessage(_hWnd, WM_COMMAND, 0x0011, NULL);
		_currentCameraSize = _HomeSceneSize;
		break;
	case Camera::SceneType::BattleScene:
		_currentCameraSize = _BattleSceneSize;
		break;
	case Camera::SceneType::WorldMapScene:
		_currentCameraSize = _WorldMapSceneSize;
		break;
	default:
		break;
	}
	zoomChange(_currentCameraSize);
	
}

void Camera::update(void)
{
	
	if (_isZoomChange)
	{
		_zommCount++;
		_currentCameraSize = LinearMovePoint(_zoomStartPoint, _zoomEndPoint, ZOOM_SPLIT_COUNT, _zommCount);

		zoomChange(_currentCameraSize);
		if (_zommCount >= ZOOM_SPLIT_COUNT)
		{
			_zoomStartPoint = _zoomEndPoint = PointMake(0, 0);
			_zommCount = 0;
			_isZoomChange = false;
		}
	}

	if (_isFadeStart)
	{
		if (_alpha > 245) _isFadeOut = false;

		if (_isFadeOut) _alpha += _alphaOffset;
		else _alpha -= _alphaOffset;

		if (_changeSceneName != "" &&!_isFadeOut)
		{
			SCENEMANAGER->releaseCurrentScene();
			SCENEMANAGER->changeScene(_changeSceneName);
			_changeSceneName = "";
		}
		if (_alpha <= 10 && !_isFadeOut)
		{
			cout << "fade end" << endl;
			_isFadeStart = false;
			_isFadeOut = true;
			_alpha = 0;
			_alphaOffset = 0;
		}
	}

	if (_isBattleScene)
	{
		if (_isFollowingCameraToTarget)
		{
			_moveCount++;
			_moveCameraPt = LinearMovePoint(_moveToTargetStartPt, *_moveToTargetEndPt, _inputCount, _moveCount);

			_cameraRc = RectMakeCenter(_moveCameraPt.x , _moveCameraPt.y , _currentCameraSize.x, _currentCameraSize.y);

			if (_moveCount >= _inputCount)
			{
				_cameraPt = _moveToTargetEndPt;
				_moveToTargetStartPt =_moveCameraPt = PointMake(0, 0);
				_moveCount = 0;
				_isFollowingCameraToTarget = false;
				_isSettingMovePoint = false;
			}
		}
		else
		{
			if (_isShaking)
			{
				_shakingOffsetCount++;
				if (_shakingOffsetCount > 1)
				{
					_shakingOffsetCount = 0;
					_isShakingIncrease = !_isShakingIncrease;
					if (_isShakingIncrease) _cameraPt->y += 2;
					else _cameraPt->y -= 2;
				}

				if (TIMEMANAGER->getWorldTime() > _shakingStartTime + _shakingTime)
				{
					_isShaking = false;
					_shakingStartTime = 0;
					_shakingTime = 0;
					*_cameraPt = _beforeShakingPt;
				}
			}

			_cameraRc = RectMakeCenter(_cameraPt->x , _cameraPt->y, _currentCameraSize.x, _currentCameraSize.y);
		}
	}
	else
	{
		if (_cameraPt != nullptr)
		{
			_cameraRc = RectMakeCenter(_cameraPt->x, _cameraPt->y, _currentCameraSize.x, _currentCameraSize.y);
		}
		else
		{
			_cameraRc = RectMake(0, 0, _currentCameraSize.x, _currentCameraSize.y);
		}
	
	}
}


void Camera::setCameraPoint(POINT* cameraPt)
{
	_cameraPt = cameraPt;
}

void Camera::setMoveStartPoint(POINT moveStartPoint)
{
	_isSettingMovePoint = true;
	_moveToTargetStartPt = moveStartPoint;
}

void Camera::shakeStart(float time)
{
	_shakingStartTime = TIMEMANAGER->getWorldTime();
	_isShaking = true;
	_isShakingIncrease = true;
	_shakingTime = time;
	_beforeShakingPt = *_cameraPt;
}

void Camera::moveToTarget(POINT* followTargetPt, int inputCount)
{
	_isFollowingCameraToTarget = true;
	if (!_isSettingMovePoint) _moveToTargetStartPt = *_cameraPt;
	_moveToTargetEndPt = followTargetPt;
	_inputCount = inputCount;
}

void Camera::zoomIn(void)
{
	_isZoomChange = true;
	_zoomStartPoint = _currentCameraSize;
	_zoomEndPoint = _zoomInSize;
}

void Camera::zoomReset(void)
{
	_isZoomChange = true;
	_zoomStartPoint = _currentCameraSize;
	_zoomEndPoint = _BattleSceneSize;
}

void Camera::zoomOut(void)
{
	_isZoomChange = true;
	_zoomStartPoint = _currentCameraSize;
	_zoomEndPoint = _zoomOutSize;
}

void Camera::zoomChange(POINT cameraSize)
{
	_currentCameraSize = cameraSize;
	SendMessage(_hWnd, WM_COMMAND, 0x1000, MAKELPARAM(cameraSize.x, cameraSize.y));
}

void Camera::removeZData(ZOrderData* zData)
{
	vector<pair<ZIndexType, ZOrderData*>>::iterator zIter = _vZData.begin();
	for (; zIter != _vZData.end(); ++zIter)
	{
		if (zIter->second == zData)
		{
			_vZData.erase(zIter);
			break;
		}
	}
}

void Camera::registerZData(ZIndexType zIndex,ZOrderData * zData)
{
	_vZData.push_back(make_pair(zIndex, zData));
}

