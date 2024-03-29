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
CMAKE_SOURCE_DIR = /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published/CMakeFiles /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published/CMakeFiles 0
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
# Target rules for targets named tarzann

# Build rule for target.
tarzann: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tarzann
.PHONY : tarzann

# fast build rule for target.
tarzann/fast:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/build
.PHONY : tarzann/fast

#=============================================================================
# Target rules for targets named tarzann_automoc

# Build rule for target.
tarzann_automoc: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tarzann_automoc
.PHONY : tarzann_automoc

# fast build rule for target.
tarzann_automoc/fast:
	$(MAKE) -f CMakeFiles/tarzann_automoc.dir/build.make CMakeFiles/tarzann_automoc.dir/build
.PHONY : tarzann_automoc/fast

#=============================================================================
# Target rules for targets named color_model

# Build rule for target.
color_model: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 color_model
.PHONY : color_model

# fast build rule for target.
color_model/fast:
	$(MAKE) -f examples/color_model/CMakeFiles/color_model.dir/build.make examples/color_model/CMakeFiles/color_model.dir/build
.PHONY : color_model/fast

#=============================================================================
# Target rules for targets named color_model_automoc

# Build rule for target.
color_model_automoc: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 color_model_automoc
.PHONY : color_model_automoc

# fast build rule for target.
color_model_automoc/fast:
	$(MAKE) -f examples/color_model/CMakeFiles/color_model_automoc.dir/build.make examples/color_model/CMakeFiles/color_model_automoc.dir/build
.PHONY : color_model_automoc/fast

src/tarzann/Array2D.o: src/tarzann/Array2D.cpp.o

.PHONY : src/tarzann/Array2D.o

# target to build an object file
src/tarzann/Array2D.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Array2D.cpp.o
.PHONY : src/tarzann/Array2D.cpp.o

src/tarzann/Array2D.i: src/tarzann/Array2D.cpp.i

.PHONY : src/tarzann/Array2D.i

# target to preprocess a source file
src/tarzann/Array2D.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Array2D.cpp.i
.PHONY : src/tarzann/Array2D.cpp.i

src/tarzann/Array2D.s: src/tarzann/Array2D.cpp.s

.PHONY : src/tarzann/Array2D.s

# target to generate assembly for a file
src/tarzann/Array2D.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Array2D.cpp.s
.PHONY : src/tarzann/Array2D.cpp.s

src/tarzann/ComputeStrategy.o: src/tarzann/ComputeStrategy.cpp.o

.PHONY : src/tarzann/ComputeStrategy.o

# target to build an object file
src/tarzann/ComputeStrategy.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/ComputeStrategy.cpp.o
.PHONY : src/tarzann/ComputeStrategy.cpp.o

src/tarzann/ComputeStrategy.i: src/tarzann/ComputeStrategy.cpp.i

.PHONY : src/tarzann/ComputeStrategy.i

# target to preprocess a source file
src/tarzann/ComputeStrategy.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/ComputeStrategy.cpp.i
.PHONY : src/tarzann/ComputeStrategy.cpp.i

src/tarzann/ComputeStrategy.s: src/tarzann/ComputeStrategy.cpp.s

.PHONY : src/tarzann/ComputeStrategy.s

# target to generate assembly for a file
src/tarzann/ComputeStrategy.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/ComputeStrategy.cpp.s
.PHONY : src/tarzann/ComputeStrategy.cpp.s

src/tarzann/Connection.o: src/tarzann/Connection.cpp.o

.PHONY : src/tarzann/Connection.o

# target to build an object file
src/tarzann/Connection.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Connection.cpp.o
.PHONY : src/tarzann/Connection.cpp.o

src/tarzann/Connection.i: src/tarzann/Connection.cpp.i

.PHONY : src/tarzann/Connection.i

# target to preprocess a source file
src/tarzann/Connection.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Connection.cpp.i
.PHONY : src/tarzann/Connection.cpp.i

src/tarzann/Connection.s: src/tarzann/Connection.cpp.s

.PHONY : src/tarzann/Connection.s

# target to generate assembly for a file
src/tarzann/Connection.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Connection.cpp.s
.PHONY : src/tarzann/Connection.cpp.s

src/tarzann/ControlSignalGenerator.o: src/tarzann/ControlSignalGenerator.cpp.o

.PHONY : src/tarzann/ControlSignalGenerator.o

# target to build an object file
src/tarzann/ControlSignalGenerator.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/ControlSignalGenerator.cpp.o
.PHONY : src/tarzann/ControlSignalGenerator.cpp.o

