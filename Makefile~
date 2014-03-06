UNAME := $(shell uname)

MacGLFramework = -framework Carbon -framework OpenGL -framework GLUT
LinuxGLFramework = -lGLEW -lglut -lGLU
GLFramework = NOTYETSET

Include = -I/usr/include/GL -I/usr/include -I'$$ORIGIN/SOIL/src'
Link = -L/usr/lib/ -L/usr/local/lib -lm -Wl,-rpath='L$$ORIGIN/SOIL/lib'
Flags = -g -o
Sources = src/*.cpp

# -Wl,-rpath='l$$ORIGIN/assimp/lib/assimp.so.3.0.1'
CC = g++
ExeName = pa1

# Define proper GL framework
ifeq ($(UNAME), Linux)
	GLFramework = $(LinuxGLFramework)
endif
ifeq ($(UNAME), Darwin)
	GLFramework = $(MacGLFramework)
endif

all: main

# Compiling
main:
	$(CC) $(Flags) $(ExeName) $(Sources) $(Include) $(Link) $(GLFramework)
	@echo "\n\n\n\t\tATTENTION \t\t\n"
	@echo "Change directory to src and run .pal\n"



clean:
	rm -f $(ExeName)
