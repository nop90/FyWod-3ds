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


#ifndef _CONTROL_H
#define _CONTROL_H

  #ifdef __cplusplus
    extern "C" {
  #endif

  #include <stdio.h>
  #include <stdlib.h>
  #include <SDL/SDL.h>

  #include "sfx.h"

     enum KEYLIST
    {
      _KEY_UP  = SDLK_UP,
      _KEY_UP_LEFT = SDLK_UP ,
      _KEY_LEFT = SDLK_LEFT ,
      _KEY_DOWN_LEFT = SDLK_LEFT ,
      _KEY_DOWN = SDLK_DOWN ,
      _KEY_DOWN_RIGHT = SDLK_DOWN ,
      _KEY_RIGHT = SDLK_RIGHT ,
      _KEY_UP_RIGHT = SDLK_RIGHT ,
      _KEY_MENU = SDLK_RETURN ,
      _KEY_SELECT = SDLK_ESCAPE ,
      _KEY_SHLEFT = SDLK_l ,
      _KEY_SHRIGHT = SDLK_r ,
      _KEY_A = SDLK_a ,
      _KEY_B = SDLK_b ,
      _KEY_X = SDLK_x ,
      _KEY_Y = SDLK_y ,
      _KEY_VUP = SDLK_KP_PLUS,
      _KEY_VDOWN = SDLK_KP_MINUS
    };

 
  struct cntrlKeyEvent
  {

    int pressed;
    int newpressed, released;

  };

  struct cntrlMouseEvent
  {

    int x,y;
    int pressed;
    int newpressed, released;

  };

  struct
  {

    struct cntrlKeyEvent up, right, down, left ;
    struct cntrlKeyEvent y, b, x, a;
    struct cntrlKeyEvent shleft, shright;
    struct cntrlKeyEvent menu, select;
    struct cntrlKeyEvent vdown, vup;

    struct cntrlMouseEvent mouse;

  }cntrl_key;

  SDL_Joystick *cntrl_joystick;
  SDL_Event cntrl_event;


  void cntrlInit();
  void cntrlUpdate();

  #ifdef __cplusplus
    }
  #endif

#endif