src/tarzann/ControlSignalGenerator.i: src/tarzann/ControlSignalGenerator.cpp.i

.PHONY : src/tarzann/ControlSignalGenerator.i

# target to preprocess a source file
src/tarzann/ControlSignalGenerator.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/ControlSignalGenerator.cpp.i
.PHONY : src/tarzann/ControlSignalGenerator.cpp.i

src/tarzann/ControlSignalGenerator.s: src/tarzann/ControlSignalGenerator.cpp.s

.PHONY : src/tarzann/ControlSignalGenerator.s

# target to generate assembly for a file
src/tarzann/ControlSignalGenerator.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/ControlSignalGenerator.cpp.s
.PHONY : src/tarzann/ControlSignalGenerator.cpp.s

src/tarzann/Filter.o: src/tarzann/Filter.cpp.o

.PHONY : src/tarzann/Filter.o

# target to build an object file
src/tarzann/Filter.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Filter.cpp.o
.PHONY : src/tarzann/Filter.cpp.o

src/tarzann/Filter.i: src/tarzann/Filter.cpp.i

.PHONY : src/tarzann/Filter.i

# target to preprocess a source file
src/tarzann/Filter.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Filter.cpp.i
.PHONY : src/tarzann/Filter.cpp.i

src/tarzann/Filter.s: src/tarzann/Filter.cpp.s

.PHONY : src/tarzann/Filter.s

# target to generate assembly for a file
src/tarzann/Filter.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Filter.cpp.s
.PHONY : src/tarzann/Filter.cpp.s

src/tarzann/FilterDoG.o: src/tarzann/FilterDoG.cpp.o

.PHONY : src/tarzann/FilterDoG.o

# target to build an object file
src/tarzann/FilterDoG.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterDoG.cpp.o
.PHONY : src/tarzann/FilterDoG.cpp.o

src/tarzann/FilterDoG.i: src/tarzann/FilterDoG.cpp.i

.PHONY : src/tarzann/FilterDoG.i

# target to preprocess a source file
src/tarzann/FilterDoG.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterDoG.cpp.i
.PHONY : src/tarzann/FilterDoG.cpp.i

src/tarzann/FilterDoG.s: src/tarzann/FilterDoG.cpp.s

.PHONY : src/tarzann/FilterDoG.s

# target to generate assembly for a file
src/tarzann/FilterDoG.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterDoG.cpp.s
.PHONY : src/tarzann/FilterDoG.cpp.s

src/tarzann/FilterGabor.o: src/tarzann/FilterGabor.cpp.o

.PHONY : src/tarzann/FilterGabor.o

# target to build an object file
src/tarzann/FilterGabor.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterGabor.cpp.o
.PHONY : src/tarzann/FilterGabor.cpp.o

src/tarzann/FilterGabor.i: src/tarzann/FilterGabor.cpp.i

.PHONY : src/tarzann/FilterGabor.i

# target to preprocess a source file
src/tarzann/FilterGabor.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterGabor.cpp.i
.PHONY : src/tarzann/FilterGabor.cpp.i

src/tarzann/FilterGabor.s: src/tarzann/FilterGabor.cpp.s

.PHONY : src/tarzann/FilterGabor.s

# target to generate assembly for a file
src/tarzann/FilterGabor.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterGabor.cpp.s
.PHONY : src/tarzann/FilterGabor.cpp.s

src/tarzann/FilterGaussian.o: src/tarzann/FilterGaussian.cpp.o

.PHONY : src/tarzann/FilterGaussian.o

# target to build an object file
src/tarzann/FilterGaussian.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterGaussian.cpp.o
.PHONY : src/tarzann/FilterGaussian.cpp.o

src/tarzann/FilterGaussian.i: src/tarzann/FilterGaussian.cpp.i

.PHONY : src/tarzann/FilterGaussian.i

# target to preprocess a source file
src/tarzann/FilterGaussian.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterGaussian.cpp.i
.PHONY : src/tarzann/FilterGaussian.cpp.i

src/tarzann/FilterGaussian.s: src/tarzann/FilterGaussian.cpp.s

.PHONY : src/tarzann/FilterGaussian.s

# target to generate assembly for a file
src/tarzann/FilterGaussian.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterGaussian.cpp.s
.PHONY : src/tarzann/FilterGaussian.cpp.s

src/tarzann/FilterIdentity.o: src/tarzann/FilterIdentity.cpp.o

.PHONY : src/tarzann/FilterIdentity.o

