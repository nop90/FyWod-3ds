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


#include "sfx.h"

#ifdef _SFX_ON
void sfxInit()
{
  int channel;

  Mix_OpenAudio( 22050, AUDIO_S16SYS, 2, 1024);
  Mix_AllocateChannels(sfxCHANNELS);

  sfxVolume = 64;

  for( channel = 0; channel < sfxCHANNELS; channel++ )
  {
    Mix_Volume( channel, sfxVolume );
  }

}

Mix_Chunk *sfxLoadWAV( char *path )
{
  Mix_Chunk *wav = Mix_LoadWAV(path);
  Mix_VolumeChunk( wav, sfxVolume);

  return wav;

}

int sfxGetFreeChannel()
{
  int channel;
  for( channel = 0; channel < sfxCHANNELS; channel++ )
  {
    if( !Mix_Playing( channel ) ) return channel;
  }
  return 0;
}

int sfxPlaySFX( Mix_Chunk *chunk )
{
  int channel = sfxGetFreeChannel();
  Mix_PlayChannel( sfxGetFreeChannel(), chunk, 0 );
  return channel;
}

void sfxControlVolume()
{
  int channel;

  if( cntrl_key.vdown.pressed )
  {
    sfxVolume -= sfxVOLUMESTEP;
  }
  if( cntrl_key.vup.pressed )
  {
    sfxVolume += sfxVOLUMESTEP;
  }
  sfxVolume = geoLimit( sfxVolume, 0, 128 );
  for( channel = 0; channel < sfxCHANNELS; channel++ )
  {
    Mix_Volume( channel, sfxVolume );
  }
}

int sfxChunkPlaying( Mix_Chunk *chunk )
{
  int channel;
  for( channel = 0; channel < sfxCHANNELS; channel++ )
  {
    if( Mix_GetChunk(channel) == chunk && Mix_Playing(channel) ) return 1;
  }
  return 0;
}
#endif
