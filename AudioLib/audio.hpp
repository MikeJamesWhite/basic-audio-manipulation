#ifndef AUDIO_LIB
#define AUDIO_LIB

/**
 * Audio Library for performing various transformations on audio clips.
 * (Supports 8/16 bit mono/stereo RAW audio files)
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
#include <cstdint>
#include <cstdlib>
#include <math.h>
#include <numeric>

using std::string;
using std::to_string;
using std::cout;
using std::endl;

namespace WHTMIC023 {

	// custom functor for normalizing audio clips
	template <typename T>
	struct norm {
		norm(float diffFactor) : diffFactor(diffFactor) {}
		norm(float diffFactor, float diffFactor2) : diffFactor(diffFactor), diffFactor2(diffFactor2) {}

		// standard (mono) normalize
		T operator()(T sample) const { return (T) (diffFactor * sample); }
		
		// specialized (stereo) normalize
		template < std::pair<T, T> >
		std::pair<T, T> operator()(std::pair<T, T> sample) const { return std::pair<T,T>(diffFactor * sample.first, diffFactor2 * sample.second); }

		private:
			float diffFactor, diffFactor2;
	};

	// Standard AudioClip for mono files
	template <typename T>
	class AudioClip {
		private:
			int sampleRate, bitCount, numSamples, MIN, MAX;
			std::vector <T> samples;

		public:
			// ***
			// SPECIAL MEMBER FUNCTIONS
			// ***

			// default constructor
			AudioClip() { }

			// file constructor
			AudioClip(std::string filename, int sampleRate, int bitCount): sampleRate(sampleRate), bitCount(bitCount) {
				cout << "Loading in new Audio Clip..." << endl;
				cout << "Opening: " << filename << endl;
				std::ifstream in = std::ifstream(filename, std::ios::binary);
				
				// set max and min for clamping
				if (bitCount == 8) {
					MAX = INT8_MAX;
					MIN = INT8_MIN;
				}
				else {
					MAX = INT16_MAX;
					MIN = INT16_MIN;
				}

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
					if (bitCount == 8) {
						in >> tmp;
					}
					else {
						uint8_t x, y;
						in.read(reinterpret_cast<char*>(&x), sizeof(x));
						in.read(reinterpret_cast<char*>(&y), sizeof(y));
						tmp = (int8_t) x | ((int8_t) y << 8);
					}

					samples[i] = tmp;
				}

				in.close();
			}

			// destructor
			~AudioClip() {}

			// copy constructor
			AudioClip(AudioClip& otherClip) {
				// release current resources
				samples.clear();

				// copy resources from otherClip
				sampleRate = otherClip.sampleRate;
				bitCount = otherClip.bitCount;
				numSamples = otherClip.numSamples;
				MAX = otherClip.MAX;
				MIN = otherClip.MIN;
				samples = std::vector<T>(otherClip.samples);
			}

			// move constructor
			AudioClip(AudioClip&& otherClip) {
				// release current resources
				samples.clear();

				// move resources from otherClip
				sampleRate = otherClip.sampleRate;
				bitCount = otherClip.bitCount;
				numSamples = otherClip.numSamples;
				MAX = otherClip.MAX;
				MIN = otherClip.MIN;
				samples.swap(otherClip.samples);
			}

			// copy assignment
			AudioClip& operator=(AudioClip& rhs) {
				// release current resources
				samples.clear();

				// copy resources from otherClip
				sampleRate = rhs.sampleRate;
				bitCount = rhs.bitCount;
				numSamples = rhs.numSamples;
				MAX = rhs.MAX;
				MIN = rhs.MIN;
				samples = std::vector<T>(rhs.samples);
			}

			// move assignment
			AudioClip& operator=(AudioClip&& rhs) {
				// release current resources
				samples.clear();
				
				// move resources from otherClip
				sampleRate = rhs.sampleRate;
				bitCount = rhs.bitCount;
				numSamples = rhs.numSamples;
				MAX = rhs.MAX;
				MIN = rhs.MIN;								
				samples.swap(rhs.samples);
			}

			// ***
			// OTHER FUNCTIONS
			// ***

			AudioClip add(AudioClip& otherClip) {
				cout << "Performing add operation..." << endl;

				// copy this clip
				AudioClip newClip = *this;

				// add other clip's samples
				for (int i = 0; i < numSamples; i++) {
					int val = newClip.samples[i] + otherClip.samples[i];

					// clamp value
					if (val > MAX) val = MAX;
					if (val < MIN) val = MIN;

					newClip.samples[i] = val;
				}

				cout << "Done!" << endl << endl;
				return newClip;
			}

			AudioClip cut(int r1, int r2) {
				cout << "Performing cut operation..." << endl;
				cout << "Cutting between samples " << r1 << " and " << r2 << endl;

				// create new AudioClip container
				AudioClip newClip;
				newClip.sampleRate = sampleRate;
				newClip.bitCount = bitCount;
				newClip.numSamples = r2 - r1;
				newClip.MAX = MAX;
				newClip.MIN = MIN;
				newClip.samples.resize(newClip.numSamples);

				// copy samples over range
				for (int i = 0; i < newClip.numSamples; i++) {
					newClip.samples[i] = samples[r1 + i];
				}

				cout << "Done!" << endl << endl;
				return newClip;
			}

			AudioClip concatenate(AudioClip& otherClip) {
				cout << "Performing concatenate operation..." << endl;
				// copy this clip
				AudioClip newClip = *this;

				// resize and concat other clip's samples
				newClip.samples.resize(numSamples + otherClip.numSamples);

				for (int i = numSamples; i < newClip.samples.size(); i++) {
					newClip.samples[i] = otherClip.samples[i - numSamples];
				}

				newClip.numSamples += otherClip.numSamples;
				cout << "New size: " << newClip.numSamples << " samples" << endl;

				cout << "Done!" << endl << endl;
				return newClip;
			}

			AudioClip volume(float v1, float v2) {
				cout << "Performing volume adjustment operation..." << endl;
				cout << "Mono volume factor: " << v1 << endl;

				// copy this clip
				AudioClip newClip = *this;				
				
				// multiply each sample by volume factor
				for (T& sample: newClip.samples) {
					int val = sample;
					val *= v1;

					// clamp value
					if (val > MAX) val = MAX;
					if (val < MIN) val = MIN;

					sample = val;
				}

				cout << "Done!" << endl << endl;
				return newClip;
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

			AudioClip rangeadd(AudioClip& otherClip, float r1, float r2, float s1, float s2) {
				cout << "Performing ranged add operation..." << endl;
				
				// check ranges are valid
				if (fabs( (r2 - r1) - (s2 - s1)) > 0.0001f) {
					throw "ERROR: Ranges are not equal!";
				}

				// calculate sample range
				int start1 = (int) (r1 * sampleRate);
				int end1 = (int) (r2 * sampleRate);
				int start2 = (int) (s1 * sampleRate);
				int end2 = (int) (s2 * sampleRate);
				int sampleRange = end1 - start1;
				cout << "Adding over range of " << sampleRange << " samples" << endl << endl;

				// add over range (using std::copy and + operator)
				AudioClip first = *this ^ std::pair<int, int> (start1, end1);
				AudioClip second = otherClip ^ std::pair<int, int> (start2, end2);

				return  first + second;
			}

			float rms(void) {
				cout << "Calculating RMS..." << endl;

				// calculate rms using std::accumulate and custom lambda
				float ms = std::accumulate(begin(), end(), *(begin()) * *(begin()), 
					[](T a, T b) {  
            			return a + (b*b);  
        			});

				cout << "Done!" << endl << endl;
				return sqrt(ms / numSamples);
			}

			AudioClip normalize(float r1, float r2) {
				cout << "Performing normalize operation..." << endl;

				// normalize using std::transform with custom functor
				AudioClip newClip = *this;

				// calculate factor of difference with desired RMS
				float diffFactor = r1 / rms();

				// multiply each value by factor of difference
				std::transform(begin(), end(), newClip.begin(), norm<T>(diffFactor));

				cout << "Done!" << endl << endl;
				return newClip;
			}

			AudioClip fadein(float n) {
				cout << "Performing fadein operation..." << endl;

				// use custom lambda with linear ramp
				AudioClip newClip = *this;

				int sampleRange = n * sampleRate;
				int counter = 0;

				std::for_each(newClip.begin(), newClip.begin() + sampleRange, 
					[&counter, sampleRange](T &sample) {
						sample *= (counter / (float) sampleRange);
						counter++;
					});

				cout << "Done!" << endl << endl;
				return newClip;
			}

			AudioClip fadeout(float n) {
				cout << "Performing fadeout operation..." << endl;

				// use custom lambda with linear ramp
				AudioClip newClip = *this;

				int sampleRange = n * sampleRate;
				int counter = 0;

				std::for_each(newClip.end() - sampleRange, newClip.end(), 
					[&counter, sampleRange](T &sample) {
						sample *= 1.0f - (counter / (float) sampleRange);
						counter++;
					});

				cout << "Done!" << endl << endl;
				return newClip;
			}

			void write(std::string outfile) {
				string filename = outfile + "_" + to_string(sampleRate) + "_" + to_string(bitCount) + "_mono.raw";
				cout << "Writing to: " << filename << endl;
				std::ofstream ofs = std::ofstream(filename, std::ios::binary);

				int count = 0;
				for (auto iter = begin(); iter != end(); iter ++) {
					ofs.write((char*) &(*iter), (bitCount / 8));
					count += (bitCount / 8);
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

			// ***
			// ADDITIONAL OPERATOR OVERLOADS
			// ***

			AudioClip operator|(AudioClip& rhs) {
				return concatenate(rhs);
			}

			AudioClip operator+(AudioClip& rhs) {
				return add(rhs);
			}

			AudioClip operator*(std::pair<float, float> rhs) {
				return volume(rhs.first, rhs.second);
			}

			AudioClip operator^(std::pair<int, int> rhs) {
				return cut(rhs.first, rhs.second);
			}
	};


	// AudioClip specialized for stereo
	template <typename T> 
	class AudioClip < std::pair<T,T> > {
		private:
			int sampleRate, bitCount, numSamples, MAX, MIN;
			std::vector < std::pair<T,T> > samples;

		public:
			// ***
			// SPECIAL MEMBER FUNCTIONS
			// ***

			// default constructor
			AudioClip() {}

			// constructor
			AudioClip(std::string filename, int sampleRate, int bitCount) : sampleRate(sampleRate), bitCount(bitCount) {
				cout << "Loading in new Audio Clip..." << endl;
				cout << "Opening: " << filename << endl;
				std::ifstream in = std::ifstream(filename, std::ios::binary);

				// set max and min for clamping
				if (bitCount == 8) {
					MAX = INT8_MAX;
					MIN = INT8_MIN;
				}
				else {
					MAX = INT16_MAX;
					MIN = INT16_MIN;
				}

				// calculate filesize
				int fileSize;
				in.seekg(0, std::ios::end);
				fileSize = in.tellg();
				in.seekg(0, std::ios::beg);
				cout << "Filesize: " << fileSize << " bytes" << endl;

				// calculate number of samples
				numSamples = (fileSize / (bitCount / 8)) / 2; // divide by two because there are two channels
				cout << "Number of samples: " << numSamples << " (" << to_string(bitCount) << " bit stereo)" << endl << endl;
				samples.resize(numSamples);

				T left, right;
				for (int i = 0; i < numSamples; i++) {
					if (bitCount == 8) {
						in >> left;
						in >> right;
					}
					else {
						uint8_t x, y;
						in.read(reinterpret_cast<char*>(&x), sizeof(x));
						in.read(reinterpret_cast<char*>(&y), sizeof(y));
						left = (int8_t) x | ((int8_t) y << 8);

						in.read(reinterpret_cast<char*>(&x), sizeof(x));
						in.read(reinterpret_cast<char*>(&y), sizeof(y));
						right = (int8_t) x | ((int8_t) y << 8);
					}
					samples[i] = std::pair<T,T>(left, right);
				}

				in.close();
			}

			// destructor
			~AudioClip() { }

			// copy constructor
			AudioClip(AudioClip& otherClip) {
				cout << "Copying audio clip." << endl;
				samples.clear();

				sampleRate = otherClip.sampleRate;
				bitCount = otherClip.bitCount;
				numSamples = otherClip.numSamples;
				MAX = otherClip.MAX;
				MIN = otherClip.MIN;
				samples = std::vector<std::pair<T,T>>(otherClip.samples);
				cout << "Copied Size: " << samples.size() << " samples" << endl;
			}

			// move constructor
			AudioClip(AudioClip&& otherClip) {
				cout << "Moving audio clip." << endl << endl;
				samples.clear();

				sampleRate = otherClip.sampleRate;
				bitCount = otherClip.bitCount;
				numSamples = otherClip.numSamples;
				MAX = otherClip.MAX;
				MIN = otherClip.MIN;
				samples.swap(otherClip.samples);				
			}

			// copy assignment
			AudioClip& operator=(AudioClip& rhs) {
				cout << "Copying audio clip." << endl << endl;
				samples.clear();

				sampleRate = rhs.sampleRate;
				bitCount = rhs.bitCount;
				numSamples = rhs.numSamples;
				MAX = rhs.MAX;
				MIN = rhs.MIN;
				samples = std::vector<std::pair<T,T>>(rhs.samples);
				cout << "Copied Size: " << samples.size() << " samples" << endl;
			}

			// move assignment
			AudioClip& operator=(AudioClip&& rhs) {
				cout << "Moving audio clip." << endl << endl;
				samples.clear();

				sampleRate = rhs.sampleRate;
				bitCount = rhs.bitCount;
				numSamples = rhs.numSamples;
				MAX = rhs.MAX;
				MIN = rhs.MIN;
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
					int leftVal = (*iter1).first + (*iter2).first;
					int rightVal = (*iter1).second + (*iter2).second;

					// clamp values
					if (leftVal > MAX) leftVal = MAX;
					if (leftVal < MIN) leftVal = MIN;

					if (rightVal > MAX) rightVal = MAX;
					if (rightVal < MIN) rightVal = MIN;

					*iter1 = std::pair<T,T>(leftVal, rightVal);
				}

				return newClip;
			}

			AudioClip cut(int r1, int r2) {
				cout << "Performing cut operation..." << endl;
				cout << "Cutting between samples " << r1 << " and " << r2 << endl;

				// create new AudioClip container
				AudioClip newClip;
				newClip.sampleRate = sampleRate;
				newClip.bitCount = bitCount;
				newClip.numSamples = r2 - r1;
				newClip.MAX = MAX;
				newClip.MIN = MIN;
				newClip.samples.resize(newClip.numSamples);

				// copy samples over range
				for (int i = 0; i < newClip.numSamples; i++) {
					newClip.samples[i] = std::pair<T,T>(samples[r1 + i].first, samples[r1 + i].second);
				}

				cout << "Done!" << endl << endl;
				return newClip;
			}

			AudioClip concatenate(AudioClip& otherClip) {
				cout << "Performing concatenate operation..." << endl;
				// copy this clip
				AudioClip newClip = *this;

				// resize and concat other clip's samples
				newClip.samples.resize(numSamples + otherClip.numSamples);

				for (int i = numSamples; i < newClip.samples.size(); i++) {
					newClip.samples[i] = std::pair<T,T>(otherClip.samples[i - numSamples]);
				}

				newClip.numSamples += otherClip.numSamples;
				cout << "New size: " << newClip.numSamples << " samples" << endl;

				cout << "Done!" << endl << endl;
				return newClip;
			}

			AudioClip volume(float v1, float v2) {
				cout << "Performing volume adjustment operation..." << endl;
				cout << "Left volume factor: " << v1 << endl;
				cout << "Right volume factor: " << v2 << endl;

				// copy this clip
				AudioClip newClip = *this;				
				
				// multiply each sample by volume factors
				for (std::pair<T,T>& sample: newClip.samples) {
					int leftVal = sample.first;
					int rightVal = sample.second;
					leftVal *= v1;
					rightVal *= v2;

					// clamp values
					if (leftVal > MAX) leftVal = MAX;
					if (leftVal < MIN) leftVal = MIN;

					if (rightVal > MAX) rightVal = MAX;
					if (rightVal < MIN) rightVal = MIN;

					sample = std::pair<T,T>(leftVal, rightVal);
				}

				cout << "Done!" << endl << endl;
				return newClip;
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

			AudioClip rangeadd(AudioClip& otherClip, float r1, float r2, float s1, float s2) {
				cout << "Performing ranged add operation..." << endl;
				
				// check ranges are valid
				if (fabs( (r2 - r1) - (s2 - s1)) > 0.0001f) {
					throw "ERROR: Ranges are not equal!";
				}

				// calculate sample range
				int start1 = (int) (r1 * sampleRate);
				int end1 = (int) (r2 * sampleRate);
				int start2 = (int) (s1 * sampleRate);
				int end2 = (int) (s2 * sampleRate);
				int sampleRange = end1 - start1;
				cout << "Adding over range of " << sampleRange << " samples" << endl << endl;

				// add over range (using std::copy and + operator)
				AudioClip first = *this ^ std::pair<int, int> (start1, end1);
				AudioClip second = otherClip ^ std::pair<int, int> (start2, end2);

				return  first + second;
			}

			std::pair<float, float> rms(void) {
				cout << "Calculating RMS..." << endl;

				// calculate rms per channel using std::accumulate and custom lambda
				std::pair<float, float> ms = std::accumulate(begin(), end(), std::pair<float, float> (0,0), 
					[](std::pair<T,T> a, std::pair<T, T> b) {  
						return std::pair<float, float> (a.first + (b.first*b.first), a.second + (b.second*b.second));  
        			});

				cout << "Done!" << endl << endl;
				return std::pair<float, float>(sqrt(ms.first / numSamples), sqrt(ms.second / numSamples));
			}

			AudioClip normalize(float r1, float r2) {
				cout << "Performing normalize operation..." << endl;

				// normalize using std::transform with custom functor
				AudioClip newClip = *this;

				// calculate factor of difference with desired RMS per channel
				std::pair<float, float> currentRMS = rms();
				float leftDiff = r1 / currentRMS.first;
				float rightDiff = r2 / currentRMS.second;

				// multiply each value by corresponding factor of difference
				std::transform(begin(), end(), newClip.begin(), norm<std::pair<T,T> >(leftDiff, rightDiff));

				cout << "Done!" << endl << endl;
				return newClip;
			}

			AudioClip fadein(float n) {
				cout << "Performing fadein operation..." << endl;

				// use custom lambda with linear ramp
				AudioClip newClip = *this;

				int sampleRange = n * sampleRate;
				int counter = 0;

				std::for_each(newClip.begin(), newClip.begin() + sampleRange, 
					[&counter, sampleRange](std::pair<T,T> &sample) {
						sample.first *= (counter / (float) sampleRange);
						sample.second *= (counter / (float) sampleRange);

						counter++;
					});

				cout << "Done!" << endl << endl;
				return newClip;
			}

			AudioClip fadeout(float n) {
				cout << "Performing fadeout operation..." << endl;
				
				// use custom lambda with linear ramp
				AudioClip newClip = *this;

				int sampleRange = n * sampleRate;
				int counter = 0;

				std::for_each(newClip.end() - sampleRange, newClip.end(), 
					[&counter, sampleRange](std::pair<T,T> &sample) {
						sample.first *= 1.0f - (counter / (float) sampleRange);
						sample.second *= 1.0f - (counter / (float) sampleRange);
				
						counter++;
					});

				cout << "Done!" << endl << endl;
				return newClip;
			}
	
			void write(std::string outfile) {
				string filename = outfile + "_" + to_string(sampleRate) + "_" + to_string(bitCount) + "_stereo.raw";
				cout << "Writing to: " << filename << endl;
				std::ofstream ofs = std::ofstream(filename, std::ios::binary);

				int count = 0;
				for (std::pair<T,T> sample : samples) {

					ofs.write((char*) &(sample.first), (bitCount / 8));
					ofs.write((char*) &(sample.second), (bitCount / 8));

					count += 2 * (bitCount / 8);
				}

				cout << "Wrote " << count << " bytes!" << endl;

				ofs.close();
			}

			typename std::vector< std::pair<T,T> >::iterator begin() {
				return samples.begin();
			}

			typename std::vector< std::pair<T,T> >::iterator end() {
				return samples.end();
			}

			// ***
			// ADDITIONAL OPERATOR OVERLOADS
			// ***

			AudioClip operator|(AudioClip& rhs) {
				return concatenate(rhs);
			}

			AudioClip operator+(AudioClip& rhs) {
				return add(rhs);
			}

			AudioClip operator*(std::pair<float, float> rhs) {
				return volume(rhs.first, rhs.second);
			}

			AudioClip operator^(std::pair<int, int> rhs) {
				return cut(rhs.first, rhs.second);
			}
	};

}

#endif