.PHONY: all clean
CC = g++
CPPFLAGS = -g -Wall -std=c++11
#CPPFLAGS += -isystem $(GTEST_DIR)/include
FLAGS = -Wall -g -Wextra -pthread
GTEST_DIR = /usr/local
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all: lu

clean:
	rm -f lu *.o #*.sce

lu: lu.o
	$(CC) $(CPPFLAGS) $^ -o $@

lu.o: lu.cc matrix.h
	$(CC) $(CPPFLAGS) -c $<
