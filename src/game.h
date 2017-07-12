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

#ifndef _GAME_HPP
#define _GAME_HPP

  #include <stdio.h>
  #include <stdlib.h>
  #include <time.h>
  #include <dirent.h>
  #include <errno.h>

  #include "gfx.h"
  #include "control.h"
  #include "geo.h"
  #include "ini.h"
  #include "sfx.h"

  #define SAVEDATA "/3ds/FyWod/FyWod.sav"

  #define MAINMENUCAMERAMAXRANGE 700
  #define MAINMENUCAMERAMINRANGE 200
  #define MAINMENUCAMERASPEED 1
  #define MAINMENUTIPSPEED 1.5

  #define MAINMAPMAPRADIUS 12
  #define MAINMAPMARKRADIUS (MAINMAPMAPRADIUS/3)

  #define MAPSTARTCOUNTDELAY 45

  #define COIN '$'
  #define SPEEDUP '+'
  #define SLOWDOWN '-'
  #define KILLER '#'
  #define PSTART '>'
  #define PFINISH '<'

  #define BLOCKAXIS 24

  #define BLOCKTYPES 4
  #define BLOCKTYP( c ) ( (c) == 'R' ? 0 : (c) == 'G' ? 1 : (c) == 'B' ? 2 : (c) == 'W' ? 3 : -1 )
  #define _BLOCKTYP( x, y ) (((x) >= 0) && ((x) < lvl.w) && ((y) >= 0) && ((y) < lvl.h) ? BLOCKTYP( lvl.block[(x)][(y)] ) :-1)
  #define BLOCKSCREENPOS( px, py ) ((px)*BLOCKAXIS - camera.x + gfx_screen->w/2), ((py)*BLOCKAXIS - camera.y + gfx_screen->h/2)
  #define BLOCKPOS( px, py ) ((px)*BLOCKAXIS), ((py)*BLOCKAXIS)

  #define SCREENPOS( px, py ) ((px) - camera.x + gfx_screen->w/2), ((py) - camera.y + gfx_screen->h/2)

  #define ISBLOCK( c ) ( (c) == 'R' || (c) == 'G' || (c) == 'B' || (c) == 'W' ? 1 : 0 )
  #define ISCOIN( c ) ( (c) == COIN ? 1 : 0 )
  #define ISSPEEDUP( c ) ( (c) == SPEEDUP ? 1 : 0 )
  #define ISSLOWDOWN( c ) ( (c) == SLOWDOWN ? 1 : 0 )
  #define ISKILLER( c ) ( (c) == KILLER ? 1 : 0 )
  #define ISPSTART( c ) ( (c) == PSTART ? 1 : 0 )
  #define ISPFINISH( c ) ( (c) == PFINISH ? 1 : 0 )

  #define BLOCKFRAMES 1
  #define COINFRAMES 5
  #define SPEEDUPFRAMES 5
  #define SLOWDOWNFRAMES 5
  #define KILLERFRAMES 2

  #define PSTARTFRAMES 1
  #define PFINISHFRAMES 1

  #define BLOCKFRAMETIME 20
  #define COINFRAMETIME 10
  #define SPEEDUPFRAMETIME 20
  #define SLOWDOWNFRAMETIME 20
  #define KILLERFRAMETIME 20
  #define PSTARTFRAMETIME 20
  #define PFINISHFRAMETIME 20

  #define PLAYERRADIUS (BLOCKAXIS/3.0)
  #define PLAYERSCREENMIDDLEX (player.x - camera.x + gfx_screen->w/2)
  #define PLAYERSCREENMIDDLEY (player.y - camera.y + gfx_screen->h/2)
  #define PLAYERSCREENMIDDLE PLAYERSCREENMIDDLEX, PLAYERSCREENMIDDLEY
  #define PLAYERMAXACC 0.09
  #define PLAYERMINACC 0.04
  #define PLAYERSLOWDOWN 0.02
  #define PLAYERCURRENTACC (((PLAYERMAXACC - PLAYERMINACC) * ((100.0 - player.fuel)/100.0) + PLAYERMINACC) * player.acc )
  #define PLAYERFUELNEED 0.01
  #define PLAYERUNCOLLSTEP 0.2
  #define PLAYERWALLHITDELAY 10
  #define PLAYERSLOWMOTIONNEED 0.1
  #define PLAYERSLOWMOTIONFACTOR 0.05
  #define PLAYEROPENDEGREES geoRoundF(geoRad(140),2)
  #define PLAYEREXTRASIZE
  #define PLAYEREXTRASIZERADIUS (PLAYERRADIUS * 1.5)
  #define PLAYERCOUNTDOWNSIZE (PLAYERRADIUS *  2.2)

  #define SPEEDUPFACTOR 1.10
  #define SLOWDOWNFACTOR 0.90

  #define SPEEDUPRADIUS BLOCKAXIS/2
  #define SLOWDOWNRADIUS BLOCKAXIS/2
  #define COINRADIUS BLOCKAXIS/2
  #define PFINISHRADIUS BLOCKAXIS/2
  #define KILLERRADIUS BLOCKAXIS/2

  #define REFLECTIONSPEED (player.mspeed/3 + 1)

  #define POINTSTIMEBRONZEMEDAL 1000
  #define POINTSTIMESILVERMEDAL 3000
  #define POINTSTIMEGOLDMEDAL 6000
  #define POINTSTIME 2
  #define POINTSWHITSBRONZEMEDAL 300
  #define POINTSWHITSSILVERMEDAL 500
  #define POINTSWHITSGOLDMEDAL 1000
  #define POINTSWHITSPERFECT 2500
  #define POINTSWHITS 100
  #define POINTSCOINSBRONZEMEDAL 300
  #define POINTSCOINSSILVERMEDAL 750
  #define POINTSCOINSGOLDMEDAL 1500
  #define POINTSCOIN 250
  #define POINTSCOINPERFECT 2000
  #define POINTSPERFECT 4000

  #define MEDALNAME( n ) ((n) == 0 ? "No" : (n) == 1 ? "BRONZE" : (n) == 2 ? "SILVER" : (n) == 3 ? "GOLD" : (n) == 4 ? "PERFECT" : "No")
  #define MEDALSPRITE( n ) ((n) == 0 ? NULL : (n) == 1 ? media.medal.bronze : (n) == 2 ? media.medal.silver : (n) == 3 ? media.medal.gold : (n) == 4 ? media.medal.perfect : NULL)
  #define MEDALSMALLSPRITE( n ) ((n) == 0 ? NULL : (n) == 1 ? media.small.bronze : (n) == 2 ? media.small.silver : (n) == 3 ? media.small.gold : (n) == 4 ? media.small.perfect : NULL)

  #define BACKGROUNDPPP 1500
  #define BACKGROUNDMINDEPT 2
  #define BACKGROUNDMAXDEPT 15

  #define ENABLE_VERSION_1_1

  enum
  {
    FAILURE_SKIP,
    FAILURE_EXITED,
    FAILURE_KILLED,
    FAILURE_OOF,
    SUCCESS,
  };


  Uint32 blockcolor[BLOCKTYPES];

  #ifdef ENABLE_VERSION_1_1
    typedef struct
    {
      char *name;
    }sqlist_map;

    struct
    {
      int maps;
      sqlist_map **map;
    }sqlist;
  #endif


  typedef struct
  {
    int x, y;
    char *name;
    int pathes;
    int *path;
    int bpathes;
    int *bpath;
    int reachable;
  }mainmap_map;

  struct
  {
    int maps;
    mainmap_map **map;
  }mainmap;



  typedef struct
  {

    int completed;

    long best_time, best_totalpoints;
    int best_whits, best_coins;

    long best_timemedal, best_totalmedal;
    int best_whitsmedal, best_coinsmedal;
  }sav_map;

  struct
  {
    sav_map **map;
    int ms_shown;
  }sav;



  struct
  {
    struct
    {
      SDL_Surface *title;
    }menu;

    struct
    {
      SDL_Surface *map;
      SDL_Surface *uncompleted;
      SDL_Surface *pathopen;
      SDL_Surface *pathblocked;
    }mainmap;



    struct
    {
      SDL_Surface *clock;
      SDL_Surface *coin;
      SDL_Surface *fuel;
      SDL_Surface *whit;
      SDL_Surface *top;
      SDL_Surface *bronze;
      SDL_Surface *silver;
      SDL_Surface *gold;
      SDL_Surface *perfect;
      SDL_Surface *sum;
    }small;

    struct
    {
      SDL_Surface *bronze;
      SDL_Surface *silver;
      SDL_Surface *gold;
      SDL_Surface *perfect;
    }medal;

    struct
    {
      Mix_Chunk *button;
      Mix_Chunk *whit;
      Mix_Chunk *coin;
      Mix_Chunk *failure;
      Mix_Chunk *success;
      Mix_Chunk *acc;
      Mix_Chunk *fly;
      Mix_Chunk *count;
    }sfx;

    struct
    {
      SDL_Surface *start;
    }etc;

    SDL_Surface **block;
    SDL_Surface *coin;
    SDL_Surface *speedup;
    SDL_Surface *slowdown;
    SDL_Surface *killer;
    SDL_Surface *pstart;
    SDL_Surface *pfinish;
  }media;



  struct
  {
    int points;

    double *x, *y;
    int *dept;

  }background;



  struct
  {
    int num, ctip, since;
    char **tip;
  }tips;




  struct
  {
    int startdirection;
    int completemedal;
    int mapid;
    int finishtyp;
    long neededtime, lastframetime;
    int coins;
    int w,h;
    char **block;


    struct
    {
      long time_max, time_bronze, time_silver, time_gold;
      int whits_max, whits_bronze, whits_silver, whits_gold;
      int coins_bronze, coins_silver, coins_gold;
      int total_bronze, total_silver, total_gold;
    }points;

    struct
    {
      long time;
      int coins, whits;

      long points;
      int medal_time, medal_coins, medal_whits, medal_total;
    }complete;

  }lvl;



  struct
  {
    double x, y;
    int startx, starty;

    double wdir;
    double mdir, mspeed;
    int acc, slowmotion;
    double rotostep;

    double fuel;
    int coins;
    int whits, lastwhit;

    int accchannel;
  }player;



  struct
  {
    double x, y;
  }camera;


  int game_mainrunning, game_levelrunning;
  int game_lastmap;
  long double game_levelframe;



  void gameMainSetup();
  void gameLoadMedia();

  void gameLoadMainmap();
  void gameLoadSidequestList();

  void gameResetSav();
  void gameLoadSav();
  void gameSaveSav();

  void gameNotBuildScreen();
  void gameMillionScreen();
  char *gameMainmap();
  void gameLoadMap( char * );
  int gameMainmenu();
  void gameNewGameScreen();
  void gameNewGameSetup();
  void gameMapSetup();
  void gameFuelmenu();
  int gamePlayerEnvColl( int *, int *, int *, int * );
  int gameBlockCornerFree( int, int, int );
  int gamePlayerSpeedUpColl();
  int gamePlayerSlowDownColl();
  int gamePlayerCoinColl();
  int gamePlayerPFinishColl();

  void gameCalculate();
  void gameDraw();

  void gameUnloadMap();
  void gameMapFinishScreen();

  void game();

  void gameGoodbyeScreen();



#endif // _GAME_HPP
