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
	return m_size;
}

bool string::empty() const noexcept
{
	return size() == 0u;
}

}
