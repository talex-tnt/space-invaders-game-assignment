#include "SpaceInvadersEngine.h"
#include "SDLEngine.h"

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

void SpaceInvadersEngine::RenderSprite(Sprite sprite, int x, int y)
{
}

void SpaceInvadersEngine::RenderText(const char* message, int x, int y)
{
}

double SpaceInvadersEngine::GetElapsedSeconds() const
{
	return 0.0;
}

SpaceInvadersEngine::PlayerInput SpaceInvadersEngine::GetPlayerInput() const
{
	PlayerInput input;
	input.left = m_engine->GetInput().left;
	input.right = m_engine->GetInput().right;
	input.fire = m_engine->GetInput().space;
	return input;
}