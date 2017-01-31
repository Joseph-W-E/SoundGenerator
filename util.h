#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "song.h"

using namespace std;

#ifndef UTIL_H
#define UTIL_H

// KEYWORDS
const string CS229 = "cs229";
const string SAMPLE_RATE = "samplerate";
const string SAMPLES = "samples";
const string CHANNELS = "channels";
const string BIT_RES = "bitres";
const string STARTDATA = "startdata";

// FUNCTIONS
Song analyze_file(string);
void print_help(string);
string trim_spaces(string line);
string to_lower_case(string line);

#endif