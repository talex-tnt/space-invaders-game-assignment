#include "TextRenderer.h"
#include <Game/LegacyEngine/SpaceInvadersEngine.h>

#include <cmath>
#include <stdio.h>

namespace graphics
{

namespace
{
template<class NumberT>
typename std::enable_if<std::is_arithmetic<NumberT>::value>::type
SPrintFRender(const TextRenderer& i_textRenderer, const TextRenderer::Position& i_po, const TextRenderer::String& i_text, NumberT i_numbers...);
}

TextRenderer::TextRenderer(const SpaceInvadersEngine& i_engine)
	: m_engine(i_engine), m_fontSize{ SpaceInvadersEngine::FontWidth, SpaceInvadersEngine::FontRowHeight }
{
}

void TextRenderer::Render(const char* i_text, const Position& i_pos) const
{
	m_engine.RenderText(i_text,
		static_cast<int>(std::round(i_pos.GetX())),
		static_cast<int>(std::round(i_pos.GetY())));
}

void TextRenderer::Render(const String& i_text, const Position& i_pos) const
{
	m_engine.RenderText(i_text.c_str(),
		static_cast<int>(std::round(i_pos.GetX())),
		static_cast<int>(std::round(i_pos.GetY())));
}

void TextRenderer::Render(const String& i_text, int i_number, const Position& i_pos) const
{
	SPrintFRender(*this, i_pos, i_text, i_number);
}

void TextRenderer::Render(const String& i_text, std::size_t i_number, const Position& i_pos) const
{
	SPrintFRender(*this, i_pos, i_text, i_number);

}
void TextRenderer::Render(int i_number, const Position& i_pos) const
{
	SPrintFRender(*this, i_pos, "%d", i_number);
}

namespace
{
template<class NumberT>
typename std::enable_if<std::is_arithmetic<NumberT>::value>::type
SPrintFRender(const TextRenderer& i_textRenderer, const TextRenderer::Position& i_pos, const TextRenderer::String& i_text, NumberT i_numbers...)
{
	static const std::size_t size(32);
	char buffer[size];
	snprintf(buffer, size, i_text.c_str(), i_numbers);
	i_textRenderer.Render(buffer, i_pos);
}
}

graphics::Size TextRenderer::GetTextSize(const String& i_text) const
{
	const SpaceInvadersEngine::Size size = m_engine.GetTextSize(i_text.c_str());
	return graphics::Size{ size.w, size.h };
	//return graphics::Size{ i_text.size() * m_fontSize.w, m_fontSize.h };
}
}