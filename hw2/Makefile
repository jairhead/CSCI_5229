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
CLEAN=rm -f hw2 *.o *.a
endif

#  Compile and link
hw2:hw2.cpp LorenzAttractorHelper.cpp
	g++ $(CFLG) -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)
