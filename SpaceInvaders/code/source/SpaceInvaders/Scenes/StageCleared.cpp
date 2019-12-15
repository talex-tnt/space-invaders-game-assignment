#include "StageCleared.h"
#include "../GameContext.h"
#include <initializer_list>
#include <utility>

namespace 
{
static const graphics::TextRenderer::String k_stageClearedMessage("Congratulation!! Stage Cleared!");
static const graphics::TextRenderer::String k_pressToReplayMessage("Press Any Key To Play Again");
static const spaceinv::Seconds k_waitTime = 1.f;
bool IsAnyKeyPressed(const platform::Input& i_input);
}

namespace spaceinv
{
namespace scenes
{

StageCleared::StageCleared(const GameContext& i_context)
	: m_renderer(i_context.GetTextRenderer())
	, m_input(i_context.GetInput())
	, m_elapsedTime(0.f)
{
	const utils::Size displaySize = i_context.GetDisplay().GetSize();

	using Pair = std::pair<const graphics::TextRenderer::String&, Position*>;
	const utils::Size fontSize = i_context.GetTextRenderer().GetFontSize();
	Position::ValueT y = (displaySize.h - fontSize.h) / 2.f;
	for (Pair p : { std::make_pair(k_stageClearedMessage, &m_stageClearedMessagePos), std::make_pair(k_pressToReplayMessage, &m_replayMessagePos) })
	{
		const utils::Size textSize = i_context.GetTextRenderer().GetTextSize(p.first);
		p.second->Set(
			(displaySize.w - textSize.w) / 2.f,
			y);
		y += fontSize.h;
	}
}


void StageCleared::Init()
{
	m_elapsedTime = 0.f;
}

void StageCleared::Update(Seconds i_deltaTime)
{
	m_elapsedTime += i_deltaTime;
}

void StageCleared::Render() const
{
	m_renderer.Render(k_stageClearedMessage, m_stageClearedMessagePos);
	if (IsWaitOver())
	{
		m_renderer.Render(k_pressToReplayMessage, m_replayMessagePos);
	}
}

bool StageCleared::IsEnded() const
{
	return IsWaitOver() && IsAnyKeyPressed(m_input);
}

bool StageCleared::IsWaitOver() const
{
	return m_elapsedTime > k_waitTime;
}

}
}

namespace
{
bool IsAnyKeyPressed(const platform::Input& i_input)
{
	const platform::Input::ValueT leftValue = i_input.GetAction(platform::Input::Action::Left);
	const platform::Input::ValueT rightValue = i_input.GetAction(platform::Input::Action::Right);
	const platform::Input::ValueT fireValue = i_input.GetAction(platform::Input::Action::Fire);
	return (leftValue + rightValue + fireValue) != 0;
}
}