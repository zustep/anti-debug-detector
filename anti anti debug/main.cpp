#include <Windows.h>
#include <iostream>
#include <string>
#include "misc.h"
#include "check_nt.h"
#include "check_user32.h"
#include "check_regions.h"

void main()
{
    misc::create_console();

    const std::vector<std::string> nt_functions =
    {
        "NtQueryInformationProcess",
        "NtQuerySystemInformation",
        "NtSetInformationThread",
        "NtSetInformationProcess",
        "NtQueryObject",
        "NtYieldExecution",
        "NtCreateThreadEx",
        "NtClose",
        "NtSetContextThread",
        "NtGetContextThread",
        "NtContinue",
        "NtSetDebugFilterState",
        "NtQueryPerformanceCounter"
    };

    const std::vector<std::string> ui_functions =
    {
        "NtUserFindWindowEx",
        "NtUserQueryWindow",
        "NtUserBuildHwndList"
    };

    nt_check::check_funcs( nt_functions );
    ui_check::check_funcs( ui_functions );

    std::printf( "\n" );

    check_regions::query_info();
}

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved ) 
{
    switch ( fdwReason )
    {
    case DLL_PROCESS_ATTACH:
        CreateThread( 0, 0, LPTHREAD_START_ROUTINE( main ), 0, 0, 0 );
        break;
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE; 
}