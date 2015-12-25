.PHONY: all clean
CC = gcc
CPPFLAGS = -g -Wall -std=c++11
#CPPFLAGS += -isystem $(GTEST_DIR)/include
FLAGS = -Wall -g -Wextra -pthread
GTEST_DIR = /usr/local
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all: task3

clean:
	rm -f task3 *.o #*.sce

task3: task3.o
	g++ $(CPPFLAGS) $^ -o $@

task3.o: task3.cc
	g++ $(CPPFLAGS) -c $<
