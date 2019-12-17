#include <Game/LegacyEngine/SpaceInvadersEngine.h>
#include "SDLEngine.h"

#include <Game/Graphics/Renderer2D.h>
#include <Game/Graphics/TextureMgr.h>
#include <Game/Graphics/TextRenderer.h>
#include <Game/Graphics/Display.h>
#include <Game/Graphics/SpriteAtlasProvider.h>
#include <Game/Graphics/SpriteRenderer.h>
#include "../Base/Assets/Sprites.h"
#include <AppUtils/Enum.h>

SpaceInvadersEngine::SpaceInvadersEngine() 
	: m_engine(std::make_unique<SDLEngine>("Space Invaders", CanvasWidth, CanvasHeight))
{
	using Sprites = game::assets::Sprites;
	using Enum = app::utils::Enum;
	Enum::SetArrayValue(m_sprites, Sprite::Player, m_engine->GetAtlasProvider().GetSpriteAtlas(Sprites::Atlases::k_invaders)->GetSprite(Sprites::k_ship));
	Enum::SetArrayValue(m_sprites, Sprite::Enemy1, m_engine->GetAtlasProvider().GetSpriteAtlas(Sprites::Atlases::k_invaders)->GetSprite(Sprites::k_invader01));
	Enum::SetArrayValue(m_sprites, Sprite::Enemy2, m_engine->GetAtlasProvider().GetSpriteAtlas(Sprites::Atlases::k_invaders)->GetSprite(Sprites::k_invader02));
	Enum::SetArrayValue(m_sprites, Sprite::Rocket, m_engine->GetAtlasProvider().GetSpriteAtlas(Sprites::Atlases::k_invaders)->GetSprite(Sprites::k_projectile));
	Enum::SetArrayValue(m_sprites, Sprite::Bomb, m_engine->GetAtlasProvider().GetSpriteAtlas(Sprites::Atlases::k_invaders)->GetSprite(Sprites::k_explosion));
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
	using Rect = game::graphics::SpriteRenderer::Rect;
	SpriteT::Pos pos{ static_cast<float>(x), static_cast<float>(y) };
	const Rect rect{ pos , m_spriteSize };
	using Enum = app::utils::Enum;
	m_engine->GetSpriteRenderer().Render(rect, Enum::GetArrayValue(m_sprites, sprite));
}

void SpaceInvadersEngine::RenderText(const char* message, int x, int y) const
{
	using Pos = game::graphics::TextRenderer::Pos;
	Pos pos{ static_cast<float>(x), static_cast<float>(y) };
	m_engine->GetTextRenderer().RenderText(std::string(message), pos, FontRowHeight);
}

double SpaceInvadersEngine::GetElapsedSeconds() const
{
	return m_engine->GetClock().GetElaspsedSeconds().count();
}

int SpaceInvadersEngine::GetTextSize(const char* message) const
{
	//m_engine->GetTextRenderer()
	return 100;
}

SpaceInvadersEngine::PlayerInput SpaceInvadersEngine::GetPlayerInput() const
{
	PlayerInput input;
	input.left = m_engine->GetInput().left;
	input.right = m_engine->GetInput().right;
	input.fire = m_engine->GetInput().space;
	return input;
}