/*
 * LicenseLineInfo.h
 *
 *  Created on: 29.12.2016
 *      Author: eckar
 */

#ifndef LICENSELINEINFO_H_
#define LICENSELINEINFO_H_

class LicenseLineInfo
{
  public:
    int start, length;

  public:
    LicenseLineInfo()
        : start { 0 }, length { 0 }
    {
    }
    ;
    LicenseLineInfo(int start, int length)
        : start { start }, length { length }
    {
    }
    ;
    virtual ~LicenseLineInfo()
    {
    }
    ;

    bool operator >(const LicenseLineInfo&);
    bool operator <(const LicenseLineInfo&);
    bool operator <=(const LicenseLineInfo&);
    bool operator >=(const LicenseLineInfo&);
    bool operator ==(const LicenseLineInfo&);
};

#endif /* LICENSELINEINFO_H_ */
