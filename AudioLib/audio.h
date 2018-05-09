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

	template <typename T>
	class AudioClip {
		std::vector <T> samples;

		AudioClip(std::string filename); // load an audio file


	};

	template <typename T>
	class MonoAudioClip : AudioClip {
		std::vector <T> samples;

	}

	template <typename T>
	class StereoAudioClip : AudioClip {
		std::vector < std::pair<T> > samples;

	}


}

#endif