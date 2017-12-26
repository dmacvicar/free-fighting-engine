/*
  moves.c
*/

#include "global.h"
#include "moves.h"
#include "macros.h"

/** \file moves.c
 * \brief Old functions to show player sprites depending of his moves
 */

void GStatic ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.statik.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.statik.nbf - 1 ;
  draw_player( Player1.Static[ gueu + 1 ] , x , y ) ;

}

void GSingle ( int gueu , int x , int y )
{
  draw_player( Player1.Single[ gueu ] , x , y ) ;
}

void GKO ( int gueu , int x , int y )
{
  x = x - 20 ;
  switch ( gueu )
    {
    case 1 :
      draw_player( Player1.KO[ 1 ] , x , y ) ;
      break ;
    case 2 :
      draw_player( Player1.KO[ 2 ] , x , y ) ;
      break ;
    case 3 :
      draw_player( Player1.KO[ 3 ] , x , y ) ;
      break ;
    case 4 :
      draw_player( Player1.KO[ 4 ] , x , y ) ;
      break ;
    case 5 :
    case 6 :
    default:
      draw_player( Player1.Single[ 1 ] , ( x + 15 ) , y ) ;
      break ;
    }
}

void GDead ( int gueu , int x , int y )
{
  x = x - 10 ;
  switch ( gueu )
    {
    case 0 :
      draw_player( Player1.KO[ 1 ] , x , y ) ;
      break ;
    case 1 :
      draw_player( Player1.KO[ 1 ] , x , y ) ;
      break ;

    case 2 :
      draw_player( Player1.KO[ 2 ] , x , y ) ;
      break ;

    case 3 :
      draw_player( Player1.KO[ 3 ] , x , y ) ;
      break ;

    case 4 :
      draw_player( Player1.KO[ 4 ] , x , y ) ;
      break ;

    case 5 :
      draw_player( Player1.KO[ 3 ] , x , y ) ;
      break ;

    case 6 :
      draw_player( Player1.KO[ 4 ] , x , y ) ;
      break ;
    case 7 :
    default:
      draw_player( Player1.KO[ 5 ] , x , y ) ;
      break ;
    }
}

void GJump ( int gueu , int x , int y )
{
  draw_player( Player1.Jump[ gueu ] , x , y ) ;
}

void GHurt ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.hurt.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.hurt.nbf - 1 ;
  draw_player( Player1.Hurt[ gueu + 1 ] , x , y ) ;

}

void GGHurt ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.ghurt.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.ghurt.nbf - 1 ;
  draw_player( Player1.GHurt[ gueu + 1 ] , x , y ) ;

}


void GWalk ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.walk.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.walk.nbf - 1 ;
  draw_player( Player1.Walk[ gueu + 1 ] , x , y ) ;

}

void GKick ( int gueu , int x , int y , int z )
{

  switch ( z )
    {
    case 1 :
      if ( ( ( gueu + 1 ) > p1.skick.nbf ) || ( ( gueu + 1 ) < 1 ) )
	gueu = p1.skick.nbf - 1 ;
      break ;

    case 2 :
      if ( ( ( gueu + 1 ) > p1.intro.nbf ) || ( ( gueu + 1 ) < 1 ) )
	gueu = p1.intro.nbf - 1 ;
      break ;

    case 3 :
      if ( ( ( gueu + 1 ) > p1.outwin.nbf ) || ( ( gueu + 1 ) < 1 ) )
	gueu = p1.outwin.nbf - 1 ;
      break ;
    }
  draw_player( Player1.Kick[ gueu + 1 ] , x , y ) ;

}

void GGKick ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.gkick.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.gkick.nbf - 1 ;
  draw_player( Player1.GKick[ gueu + 1 ] , x , y ) ;

}

void GWKick ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.wkick.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.wkick.nbf - 1 ;
  draw_player( Player1.WKick[ gueu + 1 ] , x , y ) ;

}

void GPunch ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.spunch.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.spunch.nbf - 1 ;
  draw_player( Player1.Punch[ gueu + 1 ] , x , y ) ;

}

void GWPunch ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.wpunch.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.wpunch.nbf - 1 ;
  draw_player( Player1.WPunch[ gueu + 1 ] , x , y ) ;

}

void GAKick ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.akick.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.akick.nbf - 1 ;
  draw_player( Player1.AKick[ gueu + 1 ] , x , y ) ;

}

void GAPunch ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.apunch.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.apunch.nbf - 1 ;
  draw_player( Player1.APunch[ gueu + 1 ] , x , y ) ;

}

