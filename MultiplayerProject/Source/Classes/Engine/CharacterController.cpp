#include "Engine/CharacterController.h"
#include "Game/GameManager.h"

//TODO: Make it so we don't need any of these parameters.
bool CharacterController::Initialize(const char * imagePath, float inWidth, float inHeight, mathfu::Vector<float, 2> inPosition)
{
	RegisterSelfAsNetworked();
	CreateVariableMetadata(CharacterController, leftAxis, Networked(AuthorityType::OwningClient, leftAxis))
	CreateVariableMetadata(CharacterController, rightAxis, Networked(AuthorityType::OwningClient, rightAxis))
	
	return true;
}

void CharacterController::UpdateInputs()
{
	//TODO: This is temporary until we get a networked controller variant
	if (GameManager::GetNetworkManager().GetIsServer())
		return;

	leftAxis = mathfu::Vector<float, 2>(0, 0);
	rightAxis = mathfu::Vector<float, 2>(0, 0);

	GameManager& gameManager = GameManager::Get();
	if (gameManager.GetInputManager()->IsKeyDown(SDLK_UP, true))
	{
		leftAxis.y -= 1;
	}
	if (gameManager.GetInputManager()->IsKeyDown(SDLK_DOWN, true))
	{
		leftAxis.y += 1;
	}
	if (gameManager.GetInputManager()->IsKeyDown(SDLK_RIGHT, true))
	{
		leftAxis.x += 1;
	}
	if (gameManager.GetInputManager()->IsKeyDown(SDLK_LEFT, true))
	{
		leftAxis.x -= 1;
	}
}
