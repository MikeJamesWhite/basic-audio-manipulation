# Makefile for Audio Library
# Author: Mike James White

CC=g++
TARGET=libaudio.so
FLAGS=-fPIC -shared -std=c++11

$(TARGET): mono.o stereo.o
	$(CC) -o $(TARGET) mono.o stereo.o $(FLAGS)

mono.o: mono.cpp audio.h
	$(CC) -c -o mono.o mono.cpp $(FLAGS)

stereo.o: stereo.cpp audio.h
	$(CC) -c -o stereo.o stereo.cpp $(FLAGS)

clean:
	rm -f *.o *.so