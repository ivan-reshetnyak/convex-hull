/* Reshetnyak Ivan */

#ifndef __unit_h_
#define __unit_h_

#include "../def.h"

/* Animation unit class */
class unit
{
public:
  unit( void )
  {
  }

  virtual void Render( anim &Ani )
  {
  }

  virtual void Response( anim &Ani )
  {
  }

  virtual void Keyboard( anim &Ani, unsigned char Key, int X, int Y )
  {
  }

  virtual void Mouse( anim &Ani, int Button, int State, int X, int Y )
  {
  }

  virtual ~unit()
  {
  }
};

#endif /* __unit_h_ */
