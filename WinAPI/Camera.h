#pragma once
#include "SingletonBase.h"

#define ZOOM_SPLIT_COUNT		10
enum ZIndexType 
{
	ZIndexType_MapUI =0,
	ZIndexType_Character,
	ZIndexType_ProgressDownbar,
	ZIndexType_ProgressUpbar,
	ZIndexType_BlueUI,
	ZIndexType_Effect,
	ZIndexType_Damage,
	ZIndexType_Portrait,
};

class ZOrderData
{
private:
	RECT*	_rc;
	Animation** _animation;
	my::Image**	_img;
	int		_frameX;
	int		_frameY;
	float*	_numW;
	bool*	_isActive;
	BYTE*	_alpha;
	CALLBACKFUNCTION _callback;

public:
	Animation** getAnimation() { return _animation; }
	my::Image**	getImage() { return _img; }
	RECT*	getRECT() { return _rc; }
	int		getFrameX() { return _frameX; }
	int		getFrameY() { return _frameY; }
	float*	getNumW() { return _numW; }
	BYTE	getAlpha() { return *_alpha; }
	void	excuteRenderCallback() { _callback(); }
	bool	getIsActive() 
	{
		if (_isActive != nullptr)
		{
			return *_isActive; 
		}
		return true;
	}
	void setRenderCallback(RECT* rc, CALLBACKFUNCTION callback)
	{
		_callback = callback;
		_rc = rc;
	}

	void setRenderData(RECT* rc, Animation** ani, my::Image** img)
	{
		_rc = rc;
		_animation = ani;
		_img = img;
	}
	void setRenderData(RECT* rc, Animation** ani, my::Image** img, bool* isActive)
	{
		_rc = rc;
		_animation = ani;
		_img = img;
		_isActive = isActive;
	}

	void setRenderData(RECT* rc, Animation** ani, my::Image** img, int frameX, int frameY)
	{
		_rc = rc;
		_animation = ani;
		_img = img;
		_frameX = frameX;
		_frameY = frameY;
	}
	void setRenderData(RECT* rc, Animation** ani, my::Image** img, int frameX, int frameY, BYTE* alpha)
	{
		_rc = rc;
		_animation = ani;
		_img = img;
		_frameX = frameX;
		_frameY = frameY;
		_alpha = alpha;
	}
	void setRenderData(RECT* rc,my::Image** img, float* numW)
	{
		_rc = rc;
		_img = img;
		_numW = numW;
	}

	ZOrderData():	_rc(nullptr),
					_animation(nullptr),
					_img(nullptr),
					_frameX(0),
					_frameY(0),
					_isActive(nullptr),
					_alpha(0),
					_numW(nullptr)
	{
	}
	~ZOrderData() {}

	class zcmp
	{
	public:
		bool operator()(pair<ZIndexType, ZOrderData*> a, pair<ZIndexType, ZOrderData*> b)
		{
			if (a.first == b.first)
			{
				return a.second->getRECT()->bottom < b.second->getRECT()->bottom;
			}
			else
			{
				return a.first < b.first;
			}
		}
	};
};


class Camera :public SingletonBase<Camera>
{
public:
	enum class SceneType
	{
		TitleScene = 0,
		HomeScene,
		BattleScene,
		WorldMapScene
	};

private:
	
	vector<pair<ZIndexType,ZOrderData*>> _vZData;

	const POINT	_TitleSceneSize;
	const POINT	_BattleSceneSize;
	const POINT	_HomeSceneSize;
	const POINT	_WorldMapSceneSize;
	const POINT	_zoomInSize;
	const POINT	_zoomOutSize;

	POINT	_nomalPt;

	RECT	_cameraRc;
	POINT*	_cameraPt;
	POINT	_currentCameraSize;

	POINT	_moveCameraPt;
	POINT	_moveToTargetStartPt;
	POINT*	_moveToTargetEndPt;
	bool	_isFollowingCameraToTarget;
	bool	_isBattleScene;
	bool	_isSettingMovePoint;
	int		_moveCount;
	int		_inputCount;

	bool	_isShaking;
	bool	_isShakingIncrease;
	int		_shakingOffsetCount;
	POINT	_beforeShakingPt;
	float	_shakingStartTime;
	float	_shakingTime;

	SceneType _sceneType;

	bool	_isZoomChange;
	POINT	_zoomStartPoint;
	POINT	_zoomEndPoint;
	int		_zommCount;

	BYTE			_alpha;
	int			_alphaOffset;
	bool		_isFadeOut;
	bool		_isFadeStart;
	string		_changeSceneName;

public:
	HRESULT init(void);
	void update(void);
	void release(void);

	bool getIsFadeStart(void) { return _isFadeStart; }
	bool getIsFadeOut(void) { return _isFadeOut; }
	void FadeStart(int alphaOffset);
	void FadeChangeScenceName(string strKey) { _changeSceneName = strKey; }
	BYTE getAlpha(void) { return _alpha; }
	void setSceneType(SceneType scene);

	void setCameraPoint(POINT* cameraPt);
	void setMoveStartPoint(POINT moveStartPoint);
	void shakeStart(float time);
	void moveToTarget(POINT* target ,int inputCount = 10);
	POINT* getCameraPoint(){ return _cameraPt; }
	RECT getCameraRect() { return _cameraRc; }
	LONG getLeft() { return _cameraRc.left; }
	LONG getTop() { return _cameraRc.top; }

	void zoomIn(void);
	void zoomReset(void);
	void zoomOut(void);
	void zoomChange(POINT cameraSize);

	bool getIsFollowingCameraToTarget()
	{
		return _isFollowingCameraToTarget;
	}
	
	void setIsBattleScene(bool isBattle)
	{
		_isBattleScene = isBattle;
	}
	int getCameraWidth()
	{
		return _currentCameraSize.x;
	}
	int getCameraHeight()
	{
		return _currentCameraSize.y;
	}
	int getCameraCenterX()
	{
		return _currentCameraSize.x *0.5;
	}
	int getCameraCenterY()
	{
		return _currentCameraSize.y *0.5;
	}

	vector<pair<ZIndexType, ZOrderData*>>* getVecZData(){return &_vZData;}
	void removeZData(ZOrderData* zData);
	void registerZData(ZIndexType zIndex , ZOrderData* zData);

	Camera() :_TitleSceneSize({ 480,252}),
		_BattleSceneSize({410,215}),
		_WorldMapSceneSize({480,252}),
		_HomeSceneSize({480,252}),
		_zoomInSize({350,182}),
		_zoomOutSize({ 500,262 }),
		_cameraPt(nullptr),
		_moveToTargetEndPt(nullptr)
	{
	}
	~Camera() {}

};