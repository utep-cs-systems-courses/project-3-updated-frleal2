/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_WHITE);

  drawString5x7(10,20, "IT'S ME MARIO!", COLOR_RED, COLOR_WHITE);

  fillRectangle(0,120, 150, 60, COLOR_GREEN);

  fillRectangle(20,75, 10, 10, COLOR_BROWN);

  drawMario(10,100, COLOR_WHITE);
}

