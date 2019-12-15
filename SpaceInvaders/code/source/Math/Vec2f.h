#pragma once

namespace math
{
// basic draft: minimal required interface

class Vec2f
{
public:
	using ValueT = float;

public:
	Vec2f() : m_x(0), m_y(0) {}
	explicit Vec2f(ValueT i_x, ValueT i_y) : m_x(i_x), m_y(i_y) {}

	const ValueT& GetX() const { return m_x; }
	const ValueT& GetY() const { return m_y; }

	ValueT& GetX() { return m_x; }
	ValueT& GetY() { return m_y; }

	void SetX(ValueT i_x) { m_x = i_x; }
	void SetY(ValueT i_y) { m_y = i_y; }

	void Set(ValueT i_x, ValueT i_y) { m_x = i_x; m_y = i_y; }

	Vec2f& operator+=(const Vec2f& rhs) { m_x += rhs.m_x; m_y += rhs.m_y; return *this; }

private:
	ValueT m_x, m_y;
};
}