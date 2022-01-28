#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

auto main ( ) -> int {
	std::string file_name;

	std::cout << "Enter file name > ";
	std::cin >> file_name;

	std::ifstream file ( file_name );
	if ( !file ) {
		std::cout << "Error when opening the file!\n";
		Sleep ( 3000 );
		return false;
	}

	std::string deobfuscated;
	bool is_variable_started = false;
	std::string line;

	while ( std::getline ( file, line ) ) {
		for ( auto actual_character : line ) {
			if ( actual_character == '%' ) { is_variable_started ^= 1; continue; }
			if ( !is_variable_started ) deobfuscated += actual_character;
		}
		deobfuscated += "\n";
	}

	file.close ( );

	bool is_bat_extension = file_name.substr ( file_name.find_last_of ( "." ) + 1) == "bat";
	std::string deobfuscated_file_name = ( is_bat_extension ? file_name.substr ( 0, file_name.size ( ) - 4 ) : file_name ) + "_deobfuscated.bat";

	std::ofstream deobfusacted_file ( deobfuscated_file_name );
	if ( !deobfusacted_file.is_open ( ) ) {
		std::cout << "Error when creating/opening the deobfuscated file!\n";
		Sleep ( 3000 );
		return false;
	}

	deobfusacted_file << deobfuscated << std::endl;
	deobfusacted_file.close ( );
	std::cout << "Successfully deobfuscated\n";
	Sleep ( 3000 );


	return false;
}