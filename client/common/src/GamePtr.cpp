#include "GamePtr.h"

#pragma warning(disable: 4073)
#pragma init_seg(lib)

static GamePtr_Manager sRelocMgr;

uintptr_t GamePtr_Manager::s_baseAddress = 0;

GamePtr_Manager::GamePtr_Manager(){
    GamePtr_Manager::s_baseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
}