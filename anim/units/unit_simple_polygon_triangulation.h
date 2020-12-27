/* Reshetnyak Ivan */

#ifndef __unit_simple_polygon_triangluation_h_
#define __unit_simple_polygon_triangulation_h_

#include <glut.h>

#include "../../def.h"
#include "../anim.h"
#include "../unit.h"

#include <vector>
#include <array>

class unit_triangulation : public unit
{
private:
  std::vector<vec2> Dots;                      /* Points array - polygon to be triangulated */
  std::vector<bool> Valids;                    /* 'Valid' points */
  std::vector<std::array<vec2, 3>> Triangles;  /* Triangulation result */

public:
  /* Unit constructor.
   * ARGUMENTS: None.
   */
  unit_triangulation( void )
  {
  } /* End of 'unit_triangulation' constructor */

  /* Unit render function.
   * ARGUMENTS:
   *   - animation structure reference:
   *       anim &Ani.
   */
  void Render( anim &Ani )
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin(GL_LINE_LOOP);
    glColor3d(1, 1, 1);
    for (unsigned int i = 0; i < Dots.size(); i++)
    {
      glVertex2d(Dots[i].X, Dots[i].Y);
    }
    glEnd();

    glPointSize(5);
    glBegin(GL_POINTS);
    for (unsigned int i = 0; i < Dots.size(); i++)
    {
      if (Valids[i])
        glColor3d(1, 1, 1);
      else
        glColor3d(0, 0, 0);
      glVertex2d(Dots[i].X, Dots[i].Y);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3d(0.5, 0.7, 0.5);
    for (unsigned int i = 0; i < Triangles.size(); i++)
    {
      glVertex2d(Triangles[i][0].X, Triangles[i][0].Y);
      glVertex2d(Triangles[i][1].X, Triangles[i][1].Y);
      glVertex2d(Triangles[i][2].X, Triangles[i][2].Y);
    }
    glEnd();
  } /* End of 'Render' function */

private:
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

public:
  /* Mouse callback function.
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
    {
      Dots.push_back(vec2(Map01to_11((double)X / Ani.WinW), -Map01to_11((double)Y / Ani.WinH)));
      Valids.push_back(true);
    }
    else if (Button == GLUT_RIGHT_BUTTON && State == GLUT_DOWN)
      Slice();
    else if (Button == GLUT_MIDDLE_BUTTON && State == GLUT_DOWN)
    {
      Dots.clear();
      Valids.clear();
      Triangles.clear();
    }
  } /* End of 'Mouse' function */

  void Keyboard( anim &Ani, unsigned char Key, int X, int Y )
  {
    switch (Key)
    {
    case 'z':
      Dots.pop_back();
      Valids.pop_back();
      break;
    }
  }

private:
  /* Error-proof dots array index cut.
   * ARGUMENTS:
   *   - index you want to cut:
   *       int i;
   * RETURNS:
   *   (int) cut index (from 0 to size - 1).
   */
  int cut( int i )
  {
    int t0 = (i + Dots.size()) % Dots.size();
    return t0;
  } /* End of 'cut' function */

public:
  /* Simple polygon triangulation function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  void Slice( void )
  {
    if (Dots.size() < 3)
      /* No polygon present */
      return;
    Triangles.clear();
    for (auto &i : Valids)
      i = true;

    int sec;
    /* Cycling until whole polygon is triangulated */
    while (Triangles.size() + 2 < Dots.size())
      for (unsigned i = 0; i < Dots.size() && Triangles.size() + 2 < Dots.size();)
      {
        std::array<vec2, 3> a;
        int ci = i;
        for (int j = 0; j < 3; j++)
        {
          while (!Valids[cut(i)])
            /* Looking for valid points */
            i++;
          if (j == 1)
            /* This will be invalid */
            sec = cut(i);
          a[j] = Dots[cut(i)];
          i++;
        }
        i = ci + 1;
        if ((a[1] - a[0]) % (a[2] - a[1]) > 0)
        {
          /* We made right turn */
          bool flag = true;
          for (auto &k : Dots)
            if (k != a[0] && k != a[1] && k != a[2] &&
                (a[1] - a[0]) % (k - a[0]) > 0.00001 &&
                (a[2] - a[1]) % (k - a[1]) > 0.00001 &&
                (a[0] - a[2]) % (k - a[2]) > 0.00001)
              /* This is bad - some point is inside our triangle */
              flag = false;
          if (flag)
          {
            /* Tis is good triangle - add it and invalidate one vertex */
            Triangles.push_back(a);
            Valids[sec] = false;
          }
        }
      }
  } /* End of 'Slice' function */
};

#endif /* __unit_simple_polygon_triangulation_h_ */

/* END OF 'unit_simple_polygon_triangulation' FILE */
