#ifndef RSRC_DIR_HPP
#define RSRC_DIR_HPP

/* Exports the path to the resource directory, where all resources files are
 * kept. The path is generated so it doesn't mater where the project is but
 * rsrc has to stay under the project root.
 *
 * Also there is no trailing slash.
 */

extern char const * const resourceDirectory;

#endif//RSRC_DIR_HPP
