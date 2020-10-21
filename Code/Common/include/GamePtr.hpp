#pragma once

#include <Windows.h>
#include <utility>
#include <cstdint>

namespace Common {
    
    class GamePtr_Manager {
    public:
        GamePtr_Manager();

        static uintptr_t	s_baseAddress;
    };

    template<typename T>
    class GamePtr {
        uintptr_t offset;

        GamePtr();
        GamePtr(GamePtr& rhs);
        GamePtr& operator = (GamePtr& rhs);
    public:
        GamePtr(uintptr_t offset);

        [[nodiscard]] T* GetPtr() const { return reinterpret_cast <T*>(offset); };

        [[nodiscard]] T* operator->() const { return GetPtr(); }

        [[nodiscard]] operator T* () const { return GetPtr(); }

        [[nodiscard]] bool operator!() const { return !GetPtr(); }

        [[nodiscard]] const T* GetConstPtr() const { return reinterpret_cast<T*>(offset) }

        [[nodiscard]] uintptr_t GetIntPtr() const { return offset; }
    };

    template<typename T>
    inline GamePtr<T>::GamePtr(uintptr_t offset)
    {
        this->offset = offset + Common::GamePtr_Manager::s_baseAddress;
    }

  



}