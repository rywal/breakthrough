# makefile
# added capability to use makefile in various environments without modifications
SRCS=Game/Game.cpp Game/State.cpp Game/AI.cpp
MAIN1=Game/Client.cpp
MAIN2=Game/Server.cpp
CFLAGS=-std=c++11 -g -o
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    cc = clang++ -I/usr/local/boost
else ifeq ($(UNAME), Darwin)
    cc = g++
else
    cc = g++-4.7
endif

.PHONY: all client breakthrough clean

all: client breakthrough

client:
	$(cc) $(CFLAGS) client $(MAIN1) $(SRCS)
	
breakthrough:
	$(cc) $(CFLAGS) breakthrough $(MAIN2) $(SRCS)

clean:
	rm -r *.o *.dSYM client breakthrough
