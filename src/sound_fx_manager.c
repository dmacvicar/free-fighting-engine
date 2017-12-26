#include "allegro.h"
#include "sound_fx_manager.h"
#include "global.h"
#include "loads.h"
#include "logger.h"
#include "macros.h"
#include "global_add.h"
#include "string.h"

/** \file sound_fx_manager.c
 * \brief Function to load wav files used by old KOF 91 engine
 */

int loadsounds( Game_variables variables ){
  char * path;
 
  if (SENSEI_DEBUG_ON){
    TRON( "loadsounds()" );
  }
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"rd1.wav");
  if (exists(path))
    rd1 = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"rd1.wav");
    rd1 = xload_sample (path);
  }
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"rd2.wav");
  if (exists(path))
    rd1 = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"rd2.wav");
    rd2 = xload_sample (path);
  }

  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"rd3.wav");
  if (exists(path))
    rd3 = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"rd3.wav");
    rd3 = xload_sample (path);
  }

  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"fight.wav");
  if (exists(path))
    fight = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"fight.wav");
    fight = xload_sample (path);
  }
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"wp_alwa.wav");
  if (exists(path))
    wp_alwa = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"wp_alwa.wav");
    wp_alwa = xload_sample (path);
  }
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"wk_alwa.wav");
  if (exists(path))
    wk_alwa = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"wk_alwa.wav");
    wk_alwa = xload_sample (path);
  }
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"sp_alwa.wav");
  if (exists(path))
    sp_alwa = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"sp_alwa.wav");
    sp_alwa = xload_sample (path);
  }
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"sk_alwa.wav");
  if (exists(path))
    sk_alwa = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"sk_alwa.wav");
    sk_alwa = xload_sample (path);
  }
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"hit1.wav");
  if (exists(path))
    hit1 = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"hit1.wav");
    hit1 = xload_sample (path);
  }
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"hit2.wav");
  if (exists(path))
    hit2 = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"hit2.wav");
    hit2 = xload_sample (path);
  }
 
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"block.wav");
  if (exists(path))
    block_snd = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"block.wav");
    block_snd = xload_sample (path);
  }
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"ko.wav");
  if (exists(path))
    ko_snd = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"ko.wav");
    ko_snd = xload_sample (path);
  }  
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"timeup.wav");
  if (exists(path))
    to_snd = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"timeup.wav");
    to_snd = xload_sample (path);
  }  
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"argh1.wav");
  if (exists(path))
    argh_snd = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"argh1.wav");
    argh_snd = xload_sample (path);
  }  
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"argh2.wav");
  if (exists(path))
    female_snd = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"argh2.wav");
    female_snd = xload_sample (path);
  }  
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"perfect.wav");
  if (exists(path))
    prfct_snd = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"perfect.wav");
    prfct_snd = xload_sample (path);
  }  
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"done.wav");
  if (exists(path))
    done = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"done.wav");
    done = xload_sample (path);
  }  
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"buzz.wav");
  if (exists(path))
    buzz = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"buzz.wav");
    buzz = xload_sample (path);
  }  
  
  path = (char*)calloc(255,sizeof(char));
  path = strcpy(path,variables->Path);
  put_backslash(path);
  path = strcat(path,"bing.wav");
  if (exists(path))
    bing = xload_sample (path);
  else{
    path = (char*)calloc(255,sizeof(char));
    path = strcpy(path,"wav");
    put_backslash(path);
    path = strcat(path,"bing.wav");
    bing = xload_sample (path);
  }  
  
  if (SENSEI_DEBUG_ON){
    TRON( "loadsounds() - OK." );
  }
  return 0;
} // loadsounds()

void freesounds( void )
{
  TRON( "freesounds()" );
  destroy_sample ( rd1 );
  destroy_sample ( rd2 );
  destroy_sample ( rd3 );
  destroy_sample ( fight );
  //        destroy_sample ( hit_alwa );
  destroy_sample ( wp_alwa );
  destroy_sample ( wk_alwa );
  destroy_sample ( sp_alwa );
  destroy_sample ( sk_alwa );
  destroy_sample ( ko_snd );
  destroy_sample ( argh_snd );
  destroy_sample ( female_snd );
  destroy_sample ( done );
  destroy_sample ( bing );
  destroy_sample ( buzz );
  TRON( "freesounds() - OK." );
} // freesounds

void Buzz ( void )
{
  stop_sample( buzz );
  play_sample( buzz, snd_vol, pan, pitch, 0 );
}

void Bing ( void )
{
  play_sample( bing, snd_vol, pan, pitch, 0 );
  //rest(10);
}

void Done ( void )
{
  play_sample( done, snd_vol, pan, pitch, 0 );
  rest(50);
}

void Block ( void )
{
  play_sample( block_snd, snd_vol, pan, pitch, 0 );
}

void Paf ( char gana )
{
  switch ( gana )
    {
    case 1 :
      play_sample( wp_alwa , snd_vol, pan, pitch, 0 );
      break;
    case 2 :
      play_sample( sp_alwa , snd_vol, pan, pitch, 0 );
      break;
    case 3 :
      play_sample( wk_alwa , snd_vol, pan, pitch, 0 );
      break;
    case 4 :
      play_sample( sk_alwa , snd_vol, pan, pitch, 0 );
      break;
    }
}

void Hurt ( char gana )
{
  switch ( gana )
    {
    case 1 :
      play_sample( hit2 , snd_vol, pan, pitch, 0 );
      break;
    case 2 :
      play_sample( hit1 , snd_vol, pan, pitch, 0 );
      break;
    default:
      play_sample( hit1 , snd_vol, pan, pitch, 0 );
      break;
    }
}

void Round ( char which )
{
  switch ( which )
    {
    case 1 :
      play_sample( rd1 , snd_vol, pan, pitch, 0 );
      break;
    case 2 :
      play_sample( rd2 , snd_vol, pan, pitch, 0 );
      break;
    case 3 :
      play_sample( rd3 , snd_vol, pan, pitch, 0 );
      break;
    default :
      play_sample( rd1 , snd_vol, pan, pitch, 0 );
      break;
    }
}

void Fight( void )
{
  play_sample( fight , snd_vol, pan, pitch, 0 );
}
