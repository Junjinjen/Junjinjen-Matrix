#pragma once
#include <string>
#include "rapidjson/writer.h"

namespace junjinjen_matrix
{
	namespace firmware
	{
		namespace utilities
		{
			namespace byte_string
			{
				using byte_string = std::basic_string<uint8_t>;
				using byte_string_buffer = rapidjson::GenericStringBuffer<rapidjson::UTF8<uint8_t>>;
			}
		}
	}
}
