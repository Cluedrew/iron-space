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

# Calculated File Names
SUBDIRS=$(DIRNAMES:%=$(TMPDIR)/%)

# If USE_DEBUG add the DUBUG flags.
ifeq ($(USE_DEBUG),yes)
  CXXFLAGS+=$(DEBUG)
endif

.PHONY : all clean deepclean test mem-test

### Recipes and Rules

all : $(EXE)

# Rule for the binary
$(EXE) : $(SRCFILES:$(CPP_PAT)=$(OBJ_PAT)) $(SRCMAIN:$(CPP_PAT)=$(OBJ_PAT))
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $^ -o $@

# Rule for object files
# OK, I think the issue is dir is evaluated before stem is evaluated.
# I can get around it with SECONDEVALUATION~ but I would prefer not to have
# that for this 1 case. If there isn't a better way I'll do it.
$(OBJFILES) : $(TMPDIR)/%.o : $(CODEDIR)/%.cpp | $(dir $(TMPDIR)/$*)
	@echo generating files in $(dir $@)
	@echo $(dir $(TMPDIR)/$*)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Rule for the temperary directory
$(TMPDIR)/ :
	mkdir $@

# Rule for sub temperary directories
$(SUBDIRS)/ : | $(TMPDIR)/
	mkdir $@

# Phony rule for cleaning intermediate files
clean :
	-rm $(OBJFILES)
	-rm $(DEPFILES)
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
