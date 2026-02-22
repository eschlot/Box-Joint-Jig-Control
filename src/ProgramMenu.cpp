/*
 * ProgramMenu.cpp
 *
 * Created: 19.05.2015 22:50:53
Copyright (c) 2015 Eckart Schlottmann
Author: Eckart Schlottmann


This software is distributed under the terms of the 
Mozilla Public License Version 2.0 with extensions for safety
This license is distributed alongside with this software 


Under all circumstances note the following paragraphs of the license:


************************************************************************
*                                                                      *
*  6. Disclaimer of Warranty                                           *
*  -------------------------                                           *
*                                                                      *
*  Covered Software is provided under this License on an "as is"       *
*  basis, without warranty of any kind, either expressed, implied, or  *
*  statutory, including, without limitation, warranties that the       *
*  Covered Software is free of defects, merchantable, fit for a        *
*  particular purpose or non-infringing. The entire risk as to the     *
*  quality and performance of the Covered Software is with You.        *
*  Should any Covered Software prove defective in any respect, You     *
*  (not any Contributor) assume the cost of any necessary servicing,   *
*  repair, or correction. This disclaimer of warranty constitutes an   *
*  essential part of this License. No use of any Covered Software is   *
*  authorized under this License except under this disclaimer.         *
*                                                                      *
************************************************************************



************************************************************************
*                                                                      *
*  7. Limitation of Liability                                          *
*  --------------------------                                          *
*                                                                      *
*  Under no circumstances and under no legal theory, whether tort      *
*  (including negligence), contract, or otherwise, shall any           *
*  Contributor, or anyone who distributes Covered Software as          *
*  permitted above, be liable to You for any direct, indirect,         *
*  special, incidental, or consequential damages of any character      *
*  including, without limitation, damages for lost profits, loss of    *
*  goodwill, work stoppage, computer failure or malfunction, or any    *
*  and all other commercial damages or losses, even if such party      *
*  shall have been informed of the possibility of such damages. This   *
*  limitation of liability shall not apply to liability for death or   *
*  personal injury resulting from such party's negligence to the       *
*  extent applicable law prohibits such limitation. Some               *
*  jurisdictions do not allow the exclusion or limitation of           *
*  incidental or consequential damages, so this exclusion and          *
*  limitation may not apply to You.                                    
*                                                                      *
*  Under all circumstances the software shall only be operated under   *
*  the conditions described in the SAFETY documentation.               *
*  The software is only allowed to be operated in a surrounding where  *
*  the safety of the overall system is ensured by the design and the   *
*  construction of the jig to which the electronic hardware including  *
*  the stepper motor and the software are mounted.                     * 
*                                                                      *
*  This software is developed to be used in a jig for a table saw only *
*  where the jig itself is designed in such a way that it cannot harm  *
*  a user under any circumstance.                                      *
*  This means that the design, the construction and the usage of the   *
*  table saw jig has to be done is such a way that even in case the    *
*  stepper motor of the jig is operated in any direction in a middle   *
*  of a cut neither the jig itself or a workpiece in the jig can harm  *
*  a user.                                                             *
*  These extra safety regulations need to be taken over to any         *
*  derived work out of this work.                                      *
*                                                                      *
************************************************************************

 */

#include "ProgramMenu.h"
#include "PositionControl.h"

enum
{
  BUTTON_GO_BACK, BUTTON_CLEAR_PROGRAM, BUTTON_INDIVIDUAL_DISTRIBUTION, BUTTON_LINEAR_DISTRIBUTION,
};

#define NUMBER_OF_LAYOUT_LINES  5
#define NUMBER_OF_LAYOUT_COLUMNS 1

#define BUTTON_COLUMN_OFFSET 20
#define BUTTON_LINE_OFFSET    5

