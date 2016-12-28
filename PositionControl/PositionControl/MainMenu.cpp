/*
 * MainMenu.cpp
 *
 * Created: 02.05.2015 23:00:39
Copyright (c) 2015 Eckart Schlottmann
Author: Eckart Schlottmann


This software is distributed under the terms of the 
Mozilla Public License Version 2.0
This license is distributed alongside with this software or can be 
obtained from http://mozilla.org/MPL/2.0/

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
*  limitation may not apply to You.                                    *
*                                                                      *
************************************************************************

 */
#include "MainMenu.h"
#include "PositionControl.h"

enum
{
  BUTTON_SETTING, BUTTON_PROGRAM, BUTTON_CONTROL
};

#define NUMBER_OF_LAYOUT_LINES  4
#define NUMBER_OF_LAYOUT_COLUMNS 3

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

#define BUTTON_SETTING_COORDS BUTTON_COORDS(0,0)
#define BUTTON_PROGRAM_COORDS BUTTON_COORDS(1,0)
#define BUTTON_CONTROL_COORDS BUTTON_COORDS(2,0)

#define GROOVEPICTURE_POSITION 0, LINE(2)+BUTTON_LINE_OFFSET, SCREEN_WIDTH, NUMBER_BUTTON_HEIGHT

#define SPECIALBUTTONDEF(x,text) { x,false,true,x##_COORDS,BLUE,DARK_BLUE,WHITE, #text ,false }

menuButtonType mainMenuButton[] = {
SPECIALBUTTONDEF(BUTTON_SETTING,Settings),
SPECIALBUTTONDEF(BUTTON_PROGRAM,Program),
SPECIALBUTTONDEF(BUTTON_CONTROL,Control), };

MainMenu::MainMenu(UTFT *Disp, URTouch *Touch, TFT_Extension *TFTextention)
    : Menu(Disp, Touch, TFTextention)
{
  _screenButtons = mainMenuButton;
  _numScreenButtons = sizeof(mainMenuButton) / sizeof(menuButtonType);
}

MainMenu::~MainMenu(void)
{

}

void MainMenu::menuIsActivating(void)
{
  _Disp->setFont(SmallFont);
  _Disp->setColor(WHITE);
  _Disp->setBackColor(BLACK);

  programMenu.drawGrooves(GROOVEPICTURE_POSITION);
}

void MainMenu::dispatch(uint8_t buttonNumber)
{
  switch (buttonNumber)
  {
    case BUTTON_SETTING:
      this->settingMenuOperation();
      break;
    case BUTTON_PROGRAM:
      this->programOperation();
      break;
    case BUTTON_CONTROL:
      this->controlMenuOperation();
      break;
  }
}

void MainMenu::settingMenuOperation()
{
  this->menuDeactivate();
  settingMenu.menuActivate();
}

void MainMenu::programOperation()
{
  this->menuDeactivate();
  programMenu.menuActivate();

}

void MainMenu::controlMenuOperation()
{
  this->menuDeactivate();
  controlMenu.menuActivate();

}

void MainMenu::activate(void)
{

}
