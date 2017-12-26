#include "battle_process.h"
#include "main_process.h"
#include "background_process.h"
#include "player_process.h"
#include "sensei_config.h"

#include "global.h"

/** \file battle_process.c
 * \brief Functions to process the whole fighting stuff
 */
int battle_process(Game_variables variables, Player_variables * player_array,int time){
  char * message;
  message = (char*)calloc(255,sizeof(char));
  
  if (variables->f_keys.Esc==1){
    variables->f_keys.Esc=0;
    next_state(variables);
    rest(0);
    variables->not_show =1;
    stop_music(&variables->Fight_bg.bg_music);
    variables->System.Select_struct.state = 0;
  }
  
  if (variables->battle.fixed_players==0){
    fix_players(variables,player_array);
  }
  
  player_process(variables,player_array,time);
  background_process(&variables->Fight_bg);
  play_music(&variables->Fight_bg.bg_music);

  free(message);
  return 0;
} // battle_process
