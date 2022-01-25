#include "testCharacter.h"
#include "CDroppedItem.h"
#include "CEquippedItem.h"

testCharacter::testCharacter()
{
	spriteComponent = AddComponent<CSpriteComponent>();
	spriteComponent->LoadTexture("Resources\\birb.dds");
	spriteComponent->SetRenderRect(XMUINT2(128, 128));
	spriteComponent->SetSpriteSize(XMUINT2(128, 128));

	spriteComponent->SetTint(XMFLOAT4(float(rand() % 2 * .5), float(rand() % 2 * .5), float(rand() % 2 * .5), 0));

	if (float(rand() % 2))
		spriteComponent->SetScale(-1, 1, 1);

	timeElapsed = float(rand() / 100);
}

void testCharacter::PressedHorizontal(int dir, float deltaTime)
{
	AddHorizontalMovement(dir, speed, deltaTime);
	
}

void testCharacter::PressedVertical(int dir, float deltaTime)
{
	AddVerticalMovement(dir, speed, deltaTime);
}

void testCharacter::PressedInteract()
{
	if (droppedItem == nullptr) return;

	equippedItem = droppedItem->OnEquip(this);
	Engine::DestroyEntity(droppedItem);
	droppedItem = nullptr;
}

void testCharacter::PressedDrop()
{
	if (equippedItem == nullptr) return;

	droppedItem = equippedItem->Drop();
	Engine::DestroyEntity(equippedItem);
	equippedItem = nullptr;
}

void testCharacter::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	const uint32_t animSpeed = 24;
	spriteComponent->SetTextureOffset(XMFLOAT2(round(timeElapsed * animSpeed) * 128, float((int(round(timeElapsed * animSpeed) / 5) % 2)) * 128));
}