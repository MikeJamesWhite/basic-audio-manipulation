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
#include <sstream>

namespace WHTMIC023 {

	// Standard AudioClip for mono files
	template <typename T>
	class AudioClip {
		private:
			int sampleRate, bitCount;
			std::vector <T> samples;

		public:
			// special member functions
			AudioClip(std::string filename, int sampleRate, int bitCount);

			// abstract functions
			AudioClip add(AudioClip& otherClip);

			AudioClip cut(float r1, float r2);

			AudioClip rangeadd(AudioClip& otherClip, float r1, float r2, float s1, float s2);

			AudioClip concatenate(AudioClip& otherClip);

			AudioClip volume(float v1, float v2);

			AudioClip reverse(void);

			AudioClip rms(void);

			AudioClip normalize(void);

			AudioClip fadein(float r1, float r2);

			AudioClip fadeout(float r1, float r2);

			void write(std::string outfile);
	};

	// AudioClip specialized for stereo
	template <typename T> 
	class AudioClip < std::pair<T,T> > {
		private:
			int sampleRate, bitCount;
			std::vector < std::pair<T,T> > samples;

		public:
			// special member functions
			AudioClip(std::string filename, int sampleRate, int bitCount);

			// other functions
			AudioClip add(AudioClip& otherClip);

			AudioClip cut(float r1, float r2);

			AudioClip rangeadd(AudioClip& otherClip, float r1, float r2, float s1, float s2);

			AudioClip concatenate(AudioClip& otherClip);

			AudioClip volume(float v1, float v2);

			AudioClip reverse(void);

			AudioClip rms(void);

			AudioClip normalize(void);

			AudioClip fadein(float r1, float r2);

			AudioClip fadeout(float r1, float r2);
	
			void write(std::string outfile);	
	};

}

#endif