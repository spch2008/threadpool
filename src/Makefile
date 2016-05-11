CC=g++
RM=rm -rf
AR=ar

CFLAGS=-g -Wall
LDFLAGS=-pthread

INCDIR=../include
LIBDIR=../lib
INCS  =-I $(INCDIR)

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

LIBPREX=thread
LIBNAME=lib$(LIBPREX).a

EXEC = main

$(LIBNAME) : $(OBJS)
	$(AR) r $@ $?
	cp $(LIBNAME) $(LIBDIR)

%.o : %.cpp
	$(CC) -c $< $(CFLAGS) $(INCS) -o $@

clean:
	$(RM) $(OBJS) $(EXEC) $(LIBNAME)


