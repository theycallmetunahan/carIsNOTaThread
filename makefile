CC = g++
CXXFLAGS = -std=c++14
LDFLAGS = -pthread

OBJS = main.o path.o car.o ferry.o crossroad.o bridge.o WriteOutput.o helper.o

all: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o simulator

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o simulator

test-mac:
	for i in {0..10}; do \
		./simulator < io/inputs/input$$i.txt > output-mac/output$$i.txt; \
	done

SHELL := /bin/bash

test-ubuntu:
	for i in {0..10}; do \
		./simulator < io/inputs/input$$i.txt > output-ubuntu/output$$i.txt; \
	done

