#include "CameraManager.h"
#include "Cerberus\Core\Utility\DebugOutput\Debug.h"

std::map<std::uintptr_t,CCameraComponent*> CameraManager::cameras;
CCameraComponent* CameraManager::renderingCamera;

/**
 * Adds a camera to the manager.
 * 
 * \param camera camera you wish to add.
 */
void CameraManager::AddCamera(CCameraComponent* camera)
{
	cameras.emplace(std::make_pair((uintptr_t)camera, camera));
}

/**
 * Removes a camera from the manager. Further, if a rendering camera is delete it will move the rendering camera to the next camera in the manager.
 * 
 * \param camera camera you wish to remove.
 */
void CameraManager::RemoveCamera(CCameraComponent* camera)
{
	if(cameras.find((uintptr_t)camera) != cameras.end())
	{
		cameras.erase((uintptr_t)camera);

		if(camera == renderingCamera)
		{
			if(cameras.size() > 0)
			{
				std::map<std::uintptr_t, CCameraComponent*>::iterator it = cameras.begin();
				renderingCamera = it->second;
			}
			else
			{
				Debug::LogError("Removed the last camera in the manager. No Rendering Camera exists now!.");
				renderingCamera = nullptr;
			}
		}
	}
	else
	{
		Debug::LogError("Tried to remove a camera that doesnt exist.");
		return;
	}
}

/**
 * Returns the rendering camera.
 * 
 * \return the current rendering camera.
 */
CCameraComponent* CameraManager::GetRenderingCamera()
{
	if(renderingCamera == nullptr)
	{
		Debug::LogError("Tried to get rendering camera when it has not been set.");
	}

	return renderingCamera;
}

/**
 * Sets the rendering camera.
 * 
 * \param camera the camera you wish to set as the rendering camera.
 */
void CameraManager::SetRenderingCamera(CCameraComponent* camera)
{
	if(cameras.find((uintptr_t)camera) != cameras.end())
	{
		renderingCamera = camera;
	}
	else
	{
		Debug::LogError("Tried to set rendering camera when it does not exist within the camera manager.");
		return;
	}
}

/**
 * Returns a vector of all cameras inside the manager.
 * 
 * \return a vector of all cameras stored within the camera manager.
 */
std::vector<CCameraComponent*> CameraManager::GetAllCameras()
{
	std::vector<CCameraComponent*> vec;

	for(const auto& cam : cameras)
	{
		vec.push_back(cam.second);
	}

	return vec;
}
