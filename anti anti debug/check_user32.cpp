#include "check_user32.h"

HMODULE ui_check::get_win32udll()
{
	HMODULE win32u = LoadLibraryA( "win32u.dll" );

	if ( win32u == NULL )
		MessageBoxA( 0, "LoadLibraryA win32u", "error", MB_ICONERROR );

	return win32u;
}

std::uint64_t* ui_check::func_address( std::string func_name )
{
	HMODULE win32u = ui_check::get_win32udll();
	return ( std::uint64_t* )GetProcAddress( win32u, func_name.c_str() );
}

bool ui_check::detect_hooks( std::uint64_t* func_adr )
{
	if ( *( BYTE* )func_adr != 0x4c) // first byte of mov r10,rcx (4C:8BD1)
		return true;

	return false;
}

void ui_check::check_funcs( const std::vector<std::string>& functions )
{
    for ( auto func : functions )
	{
        auto adr = ui_check::func_address( func );

        if ( ui_check::detect_hooks( adr ) )
            std::printf( "Detected: %s\n", func.c_str() );
    }
}

