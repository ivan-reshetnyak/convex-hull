/* Reshetnyak Ivan */

#ifndef __unit_hull_brute_h_
#define __unit_hull_brute_h_

#include <glut.h>

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
    Dots.push_back(vec2(0, 0.1));
    Dots.push_back(vec2(0, -0.1));
    Dots.push_back(vec2(0, -0.2));
    Dots.push_back(vec2(0, 0.0));
    Dots.push_back(vec2(0.1, 0.0));
  }

  void Render( anim &Ani )
  {
    glPointSize(5);
    glBegin(GL_POINTS);
    for (auto &i : Dots)
      glVertex2d(i.X, i.Y);
    glEnd();

    if (Dots.size() < 4)
      return;
    glBegin(GL_LINES);

    for (unsigned int i = 0; i < Lines.size(); i += 2)
    {
      glVertex2d(Lines[i].X, Lines[i].Y);
      glVertex2d(Lines[i + 1].X, Lines[i + 1].Y);
    }
    glEnd();
  }

  static double Map01to_11( double a )
  {
    return Map(a, 0, 1, -1, 1);
  }

  void Mouse( anim &Ani, int Button, int State, int X, int Y )
  {
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
      Dots.push_back(vec2(Map01to_11((double)X / Ani.WinW), -Map01to_11((double)Y / Ani.WinH)));

    if (Dots.size() < 4)
      return;
    Lines.clear();
    for (unsigned i = 0; i < Dots.size(); i++)
      for (unsigned j = i + 1; j < Dots.size(); j++)
      {
        if (Dots[i] == Dots[j])
          /* Degenerate */
          continue;
        int sgn = -8, t;
        vec2 v = Dots[j] - Dots[i];
        bool flag = true;  /* Isok */
        for (unsigned k = 0; k < Dots.size(); k++)
        {
          if (Dots[i] == Dots[k] || Dots[j] == Dots[k])
            /* Degenerate */
            continue;
          if (sgn == -8)
            /* First time */
            sgn = Sign(v % (Dots[k] - Dots[i]));
          if (sgn == 0)
            sgn = -8;
          else if ((t = Sign(v % (Dots[k] - Dots[i]))) != sgn && t != 0)
          {
            /* Wrong side */
            flag = false;
            break;
          }
        }
        if (flag)
        {
          Lines.push_back(Dots[i]);
          Lines.push_back(Dots[j]);
        }
      }
  }
};

#endif /* __unit_hull_brute_h_ */
