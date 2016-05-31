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

EXEC = pool queue

pool : test_pool.o
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@

queue : test_queue.o
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@

%.o : %.cpp
	$(CC) -c $< $(CFLAGS) $(INCS) -o $@

clean:
	$(RM) $(OBJS) $(EXEC)


