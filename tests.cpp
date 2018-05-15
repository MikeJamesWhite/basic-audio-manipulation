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
    AudioClip<int8_t> clip ("sample_input/siren40sec_44100_signed_8bit_mono.raw", 44100, 8);
    AudioClip<int8_t> clip2 ("sample_input/siren40sec_44100_signed_8bit_mono.raw", 44100, 8);

    auto iter = clip.begin();

    SECTION("Add") {
        AudioClip<int8_t> clip3 = clip + clip2;
        auto iter2 = clip2.begin();
        auto iter3 = clip3.begin();

        for (int i = 0; i < 5; i++) {
            REQUIRE(*iter3 == (*iter + *iter2) );
            iter++;
            iter2++;
            iter3++;
        }
    }

    SECTION("Concat") {
        AudioClip<int8_t> clip3 = clip | clip2;
        auto iter2 = clip2.begin();
        auto iter3 = clip3.begin();

        bool correct = true;

        while (iter != clip.end()) {
            if (*iter != *iter3)
                correct = false;
            iter++;
            iter3++;
        }

        while (iter2 != clip2.end()) {
            if (*iter2 != *iter3)
                correct = false;
            iter2++;
            iter3++;
        }

        REQUIRE(correct);

    }

    SECTION("Cut") {
        AudioClip<int8_t> clip3 = clip ^ std::pair<int, int>(0, 2);
        auto iter3 = clip3.begin();

        REQUIRE(*iter == *iter3);
        iter3++;
        iter3++;
        iter3++;
        REQUIRE(iter3 == clip3.end());
    }

    SECTION("Volume") {
        AudioClip<int8_t> clip3 = clip * std::pair<float, float>(0.5f, 0.5f);

        auto iter3 = clip3.begin();
        bool correct = true;
        while (iter != clip.end()) {
            if (*iter != (*iter3)*2)
                correct = false;
            iter++;
            iter3++;
        }
        REQUIRE(correct);
    }
}

TEST_CASE("Baic Operations - 16bit mono") {
    AudioClip<int16_t> clip ("sample_input/siren40sec_44100_signed_16bit_mono.raw", 44100, 16);
    AudioClip<int16_t> clip2 ("sample_input/siren40sec_44100_signed_16bit_mono.raw", 44100, 16);

    auto iter = clip.begin();

    SECTION("Add") {
        AudioClip<int16_t> clip3 = clip + clip2;
        auto iter2 = clip2.begin();
        auto iter3 = clip3.begin();

        for (int i = 0; i < 5; i++) {
            REQUIRE(*iter3 == (*iter + *iter2) );
            iter++;
            iter2++;
            iter3++;
        }
    }

    SECTION("Concat") {
        AudioClip<int16_t> clip3 = clip | clip2;
        auto iter2 = clip2.begin();
        auto iter3 = clip3.begin();

        bool correct = true;

        while (iter != clip.end()) {
            if (*iter != *iter3)
                correct = false;
            iter++;
            iter3++;
        }

        while (iter2 != clip2.end()) {
            if (*iter2 != *iter3)
                correct = false;
            iter2++;
            iter3++;
        }

        REQUIRE(correct);
    }

    SECTION("Cut") {
        AudioClip<int16_t> clip3 = clip ^ std::pair<int, int>(0, 2);
        auto iter3 = clip3.begin();

        REQUIRE(*iter == *iter3);
        iter3++;
        iter3++;
        iter3++;
        REQUIRE(iter3 == clip3.end());
    }

    SECTION("Volume") {
        AudioClip<int16_t> clip3 = clip * std::pair<float, float>(0.5f, 0.5f);

        auto iter3 = clip3.begin();
        bool correct = true;
        while (iter != clip.end()) {
            if (*iter != (*iter3)*2)
                correct = false;
            iter++;
            iter3++;
        }
        REQUIRE(correct);
    }
}

