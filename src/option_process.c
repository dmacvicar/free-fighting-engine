#include "global_add.h"
#include "option_process.h"
#include "main_process.h"
#include "sound_fx_manager.h"
#include "read_config.h"
#include "background_process.h"

#include "mp3.h"
#include "macros.h"
#include "logger.h"
#include "sensei_config.h"

/** \file option_process.c
 * \brief Functions to change game config
 */

int option_process(Game_variables variables, Player_variables * player_array, int time){
  
  /*
   * Fixing the blazingly fast menu with has_control
   */
  for (i=0;i<2;i++){
    if (want_move(player_array,i)){
      //fprintf(stdout,"want move\n");
      if (player_array[i].has_control==0){
	clear_input_states(player_array,i);
	variables->f_keys.Esc = 0;
      }
      else
	player_array[i].has_control = 0;
    }else{
      if (player_array[i].has_control==0)
	player_array[i].has_control=1;
    }
  }

  play_music(&variables->System.title_music);
 
  if (variables->f_keys.Esc==1) {
    variables->f_keys.Esc=0;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.OCancelgrp, variables->System.OCancelnb, 255, 128);
    else
      Buzz();
    rest(50);
    variables->System.Ocurrentitem = 0;
    next_state(variables);
    variables->not_show =1;
    stop_music(&variables->System.title_music);
    
  }

  /*
    Background management
  */
  background_process(&variables->System.Option_bg);

  if (variables->f_keys.F2==1){
    variables->f_keys.F2=0;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.ODonecursorgrp, variables->System.ODonecursornb, 255, 128);
    else
      Done();
    rest(50);
    variables->System.Ocurrentitem = 0;
    variables->Game_state = 5;
    variables->not_show = 1;
  }
  
  if (validation(player_array)){
    if (variables->System.Ocurrentitem==6){
      if (variables->System.Sndexist)
	sndPlay(variables->System.Systemsnd, variables->System.ODonecursorgrp, variables->System.ODonecursornb, 255, 128);
      else
	Done();
      rest(50);
      variables->System.Ocurrentitem = 0;
      variables->Game_state = 5;
      variables->not_show = 1;
    }
    if (variables->System.Ocurrentitem==7){
      if (variables->System.Sndexist)
	sndPlay(variables->System.Systemsnd, variables->System.ODonecursorgrp, variables->System.ODonecursornb, 255, 128);
      else
	Done();
      rest(50);
      save_config (variables,player_array);
    }
    if (variables->System.Ocurrentitem==8){
      if (variables->System.Sndexist)
	sndPlay(variables->System.Systemsnd, variables->System.ODonecursorgrp, variables->System.ODonecursornb, 255, 128);
      else
	Done();
      rest(50);
      set_default_config(variables);
    }
    if (variables->System.Ocurrentitem==9){
      if (variables->System.Sndexist)
	sndPlay(variables->System.Systemsnd, variables->System.OCancelgrp, variables->System.OCancelnb, 255, 128);
      else
	Buzz();
      rest(50);
      variables->System.Ocurrentitem = 0;
      next_state(variables);
      variables->not_show = 1;
    }
  }
  
  /* moving selected item up */
  if ((player_array[0].Player_input.state[0])||(player_array[1].Player_input.state[0])){
    variables->System.Ocurrentitem--;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.OMvcursorgrp, variables->System.OMvcursornb, 255, 128);
    else
      Bing();
    
    if (variables->System.Ocurrentitem<0)
      variables->System.Ocurrentitem = 9;
  }
  
  /* moving item down */
  if ((player_array[0].Player_input.state[1])||(player_array[1].Player_input.state[1])){
    variables->System.Ocurrentitem++;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.OMvcursorgrp, variables->System.OMvcursornb, 255, 128);
    else
      Bing();
    
    if (variables->System.Ocurrentitem>9)
      variables->System.Ocurrentitem = 0;
  }
  
  /* moving item left */
  if ((player_array[0].Player_input.state[2])||(player_array[1].Player_input.state[2])){
    switch (variables->System.Ocurrentitem){
    case 0 :
      variables->Game_config.Difficulty--;
      if (variables->Game_config.Difficulty<0)
	variables->Game_config.Difficulty = 0;
      break;
    case 1 :
      variables->Game_config.Life--;
      if (variables->Game_config.Life<1)
	variables->Game_config.Life = 1;
      break;
    case 2 :
      variables->Game_config.Time--;
      if (variables->Game_config.Time<0)
	variables->Game_config.Time = 0;
      break;
    case 3:
      variables->Game_config.Game_speed--;
      if (variables->Game_config.Game_speed<1)
	variables->Game_config.Game_speed = 1;
      break;
    case 4:
      variables->Game_config.WavVolume--;
      if (variables->Game_config.WavVolume<0)
	variables->Game_config.WavVolume = 0;
      set_volume ( variables->Game_config.WavVolume , variables->Game_config.MidiVolume );
      break;
    case 5 :
      variables->Game_config.MidiVolume--;
      if (variables->Game_config.MidiVolume<0)
	variables->Game_config.MidiVolume = 0;
      set_volume ( variables->Game_config.WavVolume , variables->Game_config.MidiVolume );
      break;
    default :
      break;
    }
  }

   /* moving item right */
  if ((player_array[0].Player_input.state[3])||(player_array[1].Player_input.state[3])){
    switch (variables->System.Ocurrentitem){
    case 0 :
      variables->Game_config.Difficulty++;
      if (variables->Game_config.Difficulty>9)
	variables->Game_config.Difficulty = 9;
      break;
    case 1 :
      variables->Game_config.Life++;
      if (variables->Game_config.Life>100)
	variables->Game_config.Life = 100;
      break;
    case 2 :
      variables->Game_config.Time++;
      if (variables->Game_config.Time>99)
	variables->Game_config.Time = 99;
      break;
    case 3:
      variables->Game_config.Game_speed++;
      if (variables->Game_config.Game_speed>120)
	variables->Game_config.Game_speed = 120;
      break;
    case 4:
      variables->Game_config.WavVolume++;
      if (variables->Game_config.WavVolume>255)
	variables->Game_config.WavVolume = 255;
      set_volume ( variables->Game_config.WavVolume , variables->Game_config.MidiVolume );
      break;
    case 5 :
      variables->Game_config.MidiVolume++;
      if (variables->Game_config.MidiVolume>255)
	variables->Game_config.MidiVolume = 255;
      set_volume ( variables->Game_config.WavVolume , variables->Game_config.MidiVolume );
      break;
    default :
      break;
    }
  }

  return 0;
}
