/*
* SettingMenu.cpp
*
* Created: 04.06.2015 22:23:24
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


#include "SettingMenu.h"
#include "PositionControl.h"


enum
{
  BUTTON_GO_BACK,
  BUTTON_BLADE_WIDTH_SETTING,
  BUTTON_MILLIMETER_PER_REVOLUTION,
  BUTTON_STEPS_PER_REVOLUTION,
  BUTTON_STEPS_PER_SECOND,
  BUTTON_ACCELEARTION,
  BUTTON_DECELERATION,
  BUTTON_DIRECTION_INVERSION,
};


#define NUMBER_OF_LAYOUT_LINES  8
#define NUMBER_OF_LAYOUT_COLUMNS 2

#define BUTTON_COLUMN_OFFSET 20
#define BUTTON_LINE_OFFSET    5

#define NUMBER_BUTTON_WIDTH ((SCREEN_WIDTH/NUMBER_OF_LAYOUT_COLUMNS)-BUTTON_COLUMN_OFFSET)
#define NUMBER_BUTTON_HEIGHT ((SCREEN_HEIGHT/NUMBER_OF_LAYOUT_LINES)-BUTTON_LINE_OFFSET )

#define COLUMN(x) (((SCREEN_WIDTH * x) / NUMBER_OF_LAYOUT_COLUMNS) )
#define LINE(x)   (((SCREEN_HEIGHT *x) / NUMBER_OF_LAYOUT_LINES) )


#define BUTTON_COORDS(x,y)  COLUMN(x)+BUTTON_COLUMN_OFFSET/2,   \
LINE(y)+BUTTON_LINE_OFFSET/2,                           \
COLUMN(x)+NUMBER_BUTTON_WIDTH,                          \
LINE(y)+NUMBER_BUTTON_HEIGHT

#define BUTTON_GO_BACK_COORDS                   BUTTON_COORDS(0,0)
#define BUTTON_BLADE_WIDTH_SETTING_COORDS       BUTTON_COORDS(0,1)
#define BUTTON_MILLIMETER_PER_REVOLUTION_COORDS BUTTON_COORDS(0,2)
#define BUTTON_STEPS_PER_REVOLUTION_COORDS      BUTTON_COORDS(0,3)
#define BUTTON_STEPS_PER_SECOND_COORDS          BUTTON_COORDS(0,4)
#define BUTTON_ACCELEARTION_COORDS          BUTTON_COORDS(0,5)
#define BUTTON_DECELERATION_COORDS          BUTTON_COORDS(0,6)
#define BUTTON_DIRECTION_INVERSION_COORDS   BUTTON_COORDS(0,7)


#define BLADE_WIDTH_SETTING_COORDS        COLUMN(1)+BUTTON_COLUMN_OFFSET,LINE(1)+BUTTON_LINE_OFFSET
#define MILLIMETER_PER_REVOLUTION_COORDS  COLUMN(1)+BUTTON_COLUMN_OFFSET,LINE(2)+BUTTON_LINE_OFFSET
#define STEPS_PER_REVOLUTION_COORDS       COLUMN(1)+BUTTON_COLUMN_OFFSET,LINE(3)+BUTTON_LINE_OFFSET
#define STEPS_PER_SECOND_COORDS           COLUMN(1)+BUTTON_COLUMN_OFFSET,LINE(4)+BUTTON_LINE_OFFSET

#define ACCELEARTION_COORDS           COLUMN(1)+BUTTON_COLUMN_OFFSET,LINE(5)+BUTTON_LINE_OFFSET
#define DECELERATION_COORDS           COLUMN(1)+BUTTON_COLUMN_OFFSET,LINE(6)+BUTTON_LINE_OFFSET
#define DIRECTION_INVERSION_COORDS    COLUMN(1)+BUTTON_COLUMN_OFFSET,LINE(7)+BUTTON_LINE_OFFSET


#define SPECIALBUTTONDEF(x,text) { BUTTON_##x,false,true,BUTTON_##x##_COORDS,BLUE,DARK_BLUE,WHITE, #text ,false }

menuButtonType settingsMenuButton[] = {
  SPECIALBUTTONDEF(GO_BACK,Back),
  SPECIALBUTTONDEF(BLADE_WIDTH_SETTING,Blade width),
  SPECIALBUTTONDEF(MILLIMETER_PER_REVOLUTION,mm per rev.),
  SPECIALBUTTONDEF(STEPS_PER_REVOLUTION,Steps per rev.),
  SPECIALBUTTONDEF(STEPS_PER_SECOND,Steps per sec.),
  SPECIALBUTTONDEF(ACCELEARTION,Acceleration),
  SPECIALBUTTONDEF(DECELERATION,Deceleration),
  SPECIALBUTTONDEF(DIRECTION_INVERSION,Direction inv.)
};

SettingMenu::SettingMenu(UTFT *Disp, URTouch *Touch,TFT_Extension *TFTextention) : Menu(Disp,Touch,TFTextention)
{
  _screenButtons=settingsMenuButton;
  _numScreenButtons=sizeof(settingsMenuButton)/sizeof(menuButtonType);
  
  // Read the last setting from Flash
  bladeWidth=nvm.SettingMenu_bladeWidth();
  millimeterPerRevolution=nvm.SettingMenu_millimeterPerRevolution();
  stepsPerRevolution=nvm.SettingMenu_stepsPerRevolution();
  stepsPerSec=nvm.SettingMenu_stepsPerSec();
  acceleration=nvm.SettingMenu_acceleartion();
  deceleration=nvm.SettingMenu_deceleartion();
  directionInversion = nvm.SettingMenu_directionInversion();
}

SettingMenu::~SettingMenu(void)
{
}

#define formatValue(value) snprintf(tempStr,40,"%.0d%.4g        ", (int)value/10, value-((int)value-(int)value%10));
#define formatIntValue(value) snprintf(tempStr,40,"%3d        ", value);

void SettingMenu::menuIsActivating(void)
{
  _Disp->setFont(SmallFont);
  _Disp->setColor(WHITE);
  _Disp->setBackColor(BLACK);
  
  char tempStr[40];
  formatValue(bladeWidth);
  _Disp->print(tempStr,BLADE_WIDTH_SETTING_COORDS,0);
  
  formatValue(millimeterPerRevolution);
  _Disp->print(tempStr,MILLIMETER_PER_REVOLUTION_COORDS,0);
  
  formatValue(stepsPerRevolution);
  _Disp->print(tempStr,STEPS_PER_REVOLUTION_COORDS,0);
  
  formatIntValue(stepsPerSec);
  _Disp->print(tempStr,STEPS_PER_SECOND_COORDS,0);
  
  formatIntValue(acceleration);
  _Disp->print(tempStr,ACCELEARTION_COORDS,0);
  
  formatIntValue(deceleration);
  _Disp->print(tempStr,DECELERATION_COORDS,0);
  
  if (directionInversion)
  {
    _Disp->print((char*)"On ",DIRECTION_INVERSION_COORDS,0);
  }
  else
  {
    _Disp->print((char*)"Off",DIRECTION_INVERSION_COORDS,0);
  }
}




void SettingMenu::dispatch(uint8_t buttonNumber)
{
  switch (buttonNumber)
  {
    case BUTTON_GO_BACK:
    {
      nvm.SettingMenu_stepsPerRevolution(stepsPerRevolution);
      nvm.SettingMenu_millimeterPerRevolution(millimeterPerRevolution);
      nvm.SettingMenu_bladeWidth(bladeWidth);
      nvm.SettingMenu_stepsPerSec(stepsPerSec);
      nvm.SettingMenu_acceleartion(acceleration);
      nvm.SettingMenu_deceleartion(deceleration);
      nvm.SettingMenu_directionInversion(directionInversion);
      this->menuDeactivate();
      mainMenu.menuActivate();
      break;
    }
    
    case BUTTON_BLADE_WIDTH_SETTING:
    {
      floatNumberEntryMenu.setReturnMenu(this);
      floatNumberEntryMenu.setTextMessage("Blade Width (mm)");
      floatNumberEntryMenu.setValuePointerOnEnterPressed(&bladeWidth);
      floatNumberEntryMenu.setValue(bladeWidth);
      this->menuDeactivate();
      floatNumberEntryMenu.menuActivate();
      break;
    }
    case BUTTON_MILLIMETER_PER_REVOLUTION:
    {
      floatNumberEntryMenu.setReturnMenu(this);
      floatNumberEntryMenu.setTextMessage("Millimeter per rev.");
      floatNumberEntryMenu.setValuePointerOnEnterPressed(&millimeterPerRevolution);
      floatNumberEntryMenu.setValue(millimeterPerRevolution);
      this->menuDeactivate();
      floatNumberEntryMenu.menuActivate();
      break;
    }
    case BUTTON_STEPS_PER_REVOLUTION:
    {
      floatNumberEntryMenu.setReturnMenu(this);
      floatNumberEntryMenu.setTextMessage("Steps per rev.");
      floatNumberEntryMenu.setValuePointerOnEnterPressed(&stepsPerRevolution);
      floatNumberEntryMenu.setValue(stepsPerRevolution);
      this->menuDeactivate();
      floatNumberEntryMenu.menuActivate();
      break;
    }
    case BUTTON_STEPS_PER_SECOND:
    {
      integerNumberEntryMenu.setReturnMenu(this);
      integerNumberEntryMenu.setTextMessage("Steps per sec.");
      integerNumberEntryMenu.setValuePointerOnEnterPressed(&stepsPerSec);
      integerNumberEntryMenu.setValue(stepsPerSec);
      this->menuDeactivate();
      integerNumberEntryMenu.menuActivate();
      break;
    }
    case BUTTON_ACCELEARTION:
    {
      integerNumberEntryMenu.setReturnMenu(this);
      integerNumberEntryMenu.setTextMessage("Acceleration (typ. 1-10)");
      integerNumberEntryMenu.setValuePointerOnEnterPressed(&acceleration);
      integerNumberEntryMenu.setValue(acceleration);
      this->menuDeactivate();
      integerNumberEntryMenu.menuActivate();
      break;
    }
    case BUTTON_DECELERATION:
    {
      integerNumberEntryMenu.setReturnMenu(this);
      integerNumberEntryMenu.setTextMessage("Deceleration (typ. 1-10)");
      integerNumberEntryMenu.setValuePointerOnEnterPressed(&deceleration);
      integerNumberEntryMenu.setValue(deceleration);
      this->menuDeactivate();
      integerNumberEntryMenu.menuActivate();
      break;
    }
    case BUTTON_DIRECTION_INVERSION:
    {
      _Disp->setBackColor(BLACK);
      if (directionInversion)
      {
        directionInversion=false;
        _Disp->print((char*)"Off",DIRECTION_INVERSION_COORDS,0);
      }
      else
      {
        directionInversion=true;
        _Disp->print((char*)"On ",DIRECTION_INVERSION_COORDS,0);
      }
      break;
    }
  }
  
  
}

float SettingMenu::getStepsPerMilimeter()
{
  return stepsPerRevolution/millimeterPerRevolution;
}


float SettingMenu::getMilimeterPerStep()
{
  return millimeterPerRevolution/stepsPerRevolution;
}


int SettingMenu::getStepsPerSecond()
{
  return stepsPerSec;
}

int SettingMenu::getAcceleration()
{
  return acceleration;
}

int SettingMenu::getDeceleration()
{
  return deceleration;
}

float SettingMenu::getBladeWidth()
{
  return bladeWidth;
}

boolean SettingMenu::getDirectionInversion()
{
  return directionInversion;
}





