/*
    mp3.h
*/

#ifndef MP3_H
#define MP3_H

#include "global.h"

extern int MP3_Open( char *mp3file );
extern int MP3_Play( void );
extern int MP3_Close( void );
extern int poll_mp3_file(MP3FILE *mp3);

#endif //MP3_H
