# Makefile for Image Stenography and Encryption system
# \author Henry J Schmale
# \date 26 February 2015

# Shell Setup
SHELL=/bin/bash -O extglob -c

# Compiler Setup
CXX=g++
CXX_FLAGS= \
	-std=c++11
LD_FLAGS= \
	-lm \
	-lpthread \
	-lX11

# Cryptography Stuff
CRYPT_SRCS= \
	mainCrypt.cpp \
	crypto.cpp \
	fileHandler.cpp
CRYPT_OBJS=$(CRYPT_SRCS:.cpp=.o)
CRYPT_EXE=Crypt

# Stenography Stuff
STENO_SRCS= \
	mainSteno.cpp \
	steno.cpp \
	fileHandler.cpp
STENO_OBJS=$(STENO_SRCS:.cpp=.o)
STENO_EXE=Steno

# combined executable stuff
# combines the funcion of both executables into one
COMBO_SRCS= \
	mainCombo.cpp \
	crypto.cpp \
	steno.cpp \
	fileHandler.cpp
COMBO_OBJS=$(COMBO_SRCS:.cpp=.o)
COMBO_EXE=ImgCrypt

# ALL OF THE SOURCE CODE
ALLSRC=$(shell ls *.+(cpp|h) )

# Primary Build Target, Builds Everything and all other targets
all: depend \
	 $(CRYPT_EXE)  \
	 $(STENO_EXE) \
	 $(COMBO_EXE)

$(CRYPT_EXE): $(CRYPT_SRCS) $(CRYPT_OBJS)
	$(CXX) $(LD_FLAGS) -o $@ $(CRYPT_OBJS)

$(STENO_EXE): $(STENO_SRCS)  $(STENO_OBJS)
	$(CXX) $(LD_FLAGS) -o $@ $(STENO_OBJS)

$(COMBO_EXE): $(COMBO_SRCS) $(COMBO_OBJS)
	$(CXX) $(LD_FLAGS) -o $@ $(COMBO_OBJS)

# Rule to make *.cpp files
.cpp.o:
	$(CXX) -c $(CXX_FLAGS) -o $@ $<


# Get rid of object files and built executables if they exist
clean:
	if [ -e $(STENO_EXE) ] ; then rm -f $(STENO_EXE) ; fi
	if [ -e $(CRYPT_EXE) ] ; then rm -f $(CRYPT_EXE) ; fi
	if [ -e $(COMBO_EXE) ] ; then rm -f $(COMBO_EXE) ; fi
	rm -rf *.o

depend: .depend

.depend: $(ALLSRC)
	rm -f ./.depend
	$(CXX) $(CXX_FLAGS) -MM $^ > ./.depend

include .depend 
