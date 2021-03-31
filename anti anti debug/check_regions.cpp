#include "check_nt.h"
#include "check_regions.h"
#include <Windows.h>

void check_regions::query_info()
{
    MEMORY_BASIC_INFORMATION region = { 0 };
    for ( std::uint8_t* p = 0; VirtualQuery( p, &region, sizeof( region ) ) == sizeof( region );
        p += region.RegionSize )
    {
        if ( region.RegionSize == 0x1000 && ( region.AllocationProtect == PAGE_EXECUTE_READWRITE ) || ( region.AllocationProtect == PAGE_EXECUTE_READ ) )
            std::printf( "possible region for hooks: %p\n", region.BaseAddress );
    }
}