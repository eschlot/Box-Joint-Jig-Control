/*
* LinearDistributionMenu.cpp
*
* Created: 19.05.2015 23:45:55
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


#include "LinearDistributionMenu.h"
#include "PositionControl.h"
#include "NVM.h"

enum
{
  BUTTON_GO_BACK,
  BUTTON_INVERT,
  BUTTON_ENTER_OVERALL_LEN,
  BUTTON_ENTER_GROOVE_WIDTH,
  BUTTON_ENTER_GROOVE_NUMBER,
  BUTTON_ON_START,
  BUTTON_ON_END,
};


#define NUMBER_OF_LAYOUT_LINES  7
#define NUMBER_OF_LAYOUT_COLUMNS 3

#define BUTTON_COLUMN_OFFSET 10
#define BUTTON_LINE_OFFSET    5

#define NUMBER_BUTTON_WIDTH ((SCREEN_WIDTH/NUMBER_OF_LAYOUT_COLUMNS)-BUTTON_COLUMN_OFFSET)
#define NUMBER_BUTTON_HEIGHT ((SCREEN_HEIGHT/NUMBER_OF_LAYOUT_LINES)-BUTTON_LINE_OFFSET )

#define COLUMN(x) (((SCREEN_WIDTH * x) / NUMBER_OF_LAYOUT_COLUMNS) )
#define LINE(x)   (((SCREEN_HEIGHT *x) / NUMBER_OF_LAYOUT_LINES) )


#define BUTTON_COORDS(x,y)  COLUMN(x)+BUTTON_COLUMN_OFFSET/2,\
LINE(y)+BUTTON_LINE_OFFSET/2,\
COLUMN(x)+NUMBER_BUTTON_WIDTH,\
LINE(y)+NUMBER_BUTTON_HEIGHT

#define BUTTON_COORDS_SPAN(x1,y1,x2,y2)  COLUMN(x1)+BUTTON_COLUMN_OFFSET/2, \
LINE(y1)+BUTTON_LINE_OFFSET/2,\
COLUMN(x2)+NUMBER_BUTTON_WIDTH,\
LINE(y2)+NUMBER_BUTTON_HEIGHT


#define BUTTON_GO_BACK_COORDS BUTTON_COORDS_SPAN(0,0,1,0)
#define BUTTON_INVERT_COORDS BUTTON_COORDS(2,0)
#define BUTTON_ENTER_OVERALL_LEN_COORDS BUTTON_COORDS_SPAN(0,1,1,1)
#define BUTTON_ENTER_GROOVE_WIDTH_COORDS BUTTON_COORDS_SPAN(0,2,1,2)
#define BUTTON_ENTER_GROOVE_NUMBER_COORDS BUTTON_COORDS_SPAN(0,3,1,3)
#define BUTTON_ON_START_COORDS BUTTON_COORDS_SPAN(0,4,1,4)
#define BUTTON_ON_END_COORDS BUTTON_COORDS_SPAN(0,5,1,5)

#define OVERALL_LEN_COORDS   COLUMN(2)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET
#define GROOVE_WIDTH_COORDS COLUMN(2)+BUTTON_COLUMN_OFFSET,LINE(2)+BUTTON_LINE_OFFSET
#define GROOVE_NUMBER_COORDS COLUMN(2)+BUTTON_COLUMN_OFFSET,LINE(3)+BUTTON_LINE_OFFSET
#define START_COORDS COLUMN(2)+BUTTON_COLUMN_OFFSET,LINE(4)+BUTTON_LINE_OFFSET
#define END_COORDS COLUMN(2)+BUTTON_COLUMN_OFFSET,LINE(5)+BUTTON_LINE_OFFSET

#define GROOVEPICTURE_POSITION 0, LINE(6)+BUTTON_LINE_OFFSET, SCREEN_WIDTH, NUMBER_BUTTON_HEIGHT



#define SPECIALBUTTONDEF(x,text) { BUTTON_##x,false,true,BUTTON_##x##_COORDS,BLUE,DARK_BLUE,WHITE, #text ,false }

menuButtonType linearDistributionButton[] = {
  SPECIALBUTTONDEF(GO_BACK,Back),
  SPECIALBUTTONDEF(INVERT,Invert),
  SPECIALBUTTONDEF(ENTER_OVERALL_LEN,Length),
  SPECIALBUTTONDEF(ENTER_GROOVE_WIDTH,Groove Width),
  SPECIALBUTTONDEF(ENTER_GROOVE_NUMBER,Number of Grooves),
  SPECIALBUTTONDEF(ON_START,Starts with Groove),
  SPECIALBUTTONDEF(ON_END,Ends with Groove),

};

char const *yes="Yes ";
char const *no="No  ";
char const* overallLengthString="Overall Length";

LinearDistributionMenu::LinearDistributionMenu(UTFT *Disp, URTouch *Touch,TFT_Extension *TFTextention) : Menu(Disp,Touch,TFTextention)
{
  _screenButtons=linearDistributionButton;
  _numScreenButtons=sizeof(linearDistributionButton)/sizeof(menuButtonType);
  
  // Read the last setting from Flash
  overallLength=nvm.LinearDistributionMenu_overallLength();
  grooveWidth=nvm.LinearDistributionMenu_grooveWidth();
  numberOfGrooves=nvm.LinearDistributionMenu_numberOfGrooves();
  startsOnGroove=nvm.LinearDistributionMenu_startsOnGroove();
  endsOnGroove=nvm.LinearDistributionMenu_endsOnGroove();
  
}

LinearDistributionMenu::~LinearDistributionMenu()
{

}

#define formatValue(value) snprintf(tempStr,40,"%.0d%.4g        ", (int)value/10, value-((int)value-(int)value%10));
#define formatIntValue(value) snprintf(tempStr,40,"%3d        ", value);

void LinearDistributionMenu::menuIsActivating(void)
{
  _Disp->setFont(SmallFont);
  _Disp->setColor(WHITE);
  _Disp->setBackColor(BLACK);
  
  char tempStr[40];
  formatValue(overallLength);
  _Disp->print(tempStr,OVERALL_LEN_COORDS,0);
  
  formatValue(grooveWidth);
  _Disp->print(tempStr,GROOVE_WIDTH_COORDS,0);
  
  formatIntValue(numberOfGrooves);
  _Disp->print(tempStr,GROOVE_NUMBER_COORDS,0);
  
  if (startsOnGroove)
  {
    _Disp->print(yes,START_COORDS,0);
  }
  else
  {
    _Disp->print(no,START_COORDS,0);
  }
  if (endsOnGroove)
  {
    _Disp->print(yes,END_COORDS,0);
  }
  else
  {
    _Disp->print(no,END_COORDS,0);
  }
  
  if (this->calculateGrooves())
  {
    programMenu.drawGrooves(GROOVEPICTURE_POSITION);
  }
}


void LinearDistributionMenu::printErrorMessage(char const* message)
{
  _Disp->setColor(RED);
  _Disp->fillRect(0,LINE(6)+BUTTON_LINE_OFFSET, SCREEN_WIDTH-1, NUMBER_BUTTON_HEIGHT-1);
  _Disp->setColor(WHITE);
  _Disp->print(message,0, LINE(6)+BUTTON_LINE_OFFSET,0);
}


bool LinearDistributionMenu::calculateGrooves(void)
{
  programMenu.program->clear();

  float bladeWidth =    nvm.SettingMenu_bladeWidth();
  // ---------------------------------------------
  if (grooveWidth<bladeWidth)
  {
    this->printErrorMessage("The Grooves are smaller than the blade used.");
    return false;
  }
  // ---------------------------------------------
  float overallSpaceLength= overallLength-numberOfGrooves*grooveWidth;
  if (overallSpaceLength<0)
  {
    this->printErrorMessage("The Grooves are longer than the overall length.");
    return false;
  }
  // ---------------------------------------------
  int numberOfSpaces = numberOfGrooves-1;
  if (!startsOnGroove)
  {
    numberOfSpaces++;
  }
  if (!endsOnGroove)
  {
    numberOfSpaces++;
  }
  // ---------------------------------------------
  float spaceLength = (overallSpaceLength/numberOfSpaces);
  // ---------------------------------------------
  float grooveStartPosition;
  if (startsOnGroove)
  {
    grooveStartPosition=0.0f;
  }
  else
  {
    grooveStartPosition=spaceLength;
  }
  float grooveEndposition=grooveStartPosition+grooveWidth;
  // ---------------------------------------------
  int numberOfGroovesDefined=0;
  while (numberOfGroovesDefined<numberOfGrooves)
  {
    float start=grooveStartPosition;
    if (start+bladeWidth>grooveEndposition)
    {
      start=grooveEndposition-bladeWidth;
      numberOfGroovesDefined++;
      grooveStartPosition=grooveEndposition+spaceLength;
      grooveEndposition=grooveStartPosition+grooveWidth;
    }
    else
    {
      grooveStartPosition+=bladeWidth;
    }
    programMenu.program->add(start);
  }
  programMenu.setOverallLength(overallLength);
  return true;
}


void LinearDistributionMenu::dispatch(uint8_t buttonNumber)
{
  switch (buttonNumber)
  {
    case BUTTON_GO_BACK:
    {
      nvm.LinearDistributionMenu_endsOnGroove(endsOnGroove);
      nvm.LinearDistributionMenu_startsOnGroove(startsOnGroove);
      nvm.LinearDistributionMenu_numberOfGrooves(numberOfGrooves);
      nvm.LinearDistributionMenu_overallLength(overallLength);
      nvm.LinearDistributionMenu_grooveWidth(grooveWidth);
      this->calculateGrooves();
      this->menuDeactivate();
      programMenu.menuActivate();
      break;
    }
    case BUTTON_INVERT:
    {
      float temp_space= overallLength-numberOfGrooves*grooveWidth;
      
      numberOfGrooves=numberOfGrooves+1;
      if (startsOnGroove)
      {
        numberOfGrooves--;
      }
      if (endsOnGroove)
      {
        numberOfGrooves--;
      }
      endsOnGroove=!endsOnGroove;
      startsOnGroove=!startsOnGroove;
      grooveWidth=temp_space/numberOfGrooves;
      
      _Disp->setFont(SmallFont);
      _Disp->setColor(WHITE);
      _Disp->setBackColor(BLACK);
      
      char tempStr[40];
      
      formatValue(grooveWidth);
//       _Disp->setColor(BLACK);
//       _Disp->drawRect(BUTTON_COORDS(1,2));
//       _Disp->setColor(WHITE);
      _Disp->print(tempStr,GROOVE_WIDTH_COORDS,0);
      
      formatIntValue(numberOfGrooves);
//       _Disp->setColor(BLACK);
//       _Disp->drawRect(BUTTON_COORDS(1,3));
//       _Disp->setColor(WHITE);      
      _Disp->print(tempStr,GROOVE_NUMBER_COORDS,0);
      
//       _Disp->setColor(BLACK);
//       _Disp->drawRect(BUTTON_COORDS(1,4));
//       _Disp->setColor(WHITE);
      if (startsOnGroove)
      {
        _Disp->print(yes,START_COORDS,0);
      }
      else
      {
        _Disp->print(no,START_COORDS,0);
      }
//       _Disp->setColor(BLACK);
//       _Disp->drawRect(BUTTON_COORDS(1,4));
//       _Disp->setColor(WHITE);
      if (endsOnGroove)
      {
        _Disp->print(yes,END_COORDS,0);
      }
      else
      {
        _Disp->print(no,END_COORDS,0);
      }
      break;
    }
    case BUTTON_ENTER_OVERALL_LEN:
    {
      floatNumberEntryMenu.setReturnMenu(this);
      floatNumberEntryMenu.setTextMessage(overallLengthString);
      floatNumberEntryMenu.setValuePointerOnEnterPressed(&overallLength);
      floatNumberEntryMenu.setValue(overallLength);
      this->menuDeactivate();
      floatNumberEntryMenu.menuActivate();
      break;
    }
    case BUTTON_ENTER_GROOVE_WIDTH:
    {
      floatNumberEntryMenu.setReturnMenu(this);
      floatNumberEntryMenu.setTextMessage("Groove Width");
      floatNumberEntryMenu.setValuePointerOnEnterPressed(&grooveWidth);
      floatNumberEntryMenu.setValue(grooveWidth);
      this->menuDeactivate();
      floatNumberEntryMenu.menuActivate();
      break;
    }
    case BUTTON_ENTER_GROOVE_NUMBER:
    {
      integerNumberEntryMenu.setReturnMenu(this);
      integerNumberEntryMenu.setTextMessage("Number of Grooves");
      integerNumberEntryMenu.setValuePointerOnEnterPressed(&numberOfGrooves);
      integerNumberEntryMenu.setValue(numberOfGrooves);
      this->menuDeactivate();
      integerNumberEntryMenu.menuActivate();
      break;
    }
    case BUTTON_ON_START:
    {
      _Disp->setBackColor(BLACK);
      if (startsOnGroove)
      {
        startsOnGroove=false;
        _Disp->print(no,START_COORDS,0);
      }
      else
      {
        startsOnGroove=true;
        _Disp->print(yes,START_COORDS,0);
      }
      
      break;
    }
    case BUTTON_ON_END:
    {
      _Disp->setBackColor(BLACK);
      if (endsOnGroove)
      {
        endsOnGroove=false;
        _Disp->print(no,END_COORDS,0);
      }
      else
      {
        endsOnGroove=true;
        _Disp->print(yes,END_COORDS,0);
      }
      break;
    }
    
  }
  
  if (this->calculateGrooves())
  {
    programMenu.drawGrooves(GROOVEPICTURE_POSITION);
  }
  
}



