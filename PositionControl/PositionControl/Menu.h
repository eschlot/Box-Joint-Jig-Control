/*
* Menu.h
*
* Created: 03.05.2015 23:45:52
Copyright (c) 2015 Eckart Schlottmann
Author: Eckart Schlottmann


This software is distributed under the terms of the 
Mozilla Public License Version 2.0
This licence is disributed alongside with this software or can be 
obtained from http://mozilla.org/MPL/2.0/

Under all thircumstances note the following paragraphs of the license:


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


#ifndef __MENU_H__
#define __MENU_H__


#include <UTFT.h>
#include <memorysaver.h>
#include <TFT_Extension.h>
#include <URTouchCD.h>
#include <URTouch.h>

class Menu;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

extern uint8_t BigFont[];
extern uint8_t SmallFont[];
extern uint8_t TRONFont[];


typedef enum
{
  MENU_INACTIVE,
  MENU_INIT,
  MENU_WAITING,
}
MenuState_t;

typedef void (Menu::*callback_type)();



typedef struct
{ // Values to define the button behavior
  uint8_t buttonNumber;
  bool size;
  bool fill;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  word color1;
  word color2;
  word textColor;
  char const * text;
  
  // Runtime values, init is don't care
  bool pressed;
} menuButtonType;


class Menu
{
  //variables :
  protected:

   UTFT	          *_Disp;
   URTouch	      *_Touch;
   TFT_Extension   *_TFTextension;
   MenuState_t     _menuState;
   menuButtonType  *_screenButtons;
   int             _numScreenButtons;

  
  //functions
  public:
  Menu(UTFT *Disp, URTouch *Touch,TFT_Extension *TFTextention);
  virtual ~Menu(void);

  virtual void menuIsActivating(void);
  virtual void menuSetup(void);
  virtual void menuDo();
  virtual void menuDrawGrid(void);
  virtual void menuActivate(void);
  virtual void menuDeactivate(void);

  virtual void dispatch(uint8_t buttonNumber) = 0 ; // Pure virtual function makes
                                                    // this class Abstract class.

}; //Menu

#endif //__MENU_H__
