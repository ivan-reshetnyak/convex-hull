/* Reshetnyak Ivan */

#include "def.h"
#include "anim/anim.h"

#include "anim/units/unit_hull_increment.h"
#include "anim/units/unit_simple_polygon_triangulation.h"

/* Main program function.
 * ARGUMENTS:
 *   - number of command line arguments:
 *       int argc;
 *   - command line arguments:
 *       char *argv[];
 * RETURNS: None.
 */
void main( int argc, char *argv[] )
{
  anim::Anim << new unit_hull(anim::Anim);// << new unit_triangulation();

  anim::Anim.Init(argc, argv, "Convex hull");
} /* End of 'main' function */
