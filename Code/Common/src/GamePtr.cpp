#include "GamePtr.hpp"


#pragma warning(disable: 4073)
#pragma init_seg(lib)

static Common::GamePtr_Manager sRelocMngr;

uintptr_t Common::GamePtr_Manager::s_baseAddress = 0;

Common::GamePtr_Manager::GamePtr_Manager()
{
    Common::GamePtr_Manager::s_baseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
}
