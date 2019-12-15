#pragma  once
#include "../Utils/Types.h"

namespace platform
{
class Display
{
public:
	using Size = utils::Size;

public:
	Size GetSize() const;

public:
	Display() = default;

	Display(const Display&) = delete;
	Display(Display&&) = delete;

	Display& operator=(const Display&) = delete;
	Display& operator=(Display&&) = delete;

private:
	//
};
}