void GGPunch ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.gpunch.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.gpunch.nbf - 1 ;
  draw_player( Player1.GPunch[ gueu + 1 ] , x , y ) ;

}

void GFireB ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.fireb.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.fireb.nbf - 1 ;
  draw_player( Player1.FireB[ gueu + 1 ] , x , y ) ;

}

void GFireB2 ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p2.fireb.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.fireb.nbf - 1 ;
  draw_player( Player2.FireB[ gueu + 1 ] , x , y ) ;

}

void GFBall ( int gueu , int x , int y )
{

  if ( ( ( gueu + 1 ) > p1.fball.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.fball.nbf - 1 ;

  B_Temp = create_bitmap( Player1.FBall[ gueu + 1 ] ->w,
			  Player1.FBall[ gueu + 1 ] ->h );

  rectfill( B_Temp, 0, 0, Player1.FBall[ gueu + 1 ] ->w,
	    Player1.FBall[ gueu + 1 ] ->h, makecol( 255, 0, 255 ) );

  draw_sprite( B_Temp, Player1.FBall[ gueu + 1 ], 0, 0 );

  set_trans_blender( 255, 255, 255, 170 );

  draw_trans_sprite( zoomscreen, B_Temp, x , y ) ;
  destroy_bitmap( B_Temp );

}

void GFBall2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.fball.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.fball.nbf - 1 ;

  B_Temp = create_bitmap( Player2.FBall[ gueu + 1 ] ->w,
			  Player2.FBall[ gueu + 1 ] ->h );

  rectfill( B_Temp, 0, 0, Player2.FBall[ gueu + 1 ] ->w,
	    Player2.FBall[ gueu + 1 ] ->h, makecol( 255, 0, 255 ) );

  draw_sprite( B_Temp, Player2.FBall[ gueu + 1 ], 0, 0 );
  set_trans_blender( 255, 255, 255, 170 );
  draw_trans_sprite( zoomscreen, B_Temp , x , y ) ;
  destroy_bitmap( B_Temp );

}

void GRush ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p1.rush.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.rush.nbf - 1 ;

  draw_player( Player1.Rush[ gueu + 1 ] , x , y ) ;

}

void GRush2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.rush.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.rush.nbf - 1 ;

  draw_player( Player2.Rush[ gueu + 1 ] , x , y ) ;

}

void GSMove ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p1.smove.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.smove.nbf - 1 ;

  draw_player( Player1.SMove[ gueu + 1 ] , x , y ) ;

}

void GSMove2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.smove.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.smove.nbf - 1 ;

  draw_player( Player2.SMove[ gueu + 1 ] , x , y ) ;

}

// SPECIALS

void GFireBX ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p1.firebx.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.firebx.nbf - 1 ;

  draw_player( Player1.FireBX[ gueu + 1 ] , x , y ) ;

}


void GFireBX2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.firebx.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.firebx.nbf - 1 ;

  draw_player( Player2.FireBX[ gueu + 1 ] , x , y ) ;

}

void GFBallX ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p1.fballx.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.fballx.nbf - 1 ;

  draw_player( Player1.FBallX[ gueu + 1 ] , x , y ) ;

}

void GFBallX2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.fballx.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.fballx.nbf - 1 ;

  draw_player( Player2.FBallX[ gueu + 1 ] , x , y ) ;

}

void GRushX ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p1.rushx.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.rushx.nbf - 1 ;

  draw_player( Player1.RushX[ gueu + 1 ] , x , y ) ;

}

void GRushX2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.rushx.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.rushx.nbf - 1 ;

  draw_player( Player2.RushX[ gueu + 1 ] , x , y ) ;

}

void GSMoveX ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p1.smovex.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p1.smovex.nbf - 1 ;

  draw_player( Player1.SMoveX[ gueu + 1 ] , x , y ) ;

}

void GSMoveX2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.smovex.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.smovex.nbf - 1 ;

  draw_player( Player2.SMoveX[ gueu + 1 ] , x , y ) ;

}

// END OF SPECIALS

void GStatic2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.statik.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.statik.nbf - 1 ;

  draw_player( Player2.Static[ gueu + 1 ] , x , y ) ;
}


void GWalk2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.walk.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.walk.nbf - 1 ;

  draw_player( Player2.Walk[ gueu + 1 ] , x , y ) ;

}

void GHurt2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.hurt.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.hurt.nbf - 1 ;

  draw_player( Player2.Hurt[ gueu + 1 ] , x , y ) ;

}

void GGHurt2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.ghurt.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.ghurt.nbf - 1 ;

  draw_player( Player2.GHurt[ gueu + 1 ] , x , y ) ;

}