# target to build an object file
src/tarzann/FilterIdentity.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterIdentity.cpp.o
.PHONY : src/tarzann/FilterIdentity.cpp.o

src/tarzann/FilterIdentity.i: src/tarzann/FilterIdentity.cpp.i

.PHONY : src/tarzann/FilterIdentity.i

# target to preprocess a source file
src/tarzann/FilterIdentity.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterIdentity.cpp.i
.PHONY : src/tarzann/FilterIdentity.cpp.i

src/tarzann/FilterIdentity.s: src/tarzann/FilterIdentity.cpp.s

.PHONY : src/tarzann/FilterIdentity.s

# target to generate assembly for a file
src/tarzann/FilterIdentity.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/FilterIdentity.cpp.s
.PHONY : src/tarzann/FilterIdentity.cpp.s

src/tarzann/GammaUnits.o: src/tarzann/GammaUnits.cpp.o

.PHONY : src/tarzann/GammaUnits.o

# target to build an object file
src/tarzann/GammaUnits.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/GammaUnits.cpp.o
.PHONY : src/tarzann/GammaUnits.cpp.o

src/tarzann/GammaUnits.i: src/tarzann/GammaUnits.cpp.i

.PHONY : src/tarzann/GammaUnits.i

# target to preprocess a source file
src/tarzann/GammaUnits.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/GammaUnits.cpp.i
.PHONY : src/tarzann/GammaUnits.cpp.i

src/tarzann/GammaUnits.s: src/tarzann/GammaUnits.cpp.s

.PHONY : src/tarzann/GammaUnits.s

# target to generate assembly for a file
src/tarzann/GammaUnits.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/GammaUnits.cpp.s
.PHONY : src/tarzann/GammaUnits.cpp.s

src/tarzann/GatingSignal.o: src/tarzann/GatingSignal.cpp.o

.PHONY : src/tarzann/GatingSignal.o

# target to build an object file
src/tarzann/GatingSignal.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/GatingSignal.cpp.o
.PHONY : src/tarzann/GatingSignal.cpp.o

src/tarzann/GatingSignal.i: src/tarzann/GatingSignal.cpp.i

.PHONY : src/tarzann/GatingSignal.i

# target to preprocess a source file
src/tarzann/GatingSignal.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/GatingSignal.cpp.i
.PHONY : src/tarzann/GatingSignal.cpp.i

src/tarzann/GatingSignal.s: src/tarzann/GatingSignal.cpp.s

.PHONY : src/tarzann/GatingSignal.s

# target to generate assembly for a file
src/tarzann/GatingSignal.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/GatingSignal.cpp.s
.PHONY : src/tarzann/GatingSignal.cpp.s

src/tarzann/Layer.o: src/tarzann/Layer.cpp.o

.PHONY : src/tarzann/Layer.o

# target to build an object file
src/tarzann/Layer.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Layer.cpp.o
.PHONY : src/tarzann/Layer.cpp.o

src/tarzann/Layer.i: src/tarzann/Layer.cpp.i

.PHONY : src/tarzann/Layer.i

# target to preprocess a source file
src/tarzann/Layer.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Layer.cpp.i
.PHONY : src/tarzann/Layer.cpp.i

src/tarzann/Layer.s: src/tarzann/Layer.cpp.s

.PHONY : src/tarzann/Layer.s

# target to generate assembly for a file
src/tarzann/Layer.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Layer.cpp.s
.PHONY : src/tarzann/Layer.cpp.s

src/tarzann/Matrix.o: src/tarzann/Matrix.cpp.o

.PHONY : src/tarzann/Matrix.o

# target to build an object file
src/tarzann/Matrix.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Matrix.cpp.o
.PHONY : src/tarzann/Matrix.cpp.o

src/tarzann/Matrix.i: src/tarzann/Matrix.cpp.i

.PHONY : src/tarzann/Matrix.i

# target to preprocess a source file
src/tarzann/Matrix.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Matrix.cpp.i
.PHONY : src/tarzann/Matrix.cpp.i

src/tarzann/Matrix.s: src/tarzann/Matrix.cpp.s

.PHONY : src/tarzann/Matrix.s

# target to generate assembly for a file
src/tarzann/Matrix.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Matrix.cpp.s
.PHONY : src/tarzann/Matrix.cpp.s

src/tarzann/Neuron.o: src/tarzann/Neuron.cpp.o

.PHONY : src/tarzann/Neuron.o

