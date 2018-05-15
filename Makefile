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
	./samp -r 44100 -b 8 -c 2 -o test -add $(SOUNDFILEDIR)/frogs18sec_44100_signed_8bit_stereo.raw $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_stereo.raw

cut: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 16 -c 2 -o test -cut 0 200000 $(SOUNDFILEDIR)/countdown40sec_44100_signed_16bit_stereo.raw

rangeadd: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -radd 3 5 14 16 $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_mono.raw $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_mono.raw

concatenate: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -cat $(SOUNDFILEDIR)/frogs18sec_44100_signed_8bit_mono.raw $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_mono.raw

volume: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 2 -o test -v 0.1 0.1 $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_stereo.raw

reverse: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 16 -c 1 -o test -rev $(SOUNDFILEDIR)/countdown40sec_44100_signed_16bit_mono.raw  

rms: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 16 -c 1 -o test -rms $(SOUNDFILEDIR)/countdown40sec_44100_signed_16bit_mono.raw  

norm: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 2 -o test -norm 4 15 $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_stereo.raw  

fadein: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 16 -c 2 -o test -fadein 10 $(SOUNDFILEDIR)/countdown40sec_44100_signed_16bit_stereo.raw  

fadeout: $(TARGET)mono
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp -r 44100 -b 8 -c 1 -o test -fadeout 30 $(SOUNDFILEDIR)/countdown40sec_44100_signed_8bit_mono.raw  

play:
	play -r 44100 -b 8 -c 1 -e signed test_44100_8_mono.raw

play16:
	play -r 44100 -b 16 -c 1 -e signed test_44100_16_mono.raw

play_st:
	play -r 44100 -b 8 -c 2 -e signed test_44100_8_stereo.raw

play_st16:
	play -r 44100 -b 16 -c 2 -e signed test_44100_16_stereo.raw
