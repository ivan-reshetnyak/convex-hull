/* Reshetnyak Ivan */

#ifndef __def_h_
#define __def_h_

/* Common includes */
#include "math/vec2.h"
#include "math/color.h"

#include <vector>

/* Debug memory allocation support */ 
#ifdef _DEBUG
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h>
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
static class __Dummy 
{
public:
  /* Class constructor */
  __Dummy( void )
  { 
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __oops;

#endif /* _DEBUG */

#ifdef _DEBUG
# ifdef _CRTDBG_MAP_ALLOC 
# define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

/* Useful types */
typedef vec2D<double> vec2;
typedef color4<double> color;

/* Forward reference */
class anim;
class unit;

inline double Map( double x, double a0, double a1, double b0, double b1 )
{
  x -= a0;
  x /= (a1 - a0);
  x *= (b1 - b0);
  x += b0;
  return x;
}

inline int Sign( double a )
{
  return a > 0 ? 1 :
    a < 0 ? -1 :
    0;
}

inline double PolygonSquare( std::vector<vec2> &Polygon, int offset = 0 )
{
  auto cut =
    [Polygon](int i) -> int
    {
      return (i + Polygon.size()) % Polygon.size();
    };
  double sq = 0;
  for (unsigned i = 0; i < Polygon.size(); i++)
    sq += 0.5 * (Polygon[cut(offset + i + 1)].X - Polygon[cut(offset + i)].X) * 
      (Polygon[cut(offset + i + 1)].Y + Polygon[cut(i + offset)].Y);
  return sq;
}

#endif /* __def_h_ */

/* END OF 'def.h' FILE */