# target to build an object file
src/tarzann/Neuron.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Neuron.cpp.o
.PHONY : src/tarzann/Neuron.cpp.o

src/tarzann/Neuron.i: src/tarzann/Neuron.cpp.i

.PHONY : src/tarzann/Neuron.i

# target to preprocess a source file
src/tarzann/Neuron.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Neuron.cpp.i
.PHONY : src/tarzann/Neuron.cpp.i

src/tarzann/Neuron.s: src/tarzann/Neuron.cpp.s

.PHONY : src/tarzann/Neuron.s

# target to generate assembly for a file
src/tarzann/Neuron.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Neuron.cpp.s
.PHONY : src/tarzann/Neuron.cpp.s

src/tarzann/NeuronLinear.o: src/tarzann/NeuronLinear.cpp.o

.PHONY : src/tarzann/NeuronLinear.o

# target to build an object file
src/tarzann/NeuronLinear.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronLinear.cpp.o
.PHONY : src/tarzann/NeuronLinear.cpp.o

src/tarzann/NeuronLinear.i: src/tarzann/NeuronLinear.cpp.i

.PHONY : src/tarzann/NeuronLinear.i

# target to preprocess a source file
src/tarzann/NeuronLinear.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronLinear.cpp.i
.PHONY : src/tarzann/NeuronLinear.cpp.i

src/tarzann/NeuronLinear.s: src/tarzann/NeuronLinear.cpp.s

.PHONY : src/tarzann/NeuronLinear.s

# target to generate assembly for a file
src/tarzann/NeuronLinear.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronLinear.cpp.s
.PHONY : src/tarzann/NeuronLinear.cpp.s

src/tarzann/NeuronLinear2.o: src/tarzann/NeuronLinear2.cpp.o

.PHONY : src/tarzann/NeuronLinear2.o

# target to build an object file
src/tarzann/NeuronLinear2.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronLinear2.cpp.o
.PHONY : src/tarzann/NeuronLinear2.cpp.o

src/tarzann/NeuronLinear2.i: src/tarzann/NeuronLinear2.cpp.i

.PHONY : src/tarzann/NeuronLinear2.i

# target to preprocess a source file
src/tarzann/NeuronLinear2.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronLinear2.cpp.i
.PHONY : src/tarzann/NeuronLinear2.cpp.i

src/tarzann/NeuronLinear2.s: src/tarzann/NeuronLinear2.cpp.s

.PHONY : src/tarzann/NeuronLinear2.s

# target to generate assembly for a file
src/tarzann/NeuronLinear2.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronLinear2.cpp.s
.PHONY : src/tarzann/NeuronLinear2.cpp.s

src/tarzann/NeuronST.o: src/tarzann/NeuronST.cpp.o

.PHONY : src/tarzann/NeuronST.o

# target to build an object file
src/tarzann/NeuronST.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronST.cpp.o
.PHONY : src/tarzann/NeuronST.cpp.o

src/tarzann/NeuronST.i: src/tarzann/NeuronST.cpp.i

.PHONY : src/tarzann/NeuronST.i

# target to preprocess a source file
src/tarzann/NeuronST.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronST.cpp.i
.PHONY : src/tarzann/NeuronST.cpp.i

src/tarzann/NeuronST.s: src/tarzann/NeuronST.cpp.s

.PHONY : src/tarzann/NeuronST.s

# target to generate assembly for a file
src/tarzann/NeuronST.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronST.cpp.s
.PHONY : src/tarzann/NeuronST.cpp.s

src/tarzann/NeuronST1.o: src/tarzann/NeuronST1.cpp.o

.PHONY : src/tarzann/NeuronST1.o

# target to build an object file
src/tarzann/NeuronST1.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronST1.cpp.o
.PHONY : src/tarzann/NeuronST1.cpp.o

src/tarzann/NeuronST1.i: src/tarzann/NeuronST1.cpp.i

.PHONY : src/tarzann/NeuronST1.i

# target to preprocess a source file
src/tarzann/NeuronST1.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronST1.cpp.i
.PHONY : src/tarzann/NeuronST1.cpp.i

src/tarzann/NeuronST1.s: src/tarzann/NeuronST1.cpp.s

.PHONY : src/tarzann/NeuronST1.s

# target to generate assembly for a file
src/tarzann/NeuronST1.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronST1.cpp.s
.PHONY : src/tarzann/NeuronST1.cpp.s

src/tarzann/NeuronSigmoid.o: src/tarzann/NeuronSigmoid.cpp.o

