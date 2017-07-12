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

#include "game.h"



void gameMainSetup()
{

  int point;

  //--srand()--//
    srand( time(NULL) );

  //--Background--//
    background.points = (gfx_screen->w * gfx_screen->h) / BACKGROUNDPPP;
    background.x = calloc( background.points, sizeof(double) );
    background.y = calloc( background.points, sizeof(double) );
    background.dept = calloc( background.points, sizeof(int) );

    for( point = 0; point < background.points; point++ )
    {
      background.x[point] = rand()%gfx_screen->w;
      background.y[point] = rand()%gfx_screen->h;
      background.dept[point] = (rand()%(BACKGROUNDMAXDEPT - BACKGROUNDMINDEPT)) + BACKGROUNDMINDEPT;
    }


  //--etc--//
    blockcolor[0] = 0xff0000ff;
    blockcolor[1] = 0x00ff00ff;
    blockcolor[2] = 0x0000ffff;
    blockcolor[3] = 0xffffffff;

    game_lastmap = 0;

    game_mainrunning = 1;


  //--sqlist--//
    #ifdef ENABLE_VERSION_1_1
    sqlist.maps = 0;
    sqlist.map = NULL;
    #endif





}

void gameLoadMedia()
{
  int block, frame, tip;
  char key[64];
  iniStream *stream;



  //--Mainmenu--//
    media.menu.title = gfxLoadBMP( "romfs:/game/gfx/menu/title.bmp" );


  //--Small icons--//
    media.small.clock = gfxLoadBMP( "romfs:/game/gfx/small/clock.bmp" );
    media.small.coin = gfxLoadBMP( "romfs:/game/gfx/small/coin.bmp" );
    media.small.fuel = gfxLoadBMP( "romfs:/game/gfx/small/fuel.bmp" );
    media.small.whit = gfxLoadBMP( "romfs:/game/gfx/small/whit.bmp" );
    media.small.top = gfxLoadBMP( "romfs:/game/gfx/small/top.bmp" );
    media.small.bronze = gfxLoadBMP( "romfs:/game/gfx/small/bronze.bmp" );
    media.small.silver = gfxLoadBMP( "romfs:/game/gfx/small/silver.bmp" );
    media.small.gold = gfxLoadBMP( "romfs:/game/gfx/small/gold.bmp" );
    media.small.perfect = gfxLoadBMP( "romfs:/game/gfx/small/perfect.bmp" );
    media.small.sum = gfxLoadBMP( "romfs:/game/gfx/small/sum.bmp" );



  //--Medals--//
    media.medal.bronze = gfxLoadBMP( "romfs:/game/gfx/medal/bronze.bmp" );
    media.medal.silver = gfxLoadBMP( "romfs:/game/gfx/medal/silver.bmp" );
    media.medal.gold = gfxLoadBMP( "romfs:/game/gfx/medal/gold.bmp" );
    media.medal.perfect = gfxLoadBMP( "romfs:/game/gfx/medal/perfect.bmp" );




  //--Blocks--//
    media.block = (SDL_Surface**) calloc( BLOCKTYPES, sizeof( void* ) );

    media.block[0] = gfxLoadBMP( "romfs:/game/gfx/block/r.bmp" );
    media.block[1] = gfxLoadBMP( "romfs:/game/gfx/block/g.bmp" );
    media.block[2] = gfxLoadBMP( "romfs:/game/gfx/block/b.bmp" );
    media.block[3] = gfxLoadBMP( "romfs:/game/gfx/block/w.bmp" );





  //--blocks--//
    media.coin = gfxLoadBMP( "romfs:/game/gfx/block/c.bmp" );
    media.speedup = gfxLoadBMP( "romfs:/game/gfx/block/p.bmp" );
    media.slowdown = gfxLoadBMP( "romfs:/game/gfx/block/m.bmp" );
    media.killer = gfxLoadBMP( "romfs:/game/gfx/block/k.bmp" );
    media.pstart = gfxLoadBMP( "romfs:/game/gfx/block/ps.bmp" );
    media.pfinish = gfxLoadBMP( "romfs:/game/gfx/block/pf.bmp" );


  //--etc--//
    media.etc.start = gfxLoadBMP( "romfs:/game/gfx/etc/start.bmp" );
      SDL_SetAlpha( media.etc.start, SDL_SRCALPHA , 128);



  //--Sounds--//
    media.sfx.button = sfxLoadWAV( "romfs:/game/sfx/button.wav" );
    media.sfx.whit = sfxLoadWAV( "romfs:/game/sfx/whit.wav" );
    media.sfx.coin = sfxLoadWAV( "romfs:/game/sfx/coin.wav" );
    media.sfx.failure = sfxLoadWAV( "romfs:/game/sfx/failure.wav" );
    media.sfx.success = sfxLoadWAV( "romfs:/game/sfx/success.wav" );
    media.sfx.acc = sfxLoadWAV( "romfs:/game/sfx/acc.wav" );
    media.sfx.fly = sfxLoadWAV( "romfs:/game/sfx/fly.wav" );
    media.sfx.count = sfxLoadWAV( "romfs:/game/sfx/button.wav" );





  //--Tips--//
    stream = iniLoad( "romfs:/game/etc/tips.dat" );
      tips.num = iniNKeys( stream, "tips", "tip" );
      tips.tip = calloc( tips.num, sizeof(void*) );

      for( tip = 0; tip < tips.num; tip++ )
      {
        sprintf( key, "tip%i", tip );
        tips.tip[tip] = iniGetStr( stream, "tips", key, "ERROR!" );
      }
    iniClose( stream );




}

void gameLoadMainmap()
{
  iniStream *stream;
  int map, path, map1, map2;
  char section[256 + 1], key[64 + 1];


  //--Get number of maps--//
    stream = iniLoad( "romfs:/game/lvl/mm/main.dat" );
      mainmap.maps = iniNSections( stream, "map" );



  //--Load Map--//
    mainmap.map = (mainmap_map**)calloc( mainmap.maps, sizeof(void*) );

    for( map = 0; map < mainmap.maps; map++ )
    {
      mainmap.map[map] = malloc( sizeof(mainmap_map) );

      sprintf( section, "map%i", map );

        mainmap.map[map]->name = iniGetStr( stream, section, "name", "ERROR!" );
        mainmap.map[map]->x = iniGetInt( stream, section, "x", 0 );
        mainmap.map[map]->y = iniGetInt( stream, section, "y", 0 );
        mainmap.map[map]->pathes = iniNKeys( stream, section, "path" );
        mainmap.map[map]->path = (int*)calloc( mainmap.map[map]->pathes, sizeof(int) );

        for( path = 0; path < mainmap.map[map]->pathes; path++ )
        {
          sprintf( key, "path%i", path );
            mainmap.map[map]->path[path] = iniGetInt( stream, section, key, 0 );
        }
    }


    //--Get BPathes--//
      for( map1 = 0; map1 < mainmap.maps; map1++ )
      {
        mainmap.map[map1]->bpathes = 0;
        mainmap.map[map1]->bpath = NULL;

        for( map2 = 0; map2 < mainmap.maps; map2++ )
        {
          if( map1 == map2 ) continue;

          for( path = 0; path < mainmap.map[map2]->pathes; path++ )
          {
            if( mainmap.map[map2]->path[path] == map1 )
            {
              mainmap.map[map1]->bpathes++;
              mainmap.map[map1]->bpath = realloc( mainmap.map[map1]->bpath, sizeof(int) * mainmap.map[map1]->bpathes );
              mainmap.map[map1]->bpath[mainmap.map[map1]->bpathes-1] = map2;
            }
          }
        }
      }



iniClose( stream );

}

void gameLoadSidequestList()
{
  #ifdef ENABLE_VERSION_1_1
  DIR *sqdir;
  struct dirent *file;
  iniStream *stream;
  char path[FILENAME_MAX];
  char *fsuffix;
  char *psuffix;


  sqdir = opendir( "romfs:/game/lvl/sq" );


  //--Load List--//
    while( (file = readdir(sqdir)) != NULL )
    {
      sprintf( path, "%s", (*file).d_name );

      if( (fsuffix = strstr( path, ".dat" )) != NULL && strlen( fsuffix ) == strlen( ".dat" ))
      {
        sqlist.map = realloc( sqlist.map, sizeof( void *) * ++sqlist.maps );
        sqlist.map[sqlist.maps-1] = malloc( sizeof( sqlist_map ) );

        *strrchr( path, '.' ) = '\0';

        sqlist.map[sqlist.maps-1]->name = calloc( strlen( path ) + 1, sizeof( char ) );
        sprintf( sqlist.map[sqlist.maps-1]->name, "%s", path );

      }
    }
  #endif
}

void gameResetSav()
{
  int map;


  sav.ms_shown = 0;

  sav.map = (sav_map**) calloc( mainmap.maps, sizeof(void*) );

  for( map = 0; map < mainmap.maps; map++ )
  {
    sav.map[map] = malloc( sizeof( sav_map ) );

    sav.map[map]->completed = 0;

    sav.map[map]->best_time = -1;
    sav.map[map]->best_totalpoints = -1;
    sav.map[map]->best_whits = -1;
    sav.map[map]->best_coins = -1;

    sav.map[map]->best_timemedal = -1;
    sav.map[map]->best_totalmedal = -1;
    sav.map[map]->best_whitsmedal = -1;
    sav.map[map]->best_coinsmedal = -1;
  }



}

void gameLoadSav()
{

  int map;
  FILE *file;
  char line[512 + 1];
  char *cut;

  file = fopen( SAVEDATA, "r" );

  map = 0;

  gameResetSav();

  fgets( line, 512, file );

  cut = strchr( line, '#' ) ;
    if( cut == NULL ) return;

  sav.ms_shown = atoi( cut + 1 ); cut = strchr( cut + 1, '/' );


  while( !feof( file ) && (map < mainmap.maps) )
  {
    fgets( line, 512, file );

    cut = strchr( line, '#' ) ;

    if( cut == NULL ) break;

    sav.map[map]->completed = atoi( cut + 1 ); cut = strchr( cut + 1, '/' );
    sav.map[map]->best_time = atoi( cut + 1 ); cut = strchr( cut + 1, '/' );
    sav.map[map]->best_totalpoints = atoi( cut + 1 ); cut = strchr( cut + 1, '/' );
    sav.map[map]->best_whits = atoi( cut + 1 ); cut = strchr( cut + 1, '/' );
    sav.map[map]->best_coins = atoi( cut + 1 ); cut = strchr( cut + 1, '/' );
    sav.map[map]->best_timemedal = atoi( cut + 1 ); cut = strchr( cut + 1, '/' );
    sav.map[map]->best_totalmedal = atoi( cut + 1 ); cut = strchr( cut + 1, '/' );
    sav.map[map]->best_whitsmedal = atoi( cut + 1 ); cut = strchr( cut + 1, '/' );
    sav.map[map]->best_coinsmedal = atoi( cut + 1 ); cut = strchr( cut + 1, '/' );

    map++;
  }

  fclose(file);
}

void gameSaveSav()
{
  int map;
  char line[512 + 1];

  FILE *file = fopen( SAVEDATA, "w" );

  fprintf( file, "#%i\n",
    sav.ms_shown
    );

  for( map = 0; map < mainmap.maps; map++ )
  {
    fprintf( file, "#%i/%i/%i/%i/%i/%i/%i/%i/%i\n",
      sav.map[map]->completed,
      sav.map[map]->best_time,
      sav.map[map]->best_totalpoints,
      sav.map[map]->best_whits,
      sav.map[map]->best_coins,
      sav.map[map]->best_timemedal,
      sav.map[map]->best_totalmedal,
      sav.map[map]->best_whitsmedal,
      sav.map[map]->best_coinsmedal
      );
  }

  fclose(file);
}

