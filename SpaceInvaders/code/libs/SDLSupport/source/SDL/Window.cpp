#include "Window.h"

#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wpragma-pack"
#endif
#include <SDL.h>
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif

#include <iostream>

namespace sdl
{

Window::Window(std::uint32_t i_flags)
	: m_window(
		SDL_CreateWindow(
			"SDL2Test",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			1280,
			1024,
			i_flags
		),
		[] (SDL_Window* win) { SDL_DestroyWindow(win); })
{
	if ( !m_window )
	{
		std::cerr << SDL_GetError();
	}
}

bool Window::IsInitialized() const noexcept
{
	return m_window != nullptr;
}

SDL_Window* Window::GetSDLWindow() noexcept
{
	return m_window.get();
}

const SDL_Window* Window::GetSDLWindow() const noexcept
{
	return m_window.get();
}

int Window::GetDisplayIndex() const
{
	return SDL_GetWindowDisplayIndex(m_window.get());
}

Window::~Window() = default;

}
