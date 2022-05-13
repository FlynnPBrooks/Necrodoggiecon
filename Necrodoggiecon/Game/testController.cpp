#include "testController.h"
#include "testCharacter.h"
#include "ItemDatabase.h"
#include "CEquippedItem.h"

#include <Necrodoggiecon\Game\CursorEntity.h>

/** 
* Inherited function
* Used to update the Controller each frame
*/
void testController::Update(float deltaTime)
{
	HandleInput(deltaTime);
}

/** 
* Inherited function
* Used to handle the input that the Controller receives
* Will pass input down to the possessed Character using the IInputable interface
*/
void testController::HandleInput(float deltaTime)
{
	if (!HasCharacter()) return;
	
	if (inputable == nullptr) return;


	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::D))
		inputable->PressedHorizontal(1, deltaTime);
	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::A))
		inputable->PressedHorizontal(-1, deltaTime);
	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::W))
		inputable->PressedVertical(1, deltaTime);
	if (Inputs::InputManager::IsKeyPressed(Inputs::InputManager::S))
		inputable->PressedVertical(-1, deltaTime);
	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::E))
		inputable->PressedInteract();
	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::G))
		inputable->PressedDrop();
	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::I))
		inputable->PressedUse();



	if (Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::Q))
	{
		//EquippedItem* item = ItemDatabase::Instance()->CreateItemFromID(0);
		//testCharacter* item = Engine::CreateEntity<testCharacter>();
		CursorEntity* item = Engine::CreateEntity<CursorEntity>();
		//CAICharacter* item = Engine::CreateEntity<CAICharacter>();
		item->SetPosition(Vector3((float(rand() % Engine::windowWidth) - Engine::windowWidth / 2), (float(rand() % Engine::windowHeight) - Engine::windowHeight / 2), 0));
	}
}

void testController::SwapChar()
{
	if (charIndex == 1)
	{
		Possess(charTwo);
		charIndex = 2;
	}
	else if (charIndex == 2)
	{
		Possess(charOne);
		charIndex = 1;
	}
}

/** 
* Inherited function
* Used to get the IInputable interface from the newly possessed character
*/
void testController::OnPossess()
{
	inputable = dynamic_cast<IInputable*>(GetCharacter());
}

/** 
* Inherited function
* Used to remove the IInputable interface
*/
void testController::OnUnpossess()
{
	inputable = nullptr;
}