int gameMainmenu()
{
  FILE *file;
  int point;
  int mainselection, activated, subselection;
  char string[512];
  double camtx, camty;
  double csx, csy;


  mainselection = 1;
  activated = 0;
  subselection = 1;


  gameLoadMap("romfs:/game/lvl/ex.dat");
  gameMapSetup();
  camtx = camera.x;
  camty = camera.y;

  tips.ctip = rand()%tips.num;
  tips.since = game_levelframe;



  while( 1 )
  {
    //--Control--//
      cntrlUpdate();

      //--Sound--//
        if( cntrl_key.b.newpressed ) sfxPlaySFX(media.sfx.button);
        if( cntrl_key.x.newpressed && activated ) sfxPlaySFX(media.sfx.button);



    //--Calc--//
      if( activated )
      {
        if( cntrl_key.left.newpressed && subselection > 0 ) subselection --;
        if( cntrl_key.right.newpressed && subselection < 1 ) subselection ++;
      }
      else
      {
        if( cntrl_key.left.newpressed && mainselection > 0 ) mainselection --;
        if( cntrl_key.right.newpressed && mainselection < 2 ) mainselection ++;
      }

      if( cntrl_key.b.newpressed && activated && subselection == 0 )
      {
        cntrl_key.b.newpressed = 0;
        break;
      }
      if( cntrl_key.b.newpressed && activated && subselection == 1 )
      {
        cntrl_key.b.newpressed = 0;
        activated = 0;
      }

      if( cntrl_key.b.newpressed ) activated = 1;
      if( cntrl_key.x.newpressed ) activated = 0;


      //--Camera--//
        if( geoDistance2D( camera.x, camera.y, camtx, camty ) <= 4 )
        {
          camtx = (rand()%lvl.w) * BLOCKAXIS;
          camty = (rand()%lvl.h) * BLOCKAXIS;
        }

        //--Move camera--//
          csx = cos( geoDirection2D( camera.x, camera.y, camtx, camty ) ) * MAINMENUCAMERASPEED;
          csy = -sin( geoDirection2D( camera.x, camera.y, camtx, camty ) ) * MAINMENUCAMERASPEED;
          camera.x += csx;
          camera.y += csy;

        //--Background--//
          for( point = 0; point < background.points; point++ )
          {
            background.x[point] -= geoRoundF(csx, 3)/background.dept[point];
            background.y[point] -= geoRoundF(csy, 3)/background.dept[point];

            if( background.x[point] < 0 ) background.x[point] += gfx_screen->w;
            if( background.y[point] < 0 ) background.y[point] += gfx_screen->h;

            if( background.x[point] >= gfx_screen->w ) background.x[point] -= gfx_screen->w;
            if( background.y[point] >= gfx_screen->h ) background.y[point] -= gfx_screen->h;
          }

    //--LevelFrame--//
      game_levelframe ++;





    //-Draw--//
      gameDraw();
      #ifndef ENABLE_VERSION_1_1
      gfxDrawSprite( gfx_screen, media.menu.main, NULL, 0, 0 );
      #else
      gfxDrawFilledRectangle( gfx_screen, 0, 0, gfx_screen->w, 75, 0x000000ff );
      gfxDrawFilledRectangle( gfx_screen, 0, 75, 16, gfx_screen->h - 75 - 55, 0x000000ff );
      gfxDrawFilledRectangle( gfx_screen, gfx_screen->w - 16, 75, 16, gfx_screen->h - 75 - 55, 0x000000ff );
      gfxDrawFilledRectangle( gfx_screen, 0, gfx_screen->h - 55, gfx_screen->w, 55, 0x000000ff );
      gfxDrawSprite( gfx_screen, media.menu.title, NULL, gfx_screen->w/2 - media.menu.title->w/2, 10 );
      #endif

      if( activated )
      {
        switch( mainselection )
        {
          case 0:
            stringColor( gfx_screen, gfx_screen->w/2 - strlen("Start a new game - delete old one?") * 4, gfx_screen->h - 45, "Start a new game - delete old one?", 0xffffffff );
          break;
          case 1:
            stringColor( gfx_screen, gfx_screen->w/2 - strlen("Continue the saved game?") * 4, gfx_screen->h - 45, "Continue the saved game?", 0xffffffff );
          break;
          case 2:
            stringColor( gfx_screen, gfx_screen->w/2 - strlen("Exit this game?") * 4, gfx_screen->h - 45, "Exit this game?", 0xffffffff );
          break;
        }

        stringColor( gfx_screen, 15, gfx_screen->h - 30, "Yes", 0xffffffff );
        stringColor( gfx_screen, gfx_screen->w - strlen("No") * 8 - 5 - 15, gfx_screen->h - 30, "No", 0xffffffff );

        switch( subselection )
        {
          case 0:
            gfxDrawLine( gfx_screen, 10, gfx_screen->h - 20, 10 + strlen("Yes") * 8 + 10, gfx_screen->h - 20, 0xffffffff );
          break;
          case 1:
            gfxDrawLine( gfx_screen, gfx_screen->w - strlen("No") * 8 - 10 - 15, gfx_screen->h - 20, gfx_screen->w - 15, gfx_screen->h - 20, 0xffffffff );
          break;
        }

      }
      else
      {
        stringColor( gfx_screen, 15, gfx_screen->h - 30, "New Game", 0xffffffff );
        stringColor( gfx_screen, gfx_screen->w/2 - strlen("Continue") * 4, gfx_screen->h - 45, "Continue", 0xffffffff );
        stringColor( gfx_screen, gfx_screen->w - strlen("Exit") * 8 - 15, gfx_screen->h - 30, "Exit", 0xffffffff );


        switch( mainselection )
        {
          case 0:
            gfxDrawLine( gfx_screen, 10, gfx_screen->h - 20, 10 + strlen("New Game") * 8 + 10, gfx_screen->h - 20, 0xffffffff );
          break;
          case 1:
            gfxDrawLine( gfx_screen, gfx_screen->w/2 - strlen("Continue") * 4 - 5, gfx_screen->h - 35, gfx_screen->w/2 + strlen("Continue") * 4 + 5, gfx_screen->h - 35, 0xffffffff );
          break;
          case 2:
            gfxDrawLine( gfx_screen, gfx_screen->w - strlen("Exit") * 8 - 15 - 5, gfx_screen->h - 20, gfx_screen->w - 10, gfx_screen->h - 20, 0xffffffff );
          break;
        }
      }

      //--Tips--//
        if( tips.num > 0 )
        {
          sprintf( string, "*Tip: %s*", tips.tip[tips.ctip] );
          stringColor( gfx_screen, gfx_screen->w - (game_levelframe - tips.since) * MAINMENUTIPSPEED, 75 - 15, string, 0xffffffff );

          if( gfx_screen->w - (game_levelframe - tips.since) * MAINMENUTIPSPEED + strlen(string)*8 < 0 )
          {
            tips.ctip = (tips.ctip + 1 )%tips.num;
            tips.since = game_levelframe;
          }
        }

      gfxShowScreen();
  }

  gameUnloadMap();





  game_mainrunning = 1;

  switch( mainselection )
  {
    case 0:
      gameResetSav();
      gameSaveSav();
      gameNewGameScreen();
      return 1;
    break;
    case 1:
      file = fopen( SAVEDATA, "r" );
      if( file != NULL )
      {
        fclose( file );
        gameLoadSav();
      }
      else
      {
        gameResetSav();
        gameSaveSav();
        gameNewGameScreen();
      }
      return 1;
    break;
    case 2:
      game_mainrunning = 0;
      return 0;
    break;
  }





}

void gameNewGameScreen()
{
  char string[2048];
  int phase, py;


  phase = 0;

  while( phase < 2 )
  {
    //--Control--//
      cntrlUpdate();

      //--Sounds--//
        if( cntrl_key.b.newpressed ) sfxPlaySFX( media.sfx.button );



    //--Calc--
      if( cntrl_key.b.newpressed ) phase++;



    //--Draw--//
      gfxDrawRectangle( gfx_screen, 15, 15, gfx_screen->w - 15*2, gfx_screen->h - 15*2, 0xffffffff );

      if( phase == 0 )
      {
        stringColor( gfx_screen, 20, 20, "Welcome!", 0xffffffff );
        sprintf( string, "%s", "Fy.WoD! is a racing game: in a giant net of maps you have to make your way to the champions location, you have to reach highscores, earn yourself medals and train your reaction, planing and strategic skills. Read the tips in the mainmenu carefully! Fy.WoD! saves automaticly!!! " );
        py = gfxPrintStringBox( gfx_screen, 20 + 10, 20 + 20, gfx_screen->w - 15*2 - 5 - 10, gfx_screen->h - 15*2 - 5, string, 0xffffffff );

        stringColor( gfx_screen, gfx_screen->w/2 - strlen("Left/Right: Rotate")*4, py + 20, "Left/Right: Rotate", 0xffffffff );
        stringColor( gfx_screen, gfx_screen->w/2 - strlen("B: Accelerate")*4, py + 20 + 10, "B: Accelerate", 0xffffffff );
        stringColor( gfx_screen, gfx_screen->w/2 - strlen("X: Back")*4, py + 20 + 20, "X: Back", 0xffffffff );
        stringColor( gfx_screen, gfx_screen->w/2 - strlen("L: SlowMotion")*4, py + 20 + 30, "L: SlowMotion", 0xffffffff );
        stringColor( gfx_screen, gfx_screen->w/2 - strlen("Start: Upper Menu / Pause")*4, py + 20 + 40, "Menu: Upper Menu / Pause", 0xffffffff );
      }

      if( phase == 1 )
      {
        stringColor( gfx_screen, 20, 20, "Further Infos:", 0xffffffff );
        sprintf( string, "%s", "You will be teleportated to the galactic map now. Since you are a bloody beginner there will be only one map available for you. If you complete this there will be new ones unlocked. To complete a map you must reach a certain medal in all 4 categories: time , coins, wall-hits and totalpoints. On the bottom left side you can see your total amount of points. Maybe something will happen if you reach the million... Ah, I nearly forgot it: Fy.WoD! is difficult. Too difficult for you??? " );
          gfxPrintStringBox( gfx_screen, 20 + 10, 20 + 20, gfx_screen->w - 15*2 - 5 - 10, gfx_screen->h - 15*2 - 5, string, 0xffffffff );
      }

      gfxShowScreen();
  }

  gameNewGameSetup();

}

void gameNewGameSetup()
{
  game_lastmap = 0;
}

void gameNotBuildScreen()
{
  int phase;
  char string[2048];


  phase = 0;

  while( phase < 1 )
  {
    //--Control--//
      cntrlUpdate();

      //--Sounds--//
        if( cntrl_key.b.newpressed ) sfxPlaySFX( media.sfx.button );


    //--Calc--//
      if( cntrl_key.b.newpressed ) phase++;


    //--Draw--//
      gfxDrawRectangle( gfx_screen, 15, 15, gfx_screen->w-15*2, gfx_screen->h-15*2, 0xffffffff );
      stringColor( gfx_screen, gfx_screen->w/2 - strlen("Not build yet!")*4 , gfx_screen->h/2-8, "Not build yet!", 0xffffffff );
      stringColor( gfx_screen, gfx_screen->w/2 - strlen("Please wait for updates!")*4 , gfx_screen->h/2+8, " Please wait for updates!", 0xffffffff );



      gfxShowScreen();

  }

}

