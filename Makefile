# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/kaneko/dynamic_programming_cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kaneko/dynamic_programming_cpp

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kaneko/dynamic_programming_cpp/CMakeFiles /home/kaneko/dynamic_programming_cpp/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kaneko/dynamic_programming_cpp/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named out

# Build rule for target.
out: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 out
.PHONY : out

# fast build rule for target.
out/fast:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/build
.PHONY : out/fast

params.o: params.cpp.o

.PHONY : params.o

# target to build an object file
params.cpp.o:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/params.cpp.o
.PHONY : params.cpp.o

params.i: params.cpp.i

.PHONY : params.i

# target to preprocess a source file
params.cpp.i:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/params.cpp.i
.PHONY : params.cpp.i

params.s: params.cpp.s

.PHONY : params.s

# target to generate assembly for a file
params.cpp.s:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/params.cpp.s
.PHONY : params.cpp.s

setup.o: setup.cpp.o

.PHONY : setup.o

# target to build an object file
setup.cpp.o:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/setup.cpp.o
.PHONY : setup.cpp.o

setup.i: setup.cpp.i

.PHONY : setup.i

# target to preprocess a source file
setup.cpp.i:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/setup.cpp.i
.PHONY : setup.cpp.i

setup.s: setup.cpp.s

.PHONY : setup.s

# target to generate assembly for a file
setup.cpp.s:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/setup.cpp.s
.PHONY : setup.cpp.s

test.o: test.cpp.o

.PHONY : test.o

# target to build an object file
test.cpp.o:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/test.cpp.o
.PHONY : test.cpp.o

test.i: test.cpp.i

.PHONY : test.i

# target to preprocess a source file
test.cpp.i:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/test.cpp.i
.PHONY : test.cpp.i

test.s: test.cpp.s

.PHONY : test.s

# target to generate assembly for a file
test.cpp.s:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/test.cpp.s
.PHONY : test.cpp.s

timer.o: timer.cpp.o

.PHONY : timer.o

# target to build an object file
timer.cpp.o:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/timer.cpp.o
.PHONY : timer.cpp.o

timer.i: timer.cpp.i

.PHONY : timer.i

# target to preprocess a source file
timer.cpp.i:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/timer.cpp.i
.PHONY : timer.cpp.i

timer.s: timer.cpp.s

.PHONY : timer.s

# target to generate assembly for a file
timer.cpp.s:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/timer.cpp.s
.PHONY : timer.cpp.s

value.o: value.cpp.o

.PHONY : value.o

# target to build an object file
value.cpp.o:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/value.cpp.o
.PHONY : value.cpp.o

value.i: value.cpp.i

.PHONY : value.i

# target to preprocess a source file
value.cpp.i:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/value.cpp.i
.PHONY : value.cpp.i

value.s: value.cpp.s

.PHONY : value.s

# target to generate assembly for a file
value.cpp.s:
	$(MAKE) -f CMakeFiles/out.dir/build.make CMakeFiles/out.dir/value.cpp.s
.PHONY : value.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... out"
	@echo "... params.o"
	@echo "... params.i"
	@echo "... params.s"
	@echo "... setup.o"
	@echo "... setup.i"
	@echo "... setup.s"
	@echo "... test.o"
	@echo "... test.i"
	@echo "... test.s"
	@echo "... timer.o"
	@echo "... timer.i"
	@echo "... timer.s"
	@echo "... value.o"
	@echo "... value.i"
	@echo "... value.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

