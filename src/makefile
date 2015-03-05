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
	mainCrypt.cpp \
	crypto.cpp
CRYPT_OBJS=$(CRYPT_SRCS:.cpp=.o)
CRYPT_EXE=Crypt

# Stenography Stuff
STENO_SRCS= \
	mainSteno.cpp \
	steno.cpp
STENO_OBJS=$(STENO_SRCS:.cpp=.o)
STENO_EXE=Steno

# combined executable stuff
# combines the funcion of both executables into one
COMBO_SRCS= \
	mainCombo.cpp \
	crypto.cpp \
	steno.cpp
COMBO_OBJS=$(COMBO_SRCS:.cpp=.o)
COMBO_EXE=ImageCrypt

# Primary Build Target, Builds Everything and all other targets
all: $(CRYPT_EXE)  \
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
