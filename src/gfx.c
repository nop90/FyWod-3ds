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

#include "gfx.h"

void gfx_Init( int w, int h, int bpp, int fs, int fps )
{

  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO  ) < 0 )
    fprintf( stderr, "Could not initialize SDL: %s.\n" , SDL_GetError() );



  gfx_screen = SDL_SetVideoMode( w, h, bpp, SDL_DOUBLEBUF | SDL_SWSURFACE | ( fs ? SDL_FULLSCREEN : 0 ) );
    if( gfx_screen == NULL )
      fprintf( stderr, "Could not initialize SDL_Video: %s.\n" , SDL_GetError() );

  gfx_fpsmanager = malloc( sizeof( FPSmanager ) );
    SDL_initFramerate( gfx_fpsmanager );
    SDL_setFramerate( gfx_fpsmanager, fps );

  printf("'gfxInit()' done!\n");

}


SDL_Surface *gfxLoadBMP( char *path )
{

  SDL_Surface *prebmp, *finbmp;

  prebmp = SDL_LoadBMP( path );
    if( prebmp == NULL){
      fprintf( stderr, "ERROR! 'gLoadBMP()' failed loading '%s' !\n", path);
      return NULL;
    }

  finbmp = SDL_DisplayFormat( prebmp );
  SDL_FreeSurface( prebmp );
  SDL_SetColorKey( finbmp, SDL_SRCCOLORKEY, SDL_MapRGB( finbmp->format, 255, 0, 128 ) );

  return finbmp;

}



gfx_sanimation *gfxLoadAnimation( char *path )
{

  char section[64];
  int frame;

  iniStream *stream = iniLoad( path );


    //------------------------Path and malloc()--------------------------//
      gfx_sbanimation *banimation = malloc( sizeof( gfx_sbanimation ) );


    //----------------------------Load frames----------------------------//

      banimation->frames = iniNSections( stream, "frame" );
      banimation->frame = calloc( banimation->frames, sizeof( void * ) );

      for( frame = 0; frame < banimation->frames; frame ++ )
      {
        banimation->frame[frame] = malloc( sizeof( gfx_sframe ) );

        sprintf( section, "frame%i", frame );

        banimation->frame[frame]->blitrect.x = iniGetInt( stream, section, "x", 0 );
        banimation->frame[frame]->blitrect.y = iniGetInt( stream, section, "y", 0 );
        banimation->frame[frame]->blitrect.w = iniGetInt( stream, section, "w", 0 );
        banimation->frame[frame]->blitrect.h = iniGetInt( stream, section, "h", 0 );

        banimation->frame[frame]->time = iniGetInt( stream, section, "time", 1 );
      }

    //------------------------------Load BMP-----------------------------//
        banimation->bmp = gfxLoadBMP( iniGetStr( stream, "ani", "path", "ERROR!" ) );



  gfx_sanimation *animation = malloc( sizeof( gfx_sanimation ) );
    animation->cframe = 0;
    animation->banimation = banimation;

  return animation;

}


void gfxDrawSprite( SDL_Surface *surface, SDL_Surface *bmp, SDL_Rect *blitrect, int x, int y )
{

  if( bmp == NULL || surface == NULL) return;

  if( blitrect == NULL )
  {
    blitrect = (SDL_Rect *) malloc( sizeof(SDL_Rect) );
    blitrect->x = 0;
    blitrect->y = 0;
    blitrect->w = bmp->w;
    blitrect->h = bmp->h;
  }

  //----------------------------------------------------------------//
  //Control data for correctness
  //----------------------------------------------------------------//
    double dstx, dsty;
    long dstw, dsth;

    dstx = x;
    dsty = y;
    dstw = geoLimit( blitrect->w, 0, surface->w - dstx );
    dsth = geoLimit( blitrect->h, 0, surface->h - dsty );

    if( !geoRectcoll( dstx, dsty, dstw, dsth, 0, 0, surface->w, surface->h ) ) return;


    double bltx, blty;
    long bltw, blth;

    if( surface->w - dstx < 0 || surface->h - dsty < 0 ) return;


  //----------------------------------------------------------------//
  //Correct dst and blitrect
  //----------------------------------------------------------------//
    SDL_Rect dst, src;
      dst.x = dstx;
      dst.y = dsty;
      dst.w = dstw;
      dst.h = dsth;

      src.x = blitrect->x;
      src.y = blitrect->y;
      src.w = geoLimit( blitrect->w, 0, surface->w - dstx );
      src.h = geoLimit( blitrect->h, 0, surface->h - dsty );


  SDL_BlitSurface( bmp, &src, surface, &dst);

}


