/*
* Menu.cpp
*
* Created: 03.05.2015 23:45:52
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


#include "Menu.h"


// default constructor
Menu::Menu(UTFT *Disp, URTouch *Touch,TFT_Extension *TFTextention):_Disp(Disp) ,_Touch(Touch),_TFTextension(TFTextention)
{
  _menuState=  MENU_INACTIVE;
  _screenButtons=NULL;
  _numScreenButtons=0;
} //Menu

Menu::~Menu(void)
{

}

void Menu::menuDrawGrid(void)
{
  int xSize=_Disp->getDisplayXSize();
  int ySize = _Disp->getDisplayYSize();
  _Disp->setColor(255,0,0);
  for (int y=1;y<ySize;y+=100)
  {
    _Disp->drawLine(1,y,xSize-1,y);
  }
  for (int x=1;x<xSize;x+=100)
  {
    _Disp->drawLine(x,1,x,ySize-1);
  }
}



void Menu::menuSetup(void)
{
  _menuState=MENU_INACTIVE;
}

void Menu::menuActivate(void)
{
  _menuState=MENU_INIT;  
}

void Menu::menuDeactivate(void)
{
  _menuState=MENU_INACTIVE;
}

void Menu::menuIsActivating(void)
{
  // empty dummy implementation to be overwritten by subclass if extra things need to be displayed when the menu appears first on the screen.
}

void Menu::menuDo()
{
  switch (_menuState)
  {
    case MENU_INACTIVE:
    // inactive - do nothing    
    break;
    case MENU_INIT:
    {
      _TFTextension->SetAll_RB_Outer_Color(WHITE);
      _TFTextension->SetAll_RB_Toggled_Color(BLUE);
      _TFTextension->SetAll_RCB_Untoggled_Color(DARK_BLUE);

      _Disp->fillScr(0,0,0);
      _Disp->setColor(255,255,255);
      //this->menuDrawGrid();

      for (int i=0;i<_numScreenButtons;i++)
      {
        menuButtonType *cb=&_screenButtons[i]; //cb == currentButton
        
        _TFTextension->SetTouchButtonColors(cb->buttonNumber,cb->color1,cb->color2,cb->fill,true);
        _TFTextension->SetTouchButtonText(cb->buttonNumber,cb->text,cb->size,cb->textColor);
        cb->pressed=false;
      }
      menuIsActivating();
      _menuState=MENU_WAITING;
    }
    break;
    case MENU_WAITING:
    {
      for (int i=0;i<_numScreenButtons;i++)
      {
        menuButtonType *cb=&_screenButtons[i]; //cb == currentButton
        if (_TFTextension->TouchButton_Draw(cb->x,cb->y,cb->width,cb->height,cb->buttonNumber))
        {
          cb->pressed=true;
        }
        else if (cb->pressed) // On Button release execute the function
        {
          cb->pressed=false;
          this->dispatch(cb->buttonNumber);
          
        }
      }
    }
    
  }
}
