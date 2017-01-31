Com Sci 327 Project 4

Fall 2015

Joseph Elliott



/*----------------------------------------
		CONTENTS
----------------------------------------*/

I. How To Compile

II. Program Descriptions
	IIa. sndinfo
	IIb. sndcat
	IIc. sndmix
	IId. sndgen

III. Source File Descriptions
	IIIa. adsr.cpp / adsr.h
	IIIb. song.cpp / song.h
	IIIc. util.cpp / util.h
	IIId. sndinfo.cpp
	IIIe. sndcat.cpp
	IIIf. sndmix.cpp
	IIIg. sndgen.cpp

/*----------------------------------------
		I. How To Compile
----------------------------------------*/

So you're trying to compile my project, huh?
All you need to do is navigate to directory with all the source files,
then type 'make'. This will make all four program compile at the same time.
To run each program, see II. Program Descriptions.

/*----------------------------------------
		II. Program Descriptions
----------------------------------------*/

IIa. sndinfo
	This displays info about .cs229 files.

	.cs229 files are passed as command line arguments.

	Note that you may enter any number of files in the command line.
	For example:
		./sndinfo sample0.cs229 sample1.cs229 sample2.cs229
	
	If not files are entered in the command line, then the program will read from cin.
	To terminate the program, simply enter 'quit' or press 'ctrl + c';

	**********
	IMPORTANT NOTE: As of 12/8/2015 at 3:26pm, Jim Lathrop stated that we may prompt 
	the user for files instead of requiring "./sndinfo < sample0.cs229".
	**********

	For example (note that lines with // are from cout):
	./sndinfo
	// reading from stdin
	sample0.cs229
	quit or 'ctrl + c'
	// ---FILE INFORMATION---
	// File Name    : sample0
	// File Type    : .cs229
	// Sample Rate  : 4
	// Bit Depth    : 16
	// Num Channels : 4
	// Num Samples  : 3
	// Length Sound : 0.75

	The following swithces are supported:
	'-h' : displays help information to cout, then termiantes the program.

IIb. sndcat
	This concatenates .cs229 files.

	.cs229 files are passed as command line arguments, where the files are concatenated 
	in order of entering them on the command line. Any number of files may be entered.
	
	For example:
		./sndcat sample0.cs229 sample1.cs229 sample2.cs229
	
	Input files MUST have the same sample rate, bit depth, and number of channels.
	If a file does not meet these requirements, it will not be concatenated to the 
	final output file.
	
	If no files are passed through the command line, then the program will read from cin.
	
	For example:
		./sndcat
		// reading from stdin
		sample0.cs229
		sample1.cs229
		sample2.cs229
		quit or 'ctrl + c'
	
	The following switches are supported:
	'-h' : displays help information to cout, then termiantes the program.
	'-o file.txt' : prints the final sound object to the designated file, otherwise to cout.
	

IIc. sndmix
	This mixes .cs229 files.
	
	.cs229 files are passed as command line arguments, where the files are mixed in 
	order of entering them on the command line. Any number of files may be entered.
	These files must be preceeded by a real number x where -10 <= x <= 10.
	
	For example:
		./sndmix 5 sample0.cs229 -0.5 sample1.cs229
	
	Input files MUST have the same sample rate, bit depth, and number of channels.
	If a file does not meet these requirements, it will not be mixed to the final 
	output file. Note that the number of samples does NOT need to be the same.
	The required sample rate, bit depth, and number of channels is based off of the 
	first file to be entered either on the command line or in cin.
	
	If no files are passed through the command line, then the program will read from cin.
	
	For example:
		./sndmix
		// reading from stdin
		5 sample0.cs229
		-0.5 sample1.cs229
		quit or 'ctrl + c'
		
	The following switches are supported:
	'-h' : displays help information to cout, then termintes the program.
	'-o file.txt' : prints the final sound object to the designated file, otherwise to cout.

	
IId. sndgen
	This produces a .cs229 file for a given waveform.
	
	A number of switches may be entered on the command line to specify exactly what 
	kind of sound file to produce. There are default values that, in the event the 
	user enters only './sndgen', a valid sound file will be produced. This default 
	sound will be a sine wave.
	
	The ADSR values entered by the user may not match the total duration of the sound, 
	so the ADSR values will be modified automatically to account for this.
	
	The WAVE values for each given wave will be between -1 and 1, and then multiplied 
	by the ADSR values and a scale based off the bit depth.
	In other words, a sample is calculated as: wave_value * adsr_value * scale 
	where wave_value is the value from the wave formula, adsr_value is the value 
	of the ADSR at the given point in time, and scale is the maximum value for the 
	given bit depth.
	
	For example:
		./sndgen -a 1 -d 1 -r 1 -t 20 --pulse --pf .5 -o output.txt
	This example generates a pulse wave.
	
	The following switches that are supported can be found by entering '-h'.
	For example:
		./sndgen -h
	This will display all the switches available for the user.


/*----------------------------------------
		III. Source File Descriptions
----------------------------------------*/

IIIa. adsr.cpp / adsr.h
	These are the files associated with the ADSR class.
	
	The ADSR class keeps track of four main components: Attack, Decay, Sustain, Release.
	All but Sustain keep track of a start time, end time, total time, and slope.
	Sustain keeps track of start time, end time, total time, and volume.
	
	There are getters and setters for each variable.
	
	There are defaults for each ADSR, where each section is 1 second long.
	
	The most important function is 'int setup_adsr(float, float);'.
	This function adjusts the values of the ADSR to fit the given total sound length 
	and the peak volume. This must be called before computing the samples.
	This function will return 1 upon a successful ADSR being generated, else return 0.
	
	There is another function used for debugging, 'void print_variables();'.
	This prints out each variable in an easy-to-read fashion.
	
IIIb. song.cpp / song.h
	This is the poorly named class that is used for holding data for sounds.
	
	The Song class keeps track of the following information:
	file name, file type, sample rate, bit depth, number of channels, 
	number of samples, total length of the sound, data, wave type, 
	frequency, pulse fraction, and peak volume.
	
	There are getters and setters for each variable.
	
	There are defaults for each Song.
	
	The following functions associated with Song are:
	void add_data(string s);
		This adds a single piece of data to the Song.
	void print_info();
		This prints out a song in a readable formated, used for sndinfo.
	int compare(Song obj);
		This compares two songs to see if they can be combined in any way.
		Returns 0 if the songs may be joined, -1 if they cannot.
	void nullify();
		This essentially turns a song 'null' without making the object itself null.
	int is_null();
		Checks if a song has been 'nullified'.
	void join(Song obj);
		This concatenates 'obj' to a Song given the songs are compatible.
	void join_mix(float mult, Song obj);
		This combines the data of two songs. Does nothing if they cannot join.
	void scale_data(float mult);
		This scales the data of the song. Note that the values of the data cannot 
		exceed the limits proposed by the bit depth. The data will simply reach the 
		cap and stop increasing/decreasing.
	string to_file();
		This returns a Song in the form of a .cs229 file as a string.
	int gen_sample(int i, adsr envelope);
		This generates a sample at a given index (i).
	
IIIc. util.cpp / util.h
	This file is used for holding random functions.
	
	The functions included are:
	Song analyze_file(string filename);
		This reads a file and produces a Song for the file.
	void print_help(string program);
		This prints help information to cout for the given program.
	string trim_spaces(string line);
		This trims the spaces on a string. Thank you, stackoverflow.
	string to_lower_case(string line);
		This makes all characters lowercase. Thank you, stackoverflow.
	
IIId. sndinfo.cpp
	This file only contains a main function.
	
	The main function interprets the information entered by the user.
	
IIIe. sndcat.cpp
	This file only contains a main function.
	
	The main function ninterprets the information entered by the user.
	It also keeps track of the output song, and what file to output to.
	
IIIf. sndmix.cpp
	This file only contains a main function.
	
	The main function ninterprets the information entered by the user.
	It also keeps track of the output song, and what file to output to.
	
IIIg. sndgen.cpp
	This file only contains a main function.
	
	The main function ninterprets the information entered by the user.
	It also keeps track of the output song, and what file to output to.
	
	Besides managing all the switches, this function also calls the aDSR generation 
	and contains the loop for generating 'x' number of samples.
	



























