/*****************************************************************//**
 * \file   EntityManager.h
 * \brief  Static class for tracking entities and components while accommodating translucency.
 * 
 * \author Arrien Bidmead
 * \date   May 2022
 *********************************************************************/

#pragma once
#include <unordered_map>

/**
 * Static class for tracking entities and components while accommodating translucency.
 */
class EntityManager
{
	static std::unordered_map<uintptr_t, class CEntity*> entities;

	static std::unordered_map<uintptr_t, class CComponent*> opaqueComps;
	static std::vector<class CComponent*> translucentComps;

public:
	/**
	 * Adds the input entity to the internal unordered map.
	 */
	static void AddEntity(class CEntity* entityToAdd);

	/**
	 * Removes the input entity to the internal unordered map.
	 * Note: does NOT delete the entity.
	 */
	static void RemoveEntity(const class CEntity* entityToRemove);

	/**
	 * Adds the input component to the internal containers based on translucency boolean in CComponent.
	 */
	static void AddComponent(class CComponent* compToAdd);

	/**
	 * Removes the input component to the internal containers based on translucency boolean in CComponent.
	 * Note: does NOT delete the component.
	 */
	static void RemoveComponent(const class CComponent* compToRemove);

	/**
	 * Sorts the translucent components container ready for drawing.
	 * This is done automatically in the engine's draw function so DON'T call this.
	 */
	static void SortTranslucentComponents();

	static const std::unordered_map<uintptr_t, class CEntity*>* GetEntitiesMap();
	static const std::unordered_map<uintptr_t, class CComponent*>* GetOpaqueCompsMap();
	static const std::vector<class CComponent*>* GetTranslucentCompsVector();
};
