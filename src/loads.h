/*
    loads.h
    //template//
*/
#ifndef LOADS_H
#define LOADS_H
#include "config.h"

#if GAME_DEBUG > 0
BITMAP *__load_sprite__( const char *file, PALLETE Pal, char *n_file , int n_line );
BITMAP *__xload_pcx__( const char *file, PALLETE Pal, char *n_file , int n_line );
//char *check_file_or_similar( const char * file, char * n_file , int n_line );
char check_file( const char * file, char * n_file , int n_line );
SAMPLE *__xload_sample__( const char *file , char * n_file , int n_line );
MIDI *__xload_midi__( const char *file, char * n_file , int n_line );
#else
BITMAP *__load_sprite__( const char *file, PALLETE Pal );
BITMAP *__xload_pcx__( const char *file, PALLETE Pal );
//char *check_file_or_similar( const char * file );
char check_file( const char * file );
SAMPLE *__xload_sample__( const char *file );
MIDI *__xload_midi__( const char *file );
#endif

char file_missing( const char * file );
char midi_ok( void );

#endif //LOADS_H
