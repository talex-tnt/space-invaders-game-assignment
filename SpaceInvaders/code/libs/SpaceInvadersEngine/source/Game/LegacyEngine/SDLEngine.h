#pragma once

#include <SDL/Policy/Initialization.h>
#include <SDL/Policy/EventDispatch.h>
#include <SDL/Policy/GraphicsProvider.h>
#include <AppEvents/IEventHandler.h>
#include <AppUtils/Clock.h>

namespace game
{
	namespace graphics
	{
		class Renderer2D;
		class Display;
		class TextRenderer;
		class SpriteRenderer;
		class TextureMgr;
		class SpriteAtlasMgr;
	}
}

// pretty rough draft..
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
	using RendererT = game::graphics::Renderer2D;
	using TextRendererT = game::graphics::TextRenderer;
	using SpriteRendererT = game::graphics::SpriteRenderer;
	using TextureMgrT = game::graphics::TextureMgr;
	using DisplayT = game::graphics::Display;
	using SpriteAtlasMgrT = game::graphics::SpriteAtlasMgr;
	using ClockT = app::utils::Clock;

	const RendererT& GetRenderer() const { return *m_renderer; }
	const TextRendererT& GetTextRenderer() const { return *m_textRenderer; }
	const SpriteRendererT& GetSpriteRenderer() const { return *m_spriteRenderer; }
	const SpriteAtlasMgrT& GetAtlasMgr() const { return *m_spriteAtlasMgr; }
	const DisplayT& GetDisplay() const { return *m_display; }
	const Input& GetInput() const;
	const ClockT& GetClock() const { return m_clock; }

public:
	void OnEventDispatchStarted() override;
	void OnEvent(app::events::EventType i_eventType) override;
	void OnEvent(const app::events::KeyEvent& i_event) override;

private:
	std::unique_ptr<RendererT> m_renderer;
	std::unique_ptr<TextureMgrT> m_textureMgr;
	std::unique_ptr<SpriteAtlasMgrT> m_spriteAtlasMgr;
	std::unique_ptr<DisplayT> m_display;
	std::unique_ptr<TextRendererT> m_textRenderer;
	std::unique_ptr<SpriteRendererT> m_spriteRenderer;
	app::utils::Clock m_clock;

	bool m_isRunning;
};

