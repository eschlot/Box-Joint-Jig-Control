/*
 * LicenseMenu.cpp
 *
 * Created: 29.12.2016 23:00:39
 Copyright (c) 2016 Eckart Schlottmann
 Author: Eckart Schlottmann


This software is distributed under the terms of the
Mozilla Public License Version 2.0 with extensions for safety
This licence is distributed alongside with this software.


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
#include "LicenseMenu.h"
#include "PositionControl.h"

enum
{
  BUTTON_BACK, BUTTON_PAGEDOWN, BUTTON_PAGEUP
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

#define BUTTON_BACK_COORDS BUTTON_COORDS(0,0)
#define BUTTON_PAGEDOWN_COORDS BUTTON_COORDS(1,0)
#define BUTTON_PAGEUP_COORDS BUTTON_COORDS(2,0)

#define TEXT_MESSGAE_OUTPUT_POS_x        COLUMN(0)+BUTTON_COLUMN_OFFSET
#define TEXT_MESSAGE_OUTPUT_POS_Y(line)  LINE(1)+BUTTON_LINE_OFFSET+line*15

#define SPECIALBUTTONDEF(x,text) { x,false,true,x##_COORDS,BLUE,DARK_BLUE,WHITE, #text ,false }

menuButtonType licenseMenuButton[] = {
SPECIALBUTTONDEF(BUTTON_BACK,Back),
SPECIALBUTTONDEF(BUTTON_PAGEUP,Up),
SPECIALBUTTONDEF(BUTTON_PAGEDOWN,Down) };

#define LINEBREAKCOLUMN 35
#define NUMBEROFLINESONSCREEN 11
const char *licenseText =
    "Position Control Version 1.0\n(c) 2016 Eckart Schlottmann\neckart.schlottmann@gmx.de\nThis software is build on many open source projects. This application software itself is also free software and licensed under the \"Mozilla Public License Version 2.0 with extensions for safety\". it is distributed alongside this software.\n\nThe license details of the used libraries is as follows:\nUTFT and URTouch from Henning Karlsen under Creative Commons (CC BY-NC-SA 3.0))\nTFT_Extension from Andrew Mascolo Jr under MIT License\nDueTimer and LinkedList from Ivan Seidel under MIT License\nDueFlashStorage from Sebastian Nilsson under MIT License\nEFC Flash driver from Atmel Corporation under ASF License\nMany thanks to the authors.\n\nDisclaimer of Warranty\nCovered Software is provided under this License on an \"as is\" basis, without warranty of any kind, either expressed, implied, or statutory, including, without limitation, warranties that the Covered Software is free of defects, merchantable, fit for a particular purpose or non-infringing. The entire risk as to the quality and performance of the Covered Software is with You. Should any Covered Software prove defective in any respect, You (not any Contributor) assume the cost of any necessary servicing, repair, or correction. This disclaimer of warranty constitutes an essential part of this License. No use of any Covered Software is authorized under this License except under this disclaimer.\n\nLimitation of Liability\nUnder no circumstances and under no legal theory, whether tort (including negligence), contract, or otherwise, shall any Contributor, or anyone who distributes Covered Software as permitted above, be liable to You for any direct, indirect, special, incidental, or consequential damages of any character including, without limitation, damages for lost profits, loss of goodwill, work stoppage, computer failure or malfunction, or any and all other commercial damages or losses, even if such party shall have been informed of the possibility of such damages. This limitation of liability shall not apply to liability for death or personal injury resulting from such party's negligence to the extent applicable law prohibits such limitation. Some jurisdictions do not allow the exclusion or limitation of incidental or consequential damages, so this exclusion and limitation may not apply to You. Under all circumstances the software shall only be operated under the conditions described in the SAFETY documentation. The software is only allowed to be operated in a surrounding where the safety of the overall system is ensured by the design and the Construction of the jig to which the electronic hardware including the stepper motor and the software are mounted. This software is developed to be used in a jig for a table saw only where the jig itself is designed in such a way that it cannot harm a user under any circumstance. This means that the design, the construction and the usage of the table saw jig has to be done is such a way that even in case the stepper motor of the jig is operated in any direction in a middle of a cut neither the jig itself or a workpiece in the jig can harm a user. These extra safety regulations need to be taken over to any derived work out of this work. \n";

LicenseMenu::LicenseMenu(UTFT *Disp, URTouch *Touch, TFT_Extension *TFTextention)
    : Menu(Disp, Touch, TFTextention)
{
  _screenButtons = licenseMenuButton;
  _numScreenButtons = sizeof(licenseMenuButton) / sizeof(menuButtonType);
  pageNumber = 0;
  {
    lineBreakList = new LinkedObjectList<LicenseLineInfo*>();

    int pos = 0;
    int start = 0;
    int lineLength = 0;
    int blankPos = 0;
    int linelengthTillBlankPos = 0;
    int textLength = strlen(licenseText);

    while (pos < textLength)
    {
      bool newLine = false;
      if (licenseText[pos] == ' ')
      {
        blankPos = pos;
        linelengthTillBlankPos = lineLength;
      }
      if (licenseText[pos] == '\n')
      {
        LicenseLineInfo* lineInfo = new LicenseLineInfo(start, lineLength);
        lineBreakList->add(lineInfo);
        start = pos + 1;
        lineLength = 0;
        linelengthTillBlankPos = 0;
        newLine = true;

      }
      if (lineLength > LINEBREAKCOLUMN)
      {
        if (linelengthTillBlankPos > 0)
        {
          LicenseLineInfo* lineInfo = new LicenseLineInfo(start, linelengthTillBlankPos);
          lineBreakList->add(lineInfo);
          pos = blankPos + 1;
          blankPos = 0;
          linelengthTillBlankPos = 0;
          start = pos;
          lineLength = 1;
          newLine = true;
        }
        else
        {
          LicenseLineInfo* lineInfo = new LicenseLineInfo(start, lineLength);
          lineBreakList->add(lineInfo);
          start = pos;
          lineLength = 1;
          newLine = true;
        }
      }
      pos++;
      if (!newLine)
        lineLength++;
    }
  }
  {
    linePosList = new LinkedList<int>();
    for (int i = 0; i < NUMBEROFLINESONSCREEN; i++)
    {
      linePosList->add(TEXT_MESSAGE_OUTPUT_POS_Y(i));
    }
  }
}

LicenseMenu::~LicenseMenu(void)
{

}

void LicenseMenu::menuIsActivating(void)
{
  _Disp->setFont(SmallFont);
  _Disp->setColor(WHITE);
  _Disp->setBackColor(BLACK);
  pageNumber = 0;
  this->drawtext();
}

void LicenseMenu::dispatch(uint8_t buttonNumber)
{
  switch (buttonNumber)
  {
    case BUTTON_BACK:
      this->mainMenuOperation();
      break;
    case BUTTON_PAGEDOWN:
    {
      int outputIndexStart = pageNumber * linePosList->size();
      if (outputIndexStart < lineBreakList->size())
      {
        pageNumber++;
        this->drawtext();
      }
      break;
    }
    case BUTTON_PAGEUP:
      if (pageNumber > 0)
      {
        pageNumber--;
        this->drawtext();
      }
      break;
  }
}

void LicenseMenu::mainMenuOperation()
{
  this->menuDeactivate();
  mainMenu.menuActivate();
}

void LicenseMenu::drawtext(void)
{
  _Disp->setFont(SmallFont);
  _Disp->setColor(WHITE);
  _Disp->setBackColor(BLACK);

  char buffer[LINEBREAKCOLUMN + 4];
  for (int i = 0; i < LINEBREAKCOLUMN+2; i++)
  {
    buffer[i] = ' ';
  }
  buffer[LINEBREAKCOLUMN + 3] = '\0';

  for (int i = 0; i < linePosList->size(); i++)
  {
    _Disp->print(buffer, TEXT_MESSGAE_OUTPUT_POS_x, linePosList->get(i), 0);
  }
  int outputIndexStart = pageNumber * linePosList->size();
  for (int i = 0; i < linePosList->size(); i++)
  {
    if (outputIndexStart + i < lineBreakList->size())
    {
      LicenseLineInfo* lineInfo = lineBreakList->get(outputIndexStart + i);
      for (int j = 0; j < lineInfo->length; j++)
      {
        buffer[j] = licenseText[lineInfo->start + j];
      }
      buffer[lineInfo->length] = '\0';
      _Disp->print(buffer, TEXT_MESSGAE_OUTPUT_POS_x, linePosList->get(i), 0);
    }
  }
}