void GKO2 ( int gueu , int x , int y , int z )

{

  x = x + 30 ;

  switch ( gueu )

    {
    case 1 :
      draw_player( Player2.KO[ 1 ] , x , y ) ;
      break ;
    case 2 :
      draw_player( Player2.KO[ 2 ] , x , y ) ;
      break ;
    case 3 :
      draw_player( Player2.KO[ 3 ] , x , y ) ;
      break ;
    case 4 :
      draw_player( Player2.KO[ 4 ] , x , y ) ;
      break ;
    case 5 :
    case 6 :
    default:
      draw_player( Player2.Single[ 1 ] , ( x + z - 25 ) , y ) ;
      break ;

    }
}

void GDead2 ( int gueu , int x , int y )

{

  x = x + 10 ;

  switch ( gueu )

    {
    case 0:
      draw_player( Player2.KO[ 1 ] , x , y ) ;
      break ;
    case 1:
      draw_player( Player2.KO[ 1 ] , x , y ) ;
      break ;
    case 2:
      draw_player( Player2.KO[ 2 ] , x , y ) ;
      break ;
    case 3:
      draw_player( Player2.KO[ 3 ] , x , y ) ;
      break ;
    case 4:
      draw_player( Player2.KO[ 4 ] , x , y ) ;
      break ;
    case 5:
      draw_player( Player2.KO[ 3 ] , x , y ) ;
      break ;
    case 6:
      draw_player( Player2.KO[ 4 ] , x , y ) ;
      break ;
    case 7 :
    default:
      draw_player( Player2.KO[ 5 ] , x , y ) ;
      break ;
    }
}

void GKick2 ( int gueu , int x , int y , int z )

{

  switch ( z )

    {

    case 1 :
      if ( ( ( gueu + 1 ) > p2.skick.nbf ) || ( ( gueu + 1 ) < 1 ) )
	gueu = p2.skick.nbf - 1 ;
      break ;

    case 2 :
      if ( ( ( gueu + 1 ) > p2.intro.nbf ) || ( ( gueu + 1 ) < 1 ) )
	gueu = p2.intro.nbf - 1 ;
      break ;

    case 3 :
      if ( ( ( gueu + 1 ) > p2.outwin.nbf ) || ( ( gueu + 1 ) < 1 ) )
	gueu = p2.outwin.nbf - 1 ;
      break ;
    }

  draw_player( Player2.Kick[ gueu + 1 ] , x , y ) ;

}

void GGKick2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.gkick.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.gkick.nbf - 1 ;

  draw_player( Player2.GKick[ gueu + 1 ] , x , y ) ;

}

void GWKick2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.wkick.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.wkick.nbf - 1 ;

  draw_player( Player2.WKick[ gueu + 1 ] , x , y ) ;

}

void GPunch2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.spunch.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.spunch.nbf - 1 ;

  draw_player( Player2.Punch[ gueu + 1 ] , x , y ) ;

}

void GWPunch2 ( int gueu , int x , int y )

{

  if ( ( ( gueu + 1 ) > p2.wpunch.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.wpunch.nbf - 1 ;

  draw_player( Player2.WPunch[ gueu + 1 ] , x , y ) ;

}

void GJump2 ( int gueu , int x , int y )

{
  draw_player( Player2.Jump[ gueu ] , x , y ) ;
}

void GSingle2 ( int gueu , int x , int y )

{
  draw_player( Player2.Single[ gueu ] , x , y ) ;
}


void GAKick2 ( int gueu , int x , int y )

{
  if ( ( ( gueu + 1 ) > p2.akick.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.akick.nbf - 1 ;

  draw_player( Player2.AKick[ gueu + 1 ] , x , y ) ;
}

void GAPunch2 ( int gueu , int x , int y )
{
  if ( ( ( gueu + 1 ) > p2.apunch.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.apunch.nbf - 1 ;
  draw_player( Player2.APunch[ gueu + 1 ] , x , y ) ;
}

void GGPunch2 ( int gueu , int x , int y )
{
  if ( ( ( gueu + 1 ) > p2.gpunch.nbf ) || ( ( gueu + 1 ) < 1 ) )
    gueu = p2.gpunch.nbf - 1 ;

  draw_player( Player2.GPunch[ gueu + 1 ] , x , y ) ;
}

/******************************************************************/
void draw_player( BITMAP *poser, int x, int y ){
  /*
  if ( inverted ){
    draw_sprite_h_flip( zoomscreen, poser , zoomscreen->w - x + 1 - poser->w , y ) ;
    }
  else
  */
    draw_sprite( zoomscreen, poser, x, y ) ;
}

