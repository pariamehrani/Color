# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published

# Utility rule file for tarzann_automoc.

# Include the progress variables for this target.
include CMakeFiles/tarzann_automoc.dir/progress.make

CMakeFiles/tarzann_automoc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic moc for target tarzann"
	/usr/bin/cmake -E cmake_autogen /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published/CMakeFiles/tarzann_automoc.dir/ Release

tarzann_automoc: CMakeFiles/tarzann_automoc
tarzann_automoc: CMakeFiles/tarzann_automoc.dir/build.make

.PHONY : tarzann_automoc

# Rule to build all files generated by this target.
CMakeFiles/tarzann_automoc.dir/build: tarzann_automoc

.PHONY : CMakeFiles/tarzann_automoc.dir/build

CMakeFiles/tarzann_automoc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tarzann_automoc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tarzann_automoc.dir/clean

CMakeFiles/tarzann_automoc.dir/depend:
	cd /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published /home/paria/shared_folder/TarzaNN_Andrei/Color_model_code/TarzaNN.3.0_journal_code_published/CMakeFiles/tarzann_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tarzann_automoc.dir/depend

