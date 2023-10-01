# MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW -I.
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32
CLEAN=rm *.exe *.o *.a
else
# OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=2 -I.
LIBS=-framework GLUT -framework OpenGL
# Linux/Unix/Solaris
else
CFLG=-O3 -Wall -I.
LIBS=-lglut -lGLU -lGL -lm
endif
# OSX/Linux/Unix/Solaris
CLEAN=rm -f hw3 *.o *.a
endif

#  Link
hw3:hw3.cpp PrimaryGraphicsHelper.cpp Cube.cpp RectangularPrism.cpp Sphere.cpp Sun.cpp Moon.cpp Star.cpp Road.cpp House.cpp DryGrass.cpp MountainBackdrop.cpp StreetLamp.cpp
	g++ $(CFLG) -o $@ $^ $(LIBS)

#  Clean
clean:
	$(CLEAN)
