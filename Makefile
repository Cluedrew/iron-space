# Makefile for InkV8.0: compiles iron-space executable and dependances.

# Call without target to make the executable.
#      with clean to remove intermediate files.
#      with deepclean to remove all generated files.
#      with test to run the program with gdb as a test wrapper.
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


# The base name of every code file used to create the binary.
FILENAMES=main util/math.tst util/echo

# The name of the directory that holds code.
CODEDIR=src
# The name of the temperary directory for object and dependancy files.
TMPDIR=.tmp
# The name of every sub directory of CODEDIR.
DIRNAMES=util

# C++ Compiler
CXX=g++
# Flags for compilation
CXXFLAGS=-Wall --std=c++11
# Additional libraries for the linking step.
CXXLIBS=-lsfml-graphics -lsfml-window -lsfml-system
# Additional flags for debug builds.
DEBUG=-ggdb -DDEBUG=true

# Calculated as to allow the repository to be used multiple places.
ROOT=$(shell ./here)

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
CPPFILES=$(FILENAMES:%=$(CODEDIR)/%.cpp)

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

# As dir, but removes the trailing /
getdir=$(patsubst %/,%,$(dir $(1)))

# Extra flags for compilation and linking of the test harness.
TSTFLAGS=-I$(ROOT)

# If USE_DEBUG add the DUBUG flags.
ifeq ($(USE_DEBUG),yes)
  CXXFLAGS+=$(DEBUG)
endif

# Special Rules

# List of 'commands', which are implemented as PHONY rules.
.PHONY : all clean deepclean test mem-test

# File uses second expansion (one rule does).
.SECONDEXPANSION :

### Recipes and Rules

all : $(EXE)

# Rule for the binary
$(EXE) : $(SRCFILES:$(CPP_PAT)=$(OBJ_PAT)) $(SRCMAIN:$(CPP_PAT)=$(OBJ_PAT))
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $^ -o $@

# Rule for test binary
$(TST_EXE) : $(patsubst $(CPP_PAT),$(OBJ_PAT),$(TSTFILES) $(SRCFILES) $(TESTMAIN))
	$(CXX) $(CXXFLAGS) $(TSTFLAGS) $(CXXLIBS) $^ -o $@

# Rule for object files
# ! This is going to have to be rules for object files.
#$(OBJFILES) : $(OBJ_PAT) : $(CPP_PAT) | $$(call getdir,$$@)

$(OBJFILES) : $(TMPDIR)/%.o : $(CODEDIR)/%.cpp | $$(call getdir,$$@)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

#$(OBJFILES) : $(OBJ_PAT) : $(CPP_PAT) | $$(call getdir,$$@)
#	$(CXX) $(CXXFLAGS) $(TSTFLAGS) -MMD -c $< -o $@

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
#	-rm $(OBJFILES)
#	-rm $(DEPFILES)
	-rmdir $(SUBDIRS)
	-rmdir $(TMPDIR)

# Phony rule for cleaning generated files
deepclean : clean
	-rm $(EXE)

# Phony rules for running the test wrappers
test : $(EXE)
	gdb ./$(EXE)

mem-test : $(EXE)
	valgrind ./$(EXE)

### Include Depends Files

-include $(DEPFILES)
