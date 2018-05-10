/**
 * basic-audio-manipulation driver program
 *
 * Author: Mike James White
 * Date: 09/05/2018
 */

#include "audio.h"
#include <iostream>

using namespace WHTMIC023;
using namespace std;

int main(int argc, char* argv []) {
	stringstream ss;
	int rate, bitCount, numChannels;
	string outFile, inFile, inFile2, op;
	vector<float> params;

	int currentArg = 2;

	// get required values
	ss = stringstream( string(argv[currentArg]) );
	ss >> rate;
	currentArg += 2;

	ss = stringstream( string(argv[currentArg]) );
	ss >> bitCount;
	currentArg += 2;

	ss = stringstream( string(argv[currentArg]) );
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
	op = string(argv[currentArg]);
	currentArg++;

	switch(op) {
		case ("-add"): //no params
			getParams(0, &params, &argv, &currentArg, &argc, &inFile, &inFile2);

			break;

		case("-cut"):
			getParams(2, &params, &argv, &currentArg, &argc, &inFile, &inFile2);
			
			break;

		case ("-radd"):
			getParams(2, &params, &argv, &currentArg, &argc, &inFile, &inFile2);

			break;

		case("-cat"): // no params
			getParams(0, &params, &argv, &currentArg, &argc, &inFile, &inFile2);

			break;

		case("-v"):
			getParams(2, &params, &argv, &currentArg, &argc, &inFile, &inFile2);

			break;

		case ("-rev"): // no params
			getParams(0, &params, &argv, &currentArg, &argc, &inFile, &inFile2);

			break;

		case("-rms"): // no params
			getParams(0, &params, &argv, &currentArg, &argc, &inFile, &inFile2);

			break;

		case ("-norm"):
			getParams(2, &params, &argv, &currentArg, &argc, &inFile, &inFile2);

			break;

		case("-fadein"):
			getParams(2, &params, &argv, &currentArg, &argc, &inFile, &inFile2);

			break;

		case("-fadeout"):
			getParams(2, &params, &argv, &currentArg, &argc, &inFile, &inFile2);
			
			break;

		default:
			cout << "No matching command found! Exiting..." << endl;
			return(1);
	}

	cout << "Operation completed successfully!" << endl;
	return 0;
}

void getParams(int numParams, vector<float>& params, char * argv [], int & currentArg, int & argc, string & inFile, string& inFile2) {
	
	// get additional parameters
	for (int i = 0; i < numParams; i++) {
		float f;
		stringstream ss = stringstream(argv[currentArg]);
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