#include "song.h"

// Constructors

Song::Song() {
	file_name = "potato";
	file_type = ".cs229";
	sample_rate = 40;
	bit_depth = 8;
	num_channels = 1;
	num_samples = 0;
	length_sound = 4;
	wave_type = "sine";
	frequency = 1.0;
	pf = 0.5;
	peak_vol = 1;
}

// Setters

void Song::set_file_name(string fn) {
	file_name = fn;
}
void Song::set_file_type(string ft) {
	file_type = ft;
}
void Song::set_sample_rate(int sr) {
	sample_rate = sr;
}
void Song::set_bit_depth(int bd) {
	bit_depth = bd;
}
void Song::set_num_channels(int nc) {
	num_channels = nc;
}
void Song::set_num_samples(int ns) {
	num_samples = ns;
}
void Song::set_length_sound(float ls) {
	length_sound = ls;
}
void Song::set_data(string d) {
	data = d;
}
void Song::set_wave_type(string wt) {
	wave_type = wt;
}
void Song::set_frequency(float f) {
	frequency = f;
}
void Song::set_pf(float p) {
	pf = p;
}
void Song::set_peak_vol(float pv) {
	peak_vol = pv;
}

// Getters

string Song::get_file_name() {
	return file_name;
}
string Song::get_file_type() {
	return file_type;
}
int Song::get_sample_rate() {
	return sample_rate;
}
int Song::get_bit_depth() {
	return bit_depth;
}
int Song::get_num_channels() {
	return num_channels;
}
int Song::get_num_samples() {
	return num_samples;
}
float Song::get_length_sound() {
	return length_sound;
}
string Song::get_data() {
	return data;
}
string Song::get_wave_type() {
	return wave_type;
}
float Song::get_frequency() {
	return frequency;
}
float Song::get_pf() {
	return pf;
}
float Song::get_peak_vol() {
	return peak_vol;
}

// Other functions
void Song::add_data(string s) {
	data += s;
	data += "\n";
}
/*
* Prints the useful information related to the song.
* Used in 'sndinfo'.
*/
void Song::print_info() {
	cout << "\n---FILE INFORMATION---\n";
	cout << "File Name    : " << file_name << endl;
	cout << "File Type    : " << file_type << endl;
	cout << "Sample Rate  : " << sample_rate << endl;
	cout << "Bit Depth    : " << bit_depth << endl;
	cout << "Num Channels : " << num_channels << endl;
	cout << "Num Samples  : " << num_samples << endl;
	cout << "Length Sound : " << length_sound << endl << endl;
}

/*
* Compares two songs.
* Returns 0 if the songs have the same channels, bitres, and sample rate.
* Returns -1 otherwise.
*/
int Song::compare(Song obj) {
	if (num_channels == obj.get_num_channels() && bit_depth == obj.get_bit_depth() && sample_rate == obj.get_sample_rate()) {
		return 0;
	} else {
		return -1;
	}
}

/*
* Makes the song "null".
*/
void Song::nullify() {
	file_name = "null";
	file_type = "null";
	sample_rate = -1;
	bit_depth = -1;
	num_channels = -1;
	num_samples = -1;
	length_sound = -1;
	data = "null";
}

/*
* Checks if the song has been "nullified".
*/
int Song::is_null() {
	if (file_name.compare("null") == 0
		&& file_type.compare("null") == 0
		&& sample_rate == -1
		&& bit_depth == -1
		&& num_channels == -1
		&& num_samples == -1
		&& length_sound == -1
		&& data.compare("null") == 0) {
		return 0;
	} else {
		return 1;
	}
}

/*
* Appends one song to another. Does nothing if they cannot join.
*/
void Song::join(Song obj) {
	if (num_channels == obj.get_num_channels() && bit_depth == obj.get_bit_depth() && sample_rate == obj.get_sample_rate()) {
		num_samples += obj.get_num_samples();
		length_sound = num_samples / sample_rate;
		data += obj.get_data();
	} else {
		cout << "Error: sound '" << obj.get_file_name() << obj.get_file_type() << "' could not be added." << endl;
	}
}

