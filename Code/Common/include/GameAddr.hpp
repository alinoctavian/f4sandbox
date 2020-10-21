#pragma once


namespace Common {
	
	template <typename T>
	class GameAddr {
		struct ConversionType{};

		ConversionType* offset;

		GameAddr();
		GameAddr(GameAddr& rhs);
		GameAddr& operator=(GameAddr& rhs);
	public:
		GameAddr(uintptr_t offset) {
			this->offset = reinterpret_cast<ConversionType*>(offset + Memory::GamePtr_Manager::s_baseAddress);
		}

		operator T() {
			return reinterpret_cast<T>(offset);
		}

		uintptr_t GetUIntPtr() {
			return reinterpret_cast<uintptr_t>(offset);
		}
	};
}