#include <stdio.h>
#include <string.h>

#include "load_sprites.h"
#include "global.h"
#include "global_add.h"
#include "macros.h"
#include "logger.h"
#include "loads.h"
#include "string.h"

/** \file load_sprites.c
 * \brief Old functions to load each pcx of a character
 */

/* Start of LOAD FUNCTIONS */
void load_sprites1(char * name )
{
  char * result = NULL;
  char * message;

  message = (char*)calloc(255,sizeof(char));
  
  TRON( "load_sprites1()" );
  
  // sprintf( passeur, "sprites" DIR_BAR "%s" DIR_BAR, name );
  for ( num = 1; num < ( p1.statik.nbf + 1 ); ++num )
    {
      sprintf( file, "%sstatic%d.pcx", passeur, num );
      Player1.Static[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p1.walk.nbf + 1 ); ++num )
    {
      sprintf( file, "%swalk%d.pcx", passeur, num );
      Player1.Walk[ num ] = xload_pcx ( file , Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p1.spunch.nbf + 1 ); ++num )
    {
      sprintf( file, "%sspunch%d.pcx", passeur, num );
      Player1.Punch[ num ] = xload_pcx ( file , Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p1.wpunch.nbf + 1 ); ++num )
    {
      sprintf( file, "%swpunch%d.pcx", passeur, num );
      Player1.WPunch[ num ] = xload_pcx ( file , Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p1.gpunch.nbf + 1 ); ++num )
    {
      sprintf( file, "%sgpunch%d.pcx", passeur, num );
      Player1.GPunch[ num ] = xload_pcx ( file , Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p1.apunch.nbf + 1 ); ++num )
    {
      sprintf( file, "%sapunch%d.pcx", passeur, num );
      Player1.APunch[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p1.intro.nbf + 1 ); ++num )
    {
      sprintf( file, "%sintro%d.pcx", passeur, num );
      Player1.Kick[ num ] = xload_pcx ( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p1.gkick.nbf + 1 ); ++num )
    {
      sprintf( file, "%sgkick%d.pcx", passeur, num );
      Player1.GKick[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p1.wkick.nbf + 1 ); ++num )
    {
      sprintf( file, "%swkick%d.pcx", passeur, num );
      Player1.WKick[ num ] = xload_pcx( file , Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p1.hurt.nbf + 1 ); ++num )
    {
      sprintf( file, "%shurt%d.pcx", passeur, num );
      Player1.Hurt[ num ] = xload_pcx ( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p1.ghurt.nbf + 1 ); ++num )
    {
      sprintf( file, "%sghurt%d.pcx", passeur, num );
      Player1.GHurt[ num ] = xload_pcx ( file, 0 );
    }
  TRON( "loading..." );
  for ( num = 1; num < 6; ++num )
    {
      sprintf( file, "%sjump%d.pcx", passeur, num );
      Player1.Jump[ num ] = xload_pcx ( file , Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < 6; ++num )
    {
      sprintf( file, "%sko%d.pcx", passeur, num );
      Player1.KO[ num ] = xload_pcx ( file , Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < 5; ++num )
    {
      strcpy ( file, passeur );
      switch ( ( int ) num )
	{
	case 1 :
	  strcat ( file, "block1.pcx" );
	  Player1.Single[ 0 ] = xload_pcx ( file , 0 );
	  break;
	case 2 :
	  strcat ( file, "crouch1.pcx" );
	  Player1.Single[ 1 ] = xload_pcx ( file, Pal );
	  break;
	case 3 :
	  strcat ( file, "gblock1.pcx" );
	  Player1.Single[ 2 ] = xload_pcx ( file, Pal );
	  break;
	case 4 :
	  strcat ( file, "hurt1.pcx" );
	  Player1.Single[ 3 ] = xload_pcx ( file, Pal );
	  break;
	}
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p1.akick.nbf + 1 ); ++num )
    {
      sprintf( file, "%sakick%d.pcx", passeur, num );
      Player1.AKick[ num ] = xload_pcx ( file, Pal );
    }
  TRON( "loading..." );
  if ( p1.fireb.flg )
    {
      TRON( "loading..." );
      
      for ( num = 1; num < ( p1.fireb.nbf + 1 ); ++num )
	{
	  sprintf( file, "%sfireb%d.pcx", passeur, num );
	  Player1.FireB[ num ] = xload_pcx ( file, Pal );
	}
      TRON( "loading..." );
      
      for ( num = 1; num < ( p1.fball.nbf + 1 ); ++num )
	{
	  sprintf( file, "%sfball%d.pcx", passeur, num );
	  Player1.FBall[ num ] = xload_pcx ( file, Pal );
	}
      TRON( "loading..." );
      sprintf( file, "%sfireb.wav", passeur );
      hadoken1 = xload_sample ( file );
    }
  TRON( "loading..." );
  if ( p1.rush.flg )
    {
      TRON( "loading..." );
      for ( num = 1; num < ( p1.rush.nbf + 1 ); ++num )
	{
	  sprintf( file, "%srush%d.pcx", passeur, num );
	  Player1.Rush[ num ] = xload_pcx ( file, Pal );
	}
      TRON( "loading..." );
      
      sprintf( file, "%srush.wav", passeur );
      copter1 = xload_sample ( file );
    }
  TRON( "loading..." );
  if ( p1.smove.flg )
    {
      TRON( "loading..." );
      
      for ( num = 1; num < ( p1.smove.nbf + 1 ); ++num )
	{
	  sprintf( file, "%ssmove%d.pcx", passeur, num );
	  Player1.SMove[ num ] = xload_pcx ( file, Pal );
	}
      TRON( "loading..." );
      sprintf( file, "%ssmove.wav", passeur );
      dragon1 = xload_sample ( file );
    }
  TRON( "loading..." );
  // SPECIALS
  if ( p1.firebx.flg )
    {
      TRON( "loading..." );
      
      for ( num = 1; num < ( p1.firebx.nbf + 1 ); ++num )
	{
	  sprintf( file, "%sfirebx%d.pcx", passeur, num );
	  Player1.FireBX[ num ] = xload_pcx ( file, Pal );
	}
      TRON( "loading..." );
      
      for ( num = 1; num < ( p1.fballx.nbf + 1 ); ++num )
	{
	  sprintf( file, "%sfballx%d.pcx", passeur, num );
	  Player1.FBallX[ num ] = xload_pcx ( file, Pal );
	}
      TRON( "loading..." );
      sprintf( file, "%sfirebx.wav", passeur );
      hadokenx1 = xload_sample ( file );
    }
  TRON( "loading..." );
  if ( p1.rushx.flg )
    {
      TRON( "loading..." );
      
      for ( num = 1; num < ( p1.rushx.nbf + 1 ); ++num )
	{
	  sprintf( file, "%srushx%d.pcx", passeur, num );
	  Player1.RushX[ num ] = xload_pcx( file, Pal );
	}
      TRON( "loading..." );
      sprintf( file, "%srushx.wav", passeur );
      copterx1 = xload_sample ( file );
    }
  TRON( "loading..." );
  if ( p1.smovex.flg )
    {
      
      TRON( "loading..." );
      for ( num = 1; num < ( p1.smovex.nbf + 1 ); ++num )
	{
	  sprintf( file, "%ssmovex%d.pcx", passeur, num );
	  Player1.SMoveX[ num ] = xload_pcx ( file, Pal );
	}
      TRON( "loading..." );
      sprintf( file, "%ssmovex.wav", passeur );
      dragonx1 = xload_sample ( file );
    }
  TRON( "\nload_sprites1() - OK." );
  free(message);
  free(result);
}

/********************************************************/
void load_sprites2( char * name ){
  char * passeur;
  passeur = (char*)calloc(255,sizeof(char));
  TRON( "\nload_sprites2()" );
  // sprintf( passeur, "sprites" DIR_BAR "%s" DIR_BAR, name );
  
  for ( num = 1; num < ( p2.statik.nbf + 1 ); ++num )
    {
      sprintf( file, "%sstatic%d.pcx", passeur, num );
      Player2.Static[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  
  for ( num = 1; num < 5; ++num )
    {
      strcpy ( file, passeur );
      switch ( ( int ) num )
	{
	case 1 :
	  strcat ( file, "block1.pcx" );
	  Player2.Single[ 0 ] = xload_pcx( file, Pal );
	  break;
	case 2 :
	  strcat ( file, "crouch1.pcx" );
	  Player2.Single[ 1 ] = xload_pcx( file, Pal );
	  break;
	case 3 :
	  strcat ( file, "gblock1.pcx" );
	  Player2.Single[ 2 ] = xload_pcx( file, Pal );
	  break;
	case 4 :
	  strcat ( file, "hurt1.pcx" );
	  Player2.Single[ 3 ] = xload_pcx( file, Pal );
	  break;
	}
    }
  TRON( "loading..." );
  
  for ( num = 1; num < ( p2.walk.nbf + 1 ); ++num )
    {
      sprintf( file, "%swalk%d.pcx", passeur, num );
      Player2.Walk[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p2.spunch.nbf + 1 ); ++num )
    {
      sprintf( file, "%sspunch%d.pcx", passeur, num );
      Player2.Punch[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p2.wpunch.nbf + 1 ); ++num )
    {
      sprintf( file, "%swpunch%d.pcx", passeur, num );
      Player2.WPunch[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p2.apunch.nbf + 1 ); ++num )
    {
      sprintf( file, "%sapunch%d.pcx", passeur, num );
      Player2.APunch[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p2.gpunch.nbf + 1 ); ++num )
    {
      sprintf( file, "%sgpunch%d.pcx", passeur, num );
      Player2.GPunch[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p2.intro.nbf + 1 ); ++num )
    {
      sprintf( file, "%sintro%d.pcx", passeur, num );
      Player2.Kick[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p2.gkick.nbf + 1 ); ++num )
    {
      sprintf( file, "%sgkick%d.pcx", passeur, num );
      Player2.GKick[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p2.wkick.nbf + 1 ); ++num )
    {
      sprintf( file, "%swkick%d.pcx", passeur, num );
      Player2.WKick[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p2.hurt.nbf + 1 ); ++num )
    {
      sprintf( file, "%shurt%d.pcx", passeur, num );
      Player2.Hurt[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p2.ghurt.nbf + 1 ); ++num )
    {
      sprintf( file, "%sghurt%d.pcx", passeur, num );
      Player2.GHurt[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < 6; ++num )
    {
      sprintf( file, "%sjump%d.pcx", passeur, num );
      Player2.Jump[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < 6; ++num )
    {
      sprintf( file, "%sko%d.pcx", passeur, num );
      Player2.KO[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  for ( num = 1; num < ( p2.akick.nbf + 1 ); ++num )
    {
      sprintf( file, "%sakick%d.pcx", passeur, num );
      Player2.AKick[ num ] = xload_pcx( file, Pal );
    }
  TRON( "loading..." );
  if ( p2.fireb.flg )
    {
      TRON( "loading..." );
      for ( num = 1; num < ( p2.fireb.nbf + 1 ); ++num )
	{
	  sprintf( file, "%sfireb%d.pcx", passeur, num );
	  Player2.FireB[ num ] = xload_pcx( file, Pal );
	}
      TRON( "loading..." );
      for ( num = 1; num < ( p2.fball.nbf + 1 ); ++num )
	{
	  sprintf( file, "%sfball%d.pcx", passeur, num );
	  Player2.FBall[ num ] = xload_pcx( file, Pal );
	}
      TRON( "loading..." );
      sprintf( file, "%sfireb.wav", passeur );
      hadoken2 = xload_sample ( file );
    }
  TRON( "loading..." );
  if ( p2.rush.flg )
    {
      TRON( "loading..." );
      for ( num = 1; num < ( p2.rush.nbf + 1 ); ++num )
	{
	  sprintf( file, "%srush%d.pcx", passeur, num );
	  Player2.Rush[ num ] = xload_pcx( file, Pal );
	}
      TRON( "loading..." );
      sprintf( file, "%srush.wav", passeur );
      copter2 = xload_sample ( file );
    }
  TRON( "loading..." );
  if ( p2.smove.flg )
    {
      TRON( "loading..." );
      for ( num = 1; num < ( p2.smove.nbf + 1 ); ++num )
	{
	  sprintf( file, "%ssmove%d.pcx", passeur, num );
	  Player2.SMove[ num ] = xload_pcx( file, Pal );
	}
      TRON( "loading..." );
      sprintf( file, "%ssmove.wav", passeur );
      dragon2 = xload_sample ( file );
    }
  TRON( "loading..." );
  // SUPER SPECIALS
  if ( p2.firebx.flg )
    {
      TRON( "loading..." );
      for ( num = 1; num < ( p2.firebx.nbf + 1 ); ++num )
	{
	  sprintf( file, "%sfirebx%d.pcx", passeur, num );
	  Player2.FireBX[ num ] = xload_pcx( file, Pal );
	}
      TRON( "loading..." );
      for ( num = 1; num < ( p2.fballx.nbf + 1 ); ++num )
	{
	  sprintf( file, "%sfballx%d.pcx", passeur, num );
	  Player2.FBallX[ num ] = xload_pcx( file, Pal );
	}
      TRON( "loading..." );
      sprintf( file, "%sfirebx.wav", passeur );
      hadokenx2 = xload_sample ( file );
    }
  TRON( "loading..." );
  if ( p2.rushx.flg )
    {
      TRON( "loading..." );
      for ( num = 1; num < ( p2.rushx.nbf + 1 ); ++num )
	{
	  sprintf( file, "%srushx%d.pcx", passeur, num );
	  Player2.RushX[ num ] = xload_pcx( file, Pal );
	}
      TRON( "loading..." );
      sprintf( file, "%srushx.wav", passeur );
      copterx2 = xload_sample( file );
    }
  TRON( "loading..." );
  if ( p2.smovex.flg )
    {
      TRON( "loading..." );
      for ( num = 1; num < ( p2.smovex.nbf + 1 ); ++num )
	{
	  sprintf( file, "%ssmovex%d.pcx", passeur, num );
	  Player2.SMoveX[ num ] = xload_pcx( file, Pal );
	}
      TRON( "loading..." );
      sprintf( file, "%ssmovex.wav", passeur );
      dragonx2 = xload_sample ( file );
    }
  free(passeur);
  TRON( "\nxload_pcxs2() - OK." );
}

void load_kick1 ( char * name )
{
  // int i;
  TRON( "\nload_kick1()" );
  // sprintf( passeur, "sprites" DIR_BAR "%s" DIR_BAR, name );

  for ( num = 1; num < ( p1.skick.nbf + 1 ); ++num )
    {
      sprintf( file, "%sskick%d.pcx", passeur, num );
		
      Player1.Kick[ num ] = xload_pcx( file, Pal );
		
    }
  TRON( "\nload_kick1() - OK" );
}

void load_win1 ( char * name )
{
  // sprintf( passeur, "sprites" DIR_BAR "%s" DIR_BAR, name );
  for ( num = 1; num < ( p1.outwin.nbf + 1 ); ++num )
    {
      sprintf( file, "%soutwin%d.pcx", passeur, num );
      Player1.Kick[ num ] = xload_pcx( file , Pal );
    }
  free(passeur);
}

void load_kick2 ( char * name )
{
  char * passeur;
  passeur = (char*)calloc(255,sizeof(char));
  TRON( "\nload_kick2()" );
  // sprintf( passeur, "sprites" DIR_BAR "%s" DIR_BAR, name );
  //rectfill( zoomscreen, 0, 0, zoomscreen->w, zoomscreen->h, makecol( 255, 0, 255 ) );
  for ( num = 1; num < ( p2.skick.nbf + 1 ); ++num )
    {
      sprintf( file, "%sskick%d.pcx", passeur, num );
      Player2.Kick[ num ] = xload_pcx( file, Pal );
    }
  TRON( "\nload_kick2() - OK" );
  free(passeur);
}
/*********************************************************/
void load_win2 ( char * name )
{
  TRON( "\nload_win2()" );
  // sprintf( passeur, "sprites" DIR_BAR "%s" DIR_BAR,name );
  //rectfill( virtscreen, 0, 0, virtscreen->w, virtscreen->h, makecol( 255, 0, 255 ) );

  for ( num = 1; num < ( p2.outwin.nbf + 1 ); ++num )
    {
      sprintf( file, "%soutwin%d.pcx", passeur, num );
      Player2.Kick[ num ] = xload_pcx( file, Pal );
    }
  TRON( "\nload_win2() - OK." );
}
/* END of LOAD FUNCTIONS */

void destroy_bitmaps ( void )
{
  TRON( "\ndestroy_bitmaps()" );
  unload_datafile ( creditflic );
  TRON( "..." );
  unload_datafile ( fonts_dat );
  TRON( "..." );
  destroy_bitmap( Title );
  //destroy_bitmap(Selecteur);
  TRON( "..." );
  destroy_bitmap( Face1 );
  destroy_bitmap( Face2 );
  TRON( "..." );
  destroy_bitmap( virtscreen );
  TRON( "..." );
  destroy_bitmap( scanliner );
  TRON( "..." );
  destroy_bitmap( Bkgd );
  TRON( "..." );
  for ( num = 1; num < 7; ++num )
    destroy_bitmap( Player1.Jump[ num ] );
  TRON( "..." );
  for ( num = 1; num < 6; ++num )
    destroy_bitmap( Player1.KO[ num ] );
  TRON( "..." );
  for ( num = 1; num < ( p1.statik.nbf + 1 ); ++num )
    destroy_bitmap ( Player1.Static[ num ] );

  TRON( "..." );
  for ( num = 1; num < ( p1.walk.nbf + 1 ); ++num )
    destroy_bitmap( Player1.Walk[ num ] );
  TRON( "..." );
  for ( num = 1; num < ( p1.spunch.nbf + 1 ); ++num )
    destroy_bitmap( Player1.Punch[ num ] );
  TRON( "..." );
  for ( num = 1; num < ( p1.wpunch.nbf + 1 ); ++num )
    destroy_bitmap( Player1.WPunch[ num ] );

  TRON( "..." );
  for ( num = 1; num < ( p1.gpunch.nbf + 1 ); ++num )
    destroy_bitmap( Player1.GPunch[ num ] );
  TRON( "..." );
  for ( num = 1; num < ( p1.apunch.nbf + 1 ); ++num )
    destroy_bitmap( Player1.APunch[ num ] );
  TRON( "..." );
  for ( num = 1; num < ( p1.skick.nbf + 1 ); ++num )
    destroy_bitmap( Player1.Kick[ num ] );
  TRON( "..." );
  for ( num = 1; num < ( p1.wkick.nbf + 1 ); ++num )
    destroy_bitmap( Player1.WKick[ num ] );
  TRON( "..." );
  for ( num = 1; num < ( p1.gkick.nbf + 1 ); ++num )
    destroy_bitmap( Player1.GKick[ num ] );

  TRON( "..." );
  for ( num = 1; num < ( p1.hurt.nbf + 1 ); ++num )
    destroy_bitmap( Player1.Hurt[ num ] );

  TRON( "..." );
  for ( num = 1; num < ( p1.ghurt.nbf + 1 ); ++num )
    destroy_bitmap( Player1.GHurt[ num ] );
  TRON( "..." );
  for ( num = 1; num < ( p1.fireb.nbf + 1 ); ++num )
    destroy_bitmap( Player1.FireB[ num ] );
  TRON( "..." );
  for ( num = 1; num < ( p1.fball.nbf + 1 ); ++num )
    destroy_bitmap( Player1.FBall[ num ] );

  TRON( "..." );
  destroy_bitmap( Player1.Single[ 0 ] );
  TRON( "..." );
  destroy_bitmap( Player1.Single[ 1 ] );
  TRON( "..." );
  destroy_bitmap( Player1.Single[ 2 ] );
  TRON( "..." );
  destroy_bitmap( Player1.Single[ 3 ] );
  TRON( "..." );
  for ( num = 1; num < ( p1.akick.nbf + 1 ); ++num )
    destroy_bitmap( Player1.AKick[ num ] );

  // PLAYER 2 SPRITES
  TRON( "PLAYER 2 SPRITES" );
  for ( num = 1; num < ( p2.statik.nbf + 1 ); ++num )
    destroy_bitmap ( Player2.Static[ num ] );

  TRON( "..." );
  for ( num = 1; num < ( p2.walk.nbf + 1 ); ++num )
    destroy_bitmap( Player2.Walk[ num ] );

  for ( num = 1; num < ( p2.spunch.nbf + 1 ); ++num )
    destroy_bitmap( Player2.Punch[ num ] );
  for ( num = 1; num < ( p2.wpunch.nbf + 1 ); ++num )
    destroy_bitmap( Player2.WPunch[ num ] );
  for ( num = 1; num < ( p2.gpunch.nbf + 1 ); ++num )
    destroy_bitmap( Player2.GPunch[ num ] );
  for ( num = 1; num < ( p2.apunch.nbf + 1 ); ++num )
    destroy_bitmap( Player2.APunch[ num ] );
  for ( num = 1; num < 6; ++num )
    destroy_bitmap( Player2.Jump[ num ] );

  for ( num = 1; num < 6; ++num )
    destroy_bitmap( Player2.KO[ num ] );
  for ( num = 1; num < ( p2.skick.nbf + 1 ); ++num )
    destroy_bitmap( Player2.Kick[ num ] );
  for ( num = 1; num < ( p2.wkick.nbf + 1 ); ++num )
    destroy_bitmap( Player2.WKick[ num ] );

  for ( num = 1; num < ( p2.gkick.nbf + 1 ); ++num )
    destroy_bitmap( Player2.GKick[ num ] );
  for ( num = 1; num < ( p2.fireb.nbf + 1 ); ++num )
    destroy_bitmap( Player2.FireB[ num ] );
  for ( num = 1; num < ( p2.fball.nbf + 1 ); ++num )
    destroy_bitmap( Player2.FBall[ num ] );

  destroy_bitmap( Player2.Single[ 0 ] );
  destroy_bitmap( Player2.Single[ 1 ] );
  destroy_bitmap( Player2.Single[ 2 ] );
  destroy_bitmap( Player2.Single[ 3 ] );
  for ( num = 1; num < ( p2.hurt.nbf + 1 ); ++num )
    destroy_bitmap( Player2.Hurt[ num ] );
  for ( num = 1; num < ( p2.ghurt.nbf + 1 ); ++num )
    destroy_bitmap( Player2.GHurt[ num ] );
  for ( num = 1; num < ( p2.akick.nbf + 1 ); ++num )
    destroy_bitmap( Player2.AKick[ num ] );
  TRON( "OK. destroy_bitmaps()" );

}
