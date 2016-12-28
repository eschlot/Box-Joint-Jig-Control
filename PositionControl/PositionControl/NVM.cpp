/*
* NVM.cpp
*
* Created: 10.05.2015 22:43:18
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


#include "NVM.h"
#include "DueFlashStorage.h"
DueFlashStorage dueFlashStorage;

// The struct of the configuration.
struct Configuration {

  float LinearDistributionMenu_overallLength;
  float LinearDistributionMenu_grooveWidth;
  int LinearDistributionMenu_numberOfGrooves;
  bool LinearDistributionMenu_startsOnGroove;
  bool LinearDistributionMenu_endsOnGroove;

  float SettingMenu_bladeWidth;
  float SettingMenu_millimeterPerRevolution;
  float SettingMenu_stepsPerRevolution;
  int SettingMenu_stepsPerSec;
  int SettingMenu_acceleartion;
  int SettingMenu_deceleartion;
  bool SettingMenu_directionInversion;

  float IndividualDistributionMenu_overallLength;
  
};

// initialize one struct
Configuration configuration;

// default constructor
NVM::NVM()
{
} //NVM

// default destructor
NVM::~NVM()
{
} //~NVM


void NVM::LinearDistributionMenu_overallLength(float value)
{
  configuration.LinearDistributionMenu_overallLength=value;
  store();
}

float NVM::LinearDistributionMenu_overallLength(void)
{
  restore();
  return configuration.LinearDistributionMenu_overallLength;
}

void NVM::LinearDistributionMenu_grooveWidth(float value)
{
  configuration.LinearDistributionMenu_grooveWidth=value;
  store();
}

float NVM::LinearDistributionMenu_grooveWidth(void)
{
  restore();
  return configuration.LinearDistributionMenu_grooveWidth;
}

void NVM::LinearDistributionMenu_numberOfGrooves(int value)
{
  configuration.LinearDistributionMenu_numberOfGrooves=value;
  store();
}

int NVM::LinearDistributionMenu_numberOfGrooves(void)
{
  restore();
  return configuration.LinearDistributionMenu_numberOfGrooves;
}
void NVM::LinearDistributionMenu_startsOnGroove(bool value)
{
  configuration.LinearDistributionMenu_startsOnGroove=value;
  store();
}

bool NVM::LinearDistributionMenu_startsOnGroove(void)
{
  restore();
  return configuration.LinearDistributionMenu_startsOnGroove;
}
void NVM::LinearDistributionMenu_endsOnGroove(bool value)
{
  configuration.LinearDistributionMenu_endsOnGroove=value;
  store();
}

bool NVM::LinearDistributionMenu_endsOnGroove(void)
{
  restore();
  return configuration.LinearDistributionMenu_endsOnGroove;
}


void NVM::SettingMenu_bladeWidth(float value)
{
  configuration.SettingMenu_bladeWidth=value;
  store();
}

float NVM::SettingMenu_bladeWidth(void)
{
  restore();
  return configuration.SettingMenu_bladeWidth;
}

void NVM::SettingMenu_millimeterPerRevolution(float value)
{
  configuration.SettingMenu_millimeterPerRevolution=value;
  store();
}

float NVM::SettingMenu_millimeterPerRevolution(void)
{
  restore();
  return configuration.SettingMenu_millimeterPerRevolution;
}

void NVM::SettingMenu_stepsPerRevolution(float value)
{
  configuration.SettingMenu_stepsPerRevolution=value;
  store();
}

float NVM::SettingMenu_stepsPerRevolution(void)
{
  restore();
  return configuration.SettingMenu_stepsPerRevolution;
}

void NVM::SettingMenu_stepsPerSec(int value)
{
  configuration.SettingMenu_stepsPerSec=value;
  store();
}

int NVM::SettingMenu_stepsPerSec(void)
{
  restore();
  return configuration.SettingMenu_stepsPerSec;
}

int NVM::SettingMenu_acceleartion(void)
{
  restore();
  return configuration.SettingMenu_acceleartion;
}

void NVM::SettingMenu_acceleartion(int value)
{
  configuration.SettingMenu_acceleartion=value;
  store();
}

int NVM::SettingMenu_deceleartion(void)
{
  restore();
  return configuration.SettingMenu_deceleartion;
}

void NVM::SettingMenu_deceleartion(int value)
{
  configuration.SettingMenu_deceleartion=value;
  store();
}

bool NVM::SettingMenu_directionInversion()
{
  restore();
  return configuration.SettingMenu_directionInversion;
}

void NVM::SettingMenu_directionInversion(bool value)
{
  configuration.SettingMenu_directionInversion=value;
  store();
}

void NVM::IndividualDistributionMenu_overallLength(float value)
{
  configuration.IndividualDistributionMenu_overallLength=value;
  store();
}

float NVM::IndividualDistributionMenu_overallLength(void)
{
  restore();
  return configuration.IndividualDistributionMenu_overallLength;
}







void NVM::store(void)
{
  // write configuration struct to flash at address 4
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configuration, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
}

void NVM::restore(void)
{
  /* Flash is erased every time new code is uploaded. Write the default configuration to flash if first time */
  // running for the first time?
  uint8_t codeRunningForTheFirstTime = dueFlashStorage.read(0); // flash bytes will be 255 at first run
  if (codeRunningForTheFirstTime) {
    configuration.LinearDistributionMenu_endsOnGroove=false;
    configuration.LinearDistributionMenu_startsOnGroove=false;
    configuration.LinearDistributionMenu_numberOfGrooves=5;
    configuration.LinearDistributionMenu_overallLength=100.0f;
    configuration.LinearDistributionMenu_grooveWidth=6.66f;

    configuration.SettingMenu_bladeWidth=2.2f;
    configuration.SettingMenu_millimeterPerRevolution=1.25f;
    configuration.SettingMenu_stepsPerRevolution=200.0f;
    configuration.SettingMenu_acceleartion=2;
    configuration.SettingMenu_deceleartion=4;
    configuration.SettingMenu_directionInversion=false;
    
    configuration.IndividualDistributionMenu_overallLength=100.0f;

    // write configuration struct to flash at address 4
    byte b2[sizeof(Configuration)]; // create byte array to store the struct
    memcpy(b2, &configuration, sizeof(Configuration)); // copy the struct to the byte array
    dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash

    // write 0 to address 0 to indicate that it is not the first time running anymore
    dueFlashStorage.write(0, 0);
  }
  else {
    /* read configuration struct from flash */
    byte* b = dueFlashStorage.readAddress(4); // byte array which is read from flash at adress 4
    memcpy(&configuration, b, sizeof(Configuration)); // copy byte array to temporary struct
  }
}


