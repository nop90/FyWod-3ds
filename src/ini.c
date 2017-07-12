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

#include "ini.h"


void iniInit()
{

  printf("'iniInit()' done!\n");

}



iniStream *iniLoad( char *path )
{

  long cpos, epos, ltpos, mtpos;
  char cchar;
  int defines = 0;
  FILE *file;

  //Open .ini
    file = fopen( path , "r");
      if( file == NULL )
      {
        fprintf( stderr, "'iniLoad()': '%s' couldn't be opened!\n", path );
        return NULL;
      }

  iniStream *stream = malloc( sizeof( iniStream ) );
    stream->buffer = malloc( INI_BUFFER );


  //Read and parse
    cpos = 0;
    while( ( !feof( file ) ) && ( cpos < INI_BUFFER ) )
    {
      cchar = fgetc( file );
      if( ( cchar != '\t' ) && ( cchar != ' ')  )
      {
        stream->buffer[cpos++] = cchar;
      }
    }
    stream->buffer[cpos - 1] = '\0';


  fclose( file );

  return stream;

}


long iniSearch( iniStream *stream, char *section, char *key, long *size )
{

  if( size == NULL){ return -1; }

  char ssection[ strlen( section ) + 3 ];
      sprintf( ssection, "[%s]", section );
  long spos = (long) strstr( stream->buffer, ssection) - (long) stream->buffer ;
      if( spos < 0 ){ fprintf( stderr, "\t'iniSearch()': Section '%s' couldn't be found!\n",section ); *size = 0; return -1; }
  spos += strlen( section ) + 2;

  long sepos = iniGetMark( stream, spos, "\0[",2);
      if( sepos < 0 ){ fprintf( stderr, "\t'iniSearch()': Strange error: section end of '%s' couldnt be found!\n", section); *size = 0; return -1;  }
      sepos --;

  char skey[ strlen( key ) + 3 ];
      sprintf( skey, "\n%s=\0", key );
  long kpos = (long) strstr( &stream->buffer[spos], skey) - (long) stream->buffer ;
      if( ( kpos < 0 ) | ( kpos > sepos )){ fprintf( stderr, "\t'iniSearch()': Key '%s' couldn't be found in section '%s'!\n",key,section ); *size = 0; return -1; }
  kpos += strlen( key ) + 2;

  #ifdef WIN32
    long kepos = iniGetMark( stream, kpos, "#\0\n[", 4);
  #endif

  #ifndef WIN32
    long kepos = iniGetMark( stream, kpos, "#\0\r[", 4);
  #endif

    if( kepos < 0 ){fprintf( stderr, "\t'iniSearch()': Strange error: key end of '%s' in '%s' couldnt be found!\n", key, section); *size = 0; return -1;  }
    kepos --;


  *size = kepos - kpos + 1;
  if( *size <= 0 ) fprintf( stderr, "\t'iniSearch()': Key '%s' in '%s' has a lenght of '%li'!\n", key, section, *size);

  return kpos;

}


long iniGetMark( iniStream *stream, long pos, char *mark, int marks )
{

  if( stream == NULL ) return 0;

  if( marks <= 0 ) return -1;

  int cmark, nmark = 0, cmarks = 0;
  long mpos[marks], tpos;

  for( cmark = 0; cmark < marks; cmark++ ){
      tpos = (long) strchr( &stream->buffer[pos], mark[cmark] );
      if( tpos != 0 ){ mpos[cmarks] = tpos; cmarks ++;}
  }

  if( cmarks == 0 ) return -1;

  for( cmark = 1; cmark < cmarks; cmark++ ) if( mpos[cmark] < mpos[nmark] ) nmark = cmark;

  return mpos[nmark] - (long) stream->buffer;

}


int iniGetInt( iniStream *stream, char *section, char *key, int onerror)
{

  if( stream == NULL ) return onerror;

  int result;
  long size;
  long pos = iniSearch( stream, section, key, &size );
      if( pos < 0  || ( size <= 0 )){
          return onerror;
      }

  char temp = stream->buffer[ pos + size];
      stream->buffer[pos + size] = '\0';

      result = atoi( &stream->buffer[pos] );

      stream->buffer[pos + size] = temp;

  return result;
}


double iniGetDouble( iniStream *stream, char *section, char *key, double onerror)
{

  if( stream == NULL ) return onerror;

  double result;
  long size;
  long pos = iniSearch( stream, section, key, &size );
      if( pos < 0  || ( size <= 0 )){
        return onerror;
      }

  char temp = stream->buffer[pos + size];
      stream->buffer[pos + size] = '\0';

      result = strtod( &stream->buffer[pos],NULL );

      stream->buffer[pos + size] = temp;

  return result;
}

char iniGetChar( iniStream *stream, char *section, char *key, char onerror)
{

  if( stream == NULL ) return onerror;

  char result;
  long size;
  long pos = iniSearch( stream, section, key, &size );
    if( pos < 0 || ( size <= 0 ) ){
      return onerror;
    }

  result = stream->buffer[pos];

  return result;
}

char *iniGetStr( iniStream *stream, char *section, char *key, char *onerror)
{
  if( stream == NULL ) return onerror;

  char *result;
  long size;
  int cchr;
  long pos = iniSearch( stream, section, key, &size );
    if( pos < 0 || ( size <= 0 )){
      return onerror;
    }

  char temp = stream->buffer[pos + size];
      stream->buffer[pos + size] ='\0';

  result = malloc( size + 1 );
    sprintf( result, "%s\0",&stream->buffer[pos] );

  stream->buffer[pos + size] = temp;

  for( cchr = 0; cchr < strlen( result ); cchr++ )
  {
    if( result[cchr] == '%' ) result[cchr] = ' ';
  }

  return result;

}

int iniSection( iniStream *stream, char *section )
{

  if( stream == NULL ) return 0;

  char *ssection =  malloc( strlen( section ) + 3 );
      sprintf( ssection, "[%s]", section );

  char* spos = strstr( stream->buffer, ssection);
  free( ssection );

  if(spos == NULL) return 0;
  else return 1;

}

int iniKey( iniStream *stream, char *section, char *key )
{

  if( stream == NULL ) return 0;

  long size;

  if( iniSearch( stream, section, key, &size) == -1) return 0;
  else return 1;

}

int iniNSections( iniStream *stream, char *section )
{

  if( stream == NULL ) return 0;

  char str[ strlen( section ) + 8 ];

  int sections = 0;
  while( 1 )
  {
      sprintf( str, "%s%i", section, sections );
      if( !iniSection( stream, str ) ) break;
      sections ++;
  }

  return sections;

}

int iniNKeys( iniStream *stream, char *section, char *key )
{

  if( stream == NULL ) return 0;

  char str[ strlen( key ) + 8 ];

  int keys = 0;
  while( 1 )
  {
      sprintf( str, "%s%i", key, keys );
      if( !iniKey( stream, section, str ) ) break;
      keys ++;
  }

  return keys;

}

void iniClose( iniStream *stream )
{
  if( stream == NULL ) return;

  free( stream->buffer );
  free( stream );

}






