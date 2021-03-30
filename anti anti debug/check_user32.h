#pragma once
#include "check_nt.h"

namespace ui_check
{
	HMODULE get_win32udll();
	std::uint64_t* func_address( std::string );
	bool detect_hooks( std::uint64_t* );
	void check_funcs( const std::vector<std::string>& );
}