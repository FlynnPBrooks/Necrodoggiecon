#pragma once
#include <Necrodoggiecon\Game\CCharacter.h>
#include <Cerberus\Core\Environment\IInputable.h>
#include <functional>
#include "Cerberus/Core/Components/CAudioEmitterComponent.h"

#include "weapons.h"

class CDroppedItem;
class CEquippedItem;
struct PickupItemData;

class PlayerCharacter : public CCharacter, public IInputable
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
	PlayerCharacter();

	void PressedHorizontal(int dir, float deltaTime) override;
	void PressedVertical(int dir, float deltaTime) override;
	void PressedInteract() override;
	void PressedDrop() override;
	void PressedUse() override;
	virtual void Update(float deltaTime) override;

	CDroppedItem* droppedItem = nullptr;

	virtual void UsePickup(PickupItemData* itemToPickup) override;

	bool GetVisible() { return visible; }
	CEquippedItem* equippedItem = nullptr;

	Weapon* weapon = nullptr;
	class CCameraComponent* camera = nullptr;
	CAudioEmitterComponent* loadNoise;
};

