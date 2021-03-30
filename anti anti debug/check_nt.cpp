#include "check_nt.h"
#include <iostream>

HMODULE nt_check::get_ntdll()
{
	HMODULE ntdll = LoadLibraryA( "ntdll.dll" );

	if ( ntdll == NULL )
		MessageBoxA( 0, "LoadLibraryA ntdll", "error", MB_ICONERROR );
	
	return ntdll;
}

std::uint64_t* nt_check::func_address( std::string func_name )
{
	HMODULE ntdll = nt_check::get_ntdll();
	return ( std::uint64_t* )GetProcAddress( ntdll, func_name.c_str() );
}

bool nt_check::detect_hooks( std::uint64_t* func_adr )
{
	if ( *( BYTE* )func_adr != 0x4c ) // first byte of mov r10,rcx (4C:8BD1)
		return true;

	return false;
}

void nt_check::check_funcs( const std::vector<std::string>& functions )
{
	for ( auto func : functions )
	{
		auto adr = nt_check::func_address( func );

		if ( nt_check::detect_hooks( adr ) )
			std::printf( "Detected: %s\n", func.c_str() );
	}
}
