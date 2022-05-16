#pragma once
#include "SingletonBase.h"
#include "ItemManager.h"

class GameCharacter;
class GameManager :public SingletonBase<GameManager>
{
private:
	ItemManager* _itemManager;
	vector<GameCharacter*> _playerUnits;
	vector<Item*> _vInvenItem;
	int _gold;

	int _stageIndex;
	int _DetailStageIndex;

public:
	HRESULT init(void);
	void release(void);

	void playerUnitClear(void);
	void setStageIndex(int index) { _stageIndex = index; }
	void setDetailStageIndex(int detailIndex){_DetailStageIndex = detailIndex;}
	int getStageIndex(void) { return _stageIndex; }
	int getDetailStageIndex(void) { return _DetailStageIndex; }

	void healAllCharacter(void);
	vector<GameCharacter*>* getAllPlayerUnits(){return &_playerUnits;}
	vector<Item*> getAllInvenItems() { return _vInvenItem; }
	GameCharacter* getPlayerUnit(int index)
	{
		return _playerUnits[index];
	}
	Item* getItem(int index) { return _vInvenItem[index]; }

	void addPlayerUnit(GameCharacter* playerUnit) { _playerUnits.push_back(playerUnit); }
	void addPlayerUnit(Item* item) { _vInvenItem.push_back(item); }

	int getGold(void) { return _gold; }
	void setGold(int gold) { _gold = gold; }



	GameManager() {}
	~GameManager() {}
};