void gameMillionScreen()
{
  int phase;
  char string[2048];


  phase = 0;

  while( phase < 4 )
  {
    //--Control--//
      cntrlUpdate();

      //--Sounds--//
        if( cntrl_key.b.newpressed ) sfxPlaySFX( media.sfx.button );


    //--Calc--//
      if( cntrl_key.b.newpressed ) phase++;


    //--Draw--//
      gfxDrawRectangle( gfx_screen, 15, 15, gfx_screen->w - 15*2, gfx_screen->h - 15*2, 0xffffffff );
      stringColor( gfx_screen, gfx_screen->w/2 - strlen("You reached 1 million points!")*4, 25, "You reached 1 million points!", 0xffffffff );

      switch( phase )
      {
        case 0:
          sprintf( string, "%s","Congratulations! Remember that I promissed you something, when you started this game? " );
          gfxPrintStringBox( gfx_screen, 30, 40, gfx_screen->w-15-30, gfx_screen->h-15-40, string, 0xffffffff );
          sprintf( string, "%s","That something would happen? Yeah, indeed, something will happen. I will tell you the truth about this game. The REAL truth. You will learn, why this game is called Fy.WoD!. Are you sure you want to go on? " );
          gfxPrintStringBox( gfx_screen, 30, 40 + 35, gfx_screen->w-15-30, gfx_screen->h-15-40-35, string, 0xffffffff );

        break;
        case 1:
          sprintf( string, "%s","So, you really wish to know? Sure, that you are ready to take this? Really? So if you wish so, here is the truth about Fy.WoD! " );
          gfxPrintStringBox( gfx_screen, 30, 40, gfx_screen->w-15-30, gfx_screen->h-15-40, string, 0xffffffff );
          sprintf( string, "%s","You really must be mad... " );
          gfxPrintStringBox( gfx_screen, 30, 40 + 45, gfx_screen->w-15-30, gfx_screen->h-15-40-45, string, 0xffffffff );

        break;
        case 2:
          sprintf( string, "%s","Shivering in fear? " );
          gfxPrintStringBox( gfx_screen, 30, 40, gfx_screen->w-15-30, gfx_screen->h-15-40, string, 0xffffffff );
          sprintf( string, "%s","As you may have thought, the truth is simple: There is simply no truth. Fy.WoD! was a name I just hacked into my keyboard. There is no story, no legend. I know, that this must be shocking for you... " );
          gfxPrintStringBox( gfx_screen, 30, 40 + 25, gfx_screen->w-15-30, gfx_screen->h-15-40-45, string, 0xffffffff );

        break;
        case 3:
          sprintf( string, "%s","But feel free to go on playing. Maybe I have hidden one or another thing out there for you ;P " );
          gfxPrintStringBox( gfx_screen, 30, 40, gfx_screen->w-15-30, gfx_screen->h-15-40, string, 0xffffffff );
          stringColor( gfx_screen, gfx_screen->w - strlen("Much fun!")*8 - 25, gfx_screen->h-30, "Much fun!", 0xffffffff );

        break;


      }

      gfxShowScreen();

  }

}

char *gameMainmap()
{
  int point, total_bronze, total_silver, total_gold;
  long total_points;
  Uint8 alpha;
  int cmap, cpath, cbpath, cselection;
  int map, path, bpath;
  double dir;
  static char mappath[512 + 1];
  char string[512 + 1];
  double csx, csy;
  FILE *file;


  cmap = game_lastmap;
  cpath = 0;
  cbpath = 0;
  cselection = 0;

  //--Preset camera--//
    if( mainmap.maps > 0 )
    {
      camera.x = mainmap.map[cmap]->x;
      camera.y = mainmap.map[cmap]->y;
    }

  //--Set reachability--//
   for( map = 0; map < mainmap.maps; map++ ) mainmap.map[map]->reachable = 0;
   for( map = 0; map < mainmap.maps; map++ )
   {
     if( !sav.map[map]->completed ) continue;

     mainmap.map[map]->reachable = 1;

     for( path = 0; path < mainmap.map[map]->pathes; path++ )
     {
       mainmap.map[mainmap.map[map]->path[path]]->reachable = 1;
     }
     for( bpath = 0; bpath < mainmap.map[map]->bpathes; bpath++ )
     {
       mainmap.map[mainmap.map[map]->bpath[bpath]]->reachable = 1;
     }
   }



  //--GetTotalpoints--//
    total_points = 0;
    total_bronze = 0;
    total_silver = 0;
    total_gold = 0;
    for( map = 0; map < mainmap.maps; map++ )
    {
      if( sav.map[map]->best_totalpoints > 0 ) total_points += sav.map[map]->best_totalpoints;

      if( sav.map[map]->best_timemedal == 1 ) total_bronze++; else if( sav.map[map]->best_timemedal == 2 ) total_silver++; else if( sav.map[map]->best_timemedal == 3 || sav.map[map]->best_timemedal == 4 ) total_gold++;
      if( sav.map[map]->best_coinsmedal == 1 ) total_bronze++; else if( sav.map[map]->best_coinsmedal == 2 ) total_silver++; else if( sav.map[map]->best_coinsmedal == 3 || sav.map[map]->best_coinsmedal == 4 ) total_gold++;
      if( sav.map[map]->best_whitsmedal == 1 ) total_bronze++; else if( sav.map[map]->best_whitsmedal == 2 ) total_silver++; else if( sav.map[map]->best_whitsmedal == 3 || sav.map[map]->best_whitsmedal == 4 ) total_gold++;
      if( sav.map[map]->best_totalmedal == 1 ) total_bronze++; else if( sav.map[map]->best_totalmedal == 2 ) total_silver++; else if( sav.map[map]->best_totalmedal == 3 || sav.map[map]->best_totalmedal == 4 ) total_gold++;
    }

    if( total_points >= 1000000 && !sav.ms_shown )
    {
     gameMillionScreen();
     sav.ms_shown = 1;
     gameSaveSav();
    }





  while( mainmap.maps > 0 )
  {
    //--Control--//
      cntrlUpdate();

      //--Sounds--//
        if( cntrl_key.menu.newpressed ) sfxPlaySFX( media.sfx.button );
        if( cntrl_key.b.newpressed && cselection == 0 ) sfxPlaySFX( media.sfx.button );
        if( cntrl_key.b.newpressed && cselection == -1 && mainmap.map[mainmap.map[cmap]->bpath[cbpath]]->reachable ) sfxPlaySFX( media.sfx.fly );
        if( cntrl_key.b.newpressed && cselection == 1 && mainmap.map[mainmap.map[cmap]->path[cpath]]->reachable ) sfxPlaySFX( media.sfx.fly );


    //--Calculate--//
      //--Quit to Mainmenu--//
        if( cntrl_key.menu.newpressed )
        {
          game_levelrunning = 0;
          game_mainrunning = 0;

          return;
        }

      //--Finish selection--//
        if( cntrl_key.b.newpressed && cselection == 0)
        {
          sprintf( mappath, "romfs:/game/lvl/mm/%i.dat", cmap );
          file = fopen( mappath, "r" );

          if( file == NULL )
          {
            gameNotBuildScreen();
          }
          else
          {
            fclose( file );
            break;
          }
        }

      //--Change selection--//
        if( cntrl_key.up.newpressed ) cselection --;
        if( cntrl_key.down.newpressed ) cselection ++;

        if( cselection < -1 ) cselection = -1;
        if( cselection > 1 ) cselection = 1;

        if( (cselection == -1) && (mainmap.map[cmap]->bpathes == 0) ) cselection = 0;
        if( cselection == 1 && mainmap.map[cmap]->pathes == 0 ) cselection = 0;


      //--Change path--//
        if( cntrl_key.left.newpressed  && cselection == 1) cpath ++;
        if( cntrl_key.right.newpressed  && cselection == 1) cpath --;

        if( cntrl_key.left.newpressed && cselection == -1) cbpath ++;
        if( cntrl_key.right.newpressed  && cselection == -1) cbpath --;

          if( cpath < 0 ) cpath += mainmap.map[cmap]->pathes;
          if( mainmap.map[cmap]->pathes > 0 ) cpath = cpath % mainmap.map[cmap]->pathes;

          if( cbpath < 0 ) cbpath += mainmap.map[cmap]->bpathes;
          if( mainmap.map[cmap]->bpathes > 0 ) cbpath = cbpath % mainmap.map[cmap]->bpathes;


      //--Change map--//
        if( cntrl_key.b.newpressed )
        {
          if( cselection == -1 && mainmap.map[mainmap.map[cmap]->bpath[cbpath]]->reachable )
          {
            cmap = mainmap.map[cmap]->bpath[cbpath];
            cpath = 0;
            cbpath = 0;
            cselection = 0;
          }
          if( cselection == 1 && mainmap.map[mainmap.map[cmap]->path[cpath]]->reachable )
          {
            cmap = mainmap.map[cmap]->path[cpath];
            cpath = 0;
            cbpath = 0;
            cselection = 0;
          }
        }


      //--Move camera--//
        csx = (mainmap.map[cmap]->x - camera.x)/15;
        csy = (mainmap.map[cmap]->y - camera.y)/15;
        camera.x += csx;
        camera.y += csy;

        //--Background--//
          for( point = 0; point < background.points; point++ )
          {
            background.x[point] -= geoRoundF(csx, 3)/background.dept[point];
            background.y[point] -= geoRoundF(csy, 3)/background.dept[point];

            if( background.x[point] < 0 ) background.x[point] += gfx_screen->w;
            if( background.y[point] < 0 ) background.y[point] += gfx_screen->h;

            if( background.x[point] >= gfx_screen->w ) background.x[point] -= gfx_screen->w;
            if( background.y[point] >= gfx_screen->h ) background.y[point] -= gfx_screen->h;
          }





    //--Draw--//
      //--Background--//
        for( point = 0; point < background.points; point++ )
        {
          alpha = 255 / (int)geoLimit((background.dept[point]/5), 1, 255);
          gfxDrawPixel( gfx_screen, (Sint16)background.x[point], (Sint16)background.y[point], 0x0000000ff | alpha | alpha << 8 | alpha << 16 | alpha << 24 );
        }


      //--Net of maps--//
        for( map = 0; map < mainmap.maps; map++ )
        {
          gfxDrawFilledCircle( gfx_screen, SCREENPOS( mainmap.map[map]->x, mainmap.map[map]->y ), MAINMAPMAPRADIUS, 0xffffffff );

          for( path = 0; path < mainmap.map[map]->pathes; path++ )
          {
            dir = geoDirection2D( mainmap.map[map]->x, mainmap.map[map]->y, mainmap.map[mainmap.map[map]->path[path]]->x, mainmap.map[mainmap.map[map]->path[path]]->y  );

            gfxDrawLine( gfx_screen,
              SCREENPOS( mainmap.map[map]->x + cos(dir) * (MAINMAPMAPRADIUS + 12), mainmap.map[map]->y - sin(dir) * (MAINMAPMAPRADIUS + 12) ),
              SCREENPOS( mainmap.map[mainmap.map[map]->path[path]]->x - cos(dir) * (MAINMAPMAPRADIUS + 12), mainmap.map[mainmap.map[map]->path[path]]->y + sin(dir) * (MAINMAPMAPRADIUS + 12) ),
              0xccccccff );
          }
        }


      //--Uncompleted symbol--//
        for( map = 0; map < mainmap.maps; map++ )
        {
          if( !sav.map[map]->completed )
          {
            gfxDrawFilledCircle( gfx_screen, SCREENPOS( mainmap.map[map]->x, mainmap.map[map]->y ), MAINMAPMAPRADIUS - 2, 0xff0000ff );
            gfxDrawFilledCircle( gfx_screen, SCREENPOS( mainmap.map[map]->x, mainmap.map[map]->y ), MAINMAPMAPRADIUS - 4, 0xffffffff );
          }
        }


      //--Mark--//
        if( cselection == 0 )
        {
          gfxDrawFilledCircle( gfx_screen, SCREENPOS( mainmap.map[cmap]->x, mainmap.map[cmap]->y ), MAINMAPMARKRADIUS, 0xaaffffff );
        }

        if( cselection == -1 )
        {
          dir = geoDirection2D(  mainmap.map[cmap]->x, mainmap.map[cmap]->y, mainmap.map[mainmap.map[cmap]->bpath[cbpath]]->x, mainmap.map[mainmap.map[cmap]->bpath[cbpath]]->y  );
          gfxDrawFilledCircle( gfx_screen, SCREENPOS( mainmap.map[cmap]->x + cos(dir) * (MAINMAPMAPRADIUS + 15), mainmap.map[cmap]->y - sin(dir) * (MAINMAPMAPRADIUS + 15) ), MAINMAPMARKRADIUS, mainmap.map[mainmap.map[cmap]->bpath[cbpath]]->reachable ? 0xaaffffff : 0xaa0000ff );
        }

        if( cselection == 1 )
        {
          dir = geoDirection2D(  mainmap.map[cmap]->x, mainmap.map[cmap]->y, mainmap.map[mainmap.map[cmap]->path[cpath]]->x, mainmap.map[mainmap.map[cmap]->path[cpath]]->y  );
          gfxDrawFilledCircle( gfx_screen, SCREENPOS( mainmap.map[cmap]->x + cos(dir) * (MAINMAPMAPRADIUS + 15), mainmap.map[cmap]->y - sin(dir) * (MAINMAPMAPRADIUS + 15) ), MAINMAPMARKRADIUS, mainmap.map[mainmap.map[cmap]->path[cpath]]->reachable ? 0xaaffffff : 0xaa0000ff );
        }


      //--Info--//
        #ifndef ENABLE_VERSION_1_1
        gfxDrawSprite( gfx_screen, media.menu.map, NULL, 0, 0 );
        #else
        gfxDrawFilledRectangle( gfx_screen, gfx_screen->w/2 - 85, 0, 85*2, 35, 0x000000ff );
        gfxDrawFilledRectangle( gfx_screen, 0, 0, gfx_screen->w/2 - 85, 26, 0x000000ff );
        gfxDrawFilledRectangle( gfx_screen, gfx_screen->w/2 + 85, 0, gfx_screen->w/2 - 85, 26, 0x000000ff );
        gfxDrawLine( gfx_screen, 0, 26, gfx_screen->w/2 - 85, 26, 0xffffffff );
        gfxDrawLine( gfx_screen, gfx_screen->w/2 - 85, 26, gfx_screen->w/2 - 85, 35, 0xffffffff );
        gfxDrawLine( gfx_screen, gfx_screen->w/2 - 85, 35, gfx_screen->w/2 + 85, 35, 0xffffffff );
        gfxDrawLine( gfx_screen, gfx_screen->w/2 + 85, 35, gfx_screen->w/2 + 85, 26, 0xffffffff );
        gfxDrawLine( gfx_screen, gfx_screen->w/2 + 85, 26, gfx_screen->w, 26, 0xffffffff );

        gfxDrawFilledRectangle( gfx_screen, gfx_screen->w/2 - 58, gfx_screen->h - 18, 58*2, 18, 0x000000ff );
        gfxDrawFilledRectangle( gfx_screen, 0, gfx_screen->h - 29, gfx_screen->w/2 - 58, 29, 0x000000ff );
        gfxDrawFilledRectangle( gfx_screen, gfx_screen->w/2 + 58, gfx_screen->h - 29, gfx_screen->w/2 - 58, 29, 0x000000ff );
        gfxDrawLine( gfx_screen, 0, gfx_screen->h - 30, gfx_screen->w/2 - 58, gfx_screen->h - 30, 0xffffffff );
        gfxDrawLine( gfx_screen, gfx_screen->w/2 - 58, gfx_screen->h - 30, gfx_screen->w/2 - 58, gfx_screen->h - 18, 0xffffffff );
        gfxDrawLine( gfx_screen, gfx_screen->w/2 - 58, gfx_screen->h - 18, gfx_screen->w/2 + 58, gfx_screen->h - 18, 0xffffffff );
        gfxDrawLine( gfx_screen, gfx_screen->w/2 + 58, gfx_screen->h - 18, gfx_screen->w/2 + 58, gfx_screen->h - 30, 0xffffffff );
        gfxDrawLine( gfx_screen, gfx_screen->w/2 + 58, gfx_screen->h - 30, gfx_screen->w, gfx_screen->h - 30, 0xffffffff );
        #endif

        //--Bottom Info Bar--//
          if( sav.map[cmap]->completed )
          {
            stringColor( gfx_screen, gfx_screen->w/2 - strlen("Completed!")*4, gfx_screen->h - 12, "Completed!", 0xffffffff );
          }
          else
          {
            stringColor( gfx_screen, gfx_screen->w/2 - strlen("Uncompleted!")*4, gfx_screen->h - 12, "Uncompleted!", 0xffffffff );
          }



          sprintf( string, "%i", total_points );
            stringColor( gfx_screen, 20, gfx_screen->h - 16, string, 0xffffffff );
          gfxDrawSprite( gfx_screen, media.small.sum, NULL, 20 - 12, gfx_screen->h - 16 );

          sprintf( string, "%i", total_gold );
            stringColor( gfx_screen, gfx_screen->w - 16 - strlen(string) * 4 - 5, gfx_screen->h - 10, string, 0xffffffff );
          gfxDrawSprite( gfx_screen, media.small.gold, NULL, gfx_screen->w - 16 - 4 - 5, gfx_screen->h - 10 - 12 );

          sprintf( string, "%i", total_silver );
            stringColor( gfx_screen, gfx_screen->w - 48 - strlen(string) * 4 - 5, gfx_screen->h - 10, string, 0xffffffff );
          gfxDrawSprite( gfx_screen, media.small.silver, NULL, gfx_screen->w - 48 - 4 - 5, gfx_screen->h - 10 - 12 );

          sprintf( string, "%i", total_bronze );
            stringColor( gfx_screen, gfx_screen->w - 80 - strlen(string) * 4 - 5, gfx_screen->h - 10, string, 0xffffffff );
          gfxDrawSprite( gfx_screen, media.small.bronze, NULL, gfx_screen->w - 80 - 4 - 5, gfx_screen->h - 10 - 12 );


        //--Upper Info Bar--//
          sprintf( string, "%s", mainmap.map[cmap]->name );
             stringColor( gfx_screen, gfx_screen->w/2 - strlen(string)*4 , 25, string, 0xffffffff );

          if( sav.map[cmap]->best_time != -1 )
            sprintf( string, "%.2f", geoLimit( (double)sav.map[cmap]->best_time/1000, 0, geoLIMITMAX ) );
          else
            sprintf( string, "%c", '/' );
          gfxDrawSprite( gfx_screen, media.small.clock, NULL, gfx_screen->w*0/4 + 5, 5 );
            stringColor( gfx_screen, gfx_screen->w*0/4 + 15, 5, string, 0xffffffff );
          gfxDrawSprite( gfx_screen, MEDALSMALLSPRITE( sav.map[cmap]->best_timemedal ), NULL, gfx_screen->w*0/4 + 15 + strlen(string)*4 - 4, 15 );

          if( sav.map[cmap]->best_coins != -1 )
            sprintf( string, "%i", (int)geoLimit( sav.map[cmap]->best_coins, 0, geoLIMITMAX ) );
          else
            sprintf( string, "%c", '/' );
          gfxDrawSprite( gfx_screen, media.small.coin, NULL, gfx_screen->w*1/4 + 5, 5 );
            stringColor( gfx_screen, gfx_screen->w*1/4 + 15, 5, string, 0xffffffff );
          gfxDrawSprite( gfx_screen, MEDALSMALLSPRITE( sav.map[cmap]->best_coinsmedal ), NULL, gfx_screen->w*1/4 + 15 + strlen(string)*4 - 4, 15 );


          if( sav.map[cmap]->best_whits != -1 )
            sprintf( string, "%i", (int)geoLimit( sav.map[cmap]->best_whits, 0, geoLIMITMAX ) );
          else
             sprintf( string, "%c", '/' );
          gfxDrawSprite( gfx_screen, media.small.whit, NULL, gfx_screen->w*2/4 + 5, 5 );
            stringColor( gfx_screen, gfx_screen->w*2/4 + 15, 5, string, 0xffffffff );
          gfxDrawSprite( gfx_screen, MEDALSMALLSPRITE( sav.map[cmap]->best_whitsmedal ), NULL, gfx_screen->w*2/4 + 15 + strlen(string)*4 - 4, 15 );

          if( sav.map[cmap]->best_totalpoints != -1 )
            sprintf( string, "%i", (int) geoLimit( sav.map[cmap]->best_totalpoints, 0, geoLIMITMAX ) );
          else
            sprintf( string, "%c", '/' );
          gfxDrawSprite( gfx_screen, media.small.top, NULL, gfx_screen->w*3/4 + 5, 5);
            stringColor( gfx_screen, gfx_screen->w*3/4 + 15, 5, string, 0xffffffff );
          gfxDrawSprite( gfx_screen, MEDALSMALLSPRITE( sav.map[cmap]->best_totalmedal ), NULL, gfx_screen->w*3/4 + 15 + strlen(string)*4 - 4, 15 );


      gfxShowScreen();
  }


  lvl.mapid = cmap;
  game_lastmap = cmap;
  sprintf( mappath, "romfs:/game/lvl/mm/%i.dat", cmap );
  return mappath;
}

