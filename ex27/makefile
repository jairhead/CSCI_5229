# Example 27
EXE=ex27

# Main target
all: $(EXE) vert.spv frag.spv

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lglfw3 -lvulkan-1 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES)
LIBS=-lglfw -lvulkan -lm
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglfw -lvulkan -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
ex27.o: ex27.c mat4.h
mat4.o: mat4.c mat4.h

# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
.cpp.o:
	g++ -c $(CFLG)  $<

#  Compile shaders
vert.spv:vulkan.vert
	glslangValidator -V -o vert.spv vulkan.vert
frag.spv:vulkan.frag
	glslangValidator -V -o frag.spv vulkan.frag
#  Link
ex27:ex27.o mat4.o 
	gcc $(CFLG) -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
