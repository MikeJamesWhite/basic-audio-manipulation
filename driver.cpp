/**
 * basic-audio-manipulation driver program
 *
 * Author: Mike James White
 * Date: 09/05/2018
 */

#include "audio.h"

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

	}

	else if ( op == "-cut" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);	
	
	}

	else if ( op == "-radd" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);
	
	}

	else if ( op == "-cat" ) {
		getParams(0, params, argv, currentArg, argc, inFile, inFile2);
	
	}

	else if ( op == "-v" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);
	
	}

	else if ( op == "-rev" ) {
		getParams(0, params, argv, currentArg, argc, inFile, inFile2);
		if ()
		AudioClip
	}

	else if ( op == "-rms" ) {
		getParams(0, params, argv, currentArg, argc, inFile, inFile2);
	
	}

	else if ( op == "-norm" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);
	
	}

	else if ( op == "-fadein" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);
	
	}

	else if ( op == "-fadeout" ) {
		getParams(2, params, argv, currentArg, argc, inFile, inFile2);
	
	}

	else {
		cout << "No matching command found! Exiting..." << endl;
		return(1);
	}

	cout << "Operation completed successfully!" << endl;
	return 0;
}