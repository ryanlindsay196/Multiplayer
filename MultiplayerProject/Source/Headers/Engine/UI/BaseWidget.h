#pragma once
#include <vector>
#include "mathfu/vector.h"
#include "SDL_rect.h"
#include "Engine/Delegate.h"

#include "Engine/InputManager.h"
#include "Engine/JsonDataPopulator.h"
#include "Engine/Reflection/Reflection.h"

#include "rapidjson/document.h"

class Renderer;

enum class InputResponse
{
	Handled,
	UnHandled
};

struct Anchor
{
public:
	Anchor() : normalizedValue(0, 0) {}
	Anchor(mathfu::Vector<float, 2> inNormalizedValue) : normalizedValue(inNormalizedValue) {}
	
	static const Anchor TopLeft()			{ return Anchor(mathfu::Vector<float, 2>(0.0f, 0.0f)); }
	static const Anchor CenterLeft()		{ return Anchor(mathfu::Vector<float, 2>(0.0f, 0.5f)); }
	static const Anchor BottomLeft()		{ return Anchor(mathfu::Vector<float, 2>(0.0f, 1.0f)); }
	static const Anchor TopCenter()			{ return Anchor(mathfu::Vector<float, 2>(0.5f, 0.0f)); }
	static const Anchor CenterCenter()		{ return Anchor(mathfu::Vector<float, 2>(0.5f, 0.5f)); }
	static const Anchor BottomCenter()		{ return Anchor(mathfu::Vector<float, 2>(0.5f, 1.0f)); }
	static const Anchor TopRight()			{ return Anchor(mathfu::Vector<float, 2>(1.0f, 0.0f)); }
	static const Anchor CenterRight()		{ return Anchor(mathfu::Vector<float, 2>(1.0f, 0.5f)); }
	static const Anchor BottomRight()		{ return Anchor(mathfu::Vector<float, 2>(1.0f, 1.0f)); }

	mathfu::Vector<float, 2> normalizedValue;
};

typedef Anchor Alignment;

class BaseWidget
{
public:
	virtual void Initialize(Renderer* renderer, rapidjson::GenericArray<false, rapidjson::Value::ValueType>::PlainType* widgetData);

	void AddChild(BaseWidget* newChild);
	void RemoveChild(BaseWidget* childToRemove);
	void RemoveFromParent();

	void SetParent(BaseWidget* inParent);
	BaseWidget* GetParent() { return parent; }

	BaseWidget* ProcessMouseInput(Input& mouseInput);
	virtual InputResponse TryHandleMousePress(mathfu::Vector<int, 2> mousePressPosition);

	virtual void Draw(Renderer* renderer, const SDL_Rect& parentRectBounds, bool isAnyParentDirty = false);

	void SetAnchor(Anchor newAnchor)
	{
		isTransformDirty = true;
		anchor = newAnchor;
		assert(abs(anchor.normalizedValue.x) <= 1);
		assert(abs(anchor.normalizedValue.y) <= 1);
	}

	void SetAlignment(Alignment newAlignment)
	{
		isTransformDirty = true;
		alignment = newAlignment;
		assert(abs(alignment.normalizedValue.x) <= 1);
		assert(abs(alignment.normalizedValue.y) <= 1);
	}

	virtual void SetWidthInLocalSpace(int inWidth)
	{
		isTransformDirty = true;
		sizeInLocalSpace.x = inWidth;
	}

	virtual void SetHeightInLocalSpace(int inHeight)
	{
		isTransformDirty = true;
		sizeInLocalSpace.y = inHeight;
	}

	virtual int GetWidthInLocalSpace() const
	{
		return sizeInLocalSpace.x;
	}

	virtual int GetHeightInLocalSpace() const
	{
		return sizeInLocalSpace.y;
	}

	SDL_Color GetColor() { return color; }

	void SetColor(SDL_Color inColor) { color = inColor; }

	virtual float GetWidthInGlobalSpace(const Renderer* const renderer, const SDL_Rect& parentRectBounds) const;
	virtual float GetHeightInGlobalSpace(const Renderer* const renderer, const SDL_Rect& parentRectBounds) const;

	void MousePressed(mathfu::Vector<int, 2> mousePressPosition);
	void MouseReleased(mathfu::Vector<int, 2> mouseReleasePosition);

	SingleCastDelegate<void>& GetOnMousePressedDel() { return onMousePressedDel; }
	SingleCastDelegate<void>& GetOnMouseReleasedDel() { return onMouseReleasedDel; }

	void RemoveAllChildren() 
	{
		children.clear();
	}
protected:
	virtual SDL_Rect CalculateBoundsInGlobalSpace(const Renderer* const renderer, const SDL_Rect& parentRectBounds) const;

	virtual void OnMousePressed(mathfu::Vector<int, 2> mousePressPosition);
	virtual void OnMouseReleased(mathfu::Vector<int, 2> mouseReleasePosition);

	std::vector<BaseWidget*> children;

	BaseWidget* parent;
	char name[21];
	Anchor anchor;
	Alignment alignment;
	mathfu::Vector<int, 2> sizeInLocalSpace;
	SDL_Rect cachedBoundsInGlobalSpace;

	SDL_Color color;

	SingleCastDelegate<void> onMousePressedDel;
	SingleCastDelegate<void> onMouseReleasedDel;
	
	bool isTransformDirty;
};