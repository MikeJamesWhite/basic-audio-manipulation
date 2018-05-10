/**
 * Implementation file for the standard AudioClip (mono channel)
 *
 * Author: Mike James White
 * Date: 09/05/2018
 */

#include "audio.h"

using namespace WHTMIC023;
using namespace std;

template <typename T>
AudioClip<T>::AudioClip(std::string filename, int sampleRate, int bitCount) : sampleRate(sampleRate), bitCount(bitCount) {
	ifstream in = ifstream(filename, ios::binary);
	T tmp;
	int fileSize;
	numSamples;

	samples.reserve(numSamples);
	for (int i = 0; i < numSamples; i++) {
		in >> tmp;
		samples[i] = tmp;
	}
}

template <typename T>
AudioClip<T> AudioClip<T>::add(AudioClip& otherClip) {
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

template <typename T>
AudioClip<T> AudioClip<T>::cut(float r1, float r2) {

}

template <typename T>
AudioClip<T> AudioClip<T>::rangeadd(AudioClip& otherClip, float r1, float r2, float s1, float s2) {

}

template <typename T>
AudioClip<T> AudioClip<T>::concatenate(AudioClip& otherClip) {
	// copy this clip
	AudioClip newClip = *this;

	// concat other clip's samples


	return newClip;
}

template <typename T>
AudioClip<T> AudioClip<T>::volume(float v1, float v2) {

}

template <typename T>
AudioClip<T> AudioClip<T>::reverse(void) {
	// copy this clip
	AudioClip newClip = *this;

	// reverse the new clip using stl
	reverse(newClip.begin(), newClip.end());

	return newClip;
}

template <typename T>
AudioClip<T> AudioClip<T>::rms(void) {

}

template <typename T>
AudioClip<T> AudioClip<T>::normalize(void) {

}

template <typename T>
AudioClip<T> AudioClip<T>::fadein(float r1, float r2) {

}

template <typename T>
AudioClip<T> AudioClip<T>::fadeout(float r1, float r2) {

}

template <typename T>
void AudioClip<T>::write(std::string outfile) {
	ofstream ofs = ofstream(outfile, ios::binary);

	for (T sample : samples) {
		ofs << sample;
	}

	ofs.close();
}