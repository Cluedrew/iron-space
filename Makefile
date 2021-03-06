# Makefile for InkV8.0: compiles iron-space executable and dependances.

# Call without target to make the executable.
#      with run to make & run the exectutable.
#      with clean to remove intermediate files.
#      with deepclean to remove all generated files.
#      with test to make and run the test executable.
#      with step-test to run the program with gdb as a test wrapper.
#      with mem-test to run the program with valgrind as a test wrapper.
# And you of course may call with any generated file to create that file.

# Allows for one level of subdirectories within the code directory.
# Some of the internal do have to be updated as you go.

### Variables & Setup

# 'yes' to turn on debugging options, otherwise leaves them off.
USE_DEBUG=no

# Name of binary executable.
EXE=iron-space

# Name of test binary executable.
TST_EXE=run-tests


# The name of the directory that holds code.
CODEDIR=src
# The name of every sub directory of CODEDIR.
#   It is defined as all files in CODEDIR that do not contain a '.'
DIRNAMES ::= $(shell ls -1 $(CODEDIR) | grep '^[^.]*$$' -)

# List of secondary make files:
SUBMAKES ::= $(wildcard mk/*.mk)

# Calculated as to allow the repository to be used multiple places.
ROOT=$(shell ./.here)

# The name of the temperary directory for object and dependancy files.
TMPDIR=.tmp

# C++ Compiler
CXX=g++
# Flags for compilation
CXXFLAGS=-Wall --std=c++11 -iquote $(ROOT)/src
# Additional libraries for the linking step.
CXXLIBS=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
# Additional flags for debug builds.
DEBUG=-ggdb -DDEBUG=true
# Extra flags for building the test harness.
TSTFLAGS=-I$(ROOT)

### End of Setup

### Interal variables

# Patterns:
CPP_PAT=$(CODEDIR)/%.cpp
MAIN_PAT=$(CODEDIR)/main%cpp
# NRM_PAT does not exist, it is CPP_PAT excluding MAIN_PAT.
# SRC_PAT does not exist, it is CPP_PAT excluding MAIN_PAT and TST_PAT.
TST_PAT=$(CODEDIR)/%.tst.cpp
OBJ_PAT=$(TMPDIR)/%.o
DEP_PAT=$(TMPDIR)/%.d

# List of other generated files.
search=$(firstword $(shell egrep '_GENERATES' $(1)))
GEN_FILES=$(foreach mkfile,$(SUBMAKES),$(call search,$(mkfile)))

# List of all cpp files. These are the files complied to objects.
# All existing cpp files are used.
CPP1=$(wildcard $(CODEDIR)/*.cpp $(CODEDIR)/*/*.cpp)
# Any generated cpp files are added.
CPP2=$(filter $(CPP_PAT),$(GEN_FILES))
CPPFILES=$(sort $(CPP1) $(CPP2))

# List of all object and depends files, one each for each cpp.
OBJFILES=$(CPPFILES:$(CPP_PAT)=$(OBJ_PAT))
DEPFILES=$(CPPFILES:$(CPP_PAT)=$(DEP_PAT))

# List of normal cpp files that do not contain main functions.
NRMFILES=$(filter-out $(MAIN_PAT),$(CPPFILES))

# List of all cpp files that contain main functions.
# I don't actually use this, but here is how you would find it.
MAINFILES=$(filter $(MAIN_PAT),$(CPPFILES))

# List of source cpp files, those used for the final executable.
SRCFILES=$(filter-out $(TST_PAT),$(NRMFILES))
SRCMAIN=src/main.cpp

# List of test cpp files, those used for the test executable.
TSTFILES=$(filter $(TST_PAT),$(NRMFILES))
TSTMAIN=src/main.tst.cpp

# Calculated File Names
SUBDIRS=$(DIRNAMES:%=$(TMPDIR)/%)

# Functions: use with call.
# As dir, but removes the trailing /
getdir=$(patsubst %/,%,$(dir $(1)))

# Get a list of the objects for the given cpp files.
objsfor=$(1:$(CPP_PAT)=$(OBJ_PAT))

# If USE_DEBUG add the DUBUG flags.
ifeq ($(USE_DEBUG),yes)
  CXXFLAGS+=$(DEBUG)
endif

# Special Rules

# List of 'commands', which are implemented as PHONY rules.
.PHONY : all run clean deepclean test step-test mem-test

# File uses second expansion (one rule does).
.SECONDEXPANSION :

### Recipes and Rules

all : $(EXE)

# Rule for the binary
$(EXE) : $(call objsfor,$(SRCFILES) $(SRCMAIN))
	$(CXX) $(CXXFLAGS) $^ $(CXXLIBS) -o $@

# Rule for test binary
$(TST_EXE) : $(call objsfor,$(TSTFILES) $(SRCFILES) $(TSTMAIN))
	$(CXX) $(CXXFLAGS) $(TSTFLAGS) $^ $(CXXLIBS) -o $@

# Rules for object files
# Object depencancy rule, gives the dependancies that always apply.
$(OBJFILES) : $(OBJ_PAT) : $(CPP_PAT) | $$(call getdir,$$@)

# Object compilation for regular (non-testing) objects
$(call objsfor,$(SRCFILES) $(SRCMAIN)) :
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@
#       echo "compiling src $< to $@"

# Object compilation for testing objects
$(call objsfor,$(TSTFILES) $(TSTMAIN)) :
	$(CXX) $(CXXFLAGS) $(TSTFLAGS) -MMD -c $< -o $@
#       echo "compiling tst $< to $@"

# Rule for the temperary directory
$(TMPDIR) :
	mkdir $@

# Rule for sub temperary directories
$(SUBDIRS) : | $(TMPDIR)
	mkdir $@

### Action rules:

# Phony rule for running the executable.
run : $(EXE)
	./$<

# Phony rule for cleaning intermediate files
clean :
	-rm $(TMPDIR)/*/*.[do]
	-rm $(TMPDIR)/*.[do]
	-rmdir $(SUBDIRS)
	-rmdir $(TMPDIR)

# Phony rule for cleaning generated files
deepclean : clean
	-rm $(EXE)
	-rm $(TST_EXE)
	-rm $(GEN_FILES)

# Phony rule for running the test executable.
test : $(TST_EXE)
	./$<

# Phony rules for running the test wrappers
step-test : $(EXE)
	gdb ./$(EXE)

mem-test : $(EXE)
	valgrind ./$(EXE)

### Include Sub-Makefiles

include mk/*.mk

### Include Depends Files

-include $(DEPFILES)