.PHONY : src/tarzann/NeuronSigmoid.o

# target to build an object file
src/tarzann/NeuronSigmoid.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronSigmoid.cpp.o
.PHONY : src/tarzann/NeuronSigmoid.cpp.o

src/tarzann/NeuronSigmoid.i: src/tarzann/NeuronSigmoid.cpp.i

.PHONY : src/tarzann/NeuronSigmoid.i

# target to preprocess a source file
src/tarzann/NeuronSigmoid.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronSigmoid.cpp.i
.PHONY : src/tarzann/NeuronSigmoid.cpp.i

src/tarzann/NeuronSigmoid.s: src/tarzann/NeuronSigmoid.cpp.s

.PHONY : src/tarzann/NeuronSigmoid.s

# target to generate assembly for a file
src/tarzann/NeuronSigmoid.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/NeuronSigmoid.cpp.s
.PHONY : src/tarzann/NeuronSigmoid.cpp.s

src/tarzann/PLattice.o: src/tarzann/PLattice.cpp.o

.PHONY : src/tarzann/PLattice.o

# target to build an object file
src/tarzann/PLattice.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/PLattice.cpp.o
.PHONY : src/tarzann/PLattice.cpp.o

src/tarzann/PLattice.i: src/tarzann/PLattice.cpp.i

.PHONY : src/tarzann/PLattice.i

# target to preprocess a source file
src/tarzann/PLattice.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/PLattice.cpp.i
.PHONY : src/tarzann/PLattice.cpp.i

src/tarzann/PLattice.s: src/tarzann/PLattice.cpp.s

.PHONY : src/tarzann/PLattice.s

# target to generate assembly for a file
src/tarzann/PLattice.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/PLattice.cpp.s
.PHONY : src/tarzann/PLattice.cpp.s

src/tarzann/Probe.o: src/tarzann/Probe.cpp.o

.PHONY : src/tarzann/Probe.o

# target to build an object file
src/tarzann/Probe.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Probe.cpp.o
.PHONY : src/tarzann/Probe.cpp.o

src/tarzann/Probe.i: src/tarzann/Probe.cpp.i

.PHONY : src/tarzann/Probe.i

# target to preprocess a source file
src/tarzann/Probe.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Probe.cpp.i
.PHONY : src/tarzann/Probe.cpp.i

src/tarzann/Probe.s: src/tarzann/Probe.cpp.s

.PHONY : src/tarzann/Probe.s

# target to generate assembly for a file
src/tarzann/Probe.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Probe.cpp.s
.PHONY : src/tarzann/Probe.cpp.s

src/tarzann/ReceptiveField.o: src/tarzann/ReceptiveField.cpp.o

.PHONY : src/tarzann/ReceptiveField.o

# target to build an object file
src/tarzann/ReceptiveField.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/ReceptiveField.cpp.o
.PHONY : src/tarzann/ReceptiveField.cpp.o

src/tarzann/ReceptiveField.i: src/tarzann/ReceptiveField.cpp.i

.PHONY : src/tarzann/ReceptiveField.i

# target to preprocess a source file
src/tarzann/ReceptiveField.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/ReceptiveField.cpp.i
.PHONY : src/tarzann/ReceptiveField.cpp.i

src/tarzann/ReceptiveField.s: src/tarzann/ReceptiveField.cpp.s

.PHONY : src/tarzann/ReceptiveField.s

# target to generate assembly for a file
src/tarzann/ReceptiveField.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/ReceptiveField.cpp.s
.PHONY : src/tarzann/ReceptiveField.cpp.s

src/tarzann/RetinalLayer.o: src/tarzann/RetinalLayer.cpp.o

.PHONY : src/tarzann/RetinalLayer.o

# target to build an object file
src/tarzann/RetinalLayer.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/RetinalLayer.cpp.o
.PHONY : src/tarzann/RetinalLayer.cpp.o

src/tarzann/RetinalLayer.i: src/tarzann/RetinalLayer.cpp.i

.PHONY : src/tarzann/RetinalLayer.i

# target to preprocess a source file
src/tarzann/RetinalLayer.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/RetinalLayer.cpp.i
.PHONY : src/tarzann/RetinalLayer.cpp.i

src/tarzann/RetinalLayer.s: src/tarzann/RetinalLayer.cpp.s

.PHONY : src/tarzann/RetinalLayer.s

# target to generate assembly for a file
src/tarzann/RetinalLayer.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/RetinalLayer.cpp.s
.PHONY : src/tarzann/RetinalLayer.cpp.s

