/* 
 * IntegerNumberEntryMenu.cpp
 *
 * Created: 24.05.2015 21:49:54
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

#include "IntegerNumberEntryMenu.h"
#include "PositionControl.h"

enum
{
  BUTTON_GO_BACK, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8, BUTTON_9, BUTTON_ENTER, BUTTON_CLEAR
};

#define NUMBER_OF_LAYOUT_LINES  7
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

#define TEXT_MESSGAE_OUTPUT_POS        COLUMN(0)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET
#define ERROR_OUTPUT_POS  COLUMN(2)+BUTTON_COLUMN_OFFSET,LINE(2)+BUTTON_LINE_OFFSET
#define OUTPUT_POS        COLUMN(0)+BUTTON_COLUMN_OFFSET,LINE(2)+BUTTON_LINE_OFFSET

#define BUTTON_0_COORDS BUTTON_COORDS(1,6)
#define BUTTON_1_COORDS BUTTON_COORDS(0,5)
#define BUTTON_2_COORDS BUTTON_COORDS(1,5)
#define BUTTON_3_COORDS BUTTON_COORDS(2,5)
#define BUTTON_4_COORDS BUTTON_COORDS(0,4)
#define BUTTON_5_COORDS BUTTON_COORDS(1,4)
#define BUTTON_6_COORDS BUTTON_COORDS(2,4)
#define BUTTON_7_COORDS BUTTON_COORDS(0,3)
#define BUTTON_8_COORDS BUTTON_COORDS(1,3)
#define BUTTON_9_COORDS BUTTON_COORDS(2,3)

#define BUTTON_ENTER_COORDS BUTTON_COORDS(2,0)
#define BUTTON_GO_BACK_COORDS BUTTON_COORDS(0,0)
#define BUTTON_CLEAR_COORDS BUTTON_COORDS(1,0)

#define NUMBERBUTTONDEF(x) { BUTTON_##x,true,true,BUTTON_##x##_COORDS,BLUE,DARK_BLUE,WHITE, #x ,false }
#define SPECIALBUTTONDEF(x,text) { BUTTON_##x,true,true,BUTTON_##x##_COORDS,BLUE,DARK_BLUE,WHITE, #text ,false }

menuButtonType intergerNumberEntryMenuButton[] = {
SPECIALBUTTONDEF(GO_BACK,Back),
NUMBERBUTTONDEF(0),
NUMBERBUTTONDEF(1),
NUMBERBUTTONDEF(2),
NUMBERBUTTONDEF(3),
NUMBERBUTTONDEF(4),
NUMBERBUTTONDEF(5),
NUMBERBUTTONDEF(6),
NUMBERBUTTONDEF(7),
NUMBERBUTTONDEF(8),
NUMBERBUTTONDEF(9),
SPECIALBUTTONDEF(ENTER,Enter),
SPECIALBUTTONDEF(CLEAR,<--) };

IntegerNumberEntryMenu::IntegerNumberEntryMenu(UTFT *Disp, URTouch *Touch, TFT_Extension *TFTextention)
    : Menu(Disp, Touch, TFTextention)
{
  _screenButtons = intergerNumberEntryMenuButton;
  _numScreenButtons = sizeof(intergerNumberEntryMenuButton) / sizeof(menuButtonType);

  textMessagePtr = (char*) "No Message defined";
  valueToWriteHereOnEnterPressed = (nullptr_t) NULL;
  value = 0;
  returnMenuPtr = NULL;
}

IntegerNumberEntryMenu::~IntegerNumberEntryMenu(void)
{

}

void IntegerNumberEntryMenu::setTextMessage(char const* text)
{
  this->textMessagePtr = text;
}

int IntegerNumberEntryMenu::getValue()
{
  return value;
}

void IntegerNumberEntryMenu::setValue(int v)
{
  this->value = v;
}

void IntegerNumberEntryMenu::setReturnMenu(Menu* m)
{
  returnMenuPtr = m;
}

void IntegerNumberEntryMenu::setValuePointerOnEnterPressed(int* retValPtr)
{
  valueToWriteHereOnEnterPressed = retValPtr;
}

void IntegerNumberEntryMenu::menuIsActivating(void)
{
  _Disp->print((char*) "             ", ERROR_OUTPUT_POS, 0);
  if (valueToWriteHereOnEnterPressed == NULL || returnMenuPtr == NULL || textMessagePtr == NULL)
  {
    _Disp->print((char*) "Internal error: Uninitialized pointers",
    ERROR_OUTPUT_POS, 0);
  }

  snprintf(valueString, 40, "%d", value);
  _Disp->setFont(BigFont);
  _Disp->setColor(WHITE);
  _Disp->setBackColor(BLACK);
  _Disp->print(valueString, OUTPUT_POS, 0);
  _Disp->print(textMessagePtr, TEXT_MESSGAE_OUTPUT_POS, 0);
}

#define NUMBERBUTTONHANDLER(x) case BUTTON_##x : { \
  size_t strlength = strlen(valueString);\
  char appendStr[2]=#x;\
  strcpy(&valueString[strlength],appendStr);\
  break;\
}

void IntegerNumberEntryMenu::dispatch(uint8_t buttonNumber)
{
  switch (buttonNumber)
  {
    case BUTTON_GO_BACK:
      this->menuDeactivate();
      returnMenuPtr->menuActivate();
      break;
    NUMBERBUTTONHANDLER(0)
      ;
    NUMBERBUTTONHANDLER(1)
      ;
    NUMBERBUTTONHANDLER(2)
      ;
    NUMBERBUTTONHANDLER(3)
      ;
    NUMBERBUTTONHANDLER(4)
      ;
    NUMBERBUTTONHANDLER(5)
      ;
    NUMBERBUTTONHANDLER(6)
      ;
    NUMBERBUTTONHANDLER(7)
      ;
    NUMBERBUTTONHANDLER(8)
      ;
    NUMBERBUTTONHANDLER(9)
      ;
    case BUTTON_CLEAR:
    {
      size_t strlength = strlen(valueString);
      if (strlength > 0)
        valueString[strlength - 1] = '\0';
      break;
    }
  }
  {
    int testValue;
    _Disp->setBackColor(BLACK);
    _Disp->setColor(WHITE);
    char rest[40];

    int numMatched = sscanf(valueString, "%d%s", &testValue, rest);
    if ((numMatched <= 0) || (numMatched >= 2))
    { // No valid number
      _Disp->setColor(RED);
      _Disp->print((char*) "Invalid", ERROR_OUTPUT_POS, 0);
    }
    else
    {
      // valid number found
      _Disp->print((char*) "         ", ERROR_OUTPUT_POS, 0);

      if (buttonNumber == BUTTON_ENTER)
      {
        value = testValue;
        *valueToWriteHereOnEnterPressed = testValue;
        this->menuDeactivate();
        returnMenuPtr->menuActivate();
      }
    }

    char blank[2] = " ";
    char result[41];
    strcpy(result, valueString);
    size_t endPos = strlen(result);

    strcpy(&result[endPos], blank);
    _Disp->print(result, OUTPUT_POS, 0);
  }
}

