#pragma once
#include <vector>
#include <memory>

#include "Engine/Reflection/Reflection.h"
#include "Engine/BaseObject.h"
#include "mathfu/vector.h"

class Entity;
class CharacterController;


class EntityManager : public BaseObject
{
public:
	EntityManager() {}

	EntityManager(EntityManager const&) = delete;
	void operator=(EntityManager const&) = delete;

	void Close() 
	{ 
		entities.clear(); 
		controllers.clear();
	}

public:
	DefineClassMetaFunctionGetters(EntityManager)

	virtual bool Initialize() override;

	template<typename T>
	std::shared_ptr<T> CreateEntity(unsigned int networkID, unsigned int owningClientID, mathfu::Vector<float, 2> startPosition, mathfu::Vector<float, 2> textureDimensions)
	{
		std::shared_ptr <T> newEntity(new T());
		newEntity->InitializeNetworkID(networkID);
		newEntity->InitializeOwningClientID(owningClientID);
		newEntity->Initialize();
		newEntity->Spawn(startPosition);
		newEntity->InitTexture((char*)"Resources/Images/Bomberman Spritesheet.png", textureDimensions);

		entities.push_back(newEntity);
		return newEntity;
	}

	std::shared_ptr<CharacterController> CreateController(unsigned int characterNetworkID, unsigned int controllerNetworkID, unsigned int owningClientID);

	void UpdateEntities(float deltaTime);
	void RenderEntities();

private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<CharacterController>> controllers;
};