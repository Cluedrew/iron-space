# Create a file that contains the path to the resourceDirectory
# ROOT must be passed in, it should be the pwd and the project root.

GEN_FILES+=src/util/rsrc-dir.gen.cpp

src/util/rsrc-dir.gen.cpp : mk/rsrc-dir.base
	sed --expression "s|ROOT_DIR|$(ROOT)|g" $< > $@
