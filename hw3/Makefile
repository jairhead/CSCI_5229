#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW -I.
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32
CLEAN=rm *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=2 -I.
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall -I.
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f hw3 *.o *.a
endif

TARGETS := hw3.o Sun.o Moon.o Star.o Cube.o RectangularPrism.o Sphere.o Road.o House.o DryGrass.o MountainBackdrop.o StreetLamp.o PrimaryGraphicsHelper.o

# Compile rules
.cpp.o:
	g++ -c $(CFLG) $<

#  Link
hw3: $(TARGETS)
	g++ $(CFLG) -o $@ $^ $(LIBS)

#  Clean
clean:
	$(CLEAN)