src/tarzann/Sheet.o: src/tarzann/Sheet.cpp.o

.PHONY : src/tarzann/Sheet.o

# target to build an object file
src/tarzann/Sheet.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Sheet.cpp.o
.PHONY : src/tarzann/Sheet.cpp.o

src/tarzann/Sheet.i: src/tarzann/Sheet.cpp.i

.PHONY : src/tarzann/Sheet.i

# target to preprocess a source file
src/tarzann/Sheet.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Sheet.cpp.i
.PHONY : src/tarzann/Sheet.cpp.i

src/tarzann/Sheet.s: src/tarzann/Sheet.cpp.s

.PHONY : src/tarzann/Sheet.s

# target to generate assembly for a file
src/tarzann/Sheet.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Sheet.cpp.s
.PHONY : src/tarzann/Sheet.cpp.s

src/tarzann/Stimulus.o: src/tarzann/Stimulus.cpp.o

.PHONY : src/tarzann/Stimulus.o

# target to build an object file
src/tarzann/Stimulus.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Stimulus.cpp.o
.PHONY : src/tarzann/Stimulus.cpp.o

src/tarzann/Stimulus.i: src/tarzann/Stimulus.cpp.i

.PHONY : src/tarzann/Stimulus.i

# target to preprocess a source file
src/tarzann/Stimulus.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Stimulus.cpp.i
.PHONY : src/tarzann/Stimulus.cpp.i

src/tarzann/Stimulus.s: src/tarzann/Stimulus.cpp.s

.PHONY : src/tarzann/Stimulus.s

# target to generate assembly for a file
src/tarzann/Stimulus.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/Stimulus.cpp.s
.PHONY : src/tarzann/Stimulus.cpp.s

src/tarzann/XMLConfig.o: src/tarzann/XMLConfig.cpp.o

.PHONY : src/tarzann/XMLConfig.o

# target to build an object file
src/tarzann/XMLConfig.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/XMLConfig.cpp.o
.PHONY : src/tarzann/XMLConfig.cpp.o

src/tarzann/XMLConfig.i: src/tarzann/XMLConfig.cpp.i

.PHONY : src/tarzann/XMLConfig.i

# target to preprocess a source file
src/tarzann/XMLConfig.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/XMLConfig.cpp.i
.PHONY : src/tarzann/XMLConfig.cpp.i

src/tarzann/XMLConfig.s: src/tarzann/XMLConfig.cpp.s

.PHONY : src/tarzann/XMLConfig.s

# target to generate assembly for a file
src/tarzann/XMLConfig.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann/XMLConfig.cpp.s
.PHONY : src/tarzann/XMLConfig.cpp.s

src/tarzann_gui/ConnectionGUI.o: src/tarzann_gui/ConnectionGUI.cpp.o

.PHONY : src/tarzann_gui/ConnectionGUI.o

# target to build an object file
src/tarzann_gui/ConnectionGUI.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/ConnectionGUI.cpp.o
.PHONY : src/tarzann_gui/ConnectionGUI.cpp.o

src/tarzann_gui/ConnectionGUI.i: src/tarzann_gui/ConnectionGUI.cpp.i

.PHONY : src/tarzann_gui/ConnectionGUI.i

# target to preprocess a source file
src/tarzann_gui/ConnectionGUI.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/ConnectionGUI.cpp.i
.PHONY : src/tarzann_gui/ConnectionGUI.cpp.i

src/tarzann_gui/ConnectionGUI.s: src/tarzann_gui/ConnectionGUI.cpp.s

.PHONY : src/tarzann_gui/ConnectionGUI.s

# target to generate assembly for a file
src/tarzann_gui/ConnectionGUI.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/ConnectionGUI.cpp.s
.PHONY : src/tarzann_gui/ConnectionGUI.cpp.s

src/tarzann_gui/NetworkWindow.o: src/tarzann_gui/NetworkWindow.cpp.o

.PHONY : src/tarzann_gui/NetworkWindow.o

# target to build an object file
src/tarzann_gui/NetworkWindow.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/NetworkWindow.cpp.o
.PHONY : src/tarzann_gui/NetworkWindow.cpp.o

src/tarzann_gui/NetworkWindow.i: src/tarzann_gui/NetworkWindow.cpp.i

.PHONY : src/tarzann_gui/NetworkWindow.i

# target to preprocess a source file
src/tarzann_gui/NetworkWindow.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/NetworkWindow.cpp.i
.PHONY : src/tarzann_gui/NetworkWindow.cpp.i

