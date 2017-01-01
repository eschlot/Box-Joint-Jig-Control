/*
* IndividualDistributionMenu.cpp
*
* Created: 19.05.2015 23:45:55

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


#include "IndividualDistributionMenu.h"
#include "PositionControl.h"
#include "NVM.h"

enum
{
  BUTTON_GO_BACK,
  BUTTON_INVERT,
  BUTTON_ENTER_OVERALL_LEN,
  BUTTON_ADD,
  BUTTON_REMOVE,
  BUTTON_EDIT_START,
  BUTTON_EDIT_WIDTH,
  BUTTON_UP,
  BUTTON_DOWN
};


#define NUMBER_OF_LAYOUT_LINES  8
#define NUMBER_OF_LAYOUT_COLUMNS 4

#define NUMBER_OF_LIST_LINES (NUMBER_OF_LAYOUT_LINES-2)


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


#define BUTTON_GO_BACK_COORDS BUTTON_COORDS(0,0)
#define BUTTON_INVERT_COORDS BUTTON_COORDS(1,0)
#define BUTTON_ENTER_OVERALL_LEN_COORDS BUTTON_COORDS_SPAN(2,0,3,0)
#define BUTTON_ADD_COORDS BUTTON_COORDS(2,1)
#define BUTTON_REMOVE_COORDS BUTTON_COORDS(3,1)
#define BUTTON_EDIT_START_COORDS BUTTON_COORDS_SPAN(2,2,3,2)
#define BUTTON_EDIT_WIDTH_COORDS BUTTON_COORDS_SPAN(2,3,3,3)
#define BUTTON_UP_COORDS BUTTON_COORDS(2,6)
#define BUTTON_DOWN_COORDS BUTTON_COORDS(3,6)

#define OVERALL_LEN_COORDS   COLUMN(1)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET
#define GROOVEPICTURE_POSITION 0, LINE(7)+BUTTON_LINE_OFFSET, SCREEN_WIDTH, NUMBER_BUTTON_HEIGHT


#define SPECIALBUTTONDEF(x,text) { BUTTON_##x,false,true,BUTTON_##x##_COORDS,BLUE,DARK_BLUE,WHITE, #text ,false }


menuButtonType individualDistributionButton[] = {
  SPECIALBUTTONDEF(GO_BACK,Back),
  SPECIALBUTTONDEF(INVERT,Invert),
  SPECIALBUTTONDEF(ENTER_OVERALL_LEN,Long long text),
  SPECIALBUTTONDEF(ADD,add),
  SPECIALBUTTONDEF(REMOVE,remove),
  SPECIALBUTTONDEF(EDIT_START,edit start),
  SPECIALBUTTONDEF(EDIT_WIDTH,edit width),
  SPECIALBUTTONDEF(UP,up),
  SPECIALBUTTONDEF(DOWN,down),

};

char const* editStartString="Start of groove";
char const* editWidthString="Width of groove";


IndividualDistributionMenu::IndividualDistributionMenu(UTFT *Disp, URTouch *Touch,TFT_Extension *TFTextention) : Menu(Disp,Touch,TFTextention)
{
  _screenButtons=individualDistributionButton;
  _numScreenButtons=sizeof(individualDistributionButton)/sizeof(menuButtonType);
  
  // Read the last setting from Flash
  overallLength=nvm.IndividualDistributionMenu_overallLength();
  individualDistribution=nvm.IndividualDistributionMenu_readGrooves();

  visualStartIndex=0;
  selectedLine=0;
  lastSelectedGrooveDefinition=NULL;
}

IndividualDistributionMenu::~IndividualDistributionMenu(void)
{
  delete(individualDistribution);
}

#define formatValue(value) snprintf(tempStr,40,"%4.2f  ",value);
#define formatValueForHighlighting(value) snprintf(tempStr,40,"%4.2f",value);
#define formatIntValue(value) snprintf(tempStr,40,"%3d        ", value);


void IndividualDistributionMenu::menuIsActivating(void)
{
  _Disp->setFont(SmallFont);
  _Disp->setColor(WHITE);
  _Disp->setBackColor(BLACK);
  
  fillOverallLengthButton();
  individualDistribution->sort();
  
  if (lastSelectedGrooveDefinition)
  {
    selectedLine = individualDistribution->indexOf(lastSelectedGrooveDefinition);
    visualStartIndex = selectedLine-2;
    if (visualStartIndex<0)
    {
      visualStartIndex=0;
    }
    lastSelectedGrooveDefinition=NULL;
  }

  printGrooves();
  if (calculateGrooves())  
  {
    programMenu.drawGrooves(GROOVEPICTURE_POSITION);                         
  }
  
}

char lengthString[40];

void IndividualDistributionMenu::fillOverallLengthButton(void)
{
  menuButtonType *cb=&individualDistributionButton[BUTTON_ENTER_OVERALL_LEN];
  snprintf(lengthString,40,"Len: %.0d%.4g", (int)overallLength/10, overallLength-((int)overallLength-(int)overallLength%10));
  _TFTextension->SetTouchButtonText(cb->buttonNumber,lengthString,cb->size,cb->textColor);
  _TFTextension->ResetTouchButton(cb->buttonNumber);
}



void IndividualDistributionMenu::printErrorMessage(char const* message)
{
  _Disp->setColor(RED);
  _Disp->print(message,0, LINE(7)+BUTTON_LINE_OFFSET,0);
  _Disp->setColor(WHITE);
}


#define GROOVESTART_COORDS(l)   COLUMN(0)+BUTTON_COLUMN_OFFSET,LINE(l)+BUTTON_LINE_OFFSET
#define GROOVEWIDTH_COORDS(l)   COLUMN(1)+BUTTON_COLUMN_OFFSET,LINE(l)+BUTTON_LINE_OFFSET


void IndividualDistributionMenu::printGroove(int index,int inLine,boolean selected)
{
  if (selected)
  {
    _Disp->setBackColor(RED);
    GrooveDefinition *gd=individualDistribution->get(index);
    char tempStr[40];
    formatValueForHighlighting(gd->startPosition);
    _Disp->print(tempStr,GROOVESTART_COORDS(inLine),0);
    
    formatValueForHighlighting(gd->width);
    _Disp->print(tempStr,GROOVEWIDTH_COORDS(inLine),0);
    _Disp->setBackColor(BLACK);    
  }
  else
  {
    GrooveDefinition *gd=individualDistribution->get(index);
    char tempStr[40];
    formatValue(gd->startPosition);
    _Disp->print(tempStr,GROOVESTART_COORDS(inLine),0);
  
    formatValue(gd->width);
    _Disp->print(tempStr,GROOVEWIDTH_COORDS(inLine),0);
  }
}

void IndividualDistributionMenu::printGrooves()
{
  _Disp->setColor(WHITE);
  _Disp->setBackColor(BLACK);
  
  int i=visualStartIndex, j=1;
  for ( ; i<individualDistribution->size() && i< visualStartIndex+NUMBER_OF_LIST_LINES ; i++,j++)
  {
    this->printGroove(i,j,i==selectedLine);
  }
  // clear the rest of the screen
  for (;j<=NUMBER_OF_LIST_LINES;j++)
  {
    _Disp->print((char*)"        ",GROOVESTART_COORDS(j),0);
    _Disp->print((char*)"        ",GROOVEWIDTH_COORDS(j),0);
  }
}



bool IndividualDistributionMenu::calculateGrooves(void)
{
  programMenu.program->clear();

  float bladeWidth =    nvm.SettingMenu_bladeWidth();
  // ---------------------------------------------
  for (int i=0; i<individualDistribution->size();i++)
  {
    GrooveDefinition *gd=individualDistribution->get(i);
    if (gd->width<bladeWidth)
    {
      char tempStr[40];
      snprintf(tempStr,60,"The groove %d is smaller than the blade.", i+1);
      this->printErrorMessage(tempStr);
      return false;
    }
  }
  // ---------------------------------------------
  
  int numberOfGroovesDefined=0;
  for (int i=0; i<individualDistribution->size();i++)
  {
    GrooveDefinition *gd=individualDistribution->get(i);
    float grooveStartPosition=gd->startPosition;
    float grooveWidth= gd->width;
    float grooveEndposition = grooveStartPosition+grooveWidth;
    
    while (grooveWidth>=bladeWidth)
    {
      programMenu.program->add(grooveStartPosition);
      numberOfGroovesDefined++;
      grooveStartPosition+=bladeWidth;
      grooveWidth-=bladeWidth;
    }
    if (grooveWidth>0)
    {
      grooveStartPosition=grooveEndposition-bladeWidth;
      programMenu.program->add(grooveStartPosition);
      numberOfGroovesDefined++;
    }
  }
  programMenu.setOverallLength(overallLength);
  return true;
}

extern char const* overallLengthString;

void IndividualDistributionMenu::dispatch(uint8_t buttonNumber)
{
  switch (buttonNumber)
  {
    case BUTTON_GO_BACK:
    {
      this->calculateGrooves();

      nvm.IndividualDistributionMenu_overallLength(overallLength);
      nvm.IndividualDistributionMenu_writeGrooves(individualDistribution);
      
      this->menuDeactivate();
      programMenu.menuActivate();
      break;
    }
    case BUTTON_UP:
    {
      if (selectedLine>0)
      {
        selectedLine--;
      }
      if (selectedLine<individualDistribution->size()-NUMBER_OF_LIST_LINES/2)
      {
        if (visualStartIndex>0)
        {
          visualStartIndex--;
        }
      }
      printGrooves();
    }
    break;
    case BUTTON_DOWN:
    {
      if (selectedLine<individualDistribution->size()-1)
      {
        selectedLine++;
      }
      if (selectedLine>NUMBER_OF_LIST_LINES/2)
      {
        if (visualStartIndex+NUMBER_OF_LIST_LINES<individualDistribution->size())
        {
          visualStartIndex++;
        }
      }
      printGrooves();
    }
    break;
    
    case BUTTON_ADD:
    {
      GrooveDefinition *gd = new GrooveDefinition(0.0f,0.0f);
      individualDistribution->add(0,gd);
      selectedLine=0;
      visualStartIndex=0;
      individualDistribution->sort();
      printGrooves();
      break;
    }
    case BUTTON_REMOVE:
    {
      GrooveDefinition *oldObject=individualDistribution->remove(selectedLine);
      delete(oldObject);
      if (selectedLine>=individualDistribution->size() && selectedLine>0)
      {
        selectedLine--;
      }
      if (selectedLine<visualStartIndex)
      {
        if (visualStartIndex>0)
        {
          visualStartIndex--;
        }
      }
      if (selectedLine<individualDistribution->size()-NUMBER_OF_LIST_LINES/2)
      {
        if (visualStartIndex>0)
        {
          visualStartIndex--;
        }
      }
      printGrooves();
      break;
    }
    case BUTTON_INVERT:
    {
      LinkedObjectList<GrooveDefinition*> *invertedIndividualDistribution=new LinkedObjectList<GrooveDefinition*>();
      float startPos=0;
      
      int index=0;
      while (index<individualDistribution->size())
      {
        GrooveDefinition *gd=individualDistribution->get(index);
        float grooveStartPosition=gd->startPosition;
        float grooveWidth= gd->width;
        float grooveEndposition = grooveStartPosition+grooveWidth;

        if(startPos<grooveStartPosition) // There is a groove to be inserted before the current definition
        {
          GrooveDefinition *newGd= new GrooveDefinition(startPos,grooveStartPosition-startPos);
          invertedIndividualDistribution->add(newGd);
        }    
        startPos=grooveEndposition;
        index++;
      }
      if (startPos<overallLength)
      {
        GrooveDefinition *newGd= new GrooveDefinition(startPos,overallLength-startPos);
        invertedIndividualDistribution->add(newGd);        
      }        
      individualDistribution->clear();
      delete(individualDistribution);
      individualDistribution=invertedIndividualDistribution;
      //----------------------------- copied from remove above.
       if (selectedLine>=individualDistribution->size() && selectedLine>0)
       {
         selectedLine--;
       }
       if (selectedLine<visualStartIndex)
       {
         if (visualStartIndex>0)
         {
           visualStartIndex--;
         }
       }
       if (selectedLine<individualDistribution->size()-NUMBER_OF_LIST_LINES/2)
       {
         if (visualStartIndex>0)
         {
           visualStartIndex--;
         }
       }
      printGrooves();
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
    case BUTTON_EDIT_START:
    {
      floatNumberEntryMenu.setReturnMenu(this);
      floatNumberEntryMenu.setTextMessage(editStartString);
      floatNumberEntryMenu.setValuePointerOnEnterPressed(&(individualDistribution->get(selectedLine)->startPosition));
      floatNumberEntryMenu.setValue(individualDistribution->get(selectedLine)->startPosition);
      lastSelectedGrooveDefinition = individualDistribution->get(selectedLine);
      this->menuDeactivate();
      floatNumberEntryMenu.menuActivate();
      break;
    }
    case BUTTON_EDIT_WIDTH:
    {
      floatNumberEntryMenu.setReturnMenu(this);
      floatNumberEntryMenu.setTextMessage(editWidthString);
      floatNumberEntryMenu.setValuePointerOnEnterPressed(&(individualDistribution->get(selectedLine)->width));
      floatNumberEntryMenu.setValue(individualDistribution->get(selectedLine)->width);
      this->menuDeactivate();
      floatNumberEntryMenu.menuActivate();
      break;
    }
  }
  
  if (calculateGrooves())
  {
    programMenu.drawGrooves(GROOVEPICTURE_POSITION);
  }
  
}



