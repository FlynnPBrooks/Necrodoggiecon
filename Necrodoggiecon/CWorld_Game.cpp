/*******************************************************************
 * \file   CWorld_Game.cpp
 * \brief  Child class of CWorld created for the game, overrides world setup from parent.
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "CWorld_Game.h"
#include <Necrodoggiecon\Game\PlayerController.h>
#include <Necrodoggiecon\Game\PlayerCharacter.h>
#include <Cerberus\Core\Components\CCameraComponent.h>
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include <Cerberus/Core/Structs/CCamera.h>
#include "Cerberus/WorldConstants.h"
#include "Necrodoggiecon/Weapons/Ranged/MagicMissile.h"
#include "Necrodoggiecon/Weapons/Ranged/Fireball.h"
#include "Necrodoggiecon/PauseMenu.h"
#include "Cerberus/Core/Utility/CUIManager.h"

#include <weaponUI.h>
#include <Necrodoggiecon\Game\CInteractable.h>
#include <Game/WeaponPickup.h>
#include <Weapons/Melee/Dagger.h>
#include <Weapons/Melee/Rapier.h>
#include <Weapons/Melee/Longsword.h>
#include <Weapons/Ranged/Crossbow.h>
#include <Weapons/Ranged/Fireball.h>
#include <Weapons/Ranged/MagicMissile.h>
#include "Necrodoggiecon/MainMenu.h"
#include "Necrodoggiecon/PauseMenu.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include "Weapons/Pickup/InvisibilityScroll.h"
#include "Weapons/Pickup/ShieldScroll.h"

/**
 * Constructor, automatically loads world based on provided slot.
 * 
 * \param Slot
 * Determines which level to load.
 */
CWorld_Game::CWorld_Game(int Slot)
{
	mapSlot = Slot;
	LoadWorld(Slot);
}

/**  */
void CWorld_Game::SetupWorld()
{
	PlayerController* controller = Engine::CreateEntity<PlayerController>();

	PlayerCharacter* character1 = Engine::CreateEntity<PlayerCharacter>();
	EntityList.push_back(controller);


	CUIManager::AddCanvas(Engine::CreateEntity<PauseMenu>(), "PauseMenu");

	controller->charOne = character1;

	Vector3 PlayerStart = Vector3(StartPos.x, StartPos.y, 0) * (tileScale * tileScaleMultiplier) + Vector3(0, 0, -1);
	Debug::Log("Player Start Position: [%f | %f]", PlayerStart.x, PlayerStart.y);
	character1->SetPosition(PlayerStart);
	controller->Possess(character1);

	Engine::CreateEntity<WeaponPickup<Dagger>>();
	Engine::CreateEntity<WeaponPickup<Rapier>>()->SetPosition(-100.0f, 0.0f, 0.0f);
	Engine::CreateEntity<WeaponPickup<Longsword>>()->SetPosition(100.0f, 0.0f, 0.0f);
	Engine::CreateEntity<WeaponPickup<Crossbow>>()->SetPosition(100.0f, 100.0f, 0.0f);
	Engine::CreateEntity<WeaponPickup<Fireball>>()->SetPosition(0.0f, 100.0f, 0.0f);
	Engine::CreateEntity<WeaponPickup<MagicMissile>>()->SetPosition(-100.0f, 100.0f, 0.0f);
	Engine::CreateEntity<WeaponPickup<ShieldScroll>>()->SetPosition(800.0f, 400, 0.0f);
	Engine::CreateEntity<WeaponPickup<InvisibilityScroll>>()->SetPosition(800.0f, 450, 0.0f);

	//Please stop configuring stuff in here instead of in the class constructor - Lets not spread configuration to many different places in the project!

	LoadEnemyUnits(mapSlot);
}

void CWorld_Game::UnloadWorld()
{
	EntityManager::Purge();
}

void CWorld_Game::ReloadWorld()
{
	EntityManager::Purge();
	SetupWorld();
	LoadEnemyUnits(mapSlot);
}

void CWorld_Game::LoadEnemyUnits(int Slot)
{
	std::string fileName = "Resources/Levels/Level_" + std::to_string(mapSlot);
	fileName += ".json";

	std::ifstream file(fileName);

	json storedFile;

	file >> storedFile;

	int enemyCount = storedFile["EnemyCount"];

	std::vector<PatrolNode*> patrolNodes;

	for (int i = 0; i < enemyCount; i++)
	{
		int EnemyID = storedFile["Enemy"][i]["Type"];
		int EnemyX = storedFile["Enemy"][i]["Position"]["X"];
		int EnemyY = storedFile["Enemy"][i]["Position"]["Y"];
		Vector3 position = Vector3{ (float)EnemyX, (float)EnemyY, 0.0f };
		CAIController* enemy = nullptr;
		int WeaponID = -1;
		switch (EnemyID)
		{
		case 0:
		{
			enemy = Engine::CreateEntity<GruntEnemy>();
			enemy->SetPosition(position);
			WeaponID = storedFile["Enemy"][i]["WeaponIndex"];
			switch (WeaponID)
			{
			case 0:
				enemy->EquipWeapon(new Dagger());
				break;
			case 1:
				enemy->EquipWeapon(new Rapier());
				break;
			case 2:
				enemy->EquipWeapon(new Longsword());
				break;
			case 3:
				enemy->EquipWeapon(new Crossbow());
				break;
			case 4:
				enemy->EquipWeapon(new MagicMissile());
				break;
			case 5:
				enemy->EquipWeapon(new Fireball());
				break;

			}

			break;
		}
		case 1:
		{
			enemy = Engine::CreateEntity<DogEnemy>();
			enemy->SetPosition(position);
			break;
		}
		case 2:
		{
			enemy = Engine::CreateEntity<AlarmEnemy>();
			enemy->SetPosition(position);
			break;
		}
		default:
			enemy = Engine::CreateEntity<CAIController>();
			break;
		}
		EntityList.push_back(enemy);

		int waypointlist = storedFile["Enemy"][i]["WaypointList"];
		for (int y = 0; y < waypointlist; y++)
		{
			int waypointx = storedFile["Enemy"][i]["Waypoints"][y]["X"];
			int waypointy = storedFile["Enemy"][i]["Waypoints"][y]["Y"];
			Vector3 patrolPosition = Vector3{ (float)waypointx * (tileScale * tileScaleMultiplier), (float)waypointy * (tileScale * tileScaleMultiplier), 0.0f };
			PatrolNode* patrol = new PatrolNode(patrolPosition);
			patrolNodes.push_back(patrol);
		}

		int numberOfPatrolNodes = patrolNodes.size();
		for (int patrolIndex = 0; patrolIndex < numberOfPatrolNodes; ++patrolIndex)
		{
			if (patrolIndex == numberOfPatrolNodes - 1)
			{
				patrolNodes[patrolIndex]->nextPatrolNode = patrolNodes[0];
			}
			else
			{
				patrolNodes[patrolIndex]->nextPatrolNode = patrolNodes[patrolIndex + 1];
			}
		}
		Vector3 enemyPos = enemy->GetPosition();
		enemy->pathing->SetPatrolNodes(patrolNodes);
		enemy->pathing->currentPatrolNode = enemy->pathing->FindClosestPatrolNode(enemy->GetPosition());
		enemy->SetCurrentState(PatrolState::getInstance());
		patrolNodes.clear();


	}
}

void CWorld_Game::LoadEntities(int Slot)
{

}
