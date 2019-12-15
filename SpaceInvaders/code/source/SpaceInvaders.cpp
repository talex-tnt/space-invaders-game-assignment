//#include "Engine.h"
#include "LegacyEngine/SpaceInvadersEngine.h"

#include "SpaceInvaders/Game.h"
#include "SpaceInvaders/GameContext.h"
#include "Utils/Stopwatch.h"

#include <thread>
#include <chrono>
#include <algorithm>

namespace
{
const std::size_t k_targetRefreshRate{ 60u };
const spaceinv::Seconds k_targetUpdateTime{ spaceinv::Seconds(1) / k_targetRefreshRate };
//
void WaitAndReset(utils::Stopwatch& stopwatch);
}

void EngineMain()
{
	SpaceInvadersEngine engine;
	while (engine.Run())
	{

	};
#if 0
	Engine engine;
	spaceinv::GameContext context(engine);
	spaceinv::Game game(context);

	utils::Stopwatch stopwatch(engine);
	while (engine.Start())
	{
		game.Update(k_targetUpdateTime);
		WaitAndReset(stopwatch);
		game.Render();
	}
#endif
}

namespace
{
void WaitAndReset(utils::Stopwatch& stopwatch)
{
	const spaceinv::Seconds waitTime = std::max(0., k_targetUpdateTime - stopwatch.GetElapsed());
	std::this_thread::sleep_for(std::chrono::duration<spaceinv::Seconds>(waitTime));
	stopwatch.Reset();
}
}