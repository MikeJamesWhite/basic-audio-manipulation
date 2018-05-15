/**
 * Unit tests for basic-audio-manipulation
 * 
 * Author: Mike James White
 * Date: 12/05/2018
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "AudioLib/audio.hpp"

using namespace WHTMIC023;
using namespace std;

// File IO

TEST_CASE("File IO - 8bit mono") {
    AudioClip<int8_t> clip ("sample_input/siren40sec_44100_signed_8bit_mono.raw", 44100, 8);
    clip.write("test");

    AudioClip<int8_t> clip2 ("test_44100_signed_8bit_mono.raw", 44100, 8);

    bool same = true;
    auto iter = clip.begin();
    for (auto iter2 = clip2.begin(); iter2 != clip2.end(); iter2++) {
        if (*iter != *iter2) {
            same = false;
            break;
        }
        iter++;
    }

    if (iter != clip.end()) {
        same = false;
    }

    REQUIRE(same);
}

TEST_CASE("File IO - 16bit mono") {
    AudioClip<int8_t> clip ("sample_input/siren40sec_44100_signed_16bit_mono.raw", 44100, 16);
    clip.write("test");

    AudioClip<int8_t> clip2 ("test_44100_signed_16bit_mono.raw", 44100, 8);

    bool same = true;
    auto iter = clip.begin();
    for (auto iter2 = clip2.begin(); iter2 != clip2.end(); iter2++) {
        if (*iter != *iter2) {
            same = false;
            break;
        }
        iter++;
    }

    if (iter != clip.end()) {
        same = false;
    }

    REQUIRE(same);
}

TEST_CASE("File IO - 8bit stereo") {
    AudioClip< std::pair<int8_t, int8_t> > clip ("sample_input/siren40sec_44100_signed_8bit_stereo.raw", 44100, 8);
    clip.write("test");

    AudioClip< std::pair<int8_t, int8_t> > clip2 ("test_44100_signed_8bit_stereo.raw", 44100, 8);

    bool same = true;
    auto iter = clip.begin();
    for (auto iter2 = clip2.begin(); iter2 != clip2.end(); iter2++) {
        if (*iter != *iter2) {
            same = false;
            break;
        }
        iter++;
    }

    if (iter != clip.end()) {
        same = false;
    }

    REQUIRE(same);
}

TEST_CASE("File IO - 16bit stereo") {
    AudioClip< std::pair<int16_t, int16_t> > clip ("sample_input/siren40sec_44100_signed_16bit_stereo.raw", 44100, 16);
    clip.write("test");

    AudioClip< std::pair<int16_t, int16_t> > clip2 ("test_44100_signed_16bit_stereo.raw", 44100, 16);

    bool same = true;
    auto iter = clip.begin();
    for (auto iter2 = clip2.begin(); iter2 != clip2.end(); iter2++) {
        if (*iter != *iter2) {
            same = false;
            break;
        }
        iter++;
    }

    if (iter != clip.end()) {
        same = false;
    }

    REQUIRE(same);
}

// Basic operations & operators

TEST_CASE("Baic Operations - 8bit mono") {
    istringstream s1 ("5 12 14 13 15 16");
    AudioClip<int8_t> clip ("sample_input/siren40sec_44100_signed_16bit_mono.raw", 44100, 8);
    AudioClip<int8_t> clip2 ("sample_input/siren40sec_44100_signed_16bit_mono.raw", 44100, 8);

    auto iter = clip.begin();

    SECTION("Add") {
        AudioClip<int8_t> clip3 = clip + clip2;
        REQUIRE(*iter == 12);
    }

    SECTION("Concat") {
        AudioClip<int8_t> clip3 = clip | clip2;

        iter++;
        REQUIRE(*iter == 14);
        iter++;
        REQUIRE(*iter == 13);
    }

    SECTION("Cut") {
        AudioClip<int8_t> clip3 = clip ^ std::pair<int, int>(0, 2);
        auto iter3 = clip3.begin();

        REQUIRE(*iter == *iter3);
        REQUIRE(clip3.)
    }

    SECTION("Volume") {
        auto iter2 = iter;
        bool same = true;
        while (iter != i.end()) {
            if (*iter != *iter2)
                same = false;
            iter++;
            iter2++;
        }
        REQUIRE(same);
    }
}

// Move & Copy Semantics

TEST_CASE("Copying") {
    istringstream s ("5 12 14 13 15 16");
    Image i(s);
    Image j (i);

    auto iter = j.begin();
    REQUIRE(*iter == 12);
    iter++;
    REQUIRE(*iter == 14);
    iter++;
    REQUIRE(*iter == 13);
    iter++;
    REQUIRE(*iter == 15);
    iter++;
    REQUIRE(*iter == 16);
}

TEST_CASE("Moving") {
    istringstream s ("5 12 14 13 15 16");
    Image i(s);
    Image j = move(i);

    auto iter = j.begin();
    REQUIRE(*iter == 12);
    iter++;
    REQUIRE(*iter == 14);
    iter++;
    REQUIRE(*iter == 13);
    iter++;
    REQUIRE(*iter == 15);
    iter++;
    REQUIRE(*iter == 16);
}

// Image operations

TEST_CASE("Image Operations") {
    istringstream s1 ("5 12 14 13 15 16");
    Image i(s1);

    SECTION("Addition") {
        istringstream s2 ("5 12 14 13 15 255");
        Image j(s2);
        Image k = Image::add(i,j);
        auto iter = k.begin();
        REQUIRE(*iter == 24);
        iter++;
        REQUIRE(*iter == 28);
        iter++;
        REQUIRE(*iter == 26);
        iter++;
        REQUIRE(*iter == 30);
        iter++;
        REQUIRE(*iter == 255);
    }
    SECTION("Subtraction") {
        istringstream s2 ("5 10 12 10 11 255");
        Image j(s2);
        Image k = Image::subtract(i,j);
        auto iter = k.begin();
        REQUIRE(*iter == 2);
        iter++;
        REQUIRE(*iter == 2);
        iter++;
        REQUIRE(*iter == 3);
        iter++;
        REQUIRE(*iter == 4);
        iter++;
        REQUIRE(*iter == 0);
    }
    SECTION("Masking") {
        istringstream s2 ("5 0 0 255 0 255");
        Image j(s2);
        Image k = Image::mask(i,j);
        auto iter = k.begin();
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 13);
        iter++;
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 16);
    }
    SECTION("Thresholding") {
        int t = 12;
        Image k = Image::threshold(i, t);
        auto iter = k.begin();
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
    }
    SECTION("Inverting") {
        Image k = Image::invert(i);
        auto iter = k.begin();
        REQUIRE(*iter == 255 - 12);
        iter++;
        REQUIRE(*iter == 255 - 14);
        iter++;
        REQUIRE(*iter == 255 - 13);
        iter++;
        REQUIRE(*iter == 255 - 15);
        iter++;
        REQUIRE(*iter == 255 - 16);
    }
    SECTION("Filtering") {
        istringstream s2("5 120 126 170 200 250");
        Image j (s2);
        Image k = Image::filter(j, Filter("./sample_filters/unity.fir"));
        auto iter = k.begin();
        REQUIRE(*iter == 120);
        iter++;
        REQUIRE(*iter == 126);
        iter++;
        REQUIRE(*iter == 170);
        iter++;
        REQUIRE(*iter == 200);
        iter++;
        REQUIRE(*iter == 250);
    }
}

// Image operator overloads

TEST_CASE("Image Operator Overloads") {
    istringstream s1 ("5 12 14 13 15 16");
    Image i(s1);

    SECTION("Addition") {
        istringstream s2 ("5 12 14 13 15 255");
        Image j(s2);
        Image k = i+j;
        auto iter = k.begin();
        REQUIRE(*iter == 24);
        iter++;
        REQUIRE(*iter == 28);
        iter++;
        REQUIRE(*iter == 26);
        iter++;
        REQUIRE(*iter == 30);
        iter++;
        REQUIRE(*iter == 255);
    }
    SECTION("Subtraction") {
        istringstream s2 ("5 10 12 10 11 255");
        Image j(s2);
        Image k = i-j;
        auto iter = k.begin();
        REQUIRE(*iter == 2);
        iter++;
        REQUIRE(*iter == 2);
        iter++;
        REQUIRE(*iter == 3);
        iter++;
        REQUIRE(*iter == 4);
        iter++;
        REQUIRE(*iter == 0);
    }
    SECTION("Masking") {
        istringstream s2 ("5 0 0 255 0 255");
        Image j(s2);
        Image k = i/j;
        auto iter = k.begin();
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 13);
        iter++;
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 16);
    }
    SECTION("Thresholding") {
        int t = 12;
        Image k = i * t;
        auto iter = k.begin();
        REQUIRE(*iter == 0);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
        iter++;
        REQUIRE(*iter == 255);
    }
    SECTION("Inverting") {
        Image k = !i;
        auto iter = k.begin();
        REQUIRE(*iter == 255 - 12);
        iter++;
        REQUIRE(*iter == 255 - 14);
        iter++;
        REQUIRE(*iter == 255 - 13);
        iter++;
        REQUIRE(*iter == 255 - 15);
        iter++;
        REQUIRE(*iter == 255 - 16);
    }
    SECTION("Filtering") {
        istringstream s2("5 120 126 170 200 250");
        Image j (s2);
        Image k = j % Filter("./sample_filters/unity.fir");
        auto iter = k.begin();
        REQUIRE(*iter == 120);
        iter++;
        REQUIRE(*iter == 126);
        iter++;
        REQUIRE(*iter == 170);
        iter++;
        REQUIRE(*iter == 200);
        iter++;
        REQUIRE(*iter == 250);

    }
}
