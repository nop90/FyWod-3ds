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

#ifndef _SFX_H
#define _SFX_H

  #define _SFX_ON

  #ifdef _SFX_ON

    #include <SDL/SDL_mixer.h>

    #include "control.h"
    #include "geo.h"

    #define sfxVOLUMESTEP 2

    #define sfxCHANNELS 16

    double sfxVolume;


    void sfxInit();

    Mix_Chunk *sfxLoadWAV( char * );
    int sfxGetFreeChannel();
    int sfxPlaySFX( Mix_Chunk * );
    void sfxControlVolume();
    int sfxChunkPlaying( Mix_Chunk * );

  #else

    #define sfxInit()
    #define sfxLoadWAV( val ) NULL
    #define sfxGetFreeChannel() 0
    #define sfxPlaySFX( val ) 0
    #define sfxControlVolume()
    #define sfxChunkPlaying( val ) 0

    #define Mix_Chunk void


  #endif


#endif
