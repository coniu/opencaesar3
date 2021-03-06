// This file is part of openCaesar3.
//
// openCaesar3 is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// openCaesar3 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with openCaesar3.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __OPENCAESAR3_CITYFUNDS_H_INCLUDED__
#define __OPENCAESAR3_CITYFUNDS_H_INCLUDED__

#include "oc3_scopedptr.hpp"
#include "oc3_variant.hpp"
#include "oc3_signals.hpp"
#include "oc3_enums.hpp"
#include "oc3_predefinitions.hpp"

struct FundIssue
{
  int type;
  int money;

  FundIssue() : type( 0 ), money( 0 ) {}
  FundIssue( int t, int m ) : type( t ), money( m ) {}

  static void resolve( CityPtr city, int type, int money );
  static void importGoods( CityPtr city, GoodType type, int qty );
  static void exportGoods( CityPtr city, GoodType type, int qty );
};

class CityFunds
{
public:
  enum IssueType { unknown=0, taxIncome=1, 
                   exportGoods, donation, 
                   importGoods, workersWages, 
                   buildConstruction, creditPercents, 
                   playerSalary, otherExpenditure,
                   empireTax, debet, credit, profit,
                   balance,
                   issueTypeCount };
  enum { thisYear=0, lastYear=1 };

  CityFunds();
  ~CityFunds();

  void resolveIssue( FundIssue issue );

  void updateHistory( const DateTime& date );

  int getIssueValue( IssueType type, int age=thisYear ) const;

  int getValue() const;

  VariantMap save() const;
  void load( const VariantMap& stream );

oc3_signals public:
  Signal1<int>& onChange();

private:
  class Impl;
  ScopedPtr< Impl > _d;
};

#endif //__OPENCAESAR3_CITYFUNDS_H_INCLUDED__