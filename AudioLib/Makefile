# Makefile for Audio Library
# Author: Mike James White

CC=g++
TARGET=libaudio.so
FLAGS=-fPIC -shared -std=c++11

$(TARGET): audio.hpp
	$(CC) $(FLAGS) -x c++ audio.hpp -o $(TARGET)

clean:
	rm -f *.o *.so