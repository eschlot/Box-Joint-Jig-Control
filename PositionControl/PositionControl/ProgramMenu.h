/*
* ProgramMenu.h
*
* Created: 19.05.2015 22:50:53
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


#ifndef __PROGRAMMENU_H__
#define __PROGRAMMENU_H__
#include "Menu.h"
#include "LinkedList.h"



class ProgramMenu : public Menu
{
  //variables
  public:

  LinkedList<float> *program;
  float overallLength;
  
  /* status variables for the re-painting: */
  float lastTargetPosition;
  float lastCurrentPosition;
  protected:
  private:

  //functions
  public:
  ProgramMenu(UTFT *Disp, URTouch *Touch,TFT_Extension *TFTextention);
  
  virtual ~ProgramMenu(void);
  virtual void dispatch(uint8_t buttonNumber);

  virtual void menuIsActivating(void);

  virtual void drawGrooves(int x, int y, int width, int height);
  virtual void drawGrooves(int x, int y, int width, int height, int highlightedGrooveIndex);
  virtual void drawPositions(int x, int y, int width, int height, float currentPosition, float targetPosition,bool update);
  virtual float getOverallLength();

  virtual void setOverallLength(float overallLength) {
      this->overallLength = overallLength;
    }

  protected:
  private:
  ProgramMenu( const ProgramMenu &c );
  ProgramMenu& operator=( const ProgramMenu &c );

}; //ProgramMenu

#endif //__PROGRAMMENU_H__