# Homework 4
EXE=hw4

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW -I.
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES) -I.
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall -I.
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

OBJS := PrimaryGraphicsHelper.o \
				ProjectionManager.o \
				RectangularPrism.o \
				Cube.o \
				Sphere.o \
        Sun.o \
				Moon.o \
				Star.o \
				Road.o \
				House.o \
				DryGrass.o \
				MountainBackdrop.o \
				StreetLamp.o

# Default
default: all

# All
all: $(EXE)

# Dependencies
hw4.o: hw4.cpp

# Create archive / library
libhw4.a:$(OBJS)
	ar -rcs $@ $^

# Compile rules
.cpp.o:
	g++ -c $(CFLG)  $<

#  Link
hw4:hw4.o libhw4.a
	g++ $(CFLG) -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
