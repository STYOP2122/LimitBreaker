#include "main.hpp"

Plugin::Plugin(HMODULE hModule)
{
    moduleHandle = hModule;
    
    vehicleModelPool = {
        3140,
        4774, 4775, 4776, 4777, 4778, 4779, 4780, 4781, 4782, 4783,
        4784, 4785, 4786, 4787, 4788, 4789, 4790,

        5382, 5383, 5384, 5385, 5386, 5387, 5388,

        6830, 6835,

        12500, 12501, 12502, 12503, 12504, 12505, 12506, 12507, 12508, 12509,
        12510, 12511, 12513, 12514, 12515, 12516, 12517, 12518, 12519,
        12520, 12521, 12522, 12523, 12524, 12525, 12526, 12527, 12528, 12529,
        12530, 12531, 12532, 12533, 12534, 12535, 12536, 12537, 12538, 12539,
        12540, 12541, 12542, 12543, 12544, 12545, 12546, 12547, 12548, 12549,
        12550, 12551, 12552, 12553, 12554, 12555, 12556, 12557, 12558, 12559,
        12560, 12561, 12562, 12563, 12564, 12565, 12566, 12567, 12568, 12569,
        12570, 12571, 12572, 12573, 12574, 12575, 12576, 12577, 12578, 12579,
        12580
    };

    SAMPHandle = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("samp.dll"));

    InitializeLimitHooks();
    InitializeConnectHook();
    ChangeSAMPVersion();
}

Plugin::~Plugin()
{
    hook1.remove();
}

void Plugin::InitializeLimitHooks()
{
    hook1.set_dest(SAMPHandle + 0xE40D);
    hook1.set_cb([this](const kthook::kthook_naked& hook)
    {
        auto modelId = static_cast<std::uint16_t>(hook.get_context().eax);
        if (modelId < 611)
        {
            hook.get_return_address() = SAMPHandle + 0xE418;            
        }
        else
        {
            for (auto& input : vehicleModelPool) 
            {
                if (modelId == input)
                {
                    hook.get_return_address() = SAMPHandle + 0xE418;
                    return;
                }
            }

            hook.get_return_address() = SAMPHandle + 0xE53F;
        }   
    });
    hook1.install();

    hook2.set_dest(SAMPHandle + 0x9F3AD);
    hook2.set_cb([this](const kthook::kthook_naked& hook)
    {
        auto modelId = static_cast<std::uint16_t>(hook.get_context().eax & 0xFFFF);
        if (modelId < 611)
        {
            hook.get_return_address() = SAMPHandle + 0x9F3B3;            
        }
        else
        {
            for (auto& input : vehicleModelPool) 
            {
                if (modelId == input)
                {
                    hook.get_return_address() = SAMPHandle + 0x9F3B3;
                    return;
                }
            }

            hook.get_return_address() = SAMPHandle + 0x9F3BE;
        }
    });
    hook2.install();

    hook3.set_dest(SAMPHandle + 0x9F43F);
    hook3.set_cb([this](const kthook::kthook_naked& hook)
    {
        auto modelId = static_cast<std::uint16_t>(hook.get_context().eax & 0xFFFF);
        if (modelId < 611)
        {
            hook.get_return_address() = SAMPHandle + 0x9F445;            
        }
        else
        {
            for (auto& input : vehicleModelPool) 
            {
                if (modelId == input)
                {
                    hook.get_return_address() = SAMPHandle + 0x9F445;
                    return;
                }
            }

            hook.get_return_address() = SAMPHandle + 0x9F449;
        }
    });
    hook3.install();

    hook4.set_dest(SAMPHandle + 0x09F46A);
    hook4.set_cb([this](const kthook::kthook_naked& hook)
    {
        auto modelId = static_cast<std::uint16_t>(hook.get_context().eax & 0xFFFF);
        printf("4modelId: %d\n", modelId);
        if (modelId < 611)
        {
            hook.get_return_address() = SAMPHandle + 0x9F470;            
        }
        else
        {
            for (auto& input : vehicleModelPool) 
            {
                if (modelId == input)
                {
                    hook.get_return_address() = SAMPHandle + 0x9F470;
                    return;
                }
            }

            hook.get_return_address() = SAMPHandle + 0x9F485;
        }
    });
    hook4.install();

    hook5.set_dest(SAMPHandle + 0xB2D2E);
    hook5.set_cb([this](const kthook::kthook_naked& hook)
    {
        auto modelId = static_cast<std::uint16_t>(hook.get_context().eax & 0xFFFF);
        if (modelId < 611)
        {
            hook.get_return_address() = SAMPHandle + 0xB2D34;            
        }
        else
        {
            for (auto& input : vehicleModelPool) 
            {
                if (modelId == input)
                {
                    hook.get_return_address() = SAMPHandle + 0xB2D34;
                    return;
                }
            }

            hook.get_return_address() = SAMPHandle + 0xB2D6D;
        }
    });
    hook5.install();

    DWORD targetAddr = SAMPHandle + 0xAA130;
    patch::PutRetn(targetAddr);
}

void Plugin::InitializeConnectHook()
{
    RakClient__ConnectHook.set_dest(SAMPHandle + 0x339F0);
    RakClient__ConnectHook.set_cb([this](const decltype(RakClient__ConnectHook)& hook, void* rakClient, char* host, auto&&... args)
    {
        if (std::strcmp(host, "51.83.49.125") != 0 && std::strcmp(host, "127.0.0.1") != 0)
        { 
            exit(0);
        }

        hook.get_trampoline()(rakClient, host, args...);
    });
    RakClient__ConnectHook.install();
}

void Plugin::ChangeSAMPVersion()
{
    memwrapper::write_memory<std::uint8_t>(SAMPHandle + 0xAC67, 8);
    memwrapper::write_memory(SAMPHandle + 0xAC70, "Omega RP");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID) {
	if (dwReasonForCall == DLL_PROCESS_ATTACH) {
		plugin = std::make_unique<Plugin>(hModule);
	}
	return TRUE;
}