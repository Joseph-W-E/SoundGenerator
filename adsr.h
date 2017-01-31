#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#ifndef adsr_H
#define adsr_H

class adsr {
	
	public:
		adsr();
		
		// Getters
		float get_attack_time();
		float get_decay_time();
		float get_sustain_time();
		float get_release_time();
		
		float get_attack_time_start();
		float get_decay_time_start();
		float get_sustain_time_start();
		float get_release_time_start();
		
		float get_attack_time_end();
		float get_decay_time_end();
		float get_sustain_time_end();
		float get_release_time_end();
		
		float get_attack_time_slope();
		float get_decay_time_slope();
		float get_sustain_time_volume();
		float get_release_time_slope();
		// Setters
		void set_attack_time(float);
		void set_decay_time(float);
		void set_sustain_time(float);
		void set_release_time(float);
		
		void set_attack_time_start(float);
		void set_decay_time_start(float);
		void set_sustain_time_start(float);
		void set_release_time_start(float);
		
		void set_attack_time_end(float);
		void set_decay_time_end(float);
		void set_sustain_time_end(float);
		void set_release_time_end(float);
		
		void set_attack_time_slope(float);
		void set_decay_time_slope(float);
		void set_sustain_time_volume(float);
		void set_release_time_slope(float);
		
		/*
		* This initializes an ADSR given a total duration and a peak.
		* Parameters:
		*  float duration : total length of the sound
		*  float peak : maximum volume of the sound
		* Returns:
		*  0 : failed to produced a valid ADSR
		*  1 : produced a valid ADSR
		*/
		int setup_adsr(float, float);
		
		/*
		* Displays to cout all the variables in an easy-to-read fashion.
		*/
		void print_variables();
	private:
	
		// Total lengths of each component in seconds.
		float attack_time;
		float decay_time;
		float sustain_time;
		float release_time;
	
		// Start times of each component in seconds after time 0.
		float attack_time_start;
		float decay_time_start;
		float sustain_time_start;
		float release_time_start;
		
		// End times of each component in seconds after time 0.
		float attack_time_end;
		float decay_time_end;
		float sustain_time_end;
		float release_time_end;
		
		// Slopes (and volume) of each component.
		float attack_time_slope;
		float decay_time_slope;
		float sustain_time_volume;
		float release_time_slope;
};

#endif