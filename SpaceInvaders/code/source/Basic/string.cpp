#include "string.h"

namespace basic
{

string::~string() = default;

string::const_pointer string::c_str() const
{
	return m_data;
}

std::size_t string::size() const noexcept
{
	static const std::size_t trailingNullTerminatorSize = 1u;
	return m_size > 0u ? m_size - trailingNullTerminatorSize : 0u;
}

bool string::empty() const noexcept
{
	return size() == 0u;
}

}
