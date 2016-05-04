# Makefile for InkV8.0: compiles inkv8 executable and dependances.

# Call without target to make the executable.
#      with clean to remove intermediate files.
#      with deepclean to remove all generated files.
#      with test to run the program with gdb as a test wrapper.
#      with mem-test to run the program with valgrind as a test wrapper.

# Allows for one level of subdirectories within the code directory.
# Some of the internal variables do have to be updated as you go.

### Variables & Setup

# 'yes' to turn on debugging options, otherwise leaves them off.
USE_DEBUG=no

# Name of binary executable.
EXE=inkv8

# The base name of every code file used to create the binary.
FILENAMES=main

# The name of the directory that holds code.
CODEDIR=src
# The name of the temperary directory for object and dependancy files.
TMPDIR=.tmp
# The name of every sub directory of CODEDIR.
DIRNAMES=physics

# C++ Compiler
CXX=g++
# Flags for compilation
CXXFLAGS=-Wall --std=c++11
# Additional libraries for the linking step.
CXXLIBS=-lsfml-graphics -lsfml-window -lsfml-system
# Additional flags for debug builds.
DEBUG=-ggdb -DDEBUG=true

# Functions
# I'm just thinking about how I could automate this process, so the file
# doesn't have to be updated.
#filter-out-code
#  =$(filter-out %.cpp,$(filter-out %.hpp,$(filter-out %.tpp,$(1))))
#ROOTFILES=$(wildcard $(CODEDIR)/*)
#DIRS=$(call filter-out-code,$(ROOTFILES))
#ALLFILES=$()

# Calculated File Names
CPPFILES=$(FILENAMES:%=$(CODEDIR)/%.cpp)
OBJFILES=$(FILENAMES:%=$(TMPDIR)/%.o)
DEPFILES=$(OBJFILES:%.o=%.d)
SUBDIRS=$(DIRNAMES:%=$(TMPDIR)/%)

# If USE_DEBUG add the DUBUG flags.
ifeq ($(USE_DEBUG),yes)
  CXXFLAGS+=$(DEBUG)
endif

.PHONY : all clean deepclean test mem-test

### Recipes and Rules

all : $(EXE)

# Rule for the binary
$(EXE) : $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(CXXLIBS) $^ -o $@

# Rule for object files
$(OBJFILES) : $(TMPDIR)/%.o : $(CODEDIR)/%.cpp | $(TMPDIR)/$(dir %)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Rule for the temperary directory
$(TMPDIR) :
	mkdir $@

# Rule for sub temperary directories
$(SUBDIRS) : | $(TMPDIR)
	mkdir $@

# Phony rule for cleaning intermediate files
clean :
	-rm $(OBJFILES)
	-rm $(DEPFILES)
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
