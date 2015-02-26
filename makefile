# Makefile for image encrypter
# \author Henry J Schmale
# \date 26 February 2015

EXE=ImgCrypt
CXX_FLAGS=-std=c++11

all:
	g++ $(CXX_FLAGS) -o $(EXE) main.cpp

# Get rid of object files and built executable
clean:
	rm $(EXE)
	if [ -e *.o ] ; then rm -r *.o ; fi
