#include "CDroppedItem.h"
#include "ItemDatabase.h"
#include "ItemData.h"
#include "CEquippedItem.h"
#include "CCharacter.h"
#include "PickupItemData.h"
#include "Cerberus\Core\Engine.h"

CDroppedItem::CDroppedItem()
{
}

CDroppedItem::~CDroppedItem()
{
}
/*
* Function used when a player interacts with a dropped item
* Will equip the dropped item to the player by creating a new EquippedItem with the DroppedItems data
* Will then destroy the DroppedItem
*/
void CDroppedItem::OnInteract(CCharacter* owner)
{
	owner->Equip(ItemDatabase::CreateEquippedItemFromID(itemID, owner));

	Engine::DestroyEntity(this);
}
/*
* Function used to initialise the DroppedItem with the correct ItemData
* Will get the ItemData from the ItemDatabase using the passed in id
* Will then set sprite data to the data from the retrieved ItemData
*/
void CDroppedItem::Initialise(int id)
{
	itemID = id;

	itemData = ItemDatabase::GetItemFromID(id);

	spriteComponent = AddComponent<CSpriteComponent>();
	spriteComponent->LoadTexture(itemData->texturePath);
	spriteComponent->SetRenderRect(XMUINT2(128, 128));
	spriteComponent->SetSpriteSize(XMUINT2(128, 128));
}
/*
* Inherited function used to update the DroppedItem if necessary
*/
void CDroppedItem::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}
