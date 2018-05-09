# Makefile for basic-audio-manipulation
# Author: Mike James White (WHTMIC023)

CC=g++
TARGET=samp
LIB = ./AudioLib
FLAGS=-std=c++11 -I ./AudioLib -L ./AudioLib -laudio

.PHONY: clean

$(TARGET): driver.o
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

run: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp testinput.txt testoutput

encode: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp testinput.txt testoutput -e

decode: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp testoutput decoded.txt -d

bitEncode: $(TARGET)
	export LD_LIBRARY_PATH=$(LIB)/; \
	./samp testinput.txt testoutput -be