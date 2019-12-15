#pragma once
#include <functional>
#include <memory>

struct SDL_Window;

namespace sdl
{
class Window;
namespace policy
{
class Initialization
{
public:
	using WindowT = Window;

	bool Init();
	WindowT* GetWindow();
	const WindowT* GetWindow() const;

protected:
	Initialization();
	~Initialization();

	Initialization(const Initialization&) = delete;
	Initialization(Initialization&&) = delete;

	Initialization& operator=(const Initialization&) = delete;
	Initialization& operator=(Initialization&&) = delete;

protected:
	std::unique_ptr<WindowT> m_window;
};

}
}