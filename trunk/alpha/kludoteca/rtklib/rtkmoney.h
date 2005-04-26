/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkmoney.h Class to handle currency amounts
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
/*>>>>>COPYRIGHT*/

#ifndef RTKMONEY_H
#define RTKMONEY_H


/**
  *@author Francisco Santiago Capel Torres
  */

#include <qstring.h>

namespace RTK
{

class Money
{
public:
        Money(short int ndecimals =2);
        Money(long long amount, short int ndecimals =2);
        Money(long amount, short int ndecimals =2);
        Money(double amount, short int ndecimals =2);
		
        QString toString() const;
        int toInt() const;
        double toDouble() const;
        long long toLong() const;

        bool operator==( const Money& other) const;
        bool operator!=( const Money& other) const;
        bool operator<( const Money& other) const;
        bool operator<=( const Money& other) const;
        bool operator>( const Money& other) const;
        bool operator>=( const Money& other) const;
        Money &operator+=( const Money& other);
        Money operator+( const Money& other) const;
        Money operator-( const Money& other) const;
        Money operator*( const Money& other) const;
        Money operator/( const Money& other) const;

private:
        long long mAmount;
		int mCentFactor;
        long long getAmount() const;
};

}; // namespace

#endif
