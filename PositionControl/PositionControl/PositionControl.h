/*
 * PositionControl.h
 *
 * Created: 05.05.2015 21:50:52
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


#ifndef POSITIONCONTROL_H_
#define POSITIONCONTROL_H_

#include <UTFT.h>
#include <memorysaver.h>
#include <TFT_Extension.h>
#include <URTouchCD.h>
#include <URTouch.h>

#include "SettingMenu.h"
#include "MainMenu.h"
#include "ProgramMenu.h"
#include "LinearDistributionMenu.h"
#include "FloatNumberEntryMenu.h"
#include "IntegerNumberEntryMenu.h"
#include "NVM.h"
#include "Control.h"
#include "ControlMenu.h"
#include "IndividualDistributionMenu.h"

extern MainMenu mainMenu;
extern ProgramMenu programMenu;
extern LinearDistributionMenu linearDistributionMenu;
extern FloatNumberEntryMenu floatNumberEntryMenu;
extern IntegerNumberEntryMenu integerNumberEntryMenu;
extern SettingMenu settingMenu;
extern NVM nvm;
extern ControlSystem controlSystem;
extern ControlMenu controlMenu;
extern IndividualDistributionMenu individualDistributionMenu;



#endif /* INCFILE1_H_ */
