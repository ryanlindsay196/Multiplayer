#pragma once
#include <SDL_stdinc.h>

struct SDL_Surface;
struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Window;
union SDL_Event;

class Texture;

class Renderer
{
public:
	bool Initialize(unsigned int inWidth, unsigned int inHeight, bool shouldMaximizeWindow, const char* windowName);

	void Update(float deltaTime);

	void UpdateRender(Texture* textureToAdd, SDL_Rect* srcRect, SDL_Rect* destRect);
	void Render();

	void Destroy();

	int GetWidth() { return windowWidth; }
	int GetHeight() { return windowHeight; }
	int GetViewportWidth() { return viewportWidth; }
	int GetViewportHeight() { return viewportHeight; }

	bool HasMouseFocus() { return hasMouseFocus; }
	bool HasKeyboardFocus() { return hasKeyboardFocus; }
	bool IsMinimized() { return isMinimized; }

	void HandleWindowEvent(const SDL_Event& e);

	void Close();
	void Open();
	bool IsOpen();

	SDL_Renderer* GetSDLRenderer() const { return SDLRenderer; }
	Uint32 GetWindowID() const;
	unsigned int GetWindowFlags() const;

private:
	float GetWindowAspectRatio();
	float GetViewportAspectRatio();
	void TryUpdateViewportSize();

	SDL_Renderer* SDLRenderer;
	SDL_Window* window;

	int windowWidth, windowHeight;
	int viewportWidth, viewportHeight;

	//Window focus
	bool hasMouseFocus;
	bool hasKeyboardFocus;
	bool isFullScreen;
	bool isMinimized;
};