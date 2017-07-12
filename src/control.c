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


#include "control.h"

void cntrlInit()
{

  cntrl_joystick = SDL_JoystickOpen(0);
  if( cntrl_joystick == NULL )
    fprintf( stderr, "Could not initialize SDL_Joystick: %s.\n" , SDL_GetError() );

  cntrl_key.up.newpressed = 0;
  cntrl_key.down.newpressed = 0;
  cntrl_key.left.newpressed = 0;
  cntrl_key.right.newpressed = 0;
  cntrl_key.a.newpressed = 0;
  cntrl_key.b.newpressed = 0;
  cntrl_key.x.newpressed = 0;
  cntrl_key.y.newpressed = 0;
  cntrl_key.shleft.newpressed = 0;
  cntrl_key.shright.newpressed = 0;
  cntrl_key.vup.newpressed = 0;
  cntrl_key.vdown.newpressed = 0;
  cntrl_key.menu.newpressed = 0;
  cntrl_key.select.newpressed = 0;

  cntrl_key.up.released = 0;
  cntrl_key.down.released = 0;
  cntrl_key.left.released = 0;
  cntrl_key.right.released = 0;
  cntrl_key.a.released = 0;
  cntrl_key.b.released = 0;
  cntrl_key.x.released = 0;
  cntrl_key.y.released = 0;
  cntrl_key.shleft.released = 0;
  cntrl_key.shright.released = 0;
  cntrl_key.vup.released = 0;
  cntrl_key.vdown.released = 0;
  cntrl_key.menu.released = 0;
  cntrl_key.select.released = 0;

  cntrl_key.up.pressed = 0;
  cntrl_key.down.pressed = 0;
  cntrl_key.left.pressed = 0;
  cntrl_key.right.pressed = 0;
  cntrl_key.a.pressed = 0;
  cntrl_key.b.pressed = 0;
  cntrl_key.x.pressed = 0;
  cntrl_key.y.pressed = 0;
  cntrl_key.shleft.pressed = 0;
  cntrl_key.shright.pressed = 0;
  cntrl_key.vup.pressed = 0;
  cntrl_key.vdown.pressed = 0;
  cntrl_key.menu.pressed = 0;
  cntrl_key.select.pressed = 0;

  cntrl_key.mouse.x = 0;
  cntrl_key.mouse.y = 0;
  cntrl_key.mouse.newpressed = 0;
  cntrl_key.mouse.released = 0;
  cntrl_key.mouse.pressed = 0;

  printf("'cntrlInit()' done!\n");

}