void gameLoadMap( char *path )
{
#define PUFFER 256

  char *puffer, *cut;

  int column;
  int x,y;

  char cchr;

  lvl.coins = 0;



  //Read Info
    iniStream *stream = iniLoad( path );

      //Startdirection
        lvl.startdirection = geoRad(iniGetInt( stream, "start", "direction", 0 ));

      //Size
        lvl.w = iniGetInt( stream, "size", "w", 0 );
        lvl.h = iniGetInt( stream, "size", "h", 0 );

      //Medal
        lvl.points.total_bronze = iniGetInt( stream, "total", "bronze", 0 );
        lvl.points.total_silver = iniGetInt( stream, "total", "silver", 0 );
        lvl.points.total_gold = iniGetInt( stream, "total", "gold", 0 );


      //Points
        lvl.points.time_max = iniGetInt( stream, "time", "max", 0 );
        lvl.points.time_bronze = iniGetInt( stream, "time", "bronze", 0 );
        lvl.points.time_silver = iniGetInt( stream, "time", "silver", 0 );
        lvl.points.time_gold = iniGetInt( stream, "time", "gold", 0 );

      //WHits
        lvl.points.whits_max = iniGetInt( stream, "whits", "max", 0 );
        lvl.points.whits_bronze = iniGetInt( stream, "whits", "bronze", 0 );
        lvl.points.whits_silver = iniGetInt( stream, "whits", "silver", 0 );
        lvl.points.whits_gold = iniGetInt( stream, "whits", "gold", 0 );

      //Coins
        lvl.points.coins_bronze = iniGetInt( stream, "coins", "bronze", 0 );
        lvl.points.coins_silver = iniGetInt( stream, "coins", "silver", 0 );
        lvl.points.coins_gold = iniGetInt( stream, "coins", "gold", 0 );

      //Complete Medals
        lvl.completemedal = iniGetInt( stream, "complete", "medal", 0 );



  //Read Block
    FILE *file = fopen( path, "r" );
      if( file == NULL )
      {
        fprintf( stderr, "The data - file '%s' couldnt be opened!\n", path );
        return;
      }

    puffer = (char *) calloc( PUFFER + 1, sizeof( char ) );


    //Allocate memory & set default
      lvl.block = (char **) calloc( lvl.w, sizeof( void * ) );

        for( column = 0; column < lvl.w; column++ )
        {
          lvl.block[column] = (char *) calloc( lvl.h, sizeof( char ) );
        }


      for( x = 0; x < lvl.w; x++ )
      for( y = 0; y < lvl.h; y++ )
      {
        lvl.block[x][y] = '/';
      }




  //Load the block
    for( y = 0; y < lvl.h; y++ )
    {
      x = 0;

      cchr = fgetc( file );

      #ifdef WIN32
      while( x < lvl.w && ( cchr != '\n' || cchr == '\0' ) )
      {
      #endif

      #ifndef WIN32
      while( x < lvl.w && ( cchr != '\r' || cchr == '\0' ) )
      {
      #endif

        lvl.block[x][y] = cchr;

        if( cchr == PSTART )
        {
          player.startx = x;
          player.starty = y;
        }
        if( cchr == COIN )
        {
          lvl.coins++;
        }

        cchr = fgetc( file );
        x++;

      #ifdef WIN32
      }
      #endif

      #ifndef WIN32
      }
      #endif


      #ifndef WIN32
        cchr = fgetc( file );
      #endif

    }







#undef PUFFER
}

