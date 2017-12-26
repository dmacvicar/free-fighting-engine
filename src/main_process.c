#include <stdio.h>
#include <stdlib.h>

#include "main_process.h"
#include "story_process.h"
#include "choice_process.h"
#include "option_process.h"
#include "keyconfig_process.h"
#include "select_process.h"
#include "vs_process.h"
#include "battle_process.h"
#include "global_add.h"
#include "macros.h"
#include "input_reader.h"
#include "logger.h"
#include "global.h"

/** \file main_process.c
 * \brief Functions need in all processes and main function that called each distinct process
 */

int next_state(Game_variables variables){
  // action of 'escaping' on game_state see docs/kof91_game_states
  int result;
  switch (variables->Game_state){
  case 0:
    result = 1;
    break;	
  case 1:
    result = 2;    
    break;
  case 2 :
    result = 3;
    break;
  case 3 :
    result = 666;
    break;
  case 4 :
    result = 3;
    break;
  case 5 :
    result = 4;
    break;
  case 6 :
    result = 3;
    break;
  case 7 :
    result = 8;
    break;
  case 8:
    result = 9;
    break;
  case 9 :
    result = 10;
    break;
  case 10 :
    result = 3;
    break;
  case 11 :
    result = 3;
    break;
  case 101 :
    result = 666;
    break;
  case 102 :
    result = 666;
    break;
  case 103 :
    result = 666;
    break;
  case 104 :
    result = 666;
    break;
  case 105 :
    result = 666;
    break;
  case 106 :
    result = 666;
    break;
  case 107 :
    result = 666;
    break;
  case 108 :
    result = 666;
    break;
  case 109 :
    result = 666;
    break;
  case 110 :
    result = 666;
    break;
  case 111 :
    result = 666;
    break;
  case 120 : // dummy mode test
    result = 666;
    break;
  default :
    result = 666;
    break;
  }
  variables->Game_state =  result;
  return 0;
}

int process_function_keys(Game_variables variables){
  if (variables->Game_config.Allow_debug){
    if (variables->f_keys.F1) {
      (variables->f_keys.F1) = 0;
      if (variables->Game_config.Debug_on){
	variables->Game_config.Debug_on = 0;
	SENSEI_DEBUG_ON = 0;
      }
      else{
	SENSEI_DEBUG_ON = 1;
	variables->Game_config.Debug_on = 1;
      }
    }
  }
  return 0;
}

int validation(Player_variables * player_array){
  int current_player,current_key,answer;
  answer = 0;
   
  for (current_player=0;current_player<2;current_player++){
    for (current_key=4;current_key<11;current_key++)//aka if a button is pressed
      {
	if (player_array[current_player].Player_input.state[current_key])
	  answer = current_player+1;
      }
  }
   
  if (key[KEY_ENTER]) answer = 1;
   
  return answer;
}

