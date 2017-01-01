/***

Control.cpp
Created: 06.06.2015 23:40:15
Copyright (c) 2015 Eckart Schlottmann
Author: Eckart Schlottmann


This software is distributed under the terms of the 
Mozilla Public License Version 2.0 with extensions for safety
This license is distributed alongside with this software 


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


#include "Control.h"
#include "PositionControl.h"


#define PIN_ENABLE 11
#define PIN_DIRECTION 13
#define PIN_PULSE 12



// default constructor
ControlSystem::ControlSystem()
{
  _timer = new DueTimer(0);
  _running=false;
  _timer->attachInterrupt(&isr);

  _currentPosition_f=0.0f;
  _currentTargetPosition_f=0.0f;
  _currentPosition_i32=0;
  _currentTargetPosition_i32=0;

  _active=false;
  _currentFrequency=0;
  _currentDistance=0;
  nearestIndex=0;
  this->ini();

} //Control

// default destructor
ControlSystem::~ControlSystem()
{
  delete(_timer);
} //~Control


void ControlSystem::isr(void)
{
  controlSystem._timer->stop();
  int currentLevel = digitalRead(PIN_PULSE);
  
  
  if (!currentLevel)
  {
    digitalWrite(PIN_PULSE,HIGH);
    controlSystem._timer->setFrequency(abs(controlSystem._currentFrequency));
    controlSystem._timer->start();
  }
  else
  {
    digitalWrite(PIN_PULSE,LOW);
    /* Update the position information */
    if (controlSystem._currentFrequency>0)
    {
      controlSystem._currentPosition_i32++;
    }
    else
    {
      controlSystem._currentPosition_i32--;
    }
    controlSystem._currentPosition_f=controlSystem._currentPosition_i32/settingMenu.getStepsPerMilimeter();
    
    /* calculate the next action */
    controlSystem.calculateFrequency();
    /* initiate the next action */
    if (controlSystem._currentDistance!=0)
    {
      controlSystem._timer->setFrequency(abs(controlSystem._currentFrequency));
      controlSystem._timer->start();
    }
    else
    {
      controlSystem._currentFrequency=0.0;
      controlSystem._running=false;
    }
    
  }
}


void ControlSystem::run(void)
{
  if (_active)
  {
    if (!_running)
    {
      calculateFrequency();
      if (_currentDistance!=0)
      {
        _running=true;
        digitalWrite(PIN_PULSE,LOW);
        _timer->setFrequency(abs(_currentFrequency));
        _timer->start();
      }
    }
  }
}

void ControlSystem::calculateFrequency(void)
{
  int ms = settingMenu.getAcceleration();     // Linear function y=m*x+b --> ms is the start stepness of the line
  int me = settingMenu.getDeceleration();     // me is the end stepness of the line
  
  _currentDistance=_currentTargetPosition_i32-_currentPosition_i32;
  
  // Check for change of mind: The direction to the target changed
  if((_currentFrequency<=0) && (_currentDistance>0))
  {
    _currentFrequency+=me;
  }
  else if ((_currentFrequency>=0) && (_currentDistance<0))
  {
    _currentFrequency-=me;
  }
  else // Normal operation
  {
    
    if (_currentDistance>0)
    {
      _currentFrequency+=ms;
      
      if (_currentFrequency>settingMenu.getStepsPerSecond())
      {
        _currentFrequency=settingMenu.getStepsPerSecond();
      }
      if (_currentFrequency > _currentDistance*me)
      {
        _currentFrequency= _currentDistance*me;
      }
    }
    else if (_currentDistance<0)
    {
      _currentFrequency-=ms;
      
      if (_currentFrequency< -settingMenu.getStepsPerSecond())
      {
        _currentFrequency= -settingMenu.getStepsPerSecond();
      }
      if (_currentFrequency < _currentDistance*me)
      {
        _currentFrequency= _currentDistance*me;
      }
    }
  }

  if (settingMenu.getDirectionInversion())
  {
    if (_currentFrequency>0)
    {
      digitalWrite(PIN_DIRECTION,HIGH);
    }
    else if (_currentFrequency<0)
    {
      digitalWrite(PIN_DIRECTION,LOW);
    }
    else
    {
      // Keep unchanged
    }
  }
  else
  {
    if (_currentFrequency>0)
    {
      digitalWrite(PIN_DIRECTION,LOW);
    }
    else if (_currentFrequency<0)
    {
      digitalWrite(PIN_DIRECTION,HIGH);
    }
    else
    {
      // Keep unchanged
    }
  }
}