src/tarzann_gui/NetworkWindow.s: src/tarzann_gui/NetworkWindow.cpp.s

.PHONY : src/tarzann_gui/NetworkWindow.s

# target to generate assembly for a file
src/tarzann_gui/NetworkWindow.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/NetworkWindow.cpp.s
.PHONY : src/tarzann_gui/NetworkWindow.cpp.s

src/tarzann_gui/PLatticeGUI.o: src/tarzann_gui/PLatticeGUI.cpp.o

.PHONY : src/tarzann_gui/PLatticeGUI.o

# target to build an object file
src/tarzann_gui/PLatticeGUI.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/PLatticeGUI.cpp.o
.PHONY : src/tarzann_gui/PLatticeGUI.cpp.o

src/tarzann_gui/PLatticeGUI.i: src/tarzann_gui/PLatticeGUI.cpp.i

.PHONY : src/tarzann_gui/PLatticeGUI.i

# target to preprocess a source file
src/tarzann_gui/PLatticeGUI.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/PLatticeGUI.cpp.i
.PHONY : src/tarzann_gui/PLatticeGUI.cpp.i

src/tarzann_gui/PLatticeGUI.s: src/tarzann_gui/PLatticeGUI.cpp.s

.PHONY : src/tarzann_gui/PLatticeGUI.s

# target to generate assembly for a file
src/tarzann_gui/PLatticeGUI.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/PLatticeGUI.cpp.s
.PHONY : src/tarzann_gui/PLatticeGUI.cpp.s

src/tarzann_gui/SheetImage.o: src/tarzann_gui/SheetImage.cpp.o

.PHONY : src/tarzann_gui/SheetImage.o

# target to build an object file
src/tarzann_gui/SheetImage.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/SheetImage.cpp.o
.PHONY : src/tarzann_gui/SheetImage.cpp.o

src/tarzann_gui/SheetImage.i: src/tarzann_gui/SheetImage.cpp.i

.PHONY : src/tarzann_gui/SheetImage.i

# target to preprocess a source file
src/tarzann_gui/SheetImage.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/SheetImage.cpp.i
.PHONY : src/tarzann_gui/SheetImage.cpp.i

src/tarzann_gui/SheetImage.s: src/tarzann_gui/SheetImage.cpp.s

.PHONY : src/tarzann_gui/SheetImage.s

# target to generate assembly for a file
src/tarzann_gui/SheetImage.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/src/tarzann_gui/SheetImage.cpp.s
.PHONY : src/tarzann_gui/SheetImage.cpp.s

tarzann_automoc.o: tarzann_automoc.cpp.o

.PHONY : tarzann_automoc.o

# target to build an object file
tarzann_automoc.cpp.o:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/tarzann_automoc.cpp.o
.PHONY : tarzann_automoc.cpp.o

tarzann_automoc.i: tarzann_automoc.cpp.i

.PHONY : tarzann_automoc.i

# target to preprocess a source file
tarzann_automoc.cpp.i:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/tarzann_automoc.cpp.i
.PHONY : tarzann_automoc.cpp.i

tarzann_automoc.s: tarzann_automoc.cpp.s

.PHONY : tarzann_automoc.s

# target to generate assembly for a file
tarzann_automoc.cpp.s:
	$(MAKE) -f CMakeFiles/tarzann.dir/build.make CMakeFiles/tarzann.dir/tarzann_automoc.cpp.s
