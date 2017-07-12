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


#ifndef _INI_H
#define _INI_H



  #ifdef __cplusplus
    extern "C" {
  #endif

  #define INI_BUFFER (65536 + 1)

  #include "ctype.h"
  #include <stdio.h>

  typedef struct
  {
    char *buffer;
  }iniStream;

  void iniInit();

  iniStream *iniLoad( char * );
  void iniClose( iniStream * );

  long iniSearch( iniStream *, char *, char *, long * );

  long iniGetMark( iniStream *, long, char *,int);

  int iniGetInt(  iniStream *, char *, char *, int );
  double iniGetDouble(  iniStream *, char *, char *, double );
  char iniGetChar(  iniStream *, char *, char *, char );
  char *iniGetStr(  iniStream *, char *, char *, char* );

  int iniNSections(  iniStream *, char * );
  int iniNKeys( iniStream *, char *, char * );
  int iniSection(  iniStream *, char * );
  int iniKey(  iniStream *, char *, char * );

  #ifdef __cplusplus
    }
  #endif

#endif

