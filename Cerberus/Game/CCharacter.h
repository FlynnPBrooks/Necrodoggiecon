#pragma once
#include <CSpriteComponent.h>
#include <CEntity.h>
#include <Game/Items/CEquippedItem.h>

class CCharacter : public CEntity
{
private:
protected:
	CSpriteComponent* spriteComponent = nullptr;
	CEquippedItem* equippedItem = nullptr;


	virtual void OnTakeDamage(float damageAmount, CEntity* damageCauser) {
		UNREFERENCED_PARAMETER(damageCauser);
		UNREFERENCED_PARAMETER(damageAmount);
	};

	void AddVerticalMovement(int dir, float speed, float deltaTime);
	void AddHorizontalMovement(int dir, float speed, float deltaTime);
public:
	void ApplyDamage(float damageAmount, CEntity* damageCauser) { OnTakeDamage(damageAmount, damageCauser); }

	virtual void Update(float deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };

	virtual void Equip(CEquippedItem* itemToEquip);

};

