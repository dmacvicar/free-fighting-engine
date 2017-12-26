#include "choice_process.h"
#include "global.h"
#include "global_add.h"
#include "main_process.h"
#include "sound_fx_manager.h"
#include "string.h"
#include "mp3.h"
#include "background_process.h"
#include "sensei_config.h"
#include "select_process.h"

#include "macros.h"
#include "config.h"

#include <stdio.h>

/** \file choice_process.c
 * \brief part of the engine that deal with the main title menu
 */

int choice_process(Game_variables variables, Player_variables * player_array, int time){
  int last_item;
  int i;
  int player;
  
  /*
   * Fixing the blazingly fast menu with has_control
   */
  for (i=0;i<2;i++){
    if (want_move(player_array,i)){
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
  
  if (variables->f_keys.Esc==1) {
    variables->f_keys.Esc=0;
    stop_music(&variables->System.title_music);
    next_state(variables);
    variables->not_show =1;
  }
  
  // Titlebgm sound management
  play_music(&variables->System.title_music);
  
  // TRON("before bg management");
  /*
    Background management
  */
  background_process(&variables->System.Title_bg);

  // Little hack for KOF 91 bgs
  if ((variables->System.Title_bg.type==1)||(variables->System.Title_bg.type==2)){
    variables->System.Title_bg.camerax = 0;
    variables->System.Title_bg.cameray = 0;
  }

  if (validation(player_array)){
    player = validation(player_array);
    variables->not_show = 1;
    stop_music(&variables->System.title_music);
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.Donecursorgrp, variables->System.Donecursornb, 255, 128);
    else
      Done();
    variables->System.Select_struct.stage_controller = 0;
    variables->System.Select_struct.bg_selected = 0;
    variables->System.Vs_struct.state = 0;

    switch (variables->System.currentitem){
    case 0: // Story or arcade
      variables->Game_state = 6;
      gmode = 0;
      variables->System.Select_struct.stage_showed = 0;
      
      if (player==1){
	variables->System.Select_struct.p1_showed = 1;
	variables->System.Select_struct.p2_showed = 0;
	variables->System.Select_struct.p1_max_selecter = 1;
	variables->System.Select_struct.p2_max_selecter = 1;
	variables->System.Select_struct.p1_controller = 1;
	variables->System.Select_struct.p2_controller = 0;
	variables->System.Select_struct.p1_selecter = 0;
	
      }else{
	variables->System.Select_struct.p1_showed = 0;
	variables->System.Select_struct.p2_showed = 1;
	variables->System.Select_struct.p2_max_selecter = 1;
	variables->System.Select_struct.p1_max_selecter = 1;
	variables->System.Select_struct.p1_controller = 0;
	variables->System.Select_struct.p2_controller = 2;
      }
      
      variables->not_show = 1;
      return 0;
      break;
    case 1: // vs mode
      variables->Game_state = 6;
      variables->not_show = 1;
      variables->System.Select_struct.stage_showed = 1;
      gmode = 1;
      variables->System.Select_struct.p1_showed = 1;
      variables->System.Select_struct.p2_showed = 1;
      variables->System.Select_struct.p1_max_selecter = 1;
      variables->System.Select_struct.p2_max_selecter = 1;
      variables->System.Select_struct.p1_controller = 1;
      variables->System.Select_struct.p2_controller = 2;
      return 0;
      break;
    case 2: // Team mode
      variables->Game_state = 6;
      variables->not_show = 1;
      variables->System.Select_struct.stage_showed = 0;
      gmode = 2;
      if (player==1){
	variables->System.Select_struct.p1_showed = 1;
	variables->System.Select_struct.p2_showed = 0;
	variables->System.Select_struct.p1_max_selecter = 3;
	variables->System.Select_struct.p1_controller = 1;
	variables->System.Select_struct.p2_controller = 0;
      }else{
	variables->System.Select_struct.p1_showed = 0;
	variables->System.Select_struct.p2_showed = 1;
	variables->System.Select_struct.p2_max_selecter = 3;
	variables->System.Select_struct.p1_controller = 0;
	variables->System.Select_struct.p2_controller = 2;
      }
      return 0;
      break;
    case 3: // Team VS
      variables->Game_state = 6;
      variables->not_show = 1;
      variables->System.Select_struct.stage_showed = 1;
      gmode = 3;
      variables->System.Select_struct.p1_showed = 1;
      variables->System.Select_struct.p2_showed = 1;
      variables->System.Select_struct.p1_max_selecter = 3;
      variables->System.Select_struct.p2_max_selecter = 3;
      variables->System.Select_struct.p1_controller = 1;
      variables->System.Select_struct.p2_controller = 2;
      return 0;
      break;
    case 4: // Team coop
      variables->Game_state = 6;
      variables->not_show = 1;
      gmode = 4;
      variables->System.Select_struct.stage_showed = 0;
      variables->System.Select_struct.p1_showed = 1;
      variables->System.Select_struct.p2_showed = 1;
      variables->System.Select_struct.p1_max_selecter = 1;
      variables->System.Select_struct.p2_max_selecter = 1;
      variables->System.Select_struct.p1_controller = 1;
      variables->System.Select_struct.p2_controller = 2;
      return 0;
      break;
    case 5: // Survival
      variables->Game_state = 6;
      variables->not_show = 1;
      variables->System.Select_struct.stage_showed = 0;
      gmode = 5;
      if (player==1){
	variables->System.Select_struct.p1_showed = 1;
	variables->System.Select_struct.p2_showed = 0;
	variables->System.Select_struct.p1_max_selecter = 1;
	variables->System.Select_struct.p1_controller = 1;
	variables->System.Select_struct.p2_controller = 0;
      }else{
	variables->System.Select_struct.p1_showed = 0;
	variables->System.Select_struct.p2_showed = 1;
	variables->System.Select_struct.p2_max_selecter = 1;
	variables->System.Select_struct.p1_controller = 0;
	variables->System.Select_struct.p2_controller = 2;
      }
      return 0;
      break;
    case 6: //survival coop
      variables->Game_state = 6;
      variables->not_show = 1;
      gmode = 6;
      variables->System.Select_struct.stage_showed = 0;
      variables->System.Select_struct.p1_showed = 1;
      variables->System.Select_struct.p2_showed = 1;
      variables->System.Select_struct.p1_max_selecter = 1;
      variables->System.Select_struct.p2_max_selecter = 1;
      variables->System.Select_struct.p1_controller = 1;
      variables->System.Select_struct.p2_controller = 2;
      return 0;
      break;
    case 7: // Training
      variables->Game_state = 6;
      variables->not_show = 1;
      gmode = 7;
      variables->System.Select_struct.stage_showed = 1;
      variables->System.Select_struct.p1_showed = 1;
      variables->System.Select_struct.p2_showed = 1;
      variables->System.Select_struct.p1_max_selecter = 1;
      variables->System.Select_struct.p2_max_selecter = 1;
      variables->System.Select_struct.p1_controller = 1;
      variables->System.Select_struct.p2_controller = 2;
      return 0;
      break;
    case 8: //watch
      variables->Game_state = 6;
      variables->not_show = 1;
      gmode = 8;
      variables->System.Select_struct.stage_showed = 1;
      variables->System.Select_struct.p1_showed = 1;
      variables->System.Select_struct.p2_showed = 1;
      variables->System.Select_struct.p1_controller = 1;
      variables->System.Select_struct.p2_controller = 2;
      variables->System.Select_struct.p1_max_selecter = 1;
      variables->System.Select_struct.p2_max_selecter = 1;
      return 0;
      break;
    case 9: // Option menu
      variables->Game_state = 4;
      variables->not_show = 1;
      return 0;
      break;
    case 10 :
      /* exit menu */
      variables->Game_state = 666;
      variables->not_show = 1;
      return 0;
      break;
    default:
      break;
    }
  }

  /* moving selected item up */
  if ((player_array[0].Player_input.state[0])||(player_array[1].Player_input.state[0])){
    variables->System.currentitem--;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.Mvcursorgrp, variables->System.Mvcursornb, 255, 128);
    else
      Bing();
    
    if (variables->System.currentitem<0) {
      variables->System.currentitem = (ITEM_NUMBER-1);
      while ((variables->System.itemname[variables->System.currentitem]==NULL)||(strcmp(variables->System.itemname[variables->System.currentitem],"")==0)) (variables->System.currentitem)--;
      i=0;
      variables->System.firstitem = variables->System.currentitem;
      while ((i<variables->System.visibleitems-1)&&(variables->System.firstitem>0)){
	i++;
	variables->System.firstitem--;
	while ((variables->System.itemname[variables->System.firstitem]==NULL)||(strcmp(variables->System.itemname[variables->System.firstitem],"")==0)){
	  variables->System.firstitem--;
	}
      }
    }else{
      while (((variables->System.itemname[variables->System.currentitem]==NULL)||(strcmp(variables->System.itemname[variables->System.currentitem],"")==0))&&(variables->System.currentitem>0)){
	(variables->System.currentitem)--;
      }
      if ((variables->System.currentitem)<(variables->System.firstitem))
	variables->System.firstitem = variables->System.currentitem;
      if (variables->System.currentitem<0) {
	variables->System.currentitem = (ITEM_NUMBER-1);
	while ((variables->System.itemname[variables->System.currentitem]==NULL)||(strcmp(variables->System.itemname[variables->System.currentitem],"")==0)) (variables->System.currentitem)--;
	i=0;
	variables->System.firstitem = variables->System.currentitem;
	while ((i<variables->System.visibleitems)&&(variables->System.firstitem>0)){
	  while ((variables->System.itemname[variables->System.firstitem]==NULL)||(strcmp(variables->System.itemname[variables->System.firstitem],"")==0)){
	    variables->System.firstitem--;
	  }
	  i++;
	  variables->System.firstitem--;
	}
      }
    }
  }
  
  /* moving selected item down */

  /* determine the last item showed*/
  last_item = variables->System.firstitem;
  i = 0;
  while ((i<variables->System.visibleitems)&&(last_item<=ITEM_NUMBER-1)){
    while ((variables->System.itemname[last_item]==NULL)||(strcmp(variables->System.itemname[last_item],"")==0)){
      last_item++;
    }
    i++;
    last_item++;
  }

  if ((player_array[0].Player_input.state[1])||(player_array[1].Player_input.state[1])){
    variables->System.currentitem++;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.Mvcursorgrp, variables->System.Mvcursornb, 255, 128);
    else
      Bing();

    if (variables->System.currentitem>ITEM_NUMBER-1){
      variables->System.currentitem = 0;
      variables->System.firstitem = 0;
      while ((variables->System.itemname[variables->System.currentitem]==NULL)||(strcmp(variables->System.itemname[variables->System.currentitem],"")==0)){
	(variables->System.currentitem)++;
	//fprintf(stderr,"Current item too high , empty , current item = %i\n",variables->System.currentitem);
      }
    }else{
      while ((variables->System.itemname[variables->System.currentitem]==NULL)||(strcmp(variables->System.itemname[variables->System.currentitem],"")==0)){
	(variables->System.currentitem)++;
	//fprintf(stderr,"Current item empty , current item = %i\n",variables->System.currentitem);
      }
    }
    if (variables->System.currentitem>ITEM_NUMBER-1){
      variables->System.currentitem = 0;
      variables->System.firstitem = 0;
      while ((variables->System.itemname[variables->System.currentitem]==NULL)||(strcmp(variables->System.itemname[variables->System.currentitem],"")==0))
	(variables->System.currentitem)++;
    }

    if ((variables->System.currentitem)>=(last_item)){
      variables->System.firstitem = variables->System.firstitem++;
     while ((variables->System.itemname[variables->System.firstitem]==NULL)||(strcmp(variables->System.itemname[variables->System.firstitem],"")==0))
       (variables->System.firstitem)++;
    }
    
  }

  /* determine the box position*/
  i = 0;
  last_item = variables->System.firstitem;
  while ((last_item<=ITEM_NUMBER-1)&&(last_item!=variables->System.currentitem)){
    if ((variables->System.itemname[last_item]!=NULL)&&(strcmp(variables->System.itemname[last_item],"")!=0))
      i++;
    last_item++;
  }
  
  variables->System.boxposition = i;
  
  return 0;
}
