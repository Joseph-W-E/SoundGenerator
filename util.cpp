#include "util.h"

/*
* Takes in a string, the file name, and analyzes it as a Song.
*/
Song analyze_file(string filename) {
	// REQUIRED HEADERS
	bool hasChannels = false;
	bool hasBitRes = false;
	bool hasSampleRate = false;
	
	// POSITION IN FILE
	char position = 0;
	
	// OTHER VARIABLES
	Song song;
	string line = "";
	ifstream file;
	int num_of_samples = 0;
	
	// Open the file
	file.open(filename.c_str(), ios::in);
	
	if (!file.is_open()) {
		// The file doesn't exist, throw an error.
		cout << "File '" << filename << "' doesn't exist." << endl;
		song.nullify();
	} else {
		// Get file_name and file_type
		int index = filename.find(".");
		song.set_file_name(filename.substr(0, index));
		song.set_file_type(filename.substr(index, filename.length()));
		
		// Attempt to read into line, break if you can't
		while (getline(file, line)) {
			// Formatting!
			line = to_lower_case(line);
			line = trim_spaces(line);
			// Ignore comments and blank lines
			if (line.c_str()[0] == '#' || line.length() < 1) {
				continue;
			}
			
			if (position == 0 && line.compare(CS229) == 0) {
				// LOOKING FOR CS229
				position++;
			} else if (position == 1) {
				// LOOKING FOR HEADERS
				stringstream ss(line);
				string header = "";
				string temp = "";
				int value = -1;
				
				ss >> header >> value >> temp;
				
				if (header.compare(SAMPLE_RATE) == 0 && temp.compare("") == 0) {
					hasSampleRate = true;
					song.set_sample_rate(value);
				} else if (header.compare(BIT_RES) == 0 && temp.compare("") == 0) {
					if (value != 8 && value != 16 && value != 32) {
						hasBitRes = false;
					} else {
						hasBitRes = true;
						song.set_bit_depth(value);
					}
				} else if (header.compare(CHANNELS) == 0 && temp.compare("") == 0) {
					if (value > 128) {
						hasChannels = false;
					} else {
						hasChannels = true;
						song.set_num_channels(value);
					}
				} else if (header.compare(SAMPLES) == 0 && temp.compare("") == 0) {
					song.set_num_samples(value);
				} else if (header.compare(STARTDATA) == 0 && temp.compare("") == 0) {
					position++;
				} else {
					position++;
					hasSampleRate = false;
					hasBitRes = false;
					hasChannels = false;
				}
			} else if (position == 2) {
				// LOOKING FOR DATA
				stringstream ss(line);
				int counter = 0;
				int value = 0;
				string d = "";
				while(ss >> value) {
					counter++;
					if (song.get_bit_depth() == 8) {
						if (value < -127 || value > 128) {
							hasChannels = false;
						}
					} else if (song.get_bit_depth() == 16) {
						if (value < -32767 || value > 32768) {
							hasChannels = false;
						}
					} else {
						if (value < -2147483647 || value > 2147483648) {
							hasChannels = false;
						}
					}
					ostringstream oss;
					oss << value;
					song.set_data(song.get_data() + oss.str() + "\n");
				} // END READING DATA LINE
				if (counter != song.get_num_channels()) {
					// we found more data than there are channels, throw error
					hasChannels = false;
				}
				num_of_samples++;
			}
		} // END READING FILE
		
		if (hasSampleRate && hasBitRes && hasChannels && position == 2) {
			song.set_num_samples(num_of_samples);
			song.set_length_sound((float) song.get_num_samples() / (float) song.get_sample_rate());
		} else {
			cout << "Invalid file: " << filename << endl;
			song.nullify();
		}
	}
	
	file.close();
	return song;
}

