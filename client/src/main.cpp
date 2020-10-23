#include <Windows.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <type_traits>
#include <string>
#include <thread>

#include <helpers.h>

DWORD WINAPI Main(LPVOID lpThreadParameter){
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

    F4S_LOG_INIT;

    F4S_LOG_INFO("F4Sandbox - 0.1");

    F4S_LOG_ERR("Test Error message");

    F4S_LOG_CRIT("Test Critical message");

    F4S_LOG_WARN("Test Warning message");

    return TRUE;
}

BOOL WINAPI Detach(){
    return TRUE;
}

BOOL APIENTRY DllMain(
        HMODULE hModule,
        DWORD ul_reason_for_call,
        LPVOID lpReserved)
{
    if(ul_reason_for_call == DLL_PROCESS_ATTACH){
       DisableThreadLibraryCalls(hModule);

       if ( auto handle = CreateThread(nullptr, NULL,Main,hModule,NULL,nullptr)){
            CloseHandle(handle);
       }
    }else if(ul_reason_for_call == DLL_PROCESS_DETACH){
     Detach();
    }

    return TRUE;
}