void gameMapSetup()
{
  player.x = player.startx * BLOCKAXIS + BLOCKAXIS/2;
  player.y = player.starty * BLOCKAXIS + BLOCKAXIS/2;
  player.wdir = lvl.startdirection;
  player.mdir = 0;
  player.mspeed = 0;
  player.acc = 0;
  player.rotostep = 0.10;
  player.coins = 0;
  player.whits = 0;
  player.lastwhit = 0;
  player.slowmotion = 0;
  player.accchannel = -1;

  camera.x = player.x;
  camera.y = player.y;

  lvl.finishtyp = 0;
  lvl.neededtime = 0;

  game_levelframe = 0;




  lvl.lastframetime = SDL_GetTicks();

}

void gameFuelmenu()
{
  char string[512 + 1];
  int x, y;
  int len;
  int axis;
  SDL_Surface *preview;

  //--Render preview--//
    axis = geoMin( (gfx_screen->w - 60)/lvl.w , (gfx_screen->h - 90)/lvl.h );
    preview = SDL_CreateRGBSurface( SDL_SWSURFACE | SDL_SRCCOLORKEY, axis * lvl.w, axis * lvl.h, gfx_screen->format->BitsPerPixel, 0, 0, 0, 0 );

    for( x = 0; x < lvl.w; x++ )
    for( y = 0; y < lvl.h; y++ )
    {
      if( ISBLOCK( lvl.block[x][y] ) )
      {
        gfxDrawFilledRectangle( preview, x * axis, y * axis, axis, axis, 0xffffffff );
      }
      else
      {
        gfxDrawFilledRectangle( preview, x * axis, y * axis, axis, axis, 0x000000ff );
      }

      if( ISPSTART( lvl.block[x][y] ) || ISPFINISH( lvl.block[x][y] ) )
      {
        gfxDrawFilledRectangle( preview, x * axis, y * axis, axis, axis, 0xff0000ff );
      }
    }

  player.fuel = 50;

  while( 1 )
  {
    //--Controls--//
      cntrlUpdate();

      //--Sound--//
        if( cntrl_key.b.newpressed ) sfxPlaySFX( media.sfx.button );
        if( cntrl_key.x.newpressed ) sfxPlaySFX( media.sfx.button );
        if( cntrl_key.menu.newpressed ) sfxPlaySFX( media.sfx.button );

    //--Calculate--//
      if( cntrl_key.left.pressed ) player.fuel -= 0.4;
      if( cntrl_key.right.pressed ) player.fuel += 0.4;
        player.fuel = geoLimit( player.fuel, 1, 100 );
      if( cntrl_key.b.newpressed ) break;
      if( cntrl_key.x.newpressed )
      {
        lvl.finishtyp = FAILURE_SKIP;
        game_levelrunning = 0;
        break;
      }
      if( cntrl_key.menu.newpressed )
      {
        lvl.finishtyp = FAILURE_SKIP;
        game_levelrunning = 0;
        break;
      }



    //--Draw--//

      //--Title--//
        sprintf( string, "%s", mainmap.map[lvl.mapid]->name );
        stringColor( gfx_screen, gfx_screen->w/2 - strlen(string)*4, 5, string, 0xffffffff );

      //--Preview--//
        gfxDrawSprite( gfx_screen, preview, NULL, gfx_screen->w/2 - axis * lvl.w/2, 30 );

      //--Fuelbar--//
        gfxDrawLine( gfx_screen, 30, gfx_screen->h - 40, gfx_screen->w - 30, gfx_screen->h - 40, 0xffffffff );
        gfxDrawLine( gfx_screen, 30, gfx_screen->h - 40, 30 - 10, gfx_screen->h - 40 - 10, 0xffffffff );
        gfxDrawLine( gfx_screen, 30, gfx_screen->h - 40, 30 - 10, gfx_screen->h - 40 + 10, 0xffffffff );
        gfxDrawLine( gfx_screen, gfx_screen->w - 30, gfx_screen->h - 40, gfx_screen->w - 30 + 10, gfx_screen->h - 40 - 10, 0xffffffff );
        gfxDrawLine( gfx_screen, gfx_screen->w - 30, gfx_screen->h - 40, gfx_screen->w - 30 + 10, gfx_screen->h - 40 + 10, 0xffffffff );
        gfxDrawLine( gfx_screen, gfx_screen->w - 30, gfx_screen->h - 40, gfx_screen->w - 30 + 10, gfx_screen->h - 40 + 10, 0xffffffff );

        sprintf( string, "Fuel: %i", (int)player.fuel );
        stringColor( gfx_screen, gfx_screen->w/2 - strlen("Fuel: xx")*4, gfx_screen->h - 8 - 20, string, 0xffffffff );

        len = gfx_screen->w - 30*2;

        gfxDrawLine( gfx_screen, 30 + (player.fuel/100)*len, gfx_screen->h - 40 - 5, 30 + (player.fuel/100)*len, gfx_screen->h - 40 + 5, 0xaabbffff );

      //--ShowScreen--//
        gfxShowScreen();
  }

  SDL_FreeSurface( preview );


}

int gamePlayerEnvColl( int *circlecoll, int *circlecollx, int *circlecolly, int *collcolor )
{
  int x, y;
  int sx, sy;

  sx = geoLimit( player.x/BLOCKAXIS - 1, 0, geoLIMITMAX );
  sy = geoLimit( player.y/BLOCKAXIS - 1, 0, geoLIMITMAX );

  for( x = sx; x < geoLimit( sx + 3, 0, lvl.w ); x++ )
  for( y = sy; y < geoLimit( sy + 3, 0, lvl.h ); y++ )
  {
    if( ISBLOCK(lvl.block[x][y]) )
    {
      *collcolor = BLOCKTYP( lvl.block[x][y] );
      //--UpperLeft Corner--//
        if( !gameBlockCornerFree( x, y, 0 ) )
        {
          if( geoRectCirclecoll( BLOCKPOS( x, y ), BLOCKAXIS/2, BLOCKAXIS/2, player.x, player.y, PLAYERRADIUS ) )
          {
            return 1;
          }
        }

      //--BottomLeft Corner--//
        if( !gameBlockCornerFree( x, y, 3 ) )
        {
          if( geoRectCirclecoll( BLOCKPOS( x, y + 0.5 ), BLOCKAXIS/2, BLOCKAXIS/2, player.x, player.y, PLAYERRADIUS ) )
          {
            return 1;
          }
        }

      //--UpperRight Corner--//
        if( !gameBlockCornerFree( x, y, 1 ) )
        {
          if( geoRectCirclecoll( BLOCKPOS( x + 0.5, y ), BLOCKAXIS/2, BLOCKAXIS/2, player.x, player.y, PLAYERRADIUS ) )
          {
            return 1;
          }
        }

      //--BottomRight Corner--//
        if( !gameBlockCornerFree( x, y, 2 ) )
        {
          if( geoRectCirclecoll( BLOCKPOS( x + 0.5, y + 0.5 ), BLOCKAXIS/2, BLOCKAXIS/2, player.x, player.y, PLAYERRADIUS ) )
          {
            return 1;
          }
        }

      //--With the Circle--//
        if( geoCirclecoll( ((x+0.5)*BLOCKAXIS), ((y+0.5)*BLOCKAXIS), BLOCKAXIS/2 - 1, player.x, player.y, PLAYERRADIUS ) )
        {
          *circlecoll = 1;
          *circlecollx = x;
          *circlecolly = x;
          return 2;
        }
    }
  }


  return 0;
}

int gameBlockCornerFree( int x, int y, int corner )
{
  int tx1, ty1, tx2, ty2;

  switch( corner )
  {
    case 0:
      tx1 = x - 1; ty1 = y;
      tx2 = x; ty2 = y - 1;

      if( (_BLOCKTYP( tx1, ty1 ) != BLOCKTYP( lvl.block[x][y])) && (_BLOCKTYP( tx2, ty2 ) != BLOCKTYP( lvl.block[x][y] )) ) return 1;

      return 0;
    break;

    case 1:
      tx1 = x + 1; ty1 = y;
      tx2 = x; ty2 = y - 1;

      if( (_BLOCKTYP( tx1, ty1 ) != BLOCKTYP( lvl.block[x][y])) && (_BLOCKTYP( tx2, ty2 ) != BLOCKTYP( lvl.block[x][y] )) ) return 1;

      return 0;
    break;

    case 2:
      tx1 = x + 1; ty1 = y;
      tx2 = x; ty2 = y + 1;

      if( (_BLOCKTYP( tx1, ty1 ) != BLOCKTYP( lvl.block[x][y])) && (_BLOCKTYP( tx2, ty2 ) != BLOCKTYP( lvl.block[x][y] )) ) return 1;

      return 0;
    break;

    case 3:
      tx1 = x - 1; ty1 = y;
      tx2 = x; ty2 = y + 1;

      if( (_BLOCKTYP( tx1, ty1 ) != BLOCKTYP( lvl.block[x][y])) && (_BLOCKTYP( tx2, ty2 ) != BLOCKTYP( lvl.block[x][y] )) ) return 1;

      return 0;
    break;
  }

  return 0;

}

int gamePlayerSpeedUpColl()
{
  int x, y;
  int sx, sy;

  sx = geoLimit( player.x/BLOCKAXIS - 1, 0, geoLIMITMAX );
  sy = geoLimit( player.y/BLOCKAXIS - 1, 0, geoLIMITMAX );

  for( x = sx; x < geoLimit( sx + 3, 0, lvl.w ); x++ )
  for( y = sy; y < geoLimit( sy + 3, 0, lvl.h ); y++ )
  {
    if( ISSPEEDUP( lvl.block[x][y] ) )
    {
      if( geoCirclecoll( player.x, player.y, PLAYERRADIUS, ((x + 0.5)*BLOCKAXIS), ((y + 0.5)*BLOCKAXIS), SPEEDUPRADIUS ) )
      {
        return 1;
      }
    }
  }

  return 0;
}

int gamePlayerSlowDownColl()
{
  int x, y;
  int sx, sy;

  sx = geoLimit( player.x/BLOCKAXIS - 1, 0, geoLIMITMAX );
  sy = geoLimit( player.y/BLOCKAXIS - 1, 0, geoLIMITMAX );

  for( x = sx; x < geoLimit( sx + 3, 0, lvl.w ); x++ )
  for( y = sy; y < geoLimit( sy + 3, 0, lvl.h ); y++ )
  {
    if( ISSLOWDOWN( lvl.block[x][y] ) )
    {
      if( geoCirclecoll( player.x, player.y, PLAYERRADIUS, ((x + 0.5)*BLOCKAXIS), ((y + 0.5)*BLOCKAXIS), SLOWDOWNRADIUS ) )
      {
        return 1;
      }
    }
  }

  return 0;
}

int gamePlayerCoinColl()
{
  int x, y;
  int sx, sy;

  sx = geoLimit( player.x/BLOCKAXIS - 1, 0, geoLIMITMAX );
  sy = geoLimit( player.y/BLOCKAXIS - 1, 0, geoLIMITMAX );

  for( x = sx; x < geoLimit( sx + 3, 0, lvl.w ); x++ )
  for( y = sy; y < geoLimit( sy + 3, 0, lvl.h ); y++ )
  {
    if( ISCOIN( lvl.block[x][y] ) )
    {
      if( geoCirclecoll( player.x, player.y, PLAYERRADIUS, ((x + 0.5)*BLOCKAXIS), ((y + 0.5)*BLOCKAXIS), COINRADIUS ) )
      {
        lvl.block[x][y] = '/';
        return 1;
      }
    }
  }

  return 0;
}

