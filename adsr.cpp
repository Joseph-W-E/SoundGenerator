#include "adsr.h"

// Constructors

/*
* Default ADSR constructor. This makes an ADSR with 1 second per component.
*/
adsr::adsr() {
	attack_time = 1;
	decay_time = 1;
	sustain_time = 1;
	release_time = 1;
	
	attack_time_start = 0;
	decay_time_start = 1;
	sustain_time_start = 2;
	release_time_start = 3;
	
	attack_time_end = 1;
	decay_time_end = 2;
	sustain_time_end = 3;
	release_time_end = 4;
	
	attack_time_slope = 0;
	decay_time_slope = 0;
	sustain_time_volume = .5;
	release_time_slope = 0;
}

// GETTERS
float adsr::get_attack_time() {
	return attack_time;
}
float adsr::get_decay_time() {
	return decay_time;
}
float adsr::get_sustain_time() {
	return sustain_time;
}
float adsr::get_release_time() {
	return release_time;
}

float adsr::get_attack_time_start() {
	return attack_time_start;
}
float adsr::get_decay_time_start() {
	return decay_time_start;
}
float adsr::get_sustain_time_start() {
	return sustain_time_start;
}
float adsr::get_release_time_start() {
	return release_time_start;
}
		
float adsr::get_attack_time_end() {
	return attack_time_end;
}
float adsr::get_decay_time_end() {
	return decay_time_end;
}
float adsr::get_sustain_time_end() {
	return sustain_time_end;
}
float adsr::get_release_time_end() {
	return release_time_end;
}
		
float adsr::get_attack_time_slope() {
	return attack_time_slope;
}
float adsr::get_decay_time_slope() {
	return decay_time_slope;
}
float adsr::get_sustain_time_volume() {
	return sustain_time_volume;
}
float adsr::get_release_time_slope() {
	return release_time_slope;
}

// SETTERS
void adsr::set_attack_time(float x) {
	attack_time = x;
}
void adsr::set_decay_time(float x) {
	decay_time = x;
}
void adsr::set_sustain_time(float x) {
	sustain_time = x;
}
void adsr::set_release_time(float x) {
	release_time = x;
}

void adsr::set_attack_time_start(float x) {
	attack_time_start = x;
}
void adsr::set_decay_time_start(float x) {
	decay_time_start = x;
}
void adsr::set_sustain_time_start(float x) {
	sustain_time_start = x;
}
void adsr::set_release_time_start(float x) {
	release_time_start = x;
}
		
void adsr::set_attack_time_end(float x) {
	attack_time_end = x;
}
void adsr::set_decay_time_end(float x) {
	decay_time_end = x;
}
void adsr::set_sustain_time_end(float x) {
	sustain_time_end= x;
}
void adsr::set_release_time_end(float x) {
	release_time_end = x;
}

void adsr::set_attack_time_slope(float x) {
	attack_time_slope = x;
}
void adsr::set_decay_time_slope(float x) {
	decay_time_slope = x;
}
void adsr::set_sustain_time_volume(float x) {
	sustain_time_volume = x;
}
void adsr::set_release_time_slope(float x) {
	release_time_slope = x;
}

