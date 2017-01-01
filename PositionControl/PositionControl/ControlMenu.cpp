/*
* ControlMenu.cpp
*
* Created: 02.05.2015 23:00:39

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
#include "ControlMenu.h"
#include "PositionControl.h"

enum
{
  BUTTON_GO_BACK,
  BUTTON_SETTOZERO,
  BUTTON_ACTIVATE,
  BUTTON_MOVE_LEFT_100,
  BUTTON_MOVE_LEFT_10,
  BUTTON_MOVE_LEFT_1,
  BUTTON_MOVE_LEFT_P1,
  BUTTON_MOVE_RIGHT_P1,
  BUTTON_MOVE_RIGHT_1,
  BUTTON_MOVE_RIGHT_10,
  BUTTON_MOVE_RIGHT_100,
  
  BUTTON_MOVE_LEFT_GROOVE,
  BUTTON_MOVE_RIGHT_GROOVE,
  BUTTON_SELECT_POS_0,
  BUTTON_SELECT_POS_MAX

};

#define NUMBER_OF_LAYOUT_LINES  5
#define NUMBER_OF_LAYOUT_COLUMNS 4
#define NUMBER_OF_LAYOUT_COLUMNS_DENSE 8


#define BUTTON_COLUMN_OFFSET 5
#define BUTTON_COLUMN_OFFSET_DENSE 5

#define BUTTON_LINE_OFFSET    5

#define NUMBER_BUTTON_WIDTH ((SCREEN_WIDTH/NUMBER_OF_LAYOUT_COLUMNS)-BUTTON_COLUMN_OFFSET)
#define NUMBER_BUTTON_WIDTH_DENSE ((SCREEN_WIDTH/NUMBER_OF_LAYOUT_COLUMNS_DENSE)-BUTTON_COLUMN_OFFSET_DENSE)

#define NUMBER_BUTTON_HEIGHT ((SCREEN_HEIGHT/NUMBER_OF_LAYOUT_LINES)-BUTTON_LINE_OFFSET )

#define COLUMN(x) (((SCREEN_WIDTH * x) / NUMBER_OF_LAYOUT_COLUMNS) )
#define COLUMN_DENSE(x) (((SCREEN_WIDTH * x) / NUMBER_OF_LAYOUT_COLUMNS_DENSE) )

#define LINE(x)   (((SCREEN_HEIGHT *x) / NUMBER_OF_LAYOUT_LINES) )


#define BUTTON_COORDS(x,y)  COLUMN(x)+BUTTON_COLUMN_OFFSET/2,\
LINE(y)+BUTTON_LINE_OFFSET/2,\
COLUMN(x)+NUMBER_BUTTON_WIDTH,\
LINE(y)+NUMBER_BUTTON_HEIGHT

#define BUTTON_COORDS_DENSE(x,y)  COLUMN_DENSE(x)+BUTTON_COLUMN_OFFSET_DENSE/2,\
LINE(y)+BUTTON_LINE_OFFSET/2,\
COLUMN_DENSE(x)+NUMBER_BUTTON_WIDTH_DENSE,\
LINE(y)+NUMBER_BUTTON_HEIGHT

#define BUTTON_COORDS_SPAN(x1,y1,x2,y2)  COLUMN(x1)+BUTTON_COLUMN_OFFSET/2, \
LINE(y1)+BUTTON_LINE_OFFSET/2,\
COLUMN(x2)+NUMBER_BUTTON_WIDTH,\
LINE(y2)+NUMBER_BUTTON_HEIGHT


#define BUTTON_GO_BACK_COORDS BUTTON_COORDS(0,0)
#define BUTTON_SETTOZERO_COORDS BUTTON_COORDS(1,0)
#define BUTTON_ACTIVATE_COORDS BUTTON_COORDS_SPAN(2,0,3,0)

#define BUTTON_MOVE_LEFT_100_COORDS BUTTON_COORDS_DENSE(0,2)
#define BUTTON_MOVE_LEFT_10_COORDS BUTTON_COORDS_DENSE(1,2)
#define BUTTON_MOVE_LEFT_1_COORDS BUTTON_COORDS_DENSE(2,2)
#define BUTTON_MOVE_LEFT_P1_COORDS BUTTON_COORDS_DENSE(3,2)

#define BUTTON_MOVE_RIGHT_P1_COORDS BUTTON_COORDS_DENSE(4,2)
#define BUTTON_MOVE_RIGHT_1_COORDS BUTTON_COORDS_DENSE(5,2)
#define BUTTON_MOVE_RIGHT_10_COORDS BUTTON_COORDS_DENSE(6,2)
#define BUTTON_MOVE_RIGHT_100_COORDS BUTTON_COORDS_DENSE(7,2)

#define BUTTON_MOVE_LEFT_GROOVE_COORDS BUTTON_COORDS(0,3)
#define BUTTON_MOVE_RIGHT_GROOVE_COORDS BUTTON_COORDS(3,3)

#define BUTTON_SELECT_POS_0_COORDS BUTTON_COORDS(1,3)
#define BUTTON_SELECT_POS_MAX_COORDS BUTTON_COORDS(2,3)



#define GROOVEPICTURE_POSITION 2, LINE(4)+BUTTON_LINE_OFFSET, SCREEN_WIDTH-4, NUMBER_BUTTON_HEIGHT*3/4
#define POSITIONPICTURE_POSITION 2, LINE(4)+BUTTON_LINE_OFFSET+NUMBER_BUTTON_HEIGHT*3/4, SCREEN_WIDTH-4, NUMBER_BUTTON_HEIGHT*1/4



#define SPECIALBUTTONDEF(x,text) { x,false,true,x##_COORDS,BLUE,DARK_BLUE,WHITE, #text ,false }
#define SPECIALBUTTONDEFRED(x,text) { x,true,true,x##_COORDS,RED,DARK_RED,WHITE, #text ,false }

menuButtonType controlMenuButton[] = {
  SPECIALBUTTONDEF(BUTTON_GO_BACK,Back),
  SPECIALBUTTONDEF(BUTTON_SETTOZERO,Set 0),
  SPECIALBUTTONDEFRED(BUTTON_ACTIVATE,Activate),
  
  SPECIALBUTTONDEF(BUTTON_MOVE_LEFT_100,-100),
  SPECIALBUTTONDEF(BUTTON_MOVE_LEFT_10,-10),
  SPECIALBUTTONDEF(BUTTON_MOVE_LEFT_1,-1),
  SPECIALBUTTONDEF(BUTTON_MOVE_LEFT_P1,-0.1),
  SPECIALBUTTONDEF(BUTTON_MOVE_RIGHT_P1,+0.1),
  SPECIALBUTTONDEF(BUTTON_MOVE_RIGHT_1,+1),
  SPECIALBUTTONDEF(BUTTON_MOVE_RIGHT_10,+10),
  SPECIALBUTTONDEF(BUTTON_MOVE_RIGHT_100,+100),
  
  SPECIALBUTTONDEF(BUTTON_MOVE_LEFT_GROOVE,<----),
  SPECIALBUTTONDEF(BUTTON_MOVE_RIGHT_GROOVE,---->),
  SPECIALBUTTONDEF(BUTTON_SELECT_POS_0,Pos 0),
  SPECIALBUTTONDEF(BUTTON_SELECT_POS_MAX,Pos max),
  
  
};


ControlMenu::ControlMenu(UTFT *Disp, URTouch *Touch,TFT_Extension *TFTextention) : Menu(Disp,Touch,TFTextention)
{
  _screenButtons=controlMenuButton;
  _numScreenButtons=sizeof(controlMenuButton)/sizeof(menuButtonType);
  justActivated=false;
}

ControlMenu::~ControlMenu(void)
{

}

void ControlMenu::menuIsActivating(void)
{
  _Disp->setFont(SmallFont);
  _Disp->setColor(WHITE);
  _Disp->setBackColor(BLACK);

  this->fillActivationButton();
  
  programMenu.drawGrooves(GROOVEPICTURE_POSITION,controlSystem.nearestIndex);
  programMenu.drawPositions(POSITIONPICTURE_POSITION,controlSystem._currentPosition_f,controlSystem._currentTargetPosition_f,false);
  justActivated=true;
}


void ControlMenu::dispatch(uint8_t buttonNumber)
{
  switch (buttonNumber)
  {
    case BUTTON_GO_BACK:
    this->menuDeactivate();
    mainMenu.menuActivate();
    break;
    case BUTTON_SETTOZERO:
    controlSystem.setZero();
    break;
    case BUTTON_ACTIVATE:
    this->activate();
    break;
    case BUTTON_MOVE_LEFT_P1:
    controlSystem.go(-0.1f);
    break;
    case BUTTON_MOVE_LEFT_1:
    controlSystem.go(-1.0f);
    break;
    case BUTTON_MOVE_LEFT_10:
    controlSystem.go(-10.0f);
    break;
    case BUTTON_MOVE_LEFT_100:
    controlSystem.go(-100.0f);
    break;
    case  BUTTON_MOVE_RIGHT_P1:
    controlSystem.go(0.1f);
    break;
    case  BUTTON_MOVE_RIGHT_1:
    controlSystem.go(1.0f);
    break;
    case  BUTTON_MOVE_RIGHT_10:
    controlSystem.go(10.0f);
    break;
    case  BUTTON_MOVE_RIGHT_100:
    controlSystem.go(100.0f);
    break;
    case BUTTON_MOVE_LEFT_GROOVE:
    controlSystem.nextPositionLeft();
    programMenu.drawGrooves(GROOVEPICTURE_POSITION,controlSystem.nearestIndex);
    break;
    case  BUTTON_MOVE_RIGHT_GROOVE:
    controlSystem.nextPositionRight();
    programMenu.drawGrooves(GROOVEPICTURE_POSITION,controlSystem.nearestIndex);
    break;
    case BUTTON_SELECT_POS_0:
    controlSystem.selectPos0();
    programMenu.drawGrooves(GROOVEPICTURE_POSITION,controlSystem.nearestIndex);
    break;
    case BUTTON_SELECT_POS_MAX:
    controlSystem.selectPosMax();
    programMenu.drawGrooves(GROOVEPICTURE_POSITION,controlSystem.nearestIndex);
    break;
    
    
  }
}


void ControlMenu::fillActivationButton(void)
{
  bool active = controlSystem.getActivationState();
  
  menuButtonType *cb=&controlMenuButton[BUTTON_ACTIVATE];
  if (active)
  {
    _TFTextension->SetTouchButtonColors(cb->buttonNumber,RED,DARK_RED,true,true);
    _TFTextension->SetTouchButtonText(cb->buttonNumber,"  Stop  ",cb->size,cb->textColor);
  }
  else
  {
    _TFTextension->SetTouchButtonText(cb->buttonNumber,"Activate",cb->size,cb->textColor);
    _TFTextension->SetTouchButtonColors(cb->buttonNumber,LIGHT_GREEN,GREEN,true,true);
  }
  _TFTextension->ResetTouchButton(cb->buttonNumber);           // Trigger the repaint with the new text
}



void ControlMenu::activate(void)
{
  controlSystem.toggleActivation();
  this->fillActivationButton();
}

#define OUTPUT_POS1        COLUMN(0)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET
#define OUTPUT_POS2        COLUMN(1)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET
#define OUTPUT_POS3        COLUMN(2)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET
#define OUTPUT_POS4        COLUMN(3)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET
#define OUTPUT_POS5        COLUMN(0)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET+_Disp->getFontYsize()
#define OUTPUT_POS6        COLUMN(1)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET+_Disp->getFontYsize()
#define OUTPUT_POS7        COLUMN(2)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET+_Disp->getFontYsize()
#define OUTPUT_POS8        COLUMN(3)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET+_Disp->getFontYsize()
#define OUTPUT_POS9        COLUMN(2)+BUTTON_COLUMN_OFFSET,LINE(0)+BUTTON_LINE_OFFSET


#define OUTPUT_LOG_MESSAGE_I32(n,format,value)\
static int32_t old##n = 0x7FFFFFFF;           \
if ((old##n!=value) || justActivated)         \
{                                             \
  old##n=value;                               \
  snprintf(valueString,40,format, old##n);    \
  _Disp->print((char*)"          ",OUTPUT_POS##n,0);	\
  _Disp->print(valueString,OUTPUT_POS##n,0);  \
}

#define OUTPUT_LOG_MESSAGE_F(n,format,value) \
static float old##n = -9999999;              \
if ((old##n!=value) || justActivated)        \
{                                            \
  old##n=value;                              \
  snprintf(valueString,40,format, old##n);   \
  _Disp->print((char*)"          ",OUTPUT_POS##n,0);\
  _Disp->print(valueString,OUTPUT_POS##n,0); \
}


void ControlMenu::run(void)
{
  if (_menuState == MENU_WAITING)
  {
    _Disp->setColor(WHITE);
    _Disp->setBackColor(BLACK);
    _Disp->setFont(SmallFont);

    OUTPUT_LOG_MESSAGE_F  (1," Target: %4.2f",controlSystem._currentTargetPosition_f)
    OUTPUT_LOG_MESSAGE_F  (5,"Current: %4.2f",controlSystem._currentPosition_f)
    OUTPUT_LOG_MESSAGE_F  (3,"Dist.: %4.2f",controlSystem._currentDistance/settingMenu.getStepsPerMilimeter())
    OUTPUT_LOG_MESSAGE_I32(7,"Speed: %5ld",controlSystem._currentFrequency)
    justActivated=false;
    
    programMenu.drawPositions(POSITIONPICTURE_POSITION,controlSystem._currentPosition_f,controlSystem._currentTargetPosition_f,true);
  }
}
