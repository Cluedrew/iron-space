# Test Handler MakeFile

# OK it divolved into scratchpad. Writing things down helps me think
# them through.

# This may/probably will be folded into the project Make, but while I'm
# scratching out my thoughts, here it goes.
# Currently running 'g++ test.cpp math.tst.cpp -o test' is enough but I need
# something a little more repeatable, especially as the project (and the
# tests) grow.

# Makefile for InkV8: compiles iron-space executable and dependances.

# Call without target to make the executable.
#      with clean to remove intermediate files.
#      with deepclean to remove all generated files.
#      with step-test to run the program with gdb as a test wrapper.
#      with mem-test to run the program with valgrind as a test wrapper.
# And you of course may call with any generated file to create that file.

# Allows for one level of subdirectories within the code directory.
# Some of the internal variables do have to be updated as you go.

### Variables & Setup

# 'yes' to turn on debugging options, otherwise leaves them off.
USE_DEBUG=no

# Name of binary executable.
EXE=iron-space

# Name of the test executable.
TST_EXE=run-tests

# The name of the directory that holds code.
CODEDIR=src
# The name of the temperary directory for object and dependancy files.
TMPDIR=.tmp
# The name of every sub directory of CODEDIR.
DIRNAMES=physics graphics audio ai util

# Name of the executable source (main file for release)
MAIN=main
# Name of the test source (the main file for testing)
TEST=test

# Get a list off all cpp files in the src directory.
CPPFILES=$(wildcard $(CODEDIR)/*.cpp) $(wildcard $(CODEDIR)/*/*.cpp)

# C++ Compiler
CXX=g++
# Flags for compilation
CXXFLAGS=-Wall --std=c++11
# Additional libraries for the linking step.
CXXLIBS=-lsfml-graphics -lsfml-window -lsfml-system
# Additional flags for debug builds.
DEBUG=-ggdb -DDEBUG=true

# Functions:

# Function that returns a word of 1 if all words in 1 are unique, otherwise
#   returns the empty string. Should be used as a predicate.
isunique=$(word $(words $(1)), $(sort $(1))

# Patterns by which group file types.
CPP_PAT=$(CODEDIR)/%.cpp
# SRC_PAT, does not exist, it is CPP_PAT excluding TST_PAT and the origins.
TST_PAT=$(CODEDIR)/%.tst.cpp
OBJ_PAT=$(TMPDIR)/%.o
DEP_PAT=$(TMPDIR)/%.d

# Return a list of all the object files generated from the given cpp files.
objectsfor=$(1:$(CPP_PAT)=$(OBJ_PAT))

# Return a list of all the dependancy files generated for the give cpp files.
dependsfor=$(1:$(CPP_PAT)=$(DEP_PAT))

OBJFILES=$(call objectsfor,$(CPPFILES))
DEPFILES=$(call dependsfor,$(CPPFILES))
SUBDIRS=$(DIRNAMES:%=$(TMPDIR)/%)

# Compute the list of all normal files (those that do not contain a main).
MAIN_AND_TEST=$(MAIN) $(TEST)
NRMFILES=$(filter-out $(MAIN_AND_TEST:%=$(CODEDIR)/%.cpp),$(CPPFILES))
MAINFILE=$(MAIN:%=$(CPP_PAT))
TESTFILE=$(TEST:%=$(CPP_PAT))

# Source files, cpp files used in the final program.
SRCFILES=$(filter-out %.tst.cpp,$(NRMFILES))

# Test files, .tst.cpp files that contain catch tests.
TSTFILES=$(filer %.tst.cpp,$(NRMFILES))

# Include the catch header.
TESTFLAGS=-I$(ROOT)

# If USE_DEBUG add the DUBUG flags.
ifeq ($(USE_DEBUG),yes)
  CXXFLAGS+=$(DEBUG)
endif

.PHONY : all clean deepclean step-test mem-test

# Recipies

### Recipes and Rules

all : $(EXE)

# Rule for the binary
$(EXE) : $(call objectsfor,$(SRCFILES) $(MAINFILE))
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $^ -o $@

# The test executable depends on all test-code-object files
$(TST_EXE) : $(call objectsfor,$(NRMFILES) $(TESTFILE))
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $^ -o $@

# Rule for object files (dependency)
$(OBJFILES) : $(OBJ_PAT) : $(CPP_PAT) | $(TMPDIR)/$(dir %)

# Rule for source object files (build)
$(call objectsfor,$(SRCFILES) $(MAINFILE)) :
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Rule for test object files (build)
$(call objectsfor,$(TSTFILES) $(TESTFILE)) :
	$(CXX) $(CXXFLAGS) $(TESTFLAGS) -MMD -c $< -o $@

# Rule for the temperary directory
$(TMPDIR) :
	mkdir $@

# Rule for sub temperary directories
$(SUBDIRS) : | $(TMPDIR)
	mkdir $@

# Phony rule for cleaning intermediate files
clean :
	-rm $(subst %,*,$(OBJ_PAT))
	-rm $(subst %,*,$(DEP_PAT))
	-rmdir $(TMPDIR)

# Phony rule for cleaning generated files
deepclean : clean
	-rm $(EXE)

# Phony rules for running the test wrappers
step-test : $(EXE)
	gdb ./$(EXE)

mem-test : $(EXE)
	valgrind ./$(EXE)


### Include Depends Files

-include $(DEPFILES)