/*
* Combines the data of two songs. Does nothing if they cannot join.
*/
void Song::join_mix(float mult, Song obj) {
	if (num_channels == obj.get_num_channels() && bit_depth == obj.get_bit_depth() && sample_rate == obj.get_sample_rate()) {
		obj.scale_data(mult);
		// scan through the data of both songs
		stringstream ss1(data);
		stringstream ss2(obj.get_data());
		//float v1 = 0.0;
		//float v2 = 0.0;
		int v1 = 0;
		int v2 = 0;
		string l1 = "";
		string l2 = "";
		string new_data = "";
		
		//int samples_1 = num_samples;
		//int samples_2 = obj.get_num_samples();
		bool has_data_1 = true;
		bool has_data_2 = true;
		
		// while either one has data to offer...
		while (1) {
			// add the two data's together
			if (getline(ss1, l1)) {
				stringstream temp1(l1);
				temp1 >> v1;
			} else {
				has_data_1 = false;
			}
			
			if (getline(ss2, l2)) {
				stringstream temp2(l2);
				temp2 >> v2;
			} else {
				has_data_2 = false;
			}
			
			if (has_data_1 && has_data_2) {
				v1 += v2;
			} else if (has_data_1 && !has_data_2) {
				v1 = v1;
			} else if (!has_data_1 && has_data_2) {
				v1 = v2;
			} else {
				break;
			}
			
			// check to see if v1 is a valid piece
			if ((bit_depth == 8) && (v1 > 127)) {
				v1 = 127;
			} else if ((bit_depth == 8) && (v1 < -127)) {
				v1 = -127;
			} else if ((bit_depth == 16) && (v1 > 32765)) {
				v1 = 32765;
			} else if ((bit_depth == 16) && (v1 < -32765)) {
				v1 = -32765;
			} else if ((bit_depth == 32) && (v1 > 2147483647)) {
				v1 = 2147483647;
			} else if ((bit_depth == 32) && (v1 < -2147483647)) {
				v1 = -2147483647;
			}
			
			ostringstream oss;
			oss << v1;
			new_data += oss.str() + "\n";
		}
		data = new_data;
		num_samples = (num_samples >= obj.get_num_samples() ? num_samples : obj.get_num_samples() );
		
	} else {
		cout << "Error: sound '" << obj.get_file_name() << obj.get_file_type() << "' could not be added." << endl;
	}
}

/*
* Scales the data in a song by a given float.
*/
void Song::scale_data(float mult) {
	if (-10 <= mult && mult <= 10) {
		// go ahead and scale the data
		stringstream ss(data);
		string line = "";
		//float val = 0.0;
		int val = 0;
		string new_data = "";
		while (getline(ss, line)) {
			// we have a piece of data, now scale it
			// do not exceed the bitres requirement
			stringstream temp(line);
			temp >> val;
			val = val * mult;
			
			// check to see if v1 is a valid piece
			if ((bit_depth == 8) && (val > 127)) {
				val = 127;
			} else if ((bit_depth == 8) && (val < -127)) {
				val = -127;
			} else if ((bit_depth == 16) && (val > 32765)) {
				val = 32765;
			} else if ((bit_depth == 16) && (val < -32765)) {
				val = -32765;
			} else if ((bit_depth == 32) && (val > 2147483647)) {
				val = 2147483647;
			} else if ((bit_depth == 32) && (val < -2147483647)) {
				val = -2147483647;
			}
			
			ostringstream oss;
			oss << val;
			new_data += oss.str() + "\n";
		}
		data = new_data;
	}
}

/*
* Returns a string that is in the format of a .cs229 file.
*/
string Song::to_file() {
	ostringstream output;
	output << "Cs229" << endl;
	output << "Samples " << num_samples << endl;
	output << "Channels " << num_channels << endl;
	output << "BitRes " << bit_depth << endl;
	output << "SampleRate " << sample_rate << endl;
	output << "StartData" << endl;
	// Now we need to put in the data based on the number of channels
	
	stringstream ss(data);
	string line = "";
	int counter = 0;
	while (getline(ss, line)) {
		output << line;
		counter++;
		if (counter == num_channels) {
			output << endl;
			counter = 0;
		} else {
			output << " ";
		}
	}
	
	return output.str();
}