int gamePlayerKillerColl()
{
  int x, y;
  int sx, sy;

  sx = geoLimit( player.x/BLOCKAXIS - 1, 0, geoLIMITMAX );
  sy = geoLimit( player.y/BLOCKAXIS - 1, 0, geoLIMITMAX );

  for( x = sx; x < geoLimit( sx + 3, 0, lvl.w ); x++ )
  for( y = sy; y < geoLimit( sy + 3, 0, lvl.h ); y++ )
  {
    if( ISKILLER( lvl.block[x][y] ) )
    {
      if( geoCirclecoll( player.x, player.y, PLAYERRADIUS, ((x + 0.5)*BLOCKAXIS), ((y + 0.5)*BLOCKAXIS), KILLERRADIUS ) )
      {
        return 1;
      }
    }
  }

  return 0;
}

int gamePlayerPFinishColl()
{
  int x, y;
  int sx, sy;

  sx = geoLimit( player.x/BLOCKAXIS - 1, 0, geoLIMITMAX );
  sy = geoLimit( player.y/BLOCKAXIS - 1, 0, geoLIMITMAX );

  for( x = sx; x < geoLimit( sx + 3, 0, lvl.w ); x++ )
  for( y = sy; y < geoLimit( sy + 3, 0, lvl.h ); y++ )
  {
    if( ISPFINISH( lvl.block[x][y] ) )
    {
      if( geoCirclecoll( player.x, player.y, PLAYERRADIUS, ((x + 0.5)*BLOCKAXIS), ((y + 0.5)*BLOCKAXIS), PFINISHRADIUS ) )
      {
        return 1;
      }
    }
  }

  return 0;

}

void gameCalculate()
{
  int point;
  int dir;
  int turnx, turny;
  int circlecoll, circlecollx, circlecolly;
  int collcolor;
  int particles, particle, slot, fslot;
  double colldir;
  double ox, oy;
  double csx, csy;
  double direction, dist;


  //--Delay Start--//
    if( game_levelframe < MAPSTARTCOUNTDELAY * 3 )
    {
      cntrl_key.b.pressed = 0;
      cntrl_key.shleft.pressed = 0;

      lvl.lastframetime = SDL_GetTicks();
      lvl.neededtime = 0;
    }

  //--Check time--//
    lvl.neededtime += (SDL_GetTicks() - lvl.lastframetime);
    lvl.lastframetime = SDL_GetTicks();


  //--Sounds--//
    if( cntrl_key.menu.newpressed ) sfxPlaySFX( media.sfx.button );



  //--Player--//
    if( cntrl_key.left.pressed ) player.wdir += player.rotostep;
    if( cntrl_key.right.pressed ) player.wdir -= player.rotostep;
    if( cntrl_key.b.pressed ) player.acc = 1; else player.acc = 0;
    if( cntrl_key.shleft.pressed ) player.slowmotion = 1; else player.slowmotion = 0;

    turnx = turny = 0;
    circlecoll = circlecollx = circlecolly = 0;
    collcolor = 0;


    //--Move--//
      ox = player.x;
      oy = player.y;

      //--X - Direction--//
        player.x += cos( player.mdir ) * player.mspeed + cos( player.wdir ) * PLAYERCURRENTACC;
          dir = player.x > ox ? 1 : player.x < ox ? -1 : 0;

          while( gamePlayerEnvColl( &circlecoll, &circlecollx, &circlecolly, &collcolor ) && dir != 0 )
          {
            turnx = 1;
            player.x -= PLAYERUNCOLLSTEP * dir;

            if( (player.x <= ox && dir == 1) || (player.x >= ox && dir == -1) )
            {
              player.x = ox;
              break;
            }
          }


      //--Y - Direction--//
        player.y += -sin( player.mdir ) * player.mspeed - sin( player.wdir ) * PLAYERCURRENTACC;
          dir = player.y > oy ? 1 : player.y < oy ? -1 : 0;

          while( gamePlayerEnvColl( &circlecoll, &circlecollx, &circlecolly, &collcolor ) && dir != 0 )
          {
            turny = 1;
            player.y -= PLAYERUNCOLLSTEP * dir;

            if( (player.y <= oy && dir == 1) || (player.y >= oy && dir == -1) )
            {
              player.y = oy;
              break;
            }
          }




      //--New Movement--//
        player.mspeed = geoDistance2D( ox, oy, player.x, player.y ) - PLAYERSLOWMOTIONFACTOR * player.slowmotion * player.mspeed;
          player.mspeed = geoLimit( player.mspeed, 0, geoLIMITMAX );
        player.mdir = geoDirection2D( ox, oy, player.x, player.y );

        if( turnx || turny )
        {
          player.mspeed = REFLECTIONSPEED;
          player.mdir = _geoDirection2D( turnx ? -cos(player.mdir): cos(player.mdir), turny ? sin(player.mdir): -sin(player.mdir) );
        }

        if( circlecoll && !(turnx || turny ) )
        {
          player.mspeed = REFLECTIONSPEED;

          colldir = geoLineAngle( geoDirection2D( circlecollx * BLOCKAXIS + BLOCKAXIS/2, circlecolly * BLOCKAXIS + BLOCKAXIS/2, player.x, player.y ) + 90 );

          player.mdir = geoStandartAngle( player.mdir + 180 - colldir );
          player.mdir = _geoDirection2D( turnx ? -cos(player.mdir): cos(player.mdir), sin(player.mdir) ) + colldir;

        }


  //--Play acc sound--//
    if( player.acc && !sfxChunkPlaying(media.sfx.acc) ) sfxPlaySFX( media.sfx.acc );


  //--Coll with wall--//
    if( (turnx || turny) && (game_levelframe - player.lastwhit >= PLAYERWALLHITDELAY) )
    {
      sfxPlaySFX( media.sfx.whit );
      player.whits++;
      player.lastwhit = game_levelframe;
    }


  //--Special Fields--//
    if( gamePlayerSpeedUpColl() ) player.mspeed *= SPEEDUPFACTOR;
    if( gamePlayerSlowDownColl() ) player.mspeed *= SLOWDOWNFACTOR;
    if( gamePlayerCoinColl() )
    {
      sfxPlaySFX( media.sfx.coin );
      player.coins++;
    }
    if( gamePlayerKillerColl() )
    {
      lvl.finishtyp = FAILURE_KILLED;
      game_levelrunning = 0;
    };
    if( gamePlayerPFinishColl() )
    {
      lvl.finishtyp = SUCCESS;
      game_levelrunning = 0;
    };


  //--Slowdown Speed--//
    player.mspeed = geoRoundF( geoLimit( player.mspeed - PLAYERSLOWDOWN, 0, geoLIMITMAX ), 3);



  //--Take Fuel--//
    player.fuel = geoLimit( player.fuel - (PLAYERFUELNEED * player.acc) - (PLAYERSLOWMOTIONNEED * player.slowmotion), 0, geoLIMITMAX );
      if( player.fuel <= 0 )
      {
        lvl.finishtyp = FAILURE_OOF;
        game_levelrunning = 0;
      }






  //--Pause--//
    if( cntrl_key.menu.newpressed )
    {
      while( 1 )
      {
        //--Control--//
          cntrlUpdate();

          //--Sounds--//
            if( cntrl_key.b.newpressed ) sfxPlaySFX( media.sfx.button );
            if( cntrl_key.x.newpressed ) sfxPlaySFX( media.sfx.button );




        //--Calculate--//
          if( cntrl_key.x.newpressed )
          {
            lvl.finishtyp = FAILURE_EXITED;
            game_levelrunning = 0;
            break;
          }
           if( cntrl_key.b.newpressed )
          {
            lvl.lastframetime = SDL_GetTicks();
            break;
          }

        //--Draw--//
          stringColor( gfx_screen, gfx_screen->w/2 - strlen("GAME PAUSED")*4, gfx_screen->h/2 - 15, "GAME PAUSED", 0xffffffff );
          stringColor( gfx_screen, gfx_screen->w/2 - strlen("B - Continue")*4, gfx_screen->h/2, "B - Continue", 0xffffffff );
          stringColor( gfx_screen, gfx_screen->w/2 - strlen("X - Exit")*4, gfx_screen->h/2 + 15, "X - Exit", 0xffffffff );
          gfxShowScreen();
      }
    }






  //--Camera--//
    csx = (player.x - camera.x)/10;
    csy = (player.y - camera.y)/10;
    camera.x += csx;
    camera.y += csy;



  //--Background--//
    for( point = 0; point < background.points; point++ )
    {
      background.x[point] -= geoRoundF(csx, 3)/background.dept[point];
      background.y[point] -= geoRoundF(csy, 3)/background.dept[point];

      if( background.x[point] < 0 ) background.x[point] += gfx_screen->w;
      if( background.y[point] < 0 ) background.y[point] += gfx_screen->h;

      if( background.x[point] >= gfx_screen->w ) background.x[point] -= gfx_screen->w;
      if( background.y[point] >= gfx_screen->h ) background.y[point] -= gfx_screen->h;
    }

}

