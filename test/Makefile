CC=g++
RM=rm -rf
AR=ar

CFLAGS=-g -Wall
LDFLAGS=-lthread -pthread

INCDIR=../include
LIBDIR=../lib

INCS=-I $(INCDIR)
LIBS=-L $(LIBDIR)

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

LIBPREX=thread
LIBNAME=lib$(LIBPREX).a

EXEC = main

$(EXEC) : $(OBJS)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@

%.o : %.cpp
	$(CC) -c $< $(CFLAGS) $(INCS) -o $@

clean:
	$(RM) $(OBJS) $(EXEC)