#define NUMBER_BUTTON_WIDTH ((SCREEN_WIDTH/NUMBER_OF_LAYOUT_COLUMNS)-BUTTON_COLUMN_OFFSET)
#define NUMBER_BUTTON_HEIGHT ((SCREEN_HEIGHT/NUMBER_OF_LAYOUT_LINES)-BUTTON_LINE_OFFSET )

#define COLUMN(x) (((SCREEN_WIDTH * x) / NUMBER_OF_LAYOUT_COLUMNS) )
#define LINE(x)   (((SCREEN_HEIGHT *x) / NUMBER_OF_LAYOUT_LINES) )

#define BUTTON_COORDS(x,y)  COLUMN(x)+BUTTON_COLUMN_OFFSET/2,\
LINE(y)+BUTTON_LINE_OFFSET/2,\
COLUMN(x)+NUMBER_BUTTON_WIDTH,\
LINE(y)+NUMBER_BUTTON_HEIGHT

#define BUTTON_GO_BACK_COORDS BUTTON_COORDS(0,0)
#define BUTTON_CLEAR_PROGRAM_COORDS BUTTON_COORDS(0,2)
#define BUTTON_INDIVIDUAL_DISTRIBUTION_COORDS BUTTON_COORDS(0,3)
#define BUTTON_LINEAR_DISTRIBUTION_COORDS BUTTON_COORDS(0,4)

#define SPECIALBUTTONDEF(x,text) { BUTTON_##x,false,true,BUTTON_##x##_COORDS,BLUE,DARK_BLUE,WHITE, #text ,false }

menuButtonType programMenuButton[] = {
SPECIALBUTTONDEF(GO_BACK,BACK),
SPECIALBUTTONDEF(CLEAR_PROGRAM,Clear Program),
SPECIALBUTTONDEF(INDIVIDUAL_DISTRIBUTION,Individual Distribution),
SPECIALBUTTONDEF(LINEAR_DISTRIBUTION,Linear Distribution) };

ProgramMenu::ProgramMenu(UTFT *Disp, URTouch *Touch, TFT_Extension *TFTextention)
    : Menu(Disp, Touch, TFTextention)
{
  _screenButtons = programMenuButton;
  _numScreenButtons = sizeof(programMenuButton) / sizeof(menuButtonType);

  program = new LinkedList<float>();
  lastCurrentPosition = MAXFLOAT;
  lastTargetPosition = MAXFLOAT;
  overallLength = 1.0f;
}

ProgramMenu::~ProgramMenu(void)
{
  program->clear();
  delete (program);
}

void ProgramMenu::menuIsActivating(void)
{
  _Disp->setFont(SmallFont);
  _Disp->setColor(WHITE);
  _Disp->setBackColor(BLACK);
}

void ProgramMenu::dispatch(uint8_t buttonNumber)
{
  switch (buttonNumber)
  {
    case BUTTON_GO_BACK:
      this->menuDeactivate();
      mainMenu.menuActivate();
      break;
    case BUTTON_CLEAR_PROGRAM:
    {
      program->clear();
      break;
    }
    case BUTTON_INDIVIDUAL_DISTRIBUTION:
    {
      this->menuDeactivate();
      individualDistributionMenu.menuActivate();

      break;
    }
    case BUTTON_LINEAR_DISTRIBUTION:
    {
      this->menuDeactivate();
      linearDistributionMenu.menuActivate();
      break;
    }
  }
}

/********************************************************************************************************/
/* service functions for the drawing of the patterns */
/********************************************************************************************************/

void ProgramMenu::drawGrooves(int x, int y, int width, int height)
{
  this->drawGrooves(x, y, width, height, -1);
}

