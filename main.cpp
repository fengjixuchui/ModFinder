#include "Globals/include.hpp"

int main( )
{
	SetConsoleTitleA( "" );

	std::string process_name;

	std::cout << "Process name: ";
	std::getline( std::cin, process_name );

	if ( process_name.find( ".exe" ) == std::string::npos )
		process_name += ".exe";

	if ( HANDLE process_handle = process::get_handle_by_name( process_name.c_str( ) ) )
	{
		CloseHandle( process_handle );
		system( "cls" );
		query::natively_imported_addresses( process_name );
		query::memory_regions( process_name );
	}
	else
	{
		system( "cls" );
		std::cout << "Unable to parse process\nClosing in 2 seconds\n";
		std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
		exit( 0 );
	}
}