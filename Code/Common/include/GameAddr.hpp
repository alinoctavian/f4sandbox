#pragma once
#include <Windows.h>
#include <utility>
#include <cstdint>

namespace Common {
	
	template <typename T>
	class GameAddr {
		struct ConversionType{};

		ConversionType* offset;

		GameAddr();
		GameAddr(GameAddr& rhs);
		GameAddr& operator=(GameAddr& rhs);
	public:
		//So we cast the address into the pointer type
		GameAddr(uintptr_t offset) {
			this->offset = reinterpret_cast<ConversionType*>(offset + Memory::GamePtr_Manager::s_baseAddress);
		}

		//This gets you the type in what you casted
		operator T() {
			return reinterpret_cast<T>(offset);
		}

		//This get's you the uintptr_t of that offset
		uintptr_t GetUIntPtr() {
			return reinterpret_cast<uintptr_t>(offset);
		}
	};
}