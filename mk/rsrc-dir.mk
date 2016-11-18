# Create a file that contains the path to the resourceDirectory

# ROOT must be passed in, it should be the pwd and the project root.
# This is still very much a work in progress.
# It will probably be included or called from the main Makefile.

GEN_FILE=src/util/rsrc-dir.gen.cpp

$(GEN_FILE) : mk/rsrc-dir.base
	sed --expression "s|ROOT_DIR|$(ROOT)|g" $< > $@
