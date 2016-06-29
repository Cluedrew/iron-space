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


# The following directories are searched for code.
# The name of the directory that holds code.
CODEDIR=src
# The name of every sub directory of CODEDIR.
DIRNAMES=util event
#   It is defined as all files in CODEDIR that do not contain a '.'
#DIRNAMES ::= $(shell ls -1 $(CODEDIR) | grep '^[^.]*$' -)

# The name of the temperary directory for object and dependancy files.
TMPDIR=.tmp

# C++ Compiler
CXX=g++
# Flags for compilation
CXXFLAGS=-Wall --std=c++11
# Additional libraries for the linking step.
CXXLIBS=-lsfml-graphics -lsfml-window -lsfml-system
# Additional flags for debug builds.
DEBUG=-ggdb -DDEBUG=true

# Calculated as to allow the repository to be used multiple places.
ROOT=$(shell ./.here)

### End of Setup

# Patterns:
CPP_PAT=$(CODEDIR)/%.cpp
MAIN_PAT=$(CODEDIR)/main%cpp
# NRM_PAT does not exist, it is CPP_PAT excluding MAIN_PAT.
# SRC_PAT does not exist, it is CPP_PAT excluding MAIN_PAT and TST_PAT.
TST_PAT=$(CODEDIR)/%.tst.cpp
OBJ_PAT=$(TMPDIR)/%.o
DEP_PAT=$(TMPDIR)/%.d

# List of all cpp files. These are the files complied to objects.
CPPFILES=$(wildcard $(CODEDIR)/*.cpp $(CODEDIR)/*/*.cpp)
#$(FILENAMES:%=$(CODEDIR)/%.cpp)

# List of all object and depends files, one each for each cpp.
OBJFILES=$(CPPFILES:$(CPP_PAT)=$(OBJ_PAT))
DEPFILES=$(CPPFILES:$(CPP_PAT)=$(DEP_PAT))

# List of normal cpp files that do not contain main functions.
NRMFILES=$(filter-out $(MAIN_PAT),$(CPPFILES))

# List of source cpp files, those used for the final executable.
SRCFILES=$(filter-out $(TST_PAT),$(NRMFILES))
SRCMAIN=src/main.cpp

# List of test cpp files, those used for the test executable.
TSTFILES=$(filter $(TST_PAT),$(NRMFILES))
TSTMAIN=src/main.tst.cpp
# ! Should probably generate the various mains.

# Calculated File Names
SUBDIRS=$(DIRNAMES:%=$(TMPDIR)/%)

# Functions: use with call.
# As dir, but removes the trailing /
getdir=$(patsubst %/,%,$(dir $(1)))

# Get a list of the objects for the given cpp files.
objsfor=$(1:$(CPP_PAT)=$(OBJ_PAT))

# Extra flags for compilation and linking of the test harness.
TSTFLAGS=-I$(ROOT)

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

run : $(EXE)
	./$(EXE)

# Rule for the binary
$(EXE) : $(call objsfor,$(SRCFILES) $(SRCMAIN))
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $^ -o $@

# Rule for test binary
$(TST_EXE) : $(call objsfor,$(TSTFILES) $(SRCFILES) $(TSTMAIN))
	$(CXX) $(CXXFLAGS) $(TSTFLAGS) $(CXXLIBS) $^ -o $@

# Rules for object files
# Object depencancy rule, gives the dependancies that always apply.
$(OBJFILES) : $(OBJ_PAT) : $(CPP_PAT) | $$(call getdir,$$@)

# Object compilation for regular (non-testing) objects
$(call objsfor,$(SRCFILES) $(SRCMAIN)) :
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Object compilation for testing objects
$(call objsfor,$(TSTFILES) $(TSTMAIN)) :
	$(CXX) $(CXXFLAGS) $(TSTFLAGS) -MMD -c $< -o $@

# Rule for the temperary directory
$(TMPDIR) :
	mkdir $@

# Rule for sub temperary directories
$(SUBDIRS) : | $(TMPDIR)
	mkdir $@

# Phony rule for cleaning intermediate files
clean :
	-rm $(TMPDIR)/*/*.[do]
	-rm $(TMPDIR)/*.[do]
	-rmdir $(SUBDIRS)
	-rmdir $(TMPDIR)

# Phony rule for cleaning generated files
deepclean : clean
	-[ -e $(EXE) ] && rm $(EXE)
	-[ -e $(TST_EXE) ] && rm $(TST_EXE)

# Phony rules for running the test executable.
test : $(TST_EXE)
	./$<

# Phony rules for running the test wrappers
step-test : $(EXE)
	gdb ./$(EXE)

mem-test : $(EXE)
	valgrind ./$(EXE)

### Include Depends Files

-include $(DEPFILES)
