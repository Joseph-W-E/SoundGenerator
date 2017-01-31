#include "util.h"

using namespace std;

int main(int argc, char *argv[]) {
	string output_file_name = "";
	Song output_song;
	
	// READ COMMAND LINE ARGUMENTS
	if (argc < 2) {
		// Since the user only typed "./sndcat", we want to read from stdin
		cout << "Reading from stdin: " << endl;
		string argument = "";
		bool first = true;
		while (1) {
			getline(cin, argument);
			if (argument.compare("-h") == 0) {
				print_help("sndcat");
				return 0;
			} else if (argument.compare("quit") == 0) {
				break;
			} else if (argument[0] == '-' && argument[1] == 'o') {
				// we making the output file now
				stringstream ss(argument);
				string flag = "";
				ss >> flag >> output_file_name;
			} else {
				if (first) {
					output_song = analyze_file(argument);
					first = false;
				} else {
					output_song.join(analyze_file(argument));
				}
			}
		}
	} else {
		// The user typed more than "./sndcat", so we want to check for -h
		for (int i = 0; i < argc; i++) {
			string argument = argv[i];
			if (argument.compare("-h") == 0) {
				print_help("sndcat");
				return 0;
			}
		}
		
		
		bool first = true;
		// They didn't enter -h, so we can start gathering the songs we want to join
		for (int i = 1; i < argc; i++) {
			string argument = argv[i];
			if (argument.compare("-o") == 0) {
				// They specified an output file
				// The next argument is the one we want
				if (i + 1 < argc) {
					output_file_name = argv[i+1];
					i++;
				} 
			} else {
				if (first) {
					output_song = analyze_file(argument);
					first = false;
				} else {
					output_song.join(analyze_file(argument));
				}
			}
		}
		
		
		
	}
	
	if (output_file_name.compare("") != 0) {
		// create the output file
		ofstream oss(output_file_name.c_str());
		
		// write all the information to it
		oss << output_song.to_file();
		
		// close the file
		oss.close();
	} else {
		cout << output_song.to_file();
	}
	
	return 0;
}



















