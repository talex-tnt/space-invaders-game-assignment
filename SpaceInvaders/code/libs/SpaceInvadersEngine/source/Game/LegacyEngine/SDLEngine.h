#pragma once

#include <SDL/Policy/Initialization.h>
#include <SDL/Policy/EventDispatch.h>
#include <SDL/Policy/GraphicsProvider.h>
#include <AppEvents/IEventHandler.h>

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
	using RendererT = game::graphics::Renderer2D;
	using TextRendererT = game::graphics::TextRenderer;
	using SpriteRendererT = game::graphics::SpriteRenderer;
	using TextureMgrT = game::graphics::TextureMgr;
	using DisplayT = game::graphics::Display;
	using SpriteAtlasMgrT = game::graphics::SpriteAtlasMgr;
private:
	std::unique_ptr<RendererT> m_renderer;
	std::unique_ptr<TextureMgrT> m_textureMgr;
	std::unique_ptr<SpriteAtlasMgrT> m_spriteAtlasMgr;
	std::unique_ptr<DisplayT> m_display;
	std::unique_ptr<TextRendererT> m_textRenderer;
	std::unique_ptr<SpriteRendererT> m_spriteRenderer;

	bool m_isRunning;
};