.PHONY : tarzann_automoc.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... tarzann"
	@echo "... tarzann_automoc"
	@echo "... color_model"
	@echo "... color_model_automoc"
	@echo "... src/tarzann/Array2D.o"
	@echo "... src/tarzann/Array2D.i"
	@echo "... src/tarzann/Array2D.s"
	@echo "... src/tarzann/ComputeStrategy.o"
	@echo "... src/tarzann/ComputeStrategy.i"
	@echo "... src/tarzann/ComputeStrategy.s"
	@echo "... src/tarzann/Connection.o"
	@echo "... src/tarzann/Connection.i"
	@echo "... src/tarzann/Connection.s"
	@echo "... src/tarzann/ControlSignalGenerator.o"
	@echo "... src/tarzann/ControlSignalGenerator.i"
	@echo "... src/tarzann/ControlSignalGenerator.s"
	@echo "... src/tarzann/Filter.o"
	@echo "... src/tarzann/Filter.i"
	@echo "... src/tarzann/Filter.s"
	@echo "... src/tarzann/FilterDoG.o"
	@echo "... src/tarzann/FilterDoG.i"
	@echo "... src/tarzann/FilterDoG.s"
	@echo "... src/tarzann/FilterGabor.o"
	@echo "... src/tarzann/FilterGabor.i"
	@echo "... src/tarzann/FilterGabor.s"
	@echo "... src/tarzann/FilterGaussian.o"
	@echo "... src/tarzann/FilterGaussian.i"
	@echo "... src/tarzann/FilterGaussian.s"
	@echo "... src/tarzann/FilterIdentity.o"
	@echo "... src/tarzann/FilterIdentity.i"
	@echo "... src/tarzann/FilterIdentity.s"
	@echo "... src/tarzann/GammaUnits.o"
	@echo "... src/tarzann/GammaUnits.i"
	@echo "... src/tarzann/GammaUnits.s"
	@echo "... src/tarzann/GatingSignal.o"
	@echo "... src/tarzann/GatingSignal.i"
	@echo "... src/tarzann/GatingSignal.s"
	@echo "... src/tarzann/Layer.o"
	@echo "... src/tarzann/Layer.i"
	@echo "... src/tarzann/Layer.s"
	@echo "... src/tarzann/Matrix.o"
	@echo "... src/tarzann/Matrix.i"
	@echo "... src/tarzann/Matrix.s"
	@echo "... src/tarzann/Neuron.o"
	@echo "... src/tarzann/Neuron.i"
	@echo "... src/tarzann/Neuron.s"
	@echo "... src/tarzann/NeuronLinear.o"
	@echo "... src/tarzann/NeuronLinear.i"
	@echo "... src/tarzann/NeuronLinear.s"
	@echo "... src/tarzann/NeuronLinear2.o"
	@echo "... src/tarzann/NeuronLinear2.i"
	@echo "... src/tarzann/NeuronLinear2.s"
	@echo "... src/tarzann/NeuronST.o"
	@echo "... src/tarzann/NeuronST.i"
	@echo "... src/tarzann/NeuronST.s"
	@echo "... src/tarzann/NeuronST1.o"
	@echo "... src/tarzann/NeuronST1.i"
	@echo "... src/tarzann/NeuronST1.s"
	@echo "... src/tarzann/NeuronSigmoid.o"
	@echo "... src/tarzann/NeuronSigmoid.i"
	@echo "... src/tarzann/NeuronSigmoid.s"
	@echo "... src/tarzann/PLattice.o"
	@echo "... src/tarzann/PLattice.i"
	@echo "... src/tarzann/PLattice.s"
	@echo "... src/tarzann/Probe.o"
	@echo "... src/tarzann/Probe.i"
	@echo "... src/tarzann/Probe.s"
	@echo "... src/tarzann/ReceptiveField.o"
	@echo "... src/tarzann/ReceptiveField.i"
	@echo "... src/tarzann/ReceptiveField.s"
	@echo "... src/tarzann/RetinalLayer.o"
	@echo "... src/tarzann/RetinalLayer.i"
	@echo "... src/tarzann/RetinalLayer.s"
	@echo "... src/tarzann/Sheet.o"
	@echo "... src/tarzann/Sheet.i"
	@echo "... src/tarzann/Sheet.s"
	@echo "... src/tarzann/Stimulus.o"
	@echo "... src/tarzann/Stimulus.i"
	@echo "... src/tarzann/Stimulus.s"
	@echo "... src/tarzann/XMLConfig.o"
	@echo "... src/tarzann/XMLConfig.i"
	@echo "... src/tarzann/XMLConfig.s"
	@echo "... src/tarzann_gui/ConnectionGUI.o"
	@echo "... src/tarzann_gui/ConnectionGUI.i"
	@echo "... src/tarzann_gui/ConnectionGUI.s"
	@echo "... src/tarzann_gui/NetworkWindow.o"
	@echo "... src/tarzann_gui/NetworkWindow.i"
	@echo "... src/tarzann_gui/NetworkWindow.s"
	@echo "... src/tarzann_gui/PLatticeGUI.o"
	@echo "... src/tarzann_gui/PLatticeGUI.i"
	@echo "... src/tarzann_gui/PLatticeGUI.s"
	@echo "... src/tarzann_gui/SheetImage.o"
	@echo "... src/tarzann_gui/SheetImage.i"
	@echo "... src/tarzann_gui/SheetImage.s"
	@echo "... tarzann_automoc.o"
	@echo "... tarzann_automoc.i"
	@echo "... tarzann_automoc.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

