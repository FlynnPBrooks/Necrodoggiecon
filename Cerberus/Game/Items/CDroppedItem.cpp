#include "CDroppedItem.h"
#include "ItemDatabase.h"
#include "ItemData.h"
#include "CEquippedItem.h"
#include <Game/CCharacter.h>

CDroppedItem::CDroppedItem()
{
}

CDroppedItem::~CDroppedItem()
{
}

void CDroppedItem::OnEquip(CCharacter* owner)
{
	if (itemData->GetItemType() == ItemType::EQUIPPABLE)
		owner->Equip(ItemDatabase::CreateEquippedItemFromID(itemID, owner));
}

void CDroppedItem::Initialise(int id)
{
	itemID = id;

	itemData = ItemDatabase::GetItemFromID(id);

	spriteComponent = AddComponent<CSpriteComponent>();
	spriteComponent->LoadTexture(itemData->texturePath);
	spriteComponent->SetRenderRect(XMUINT2(128, 128));
	spriteComponent->SetSpriteSize(XMUINT2(128, 128));
}

void CDroppedItem::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}
