#include "util.h"
#include "adsr.h"

using namespace std;

int main(int argc, char *argv[]) {
	string output_file_name = "";
	Song output_song;
	adsr envelope;
	
	// READ COMMAND LINE ARGUMENTS
	if (argc < 2) {
		//cout << "No flags entered." << endl;
		//return 0;
	} else {
		
		// The user typed more than "./sndmix", so we want to check for -h
		for (int i = 0; i < argc; i++) {
			string argument = argv[i];
			if (argument.compare("-h") == 0) {
				print_help("sndgen");
				return 0;
			}
		}
		
		// They didn't enter -h, so we can start gathering flags
		for (int i = 1; i < argc; i++) {
			string argument = argv[i];
			string argument2 = "";
			if (i + 1 < argc) {
				argument2 = argv[i+1];
			}
			
			stringstream ss(argument2);
			
			if ((argument.compare("-o") == 0) && (i + 1 < argc)) {
				ss >> output_file_name;
				i++;
			} else if ((argument.compare("--bits") == 0) && (i + 1 < argc)) {
				int bit_depth = 0;
				ss >> bit_depth;
				if (bit_depth != 8 && bit_depth != 16 && bit_depth != 32) {
					// error, need 8 16 or 32
					cout << "Error: Invalid Bit Depth" << endl;
					cout << "Needs to be 8, 16, or 32" << endl;
					return 0;
				}
				output_song.set_bit_depth(bit_depth);
				i++;
			} else if ((argument.compare("--sr") == 0) && (i + 1 < argc)) {
				int sample_rate = 0;
				ss >> sample_rate;
				output_song.set_sample_rate(sample_rate);
				i++;
			} else if ((argument.compare("-f") == 0) && (i + 1 < argc)) {
				float frequency = 0;
				ss >> frequency;
				output_song.set_frequency(frequency);
				i++;
			} else if ((argument.compare("-t") == 0) && (i + 1 < argc)) {
				float total_duration = 0;
				ss >> total_duration;
				output_song.set_length_sound(total_duration);
				i++;
			} else if ((argument.compare("-v") == 0) && (i + 1 < argc)) {
				float peak_volume;
				ss >> peak_volume;
				if (peak_volume < 0 || peak_volume > 1) {
					// error, need 0 <= peak_volue <= 1
					cout << "Error, Invalid Peak Volume (-v)" << endl;
					cout << "Needs to be 0 <= n <= 1" << endl;
					return 0;
				}
				output_song.set_peak_vol(peak_volume);
				i++;
			} else if ((argument.compare("-a") == 0) && (i + 1 < argc)) {
				float attack_time = 1;
				ss >> attack_time;
				envelope.set_attack_time(attack_time);
				i++;
			} else if ((argument.compare("-d") == 0) && (i + 1 < argc)) {
				float decay_time = 1;
				ss >> decay_time;
				envelope.set_decay_time(decay_time);
				i++;
			} else if ((argument.compare("-s") == 0) && (i + 1 < argc)) {
				float sustain_volume = 1;
				ss >> sustain_volume;
				if (sustain_volume < 0 || sustain_volume > 1) {
					// error, need 0 <= sustain_volume <= 1
					cout << "Error, Invalid Sustain Volume (-s)" << endl;
					cout << "Needs to be 0 <= n <= 1" << endl;
					return 0;
				}
				envelope.set_sustain_time_volume(sustain_volume);
				i++;
			} else if ((argument.compare("-r") == 0) && (i + 1 < argc)) {
				float release_time = 1;
				ss >> release_time;
				envelope.set_release_time(release_time);
				i++;
			} else if (argument.compare("--sine") == 0) {
				output_song.set_wave_type("sine");
			} else if (argument.compare("--triangle") == 0) {
				output_song.set_wave_type("triangle");
			} else if (argument.compare("--sawtooth") == 0) {
				output_song.set_wave_type("sawtooth");
			} else if (argument.compare("--pulse") == 0) {
				output_song.set_wave_type("pulse");
			} else if ((argument.compare("--pf") == 0) && (i + 1 < argc)) {
				float pf = 0.0;
				ss >> pf;
				if (pf < 0 || pf > 1) {
					// error, need 0 <= pf <= 1
					cout << "Error, Invalid Pulse Fraction (--pf)" << endl;
					cout << "Needs to be 0 <= n <= 1" << endl;
					return 0;
				}
				output_song.set_pf(pf);
				i++;
			}
		}
	}
	
	// So we have all the data that we need, time to make the wave
	output_song.set_num_samples(output_song.get_sample_rate() * output_song.get_length_sound());
	
	if (envelope.setup_adsr(output_song.get_length_sound(), output_song.get_peak_vol())) {
		//envelope.print_variables();
		for (int i = 0; i < output_song.get_num_samples(); i++) {
			// calculate all the samples
			int val = output_song.gen_sample(i, envelope);
			ostringstream oss;
			oss << val;
			output_song.add_data(oss.str());
		}
	} else {
		cout << "Error making adsr" << endl << endl;
	}
	
	//./sndgen --sr 4 --bits 8 -f 5.5 -t 10 -v .99 -a 1.1 -d 1.5 -s .75 -r .5 --pf .5 --triangle -o potato.txt
	//./sndgen --bits 32 --sr 1 -f 5.5 -t 8 -v 1 -a 2 -d 2 -s .5 -r 2 --sine
	
	
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