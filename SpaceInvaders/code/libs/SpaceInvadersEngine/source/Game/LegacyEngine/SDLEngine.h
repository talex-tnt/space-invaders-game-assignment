#pragma once

#include <SDL/Policy/Initialization.h>
#include <SDL/Policy/EventDispatch.h>
#include <SDL/Policy/GraphicsProvider.h>
#include <AppEvents/IEventHandler.h>



class SDLEngine 
	: private sdl::policy::Initialization
	, private sdl::policy::EventDispatch
	, private app::events::IEventHandler
	, private sdl::policy::GraphicsProvider

{
public:
	bool Run();
	
	SDLEngine();
	~SDLEngine();

	struct Input
	{
		bool space, left, right, up, down;
	} m_input;

public:
	const Input& GetInput() const;

public:
	void OnEventDispatchStarted() override;
	void OnEvent(app::events::EventType i_eventType) override;
	void OnEvent(const app::events::KeyEvent& i_event) override;

private:

	bool m_isRunning;
};

