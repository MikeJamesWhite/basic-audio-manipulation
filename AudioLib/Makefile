# Makefile for Audio Library
# Author: Mike James White

CC=g++
TARGET=libaudio.so
FLAGS=-fPIC -shared -std=c++11

$(TARGET): audio.o
	$(CC) -o $(TARGET) audio.o $(FLAGS)

audio.o: audio.cpp audio.h
	$(CC) -c -o audio.o audio.cpp $(FLAGS)

clean:
	rm -f *.o *.so