void cntrlUpdate()
{


  unsigned char *predkey = SDL_GetKeyState (NULL);
  unsigned char *dkey = SDL_GetKeyState (NULL);

  Uint8 mousestate = SDL_GetMouseState( &cntrl_key.mouse.x, &cntrl_key.mouse.y );

    dkey[ _KEY_UP ] = predkey[ _KEY_UP ];
    dkey[ _KEY_DOWN ] = predkey[ _KEY_DOWN ];
    dkey[ _KEY_LEFT ] = predkey[ _KEY_LEFT ];
    dkey[ _KEY_RIGHT ] = predkey[ _KEY_RIGHT ];
    dkey[ _KEY_A ] = predkey[ _KEY_A ];
    dkey[ _KEY_B ] = predkey[ _KEY_B ];
    dkey[ _KEY_X ] = predkey[ _KEY_X ];
    dkey[ _KEY_Y ] = predkey[ _KEY_Y ];
    dkey[ _KEY_SHLEFT ] = predkey[ _KEY_SHLEFT ];
    dkey[ _KEY_SHRIGHT ] = predkey[ _KEY_SHRIGHT ];
    dkey[ _KEY_VUP ] = predkey[ _KEY_VUP ];
    dkey[ _KEY_VDOWN ] = predkey[ _KEY_VDOWN ];
    dkey[ _KEY_MENU ] = predkey[ _KEY_MENU ];
    dkey[ _KEY_SELECT ] = predkey[ _KEY_SELECT ];


	while ( SDL_PollEvent(&cntrl_event) ){
	  switch( cntrl_event.type ) {
	    case SDL_QUIT:
        exit( 0 );
        break;
	  }
  }

  #ifndef GP2X
    if( predkey[ SDLK_ESCAPE ] ) exit( 0 );
  #endif


  cntrl_key.up.newpressed = !cntrl_key.up.pressed && dkey[ _KEY_UP ];
  cntrl_key.down.newpressed = !cntrl_key.down.pressed && dkey[ _KEY_DOWN ];
  cntrl_key.left.newpressed = !cntrl_key.left.pressed && dkey[ _KEY_LEFT ];
  cntrl_key.right.newpressed = !cntrl_key.right.pressed && dkey[ _KEY_RIGHT ];
  cntrl_key.a.newpressed = !cntrl_key.a.pressed && dkey[ _KEY_A ];
  cntrl_key.b.newpressed = !cntrl_key.b.pressed && dkey[ _KEY_B ];
  cntrl_key.x.newpressed = !cntrl_key.x.pressed && dkey[ _KEY_X ];
  cntrl_key.y.newpressed = !cntrl_key.y.pressed && dkey[ _KEY_Y ];
  cntrl_key.shleft.newpressed = !cntrl_key.shleft.pressed && dkey[ _KEY_SHLEFT ];
  cntrl_key.shright.newpressed = !cntrl_key.shright.pressed && dkey[ _KEY_SHRIGHT ];
  cntrl_key.vup.newpressed = !cntrl_key.vup.pressed && dkey[ _KEY_VUP ];
  cntrl_key.vdown.newpressed = !cntrl_key.vdown.pressed && dkey[ _KEY_VDOWN ];
  cntrl_key.menu.newpressed = !cntrl_key.menu.pressed && dkey[ _KEY_MENU ];
  cntrl_key.select.newpressed = !cntrl_key.select.pressed && dkey[ _KEY_SELECT ];

  cntrl_key.up.released = cntrl_key.up.pressed && !dkey[ _KEY_UP ];
  cntrl_key.down.released = cntrl_key.down.pressed && !dkey[ _KEY_DOWN ];
  cntrl_key.left.released = cntrl_key.left.pressed && !dkey[ _KEY_LEFT ];
  cntrl_key.right.released = cntrl_key.right.pressed && !dkey[ _KEY_RIGHT ];
  cntrl_key.a.released = cntrl_key.a.pressed && !dkey[ _KEY_A ];
  cntrl_key.b.released = cntrl_key.b.pressed && !dkey[ _KEY_B ];
  cntrl_key.x.released = cntrl_key.x.pressed && !dkey[ _KEY_X ];
  cntrl_key.y.released = cntrl_key.y.pressed && !dkey[ _KEY_Y ];
  cntrl_key.shleft.released = cntrl_key.shleft.pressed && !dkey[ _KEY_SHLEFT ];
  cntrl_key.shright.released = cntrl_key.shright.pressed && !dkey[ _KEY_SHRIGHT ];
  cntrl_key.vup.released = cntrl_key.vup.pressed && !dkey[ _KEY_VUP ];
  cntrl_key.vdown.released = cntrl_key.vdown.pressed && !dkey[ _KEY_VDOWN ];
  cntrl_key.menu.released = cntrl_key.menu.pressed && !dkey[ _KEY_MENU ];
  cntrl_key.select.released = cntrl_key.select.pressed && !dkey[ _KEY_SELECT ];

  cntrl_key.up.pressed = dkey[ _KEY_UP ];
  cntrl_key.down.pressed = dkey[ _KEY_DOWN ];
  cntrl_key.left.pressed = dkey[ _KEY_LEFT ];
  cntrl_key.right.pressed = dkey[ _KEY_RIGHT ];
  cntrl_key.a.pressed = dkey[ _KEY_A ];
  cntrl_key.b.pressed = dkey[ _KEY_B ];
  cntrl_key.x.pressed = dkey[ _KEY_X ];
  cntrl_key.y.pressed = dkey[ _KEY_Y ];
  cntrl_key.shleft.pressed = dkey[ _KEY_SHLEFT ];
  cntrl_key.shright.pressed = dkey[ _KEY_SHRIGHT ];
  cntrl_key.vup.pressed = dkey[ _KEY_VUP ];
  cntrl_key.vdown.pressed = dkey[ _KEY_VDOWN ];
  cntrl_key.menu.pressed = dkey[ _KEY_MENU ];
  cntrl_key.select.pressed = dkey[ _KEY_SELECT ];

  sfxControlVolume();
}
