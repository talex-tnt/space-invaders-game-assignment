#pragma  once
#include "../Math/Vec2f.h"
#include "../Utils/Types.h"
#include "../Basic/string.h"

struct SpaceInvadersEngine;

namespace graphics
{
using Size = utils::Size;

class TextRenderer
{
public:
	using String = basic::string;
	using Position = math::Vec2f;
	
public:
	void Render(const char* i_text, const Position& i_pos) const;
	void Render(const String& i_text, const Position& i_pos) const;
	void Render(const String& i_text, int i_number, const Position& i_pos) const;
	void Render(int i_number, const Position& i_pos) const;
	void Render(const String& i_text, std::size_t i_number, const Position& i_pos) const;

	const Size& GetFontSize() const { return m_fontSize; }
	Size GetTextSize(const String& i_text) const;

public:
	TextRenderer(const SpaceInvadersEngine& i_engine);

	TextRenderer(const TextRenderer&) = delete;
	TextRenderer(TextRenderer&&) = delete;

	TextRenderer& operator=(const TextRenderer&) = delete;
	TextRenderer& operator=(TextRenderer&&) = delete;

private:
	const SpaceInvadersEngine& m_engine;
	const Size m_fontSize;
};
}