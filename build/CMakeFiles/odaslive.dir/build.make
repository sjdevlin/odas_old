# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/odas

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/odas/build

# Include any dependencies generated for this target.
include CMakeFiles/odaslive.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/odaslive.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/odaslive.dir/flags.make

CMakeFiles/odaslive.dir/demo/odaslive/main.o: CMakeFiles/odaslive.dir/flags.make
CMakeFiles/odaslive.dir/demo/odaslive/main.o: ../demo/odaslive/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/odas/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/odaslive.dir/demo/odaslive/main.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/odaslive.dir/demo/odaslive/main.o   -c /home/pi/odas/demo/odaslive/main.c

CMakeFiles/odaslive.dir/demo/odaslive/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/odaslive.dir/demo/odaslive/main.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/odas/demo/odaslive/main.c > CMakeFiles/odaslive.dir/demo/odaslive/main.i

CMakeFiles/odaslive.dir/demo/odaslive/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/odaslive.dir/demo/odaslive/main.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/odas/demo/odaslive/main.c -o CMakeFiles/odaslive.dir/demo/odaslive/main.s

CMakeFiles/odaslive.dir/demo/odaslive/configs.o: CMakeFiles/odaslive.dir/flags.make
CMakeFiles/odaslive.dir/demo/odaslive/configs.o: ../demo/odaslive/configs.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/odas/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/odaslive.dir/demo/odaslive/configs.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/odaslive.dir/demo/odaslive/configs.o   -c /home/pi/odas/demo/odaslive/configs.c

CMakeFiles/odaslive.dir/demo/odaslive/configs.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/odaslive.dir/demo/odaslive/configs.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/odas/demo/odaslive/configs.c > CMakeFiles/odaslive.dir/demo/odaslive/configs.i

CMakeFiles/odaslive.dir/demo/odaslive/configs.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/odaslive.dir/demo/odaslive/configs.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/odas/demo/odaslive/configs.c -o CMakeFiles/odaslive.dir/demo/odaslive/configs.s

CMakeFiles/odaslive.dir/demo/odaslive/objects.o: CMakeFiles/odaslive.dir/flags.make
CMakeFiles/odaslive.dir/demo/odaslive/objects.o: ../demo/odaslive/objects.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/odas/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/odaslive.dir/demo/odaslive/objects.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/odaslive.dir/demo/odaslive/objects.o   -c /home/pi/odas/demo/odaslive/objects.c

CMakeFiles/odaslive.dir/demo/odaslive/objects.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/odaslive.dir/demo/odaslive/objects.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/odas/demo/odaslive/objects.c > CMakeFiles/odaslive.dir/demo/odaslive/objects.i

CMakeFiles/odaslive.dir/demo/odaslive/objects.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/odaslive.dir/demo/odaslive/objects.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/odas/demo/odaslive/objects.c -o CMakeFiles/odaslive.dir/demo/odaslive/objects.s

CMakeFiles/odaslive.dir/demo/odaslive/parameters.o: CMakeFiles/odaslive.dir/flags.make
CMakeFiles/odaslive.dir/demo/odaslive/parameters.o: ../demo/odaslive/parameters.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/odas/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/odaslive.dir/demo/odaslive/parameters.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/odaslive.dir/demo/odaslive/parameters.o   -c /home/pi/odas/demo/odaslive/parameters.c

CMakeFiles/odaslive.dir/demo/odaslive/parameters.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/odaslive.dir/demo/odaslive/parameters.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/odas/demo/odaslive/parameters.c > CMakeFiles/odaslive.dir/demo/odaslive/parameters.i

CMakeFiles/odaslive.dir/demo/odaslive/parameters.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/odaslive.dir/demo/odaslive/parameters.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/odas/demo/odaslive/parameters.c -o CMakeFiles/odaslive.dir/demo/odaslive/parameters.s

CMakeFiles/odaslive.dir/demo/odaslive/profiler.o: CMakeFiles/odaslive.dir/flags.make
CMakeFiles/odaslive.dir/demo/odaslive/profiler.o: ../demo/odaslive/profiler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/odas/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/odaslive.dir/demo/odaslive/profiler.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/odaslive.dir/demo/odaslive/profiler.o   -c /home/pi/odas/demo/odaslive/profiler.c

CMakeFiles/odaslive.dir/demo/odaslive/profiler.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/odaslive.dir/demo/odaslive/profiler.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/odas/demo/odaslive/profiler.c > CMakeFiles/odaslive.dir/demo/odaslive/profiler.i

CMakeFiles/odaslive.dir/demo/odaslive/profiler.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/odaslive.dir/demo/odaslive/profiler.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/odas/demo/odaslive/profiler.c -o CMakeFiles/odaslive.dir/demo/odaslive/profiler.s

CMakeFiles/odaslive.dir/demo/odaslive/threads.o: CMakeFiles/odaslive.dir/flags.make
CMakeFiles/odaslive.dir/demo/odaslive/threads.o: ../demo/odaslive/threads.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/odas/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/odaslive.dir/demo/odaslive/threads.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/odaslive.dir/demo/odaslive/threads.o   -c /home/pi/odas/demo/odaslive/threads.c

CMakeFiles/odaslive.dir/demo/odaslive/threads.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/odaslive.dir/demo/odaslive/threads.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pi/odas/demo/odaslive/threads.c > CMakeFiles/odaslive.dir/demo/odaslive/threads.i

CMakeFiles/odaslive.dir/demo/odaslive/threads.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/odaslive.dir/demo/odaslive/threads.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pi/odas/demo/odaslive/threads.c -o CMakeFiles/odaslive.dir/demo/odaslive/threads.s

# Object files for target odaslive
odaslive_OBJECTS = \
"CMakeFiles/odaslive.dir/demo/odaslive/main.o" \
"CMakeFiles/odaslive.dir/demo/odaslive/configs.o" \
"CMakeFiles/odaslive.dir/demo/odaslive/objects.o" \
"CMakeFiles/odaslive.dir/demo/odaslive/parameters.o" \
"CMakeFiles/odaslive.dir/demo/odaslive/profiler.o" \
"CMakeFiles/odaslive.dir/demo/odaslive/threads.o"

# External object files for target odaslive
odaslive_EXTERNAL_OBJECTS =

../bin/odaslive: CMakeFiles/odaslive.dir/demo/odaslive/main.o
../bin/odaslive: CMakeFiles/odaslive.dir/demo/odaslive/configs.o
../bin/odaslive: CMakeFiles/odaslive.dir/demo/odaslive/objects.o
../bin/odaslive: CMakeFiles/odaslive.dir/demo/odaslive/parameters.o
../bin/odaslive: CMakeFiles/odaslive.dir/demo/odaslive/profiler.o
../bin/odaslive: CMakeFiles/odaslive.dir/demo/odaslive/threads.o
../bin/odaslive: CMakeFiles/odaslive.dir/build.make
../bin/odaslive: ../lib/libodas.so
../bin/odaslive: CMakeFiles/odaslive.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/odas/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable ../bin/odaslive"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/odaslive.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/odaslive.dir/build: ../bin/odaslive

.PHONY : CMakeFiles/odaslive.dir/build

CMakeFiles/odaslive.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/odaslive.dir/cmake_clean.cmake
.PHONY : CMakeFiles/odaslive.dir/clean

CMakeFiles/odaslive.dir/depend:
	cd /home/pi/odas/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/odas /home/pi/odas /home/pi/odas/build /home/pi/odas/build /home/pi/odas/build/CMakeFiles/odaslive.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/odaslive.dir/depend

