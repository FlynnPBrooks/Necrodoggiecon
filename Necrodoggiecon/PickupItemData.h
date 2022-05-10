#pragma once

#include <Necrodoggiecon/Game/ItemData.h>

enum class PickupType
{
	NECRODOGGICON_PAGE,
	SHIELD_SCROLL,
	INVISIBILITY_SCROLL,
	CHARM_SCROLL,
	SEEING_SCROLL
};
struct PickupItemData : public ItemData
{
	PickupType GetPickupType() { return pickupType; }
	float GetPickupStrength() { return pickupStrength; }
	float GetPickupTime() { return pickupTime; }

	PickupItemData(std::string name, std::string textureFilePath, PickupType type = PickupType::NECRODOGGICON_PAGE, float strength = 2.0f, float time = 5.0f) :
		ItemData(name, textureFilePath), pickupType(type), pickupStrength(strength), pickupTime(time)
	{
		itemType = ItemType::PICKUP;
	}
protected:
	PickupType pickupType;
	float pickupStrength;
	float pickupTime;
};