void gfxDrawAnimation( SDL_Surface *surface, gfx_sanimation *animation, int x, int y )
{

  if( animation == NULL || animation->banimation == NULL || animation->banimation->frames == 0 ) return;


  gfxDrawSprite(
    surface,
    animation->banimation->bmp,
    &animation->banimation->frame[(int) animation->cframe]->blitrect,
    x, y
    );

}

void gfxShowScreen()
{
  char string[512];

  sprintf( string, "%i", SDL_framerateDelay( gfx_fpsmanager ) );//stringColor(gfx_screen, 0, 100, string, 0xffffffff);
  SDL_Flip( gfx_screen );
  SDL_FillRect( gfx_screen, NULL, 0 );

}


void gfxDrawRectangle( SDL_Surface *surface, int x, int y, int w, int h, Uint32 color )
{
  rectangleColor( surface, x, y, x + w - 1, y + h - 1, color );
}

void gfxDrawFilledRectangle( SDL_Surface *surface, int x, int y, int w, int h, Uint32 color )
{
  boxColor( surface, x, y, x + w - 1, y + h - 1, color);
}

void gfxDrawCircle( SDL_Surface *surface, int x, int y, int rad, Uint32 color )
{
  circleColor( surface, x, y, rad, color);
}

void gfxDrawFilledCircle( SDL_Surface *surface, int x, int y, int rad, Uint32 color )
{
  filledCircleColor( surface, x, y, rad, color);
}


void gfxDrawLine( SDL_Surface *surface, int x1, int y1, int x2, int y2, Uint32 color )
{
  lineColor( surface, x1, y1, x2, y2, color);
}

void gfxDrawPixel( SDL_Surface *surface, int x, int y, Uint32 color )
{
  pixelColor( surface, x, y, color);
}

int gfxPrintStringBox( SDL_Surface *surface, int x, int y, int w, int h, char *string, Uint32 color )
{
  int cy, cx, len;
  char *cc, *lz;

  cx = x;
  cy = y;
  cc = string;

  while( cc < string + strlen( string ) * sizeof( char ) )
  {
    lz = strchr( cc, ' ' ); if( lz == NULL ) break;
    len = (long)lz - (long)cc;

    if( cx + len*8+8 >= x + w )
    {
      cx = x;
      cy += 10;
    }

    string[(long)lz - (long)string] = '\0';
      stringColor( surface, cx, cy, cc, color );
      cx += (strlen(cc)+1) * 8;
    string[(long)lz - (long)string] = ' ';

    cc = lz + 1;
  }


  return cy + 10;
}


void gfxAnimate( gfx_sanimation *animation )
{

  if( animation == NULL || animation->banimation == NULL || animation->banimation->frames == 0 ) return;

  animation->cframe += (double) 1 / animation->banimation->frame[ (int) animation->cframe ]->time;
  if( animation->cframe >= animation->banimation->frames ) animation->cframe = 0;

}



Uint32 gfxRGB( int r, int g, int b )
{

  return SDL_MapRGB( gfx_screen->format, geoLimit( r, 0, 255 ), geoLimit( g, 0, 255 ), geoLimit( b, 0, 255 ) );

}


Uint32 gfxGetPixel( SDL_Surface *surface, int x, int y )
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
      case 1:
          return *p;

      case 2:
          return *(Uint16 *)p;

      case 3:
          if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
              return p[0] << 16 | p[1] << 8 | p[2];
          else
              return p[0] | p[1] << 8 | p[2] << 16;

      case 4:
          return *(Uint32 *)p;

      default:
          return 0;       /* shouldn't happen, but avoids warnings */
    }
}

