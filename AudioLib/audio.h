#ifndef AUDIO_LIB
#define AUDIO_LIB

/**
 * Header file for Audio Library
 *
 * Author: Mike James White
 * Date: 09/05/2018
 */

#include <vector>
#include <cstlib>
#include <string>

namespace WHTMIC023 {

	// Abstract AudioClip base class
	template <typename T>
	class AudioClip {
		private:
			int sampleRate, bitCount;

		public:
			// constructor
			AudioClip(int sampleRate, int bitCount) : sampleRate(sampleRate), bitCount(bitCount) {}


	};


	// Concrete mono subclass
	template <typename T>
	class MonoAudioClip : AudioClip { 
		private:
			std::vector <T> samples;

		public:
			// special member functions

			MonoAudioClip(std::string filename, int sampleRate, int bitCount) : AudioClip(sampleRate, bitCount);


	}

	// Concrete stereo subclass
	template <typename T>
	class StereoAudioClip : AudioClip {
		private:
			std::vector < std::pair<T> > samples;

		public:
			// special member functions

			StereoAudioClip(std::string filename, int sampleRate, int bitCount) : AudioClip(sampleRate, bitCount);
		
	}


}

#endif