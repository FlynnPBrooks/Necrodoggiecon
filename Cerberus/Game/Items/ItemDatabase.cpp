#include "ItemDatabase.h"
#include "ItemData.h"
#include "EquippableItemData.h"
#include "CDroppedItem.h"
#include "CEquippedItem.h"
#include <Game/CCharacter.h>

std::map<int, ItemData*> ItemDatabase::itemDatabase = {};

ItemData* ItemDatabase::GetItemFromID(int id)
{
	if (itemDatabase.count(id) > 0)
	{
		return itemDatabase[id];
	}

    return nullptr;
}

CDroppedItem* ItemDatabase::CreateDroppedItemFromID(int id)
{
	ItemData* data = GetItemFromID(id);

	if (data == nullptr)
		return nullptr;

	CDroppedItem* item = Engine::CreateEntity<CDroppedItem>();
	item->Initialise(id);
	return item;
}

CEquippedItem* ItemDatabase::CreateEquippedItemFromID(int id, CCharacter* owner)
{
	ItemData* data = GetItemFromID(id);

	if (data == nullptr || data->GetItemType()  != ItemType::EQUIPPABLE)
		return nullptr;

	CEquippedItem* item = static_cast<EquippableItemData*>(data)->CreateItem();
	item->Initialise(id, owner);
	return item;
}

void ItemDatabase::AddToMap(ItemData* dataToAdd)
{
	itemDatabase.insert(std::pair<int, ItemData*>(GetNewID(), dataToAdd));
}