typedef struct
{
  float startPosition;
  float width;
} groove_t;


void NVM::IndividualDistributionMenu_writeGrooves(LinkedObjectList<GrooveDefinition*> *individualDistribution)
{
  int length = individualDistribution->size();
  uint32_t startAddress = ((4+sizeof(Configuration)+256)/256)*256;                  // Align to the next 256 Byte border following the base configuration
  
  byte b1[sizeof(int)];
  memcpy(b1,&length,sizeof(int));
  
  dueFlashStorage.write(startAddress,b1,sizeof(int));
  startAddress+=sizeof(int);
  
  for (int i=0;i<length;i++)
  {
    groove_t g;
    GrooveDefinition *gd=individualDistribution->get(i);
    g.startPosition= gd->startPosition;
    g.width=gd->width;
    
    byte b2[sizeof(groove_t)]; // create byte array to store the struct
    memcpy(b2, &g, sizeof(groove_t)); // copy the struct to the byte array
    dueFlashStorage.write(startAddress,b2,sizeof(groove_t));
    startAddress+=sizeof(groove_t);
  }
}


LinkedObjectList<GrooveDefinition*>* NVM::IndividualDistributionMenu_readGrooves(void)
{
  uint32_t startAddress = ((4+sizeof(Configuration)+256)/256)*256;                  // Align to the next 256 Byte border following the base configuration
  LinkedObjectList<GrooveDefinition*>* individualDistribution=new LinkedObjectList<GrooveDefinition*>();
  
  int length;
  byte *b = dueFlashStorage.readAddress(startAddress);
  if (*b==255 && (*(b+1)==255) &&(*(b+2)==255) &&(*(b+3)==255))
  {
    length=0;
  }
  else
  {
    memcpy(&length,b,sizeof(int));
  }
  
  startAddress+=sizeof(int);
  
  for (int i=0;i<length;i++)
  {
    groove_t g;

    b = dueFlashStorage.readAddress(startAddress);
    memcpy(&g,b,sizeof(groove_t));
    
    GrooveDefinition *gd1 = new GrooveDefinition(g.startPosition,g.width);
    individualDistribution->add(gd1);
    startAddress+=sizeof(groove_t);
  }
  return individualDistribution;  
  
}









