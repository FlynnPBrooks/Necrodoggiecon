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
	/*
	* Returns the size of the itemDatabase to be used as a new ID, will break if things get removed from the itemDatabase
	*/
	static int GetNewID() { return (int)itemDatabase.size(); }

public:
	/*
	* Returns ItemData with the associated ID
	*/
	static ItemData* GetItemFromID(int id);
	/*
	* Creates an EquippedItem from the given ID and gives it to the passed in character
	*/
	static CEquippedItem* CreateEquippedItemFromID(int id, CCharacter* owner);
	/*
	* Creates a DroppedItem from the passed in ID
	*/
	static CDroppedItem* CreateDroppedItemFromID(int id);
	/*
	* Adds the passed in ItemData to the itemDatabase
	*/
	static void AddToMap(ItemData* dataToAdd);

};

