# makefile
# added capability to use makefile in various environments without modifications
SRCS=Game/Game.cpp Game/State.cpp Game/AI.cpp
MAIN1=Game/Server.cpp
MAIN2=Game/Parser.cpp
CFLAGS=-std=c++11 -g -o
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    cc = clang++ -I/usr/local/boost
else ifeq ($(UNAME), Darwin)
    cc = g++
else
    cc = g++-4.7
endif

.PHONY: all game parser clean

all: game parser

game:
	$(cc) $(CFLAGS) breakthrough $(MAIN1) $(SRCS)
	
parser:
	$(cc) $(CFLAGS) par $(MAIN2) $(SRCS)

clean:
	rm -f *.o breakthrough par
