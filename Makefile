# compiler to use
CC = gcc
# name for executable
EXE = lexer
# each of which should be prefixed with -l
LIBS =
# space-separated list of source files
SRCS = lexer.c
 
# automatically generated list of object files
OBJS = $(SRCS:.c=.o)
 
 
# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(LIBS)
 
# dependencies 
$(OBJS): $(HDRS) Makefile
 
# housekeeping
clean:
	rm -f core $(EXE) *.o
