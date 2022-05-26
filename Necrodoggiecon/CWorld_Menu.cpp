#include "CWorld_Menu.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include "Necrodoggiecon/MainMenu.h"


void CWorld_Menu::SetupWorld()
{
	CUIManager::AddCanvas(Engine::CreateEntity<MainMenu>(), "MainMenu");
}
