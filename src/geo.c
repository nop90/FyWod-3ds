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

#include "geo.h"

double geoRoundF( double var, int fl )
{

  var = var * pow( 10, fl );
  var = (int) var;
  var = var / pow( 10, fl );

  return var;

}

double geoRoundV( double val )
{

  if( geoUSVal(val) >= (int)geoUSVal(val) + 0.5  )
  {
    return ((int)geoUSVal(val) + 1) * geoSign(val);
  }
  else
  {
    return (int) val;
  }

}

double geoLimit( double var,double min, double max ){

  if( max < min ) return var;
  if( var > max ) return max;
  if( var < min ) return min;
  return var;

}


int geoRectcoll( double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2 )
{

  double xl,xr,yo,yu;


	if( x2 < x1 ) xl = x2; else xl = x1;
	if( y2 < y1 ) yo = y2; else yo = y1;
	if( x1 + w1 > x2 + w2 )  xr = x1 + w1;  else  xr = x2 + w2;
	if( y1 + h1 > y2 + h2 )  yu = y1 + h1;  else  yu = y2 + h2;


	if( (w1 + w2 > xr - xl) && (h1 + h2 > yu - yo) )
	{
    return 1;
	}

	return 0;

}

geo_srect *geoCutrect( double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2 )
{

  double xl,xr,yo,yu;

	if( x2 < x1 ) xl = x2; else xl = x1;
	if( y2 < y1 ) yo = y2; else yo = y1;
	if( x1 + w1 > x2 + w2 )  xr = x1 + w1;  else  xr = x2 + w2;
	if( y1 + h1 > y2 + h2 )  yu = y1 + h1;  else  yu = y2 + h2;


	if( (w1 + w2 > xr - xl) && (h1 + h2 > yu - yo) )
	{
    geo_srect *srect = malloc( sizeof( geo_srect ) );
      srect->x = geoMax( x1, x2 );
      srect->y = geoMax( y1, y2 );
      srect->w = geoMin( x1 + w1, x2 + w2 ) - srect->x;
      srect->h = geoMin( y1 + h1, y2 + h2 ) - srect->y;

    return srect;
	}

	return NULL;
}



int geoLinecoll( double l1x1, double l1y1, double l1x2, double l1y2, double l2x1, double l2y1, double l2x2, double l2y2 )
{

	double a, b, n1, n2, sx, sy;
	double smx1, bix1, smx2, bix2;

	if (abs(l1x1 - l1x2) < 0.1 ) l1x1++;
	if(abs(l2x1 - l2x2) < 0.1) l2x1++;

	a  = (l1y2 - l1y1) / (l1x1 - l1x2);
	n1 =  l1y1 + (a * l1x1);

	b  = (l2y2 - l2y1) / (l2x1 - l2x2);
	n2 =  l2y1 + (b * l2x1);

	sx = -(n2 - n1) / (a - b);
	sy = (a * sx) - n1;


	if(l1x1 > l1x2)
	{
		smx1 = l1x2;
		bix1 = l1x1;
	}
	else
	{
		smx1 = l1x1;
		bix1 = l1x2;
	}

	if(l2x1 > l2x2)
	{
		smx2 = l2x2;
		bix2 = l2x1;
	}
	else
	{
		smx2 = l2x1;
		bix2 = l2x2;
	}


	if(sx >= smx1 && sx <= bix1 && sx >= smx2 && sx <= bix2)
	{
		return 1;
	}
	else
	{
		return 0;
	}


}


int geoRectCirclecoll( double x1, double y1, double w1, double h1, double x2, double y2, double rad2 )
{
  if( geoRectcoll( x1, y1, w1, h1, x2, y2, 1, 1 ) ) return 1;

  if( x2 >= x1 && x2 <= x1 + w1 ) if( geoUSVal(y1 - y2) <= rad2 || geoUSVal(y1 + h1 - y2) <= rad2 ) return 1; else return 0;
  if( y2 >= y1 && y2 <= y1 + h1 ) if( geoUSVal(x1 - x2) <= rad2 || geoUSVal(x1 + w1 - x2) <= rad2 ) return 1; else return 0;

  if( x2 <= x1 && y2 <= y1 ) if( geoDistance2D( x1, y1, x2, y2 ) <= rad2 ) return 1; else return 0;
  if( x2 >= x1 + w1 && y2 <= y1 ) if( geoDistance2D( x1 + w1, y1, x2, y2 ) <= rad2 ) return 1; else return 0;
  if( x2 >= x1 + w1 && y2 >= y1 + h1 ) if( geoDistance2D( x1 + w1, y1 + h1, x2, y2 ) <= rad2 ) return 1; else return 0;
  if( x2 <= x1 && y2 >= y1 + h1 ) if( geoDistance2D( x1, y1 + h1, x2, y2 ) <= rad2 ) return 1; else return 0;

  return 0;

}



double geoLineAngle( double angle )
{

	angle = geoStandartAngle( angle );
    if( angle >= PI ) angle -= PI;

	return angle;

}


double geoStandartAngle( double angle )
{

	while( (angle >= 2 * PI) || (angle < 0) )
	{
		if( angle >= 2 * PI) angle -= 2 * PI;
		if( angle <  0) angle += 2 * PI;
	}

	return angle;

}


int geoSign( double var )
{

  if( var > 0 ) return 1;
  if( var == 0) return 0;
  return -1;

}




