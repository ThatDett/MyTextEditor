# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\akade\Programming\MyTextEditor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\akade\Programming\MyTextEditor\build

# Include any dependencies generated for this target.
include CMakeFiles/MyTextEditor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyTextEditor.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyTextEditor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyTextEditor.dir/flags.make

CMakeFiles/MyTextEditor.dir/main.cpp.obj: CMakeFiles/MyTextEditor.dir/flags.make
CMakeFiles/MyTextEditor.dir/main.cpp.obj: CMakeFiles/MyTextEditor.dir/includes_CXX.rsp
CMakeFiles/MyTextEditor.dir/main.cpp.obj: C:/Users/akade/Programming/MyTextEditor/main.cpp
CMakeFiles/MyTextEditor.dir/main.cpp.obj: CMakeFiles/MyTextEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\akade\Programming\MyTextEditor\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyTextEditor.dir/main.cpp.obj"
	C:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyTextEditor.dir/main.cpp.obj -MF CMakeFiles\MyTextEditor.dir\main.cpp.obj.d -o CMakeFiles\MyTextEditor.dir\main.cpp.obj -c C:\Users\akade\Programming\MyTextEditor\main.cpp

CMakeFiles/MyTextEditor.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/MyTextEditor.dir/main.cpp.i"
	C:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\akade\Programming\MyTextEditor\main.cpp > CMakeFiles\MyTextEditor.dir\main.cpp.i

CMakeFiles/MyTextEditor.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/MyTextEditor.dir/main.cpp.s"
	C:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\akade\Programming\MyTextEditor\main.cpp -o CMakeFiles\MyTextEditor.dir\main.cpp.s

# Object files for target MyTextEditor
MyTextEditor_OBJECTS = \
"CMakeFiles/MyTextEditor.dir/main.cpp.obj"

# External object files for target MyTextEditor
MyTextEditor_EXTERNAL_OBJECTS =

MyTextEditor.exe: CMakeFiles/MyTextEditor.dir/main.cpp.obj
MyTextEditor.exe: CMakeFiles/MyTextEditor.dir/build.make
MyTextEditor.exe: external/glfw/src/libglfw3.a
MyTextEditor.exe: CMakeFiles/MyTextEditor.dir/linkLibs.rsp
MyTextEditor.exe: CMakeFiles/MyTextEditor.dir/objects1.rsp
MyTextEditor.exe: CMakeFiles/MyTextEditor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\akade\Programming\MyTextEditor\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MyTextEditor.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MyTextEditor.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyTextEditor.dir/build: MyTextEditor.exe
.PHONY : CMakeFiles/MyTextEditor.dir/build

CMakeFiles/MyTextEditor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MyTextEditor.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MyTextEditor.dir/clean

CMakeFiles/MyTextEditor.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\akade\Programming\MyTextEditor C:\Users\akade\Programming\MyTextEditor C:\Users\akade\Programming\MyTextEditor\build C:\Users\akade\Programming\MyTextEditor\build C:\Users\akade\Programming\MyTextEditor\build\CMakeFiles\MyTextEditor.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MyTextEditor.dir/depend
