#ifndef AUDIO_LIB
#define AUDIO_LIB

/**
 * Header file for Audio Library
 *
 * Author: Mike James White
 * Date: 09/05/2018
 */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using std::string;
using std::to_string;
using std::cout;
using std::endl;

namespace WHTMIC023 {

	// Standard AudioClip for mono files
	template <typename T>
	class AudioClip {
		private:
			int sampleRate, bitCount, numSamples;
			std::vector <T> samples;

		public:
			// ***
			// SPECIAL MEMBER FUNCTIONS
			// ***

			// constructor
			AudioClip(std::string filename, int sampleRate, int bitCount): sampleRate(sampleRate), bitCount(bitCount) {
				cout << "Loading in new Audio Clip..." << endl;
				cout << "Opening: " << filename << endl;
				std::ifstream in = std::ifstream(filename, std::ios::binary);

				// calculate filesize
				int fileSize;
				in.seekg(0, std::ios::end);
				fileSize = in.tellg();
				in.seekg(0, std::ios::beg);
				cout << "Filesize: " << fileSize << " bytes" << endl;

				// calculate number of samples
				numSamples = fileSize / (bitCount / 8);
				cout << "Number of samples: " << numSamples << " (" << to_string(bitCount) << " bit mono)" << endl << endl;
				samples.resize(numSamples);

				T tmp;

				for (int i = 0; i < numSamples; i++) {
					in >> tmp;
					samples[i] = tmp;
				}
			}

			// destructor
			~AudioClip() {}

			// copy constructor
			AudioClip(AudioClip& otherClip) {
				cout << "Copying audio clip." << endl;
				samples.clear();

				sampleRate = otherClip.sampleRate;
				bitCount = otherClip.bitCount;
				numSamples = otherClip.numSamples;
				samples = std::vector<T>(otherClip.samples);
				cout << "Copied Size: " << samples.size() << " samples" << endl;
			}

			// move constructor
			AudioClip(AudioClip&& otherClip) {
				cout << "Moving audio clip." << endl << endl;
				samples.clear();

				sampleRate = otherClip.sampleRate;
				bitCount = otherClip.bitCount;
				numSamples = otherClip.numSamples;
				samples.swap(otherClip.samples);				
			}

			// copy assignment
			AudioClip& operator=(AudioClip& rhs) {
				cout << "Copying audio clip." << endl << endl;
				samples.clear();

				sampleRate = rhs.sampleRate;
				bitCount = rhs.bitCount;
				numSamples = rhs.numSamples;
				samples = std::vector<T>(rhs.samples);
				cout << "Copied Size: " << samples.size() << " samples" << endl;
			}

			// move assignment
			AudioClip& operator=(AudioClip&& rhs) {
				cout << "Moving audio clip." << endl << endl;
				samples.clear();

				sampleRate = rhs.sampleRate;
				bitCount = rhs.bitCount;
				numSamples = rhs.numSamples;
				samples.swap(rhs.samples);
			}

			// ***
			// OTHER FUNCTIONS
			// ***

			AudioClip add(AudioClip& otherClip) {
				// copy this clip
				AudioClip newClip = *this;

				// add other clip's samples
				auto iter2 = otherClip.begin();
				for (auto iter1 = newClip.begin(); iter1 != newClip.end(); iter1++) {
					int val = *iter1 + *iter2;
					// should check if val > T's max size

					*iter1 = val;
				}

				return newClip;
			}

			AudioClip cut(float r1, float r2) {


			}

			AudioClip rangeadd(AudioClip& otherClip, float r1, float r2, float s1, float s2) {

			}

			AudioClip concatenate(AudioClip& otherClip) {
				// copy this clip
				AudioClip newClip = *this;

				// concat other clip's samples


				return newClip;
			}

			AudioClip volume(float v1, float v2) {

			}

			AudioClip reverse(void) {
				cout << "Performing reverse operation..." << endl;
				// copy this clip
				AudioClip newClip = *this;

				// reverse the new clip using stl
				std::reverse(newClip.begin(), newClip.end());

				cout << "Done!" << endl << endl;
				return newClip;
			}

			AudioClip rms(void) {

			}

			AudioClip normalize(void) {

			}

			AudioClip fadein(float r1, float r2) {

			}

			AudioClip fadeout(float r1, float r2) {

			}

			void write(std::string outfile) {
				string filename = outfile + "_" + to_string(sampleRate) + "_" + to_string(bitCount) + "_mono.raw";
				cout << "Writing to: " << filename << endl;
				std::ofstream ofs = std::ofstream(filename, std::ios::binary);

				int count = 0;
				for (T sample : samples) {
					ofs << sample;
					count++;
				}

				cout << "Wrote " << count << " bytes!" << endl;
				ofs.close();
			}

			typename std::vector<T>::iterator begin() {
				return samples.begin();
			}

			typename std::vector<T>::iterator end() {
				return samples.end();
			}
	};



	// AudioClip specialized for stereo
	template <typename T> 
	class AudioClip < std::pair<T,T> > {
		private:
			int sampleRate, bitCount, numSamples;
			std::vector < std::pair<T,T> > samples;

		public:
			// ***
			// SPECIAL MEMBER FUNCTIONS
			// ***

			// constructor
			AudioClip(std::string filename, int sampleRate, int bitCount) : sampleRate(sampleRate), bitCount(bitCount) {
				std::ifstream in = std::ifstream(filename, std::ios::binary);
				T left, right;
				int fileSize;
				numSamples; // divide by two because there are two channels

				samples.reserve(numSamples);
				for (int i = 0; i < numSamples; i++) {
					in >> left;
					in >> right;
					samples[i] = std::pair<T,T>(left, right);
				}

				in.close();
			}

			// destructor
			~AudioClip() {}

			// copy constructor
			AudioClip(AudioClip& otherClip) {

			}

			// move constructor
			AudioClip(AudioClip&& otherClip) {

			}

			// copy assignment
			AudioClip& operator=(AudioClip& rhs) {

			}

			// move assignment
			AudioClip& operator=(AudioClip&& rhs) {
				
			}

			// ***
			// OTHER FUNCTIONS
			// ***

			AudioClip add(AudioClip& otherClip) {

			}

			AudioClip cut(float r1, float r2) {

			}

			AudioClip rangeadd(AudioClip& otherClip, float r1, float r2, float s1, float s2) {

			}

			AudioClip concatenate(AudioClip& otherClip) {

			}

			AudioClip volume(float v1, float v2) {

			}

			AudioClip reverse(void) {
				// copy this clip
				AudioClip newClip = *this;

				// reverse the new clip using stl
				std::reverse(newClip.begin(), newClip.end());

				return newClip;
			}

			AudioClip rms(void) {

			}

			AudioClip normalize(void) {

			}

			AudioClip fadein(float r1, float r2) {

			}

			AudioClip fadeout(float r1, float r2) {

			}
	
			void write(std::string outfile) {
				std::ofstream ofs = std::ofstream(outfile, std::ios::binary);

				for (std::pair<T,T> sample : samples) {
					ofs << sample.first;
					ofs << sample.second;
				}

				ofs.close();
			}

			typename std::vector< std::pair<T,T> >::iterator begin() {
				return samples.begin();
			}

			typename std::vector< std::pair<T,T> >::iterator end() {
				return samples.end();
			}
	};

}

#endif