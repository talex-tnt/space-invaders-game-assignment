#include <Game/LegacyEngine/SpaceInvadersEngine.h>

#include "SpaceInvaders/Game.h"
#include "SpaceInvaders/GameContext.h"
#include "Utils/Stopwatch.h"

#include <thread>
#include <chrono>
#include <algorithm>
#include <SDL.h>
#include <assert.h>

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif

namespace
{
const std::size_t k_targetRefreshRate{ 60u };
const spaceinv::Seconds k_targetUpdateTime{ spaceinv::Seconds(1) / k_targetRefreshRate };
//
void WaitAndReset(utils::Stopwatch& stopwatch);
}

#ifdef __EMSCRIPTEN__
struct RenderContext
{
	SpaceInvadersEngine* engine;
	spaceinv::Game* game;
};

void render(void *arg)
{
	RenderContext* ctx = static_cast<RenderContext*>(arg);
	if(ctx && ctx->engine && ctx->game)
	{
		if(ctx->engine->Run())
		{
			ctx->game->Update(k_targetUpdateTime);
			ctx->game->Render();
		} else {
    		emscripten_cancel_main_loop();
		}
	}
}
#endif

int main()
{
	SpaceInvadersEngine engine;
	spaceinv::GameContext context(engine);
	spaceinv::Game si_game(context);
	utils::Stopwatch stopwatch(engine);

#ifdef __EMSCRIPTEN__
		RenderContext ctx { &engine, &si_game};
		const int simulate_infinite_loop = 1;
		emscripten_set_main_loop_arg(render, &ctx, k_targetRefreshRate, simulate_infinite_loop);
#else
	while (engine.Run())
	{
		si_game.Update(k_targetUpdateTime);
		WaitAndReset(stopwatch);
		si_game.Render();
	};
#endif
	return EXIT_SUCCESS;
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