/*
* If the user enters -h into the command line, then print out the help information.
*/
void print_help(string program) {
	if (program.compare("sndinfo") == 0) {
		cout << endl << "---HELP MENU---" << endl;
		cout << "Help:" << endl;
		cout << "   ./sndinfo <anything> -h <anything>" << endl;
		cout << "Standard In:" << endl;
		cout << "   ./sndinfo\n   filename.extension\n   -h\n   quit" << endl;
		cout << "Command Line:" << endl;
		cout << "   ./sndinfo filename.extension filename1.extension" << endl;
		cout << "Exiting:" << endl;
		cout << "    quit" << endl << endl;
	} else if (program.compare("sndcat") == 0) {
		cout << endl << "---HELP MENU---" << endl;
		cout << "Help:" << endl;
		cout << "   ./sndcat <anything> -h <anything>" << endl;
		cout << "Output File:" << endl;
		cout << "   ./sndcat -o outputfilename.extension" << endl;
		cout << "Standard In:" << endl;
		cout << "   ./sndcat\n   filename.extension\n   filename.extension\n   -o outputfilename.extension\n   quit" << endl;
		cout << "Command Line:" << endl;
		cout << "   ./sndcat filename.extension filename1.extension -o outputfilename.extension" << endl;
		cout << "Exiting:" << endl;
		cout << "   quit" << endl << endl;
	} else if (program.compare("sndmix") == 0) {
		cout << endl << "---HELP MENU---" << endl;
		cout << "Help:" << endl;
		cout << "   ./sndmix <anything> -h <anything>" << endl;
		cout << "Output File:" << endl;
		cout << "   ./sndmix -o outputfilename.extension" << endl;
		cout << "Multiplying:" << endl;
		cout << "   Only real numbers between -10 and 10 are allowed." << endl;
		cout << "Standard In:" << endl;
		cout << "   ./sndmix\n   number filename.extension\n   number filename.extension\n   -o outputfilename.extension\n   quit" << endl;
		cout << "Command Line:" << endl;
		cout << "   ./sndmix number filename.extension number filename1.extension -o outputfilename.extension" << endl;
		cout << "Exiting:" << endl;
		cout << "   quit" << endl << endl;
	} else if (program.compare("sndgen") == 0) {
		cout << endl << "---HELP MENU---" << endl;
		cout << "Help:" << endl;
		cout << "   ./sndgen <anything> -h <anything>" << endl;
		cout << "Flags:" << endl;
		cout << "   -h         : show the help screen" << endl;
		cout << "   -o         : specify the output file name" << endl;
		cout << "   --bits n   : use a bit depth of n" << endl;
		cout << "   --sr n     : use a sample rate of n" << endl;
		cout << "   -f r       : use a frequency of r Hz" << endl;
		cout << "   -t r       : total duration of r seconds" << endl;
		cout << "   -v p       : peak volume. 0 <= p <= 1" << endl;
		cout << "   -a r       : attack time of r seconds" << endl;
		cout << "   -d r       : decay time of r seconds" << endl;
		cout << "   -s p       : sustain volume. 0 <= p <= 1" << endl;
		cout << "   -r r       : release time of r seconds" << endl;
		cout << "   --sine     : generate a sine wave" << endl;
		cout << "   --triangle : generate a triangle wave" << endl;
		cout << "   --sawtooth : generate a sawtooth wave" << endl;
		cout << "   --pulse    : generate a pulse wave" << endl;
		cout << "   --pf p     : fraction of the time the pulse wave is 'up'" << endl << endl;
	} else {
		cout << "Error: wrong program specified" << endl;
	}
}

/*
* This trims the spaces on both the front and the back.
* I do not take credit for this function.
* Credit to: Evan Teran on stackoverflow.com
*/
string trim_spaces(string line) {
	// remove leading whitespace
	line.erase(line.begin(), find_if(line.begin(), line.end(), not1(ptr_fun<int, int>(isspace))));
	// remove trailing whitespace
	line.erase(find_if(line.rbegin(), line.rend(), not1(ptr_fun<int, int>(isspace))).base(), line.end());
	return line;
}

/*
* Enumerates through every character in the string and turns it to lowercase.
* Transform(InputIterator first, InputIterator last, OutputIterator result, UnaryOperator op);
*/
string to_lower_case(string line) {
	transform(line.begin(), line.end(), line.begin(), ::tolower);
	return line;
}