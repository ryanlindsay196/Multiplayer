#include "Game/Entity.h"
#include "Game/GameManager.h"

#include "Engine/Rendering/Renderer.h"

bool Entity::Initialize()
{
	RegisterSelfAsNetworked();

	return true;
}

void Entity::Spawn(mathfu::Vector<float, 2> inPosition)
{
	//TODO: Set up logic so we can't spawn if we're already spawned
	position.x = inPosition.x;
	position.y = inPosition.y;
}

void Entity::InitTexture(const char* inTextureFilename, mathfu::Vector<int, 2> textureDimensions)
{
	width = textureDimensions.x;
	height = textureDimensions.y;

	GameManager& gameManager = GameManager::Get();
	texture = gameManager.GetTextureManager()->LoadTexture(inTextureFilename);
}

void Entity::ReceiveControllerInput(float deltaTime)
{
	if (controller)
	{
		controller->UpdateInputs();
		position.x += controller->GetLeftAxis().x * deltaTime;
		position.y += controller->GetLeftAxis().y * deltaTime;
	}
}

void Entity::Update(float deltaTime)
{
	spriteSheet.Update(deltaTime);
	ReceiveControllerInput(deltaTime);
}

void Entity::Render()
{
	SDL_Rect destRect;
	destRect.x = position.x;
	destRect.y = position.y;
	destRect.w = width;
	destRect.h = height;

	SDL_Rect srcRect;
	srcRect.x = spriteSheet.GetDisplayedFrameBounds().startBounds.x;
	srcRect.y = spriteSheet.GetDisplayedFrameBounds().startBounds.y;
	srcRect.w = spriteSheet.GetDisplayedFrameBounds().endBounds.x - srcRect.x;
	srcRect.h = spriteSheet.GetDisplayedFrameBounds().endBounds.y - srcRect.y;

	GameManager& gameManager = GameManager::Get();
	Renderer* renderer = gameManager.GetRenderer();
	renderer->UpdateRender(texture.get(), &srcRect, &destRect);
}

void Entity::Destroy()
{
}
