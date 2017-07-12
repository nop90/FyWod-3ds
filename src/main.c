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


#include "main.h"
#include <3ds.h>

void terminate()
{
  fclose( stdout );
  fclose( stderr );
  romfsExit();
  SDL_Quit();
}

int main( int argc, char** argl )
{

// In case game dir doesn't exist
  mkdir("/3ds", 0777);
  mkdir("/3ds/FyWod", 0777);
  romfsInit();
  gfx_Init( 320, 240 , 16, 1, 60 );
  atexit( terminate );
  sfxInit();
  cntrlInit();

  SDL_ShowCursor( SDL_DISABLE );

  SDL_N3DSKeyBind(KEY_CPAD_UP|KEY_CSTICK_UP, SDLK_UP);
  SDL_N3DSKeyBind(KEY_CPAD_DOWN|KEY_CSTICK_DOWN, SDLK_DOWN);
  SDL_N3DSKeyBind(KEY_CPAD_LEFT|KEY_CSTICK_LEFT, SDLK_LEFT);
  SDL_N3DSKeyBind(KEY_CPAD_RIGHT|KEY_CSTICK_RIGHT, SDLK_RIGHT);

  gfxDrawSprite( gfx_screen, gfxLoadBMP( "romfs:/game/gfx/etc/splash.bmp"), NULL, gfx_screen->w/2 - 160, gfx_screen->h/2 - 120  );
  gfxShowScreen();
  SDL_Delay( 3000 );

  game();
  
  terminate();

  return 0;
}
