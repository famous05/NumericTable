# This is the Makefile for the progam 'test_prog'.

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
#  for C++ define  CC = g++
CC = g++
#CC = win_g++



CFLAGS  = -g -Wall -std=c++14
#CFLAGS  = -g -Wall


#perferred progam name
PROG_NAME = nt_test


# typing 'make' will invoke the first target entry in the file
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: $(PROG_NAME)



# define header files
INCLUDES = -I../


LIB_PATH = -L../ -lnumerictable


#define the source files as all .cpp files in the current directory
SRCS = test.cpp


#define object file names from source file names
OBJS = $(SRCS:.c=.o)




# To create the executable file $(PROG_NAME) we need
# all the object files.
$(PROG_NAME):  $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG_NAME) $(SRCS) $(LIB_PATH) $(INCLUDES)


clean:
	$(RM) $(PROG_NAME) *.o *~

depend:$(SRCS)
	makedepend $(INCLUDES) $^
