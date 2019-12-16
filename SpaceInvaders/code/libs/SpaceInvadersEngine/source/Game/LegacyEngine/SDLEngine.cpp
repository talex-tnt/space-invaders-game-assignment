#include "SDLEngine.h"

#include <Game/Graphics/Renderer2D.h>
#include <Game/Graphics/TextureMgr.h>
#include <Game/Graphics/TextRenderer.h>
#include <Game/Graphics/Display.h>
#include <Game/Graphics/SpriteAtlasProvider.h>
#include <Game/Graphics/SpriteRenderer.h>

#include "../Base/Assets/Fonts.h"
#include "../Base/Assets/Textures.h"
#include "../Base/Assets/Sprites.h"

namespace game
{
namespace graphics
{
class SpriteAtlasMgr : public SpriteAtlasProvider
{
public:
	SpriteAtlasMgr::SpriteAtlasMgr(TextureMgr& i_textureMgr)
		: SpriteAtlasProvider(i_textureMgr) { }
	using SpriteAtlasProvider::LoadSpriteAtlas;
	using SpriteAtlasProvider::LoadSpriteAtlases;
};
}
}

SDLEngine::SDLEngine()
	: m_isRunning(sdl::policy::Initialization::Init())
{
	GraphicsProvider::InitGraphics(*this);
	if (GraphicsProvider::RendererT* renderer = GraphicsProvider::GetRenderer())
	{
			m_renderer = std::make_unique<RendererT>(*renderer);
			if (m_renderer->Init() == false)
			{
				std::cerr << "Error: could or init Renderer" << std::endl;
			}
	}
	if (const GraphicsProvider::DisplayT* display = GraphicsProvider::GetDisplay())
	{
		m_display = std::make_unique<DisplayT>(*display);
	}
	if (const GraphicsProvider::TextureFactoryT* textureFactory = GraphicsProvider::GetTextureFactory())
	{
		m_textureMgr = std::make_unique<TextureMgrT>(*textureFactory);
		m_renderer->SetTextureMgr(*m_textureMgr);
		//
		m_textureMgr->CreateTextures(game::assets::Textures::GetAllTextures());

		m_spriteAtlasMgr = std::make_unique<SpriteAtlasMgrT>(*m_textureMgr);
		m_spriteAtlasMgr->LoadSpriteAtlases(game::assets::Sprites::Atlases::GetAllAtlases());

		m_spriteRenderer = std::make_unique<SpriteRendererT>(*m_renderer);
	}
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