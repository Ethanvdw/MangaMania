# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/ethan/Documents/GitHub/MangaMania

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/ethan/Documents/GitHub/MangaMania/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MangaMania.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MangaMania.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MangaMania.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MangaMania.dir/flags.make

CMakeFiles/MangaMania.dir/main.cpp.o: CMakeFiles/MangaMania.dir/flags.make
CMakeFiles/MangaMania.dir/main.cpp.o: ../main.cpp
CMakeFiles/MangaMania.dir/main.cpp.o: CMakeFiles/MangaMania.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/ethan/Documents/GitHub/MangaMania/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MangaMania.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MangaMania.dir/main.cpp.o -MF CMakeFiles/MangaMania.dir/main.cpp.o.d -o CMakeFiles/MangaMania.dir/main.cpp.o -c /mnt/c/Users/ethan/Documents/GitHub/MangaMania/main.cpp

CMakeFiles/MangaMania.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MangaMania.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/ethan/Documents/GitHub/MangaMania/main.cpp > CMakeFiles/MangaMania.dir/main.cpp.i

CMakeFiles/MangaMania.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MangaMania.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/ethan/Documents/GitHub/MangaMania/main.cpp -o CMakeFiles/MangaMania.dir/main.cpp.s

CMakeFiles/MangaMania.dir/Downloader.cpp.o: CMakeFiles/MangaMania.dir/flags.make
CMakeFiles/MangaMania.dir/Downloader.cpp.o: ../Downloader.cpp
CMakeFiles/MangaMania.dir/Downloader.cpp.o: CMakeFiles/MangaMania.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/ethan/Documents/GitHub/MangaMania/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MangaMania.dir/Downloader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MangaMania.dir/Downloader.cpp.o -MF CMakeFiles/MangaMania.dir/Downloader.cpp.o.d -o CMakeFiles/MangaMania.dir/Downloader.cpp.o -c /mnt/c/Users/ethan/Documents/GitHub/MangaMania/Downloader.cpp

CMakeFiles/MangaMania.dir/Downloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MangaMania.dir/Downloader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/ethan/Documents/GitHub/MangaMania/Downloader.cpp > CMakeFiles/MangaMania.dir/Downloader.cpp.i

CMakeFiles/MangaMania.dir/Downloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MangaMania.dir/Downloader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/ethan/Documents/GitHub/MangaMania/Downloader.cpp -o CMakeFiles/MangaMania.dir/Downloader.cpp.s

CMakeFiles/MangaMania.dir/Manga.cpp.o: CMakeFiles/MangaMania.dir/flags.make
CMakeFiles/MangaMania.dir/Manga.cpp.o: ../Manga.cpp
CMakeFiles/MangaMania.dir/Manga.cpp.o: CMakeFiles/MangaMania.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/ethan/Documents/GitHub/MangaMania/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MangaMania.dir/Manga.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MangaMania.dir/Manga.cpp.o -MF CMakeFiles/MangaMania.dir/Manga.cpp.o.d -o CMakeFiles/MangaMania.dir/Manga.cpp.o -c /mnt/c/Users/ethan/Documents/GitHub/MangaMania/Manga.cpp

CMakeFiles/MangaMania.dir/Manga.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MangaMania.dir/Manga.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/ethan/Documents/GitHub/MangaMania/Manga.cpp > CMakeFiles/MangaMania.dir/Manga.cpp.i

CMakeFiles/MangaMania.dir/Manga.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MangaMania.dir/Manga.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/ethan/Documents/GitHub/MangaMania/Manga.cpp -o CMakeFiles/MangaMania.dir/Manga.cpp.s

CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.o: CMakeFiles/MangaMania.dir/flags.make
CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.o: ../UserProgressRecorder.cpp
CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.o: CMakeFiles/MangaMania.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/ethan/Documents/GitHub/MangaMania/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.o -MF CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.o.d -o CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.o -c /mnt/c/Users/ethan/Documents/GitHub/MangaMania/UserProgressRecorder.cpp

CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/ethan/Documents/GitHub/MangaMania/UserProgressRecorder.cpp > CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.i

CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/ethan/Documents/GitHub/MangaMania/UserProgressRecorder.cpp -o CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.s

# Object files for target MangaMania
MangaMania_OBJECTS = \
"CMakeFiles/MangaMania.dir/main.cpp.o" \
"CMakeFiles/MangaMania.dir/Downloader.cpp.o" \
"CMakeFiles/MangaMania.dir/Manga.cpp.o" \
"CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.o"

# External object files for target MangaMania
MangaMania_EXTERNAL_OBJECTS =

MangaMania: CMakeFiles/MangaMania.dir/main.cpp.o
MangaMania: CMakeFiles/MangaMania.dir/Downloader.cpp.o
MangaMania: CMakeFiles/MangaMania.dir/Manga.cpp.o
MangaMania: CMakeFiles/MangaMania.dir/UserProgressRecorder.cpp.o
MangaMania: CMakeFiles/MangaMania.dir/build.make
MangaMania: /usr/lib/x86_64-linux-gnu/libcurl.so
MangaMania: CMakeFiles/MangaMania.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/ethan/Documents/GitHub/MangaMania/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable MangaMania"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MangaMania.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MangaMania.dir/build: MangaMania
.PHONY : CMakeFiles/MangaMania.dir/build

CMakeFiles/MangaMania.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MangaMania.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MangaMania.dir/clean

CMakeFiles/MangaMania.dir/depend:
	cd /mnt/c/Users/ethan/Documents/GitHub/MangaMania/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/ethan/Documents/GitHub/MangaMania /mnt/c/Users/ethan/Documents/GitHub/MangaMania /mnt/c/Users/ethan/Documents/GitHub/MangaMania/cmake-build-debug /mnt/c/Users/ethan/Documents/GitHub/MangaMania/cmake-build-debug /mnt/c/Users/ethan/Documents/GitHub/MangaMania/cmake-build-debug/CMakeFiles/MangaMania.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MangaMania.dir/depend

