#pragma once

#include <string>
#include "Hazel/Core/Core.h"

namespace Hazel {
	
	template<typename ... Args>
	std::string string_format(const std::string& format, Args ... args)
	{
		// get size
		int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...);
		HZ_CORE_ASSERT(size_s > 0, "Error during formatting.");
		auto size = static_cast<size_t>(size_s);
		// get buffer
		std::string buf;
		buf.resize(size);
		// fill buffer, size+1 for \0
		std::snprintf(buf.data(), size + 1, format.c_str(), args ...);
		return buf;
	}

}

