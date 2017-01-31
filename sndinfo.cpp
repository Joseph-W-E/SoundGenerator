#include "util.h"

using namespace std;

int main(int argc, char *argv[]) {
	Song song;
	
	// READ COMMAND LINE ARGUMENTS
	if (argc < 2) {
		// Since the user only typed "./sndinfo", we want to read from stdin
		cout << "Reading from stdin: " << endl;
		string argument = "";
		while (1) {
			getline(cin, argument);
			if (argument.compare("-h") == 0) {
				print_help("sndinfo");
				return 0;
			} else if (argument.compare("quit") == 0) {
				break;
			} else {
				song = analyze_file(argument);
				if (song.is_null() != 0) {
					song.print_info();
				}
			}
		}
	} else {
		// The user typed more than "./sndinfo", so we want to check for -h
		for (int i = 0; i < argc; i++) {
			string argument = argv[i];
			if (argument.compare("-h") == 0) {
				print_help("sndinfo");
				return 0;
			}
		}
		
		// They didn't enter -h, so we can start analyzing the arguments
		for (int i = 1; i < argc; i++) {
			string argument = argv[i];
			song = analyze_file(argument);
			if (song.is_null() != 0) {
				song.print_info();
			}
		}
	}
	
	return 0;
}





































