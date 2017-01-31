#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "adsr.h"

using namespace std;

#ifndef SONG_H
#define SONG_H

class Song {
	
	public:
		Song();
		
		void set_file_name(string);
		string get_file_name();
		
		void set_file_type(string);
		string get_file_type();
		
		void set_sample_rate(int);
		int get_sample_rate();
		
		void set_bit_depth(int);
		int get_bit_depth();
		
		void set_num_channels(int);
		int get_num_channels();
		
		void set_num_samples(int);
		int get_num_samples();
		
		void set_length_sound(float);
		float get_length_sound();
		
		void set_data(string);
		string get_data();
		void add_data(string);
		
		void set_wave_type(string);
		string get_wave_type();
		
		void set_frequency(float);
		float get_frequency();
		
		void set_pf(float);
		float get_pf();
		
		void set_peak_vol(float);
		float get_peak_vol();
		
		void print_info();
		int compare(Song);
		void nullify();
		int is_null();
		void join(Song);
		void join_mix(float, Song);
		void scale_data(float);
		string to_file();
		int gen_sample(int, adsr);
		
	private:
		string file_name;
		string file_type;
		int sample_rate;
		int bit_depth;
		int num_channels;
		int num_samples;
		float length_sound;
		string data;
		string wave_type;
		float frequency;
		float pf;
		float peak_vol;
};

#endif