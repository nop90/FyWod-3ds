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


#ifndef _GFX_H
#define _GFX_H

  #ifdef __cplusplus
    extern "C" {
  #endif

  #include <stdio.h>
  #include <stdlib.h>
  #include <SDL/SDL.h>

  #include "SDLgfx/SDLgfx.h"

  #include "ini.h"
  #include "geo.h"
  #include "control.h"



  typedef struct
  {

    int time;
    SDL_Rect blitrect;

  }gfx_sframe;

  typedef struct
  {

    int frames;
    SDL_Surface *bmp;
    gfx_sframe **frame;

  }gfx_sbanimation;

  typedef struct
  {

    double cframe;
    gfx_sbanimation *banimation;

  }gfx_sanimation;

  SDL_Surface *gfx_screen;

  FPSmanager *gfx_fpsmanager;




  void gfx_Init( int, int, int, int, int );

  gfx_sanimation *gfxLoadAnimation( char * );
  SDL_Surface *gfxLoadBMP( char * );

  void gfxDrawSprite( SDL_Surface *, SDL_Surface *, SDL_Rect *, int, int );
  void gfxDrawAnimation( SDL_Surface *, gfx_sanimation *, int, int );
  void gfxDrawRectangle( SDL_Surface *, int, int, int, int, Uint32 );
  void gfxDrawFilledRectangle( SDL_Surface *, int, int, int, int, Uint32 );
  void gfxDrawCircle( SDL_Surface *, int, int, int, Uint32 );
  void gfxDrawFilledCircle( SDL_Surface *, int, int, int, Uint32 );
  void gfxDrawLine( SDL_Surface *, int, int, int, int, Uint32 );
  void gfxDrawPixel( SDL_Surface *, int, int, Uint32 );
  int gfxPrintStringBox( SDL_Surface *, int, int, int, int, char *, Uint32 );

  void gfxAnimate( gfx_sanimation * );

  void gfxShowScreen();

  Uint32 gfxGetPixel( SDL_Surface *, int , int );
  Uint32 gfxRGB( int, int, int );


  #ifdef __cplusplus
    }
  #endif

#endif
