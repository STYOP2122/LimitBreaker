#pragma once

#include <memory>
#include <fstream>
#include <vector>
#include <filesystem>
#include <Windows.h>

#include "kthook/kthook.hpp"
#include "memwrapper/memwrapper.h"

namespace patch
{
    inline void PutRetn(std::uintptr_t address)
    {
        DWORD oldProtect;
        VirtualProtect(reinterpret_cast<LPVOID>(address), 1, PAGE_EXECUTE_READWRITE, &oldProtect);
        *reinterpret_cast<std::uint8_t*>(address) = 0xC3; // RET
        VirtualProtect(reinterpret_cast<LPVOID>(address), 1, oldProtect, &oldProtect);
    }
}

class Plugin
{
private:
    std::vector<std::uint16_t> vehicleModelPool;
    std::uintptr_t SAMPHandle;
    HMODULE moduleHandle;

    kthook::kthook_naked hook1;
    kthook::kthook_naked hook2;
    kthook::kthook_naked hook3;
    kthook::kthook_naked hook4;
    kthook::kthook_naked hook5;

    using RakClient__Connect_t = void(__thiscall*)(void* rakClient, char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer);  
    kthook::kthook_simple<RakClient__Connect_t> RakClient__ConnectHook;

public:
    Plugin(HMODULE hModule);
    ~Plugin();

    bool ReadConfig(std::string filePath);

    void InitializeLimitHooks();
    void InitializeConnectHook();
    void ChangeSAMPVersion();

    std::string GetCurrentDllName();
};

inline std::unique_ptr<Plugin> plugin;
