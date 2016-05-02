.PHONY: all clean
CC = g++
CPPFLAGS = -g -Wall -std=c++11
#CPPFLAGS += -isystem $(GTEST_DIR)/include
FLAGS = -Wall -g -Wextra -pthread
GTEST_DIR = /usr/local
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all: task6

clean:
	rm -f task6 test e *.o #*.sce

task6: task6.o
	$(CC) $(CPPFLAGS) $^ -o $@

task6.o: task6.cc
	$(CC) $(CPPFLAGS) -c $<

test: test.o
	$(CC) $(CPPFLAGS) $^ -o $@

test.o: test.cc
	$(CC) $(CPPFLAGS) -c $<
