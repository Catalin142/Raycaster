#include "Core/RaycastPCH.h"
#include "Button.h"

Button::Button(const std::shared_ptr<Sprite>& spr, float width, float height) : InteractableUI(spr, width, height)
{ }

Button::Button(const std::string& filepath, float width, float height) : InteractableUI(filepath, width, height)
{ }

Button::Button(const vec3 & color, float width, float height) : InteractableUI(color, width, height)
{ }