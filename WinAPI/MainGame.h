#pragma once
#include "GameNode.h"

class DataSetUp;
class MainGame : public GameNode
{
private:
	DataSetUp* _dataSetup;
	my::Image*	_fadeImg;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	MainGame() {}
	virtual ~MainGame() {}
};