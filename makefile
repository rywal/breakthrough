# makefile
# added capability to use makefile in various environments without modifications
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    cc = clang++
else ifeq ($(UNAME), Darwin)
    cc = g++
else
    cc = g++-4.7
endif

.PHONY: all game clean

all: game

game:
	$(cc) -std=c++11 -g -o breakthrough Game/Game.cpp

clean:
	rm -f *.o a.out breakthrough
