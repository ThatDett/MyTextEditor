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

# Utility rule file for docs.

# Include any custom commands dependencies for this target.
include external/glfw/docs/CMakeFiles/docs.dir/compiler_depend.make

# Include the progress variables for this target.
include external/glfw/docs/CMakeFiles/docs.dir/progress.make

external/glfw/docs/html/index.html: external/glfw/docs/Doxyfile
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/include/GLFW/glfw3.h
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/include/GLFW/glfw3native.h
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/main.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/news.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/quick.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/moving.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/compile.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/build.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/intro.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/context.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/monitor.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/window.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/input.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/vulkan.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/compat.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/internal.md
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/DoxygenLayout.xml
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/header.html
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/footer.html
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/extra.css
external/glfw/docs/html/index.html: C:/Users/akade/Programming/MyTextEditor/external/glfw/docs/spaces.svg
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:\Users\akade\Programming\MyTextEditor\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating HTML documentation"
	cd /d C:\Users\akade\Programming\MyTextEditor\build\external\glfw\docs && C:\mingw64\bin\doxygen.exe

docs: external/glfw/docs/html/index.html
docs: external/glfw/docs/CMakeFiles/docs.dir/build.make
.PHONY : docs

# Rule to build all files generated by this target.
external/glfw/docs/CMakeFiles/docs.dir/build: docs
.PHONY : external/glfw/docs/CMakeFiles/docs.dir/build

external/glfw/docs/CMakeFiles/docs.dir/clean:
	cd /d C:\Users\akade\Programming\MyTextEditor\build\external\glfw\docs && $(CMAKE_COMMAND) -P CMakeFiles\docs.dir\cmake_clean.cmake
.PHONY : external/glfw/docs/CMakeFiles/docs.dir/clean

external/glfw/docs/CMakeFiles/docs.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\akade\Programming\MyTextEditor C:\Users\akade\Programming\MyTextEditor\external\glfw\docs C:\Users\akade\Programming\MyTextEditor\build C:\Users\akade\Programming\MyTextEditor\build\external\glfw\docs C:\Users\akade\Programming\MyTextEditor\build\external\glfw\docs\CMakeFiles\docs.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/glfw/docs/CMakeFiles/docs.dir/depend
