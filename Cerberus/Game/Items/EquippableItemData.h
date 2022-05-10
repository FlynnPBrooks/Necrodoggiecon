#pragma once

#include <Items/ItemData.h>
#include <Items/CEquippedItem.h>

struct EquippableItemData : public ItemData
{
	EquippableItemData(std::string name, std::string textureFilePath) : ItemData(name, textureFilePath)
	{
		itemType = ItemType::EQUIPPABLE;
	}

	virtual CEquippedItem* CreateItem()
	{
		return Engine::CreateEntity<CEquippedItem>();
	}
};