/*
 * LicenseLineInfo.cpp
 *
 *  Created on: 29.12.2016
 *      Author: eckar
 */

#include "LicenseLineInfo.h"

// empty

bool LicenseLineInfo:: operator<(const LicenseLineInfo& other)
{
  return start < other.start;
}

bool LicenseLineInfo:: operator>(const LicenseLineInfo& other)
{
  return start > other.start;
}

bool LicenseLineInfo:: operator ==(const LicenseLineInfo& other)
{
  return start == other.start;
}

bool LicenseLineInfo:: operator <=(const LicenseLineInfo& other)
{
  return start <= other.start;
}

bool LicenseLineInfo:: operator >=(const LicenseLineInfo& other)
{
  return start >= other.start;
}

