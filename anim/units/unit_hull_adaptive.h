/* Reshetnyak Ivan */

#ifndef __unit_hull_adaptive_h_
#define __unit_hull_adaptive_h_

#include <glut.h>

#include "../../def.h"
#include "../anim.h"
#include "../unit.h"

#include <vector>

class unit_hull : public unit
{
private:
  std::vector<vec2> Dots;

public:
  unit_hull( anim &Ani )
  {
    AddPoint(vec2(0.1, 0.1));
    AddPoint(vec2(0.1, -0.1));
    AddPoint(vec2(-0.1, -0.1));
    /*AddPoint(vec2(0, -0.1));
    AddPoint(vec2(0.4, 0.1));
    AddPoint(vec2(0.5, 0.0));
    AddPoint(vec2(0.2, 0.15));
    AddPoint(vec2(0.1, 0.1));
    AddPoint(vec2(0.5, 0.1));
    AddPoint(vec2(0.5, -0.1));*/
  }

  void Render( anim &Ani )
  {
    glPointSize(5);
    glBegin(GL_POINTS);
    for (auto &i : Dots)
      glVertex2d(i.X, i.Y);
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (unsigned int i = 0; i < Dots.size(); i++)
      glVertex2d(Dots[i].X, Dots[i].Y);
    glEnd();
  }

  /* Map value from 0..1 to -1..1 function.
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
      AddPoint(vec2(Map01to_11((double)X / Ani.WinW), -Map01to_11((double)Y / Ani.WinH)));
  } /* End of 'Mouse' function */

private:
  int cut( int i )
  {
    int t0 = (i + Dots.size()) % Dots.size();
    return t0;
  }

public:
  void AddPoint( const vec2 &P )
  {
    std::vector<vec2> nl;

    if (Dots.size() < 3)
    {
      Dots.push_back(P);
      return;
    }

    int i = 0;
    int t1, t2;
    int n, p;
    while (i < Dots.size() &&
      (t1 = Sign((Dots[n = cut(i - 1)] - Dots[i]) % (Dots[i] - P))) !=
      (t2 = Sign((Dots[p = cut(i + 1)] - Dots[i]) % (Dots[i] - P))))
    {
      nl.push_back(Dots[cut(i)]);
      i++;
    }
    nl.push_back(Dots[cut(i)]);
    nl.push_back(P);

    i++;
    while (i < Dots.size() &&
      (t1 = Sign((Dots[n = cut(i - 1)] - Dots[i]) % (Dots[i] - P))) !=
      (t2 = Sign((Dots[p = cut(i + 1)] - Dots[i]) % (Dots[i] - P))))
      i++;
    nl.push_back(Dots[cut(i)]);

    Dots = nl;
  }
}; /* End of 'unit_hull' function */

#endif /* __unit_hull_adaptive_h_ */
