#pragma once

#include <functional>
#include <string>

namespace program
{
	int start(std::function<void(std::string)> printer);
}

