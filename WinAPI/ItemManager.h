#pragma once
#include "SingletonBase.h"
#include "Item.h"

class ItemManager : public SingletonBase<ItemManager>
{
private:
	vector<Item*> _vItem;
	Item* _emptyItem;

public:
	HRESULT init(void);
	void release(void);

	int getItemSize() { return _vItem.size(); }
	Item* getItem(int index);

	Item* getEmptyItem() { return _emptyItem; }

	ItemManager() {}
	~ItemManager() {} 
};

