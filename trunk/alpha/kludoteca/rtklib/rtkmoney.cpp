/*<<<<<COPYRIGHT*/
/*
 * RTK The report toolkit
 * Copyright (C) 2003 Francisco Santiago Capel Torres

 * rtkmoney.cpp Class to handle currency amounts
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

#include <math.h>
#include "rtkmoney.h"

using namespace RTK;

static int exp10(short int ndecimals)
{
	if( ndecimals >= 10 )
		return ndecimals;
	int r = 1;
	for( ; ndecimals>0; ndecimals-- )
		r *= 10;
	return r;
}

Money::Money(short int ndecimals)
{
	mAmount = 0;
	mCentFactor = exp10(ndecimals);
}


Money::Money(long amount, short int ndecimals)
{
  mCentFactor = exp10(ndecimals) ;
  mAmount = (long long)round(amount * mCentFactor);
}

Money::Money(long long amount, short int ndecimals)
{
  mCentFactor = exp10(ndecimals) ;
  mAmount = (long long)round(amount * mCentFactor);
}

Money::Money(double amount, short int ndecimals)
{
  mCentFactor = exp10(ndecimals) ;
  mAmount = (long long)round(amount * mCentFactor);
}

int Money::toInt() const
{
  return mAmount / mCentFactor;
}

long long Money::toLong() const
{
  return (long long)(mAmount / mCentFactor);
}


double Money::toDouble() const
{
  return (double)mAmount / (double)mCentFactor;
}

long long Money::getAmount() const
{
  return mAmount;
}

QString Money::toString() const
{
  return QString::number((double)mAmount / mCentFactor);
}

bool Money::operator==( const Money& other) const
{
  return (mAmount == other.mAmount && mCentFactor == other.mCentFactor );
}  

bool Money::operator!=( const Money& other) const
{
  return !(*this == other );
}

Money &Money::operator+=( const Money& other) 
{
  Q_ASSERT(mCentFactor == other.mCentFactor);
  mAmount += other.mAmount;
  return *this;
}

Money Money::operator+( const Money& other) const
{
  Q_ASSERT(mCentFactor == other.mCentFactor);
  return Money((double)((mAmount + other.mAmount))/(double)mCentFactor, mCentFactor);   
}

Money Money::operator-( const Money& other) const
{
  Q_ASSERT(mCentFactor == other.mCentFactor);
  return Money((double)((mAmount - other.mAmount))/(double)mCentFactor, mCentFactor);
}

Money Money::operator*( const Money& other) const
{
  Q_ASSERT(mCentFactor == other.mCentFactor);
  return Money( (double)(mAmount * other.mAmount)
          / (double)mCentFactor
          / (double)mCentFactor,
          mCentFactor);
}


Money Money::operator/( const Money& other) const
{
  Q_ASSERT(mCentFactor == other.mCentFactor);
  return Money( (double)(mAmount / other.mAmount)
          / (double)mCentFactor
          / (double)mCentFactor,
          mCentFactor);
}

bool Money::operator<( const Money& other) const
{
  Q_ASSERT(mCentFactor == other.mCentFactor);
  return mAmount < other.mAmount;
}

bool Money::operator<=( const Money& other) const
{
  Q_ASSERT(mCentFactor == other.mCentFactor);
  return mAmount <= other.mAmount;
}

bool Money::operator>( const Money& other) const
{
  Q_ASSERT(mCentFactor == other.mCentFactor);
  return mAmount > other.mAmount;
}

bool Money::operator>=( const Money& other) const
{
  Q_ASSERT(mCentFactor == other.mCentFactor);
  return mAmount < other.mAmount;
}

