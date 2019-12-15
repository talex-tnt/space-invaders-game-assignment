#pragma once
#include <cstddef>

namespace basic
{
// basic draft: minimal required interface
// to provide a reasonable level of abstraction over a char[]
class string
{
public:
	using const_pointer = const char*;

	template<std::size_t N>
	string(const char(&i_text)[N]) : m_data(i_text), m_size(N) {};
	~string();

	const_pointer c_str() const;
	std::size_t size() const noexcept;
	bool empty() const noexcept;

private:
	const_pointer m_data;
	const std::size_t m_size;
};

}