# Create and remove links for the code base.
# Work-In-Progress

# Really, I'm just tried of "../objects/button.hpp" and with the right links
# ".top/objects/button.hpp" or ".objects/button.hpp" can be used, which might
# be just a bit cleaner.

# Should import CODEDIR and DIRNAMES

.PHONY: links clean-links

ALL_LINKS=$(addsuffix /.top,$(CODEDIR) $(addprefix $(CODEDIR),$(DIRNAMES)))
TOP_LINKS=$(CODEDIR)/.top
SUB_LINKS=$(patsubst %,$(CODEDIR)/%/.top,$(DIRNAMES))

links : $(ALL_LINKS)

# No-op link. .top -> .
$(TOP_LINKS) :
	ln -s -T $(CODEDIR) $@

# Bring us up to the top level. .top -> ..
$(SUB_LINKS) :
	ln -s -T $(CODEDIR) $@

# .DIR links would just expand to .top/DIR
