#pragma once

#include <string>
#include <Necrodoggiecon/Game/ItemDatabase.h>

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
