#pragma once
#include <memory>

class SDLEngine;
struct SpaceInvadersEngine 
{
	static const int CanvasWidth   = 640;
	static const int CanvasHeight  = 480;
	static const int SpriteSize    = 32;
	static const int FontWidth     = 8;
	static const int FontRowHeight = 18;
	
	struct PlayerInput
	{
		bool fire, left, right;
	};

	enum class Sprite : int
	{
		Player,
		Bomb,
		Rocket,
		Enemy1,
		Enemy2,
	};

	bool Run();
	void RenderSprite(Sprite sprite, int x, int y);
	void RenderText(const char* message, int x, int y);

	PlayerInput GetPlayerInput() const;
	double GetElapsedSeconds() const;
	
	SpaceInvadersEngine();
	~SpaceInvadersEngine();

private:
	std::unique_ptr<SDLEngine> m_engine;

};

