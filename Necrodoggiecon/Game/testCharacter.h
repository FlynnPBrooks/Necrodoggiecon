#pragma once
#include <Necrodoggiecon\Game\CCharacter.h>
#include <Cerberus\Core\Environment\IInputable.h>
#include <functional>

class CDroppedItem;
class CEquippedItem;
struct PickupItemData;

class testCharacter : public CCharacter, public IInputable
{
protected:
	float speed = 200;
	float timeElapsed = 0;

	float pickupTimer;
	bool pickupActive;
	float pickupActiveTime;

	bool visible = true;

	void LookAt(Vector3 pos);

	std::function<void()> pickupTimerCallback;

	void InvisibilityCallback();

	void PickupTimer(float deltaTime);
public:
	testCharacter();

	void PressedHorizontal(int dir, float deltaTime) override;
	void PressedVertical(int dir, float deltaTime) override;
	void PressedInteract() override;
	void PressedDrop() override;
	virtual void Update(float deltaTime) override;

	virtual void HasCollided(CollisionComponent* collidedObject) override;

	CDroppedItem* droppedItem = nullptr;

	virtual void Pickup(PickupItemData* itemToPickup) override;

	bool GetVisible() { return visible; }
};

