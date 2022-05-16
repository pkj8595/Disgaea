#include "Stdafx.h"
#include "ItemManager.h"

HRESULT ItemManager::init(void)
{
	_emptyItem = new Item;
	_emptyItem->_name = "ºó Ä­";

	return S_OK;
}

void ItemManager::release(void)
{

}

Item* ItemManager::getItem(int index)
{
	if (index < 0 ||index > _vItem.size() - 1) return nullptr;

	return _vItem[index];
}
