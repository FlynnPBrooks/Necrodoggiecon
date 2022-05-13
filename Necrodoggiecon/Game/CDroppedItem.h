#pragma once
#include <Cerberus\Core\Components\CSpriteComponent.h>
#include <Cerberus\Core\CEntity.h>

class CEquippedItem;
struct ItemData;
class CCharacter;

class CDroppedItem : public CEntity
{
protected:
	CSpriteComponent* spriteComponent = nullptr;
	int itemID = 0;

	ItemData* itemData = nullptr;
public:
	CDroppedItem();
	~CDroppedItem();

	virtual void OnInteract(CCharacter* owner);

	int  GetID() { return itemID; }

	virtual void Initialise(int id);
	virtual void Update(float deltaTime) override;
};

