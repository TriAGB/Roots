# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = W:/PortableGit/REPO1/_ADVANCED_C/test_001

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = W:/PortableGit/REPO1/_ADVANCED_C/test_001/build

# Include any dependencies generated for this target.
include CMakeFiles/HelloWorld.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HelloWorld.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HelloWorld.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HelloWorld.dir/flags.make

CMakeFiles/HelloWorld.dir/main.cpp.obj: CMakeFiles/HelloWorld.dir/flags.make
CMakeFiles/HelloWorld.dir/main.cpp.obj: W:/PortableGit/REPO1/_ADVANCED_C/test_001/main.cpp
CMakeFiles/HelloWorld.dir/main.cpp.obj: CMakeFiles/HelloWorld.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=W:/PortableGit/REPO1/_ADVANCED_C/test_001/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HelloWorld.dir/main.cpp.obj"
	C:/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HelloWorld.dir/main.cpp.obj -MF CMakeFiles/HelloWorld.dir/main.cpp.obj.d -o CMakeFiles/HelloWorld.dir/main.cpp.obj -c W:/PortableGit/REPO1/_ADVANCED_C/test_001/main.cpp

CMakeFiles/HelloWorld.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HelloWorld.dir/main.cpp.i"
	C:/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E W:/PortableGit/REPO1/_ADVANCED_C/test_001/main.cpp > CMakeFiles/HelloWorld.dir/main.cpp.i

CMakeFiles/HelloWorld.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HelloWorld.dir/main.cpp.s"
	C:/msys64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S W:/PortableGit/REPO1/_ADVANCED_C/test_001/main.cpp -o CMakeFiles/HelloWorld.dir/main.cpp.s

# Object files for target HelloWorld
HelloWorld_OBJECTS = \
"CMakeFiles/HelloWorld.dir/main.cpp.obj"

# External object files for target HelloWorld
HelloWorld_EXTERNAL_OBJECTS =

HelloWorld.exe: CMakeFiles/HelloWorld.dir/main.cpp.obj
HelloWorld.exe: CMakeFiles/HelloWorld.dir/build.make
HelloWorld.exe: CMakeFiles/HelloWorld.dir/linkLibs.rsp
HelloWorld.exe: CMakeFiles/HelloWorld.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=W:/PortableGit/REPO1/_ADVANCED_C/test_001/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HelloWorld.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/HelloWorld.dir/objects.a
	C:/msys64/mingw64/bin/ar.exe qc CMakeFiles/HelloWorld.dir/objects.a @CMakeFiles/HelloWorld.dir/objects1.rsp
	C:/msys64/mingw64/bin/g++.exe -g -Wl,--whole-archive CMakeFiles/HelloWorld.dir/objects.a -Wl,--no-whole-archive -o HelloWorld.exe -Wl,--out-implib,libHelloWorld.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/HelloWorld.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/HelloWorld.dir/build: HelloWorld.exe
.PHONY : CMakeFiles/HelloWorld.dir/build

CMakeFiles/HelloWorld.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HelloWorld.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HelloWorld.dir/clean

CMakeFiles/HelloWorld.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" W:/PortableGit/REPO1/_ADVANCED_C/test_001 W:/PortableGit/REPO1/_ADVANCED_C/test_001 W:/PortableGit/REPO1/_ADVANCED_C/test_001/build W:/PortableGit/REPO1/_ADVANCED_C/test_001/build W:/PortableGit/REPO1/_ADVANCED_C/test_001/build/CMakeFiles/HelloWorld.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HelloWorld.dir/depend
