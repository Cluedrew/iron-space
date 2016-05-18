# Test Handler MakeFile

# OK it divolved into scratchpad. Writing things down helps me think
# them through.

# This may/probably will be folded into the project Make, but while I'm
# scratching out my thoughts, here it goes.
# Currently running 'g++ test.cpp math.tst.cpp -o test' is enough but I need
# something a little more repeatable, especially as the project (and the
# tests) grow.

# Name of the test executable:
TST_EXE=run-tests

# Name of the test source (the main file for testing)
TST_SRC=test

# I need a list of all the test files (that contain actual tests).
TSTFILES=${ list of *.tst.cpp files }

# Now part of the reason I think the two Makefiles will have to merge is
# there is actually a lot of overlap in terms of the regular .cpp files.
# Infact the only one we don't care about is main.cpp, which would generate
# conflicts, ideally every other file will be touched by the tests.

# Test code files are compiled into objects the same way regular code files
# are. Maybe with the same rule.

# The test executable depends on all test-code-object files
$(TST_EXE) : $(TST_SRC:%.cpp=%.o)
	# Similar call as the main exicutable.

# We need for lists of .cpp files
# MAIN : contains the main function for regular exicution.
# TEST : contains the main function for testing (could have more than one).
# CODE : regular source files, linked with main to create the EXE.
# TESTS: test source files, contain TEST_CASEs to be run.

# All would be compiled to object files in the same way, really it is just
# a matter of what is linked when.
# MAIN + CODE would be used to create the regular executable.
# TEST + TESTS + CODE would be used for tests.

# Next time I'm probably going to just implement the above, at least to start.

# Linking the entire code base might be excesive, but unless there is a way
# to expant the dependancy tree from .d files.

# Later expanding the system might make it worth dividing up the tests a bit.
# But that is sort of what tags are for...
