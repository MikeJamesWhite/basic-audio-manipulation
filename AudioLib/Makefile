# Makefile for Audio Library
# Author: Mike James White

CC=g++
TARGET=libaudio.so
FLAGS=-fPIC -shared -std=c++11

$(TARGET): audio.hpp
	$(CC) -o $(TARGET) audio.hpp $(FLAGS)

#mono.o: mono.hpp audio.h
#	$(CC) -c -o mono.o mono.hpp $(FLAGS)

#stereo.o: stereo.hpp audio.h
#	$(CC) -c -o stereo.o stereo.hpp $(FLAGS)

clean:
	rm -f *.o *.so