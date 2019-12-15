#include "Intro.h"
#include "../GameContext.h"

namespace 
{
static const graphics::TextRenderer::String k_message("Press Any Key To Start");
bool IsAnyKeyPressed(const platform::Input& i_input);
}

namespace spaceinv
{
namespace scenes
{

Intro::Intro(const GameContext& i_context)
	: m_renderer(i_context.GetTextRenderer())
	, m_input(i_context.GetInput())
	, m_textSize(i_context.GetTextRenderer().GetTextSize(k_message))
{
	const utils::Size displaySize = i_context.GetDisplay().GetSize();
	m_position.Set(
		(displaySize.w - m_textSize.w) / 2.f,
		(displaySize.h - m_textSize.h) / 2.f);
}


void Intro::Update(Seconds /*i_deltaTime*/) { }

void Intro::Render() const
{
	m_renderer.Render(k_message, m_position);
}

bool Intro::IsEnded() const
{
	return IsAnyKeyPressed(m_input);
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