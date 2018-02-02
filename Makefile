#
# This is the Makefile for NumericTable library.

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
#CFLAGS  = -g


# source files.
SOURCES = numeric_table.cpp


OBJECTS = $(SOURCES:.cpp=.o)

OUTPUT = libnumerictable.a

# include directories
#INCLUDES = -I. -I../include/ -I/usr/local/include
INCLUDES = numeric_table.h


# The file copy command (copy but do not delete original)
COPY = cp


# The make directory commmand
MKDIR = mkdir

# Directory for output of static library file
# Copy to system library path or add path to system library paths
LIBRARY_DIR = lib


# Directory for include header file
# Copy header files to system library path or add path to system include paths
INCLUDE_DIR = include



.SUFFIXES: .cpp

default: $(OUTPUT)

.cpp.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

$(OUTPUT): $(OBJECTS)
	ar rcs $(OUTPUT) $(OBJECTS)



manage:

	# Make new directories for libary and include headers
	$(MKDIR) $(LIBRARY_DIR)
	$(MKDIR) $(INCLUDE_DIR)

	$(COPY) $(OUTPUT) $(LIBRARY_DIR)
	$(COPY) $(INCLUDES) $(INCLUDE_DIR)

clean:
	rm -f $(OBJECT) Makefile~
