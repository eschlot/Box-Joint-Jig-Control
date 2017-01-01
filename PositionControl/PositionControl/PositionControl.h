/*
 * PositionControl.h
 *
 * Created: 05.05.2015 21:50:52
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
#include "LicenseMenu.h"

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
extern LicenseMenu licenseMenu;


#endif /* INCFILE1_H_ */
