#include "global.h"
#include "macros.h"
#include "config.h"
#include "refresh.h"
#include "2xsai.h"
#include "aastr.h"


/** \file refresh.c
 * \brief functions (src) to blit the bitmap buffer to the screen
 */
 
/** \brief function to blit virtscreen to the screen
 *
 * use diffents libraries (2xsai, libaastr, manual scanlines , unstreteched blit to do it
 */
void blit_KOF91( void )
{
  BITMAP * buff_screen;
  static int y;

  if (!stretch){
    acquire_screen();
    blit( virtscreen, screen, 0,0, ((SCREEN_W-320)/2) , ((SCREEN_H-240)/2), ((SCREEN_W-320)/2)+320, ((SCREEN_H-240)/2)+240  );
    release_screen();
    return;
  }


  switch (gfmode){
  case 0: //No double res
    acquire_screen();
    stretch_blit( virtscreen, screen, 0, 0, 320, 240, 0,0, SCREEN_W, SCREEN_H);
    release_screen();
    break;
  case 1: //Super 2xsai
    buff_screen = create_bitmap(640,480);
    clear_bitmap(buff_screen);
    Super2xSaI( virtscreen, buff_screen, 0, 0, 0, 0, 320, 240);
    acquire_screen();
    stretch_blit( buff_screen, screen, 0,0, 640,480, 0,0, SCREEN_W, SCREEN_H);
    release_screen();
    destroy_bitmap(buff_screen);
    break;
  case 2: //aa stretch
    //buff_screen = create_bitmap(640,480);
    //clear_bitmap(buff_screen);
    //aa_stretch_blit (virtscreen, buff_screen, 0, 0, 320, 240, 0, 0, 640, 480); 
    acquire_screen();
    //aa_stretch_blit (virtscreen, screen, 0, 0, 320, 240, 0, 0, SCREEN_W, SCREEN_H);
    stretch_blit (virtscreen, screen, 0, 0, 320, 240, 0, 0, SCREEN_W, SCREEN_H); 
    release_screen();
    break;
  case 3: //Scanlines
    stretch_blit (virtscreen, scanliner, 0,0, 320,240, 0,0, SCREEN_W, SCREEN_H);
    for (y=0; y<screen_height; y+=2)
      hline (scanliner, 0, y, screen_width, 0);
    acquire_screen();
    stretch_blit ( scanliner , screen , 0, 0, screen_width, screen_height, 0, 0, SCREEN_W, SCREEN_H);
    release_screen();
    break;
  default: 
    acquire_screen();
    stretch_blit( virtscreen, screen, 0, 0, 320, 240, 0,0, SCREEN_W, SCREEN_H);
    release_screen();
    break;
  }
} /*blit_KOF91( void )*/

/*************************************************/
   void blit_Bkgd( void )
   {
      if ( animated )
      {
         if ( bkgd_counter > bkgd_delay )
         {
            reset_fli_variables();
            next_fli_frame( 1 );
            bkgd_counter = 0;
         }
         blit ( fli_bitmap, zoomscreen, 0, 0, 0, 0,
              ( bkgdlim + 320 ), ( 200 + zoomsup ) );
      }
      else
      {
         blit ( Bkgd, zoomscreen, 0, 0, 0, 0,
              ( bkgdlim + 320 ), ( 200 + zoomsup ) );
      }
   } /* blit_Bkgd( void ) */
