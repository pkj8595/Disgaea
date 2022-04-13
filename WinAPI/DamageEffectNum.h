#pragma once
#include "GameNode.h"

class DamageEffectNum : public GameNode
{
private:
	vector<ZOrderData*>	_vFrame;
	vector<ZOrderData*>::iterator	_viFrame;
	my::Image* _image;
	RECT	_rc;
	POINT	_point;
	LONG	_startPointY;
	int		_frame;
	int		_num;
	BYTE	_alpha;

	bool	_isActive;
	bool	_isIncrease;

public:
	HRESULT init(string imgkeyName, POINT point, int number);
	void release(void);
	void update(void);
	void render(void);

	bool getIsActive(void) { return _isActive; }

	DamageEffectNum() {}
	~DamageEffectNum() {}
};

