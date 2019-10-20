# Copyright 2019 Remus-Mihai Neatu

# compiler setup
CC=g++
CFLAGS=-Wall -Wextra 

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:%.cpp=%.o)
TARGETS=$(OBJS:%.o=%)

build: $(OBJS) $(TARGETS)

pack:
    zip -FSr 3XYCA_FirstnameLastname_Tema1.zip README Makefile *.cpp *.h

clean:
    rm -f $(TARGETS) $(OBJS)