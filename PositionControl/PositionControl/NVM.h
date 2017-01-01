/*
* NVM.h
*
* Created: 10.05.2015 22:43:18
Copyright (c) 2015 Eckart Schlottmann
Author: Eckart Schlottmann


This software is distributed under the terms of the 
Mozilla Public License Version 2.0 with extensions for safety
This licence is distributed alongside with this software 


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


#ifndef __NVM_H__
#define __NVM_H__

#include "Menu.h"
#include "LinkedObjectList.h"
#include "GrooveDefinition.h"




class NVM
{
  //variables
  public:
  protected:
  private:


  //functions
  public:
  NVM();
  ~NVM();
  
  static void LinearDistributionMenu_overallLength(float value);
  static float LinearDistributionMenu_overallLength(void);
  static void LinearDistributionMenu_grooveWidth(float value);
  static float LinearDistributionMenu_grooveWidth(void);
  static void LinearDistributionMenu_numberOfGrooves(int value);
  static int LinearDistributionMenu_numberOfGrooves(void);
  static void LinearDistributionMenu_startsOnGroove(bool value);
  static bool LinearDistributionMenu_startsOnGroove(void);
  static void LinearDistributionMenu_endsOnGroove(bool value);
  static bool LinearDistributionMenu_endsOnGroove(void);
  
  static void SettingMenu_bladeWidth(float value);
  static float SettingMenu_bladeWidth(void);
  static void SettingMenu_millimeterPerRevolution(float value);
  static float SettingMenu_millimeterPerRevolution(void);
  static void SettingMenu_stepsPerRevolution(float value);
  static float SettingMenu_stepsPerRevolution(void);
  static void SettingMenu_stepsPerSec(int value);
  static  int SettingMenu_stepsPerSec(void);
  
  static int SettingMenu_acceleartion(void);
  static void SettingMenu_acceleartion(int value);
  static int SettingMenu_deceleartion(void);
  static void SettingMenu_deceleartion(int value);
  
  static bool SettingMenu_directionInversion();
  static void SettingMenu_directionInversion(bool value);

  static void IndividualDistributionMenu_overallLength(float value);
  static float IndividualDistributionMenu_overallLength(void);
  
  
  static void IndividualDistributionMenu_writeGrooves(LinkedObjectList<GrooveDefinition*> *individualDistribution);
  static LinkedObjectList<GrooveDefinition*>* IndividualDistributionMenu_readGrooves(void);

  
  protected:
  static void store(void);
  static void restore(void);

  private:
  NVM( const NVM &c );
  NVM& operator=( const NVM &c );

  
}; //NVM

#endif //__NVM_H__