void ProgramMenu::drawPositions(int x, int y, int width, int height, float currentPosition, float targetPosition, bool update)
{ // if update is not set a paint is forced. If update is set than the painting is only done if a change of the variables is detected.

  if (!update || (targetPosition != this->lastTargetPosition) || (currentPosition != this->lastCurrentPosition))
  {

    lastCurrentPosition = currentPosition;
    lastTargetPosition = targetPosition;

    _Disp->setColor(GREEN);
    _Disp->fillRect(x, y, x + width - 1, y + height - 1);
    _Disp->setColor(WHITE);
    _Disp->drawRect(x, y, x + width - 1, y + height - 1);

    float bladeWidth = nvm.SettingMenu_bladeWidth();

    float factor = ((float) width) / (overallLength + 2 * bladeWidth);
    int y1 = y + 1;
    int y2 = y + height - 2;

    int x1 = ((int) (((targetPosition + bladeWidth) * factor) + .5f)) + x; // +.5f for rounding, bladeWidth because the complete diagram is shifted to the right by one bladeWidth
    int x2 = ((int) (((targetPosition + bladeWidth * 2) * factor) + .5f)) + x;
    _Disp->setColor(BLUE);
    if (x1 < 0)
      x1 = 0;
    if (x2 >= 0)
    {
      if (x2 >= SCREEN_WIDTH)
        x2 = SCREEN_WIDTH - 1;
      if (x1 < SCREEN_WIDTH)
        _Disp->fillRect(x1, y1, x2, y2);
    }
    x1 = ((int) (((currentPosition + bladeWidth) * factor) + .5f)) + x; // +.5f for rounding, bladeWidth because the complete diagram is shifted to the right by one bladeWidth
    x2 = ((int) (((currentPosition + bladeWidth * 2) * factor) + .5f)) + x;
    _Disp->setColor(LIGHT_BLUE);
    if (x1 < 0)
      x1 = 0;
    if (x2 >= 0)
    {
      if (x2 >= SCREEN_WIDTH)
        x2 = SCREEN_WIDTH - 1;
      if (x1 < SCREEN_WIDTH)
        _Disp->fillRect(x1, y1, x2, y2);
    }
  }
}

void ProgramMenu::drawGrooves(int x, int y, int width, int height, int highlightedGrooveIndex)
{

  int listSize = program->size();
  if (listSize > 0)
  {
    float bladeWidth = nvm.SettingMenu_bladeWidth();
    float factor = ((float) width) / (overallLength + 2 * bladeWidth);

    int x1 = ((int) (((bladeWidth) * factor) + .5f)) + x; // +.5f for rounding, bladeWidth because the complete diagram is shifted to the right by one bladeWidth
    int x2 = ((int) (((overallLength + bladeWidth) * factor) + .5f)) + x;

    _Disp->setColor(LIGHT_YELLOW);
    _Disp->fillRect(x1, y, x2, y + height - 1);
    _Disp->setColor(WHITE);
    _Disp->drawRect(x1, y, x2, y + height - 1);

    int y1 = y + 1;
    int y2 = y + height - 2;

    for (int i = 0; i < listSize; i++)
    {
      float startPos = program->get(i);
      x1 = ((int) (((startPos + bladeWidth) * factor) + .5f)) + x; // +.5f for rounding, bladeWidth because the complete diagram is shifted to the right by one bladeWidth
      x2 = ((int) (((startPos + bladeWidth * 2) * factor) + .5f)) + x;
      if (highlightedGrooveIndex == i)
      {
        _Disp->setColor(RED);
      }
      else
      {
        if ((i & 0x01) == 0x01)
        {
          _Disp->setColor(DARK_BLUE);
        }
        else
        {
          _Disp->setColor(LIGHT_BLUE);
        }
      }

      _Disp->fillRect(x1, y1, x2, y2);
    }
    _Disp->setColor(WHITE);
  }
  else
  {
    _Disp->setColor(LIGHT_YELLOW);
    _Disp->fillRect(x + 1, y + 1, x + width - 1, y + height - 1);
    _Disp->setColor(WHITE);
    _Disp->drawRect(x, y, x + width, y + height);
  }
}

float ProgramMenu::getOverallLength()
{
  return overallLength;
}