/*
* Generates a sample for a song based off the position in the total number of samples.
*/
int Song::gen_sample(int i, adsr envelope) {
	// This is the sample we are going to return
	int sample = 0;
	// This is used for scaling the -1 <= data <= 1 to a useable data value
	int scale = 0;
	
	// variables needed for the pulse wave
	static int up_counter = 0;
	static int down_counter = 0;
	static int up_or_down = 0; // 0 means up, 1 means down
	static float pulse_adsr_value = 0;
	float total_time_up = (float) num_samples * pf;
	float total_time_down = (float) num_samples - total_time_up;
	float seg_time_up = total_time_up / (frequency * length_sound);
	float seg_time_down = total_time_down / (frequency * length_sound);
	
	// These values are going to be between -1 and 1 due to the formula we are using
	float wave_value;
	float adsr_value;
	
	// This is the current time we are in. i is the sample we are at.
	// This is needed for where we are in the adsr envelope.
	float time = (float) i / (float) sample_rate;
	
	/*
	// If we are in a pulse, get the adsr_value for halfway through the segment
	if (wave_type.compare("pulse") == 0 && up_or_down == 0) {
		time = (float) (i + (int) (seg_time_up / 2)) / (float) sample_rate;
	} else if (wave_type.compare("pulse") == 0 && up_or_down == 1) {
		time = (float) (i + (int) (seg_time_down / 2)) / (float) sample_rate;
	}
	*/
	
	// Get the adsr value at 'time'
	if ((envelope.get_attack_time_start() <= time) && (time < envelope.get_attack_time_end())) {
		// we are in the attack phase
		adsr_value = envelope.get_attack_time_slope() * time;
	} else if ((envelope.get_decay_time_start() <= time) && (time < envelope.get_decay_time_end())) {
		// we are in the decay phase
		adsr_value = peak_vol + (envelope.get_decay_time_slope() * (time - envelope.get_decay_time_start()));
	} else if ((envelope.get_sustain_time_start() <= time) && (time < envelope.get_sustain_time_end())) {
		// we are in the sustain phase
		adsr_value = envelope.get_sustain_time_volume();
	} else if ((envelope.get_release_time_start() <= time) && (time < envelope.get_release_time_end())) {
		// we are in the release phase
		adsr_value = envelope.get_sustain_time_volume() + (envelope.get_release_time_slope() * (time - envelope.get_release_time_start()));
	}
	
	// First we are going to generate a wave value from -1 to 1
	// Credit for these formulas goes to Wikipedia. Much love <3
	if (wave_type.compare("sine") == 0) {
		wave_value = sin(2 * M_PI * frequency * time);
		//wave_value = 1;
	} else if (wave_type.compare("triangle") == 0) {
		// we need to flip if the wave_value exceeds the adsr_value for both + and -
		wave_value = 2 * fabs(2 * (frequency * time - floor(frequency * time + .5))) - 1;
	} else if (wave_type.compare("sawtooth") == 0) {
		wave_value = 2 * (frequency * time - floor(frequency * time + .5));
	} else if (wave_type.compare("pulse") == 0) {
		
		/*
		if ((up_counter == 0) && (up_or_down == 0)) {
			// we just started counting up, get the adsr
			pulse_adsr_value = adsr_value;
		} else if ((down_counter == 0) && (up_or_down == 1)) {
			// we just started counting down, get the adsr
			pulse_adsr_value = adsr_value;
		}
		*/
		
		
		if (up_or_down == 0) {
			// we are up
			wave_value = peak_vol;
			up_counter++;
		} else {
			// we are down
			wave_value = -1 * peak_vol;
			down_counter++;
		}
		
		if (up_counter >= seg_time_up) {
			// we reached the end of our up counter, flip sides
			up_counter = 0;
			up_or_down = 1;
		} else if (down_counter >= seg_time_down) {
			// we reached the end of our down counter, flip sides
			down_counter = 0;
			up_or_down = 0;
		}
	}
	
	// Scale the data (it's only  -1 <= data <= 1  right now)
	if (bit_depth == 8) {
		scale = 127;
	} else if (bit_depth == 16) {
		scale = 32765;
	} else if (bit_depth == 32) {
		scale = 2147483647;
	}
	
	if (wave_type.compare("sine") == 0) {
		//sample = wave_value * adsr_value * scale;
		sample = wave_value * adsr_value * scale;
	} else if (wave_type.compare("triangle") == 0) {
		// only flip if we reach the slope at the adsr_value
		sample = wave_value * adsr_value * scale;
	} else if (wave_type.compare("sawtooth") == 0) {
		sample = wave_value * adsr_value * scale;
	} else if (wave_type.compare("pulse") == 0) {
		//sample = wave_value * pulse_adsr_value * scale;
		sample = wave_value * adsr_value * scale;
	}
	
	return sample;
}










