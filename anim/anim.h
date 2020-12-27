/* Reshetnyak Ivan */

#ifndef __anim_h_
#define __anim_h_

#include <cstdlib>

#include <glut.h>

#include "../def.h"
#include "unit.h"

#include <vector>

/* Animation handle class */
class anim
{
public:
  static anim Anim;
  std::vector<unit *> Units;
  int WinW, WinH;

  vec2 RightClick;

private:
  /* Keyboard callback function.
   * ARGUMENTS:
   *   - pressed key code:
   *       unsigned char Key;
   *   - mouse coordinates:
   *       int X, Y;
   * RETURNS: None.
   */
  static void Keyboard( unsigned char Key, int X, int Y )
  {
    for (auto &i : Anim.Units)
      i->Keyboard(Anim, Key, X, Y);
    switch (Key)
    {
    case 27:
      exit(0);
    };
  } /* End of 'Keyboard' function */

  /* Display callback function.
   * ARGUMENTS: None. 
   * RETURNS: None.
   */
  static void Display( void )
  {
    glClearColor(0.6, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &i : Anim.Units)
      i->Response(Anim);

    for (auto &i : Anim.Units)
      i->Render(Anim);
    //glutWireTeapot(1);
    //glDrawPixels(1366, 768, GL_BGRA_EXT, GL_UNSIGNED_BYTE, nullptr);

    glutSwapBuffers();
    glutPostRedisplay();
    glFinish();
  } /* End of 'Display' function */


  /* Keyboard callback function.
   * ARGUMENTS:
   *   - pressed key code:
   *       unsigned char Key;
   *   - mouse coordinates:
   *       int X, Y;
   * RETURNS: None.
   */
  static void Mouse( int Button, int State, int X, int Y )
  {
    /*if (Button == GLUT_RIGHT_BUTTON)
      Anim.RightClick = vec2(Map((double)X / Anim.WinW, 0, 1, -1, 1),
        Map((double)Y / Anim.WinH, 0, 1, -1, 1));*/

    for (auto &i : Anim.Units)
      i->Mouse(Anim, Button, State, X, Y);
  } /* End of 'Mouse' function */

  /* Keyboard callback function.
   * ARGUMENTS:
   *   - mouse coordinates:
   *       int X, Y;
   * RETURNS: None.
   */
  static void Motion( int X, int Y )
  {
    return;
    glTranslated(Map((double)X / Anim.WinW, 0, 1, -1, 1) - Anim.RightClick.X,
      -Map((double)Y / Anim.WinH, 0, 1, -1, 1) + Anim.RightClick.Y, 0);
    Anim.RightClick = vec2(Map((double)X / Anim.WinW, 0, 1, -1, 1),
        Map((double)Y / Anim.WinH, 0, 1, -1, 1));
  } /* End of 'Mouse' function */

  static void Resize( int W, int H )
  {
    Anim.WinW = W;
    Anim.WinH = H;
    glViewport(0, 0, W, H);
  }
public:
  /* Initialization function.
   * ARGUMENTS:
   *   - number of command line arguments:
   *       int argc;
   *   - command line arguments:
   *       char *argv[];
   *   - window caption:
   *       char *WindowName = "";
   * RETURNS: None.
   */
  void Init( int argc, char *argv[], char *WindowName = "" )
  {
    glutInit(&argc, argv);
    glutInitWindowSize(WinW, WinH);
    glutCreateWindow(WindowName);

    glutDisplayFunc(Display);
    glutMouseFunc(Mouse);
    glutKeyboardFunc(Keyboard);
    glutMotionFunc(Motion);
    glutReshapeFunc(Resize);

    glutMainLoop();
  } /* End of 'Init' function */

  anim & operator<<( unit *Unit )
  {
    Units.push_back(Unit);
    return *this;
  }

private:
  const int DEFAULT_WINDOW_WIDTH = 1366;
  const int DEFAULT_WINDOW_HEIGHT = 768;

  /* Class constructor.
   */
  anim()
  {
    WinW = DEFAULT_WINDOW_WIDTH;
    WinH = DEFAULT_WINDOW_HEIGHT;
  } /* End of 'anim' constructor */

  ~anim()
  {
    for (auto &i : Units)
      delete i;
  }
}; /* End of 'anim' class */

#endif /* __anim_h_ */
