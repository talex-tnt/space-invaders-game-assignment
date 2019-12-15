#include "Display.h"
#include "../Engine.h"

namespace platform
{

platform::Display::Size Display::GetSize() const
{
	return Size{
		static_cast<Size::ValueT>(Engine::CanvasWidth),
		static_cast<Size::ValueT>(Engine::CanvasHeight) 
	};
}

}