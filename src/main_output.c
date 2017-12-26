#include <stdio.h>
#include <stdlib.h>


#include "allegro.h"

#include "macros.h"
#include "global.h"
#include "global_add.h"
#include "logger.h"

#include "refresh.h"
#include "main_output.h"
#include "story_output.h"
#include "choice_output.h"
#include "option_output.h"
#include "keyconfig_output.h"
#include "select_output.h"
#include "vs_output.h"
#include "battle_output.h"

/** \file main_output.c
 * \brief Functions that deals with global output, by switching to specific outputs depending the game_state
 */

int screenshot(BITMAP * a_bitmap);

int debug_text(Game_variables variables,Player_variables * player_array,int time,BITMAP * a_bitmap){
  int color;
  if ((variables->Game_state!=10)&&(variables->Game_state!=100)){
  color = makecol(255,255,255);
  textprintf_ex(a_bitmap,font, 0,0,color,-1,"Engine State = %i, fps = %i", variables->Game_state, variables->fps);
  textprintf_ex(a_bitmap,font, 0,7,color,-1,"Total time = %d",time);
  }else{
    color = makecol(255,255,255);
    textprintf_ex(a_bitmap,font, 5,206,color,-1,"Frames : %i (%i fps)", time, variables->fps);
    textprintf_ex(a_bitmap,font, 5,213,color,-1,"Name %s (%i)",player_array[0].name,0);
    textprintf_ex(a_bitmap,font, 5,220,color,-1,"Action id : %i Spr : %i.%i Elemno : %i / %i Time %i / %i",player_array[0].cns.action,player_array[0].cns.sprg,player_array[0].cns.spri,player_array[0].cns.elementno,player_array[0].cns.maxelement,player_array[0].cns.elementtime,player_array[0].cns.maxelementtime);
  }
  return 0;
}

int main_output(Game_variables variables,Player_variables * player_array,int time){
  int error = 0;
  char * message;
  message = (char*)malloc(255*sizeof(char));
  if (variables->Game_config.Debug_on) {
    sprintf(message,"Beginning Main_output in state %d",variables->Game_state);
    TRON(message);
  }

  if (variables->not_show){
    variables->not_show=0;
    if (variables->Game_config.Debug_on){
      sprintf(message,"In state %d not show",variables->Game_state);
      TRON(message);
    }
    return 0;
  }
  
  /*
  if (virtscreen==NULL)
    virtscreen = create_bitmap(variables->Game_config.Buffer_w,variables->Game_config.Buffer_h);
  */
  clear_bitmap(virtscreen);
  
  switch (variables->Game_state){
  case 1 :
    if (variables->Game_config.Debug_on)
      TRON("Entering story_output");
    error += story_output(variables->System.Intro,time);
    if (variables->Game_config.Debug_on)
      TRON("Exiting story_output");
    break;
  case 2 :
    if (variables->Game_config.Debug_on)
      TRON("Entering story_output");
    error += story_output(variables->System.Open,time);
    if (variables->Game_config.Debug_on)
      TRON("Exiting story_output");
    break;
  case 3 :
    if (variables->Game_config.Debug_on)
      TRON("Entering choice_output");
    error += choice_output(variables,time);
    if (variables->Game_config.Debug_on)
      TRON("Exiting choice_output");
    break;
  case 4 :
    if (variables->Game_config.Debug_on)
      TRON("Entering option_output");
    error += option_output(variables,player_array,time);
    if (variables->Game_config.Debug_on)
       TRON("Exiting option_output");
    break;
  case 5 :
    if (variables->Game_config.Debug_on)
      TRON("Entering keyconfig_output");
    error += keyconfig_output(variables,player_array,time);
    if (variables->Game_config.Debug_on)
       TRON("Exiting keyconfig_output");
    break;
  case 6:
    if (SENSEI_DEBUG_ON)
      TRON("Entering select_output");
    error += select_output(variables,player_array,time);
    if (SENSEI_DEBUG_ON)
      TRON("Exiting select_output");
    break;
  case 8 :
    if (SENSEI_DEBUG_ON)
      TRON("Entering vs_output");
    error += vs_output(variables,player_array,time);
    if (SENSEI_DEBUG_ON)
      TRON("Exiting vs_output");
    break;
  case 9:
    
    break;
  case 10:
    if (SENSEI_DEBUG_ON)
      TRON("Entering battle output");
    error += battle_output(variables,player_array,time);
    if (SENSEI_DEBUG_ON)
      TRON("Exiting battle output");
    break;
  case 101:
    if (variables->Game_config.Debug_on)
      TRON("Entering story_output");
    error += story_output(variables->System.Intro,time);
    if (variables->Game_config.Debug_on)
      TRON("Exiting story_output");
    break;
  case 102:
    if (variables->Game_config.Debug_on)
      TRON("Entering story_output");
    error += story_output(variables->System.Open,time);
    if (variables->Game_config.Debug_on)
      TRON("Exiting story_output");
    break;
  case 103 :
    if (variables->Game_config.Debug_on)
      TRON("Entering choice_output");
    error += choice_output(variables,time);
    if (variables->Game_config.Debug_on)
      TRON("Exiting choice_output");
    break;
  case 104 :
    if (variables->Game_config.Debug_on)
      TRON("Entering option_output");
    error += option_output(variables,player_array,time);
    if (variables->Game_config.Debug_on)
      TRON("Exiting option_output");
    break;
  case 105 :
    if (variables->Game_config.Debug_on)
      TRON("Entering keyconfig_output");
    error += keyconfig_output(variables,player_array,time);
    if (variables->Game_config.Debug_on)
      TRON("Exiting keyconfig_output");
    break;
  case 106:
    if (SENSEI_DEBUG_ON)
      TRON("Entering select_output");
    error += select_output(variables,player_array,time);
    if (SENSEI_DEBUG_ON)
      TRON("Exiting select_output");
    break;
  case 108 :
    if (SENSEI_DEBUG_ON)
      TRON("Entering vs_output");
    error += vs_output(variables,player_array,time);
    if (SENSEI_DEBUG_ON)
      TRON("Exiting vs_output");
    break;
  default:
    if (variables->Game_config.Debug_on){
      message = (char*)calloc(255,sizeof(char));
      sprintf(message,"In main_output state %i not implemented",variables->Game_state);
      TRON (message);
    }
    break;
  }
  
  if (error>0) {
    ERROR("In main_output after switch error\n");
    return 1;
  }
  if (variables->Game_config.Debug_on) 
    error=debug_text(variables,player_array,time,virtscreen);
  
  if (variables->f_keys.F12){
    screenshot(virtscreen);
    variables->f_keys.F12 = 0;
  }

  blit_KOF91();
  free(message);
  //destroy_bitmap(virtscreen);
  return 0;
} //main_output

int screenshot(BITMAP * a_bitmap){
  int number = 0;
  int ok = 0;
  char * message;
  message = (char*)calloc(255,sizeof(char));
  
  while (!ok){
    sprintf(message,"kof91_%i.pcx",number);
    if (exists(message))
      number++;
    else
      ok=1;
  }
  
  save_pcx(message,a_bitmap,NULL);
  rest(5);
  free(message);
  return 0;
}
