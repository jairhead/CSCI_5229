# Homework 5
EXE=hw5

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

OBJS := PrimaryGraphicsHelper.o Cube.o

# Default
default: all

# All
all: $(EXE)

# Dependencies
hw5.o: hw5.cpp

# Create archive / library
libhw5.a:$(OBJS)
	ar -rcs $@ $^

# Compile rules
.cpp.o:
	g++ -c $(CFLG)  $<

#  Link
hw5:hw5.o libhw5.a
	g++ $(CFLG) -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
