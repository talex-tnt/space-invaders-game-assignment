#include "Display.h"
#include <Game/LegacyEngine/SpaceInvadersEngine.h>

namespace platform
{

platform::Display::Size Display::GetSize() const
{
	return Size{
		static_cast<Size::ValueT>(SpaceInvadersEngine::CanvasWidth),
		static_cast<Size::ValueT>(SpaceInvadersEngine::CanvasHeight)
	};
}

}