// Other functions
/*
* This initializes an ADSR given a total duration and a peak.
* Parameters:
*  float duration : total length of the sound
*  float peak : maximum volume of the sound
* Returns:
*  0 : failed to produced a valid ADSR
*  1 : produced a valid ADSR
*/
int adsr::setup_adsr(float duration, float peak) {
	if (get_release_time() > duration) {
		// No sound should be produced if the duration t is less than the release time
		return 0;
	}
	if (peak <= get_sustain_time_volume()) {
		// Otherwise the decay slope would be positive and that doesn't make sense
		return 0;
	}
	
	// If all of the times combined is bigger than how long the wave is, reduce them
	if ((get_attack_time() + get_decay_time() + get_release_time()) >= duration) {
		// Decay has the lowest precedence, so check if attack and release is too much
		if ((get_attack_time() + get_release_time()) >= duration) {
			// If the release time is exactly the same as duration, do it one way
			if (get_release_time() == duration) {
				// ZERO OUT EVERYTHING BUT RELEASE TIME
				set_attack_time_start(0);
				set_attack_time_end(0);
				set_attack_time(get_attack_time_end() - get_attack_time_start());
				set_attack_time_slope(0);
				
				set_decay_time_start(0);
				set_decay_time_end(0);
				set_decay_time(get_decay_time_end() - get_decay_time_start());
				set_decay_time_slope(0);
				
				set_sustain_time_start(0);
				set_sustain_time_end(0);
				set_sustain_time(get_sustain_time_end() - get_sustain_time_start());
				set_sustain_time_volume(peak);
				
				set_release_time_start(0);
				set_release_time_end(duration);
				set_release_time(get_release_time_end() - get_release_time_start());
				// Since the entire song is a release, it will be a negative slope.
				// The slope will be the rise over run, or peak over total time.
				set_release_time_slope( (-1) * (peak / get_release_time()) );
			} else {
				// THIS IS BROKEN
				// If release and attack are both too big, but release isn't big enough, shorten attack
				set_attack_time_start(0);
				set_attack_time_end(duration - get_release_time());
				set_attack_time(get_attack_time_end() - get_attack_time_start());
				set_attack_time_slope(peak / get_attack_time());
				
				set_decay_time_start(get_attack_time_end());
				set_decay_time_end(get_attack_time_end());
				set_decay_time(get_decay_time_end() - get_decay_time_start());
				set_decay_time_slope(0);
				
				set_sustain_time_start(get_decay_time_end());
				set_sustain_time_end(get_decay_time_end());
				set_sustain_time(get_sustain_time_end() - get_sustain_time_start());
				
				set_release_time_start(get_sustain_time_end());
				set_release_time_end(duration);
				set_release_time(get_release_time_end() - get_release_time_start());
				// Since the entire song is a release, it will be a negative slope.
				// The slope will be the rise over run, or peak over total time.
				set_release_time_slope( (-1) * (peak / get_release_time()) );
			}
		} else {
			// We need to shorten decay time now
			set_attack_time_start(0);
			set_attack_time_end(get_attack_time());
			set_attack_time(get_attack_time_end() - get_attack_time_start());
			set_attack_time_slope(peak / get_attack_time());
		
			set_decay_time_start(get_attack_time_end());
			set_decay_time_end(duration - get_attack_time() - get_release_time() + get_decay_time_start());
			set_decay_time(get_decay_time_end() - get_decay_time_start());
			set_decay_time_slope(-1 * (peak - get_sustain_time_volume()) / get_decay_time() );
			
			set_sustain_time_start(get_decay_time_end());
			set_sustain_time_end(get_decay_time_end());
			set_sustain_time(get_sustain_time_end() - get_sustain_time_start());
			set_sustain_time_volume(get_decay_time_slope() * get_decay_time() + peak);
			
			set_release_time_start(get_sustain_time_end());
			set_release_time_end(duration);	
			set_release_time(get_release_time_end() - get_release_time_start());
			// Since the entire song is a release, it will be a negative slope.
			// The slope will be the rise over run, or peak over total time.
			set_release_time_slope( (-1) * (get_sustain_time_volume() / get_release_time()) );
		}
	} else {
		// We are going to have a sustain time now
		set_attack_time_start(0);
		set_attack_time_end(get_attack_time());
		set_attack_time(get_attack_time_end() - get_attack_time_start());
		set_attack_time_slope(peak / get_attack_time());
	
		set_decay_time_start(get_attack_time_end());
		set_decay_time_end(get_decay_time_start() + get_decay_time());
		set_decay_time(get_decay_time_end() - get_decay_time_start());
		set_decay_time_slope(-1 * (peak - get_sustain_time_volume()) / get_decay_time() );
		
		set_sustain_time_start(get_decay_time_end());
		set_sustain_time_end(duration - get_attack_time() - get_decay_time() - get_release_time() + get_sustain_time_start());
		set_sustain_time(get_sustain_time_end() - get_sustain_time_start());
		
		set_release_time_start(get_sustain_time_end());
		set_release_time_end(duration);	
		set_release_time(get_release_time_end() - get_release_time_start());
		// Since the entire song is a release, it will be a negative slope.
		// The slope will be the rise over run, or peak over total time.
		set_release_time_slope( (-1) * (get_sustain_time_volume() / get_release_time()) );
	}
	
	return 1;
}

/*
* Displays to cout all the variables in an easy-to-read fashion.
*/
void adsr::print_variables() {
	cout << "attack_time         : " << attack_time << endl;
	cout << "decay_time          : " << decay_time << endl;
	cout << "sustain_time        : " << sustain_time << endl;
	cout << "release_time        : " << release_time << endl;
	
	cout << "attack_time_start   : " << attack_time_start << endl;
	cout << "attack_time_end     : " << attack_time_end << endl;
	cout << "attack_time_slope   : " << attack_time_slope << endl;
	
	cout << "decay_time_start    : " << decay_time_start << endl;
	cout << "decay_time_end      : " << decay_time_end << endl;
	cout << "decay_time_slope    : " << decay_time_slope << endl;
	
	cout << "sustain_time_start  : " << sustain_time_start << endl;
	cout << "sustain_time_end    : " << sustain_time_end << endl;
	cout << "sustain_time_volume : " << sustain_time_volume << endl;
	
	cout << "release_time_start  : " << release_time_start << endl;
	cout << "release_time_end    : " << release_time_end << endl;
	cout << "release_time_slope  : " << release_time_slope << endl;
}






































