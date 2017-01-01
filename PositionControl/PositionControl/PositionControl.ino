/*
 * PositionControl3.ino
 *
 * Created: 4/30/2015 10:11:50 PM

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

#include <DueTimer.h>
#include <UTFT.h>
#include <memorysaver.h>
#include <TFT_Extension.h>
#include <URTouchCD.h>
#include <URTouch.h>
#include "NVM.h"
#include "LinkedList.h"
#include "MainMenu.h"
#include "ProgramMenu.h"
#include "LinearDistributionMenu.h"
#include "FloatNumberEntryMenu.h"
#include "IntegerNumberEntryMenu.h"
#include "SettingMenu.h"
#include "Control.h"
#include "ControlMenu.h"
#include "IndividualDistributionMenu.h"
#include "LicenseMenu.h"

// Declare which fonts we will be using
//extern uint8_t BigFont[];
extern uint8_t SmallFont[];


// Initialize display
// ------------------
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino Uno/2009 Shield            : <display model>,19,18,17,16
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Due       : <display model>,25,26,27,28
// Teensy 3.x TFT Test Board                   : <display model>,23,22, 3, 4
// ElecHouse TFT LCD/SD Shield for Arduino Due : <display model>,22,23,31,33
//
// Remember to change the model parameter to suit your display module!

//UTFT    myGLCD(ITDB32S,38,39,40,41); //TFT_320QVT
UTFT    myGLCD(ILI9341_16,38,39,40,41); //TFT_320QVT_9341

// Initialize touchscreen
// ----------------------
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino Uno/2009 Shield            : 15,10,14, 9, 8
// Standard Arduino Mega/Due shield            :  6, 5, 4, 3, 2
// CTE TFT LCD/SD Shield for Arduino Due       :  6, 5, 4, 3, 2
// Teensy 3.x TFT Test Board                   : 26,31,27,28,29
// ElecHouse TFT LCD/SD Shield for Arduino Due : 25,26,27,29,30
//
URTouch  myTouch( 6, 5, 4, 3, 2);
TFT_Extension myTFT(&myGLCD, &myTouch);
NVM nvm;
ControlSystem controlSystem;

MainMenu mainMenu(&myGLCD, &myTouch, &myTFT);
ProgramMenu programMenu(&myGLCD, &myTouch, &myTFT);
LinearDistributionMenu linearDistributionMenu(&myGLCD, &myTouch, &myTFT);
FloatNumberEntryMenu floatNumberEntryMenu(&myGLCD, &myTouch, &myTFT);
IntegerNumberEntryMenu integerNumberEntryMenu(&myGLCD, &myTouch, &myTFT);
SettingMenu settingMenu(&myGLCD, &myTouch, &myTFT);
ControlMenu controlMenu(&myGLCD, &myTouch, &myTFT);
IndividualDistributionMenu individualDistributionMenu(&myGLCD, &myTouch, &myTFT);
LicenseMenu licenseMenu(&myGLCD,&myTouch, &myTFT);

void watchdogSetup(void)
{
  watchdogEnable(500);
}

void setup()
{
//  Serial.begin(9600);
//  while(!SerialUSB){};
//  SerialUSB.println("start");
  watchdogSetup();
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
           
  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_MEDIUM);
  myTouch.calibrateRead();
  myTFT.ExtSetup();

// Init all Menus
  mainMenu.menuSetup();
  settingMenu.menuSetup();
  programMenu.menuSetup();
  linearDistributionMenu.menuSetup();
  floatNumberEntryMenu.menuSetup();
  integerNumberEntryMenu.menuSetup();
  controlMenu.menuSetup();
  individualDistributionMenu.menuSetup();
  licenseMenu.menuSetup();
  
  controlSystem.ini();
  mainMenu.menuActivate();
  watchdogReset();
}

void loop()
{
  // Run all menus

  mainMenu.menuDo();
  settingMenu.menuDo();
  programMenu.menuDo();
  linearDistributionMenu.menuDo();
  individualDistributionMenu.menuDo();
  licenseMenu.menuDo();
  floatNumberEntryMenu.menuDo();
  integerNumberEntryMenu.menuDo();
  controlMenu.menuDo();
  controlMenu.run();
  
  watchdogReset();
  controlSystem.run();
}

void startup()
{
}