void gameDraw()
{
  int point;
  Uint8 alpha;
  int x, y;
  int sx, sy;
  int particle;
  char string[512];

  static SDL_Rect brect;
    brect.x = 0;
    brect.y = 0;
    brect.w = BLOCKAXIS;
    brect.h = BLOCKAXIS;


  //--Background--//
    for( point = 0; point < background.points; point++ )
    {
      alpha = 255 / geoLimit((background.dept[point]/5), 1, 255);
      gfxDrawPixel( gfx_screen, (Sint16)background.x[point], (Sint16)background.y[point], 0x0000000ff | alpha | alpha << 8 | alpha << 16 | alpha << 24 );
    }


  //--Level--//
    sx = geoLimit( (camera.x - gfx_screen->w/2) / BLOCKAXIS, 0, lvl.w );
    sy = geoLimit( (camera.y - gfx_screen->h/2) / BLOCKAXIS, 0, lvl.h );

    for( x = sx; x < geoLimit( sx + gfx_screen->w/BLOCKAXIS + 2, 0, lvl.w ); x++ )
    for( y = sy; y < geoLimit( sy + gfx_screen->h/BLOCKAXIS + 2, 0, lvl.h ); y++ )
    {

      //--Blocks--//
        if( ISBLOCK(lvl.block[x][y]) )
        {
          brect.w = BLOCKAXIS/2;
          brect.h = BLOCKAXIS/2;

          //--UpperLeft Corner--//
            brect.x = (((int)game_levelframe / BLOCKFRAMETIME) % BLOCKFRAMES) * BLOCKAXIS;
            brect.y = (gameBlockCornerFree( x, y, 0 ) ? BLOCKAXIS : 0);
            gfxDrawSprite( gfx_screen, media.block[BLOCKTYP(lvl.block[x][y])], &brect, BLOCKSCREENPOS( x, y ) );

          //--BottomLeft Corner--//
            brect.x = (((int)game_levelframe / BLOCKFRAMETIME) % BLOCKFRAMES) * BLOCKAXIS;
            brect.y = (gameBlockCornerFree( x, y, 3 ) ? BLOCKAXIS : 0) + BLOCKAXIS/2;
            gfxDrawSprite( gfx_screen, media.block[BLOCKTYP(lvl.block[x][y])], &brect, BLOCKSCREENPOS( x, y+0.5 ) );

          //--UpperRight Corner--//
            brect.x = (((int)game_levelframe / BLOCKFRAMETIME) % BLOCKFRAMES) * BLOCKAXIS + BLOCKAXIS/2;
            brect.y = (gameBlockCornerFree( x, y, 1 ) ? BLOCKAXIS : 0);
            gfxDrawSprite( gfx_screen, media.block[BLOCKTYP(lvl.block[x][y])], &brect, BLOCKSCREENPOS( x+0.5, y ) );

          //--BottomRight Corner--//
            brect.x = (((int)game_levelframe / BLOCKFRAMETIME) % BLOCKFRAMES) * BLOCKAXIS + BLOCKAXIS/2;
            brect.y = (gameBlockCornerFree( x, y, 2 ) ? BLOCKAXIS : 0) + BLOCKAXIS/2;
            gfxDrawSprite( gfx_screen, media.block[BLOCKTYP(lvl.block[x][y])], &brect, BLOCKSCREENPOS( x+0.5, y+0.5 ) );
        }
        brect.w = BLOCKAXIS;
        brect.h = BLOCKAXIS;


      //--Coin--//
        if( ISCOIN(lvl.block[x][y]) )
        {
          brect.x = (((int)game_levelframe / COINFRAMETIME) % COINFRAMES) * BLOCKAXIS;
          brect.y = 0;
          gfxDrawSprite( gfx_screen, media.coin, &brect, BLOCKSCREENPOS( x, y ) );
        }

      //--SpeedUp--//
        if( ISSPEEDUP(lvl.block[x][y]) )
        {
          brect.x = (((int)game_levelframe / SPEEDUPFRAMETIME) % SPEEDUPFRAMES) * BLOCKAXIS;
          brect.y = 0;
          gfxDrawSprite( gfx_screen, media.speedup, &brect, BLOCKSCREENPOS( x, y ) );
        }

      //--SlowDown--//
        if( ISSLOWDOWN(lvl.block[x][y]) )
        {
          brect.x = (((int)game_levelframe / SPEEDUPFRAMETIME) % SLOWDOWNFRAMES) * BLOCKAXIS;
          brect.y = 0;
          gfxDrawSprite( gfx_screen, media.slowdown, &brect, BLOCKSCREENPOS( x, y ) );
        }

      //--Killer--//
        if( ISKILLER(lvl.block[x][y]) )
        {
          brect.x = (((int)game_levelframe / KILLERFRAMETIME) % KILLERFRAMES) * BLOCKAXIS;
          brect.y = 0;
          gfxDrawSprite( gfx_screen, media.killer, &brect, BLOCKSCREENPOS( x, y ) );
        }

      //--PStart--//
        if( ISPSTART(lvl.block[x][y]) )
        {
          brect.x = (((int)game_levelframe / PSTARTFRAMETIME) % PSTARTFRAMES) * BLOCKAXIS;
          brect.y = 0;
          gfxDrawSprite( gfx_screen, media.pstart, &brect, BLOCKSCREENPOS( x, y ) );
        }

      //--PFinish--//
        if( ISPFINISH(lvl.block[x][y]) )
        {
          brect.x = (((int)game_levelframe / PFINISHFRAMETIME) % PFINISHFRAMES) * BLOCKAXIS;
          brect.y = 0;
          gfxDrawSprite( gfx_screen, media.pfinish, &brect, BLOCKSCREENPOS( x, y ) );
        }
    }



  //--Player--//
    gfxDrawFilledCircle( gfx_screen, PLAYERSCREENMIDDLE, PLAYERRADIUS, 0xff800055 );
    gfxDrawCircle( gfx_screen, PLAYERSCREENMIDDLE, PLAYERRADIUS, 0xffa000ff );

    if( game_levelframe < MAPSTARTCOUNTDELAY*3 )
    {
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir) * PLAYERCOUNTDOWNSIZE, PLAYERSCREENMIDDLEY - sin(player.wdir) * PLAYERCOUNTDOWNSIZE, PLAYERSCREENMIDDLEX + cos(player.wdir + PLAYEROPENDEGREES) * PLAYERCOUNTDOWNSIZE, PLAYERSCREENMIDDLEY - sin(player.wdir + PLAYEROPENDEGREES) * PLAYERCOUNTDOWNSIZE, 0xff0000ff );
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir) * PLAYERCOUNTDOWNSIZE, PLAYERSCREENMIDDLEY - sin(player.wdir) * PLAYERCOUNTDOWNSIZE, PLAYERSCREENMIDDLEX + cos(player.wdir - PLAYEROPENDEGREES) * PLAYERCOUNTDOWNSIZE, PLAYERSCREENMIDDLEY - sin(player.wdir - PLAYEROPENDEGREES) * PLAYERCOUNTDOWNSIZE, 0xff0000ff );
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir + PLAYEROPENDEGREES) * PLAYERCOUNTDOWNSIZE, PLAYERSCREENMIDDLEY - sin(player.wdir + PLAYEROPENDEGREES) * PLAYERCOUNTDOWNSIZE, PLAYERSCREENMIDDLE, 0xff0000ff );
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir - PLAYEROPENDEGREES) * PLAYERCOUNTDOWNSIZE, PLAYERSCREENMIDDLEY - sin(player.wdir - PLAYEROPENDEGREES) * PLAYERCOUNTDOWNSIZE, PLAYERSCREENMIDDLE, 0xff0000ff );
    }
    else
    {
      #ifdef PLAYEREXTRASIZE
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir) * PLAYEREXTRASIZERADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir) * PLAYEREXTRASIZERADIUS, PLAYERSCREENMIDDLEX + cos(player.wdir + PLAYEROPENDEGREES) * PLAYEREXTRASIZERADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir + PLAYEROPENDEGREES) * PLAYEREXTRASIZERADIUS, 0xff0000ff );
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir) * PLAYEREXTRASIZERADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir) * PLAYEREXTRASIZERADIUS, PLAYERSCREENMIDDLEX + cos(player.wdir - PLAYEROPENDEGREES) * PLAYEREXTRASIZERADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir - PLAYEROPENDEGREES) * PLAYEREXTRASIZERADIUS, 0xff0000ff );
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir + PLAYEROPENDEGREES) * PLAYEREXTRASIZERADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir + PLAYEROPENDEGREES) * PLAYEREXTRASIZERADIUS, PLAYERSCREENMIDDLE, 0xff0000ff );
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir - PLAYEROPENDEGREES) * PLAYEREXTRASIZERADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir - PLAYEROPENDEGREES) * PLAYEREXTRASIZERADIUS, PLAYERSCREENMIDDLE, 0xff0000ff );
      #else
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir) * PLAYERRADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir) * PLAYERRADIUS, PLAYERSCREENMIDDLEX + cos(player.wdir + PLAYEROPENDEGREES) * PLAYERRADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir + PLAYEROPENDEGREES) * PLAYERRADIUS,0xff0000ff );
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir) * PLAYERRADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir) * PLAYERRADIUS, PLAYERSCREENMIDDLEX + cos(player.wdir - PLAYEROPENDEGREES) * PLAYERRADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir - PLAYEROPENDEGREES) * PLAYERRADIUS,0xff0000ff );
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir + PLAYEROPENDEGREES) * PLAYERRADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir + PLAYEROPENDEGREES) * PLAYERRADIUS, PLAYERSCREENMIDDLE, 0xff0000ff );
      gfxDrawLine( gfx_screen, PLAYERSCREENMIDDLEX + cos(player.wdir - PLAYEROPENDEGREES) * PLAYERRADIUS, PLAYERSCREENMIDDLEY - sin(player.wdir - PLAYEROPENDEGREES) * PLAYERRADIUS, PLAYERSCREENMIDDLE, 0xff0000ff );
      #endif
    }



  //--Count down--//
    if( game_levelframe < MAPSTARTCOUNTDELAY*4 )
    {
      brect.x = ((int)(game_levelframe/MAPSTARTCOUNTDELAY)) * 36;
      brect.y = 0;
      brect.w = brect.x == 3*36 ? 123 : 36;
      brect.h = 64;

      gfxDrawSprite( gfx_screen, media.etc.start, &brect, gfx_screen->w/2 - brect.w/2, gfx_screen->h/2 - brect.h/2 );

    }

  //--Infobar--//
    gfxDrawSprite( gfx_screen, media.small.coin, NULL, 5, 5 );
    sprintf( string, "%i/%i", player.coins, lvl.coins );
      stringColor( gfx_screen, 5 + 10, 5, string, 0xffffffff );

    gfxDrawSprite( gfx_screen, media.small.fuel, NULL, gfx_screen->w/4, 5 );
    sprintf( string, "%.2f", player.fuel, 100 );
      stringColor( gfx_screen, gfx_screen->w/4 + 10, 5, string, 0xffffffff );

    gfxDrawSprite( gfx_screen, media.small.clock, NULL, gfx_screen->w/2, 5 );
    sprintf( string, "%.2f", ((double)lvl.neededtime)/1000 );
      stringColor( gfx_screen, gfx_screen->w/2 + 10, 5, string, 0xffffffff );

    gfxDrawSprite( gfx_screen, media.small.whit, NULL, gfx_screen->w*3/4, 5 );
    sprintf( string, "%i", player.whits );
      stringColor( gfx_screen, gfx_screen->w*3/4 + 10, 5, string, 0xffffffff );



}

void gameUnloadMap()
{
  int column;

  for( column = 0; column < lvl.w; column++ )
  {
    free( lvl.block[column] );
  }

  free( lvl.block );

}