int main_process(Game_variables variables,Player_variables * player_array,int time){
  int error;
  char * message;
  
  // we hope initialisations are on...
  if (variables->Game_state==0) variables->Game_state=1;

  error = 0;
  message = (char*)malloc(255*sizeof(char));
  if (variables->Game_config.Debug_on){
    sprintf(message,"Begining main_process in state %i and Path = %s",variables->Game_state,variables->Path);
    TRON(message);
  }
  
  input_reader(variables,player_array);
  error += process_function_keys(variables);
  clear_keybuf();
  
  switch (variables->Game_state){
  case 1: 
    if (variables->Game_config.Debug_on){
      sprintf(message,"Beginning story_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    error += story_process(variables,player_array,&variables->System.Intro,time);
    if (variables->Game_config.Debug_on){
      sprintf(message,"Exiting story_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    break;
  case 2:
    error += story_process(variables,player_array,&variables->System.Open,time);
    break;
  case 3:
    if (variables->Game_config.Debug_on){
      sprintf(message,"Beginning choice_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    if (variables->System.Select_struct.loaded == 0){
      error += make_lists(variables,player_array);
      if (variables->System.Select_struct.type==1)
	variables->System.Select_struct.faces = make_faces_screen(variables,player_array);
      variables->System.Select_struct.loaded = 1;
    }
    error += choice_process(variables,player_array,time);
    if (variables->Game_config.Debug_on){
      sprintf(message,"Exiting choice_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    break;
  case 4:
    if (variables->Game_config.Debug_on){
      sprintf(message,"Beginning option_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    error += option_process(variables,player_array,time);
    if (variables->Game_config.Debug_on){
      sprintf(message,"Exit option_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    break;
  case 5:
    if (variables->Game_config.Debug_on){
      sprintf(message,"Beginning keyconfig_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    error += keyconfig_process(variables,player_array,time);
    if (variables->Game_config.Debug_on){
      sprintf(message,"Exit keyconfig_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    break;
  case 6: 
    if (variables->Game_config.Debug_on){
      sprintf(message,"Beginning select_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    error += select_process(variables,player_array,time);
    //startmenu();
    if (variables->Game_config.Debug_on){
      sprintf(message,"Exit select_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    break;
  case 7:
    variables->Game_state = 8;
    variables->not_show = 1;
    break;
  case 8:
    if (variables->Game_config.Debug_on){
      sprintf(message,"Beginning Vs_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    error += vs_process(variables,player_array,time);
    if (variables->Game_config.Debug_on){
      sprintf(message,"Exit Vs_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    break;
  case 9:
    variables->Game_state = 10;
    variables->not_show = 1;
    break;
  case 10:
    if (SENSEI_DEBUG_ON)
      TRON("Begin battle_process");
    error += battle_process(variables,player_array,time);
    if (SENSEI_DEBUG_ON)
      TRON("Exit battle_process");
    break;
  case 101:
    error += story_process(variables,player_array,&variables->System.Intro,time);
    break;
  case 102:
    error += story_process(variables,player_array,&variables->System.Open,time);
    break;
 case 103:
   if (variables->Game_config.Debug_on){
     sprintf(message,"Beginning choice_process in state %i and Path = %s",variables->Game_state,variables->Path);
     TRON(message);
   }
   if (variables->System.Select_struct.loaded == 0){
     error += make_lists(variables,player_array);
     if (variables->System.Select_struct.type==1)
       variables->System.Select_struct.faces = make_faces_screen(variables,player_array);
     variables->System.Select_struct.loaded = 1;
   }
   error += choice_process(variables,player_array,time);
   if (variables->Game_config.Debug_on){
     sprintf(message,"Exiting choice_process in state %i and Path = %s",variables->Game_state,variables->Path);
     TRON(message);
   }
   break;
  case 104:
    if (variables->Game_config.Debug_on){
      sprintf(message,"Beginning option_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    error += option_process(variables,player_array,time);
    if (variables->Game_config.Debug_on){
      sprintf(message,"Exit option_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    break;
  case 105:
    if (variables->Game_config.Debug_on){
      sprintf(message,"Beginning keyconfig_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    error += keyconfig_process(variables,player_array,time);
    if (variables->Game_config.Debug_on){
      sprintf(message,"Exit keyconfig_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    break;
  case 106:
    if (variables->Game_config.Debug_on){
      sprintf(message,"Beginning select_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    error += select_process(variables,player_array,time);
    //startmenu();
    if (variables->Game_config.Debug_on){
      sprintf(message,"Exit select_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    break;
  case 108:
    if (variables->Game_config.Debug_on){
      sprintf(message,"Beginning Vs_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    error += vs_process(variables,player_array,time);
    if (variables->Game_config.Debug_on){
      sprintf(message,"Exit Vs_process in state %i and Path = %s",variables->Game_state,variables->Path);
      TRON(message);
    }
    break;
  case 110 :
    if (SENSEI_DEBUG_ON)
      TRON("Begin battle_process");
    error += battle_process(variables,player_array,time);
    if (SENSEI_DEBUG_ON)
      TRON("Exit battle_process");
    break;
  case 666:
    return 0;
    break;
  case 766:
    return 0;
    break;
  default :
    sprintf(message,"In main process strange game state %i",variables->Game_state);
    ERROR(message);
    error++;
    break;
  }
  
  free(message);
  if (error==0) 
    return 0;
  else{
    if (variables->Game_config.Debug_on)
      ERROR("Error in main_process");
    return -1;
  }
}
