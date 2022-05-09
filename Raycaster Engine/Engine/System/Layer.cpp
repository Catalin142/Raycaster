#include "Core/RaycastPCH.h"
#include "Application.h"
#include "Layer.h"

Layer::Layer()
{
	UiManager = std::make_shared<UIManager>();
}
