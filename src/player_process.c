#include "global.h"
#include "player_process.h"
#include "macros.h"
#include "logger.h"
#include <stdio.h>
#include "sensei_config.h"

int player_process(Game_variables variables, Player_variables * player_array,int time){
  char * message;
  int act_index,j;
  int element;

  message = (char*)calloc(255,sizeof(char));
  if (SENSEI_DEBUG_ON)
    TRON("Begin player_process");
  for (i=0;i<4;i++){
    act_index = -1;
    for (j=0;j<player_array[i].action_number;j++){
      if (player_array[i].action_array[j].number==0)
	act_index = j; 
    }
    
    if (SENSEI_DEBUG_ON){
      sprintf(message,"act index = %i != -1 ?? and action_number = %i",act_index,player_array[i].action_number);
      TRON(message);
    }
    
    if (act_index!=-1){
      process_action(&player_array[i].action_array[act_index]);
      element = player_array[i].action_array[act_index].current_element;
      player_array[i].cns.action = 0;
      player_array[i].cns.sprg = player_array[i].action_array[act_index].animation_array[element].groupeno;
      player_array[i].cns.spri = player_array[i].action_array[act_index].animation_array[element].spriteno;
      player_array[i].cns.elementtime = player_array[i].action_array[act_index].animation_array[element].current_time;
      player_array[i].cns.maxelementtime = player_array[i].action_array[act_index].animation_array[element].time;
      player_array[i].cns.elementno = player_array[i].action_array[act_index].current_element;
      player_array[i].cns.maxelement =  player_array[i].action_array[act_index].nb_elt;
    }
  }
  
  free(message);
  return 0;
} // player_process
