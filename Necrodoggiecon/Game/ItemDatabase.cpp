#include "ItemDatabase.h"
#include "EquippableItemData.h"
#include "ItemData.h"
#include "CDroppedItem.h"
#include "CEquippedItem.h"
#include "CCharacter.h"
#include "testEquippedItem.h"

std::map<int, ItemData*> ItemDatabase::itemDatabase = {};

/*
Will return the ItemData with the associated ID if it exists, if it doesn't it returns nullptr
*/
ItemData* ItemDatabase::GetItemFromID(int id)
{
	if (itemDatabase.count(id) > 0)
	{
		return itemDatabase[id];
	}

    return nullptr;
}


/*
Will create a new DroppedItem and initialise it with the passed in ID, if an ItemData with the ID doesn't exist it will return nullptr
*/
CDroppedItem* ItemDatabase::CreateDroppedItemFromID(int id)
{
	ItemData* data = GetItemFromID(id);

	if (data == nullptr)
		return nullptr;

	CDroppedItem* item = Engine::CreateEntity<CDroppedItem>();
	item->Initialise(id);
	return item;
}
/*
Will create a new EquippedItem and initialise it with the passed in ID, if an ItemData with the ID doesn't exist it will return nullptr
*/
CEquippedItem* ItemDatabase::CreateEquippedItemFromID(int id, CCharacter* owner)
{
	ItemData* data = GetItemFromID(id);

	if (data == nullptr || data->GetItemType() != ItemType::EQUIPPABLE)
		return nullptr;

	CEquippedItem* item = static_cast<EquippableItemData*>(data)->CreateItem();
	item->Initialise(id, owner);
	return item;
}
/*
Will add the passed in ItemData to the itemDatabase and give it a unique ID
*/
void ItemDatabase::AddToMap(ItemData* dataToAdd)
{
	itemDatabase.insert(std::pair<int, ItemData*>(GetNewID(), dataToAdd));
}

