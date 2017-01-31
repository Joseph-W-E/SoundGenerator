#include "util.h"

using namespace std;

int main(int argc, char *argv[]) {
	string output_file_name = "";
	Song output_song;
	
	// READ COMMAND LINE ARGUMENTS
	if (argc < 2) {
		// Since the user only typed "./sndmix", we want to read from stdin
		cout << "Reading from stdin: " << endl;
		string line = "";
		string s1 = "";
		string s2 = "";
		float value = 1.0;
		
		bool first = true;
		
		
		while (1) {
			getline(cin, line);
			stringstream ss(line);
			ss >> s1 >> s2;
			
			stringstream temp(s1);
			temp >> value;
			
			if (s1.compare("-h") == 0) {
				print_help("sndmix");
				return 0;
			} else if (s1.compare("-o") == 0) {
				output_file_name = s2;
			} else if (s1.compare("quit") == 0) {
				break;
			} else if (-10 <= value && value <= 10) {
				if (first) {
					output_song = analyze_file(s2);
					if (output_song.is_null() != 0) {
						output_song.scale_data(value);
						first = false;
					}
				} else {
					Song s = analyze_file(s2);
					output_song.join_mix(value, s);
				}
			} else {
				// they entered something they shouldn't have
				cout << "Error: invalid command '" << s1 << "'" << endl;
			}
		} // END STDIN LOOP
	} else {
		
		// The user typed more than "./sndmix", so we want to check for -h
		for (int i = 0; i < argc; i++) {
			string argument = argv[i];
			if (argument.compare("-h") == 0) {
				print_help("sndmix");
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
				stringstream ss(argument);
				float value = 1.0;
				ss >> value;
				if (-10 <= value && value <= 10) {
					if (first) {
						if (i + 1 < argc) {
							string arg2 = argv[i+1];
							output_song = analyze_file(arg2);
							i++;
						} else {
							output_song.nullify();
						}
						
						if (output_song.is_null() != 0) {
							output_song.scale_data(value);
							first = false;
						}
					} else {
						if (i + 1 < argc) {
							string arg2 = argv[i+1];
							Song s = analyze_file(arg2);
							output_song.join_mix(value, s);
							i++;
						}
						
					}
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