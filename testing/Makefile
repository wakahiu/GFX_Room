UNAME := $(shell uname)

MacGLFramework = -framework Carbon -framework OpenGL -framework GLUT
LinuxGLFramework = -lGLEW -lglut -lGLU
GLFramework = NOTYETSET

Include = -I/usr/include/GL -I/usr/include -I/usr/include/assimp
Link = -L/usr/lib/ -lassimp -L/usr/local/lib -lm
Flags = -g -o
Sources = *.cpp

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
	./$(ExeName)



clean:
	rm -f $(ExeName)
