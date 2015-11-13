.PHONY: all clean
CC = gcc
CPPFLAGS = -g -Wall -std=c++11
#CPPFLAGS += -isystem $(GTEST_DIR)/include
FLAGS = -Wall -g -Wextra -pthread
GTEST_DIR = /usr/local
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all: task2

clean:
	rm -f task2 *.o #*.sce

task2: task2.o
	g++ $(CPPFLAGS) $^ -o $@

task1.o: task2.cc
	g++ $(CPPFLAGS) -c $<
