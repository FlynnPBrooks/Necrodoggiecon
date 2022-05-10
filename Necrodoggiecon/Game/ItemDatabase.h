#pragma once
#include <map>

class CEquippedItem;
class CDroppedItem;
class CCharacter;

struct ItemData;

class ItemDatabase
{
private:
	static ItemDatabase* instance;
	ItemDatabase() {};
protected:
	static std::map<int, ItemData*> itemDatabase;
	static int GetNewID() { return (int)itemDatabase.size(); }

public:
	static ItemData* GetItemFromID(int id);
	static CEquippedItem* CreateEquippedItemFromID(int id, CCharacter* owner);
	static CDroppedItem* CreateDroppedItemFromID(int id);

	static void AddToMap(ItemData* dataToAdd);

};

