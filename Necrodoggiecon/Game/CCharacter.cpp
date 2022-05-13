#include "CCharacter.h"
/*****************************************************************//**
 * \file   CCharacter.cpp
 * \brief  Base class for Characters
 * 
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/
/*
* Function to add vertical movement to the character
* dir is the direction on the y axis that the character will move
* speed is how fast to move the character
* deltaTime is used to ensure the character will move at a consistent speed that is not dependent on frame rate
*/
void CCharacter::AddVerticalMovement(int dir, float speed, float deltaTime)
{
	Vector3 pos = GetPosition();
	pos.y += dir * (speed * deltaTime);
	SetPosition(pos);
}
/** 
* Function to add vertical movement to the character
* dir is the direction on the y axis that the character will move 
* speed is how fast to move the character
* deltaTime is used to ensure the character will move at a consistent speed that is not dependent on frame rate
*/
void CCharacter::AddHorizontalMovement(int dir, float speed, float deltaTime)
{
	Vector3 pos = GetPosition();
	pos.x += dir * (speed * deltaTime);
	SetPosition(pos);
}
/** 
* Function used to equip items to the character
* itemToEquip will become the characters equippedItem
*/
void CCharacter::Equip(CEquippedItem* itemToEquip)
{
	if (itemToEquip == nullptr) return;

	equippedItem = itemToEquip;
}
/** 
* Virtual function used to determine how a character will interact with various pickups.
*/
void CCharacter::UsePickup(PickupItemData* itemToPickup)
{
}
