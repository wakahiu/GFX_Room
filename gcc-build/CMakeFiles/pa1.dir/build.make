# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wakahiu/Documents/Graphics/pa1_starter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wakahiu/Documents/Graphics/pa1_starter/gcc-build

# Include any dependencies generated for this target.
include CMakeFiles/pa1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pa1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pa1.dir/flags.make

CMakeFiles/pa1.dir/src/main.cpp.o: CMakeFiles/pa1.dir/flags.make
CMakeFiles/pa1.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/wakahiu/Documents/Graphics/pa1_starter/gcc-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/pa1.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pa1.dir/src/main.cpp.o -c /home/wakahiu/Documents/Graphics/pa1_starter/src/main.cpp

CMakeFiles/pa1.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pa1.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/wakahiu/Documents/Graphics/pa1_starter/src/main.cpp > CMakeFiles/pa1.dir/src/main.cpp.i

CMakeFiles/pa1.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pa1.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/wakahiu/Documents/Graphics/pa1_starter/src/main.cpp -o CMakeFiles/pa1.dir/src/main.cpp.s

CMakeFiles/pa1.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/pa1.dir/src/main.cpp.o.requires

CMakeFiles/pa1.dir/src/main.cpp.o.provides: CMakeFiles/pa1.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/pa1.dir/build.make CMakeFiles/pa1.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/pa1.dir/src/main.cpp.o.provides

CMakeFiles/pa1.dir/src/main.cpp.o.provides.build: CMakeFiles/pa1.dir/src/main.cpp.o

CMakeFiles/pa1.dir/src/trackball.cpp.o: CMakeFiles/pa1.dir/flags.make
CMakeFiles/pa1.dir/src/trackball.cpp.o: ../src/trackball.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/wakahiu/Documents/Graphics/pa1_starter/gcc-build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/pa1.dir/src/trackball.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pa1.dir/src/trackball.cpp.o -c /home/wakahiu/Documents/Graphics/pa1_starter/src/trackball.cpp

CMakeFiles/pa1.dir/src/trackball.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pa1.dir/src/trackball.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/wakahiu/Documents/Graphics/pa1_starter/src/trackball.cpp > CMakeFiles/pa1.dir/src/trackball.cpp.i

CMakeFiles/pa1.dir/src/trackball.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pa1.dir/src/trackball.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/wakahiu/Documents/Graphics/pa1_starter/src/trackball.cpp -o CMakeFiles/pa1.dir/src/trackball.cpp.s

CMakeFiles/pa1.dir/src/trackball.cpp.o.requires:
.PHONY : CMakeFiles/pa1.dir/src/trackball.cpp.o.requires

CMakeFiles/pa1.dir/src/trackball.cpp.o.provides: CMakeFiles/pa1.dir/src/trackball.cpp.o.requires
	$(MAKE) -f CMakeFiles/pa1.dir/build.make CMakeFiles/pa1.dir/src/trackball.cpp.o.provides.build
.PHONY : CMakeFiles/pa1.dir/src/trackball.cpp.o.provides

CMakeFiles/pa1.dir/src/trackball.cpp.o.provides.build: CMakeFiles/pa1.dir/src/trackball.cpp.o

CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o: CMakeFiles/pa1.dir/flags.make
CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o: ../src/GLScreenCapturer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/wakahiu/Documents/Graphics/pa1_starter/gcc-build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o -c /home/wakahiu/Documents/Graphics/pa1_starter/src/GLScreenCapturer.cpp

CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/wakahiu/Documents/Graphics/pa1_starter/src/GLScreenCapturer.cpp > CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.i

CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/wakahiu/Documents/Graphics/pa1_starter/src/GLScreenCapturer.cpp -o CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.s

CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o.requires:
.PHONY : CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o.requires

CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o.provides: CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o.requires
	$(MAKE) -f CMakeFiles/pa1.dir/build.make CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o.provides.build
.PHONY : CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o.provides

CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o.provides.build: CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o

# Object files for target pa1
pa1_OBJECTS = \
"CMakeFiles/pa1.dir/src/main.cpp.o" \
"CMakeFiles/pa1.dir/src/trackball.cpp.o" \
"CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o"

# External object files for target pa1
pa1_EXTERNAL_OBJECTS =

pa1: CMakeFiles/pa1.dir/src/main.cpp.o
pa1: CMakeFiles/pa1.dir/src/trackball.cpp.o
pa1: CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o
pa1: /usr/lib/x86_64-linux-gnu/libglut.so
pa1: /usr/lib/x86_64-linux-gnu/libXmu.so
pa1: /usr/lib/x86_64-linux-gnu/libXi.so
pa1: /usr/lib/x86_64-linux-gnu/libGLU.so
pa1: /usr/lib/x86_64-linux-gnu/libGL.so
pa1: /usr/lib/x86_64-linux-gnu/libSM.so
pa1: /usr/lib/x86_64-linux-gnu/libICE.so
pa1: /usr/lib/x86_64-linux-gnu/libX11.so
pa1: /usr/lib/x86_64-linux-gnu/libXext.so
pa1: CMakeFiles/pa1.dir/build.make
pa1: CMakeFiles/pa1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable pa1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pa1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pa1.dir/build: pa1
.PHONY : CMakeFiles/pa1.dir/build

CMakeFiles/pa1.dir/requires: CMakeFiles/pa1.dir/src/main.cpp.o.requires
CMakeFiles/pa1.dir/requires: CMakeFiles/pa1.dir/src/trackball.cpp.o.requires
CMakeFiles/pa1.dir/requires: CMakeFiles/pa1.dir/src/GLScreenCapturer.cpp.o.requires
.PHONY : CMakeFiles/pa1.dir/requires

CMakeFiles/pa1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pa1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pa1.dir/clean

CMakeFiles/pa1.dir/depend:
	cd /home/wakahiu/Documents/Graphics/pa1_starter/gcc-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wakahiu/Documents/Graphics/pa1_starter /home/wakahiu/Documents/Graphics/pa1_starter /home/wakahiu/Documents/Graphics/pa1_starter/gcc-build /home/wakahiu/Documents/Graphics/pa1_starter/gcc-build /home/wakahiu/Documents/Graphics/pa1_starter/gcc-build/CMakeFiles/pa1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pa1.dir/depend

