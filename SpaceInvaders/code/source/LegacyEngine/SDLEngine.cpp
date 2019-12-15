#include "SDLEngine.h"

SDLEngine::SDLEngine()
	: m_isRunning(sdl::policy::Initialization::Init())
{

}

SDLEngine::~SDLEngine()
{
}

const SDLEngine::SDLEngine::Input& SDLEngine::GetInput() const
{
	return m_input;
}

void SDLEngine::OnEventDispatchStarted()
{
	m_input = Input{false, false, false};
}

void SDLEngine::OnEvent(app::events::EventType i_eventType)
{
	if (i_eventType == app::events::EventType::k_quit)
	{
		m_isRunning = false;
	}
}

void SDLEngine::OnEvent(const app::events::KeyEvent& i_event)
{
	switch (i_event.GetKeycode())
	{
	case app::events::KeyEvent::KeycodeType::k_esc:
		m_isRunning = false;
		break;
	case app::events::KeyEvent::KeycodeType::k_space:
		m_input.space = true;
		break;
	case app::events::KeyEvent::KeycodeType::k_left:
		m_input.left = true;
		break;
	case app::events::KeyEvent::KeycodeType::k_right:
		m_input.right = true;
		break;
	case app::events::KeyEvent::KeycodeType::k_up:
		m_input.up = true;
		break;
	case app::events::KeyEvent::KeycodeType::k_down:
		m_input.down = true;
		break;

	default:
		break;
	}
}

bool SDLEngine::Run()
{
	sdl::policy::EventDispatch::ProcessAndDispatch(*this);

	return m_isRunning;
}