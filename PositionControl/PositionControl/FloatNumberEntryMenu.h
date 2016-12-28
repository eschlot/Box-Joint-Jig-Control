/* 
* FloatNumberEntryMenu.h
*
* Created: 23.05.2015 22:37:11
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


#ifndef __FLOATNUMBERENTRYMENU_H__
#define __FLOATNUMBERENTRYMENU_H__
#include "Menu.h"

class FloatNumberEntryMenu: public Menu
{
//variables
public:
protected:
private:
  float value;
  char valueString[40];
  char const* textMessagePtr;
  Menu* returnMenuPtr;
  float* valueToWriteHereOnEnterPressed;

//functions
public:
FloatNumberEntryMenu(UTFT *Disp, URTouch *Touch,TFT_Extension *TFTextention);

virtual ~FloatNumberEntryMenu(void);
virtual void dispatch(uint8_t buttonNumber);

virtual void menuIsActivating(void);

virtual float getValue();
virtual void setValuePointerOnEnterPressed(float* retValPtr);
virtual void setValue(float v);
virtual void setTextMessage(char const* text);
virtual void setReturnMenu(Menu* m);

protected:
private:
	FloatNumberEntryMenu( const FloatNumberEntryMenu &c );
	FloatNumberEntryMenu& operator=( const FloatNumberEntryMenu &c );

}; //FloatNumberEntryMenu

#endif //__FLOATNUMBERENTRYMENU_H__