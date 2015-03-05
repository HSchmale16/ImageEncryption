# Makefile for Image Stenography and Encryption system
# \author Henry J Schmale
# \date 26 February 2015

CXX=g++
CXX_FLAGS= \
	-Wall \
	-std=c++11
LD_FLAGS= \
	-lm \
	-lpthread \
	-lX11

# Cryptography Stuff
CRYPT_SRCS= \
	mainCrypt.cpp
CRYPT_OBJS=$(CRYPT_SRCS:.cpp=.o)
CRYPT_EXE=Crypt

# Stenography Stuff
STENO_SRCS= \
	mainSteno.cpp
STENO_OBJS=$(STENO_SRCS:.cpp=.o)
STENO_EXE=Steno

# Primary Build Target
all: $(CRYPT_SRCS) \
     $(CRYPT_EXE)  \
	 $(STENO_SRCS) \
	 $(STENO_EXE)

$(CRYPT_EXE): $(CRYPT_OBJS)
	$(CXX) $(LD_FLAGS) -o $@ $(CRYPT_OBJS)

$(STENO_EXE): $(STENO_OBJS)
	$(CXX) $(LD_FLAGS) -o $@ $(STENO_OBJS)

# Rule to make *.cpp files
.cpp.o:
	$(CXX) -c $(CXX_FLAGS) -o $@ $<


# Get rid of object files and built executable
clean:
	if [ -e $(STENO_EXE) ] ; then rm $(STENO_EXE) ; fi
	if [ -e $(CRYPT_EXE) ] ; then rm $(CRYPT_EXE) ; fi
	if [ -e *.o ] ; then rm -r *.o ; fi
