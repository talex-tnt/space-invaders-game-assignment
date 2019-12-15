#pragma  once
#include <cstddef>

namespace utils
{
struct Size
{
	using ValueT = std::size_t;
	ValueT w, h;
};
}