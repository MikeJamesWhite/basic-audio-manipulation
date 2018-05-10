/**
 * Implementation file for the stereo AudioClip
 *
 * Author: Mike James White
 * Date: 09/05/2018
 */

#include "audio.h"

using namespace WHTMIC023;
using namespace std;

template <typename T>
AudioClip< pair<T,T> >::AudioClip(std::string filename, int sampleRate, int bitCount) : sampleRate(sampleRate), bitCount(bitCount) {
	ifstream in = ifstream(filename, ios::binary);
	T left, right;
	int fileSize;
	numSamples; // divide by two because there are two channels

	samples.reserve(numSamples);
	for (int i = 0; i < numSamples; i++) {
		in >> left;
		in >> right;
		samples[i] = pair<T,T>(left, right);
	}

	in.close();
}

template <typename T>
AudioClip< pair<T,T> > AudioClip< pair<T,T> >::add(AudioClip& otherClip) {

}

template <typename T>
AudioClip< pair<T,T> > AudioClip< pair<T,T> >::cut(float r1, float r2) {

}

template <typename T>
AudioClip< pair<T,T> > AudioClip< pair<T,T> >::rangeadd(AudioClip& otherClip, float r1, float r2, float s1, float s2) {

}

template <typename T>
AudioClip< pair<T,T> > AudioClip< pair<T,T> >::concatenate(AudioClip& otherClip) {

}

template <typename T>
AudioClip< pair<T,T> > AudioClip< pair<T,T> >::volume(float v1, float v2) {

}

template <typename T>
AudioClip< pair<T,T> > AudioClip< pair<T,T> >::reverse(void) {
	// copy this clip
	AudioClip newClip = *this;

	// reverse the new clip using stl
	reverse(newClip.begin(), newClip.end());

	return newClip;
}

template <typename T>
AudioClip< pair<T,T> > AudioClip< pair<T,T> >::rms(void) {

}

template <typename T>
AudioClip< pair<T,T> > AudioClip< pair<T,T> >::normalize(void) {

}

template <typename T>
AudioClip< pair<T,T> > AudioClip< pair<T,T> >::fadein(float r1, float r2) {

}

template <typename T>
AudioClip< pair<T,T> > AudioClip< pair<T,T> >::fadeout(float r1, float r2) {

}

template <typename T>
void AudioClip< pair<T,T> >::write(std::string outfile) {
	ofstream ofs = ofstream(outfile, ios::binary);

	for (pair<T,T> sample : samples) {
		ofs << sample.first;
		ofs << sample.second;
	}

	ofs.close();
}