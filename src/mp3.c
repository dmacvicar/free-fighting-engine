/*
    mp3.c
    code mainly copy from the example of almp3
 */

#include "config.h"
#include "stdio.h"
#include "macros.h"
#include "mp3.h"
#include "global.h"
#include "almp3.h"

#define DATASZ  (1<<15) /* (32768) amount of data to read from disk each time */
#define BUFSZ   (1<<16) /* (65536) size of audiostream buffer */

/** \file mp3.c
 * \brief functions to deal with mp3, mainly copy for original exemples of almp3
 */


MP3FILE *open_mp3_file(char *filename) {
  MP3FILE *p = NULL;
  PACKFILE *f = NULL;
  ALMP3_MP3STREAM *s = NULL;
  char data[DATASZ];
  int len;

  if (!(p = (MP3FILE *)malloc(sizeof(MP3FILE))))
    goto error;
  if (!(f = pack_fopen(filename, F_READ)))
    goto error;
  if ((len = pack_fread(data, DATASZ, f)) <= 0)
    goto error;
  if (len < DATASZ) {
    if (!(s = almp3_create_mp3stream(data, len, TRUE)))
      goto error;
  }
  else {
    if (!(s = almp3_create_mp3stream(data, DATASZ, FALSE)))
      goto error;
  }
  p->f = f;
  p->s = s;
  return p;

  error:
  pack_fclose(f);
  free(p);
  return NULL;
}


int play_mp3_file(MP3FILE *mp3, int buflen, int vol, int pan) {
  return almp3_play_mp3stream(mp3->s, buflen, vol, pan);
}


void close_mp3_file(MP3FILE *mp3) {
  if (mp3) {
    pack_fclose(mp3->f);
    almp3_destroy_mp3stream(mp3->s);
    free(mp3);
  }
}


int poll_mp3_file(MP3FILE *mp3) {
  char *data;
  long len;

  data = (char *)almp3_get_mp3stream_buffer(mp3->s);
  if (data) {
    len = pack_fread(data, DATASZ, mp3->f);
    if (len < DATASZ)
      almp3_free_mp3stream_buffer(mp3->s, len);
    else
      almp3_free_mp3stream_buffer(mp3->s, -1);
  }

  return almp3_poll_mp3stream(mp3->s);
}


int MP3_Open( char *mp3file )
{
  mp3 = open_mp3_file(mp3file);
  if (!(mp3))
    return -1;
  else
    return 0 ;
}

/***************************************************/
int MP3_Play( void )
{
  play_mp3_file(mp3, BUFSZ, 255, 128);
  return 0 ;
}

/****************************************************/
int MP3_Close( void )
{
  close_mp3_file(mp3);
  mp3 = NULL;
  return 0 ;
}
