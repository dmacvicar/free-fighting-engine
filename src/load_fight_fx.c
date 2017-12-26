#include "load_fight_fx.h"
#include "loads.h"
#include "macros.h"
#include "config.h"
#include "logger.h"
#include "global.h"
#include "global_add.h"
#include "string.h"
#include "sensei_config.h"
#include <stdio.h>

/** \file load_fight_fx.c
 * \brief Old function to load fight Effects (lock, impact, etc..)
 */
int load_fight_fx(Game_variables variables){
  char * message;
  char * result;
  int error = 0;
  message = (char*)calloc(255,sizeof(char));
  
  result = strcpy((char*)calloc(255,sizeof(char)),"sprites");
  put_backslash(result);
  result = strcat(result,"lock.pcx");
  
  if ( ( Lock = xload_pcx ( result , 0 ) ) == NULL ){
    result = check_path("lock.pcx",variables->Path,"Lock.pcx",&error);
    if (error!=0)
      Lock = xload_pcx(result,0);
  }
  
  for ( num = 1; num < ( wimpact_nbf + 1 ); ++num ){
    result = strcpy((char*)calloc(255,sizeof(char)),"sprites");
    put_backslash(result);
    sprintf(message,"wimpact%d.pcx", num);
    result = strcat(result,message);
    // sprintf( file, "sprites" DIR_BAR "wimpact%d.pcx", num );
    if ( ( WImpact[ num ] = xload_pcx ( result , 0 ) ) == NULL ){
      result = check_path(message,variables->Path,message,&error);
      if (error!=0)
	WImpact[ num ] = xload_pcx (result,0);
    }
  }
  
  for ( num = 1; num < ( simpact_nbf + 1 ); ++num ){
    result = strcpy((char*)calloc(255,sizeof(char)),"sprites");
    put_backslash(result);
    sprintf(message,"simpact%d.pcx", num);
    result = strcat(result,message);
    // sprintf( file, "sprites" DIR_BAR "simpact%d.pcx", num );
    if ( ( SImpact[ num ] = xload_pcx ( result , 0 ) ) == NULL){
      result = check_path(message,variables->Path,message,&error);
      if (error!=0)
	SImpact[ num ] = xload_pcx (result,0);
    }
  }
  
  for ( num = 1; num < ( bimpact_nbf + 1 ); ++num ){
    // sprintf( file, "sprites" DIR_BAR "bimpact%d.pcx", num );
    result = strcpy((char*)calloc(255,sizeof(char)),"sprites");
    put_backslash(result);
    sprintf(message,"bimpact%d.pcx", num);
    result = strcat(result,message);
    // sprintf( file, "sprites" DIR_BAR "simpact%d.pcx", num );
    if ( ( BlockImpact[ num ] = xload_pcx ( result , 0 )) == NULL){
      result = check_path(message,variables->Path,message,&error);
      if (error!=0)
	BlockImpact[ num ] = xload_pcx (result,0);
    }
  }
  
  free(result);
  free(message);
  return 0;
}
