# Makefile for image encrypter
# \author Henry J Schmale
# \date 26 February 2015

CXX=g++
CXX_FLAGS= \
	-Wall \
	-std=c++11 \
	-O2 \
	-s	
LD_FLAGS= \
	-lm \
	-lpthread \
	-lX11
SOURCES= \
	main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXE=ImgCrypt

# Primary Build Target
all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(LD_FLAGS) -o $@ $(OBJECTS)

.cpp.o:
	$(CXX) -c $(CXX_FLAGS) -o $@ $<


# Get rid of object files and built executable
clean:
	if [ -e $(EXE) ] ; then rm $(EXE) ; fi
	if [ -e *.o ] ; then rm -r *.o ; fi
