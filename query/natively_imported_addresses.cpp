#include "query.hpp"

void query::natively_imported_addresses( std::string const& process_name )
{
    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    // Get a handle to the process.
    hProcess = process::get_handle_by_name( process_name.c_str( ) );

    if ( !hProcess )
    {
        printf( "Unable to read process\n" );
        return;
    }

    // Get a list of all the modules in this process.
    if ( K32EnumProcessModules( hProcess, hMods, sizeof( hMods ), &cbNeeded ) )
    {
        for ( i = 0; i < ( cbNeeded / sizeof( HMODULE ) ); i++ )
        {
            TCHAR szModName[MAX_PATH];

            // Get the full path to the module's file.
            GetModuleFileNameEx( hProcess, hMods[i], szModName, sizeof( szModName ) / sizeof( TCHAR ) );

            // Append all process module addresses.
            linked.push_back( hMods[i] );
        }
    }

    // Don't leak the handle.
    CloseHandle( hProcess );
}