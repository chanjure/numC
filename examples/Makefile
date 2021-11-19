#===================#
# Makefile for c++  #
# Jan, 9, 2020      #
# Chanju Park       #
# LGTRC, SNU        #
#===================#

# Including gsl library

CC = g++
CFLAGS = -g -O3 -Wall -fexceptions
LDLIBS = -L/usr/local/lib -lnumC -lgsl -lgslcblas -lm # Hirachy from right to left

SRCS := $(wildcard *.C)
HDRS := $(wildcard *.h)
OBJS := $(SRCS:%.cpp=%.o)

TARGET := a.out #$(SRCS:%.cpp=%.out)

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

clean :
	rm -f *.o  *~
	rm -f $(TARGET)