void gameMapFinishScreen()
{
  char string[512];
  long points_time, points_coins, points_whits, points_extra;


  //--Sounds--//
    if( lvl.finishtyp == SUCCESS )
    {
      sfxPlaySFX( media.sfx.success );
    }
    else if( lvl.finishtyp != FAILURE_SKIP )
    {
      sfxPlaySFX( media.sfx.failure );
    }



  if( lvl.finishtyp == SUCCESS )
  {
    //--Backup complete - data--//
      lvl.complete.time = lvl.neededtime;
      lvl.complete.whits = player.whits;
      lvl.complete.coins = player.coins;



    //--Presets--//
      lvl.complete.medal_time = lvl.complete.medal_coins = lvl.complete.medal_whits = lvl.complete.medal_total = 0;
      points_time = points_coins = points_whits = points_extra = 0;
      lvl.complete.points = 0;



    //--Count points--//
      //--From time--//
        if( lvl.complete.time <= lvl.points.time_max )
        {
          points_time += (lvl.points.time_max - lvl.complete.time) * POINTSTIME;

          if( lvl.complete.time <= lvl.points.time_bronze )
          {
            if( lvl.complete.time <= lvl.points.time_silver )
            {
              if( lvl.complete.time <= lvl.points.time_gold )
              {
                points_time += POINTSTIMEGOLDMEDAL;
                lvl.complete.medal_time = 3;
              }
              else
              {
                points_time += POINTSTIMESILVERMEDAL;
                lvl.complete.medal_time = 2;
              }
            }
            else
            {
              points_time += POINTSTIMEBRONZEMEDAL;
              lvl.complete.medal_time = 1;
            }
          }
        }


      //--From coins--//
        points_coins += lvl.complete.coins * POINTSCOIN;

        if( lvl.complete.coins >= lvl.points.coins_bronze )
        {
          if( lvl.complete.coins >= lvl.points.coins_silver )
          {
            if( lvl.complete.coins >= lvl.points.coins_gold )
            {
              points_coins += POINTSCOINSGOLDMEDAL;
              lvl.complete.medal_coins = 3;
            }
            else
            {
              points_coins += POINTSCOINSSILVERMEDAL;
              lvl.complete.medal_coins = 2;
            }
          }
          else
          {
            points_coins += POINTSCOINSBRONZEMEDAL;
            lvl.complete.medal_coins = 1;
          }

          if( lvl.complete.coins == lvl.coins )
          {
            lvl.complete.medal_coins = 4;
            points_coins += POINTSCOINPERFECT;
          }
        }


      //--From whits--//
        if( lvl.complete.whits <= lvl.points.whits_max )
        {
          points_whits += (lvl.points.whits_max - lvl.complete.whits) * POINTSWHITS;

          if( lvl.complete.whits <= lvl.points.whits_bronze )
          {
            if( lvl.complete.whits <= lvl.points.whits_silver )
            {
              if( lvl.complete.whits <= lvl.points.whits_gold )
              {
                points_whits += POINTSWHITSGOLDMEDAL;
                lvl.complete.medal_whits = 3;
              }
              else
              {
                points_whits += POINTSWHITSSILVERMEDAL;
                lvl.complete.medal_whits = 2;
              }
            }
            else
            {
              points_whits += POINTSWHITSBRONZEMEDAL;
              lvl.complete.medal_whits = 1;
            }
          }

          if( lvl.complete.whits == 0 )
          {
            lvl.complete.medal_whits = 4;
            points_whits += POINTSWHITSPERFECT;
          }
        }




      //--From all perfect--//
        if( lvl.complete.medal_time == 3 && lvl.complete.coins == lvl.coins && lvl.complete.whits == 0 )
        {
          points_extra += POINTSPERFECT;
        }



      //--Make sum--//
        lvl.complete.points = points_time + points_coins + points_whits + points_extra;



      //--Total medal--//
        if( lvl.complete.points >= lvl.points.total_bronze )
        {
          if( lvl.complete.points >= lvl.points.total_silver )
          {
            if( lvl.complete.points >= lvl.points.total_gold )
            {
              lvl.complete.medal_total = 3;
            }
            else
            {
              lvl.complete.medal_total = 2;
            }
          }
          else
          {
            lvl.complete.medal_total = 1;
          }
        }


    //--Update Save--//
      //--Time--//
        if( (lvl.complete.time < sav.map[lvl.mapid]->best_time) || sav.map[lvl.mapid]->best_time == -1 )
        {
          sav.map[lvl.mapid]->best_time = lvl.complete.time;
          sav.map[lvl.mapid]->best_timemedal = lvl.complete.medal_time;
        }

      //--Coins--//
        if( (lvl.complete.coins > sav.map[lvl.mapid]->best_coins) || sav.map[lvl.mapid]->best_coins == -1 )
        {
          sav.map[lvl.mapid]->best_coins = lvl.complete.coins;
          sav.map[lvl.mapid]->best_coinsmedal = lvl.complete.medal_coins;
        }

      //--WHits--//
        if( (lvl.complete.whits < sav.map[lvl.mapid]->best_whits) || sav.map[lvl.mapid]->best_whits == -1 )
        {
          sav.map[lvl.mapid]->best_whits = lvl.complete.whits;
          sav.map[lvl.mapid]->best_whitsmedal = lvl.complete.medal_whits;
        }

      //--Total--//
        if( (lvl.complete.points > sav.map[lvl.mapid]->best_totalpoints) || sav.map[lvl.mapid]->best_totalpoints == -1 )
        {
          sav.map[lvl.mapid]->best_totalpoints = lvl.complete.points;
          sav.map[lvl.mapid]->best_totalmedal = lvl.complete.medal_total;
        }

      //Complete
        if( lvl.complete.medal_time >= lvl.completemedal && lvl.complete.medal_coins >= lvl.completemedal && lvl.complete.medal_whits >= lvl.completemedal && lvl.complete.medal_total >= lvl.completemedal )
        {
          sav.map[lvl.mapid]->completed = 1;
        }



    //--Save state--//
      gameSaveSav();
  }



  //--Display info--//
    while( lvl.finishtyp != FAILURE_SKIP )
    {
      //-Control--//
        cntrlUpdate();

        //--Sounds--//
          if( cntrl_key.b.newpressed ) sfxPlaySFX( media.sfx.button );
          if( cntrl_key.x.newpressed ) sfxPlaySFX( media.sfx.button );



      //--Calculate--//
        if( cntrl_key.b.newpressed ) break;
        if( cntrl_key.x.newpressed ) break;



      //--Draw--//
        //--The block around--//
          gfxDrawRectangle( gfx_screen, gfx_screen->w*1/4 - 25, gfx_screen->h*1/4 - 10, gfx_screen->w*2/3, gfx_screen->h*2/4, 0xffffffff  );

        if( lvl.finishtyp == SUCCESS )
        {

          //--Top info text--//
            sprintf( string, "You finished %s", mainmap.map[lvl.mapid]->name );
            stringColor( gfx_screen, gfx_screen->w/2 - strlen(string)*4, 25, string, 0xffffffff );


          //--Time--//
            gfxDrawSprite( gfx_screen, media.small.clock, NULL, gfx_screen->w*1/4 - 15,  gfx_screen->h*1/4 );
            sprintf( string, "%.2f", (double)lvl.neededtime/1000 );
              stringColor( gfx_screen, gfx_screen->w*1/4, gfx_screen->h*1/4, string, 0xffffffff );

            if( lvl.complete.time == sav.map[lvl.mapid]->best_time )
              gfxDrawSprite( gfx_screen, media.small.top, NULL, gfx_screen->w*1/4 + strlen(string) * 8 + 10,  gfx_screen->h*1/4 );

            sprintf( string, "Points: %i", points_time );
              stringColor( gfx_screen, gfx_screen->w*1/4 + 15, gfx_screen->h*1/4 + 15, string, 0xffffffff );

            gfxDrawSprite( gfx_screen, MEDALSPRITE( lvl.complete.medal_time ), NULL, gfx_screen->w*1/4 + 130, gfx_screen->h*1/4 - 5 );


          //--Coins--//
            gfxDrawSprite( gfx_screen, media.small.coin, NULL, gfx_screen->w*1/4 - 15,  gfx_screen->h*1/4 + 40 );
            sprintf( string, "%i/%i", lvl.complete.coins, lvl.coins );
              stringColor( gfx_screen, gfx_screen->w*1/4, gfx_screen->h*1/4 + 40, string, 0xffffffff );

            if( lvl.complete.coins == sav.map[lvl.mapid]->best_coins )
              gfxDrawSprite( gfx_screen, media.small.top, NULL, gfx_screen->w*1/4 + strlen(string) * 8 + 10,  gfx_screen->h*1/4 + 40 );

            sprintf( string, "Points: %i", points_coins );
              stringColor( gfx_screen, gfx_screen->w*1/4 + 15, gfx_screen->h*1/4 + 15 + 40, string, 0xffffffff );

            gfxDrawSprite( gfx_screen, MEDALSPRITE( lvl.complete.medal_coins ), NULL, gfx_screen->w*1/4 + 130, gfx_screen->h*1/4 - 5 + 40 );


          //--Coins--//
            gfxDrawSprite( gfx_screen, media.small.whit, NULL, gfx_screen->w*1/4 - 15,  gfx_screen->h*1/4 + 80 );
            sprintf( string, "%i", lvl.complete.whits );
              stringColor( gfx_screen, gfx_screen->w*1/4, gfx_screen->h*1/4 + 80, string, 0xffffffff );

            if( lvl.complete.whits == sav.map[lvl.mapid]->best_whits )
              gfxDrawSprite( gfx_screen, media.small.top, NULL, gfx_screen->w*1/4 + strlen(string) * 8 + 10,  gfx_screen->h*1/4 + 80 );

            sprintf( string, "Points: %i", points_whits );
              stringColor( gfx_screen, gfx_screen->w*1/4 + 15, gfx_screen->h*1/4 + 15 + 80, string, 0xffffffff );

            gfxDrawSprite( gfx_screen, MEDALSPRITE( lvl.complete.medal_whits ), NULL, gfx_screen->w*1/4 + 130, gfx_screen->h*1/4 - 5 + 80 );


          //--Total--//
            sprintf( string, "Total points: %i", lvl.complete.points );
              stringColor( gfx_screen, gfx_screen->w*1/4 + 15, gfx_screen->h*1/4 + 130, string, 0xffffffff );

            if( lvl.complete.points == sav.map[lvl.mapid]->best_totalpoints )
              gfxDrawSprite( gfx_screen, media.small.top, NULL, gfx_screen->w*1/4 + strlen(string) * 8 + 10 + 15,  gfx_screen->h*1/4 + 130 );


            gfxDrawSprite( gfx_screen, MEDALSPRITE( lvl.complete.medal_total ), NULL, gfx_screen->w*1/4 + 190, gfx_screen->h*1/4 - 16 + 130 );


         //--Complete--//
          if( lvl.complete.medal_time >= lvl.completemedal && lvl.complete.medal_coins >= lvl.completemedal && lvl.complete.medal_whits >= lvl.completemedal && lvl.complete.medal_total >= lvl.completemedal )
          {
            stringColor( gfx_screen, gfx_screen->w*1/4 + 15, gfx_screen->h*1/4 + 150, "...completed!", 0xffffffff  );
          }
          else if( !sav.map[lvl.mapid]->completed )
          {
            stringColor( gfx_screen, gfx_screen->w*1/4 + 15, gfx_screen->h*1/4 + 150, "...remains uncompleten!", 0xffffffff  );
          }



        }
        else
        {
          //--Top info text--//
            sprintf( string, "You failed on %s!", mainmap.map[lvl.mapid]->name );
            stringColor( gfx_screen, gfx_screen->w/2 - strlen(string)*4, 25, string, 0xffffffff );


          //--Box info text--//
            switch( lvl.finishtyp )
            {
              case FAILURE_EXITED:
                sprintf( string, "You left the map!");
              break;
              case FAILURE_KILLED:
                sprintf( string, "You hitted the death!");
              break;
              case FAILURE_OOF:
                sprintf( string, "You ran out of fuel!");
              break;
              default:
                sprintf( string, "Unknown failure!");
            }

            stringColor( gfx_screen, gfx_screen->w*1/2 - strlen(string) * 4, gfx_screen->h*1/2 - 30, string, 0xffffffff );

        }


      //--ShowScreen--//
        gfxShowScreen();


    }





}

void game()
{
  char *mappath;

  gameMainSetup();
  gameLoadMedia();
  gameLoadMainmap();
  #ifdef ENABLE_VERSION_1_1
  gameLoadSidequestList();
  #endif


  while( gameMainmenu() )
  {
      while( game_mainrunning )
      {

        mappath = gameMainmap();
          if( !game_mainrunning ) break;

        gameLoadMap( mappath );
          game_levelrunning = 1;
        gameFuelmenu();
        gameMapSetup();


        while( game_mainrunning && game_levelrunning )
        {
          cntrlUpdate();
          gameCalculate();
          gameDraw();
          gfxShowScreen();
          game_levelframe ++;
        }
        gameUnloadMap();
        gameMapFinishScreen();
      }
  }

  gameGoodbyeScreen();
}

void gameGoodbyeScreen()
{

  int py;
  char string[2048];




  while( 1 )
  {
    //--Control--//
      cntrlUpdate();


    //--Calc--//
      if( cntrl_key.b.newpressed ) break;


    //--Draw--//
      gfxDrawRectangle( gfx_screen, 15, 15, gfx_screen->w - 30, gfx_screen->h - 30, 0xffffffff );

      stringColor( gfx_screen, gfx_screen->w/2 - strlen("Thanks for playing!")*4, 25, "Thanks for playing!", 0xffffffff );
      sprintf( string, "%s","Fy.WoD! is available under the GPL. You should have received a copy along with the source of this game. If not please contact Schnatterplatsch@t-online.de!!! " );
      py = gfxPrintStringBox( gfx_screen, 15 + 15, 20 + 30, gfx_screen->w - 30 - 15 - 5, gfx_screen->h - 30 - 15 - 5, string, 0xffffffff );
      sprintf( string, "%s","All used media is either selfmade or copyright - free! " );
      gfxPrintStringBox( gfx_screen, 15 + 15, py + 15, gfx_screen->w - 30 - 15 - 5, gfx_screen->h - py - 15 - 5, string, 0xffffffff );
      stringColor( gfx_screen, gfx_screen->w - strlen("Goodbye!")*8 - 8 - 15, gfx_screen->h - 35, "Goodbye!", 0xffffffff );


      gfxShowScreen();

  }

}
