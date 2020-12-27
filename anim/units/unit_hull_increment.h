/* Reshetnyak Ivan */

#ifndef __unit_hull_increment_h_
#define __unit_hull_increment_h_

#include <glut.h>

#include <algorithm>

#include "../../def.h"
#include "../anim.h"
#include "../unit.h"

#include <vector>

class unit_hull : public unit
{
private:
  std::vector<vec2> Dots;
  std::vector<vec2> Lines;

public:
  unit_hull( anim &Ani )
  {
    /*
    Dots.push_back(vec2(0, 0.1));
    Dots.push_back(vec2(0, 0.0));
    Dots.push_back(vec2(0.3, 0.2));
    Dots.push_back(vec2(0, -0.1));
    Dots.push_back(vec2(0.4, 0.1));
    Dots.push_back(vec2(0.5, 0.0));
    Dots.push_back(vec2(0.2, 0.15));
    Dots.push_back(vec2(0.1, 0.1));
    Dots.push_back(vec2(0.5, 0.1));
    Dots.push_back(vec2(0.5, -0.1));
    CreateHull();
    */
  }

  void Render( anim &Ani )
  {
    glPointSize(5);
    glBegin(GL_POINTS);
    for (auto &i : Dots)
      glVertex2d(i.X, i.Y);
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (unsigned int i = 0; i < Lines.size(); i++)
      glVertex2d(Lines[i].X, Lines[i].Y);
    glEnd();
  }

  /* Map value from 0..1 to -1..1 range function.
   * ARGUMENTS:
   *   - value to map:
   *       double a;
   * RETURNS:
   *   (double) mapped value.
   */
  static double Map01to_11( double a )
  {
    return Map(a, 0, 1, -1, 1);
  } /* End of 'Map01to_11' function */

  /* Mouse callback.
   * ARGUMENS:
   *   - animation structure:
   *       anim &Ani;
   *   - pressed button:
   *       int Button;
   *   - button state:
   *       int State;
   *   - mouse coordinates:
   *       int X, Y;
   * RETURNS: None.
   */
  void Mouse( anim &Ani, int Button, int State, int X, int Y )
  {
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
      Dots.push_back(vec2(Map01to_11((double)X / Ani.WinW), -Map01to_11((double)Y / Ani.WinH)));
    CreateHull();
  } /* End of 'Mouse' function */

  /* Create convex hull function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  void CreateHull( void )
  {
    if (Dots.size() < 2)
      return;
    Lines.clear();  /* Clear old */

    /* Sort new input */
    std::sort(Dots.begin(), Dots.end(),
      []( vec2 &a, vec2 &b ) -> int
      {
        if (a.X == b.X)
          return a.Y > b.Y;
        else
          return a.X < b.X;
      });

    Lines.push_back(Dots[0]);
    Lines.push_back(Dots[1]);
    for (unsigned i = 2; i < Dots.size(); i++)
    {
      //Lines.push_back(Dots[i]);
      double t1;
      while (Lines.size() >= 2 &&
        (t1 = ((Lines[Lines.size() - 1] - Lines[Lines.size() - 2]) % (Dots[i] - Lines[Lines.size() - 1]))) < 0 && abs(t1) > 0.00000001)
        Lines.pop_back();
      Lines.push_back(Dots[i]);
    }

    for (int i = Dots.size() - 2; i >= 0; i--)
    {
      //Lines.push_back(Dots[i]);
      double t1;
      while (Lines.size() >= 2 &&
        (t1 = ((Lines[Lines.size() - 1] - Lines[Lines.size() - 2]) % (Dots[i] - Lines[Lines.size() - 1]))) < 0 && abs(t1) > 0.00000001)
        Lines.pop_back();
      Lines.push_back(Dots[i]);
    }
  } /* End of 'CreateHull' function */
}; /* End of 'unit_hull' function */

#endif /* __unit_hull_increment_h_ */
