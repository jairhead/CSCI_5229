# Final project
EXE=final_project

# Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CXXFLAGS=-O3 -Wall -DUSEGLEW -I./include
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32
CLEAN=rm -f *.exe *.o *.a
else
# OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CXXFLAGS=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES) -I./include
LIBS=-framework GLUT -framework OpenGL
# Linux/Unix/Solaris
else
CXXFLAGS=-O3 -Wall -I./include
LIBS=-lglut -lGLU -lGL -lm
endif
# OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Objects to include in library
OBJ := final_project.o \
       PrimaryGraphicsHelper.o \
			 Utilities.o \
			 ProjectionManager.o \
			 LightManager.o \
			 WeatherData.o \
			 WeatherUpdater.o \
			 Scene.o \
			 Axes.o \
			 RectangularPrism.o \
			 Sphere.o \
			 AnalogClock.o \
			 SkyBox.o \
			 LightRain.o
SRC_DIR := src

# Default
default: all

# All
all: $(EXE)

# Compile rules
%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c $< -o $@

# Create archive / library
libweather.a: $(OBJ)
	ar -rcs $@ $^

# Link
$(EXE): libweather.a
	g++ $(CXXFLAGS) -o $@ $^ $(LIBS)

#  Clean
clean:
	$(CLEAN)
