/*
  loads.c
*/

#include "global.h"
#include "stdio.h"
#include "macros.h"
#include "config.h"
#include "loads.h"

#include "allegro.h"

/*************************************************************************
 patch: ric@asbyte.com.br
**************************************************************************/
/** \file loads.c
 * \brief Old functions to load sprites,pcx, etc... without crashing and with error logon
 */

static char c_midi_ok=0;
/*************************************************************************
 * __load_sprite__() look in macros.h the xload_pcx macro 
 *
 * this function replace the load_pcx function of allegro and add the green 
 *    clone player.
 * __load_sprite__() verify if pcx file is found and report to logfile.
 **************************************************************************/
#if GAME_DEBUG > 0
BITMAP *__load_sprite__( const char *file, PALLETE Pal, char *n_file , int n_line )
{
#else
  BITMAP * __load_sprite__( const char * file, PALLETE Pal )
  {
#endif
    BITMAP *p1;
    BITMAP *p2;
    int missing;

    missing=0;
#if GAME_DEBUG > 0
    missing=check_file( file, n_file, n_line );
#else
    missing=check_file( file );
#endif
    if(missing == 1){
      p2 = create_bitmap( 113,16 );
      rectfill( p2, 0, 0, 112,15, makecol( 255, 0, 0 ) );
      rect( p2, 0, 0, 112,15, makecol( 0, 0, 255 ) );
      select_palette( *pal[0]);
      textout_ex( p2, small_font, "Image Missing!", 2, 4, -1 , -1);
      unselect_palette();
    }else{
      p2 = load_pcx ( file , Pal );
    }
	
    p1 = create_bitmap ( p2->w, p2->h );

    fill_sprite( p1 );

    draw_sprite_h_flip( p1, p2, 0, 0 );
    fill_sprite( p2 );

    if ( clone )
      {
	set_trans_blender( 0, 255, 0, 0 );
	draw_lit_sprite( p2, p1, 0, 0, 100 );
      }
    else
      {
	draw_sprite( p2, p1, 0, 0 );
      }
    destroy_bitmap( p1 );
    return p2;
  }

  /*************************************************************************
   * __xload_pcx__() look in macros.h the xload_pcx macro 
   *
   * this function replace the load_pcx function of allegro.
   * __xload_pcx__() verify if pcx file is found and report to logfile.
   **************************************************************************/
#if GAME_DEBUG > 0
  BITMAP *__xload_pcx__( const char * file, PALLETE Pal, char * n_file , int n_line )
  {
#else
    BITMAP * __xload_pcx__( const char * file, PALLETE Pal )
    {
#endif
      BITMAP * PCX_RETURNED;
      int missing;
      char *name_image;
      
      missing = 0;
      
#if GAME_DEBUG > 0
      missing=check_file( file, n_file, n_line );
#else
      missing=check_file( file );
#endif

      if ( missing == 1 ){
	//TRON("CREATING IMAGE...");
	PCX_RETURNED = create_bitmap( 113,16 ); //load_pcx( "sprites" DIR_BAR "miss.pcx", Pal );
        rectfill( PCX_RETURNED, 0, 0, 112,15, makecol( 255, 0, 0 ) );
	rect( PCX_RETURNED, 0, 0, 112,15, makecol( 0, 0, 255 ) );
	select_palette(default_palette);
	textout_ex( PCX_RETURNED, small_font, "Image Missing!", 2, 4, -1, -1 );
	unselect_palette();
	//	    TRON("OK");
      }else{
	name_image = (char*)calloc(255,sizeof(char));
	sprintf(name_image,"Loading %s",file);
	TRON(name_image);
	PCX_RETURNED = load_pcx( file, Pal );		
	TRON("OK pcx loaded");
      }
      //TRON("OK x_load_pcx");
      return PCX_RETURNED;
    }
    
    /*************************************************************************
     * __xload_midi()__ 
     *
     * this function replace the load_midi function of allegro.
     * __xload_midi()__ verify if midi file is found and report to logfile.
     **************************************************************************/
#if GAME_DEBUG > 0
    MIDI *__xload_midi__( const char * file, char * n_file, int n_line)
    {
#else
      MIDI *__xload_midi__( const char * file )
      {
#endif	
	MIDI * tmpmidi;
	static int missing;

	missing=0;
#if GAME_DEBUG > 0
	missing=check_file( file, n_file, n_line );
#else
	missing=check_file( file );
#endif
 	if(missing==1){
          tmpmidi=NULL;
	  c_midi_ok=0;
	}else{
	  c_midi_ok=1;	
          tmpmidi=load_midi( file );
	}
	return tmpmidi;	
      }

      /*************************************************************************
       * xload_sample() 
       *
       * this function replace the load_sample function of allegro.
       * xload_sample() verify if sample file is found and report to logfile.
       **************************************************************************/

#if GAME_DEBUG > 0
      SAMPLE *__xload_sample__( const char * file, char *n_file, int n_line  )
      {
#else
	SAMPLE *__xload_sample__( const char * file )
	{
#endif	
	  SAMPLE *tmpsample;
	  static char missing;

	  missing=0;
	
#if GAME_DEBUG > 0
	  missing=check_file( file, n_file, n_line );
#else
	  missing=check_file( file );
#endif
	  if(missing==1){
	    tmpsample=create_sample(8,2,14400,0);
	  }else{
	    tmpsample=load_sample( file );
	  }

	  return tmpsample;
	}

/******************************************************
 * check_file( filename ) 
 *   verify if filename is found and report to logfile
 *******************************************************/
#if GAME_DEBUG > 0
 char check_file( const char * file, char * n_file , int n_line ){
#else
 char check_file( const char * file ){
#endif
   static char missing; 
   missing =0 ;
   if (!exists(file)){
#if GAME_DEBUG > 0
     sprintf( log_mess, "FILE:%s LINE:%d ERROR: file (%s) not found! ",n_file, n_line, file );
     __tron__( log_mess, n_file, n_line );
#else
     sprintf( log_mess, "ERROR: file (%s) not found! ", file );
     TRON( log_mess );
#endif
     missing = 1;
   }
   return missing;
 }
	  
/****************************************/
 char file_missing( const char * file ){
   static FILE *tmpfile;
   static char missing;
   
   missing =0;
   if ( ( tmpfile=fopen( file, "r" ) ) == NULL )
     {
       missing = 1;
     }else{
     fclose( tmpfile );
   }
   
   return missing;
 }
 
 /****************************************/
 char midi_ok( void ){
   return c_midi_ok;
 }
 
