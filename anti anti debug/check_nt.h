#pragma once
#include <string>
#include <cinttypes>
#include <Windows.h>
#include <vector>

namespace nt_check
{
	HMODULE get_ntdll();
	std::uint64_t* func_address( std::string );
	bool detect_hooks( std::uint64_t* );
	void check_funcs( const std::vector<std::string>& );
}