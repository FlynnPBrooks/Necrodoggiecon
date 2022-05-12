#include "testCharacter.h"
#include "CDroppedItem.h"
#include "CEquippedItem.h"
#include "PickupItemData.h"
#include "Cerberus/Core/Engine.h"
#include "Cerberus/Core/Structs/CCamera.h"

testCharacter::testCharacter()
{
	spriteComponent = AddComponent<CSpriteComponent>();
	spriteComponent->LoadTexture("Resources\\birb.dds");
	spriteComponent->SetRenderRect(XMUINT2(128, 128));
	spriteComponent->SetSpriteSize(XMUINT2(128, 128));

	spriteComponent->SetTint(XMFLOAT4(float(rand() % 2 * .5), float(rand() % 2 * .5), float(rand() % 2 * .5), 0));

	colComponent = new CollisionComponent("Character 1");

	if (float(rand() % 2))
		spriteComponent->SetScale(-1, 1, 1);

	timeElapsed = float(rand() / 100);
	pickupActive = false;
	pickupTimer = 0;
	pickupActiveTime = 0;
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

	droppedItem->OnInteract(this);
	droppedItem = nullptr;
}

void testCharacter::PressedDrop()
{
	if (equippedItem == nullptr) return;

	droppedItem = equippedItem->Drop();
	equippedItem = nullptr;
}


void testCharacter::PressedInvisible()
{
	if (droppedItem == nullptr) return;

	droppedItem->OnInteract(this);
	droppedItem = nullptr;
}

void testCharacter::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	const uint32_t animSpeed = 24;
	spriteComponent->SetTextureOffset(XMFLOAT2(round(timeElapsed * animSpeed) * 128, float((int(round(timeElapsed * animSpeed) / 5) % 2)) * 128));

	LookAt(Vector3(Inputs::InputManager::mousePos.x - Engine::windowWidth * 0.5f, -Inputs::InputManager::mousePos.y + Engine::windowHeight * 0.5f, GetPosition().z));

	colComponent->SetPosition(GetPosition());

	PickupTimer(deltaTime);
}

void testCharacter::HasCollided(CollisionComponent* collidedObject)
{
	if (collidedObject->GetName() == "Wall")
		Debug::Log("Player has collided with a wall");
}


/*
Checks the pickup item type and activates the functionality for that pickup.
E.g, Invisibility scroll will make the player invisible and bind a callback to the timer to make the player visible after a certain amount of time.
*/
void testCharacter::Pickup(PickupItemData* itemToPickup)
{
	pickupActive = true;
	pickupTimer = 0;
	pickupActiveTime = itemToPickup->GetPickupTime();

	switch (itemToPickup->GetPickupType())
	{
	case PickupType::NECRODOGGICON_PAGE:
		Debug::Log("Pickup Necrodoggiecon Page \n");
		break;
	case PickupType::CHARM_SCROLL:
		Debug::Log("Pickup Charm Scroll \n");
		break;
	case PickupType::INVISIBILITY_SCROLL:
		visible = false;
		pickupTimerCallback = std::bind(&testCharacter::InvisibilityCallback, this);
		spriteComponent->shouldDraw = false;
		Debug::Log("Pickup Invisibility Scroll \n");
		break;
	case PickupType::SEEING_SCROLL:
		Debug::Log("Pickup Seeing Scroll \n");
		break;
	case PickupType::SHIELD_SCROLL:
		Debug::Log("Pickup Shield Scroll \n");
		break;
	default:
		break;
	}
}

void testCharacter::InvisibilityCallback()
{
	Debug::Log("invisCB");
	visible = true;
	spriteComponent->shouldDraw = true;
}

void testCharacter::PickupTimer(float deltaTime)
{
	if (!pickupActive) return;
	
	pickupTimer += deltaTime;

	if (pickupTimer >= pickupActiveTime)
	{
		pickupActive = false;
		pickupTimerCallback();
	}
}

void testCharacter::LookAt(Vector3 pos)
{
	Vector3 up = { 0.0f, 1.0f, 0.0f };

	Vector3 dir = pos - GetPosition();
	
	auto normDir = pos.Normalize();

	float dot = up.Dot(normDir);
	float det = up.x * normDir.y - up.y * normDir.x;

	SetRotation(atan2f(det, dot));
}