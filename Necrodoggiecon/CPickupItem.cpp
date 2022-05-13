#include "CPickupItem.h"

/*
* Inherited function used to update the EquippedItem if necessary
*/
void CPickupItem::Update(float deltaTime)
{

}
/*
* Inherited function used to initialise the PickupItem
* Calls the base Initialise function
*/
void CPickupItem::Initialise(int id, CEntity* owner)
{
	CEquippedItem::Initialise(id, owner);
}
