# makefile
# added capability to use makefile in various environments without modifications
SRCS=Game/Game.cpp Game/State.cpp Game/AI.cpp Game/Node.cpp Game/Tree.cpp
MAIN=Game/Server.cpp
CFLAGS=-std=c++11 -g -o
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    cc = clang++ -I/usr/local/boost
else ifeq ($(UNAME), Darwin)
    cc = g++
else 
    cc = g++-4.7
endif

.PHONY: all breakthrough clean

all: breakthrough
	
breakthrough:
	$(cc) $(CFLAGS) breakthrough $(SRCS) $(MAIN)

clean:
	rm -r *.o *.dSYM breakthrough
