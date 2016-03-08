.PHONY: all clean
CC = gcc
CPPFLAGS = -g -Wall -std=c++11
#CPPFLAGS += -isystem $(GTEST_DIR)/include
FLAGS = -Wall -g -Wextra -pthread
GTEST_DIR = /usr/local
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all: spline

clean:
	rm -f spline *.o #*.sce

spline: spline.o
	g++ $(CPPFLAGS) $^ -o $@

spline.o: spline.cc
	g++ $(CPPFLAGS) -c $<
