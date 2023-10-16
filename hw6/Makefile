# Homework 6
EXE=hw6

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CXXFLAGS=-O3 -Wall -DUSEGLEW -I./include
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CXXFLAGS=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES) -I./include
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CXXFLAGS=-O3 -Wall -I./include
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Common variables
SRC_DIR := src
OBJ := hw6.o \
       PrimaryGraphicsHelper.o \
			 RectangularPrism.o \
			 Sphere.o

# Default
default: all

# All
all: $(EXE)

# Compile rules
%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c $< -o $@

# Create archive / library
libhw6.a: $(OBJ)
	ar -rcs $@ $^

# Link
$(EXE): $(OBJ) libhw6.a
	g++ $(CXXFLAGS) -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
