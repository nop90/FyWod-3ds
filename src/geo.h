//   Copyright 2010 Schnatterplatsch
//
//   This file is part of Fy.WoD!.
//
//   Fy.WoD!. is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   Fy.WoD!. is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with Fy.WoD!.  If not, see <http://www.gnu.org/licenses/>.
//


#ifndef _GEO_H
#define _GEO_H

  #ifdef __cplusplus
    extern "C" {
  #endif

  #include <stdlib.h>
  #include <stdio.h>
  #include <float.h>


  typedef struct{
    int x1,y1,x2,y2;
  }geo_sline;

  typedef struct{
    int x,y,w,h;
  }geo_srect;

  #define PI 3.141592654

  #define geoLIMITMAX DBL_MAX
  #define geoLIMITMIN -DBL_MAX

  #define geoMax( val1, val2 ) ((val1) > (val2) ? (val1) : (val2))
  #define geoMin( val1, val2 ) ((val1) < (val2) ? (val1) : (val2))

  #define geoDeg( x ) (((x)*180)/PI)
  #define geoRad( x ) (((x)*PI)/180)

  #define geoQdr( x ) ((x) * (x))

  #define geoDistance2D( x1, y1, x2, y2 ) sqrt( geoQdr( (x1) - (x2) ) + geoQdr( (y1) - (y2) ) )
  #define _geoDistance2D( x, y ) sqrt( geoQdr( x ) + geoQdr( y ) )
  #define geoDirection2D( x1, y1, x2, y2 ) geoStandartAngle(atan2( -((y2) - (y1)) , (x2) - (x1) ))
  #define _geoDirection2D( x, y ) geoStandartAngle(atan2( -((y) - 0) , (x) - (0) ))

  #define geoDistance3D( x1, y1, z1, x2, y2, z2 ) sqrt( geoQdr( x1 - x2 ) + geoQdr( y1 - y2 ) + geoQdr( z1 - z2 ) )
  #define _geoDistance3D( x, y, z ) sqrt( geoQdr( x ) + geoQdr( y ) + geoQdr( z ) )

  #define geoUSVal( val ) ((val) > 0 ? (val) : (val) < 0 ? -(val) : 0)

  #define geoCirclecoll( x1, y1, rad1, x2, y2, rad2 ) ( geoDistance2D( (x1), (y1), (x2), (y2) ) <= (rad1) + (rad2) ? 1 : 0 )



  double geoRoundF( double , int  );
  double geoRoundV( double );

  double geoLimit(double, double, double);

  double geoStandartAngle( double );
  double geoLineAngle( double );


  int geoRectcoll( double, double, double, double, double, double, double, double  );
  geo_srect *geoCutrect( double, double, double, double, double, double, double, double  );
  int geoLinecoll( double, double, double, double, double, double, double, double );
  int geoRectCirclecoll( double, double, double, double, double, double, double );



  int geoSign( double );

  #ifdef __cplusplus
    }
  #endif


#endif
