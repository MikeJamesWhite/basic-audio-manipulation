/**
 * basic-audio-manipulation driver program
 *
 * Author: Mike James White
 * Date: 09/05/2018
 */

#include "audio.hpp"

using namespace WHTMIC023;
using namespace std;

void getParams(int numParams, vector<float>& params, char * argv [], int & currentArg, int & argc, string & inFile, string& inFile2) {
	
	// get additional parameters
	for (int i = 0; i < numParams; i++) {
		float f;
		istringstream ss = istringstream(argv[currentArg]);
		ss >> f;
		params.push_back(f);
		currentArg++;
	}

	// get input files
	inFile = string(argv[currentArg]);
	currentArg++;

	if (currentArg < argc)
		inFile2 = string(argv[currentArg]);
}

int main(int argc, char* argv []) {
	system("clear");
	cout << "Simple Audio Manipulation Program v1.0 - by Michael White" << endl;
	cout << "---------------------------------------------------------" << endl << endl;
	
	istringstream ss;
	int rate, bitCount, numChannels;
	string outFile, inFile, inFile2, op;
	vector<float> params;
	int currentArg = 2;

	// get required values
	ss = istringstream( string(argv[currentArg]) );
	ss >> rate;
	currentArg += 2;

	ss = istringstream( string(argv[currentArg]) );
	ss >> bitCount;
	currentArg += 2;

	ss = istringstream( string(argv[currentArg]) );
	ss >> numChannels;
	currentArg++;

	// get output file if present
	if (string(argv[currentArg]) == "-o") {
		currentArg++;
		outFile = string(argv[currentArg]);
		currentArg++;
	}
	else {
		outFile = "out";
	}

	// get op + extra params and run
	op = argv[currentArg];
	currentArg++;

	if (op == "-add" ) {
		getParams(0, params, argv, currentArg, argc, inFile, inFile2);
		if (numChannels == 1) {
			if (bitCount == 8) {
				AudioClip<int8_t> inputAudio = AudioClip<int8_t> (inFile, rate, bitCount);
				AudioClip<int8_t> inputAudio2 = AudioClip<int8_t> (inFile2, rate, bitCount);
				AudioClip<int8_t> added = inputAudio.add(inputAudio2);
				added.write(outFile);
			}
			else {
				AudioClip<int16_t> inputAudio = AudioClip<int16_t> (inFile, rate, bitCount);
				AudioClip<int16_t> inputAudio2 = AudioClip<int16_t> (inFile2, rate, bitCount);
				AudioClip<int16_t> added = inputAudio.add(inputAudio2);
				added.write(outFile);
			}
		}
		else {

		}
	}

	else if ( op == "-cut" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);	
		if (numChannels == 1) {
			if (bitCount == 8) {
				AudioClip<int8_t> inputAudio = AudioClip<int8_t> (inFile, rate, bitCount);
				AudioClip<int8_t> cut = inputAudio.cut((int) params[0], (int) params[1]);
				cut.write(outFile);
			}
			else {
				AudioClip<int16_t> inputAudio = AudioClip<int16_t> (inFile, rate, bitCount);
				AudioClip<int16_t> cut = inputAudio.cut((int) params[0], (int) params[1]);
				cut.write(outFile);
			}
		}
		else {
			
		}
	}

	else if ( op == "-radd" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);
		if (numChannels == 1) {


		}
		else {
			
		}
	}

	else if ( op == "-cat" ) {
		getParams(0, params, argv, currentArg, argc, inFile, inFile2);
		if (numChannels == 1) {
			if (bitCount == 8) {
				AudioClip<int8_t> inputAudio = AudioClip<int8_t> (inFile, rate, bitCount);
				AudioClip<int8_t> inputAudio2 = AudioClip<int8_t> (inFile2, rate, bitCount);
				AudioClip<int8_t> added = inputAudio.concatenate(inputAudio2);
				added.write(outFile);
			}
			else {
				AudioClip<int16_t> inputAudio = AudioClip<int16_t> (inFile, rate, bitCount);
				AudioClip<int16_t> inputAudio2 = AudioClip<int16_t> (inFile2, rate, bitCount);
				AudioClip<int16_t> added = inputAudio.concatenate(inputAudio2);
				added.write(outFile);
			}
		}
		else {
			
		}	
	}

	else if ( op == "-v" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);
		if (numChannels == 1) {
			if (bitCount == 8) {
				AudioClip<int8_t> inputAudio = AudioClip<int8_t> (inFile, rate, bitCount);
				AudioClip<int8_t> quieter = inputAudio.volume(params[0], params[1]);
				quieter.write(outFile);
			}
			else {
				AudioClip<int16_t> inputAudio = AudioClip<int16_t> (inFile, rate, bitCount);
				AudioClip<int16_t> quieter = inputAudio.volume(params[0], params[1]);
				quieter.write(outFile);				
			}
		}
		else {
			
		}	
	}

	else if ( op == "-rev" ) { // reverse the input track
		getParams(0, params, argv, currentArg, argc, inFile, inFile2);
		if (numChannels == 1) {
			if (bitCount == 8) {
				AudioClip<int8_t> inputAudio = AudioClip<int8_t> (inFile, rate, bitCount);
				AudioClip<int8_t> reversed = inputAudio.reverse();
				reversed.write(outFile);
			}
			else {
				AudioClip<int16_t> inputAudio = AudioClip<int16_t> (inFile, rate, bitCount);
				AudioClip<int16_t> reversed = inputAudio.reverse();
				reversed.write(outFile);
			}
		}
		else {
			if (bitCount == 8) {
				AudioClip< pair<int8_t, int8_t> > inputAudio = AudioClip< pair<int8_t, int8_t> >(inFile, rate, bitCount);
				AudioClip< pair<int8_t, int8_t> > reversed = inputAudio.reverse();
				reversed.write(outFile);	
			}
			else {
				AudioClip< pair<int16_t, int16_t> > inputAudio = AudioClip< pair<int16_t, int16_t> >(inFile, rate, bitCount);
				AudioClip< pair<int16_t, int16_t> > reversed = inputAudio.reverse();
				reversed.write(outFile);	
			}		
		}
	}

	else if ( op == "-rms" ) {
		getParams(0, params, argv, currentArg, argc, inFile, inFile2);
		if (numChannels == 1) {


		}
		else {
			
		}	
	}

	else if ( op == "-norm" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);
		if (numChannels == 1) {


		}
		else {
			
		}	
	}

	else if ( op == "-fadein" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);
		if (numChannels == 1) {


		}
		else {
			
		}	
	}

	else if ( op == "-fadeout" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);
		if (numChannels == 1) {


		}
		else {
			
		}	
	}

	else {
		cout << "No matching command found! Exiting..." << endl;
		return(1);
	}

	cout << "Operation completed successfully!" << endl;
	return 0;
}