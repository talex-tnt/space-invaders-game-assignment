#include <Game/LegacyEngine/SpaceInvadersEngine.h>
#include "SDLEngine.h"

#include <Game/Graphics/Renderer2D.h>
#include <Game/Graphics/TextureMgr.h>
#include <Game/Graphics/TextRenderer.h>
#include <Game/Graphics/Display.h>
#include <Game/Graphics/SpriteAtlasProvider.h>
#include <Game/Graphics/SpriteRenderer.h>

SpaceInvadersEngine::SpaceInvadersEngine() 
	: m_engine(std::make_unique<SDLEngine>())
{

}

SpaceInvadersEngine::~SpaceInvadersEngine()
{
}

bool SpaceInvadersEngine::Run() 
{
	return m_engine->Run();
}

void SpaceInvadersEngine::RenderSprite(Sprite sprite, int x, int y) const 
{
}

void SpaceInvadersEngine::RenderText(const char* message, int x, int y) const
{
	using Pos = game::graphics::TextRenderer::Pos;
	m_engine->GetTextRenderer().RenderText(std::string(message),Pos(static_cast<Pos::value_type>(x), static_cast<Pos::value_type>(y)), FontRowHeight);
}

double SpaceInvadersEngine::GetElapsedSeconds() const
{
	return m_engine->GetClock().GetElaspsedSeconds().count();
}

int SpaceInvadersEngine::GetTextSize(const char* message) const
{
	//m_engine->GetTextRenderer()
	return 0;
}

SpaceInvadersEngine::PlayerInput SpaceInvadersEngine::GetPlayerInput() const
{
	PlayerInput input;
	input.left = m_engine->GetInput().left;
	input.right = m_engine->GetInput().right;
	input.fire = m_engine->GetInput().space;
	return input;
}