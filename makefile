# makefile
# added capability to use makefile in various environments without modifications
SRCS=Game/Game.cpp Game/State.cpp Game/AI.cpp Game/Node.cpp Game/Tree.cpp
MAIN=Game/Server.cpp
CFLAGS= -std=c++11 -g -o
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    cc = clang++ -I/usr/local/boost -Wno-deprecated-register -Wno-format-security
else ifeq ($(UNAME), Darwin)
    cc = g++
else 
    cc = g++-4.7
endif
JCC = javac -d $(shell pwd) Game/GUI.java
JRUN = java -cp $(shell pwd) GUI

.PHONY: all breakthrough clean

all: breakthrough
	
breakthrough:
	$(cc) $(CFLAGS) breakthrough $(SRCS) $(MAIN)
	
gui:
	$(JCC) $(JSRCS)
	$(JRUN) $(JSRCS)

clean:
	rm -r *.o *.dSYM breakthrough