void ControlSystem::go(float distance)

{
  noInterrupts();
  _currentTargetPosition_f+=distance;
  _currentTargetPosition_i32=_currentTargetPosition_f*settingMenu.getStepsPerMilimeter();
  interrupts();
}


void ControlSystem::nextPositionLeft(void)
{
  uint16_t index=0;
  nearestIndex=UINT16_MAX;
  for (index=0;index<programMenu.program->size();index++)
  {
    float programPosition = programMenu.program->get(index);
    if (programPosition>=_currentTargetPosition_f)
    {
      break;
    }
    else
    {
      nearestIndex=index;
    }
  }
  if (nearestIndex!=UINT16_MAX)
  {
    noInterrupts();
    _currentTargetPosition_f=programMenu.program->get(nearestIndex);
    _currentTargetPosition_i32=_currentTargetPosition_f*settingMenu.getStepsPerMilimeter();
    interrupts();
  }
  else
  { // Position the blade to -bladeWidth
    noInterrupts();
    _currentTargetPosition_f=-settingMenu.getBladeWidth();
    _currentTargetPosition_i32=_currentTargetPosition_f*settingMenu.getStepsPerMilimeter();
    interrupts();
  }
  
  
}

void ControlSystem::nextPositionRight(void)
{ // Search from right to left in the positions for the next position to the current position.
  // If the current position is really near to the current one than choose the next one
  int16_t index;
  nearestIndex=UINT16_MAX;
  for (index=programMenu.program->size()-1;index>=0;index--)
  {
    float programPosition = programMenu.program->get(index);
    if (programPosition<=_currentTargetPosition_f)
    {
      break;
    }
    else
    {
      nearestIndex=index;
    }
  }
  if (nearestIndex!=UINT16_MAX)
  {
    noInterrupts();
    _currentTargetPosition_f=programMenu.program->get(nearestIndex);
    _currentTargetPosition_i32=_currentTargetPosition_f*settingMenu.getStepsPerMilimeter();
    interrupts();
  }
  else
  { // position the blade to the end of the Werkstueck
    noInterrupts();
    _currentTargetPosition_f=programMenu.getOverallLength();
    _currentTargetPosition_i32=_currentTargetPosition_f*settingMenu.getStepsPerMilimeter();
    interrupts();
    
  }
}


void ControlSystem::selectPos0(void)
{
  if (programMenu.program->size()>0)
  {
    noInterrupts();
    _currentTargetPosition_f=programMenu.program->get(0);
    _currentTargetPosition_i32=_currentTargetPosition_f*settingMenu.getStepsPerMilimeter();
    nearestIndex=0;
    interrupts();
  }
  
}

void ControlSystem::selectPosMax(void)
{
  int si=programMenu.program->size();
  if (si>0)
  {
    noInterrupts();
    _currentTargetPosition_f=programMenu.program->get(si-1);
    _currentTargetPosition_i32=_currentTargetPosition_f*settingMenu.getStepsPerMilimeter();
    nearestIndex=si-1;
    interrupts();
  }
}


void ControlSystem::ini(void)
{
  _active=false;
  pinMode(PIN_ENABLE,OUTPUT);
  pinMode(PIN_DIRECTION,OUTPUT);
  pinMode(PIN_PULSE,OUTPUT);
  
  digitalWrite(PIN_ENABLE,LOW);
  digitalWrite(PIN_DIRECTION,LOW);
  digitalWrite(PIN_PULSE,LOW);
  
  _currentFrequency=0;
  this->setZero();
}

void ControlSystem::setZero(void)
{
  _currentPosition_f=0.0f;
  _currentTargetPosition_f=0.0f;
  _currentPosition_i32=0;
  _currentTargetPosition_i32=0;
}


bool ControlSystem::toggleActivation(void)
{
  _active = !_active;
  if (_active)
  {
    digitalWrite(PIN_ENABLE,LOW);
  }
  else
  {
    digitalWrite(PIN_ENABLE,HIGH);
  }
  return _active;
}

bool ControlSystem::getActivationState(void)
{
  return _active;
}
