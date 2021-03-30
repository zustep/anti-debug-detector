#include <iostream>
#include <Windows.h>
#include "misc.h"

void misc::create_console()
{
    if (!AllocConsole()) {
        return;
    }
    FILE* fDummy;
    freopen_s( &fDummy, "CONOUT$", "w", stdout );
    freopen_s( &fDummy, "CONOUT$", "w", stderr );
    freopen_s( &fDummy, "CONIN$", "r", stdin );
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();
    HANDLE hConOut = CreateFile( L"CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    HANDLE hConIn = CreateFile( L"CONIN$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    SetStdHandle( STD_OUTPUT_HANDLE, hConOut );
    SetStdHandle( STD_ERROR_HANDLE, hConOut );
    SetStdHandle( STD_INPUT_HANDLE, hConIn );
    std::wcout.clear();
    std::wclog.clear();
    std::wcerr.clear();
    std::wcin.clear();
}