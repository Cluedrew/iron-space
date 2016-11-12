#ifndef RSRC_DIR_HPP
#define RSRC_DIR_HPP

/* Exports the path to the resource directory, where all resources files are
 * kept. The path is generated so it doesn't mater where the project is but
 * rsrc has to stay under root.
 *
 * Also there is no trailing slash.
 */

extern const char const * resourceDirectory;

#endif//RSRC_DIR_HPP

/* Thoughts on the cpp file:
 * The tricky bit is I can't (or shouldn't) hardcode the path.
 * So it has to be generated. Ultimately by a make file, although there could
 * be an intermediate shell file (or interemediate make file) if need be.
 * This example is sort of make, as it uses the $(ROOT) varable from the
 * Makefile.
 */
#if 0
#include "rsrc-dir.hpp"

const char const * resourceDirectory = "$(ROOT)/rsrc"
#endif

/* So lets say we use sub-makefiles to generate all this.
 * In the main Makefile there would be:
 * | $(MAKE) -f $(SUBMAKE) ROOT=$(ROOT)
 * Probably inside a rule to control when it runs and maybe inside a loop
 * to cover however many SUBMAKEs I got. This SUBMAKE would be:
 * | src/util/rsrc-dir.cpp :
 * |         echo #include '"rsrc-dir.hpp"' > $@
 * |         echo >> $@
 * |         echo const char const * resourceDirectory = \"$(ROOT)/rsrc\" >> $@
 * Maybe a variable then echoing the varible might work better.
 */
