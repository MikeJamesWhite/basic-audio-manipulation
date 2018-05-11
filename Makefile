# Makefile for basic-audio-manipulation
# Author: Mike James White (WHTMIC023)

CC=g++
TARGET=samp
LIB = ./AudioLib
FLAGS=-std=c++11 -I ./AudioLib -L ./AudioLib -laudio
SOUNDFILEDIR=./sample_input

.PHONY: clean

$(TARGET): driver.o $(LIB)/audio.hpp
	make -C $(LIB)
	$(CC) -o $(TARGET) driver.o $(FLAGS)

driver.o: driver.cpp
	make -C $(LIB)
	$(CC) -c -o driver.o driver.cpp $(FLAGS)

tests: tests.cpp
	make -C $(LIB)
	$(CC) -o testRunner tests.cpp $(FLAGS)
	export LD_LIBRARY_PATH=$(LIB); \
	./testRunner -s

clean:
	rm -f *.o ./$(TARGET) ./testRunner
	make -C $(LIB) clean

add: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -add $(SOUNDFILEDIR)/frogs18sec_44100_signed_8bit_mono.raw $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_mono.raw $(SOUNDFILEDIR)/frogs18sec_44100_signed_8bit_mono.raw $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_mono.raw

cut: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -cut 0 200000 $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_mono.raw $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_mono.raw $(SOUNDFILEDIR)/frogs18sec_44100_signed_8bit_mono.raw $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_mono.raw

rangeadd: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -radd range1 range2 range3 range4 inputFile inputFile2

concatenate: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -cat $(SOUNDFILEDIR)/frogs18sec_44100_signed_8bit_mono.raw $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_mono.raw

volume: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -v 0.5 0.5 $(SOUNDFILEDIR)/frogs18sec_44100_signed_8bit_mono.raw $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_mono.raw

reverse: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 16 -c 1 -o test -rev $(SOUNDFILEDIR)/countdown40sec_44100_signed_16bit_mono.raw  

reverse_st: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 16 -c 2 -o test -rev $(SOUNDFILEDIR)/countdown40sec_44100_signed_16bit_stereo.raw  

rms: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -rms inputFile  

norm: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -norm rms1 rms2 inputFile  

fadein: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -fadein numSeconds inputFile  

fadeout: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -fadeout numSeconds inputFile  

play:
	play -r 44100 -b 8 -c 1 -e signed test_44100_8_mono.raw

play16:
	play -r 44100 -b 16 -c 1 -e signed test_44100_16_mono.raw

play_st:
	play -r 44100 -b 8 -c 2 -e signed test_44100_8_stereo.raw

play_st16:
	play -r 44100 -b 16 -c 2 -e signed test_44100_16_stereo.raw
