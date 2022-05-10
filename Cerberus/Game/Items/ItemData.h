#pragma once
#include <Items/ItemDatabase.h>
#include <string>

enum class ItemType
{
	PICKUP,
	EQUIPPABLE
};

struct ItemData
{
	std::string itemName;
	std::string texturePath;

	ItemData(std::string name, std::string textureFilePath) : itemName(name), texturePath(textureFilePath)
	{
		ItemDatabase::AddToMap(this);
	}

	ItemType GetItemType() { return itemType; }
protected:
	ItemType itemType;

	
};