TEST_CASE("Baic Operations - 8bit stereo") {
    AudioClip<std::pair<int8_t, int8_t> > clip ("sample_input/siren40sec_44100_signed_8bit_stero.raw", 44100, 8);
    AudioClip<std::pair<int8_t, int8_t> > clip2 ("sample_input/siren40sec_44100_signed_8bit_stereo.raw", 44100, 8);

    auto iter = clip.begin();

    SECTION("Add") {
        AudioClip<std::pair<int8_t, int8_t>> clip3 = clip + clip2;
        auto iter2 = clip2.begin();
        auto iter3 = clip3.begin();

        for (int i = 0; i < 5; i++) {
            REQUIRE(iter3 -> first == (iter -> first + iter2 -> first) );
            iter++;
            iter2++;
            iter3++;
        }
    }

    SECTION("Concat") {
        AudioClip<std::pair<int8_t, int8_t>> clip3 = clip | clip2;
        auto iter2 = clip2.begin();
        auto iter3 = clip3.begin();

        bool correct = true;

        while (iter != clip.end()) {
            if (*iter != *iter3)
                correct = false;
            iter++;
            iter3++;
        }

        while (iter2 != clip2.end()) {
            if (*iter2 != *iter3)
                correct = false;
            iter2++;
            iter3++;
        }

        REQUIRE(correct);

    }

    SECTION("Cut") {
        AudioClip<std::pair<int8_t, int8_t>> clip3 = clip ^ std::pair<int, int>(0, 2);
        auto iter3 = clip3.begin();

        REQUIRE(*iter == *iter3);
        iter3++;
        iter3++;
        iter3++;
        REQUIRE(iter3 == clip3.end());
    }

    SECTION("Volume") {
        AudioClip<std::pair<int8_t, int8_t>> clip3 = clip * std::pair<float, float>(0.5f, 0.5f);

        auto iter3 = clip3.begin();
        bool correct = true;
        while (iter != clip.end()) {
            if (iter -> first != iter3 -> first * 2)
                correct = false;
            if (iter -> second != iter3 -> second * 2)
                correct = false;
            iter++;
            iter3++;
        }
        REQUIRE(correct);
    }
}

TEST_CASE("Baic Operations - 16bit stereo") {
    AudioClip<std::pair<int16_t, int16_t> > clip ("sample_input/siren40sec_44100_signed_16bit_stereo.raw", 44100, 16);
    AudioClip<std::pair<int16_t, int16_t> > clip2 ("sample_input/siren40sec_44100_signed_16bit_stereo.raw", 44100, 16);

    auto iter = clip.begin();

    SECTION("Add") {
        AudioClip<std::pair<int16_t, int16_t> > clip3 = clip + clip2;
        auto iter2 = clip2.begin();
        auto iter3 = clip3.begin();

        for (int i = 0; i < 5; i++) {
            REQUIRE(iter3 -> first == (iter -> first + iter2 -> first) );
            iter++;
            iter2++;
            iter3++;
        }
    }

    SECTION("Concat") {
        AudioClip<std::pair<int16_t, int16_t> > clip3 = clip | clip2;
        auto iter2 = clip2.begin();
        auto iter3 = clip3.begin();

        bool correct = true;

        while (iter != clip.end()) {
            if (*iter != *iter3)
                correct = false;
            iter++;
            iter3++;
        }

        while (iter2 != clip2.end()) {
            if (*iter2 != *iter3)
                correct = false;
            iter2++;
            iter3++;
        }

        REQUIRE(correct);
    }

    SECTION("Cut") {
        AudioClip<std::pair<int16_t, int16_t> > clip3 = clip ^ std::pair<int, int>(0, 2);
        auto iter3 = clip3.begin();

        REQUIRE(*iter == *iter3);
        iter3++;
        iter3++;
        iter3++;
        REQUIRE(iter3 == clip3.end());
    }

    SECTION("Volume") {
        AudioClip<std::pair<int16_t, int16_t> > clip3 = clip * std::pair<float, float>(0.5f, 0.5f);

        auto iter3 = clip3.begin();
        bool correct = true;
        while (iter != clip.end()) {
            if (iter -> first != iter3 -> first * 2)
                correct = false;
            if (iter -> second != iter3 -> second * 2)
                correct = false;
            iter++;
            iter3++;
        }
        REQUIRE(correct);
    }
}

// RMS & Normalization

TEST_CASE("RMS") {

}

TEST_CASE("Normalization") {

}

// Fadein & Fadeout
TEST_CASE("Fadein") {

}

TEST_CASE("Fadeout") {

}