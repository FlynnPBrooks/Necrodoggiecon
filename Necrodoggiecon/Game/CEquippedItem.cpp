#include "CEquippedItem.h"
#include "ItemDatabase.h"
#include "ItemData.h"
#include "CDroppedItem.h"

CEquippedItem::CEquippedItem()
{
}

CEquippedItem::~CEquippedItem()
{
}
/*
* Inherited function used to update the EquippedItem if necessary
*/
void CEquippedItem::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}
/*
* Function used to initialise the EquippedItem with the correct ItemData 
* Will get the ItemData from the ItemDatabase using the passed in id
* Will then set sprite data to the data from the retrieved ItemData
* Will then call the virtual Equip function for any necessary additional setup
*/
void CEquippedItem::Initialise(int id, CEntity* newOwner)
{
	itemID = id;
	itemOwner = newOwner;

	itemData = ItemDatabase::GetItemFromID(id);

	spriteComponent = AddComponent<CSpriteComponent>();
	GetSpriteComponent()->LoadTexture(GetItemData()->texturePath);
	GetSpriteComponent()->SetRenderRect(XMUINT2(128, 128));
	GetSpriteComponent()->SetSpriteSize(XMUINT2(128, 128));

	Equip();
}

void CEquippedItem::Equip()
{
}

void CEquippedItem::Unequip()
{
}

CDroppedItem* CEquippedItem::Drop()
{
	Unequip();

	auto item = ItemDatabase::CreateDroppedItemFromID(itemID);
	item->SetPosition(GetPosition());
	Engine::DestroyEntity(this);

	return item;
}
