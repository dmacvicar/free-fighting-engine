#include "global.h"
#include "global_add.h"
#include "main_process.h"
#include "sound_fx_manager.h"
#include "read_config.h"
#include "mp3.h"
#include "main_process.h"
#include "background_process.h"
#include "keyconfig_process.h"
#include "input_reader.h"
#include <stdio.h>
#include "sensei_config.h"

#include "macros.h"
#include "logger.h"
/** \file keyconfig_process.c
 * \brief Function to change Key configuration
 */

/** \brief Function to check if the key has been already assigned to another move
*/
int key_not_used(Player_variables * player_array, int player, int key){
  int current_key;
  for (current_key = 0;current_key<11;current_key++){
    if (player_array[player].Player_input.keys[current_key]==key)
      return 0;
  }
  return 1;
}


/** \brief Function to config keys
 */
int keyconfig_process(Game_variables variables, Player_variables * player_array, int time){
  int player_choice; /* Var to know wich player have change key */
  int i;
  int key_pressed = 0;
  char * message;
  message = (char*)malloc(255*sizeof(char));
  player_choice = 0;
  
   /*
   * Optionbgm sound management
   */
  play_music(&variables->System.title_music);
  
  /*
   * Fixing the blazingly fast menu with has_control
   */
  for (i=0;i<2;i++){
    if (want_move(player_array,i)){
      //fprintf(stdout,"want move\n");
      if (player_array[i].has_control==0)
	clear_input_states(player_array,i);
      else
	player_array[i].has_control = 0;
    }else{
      if (player_array[i].has_control==0)
	player_array[i].has_control=1;
    }
  }

  /*
    Background management
  */
  background_process(&variables->System.Option_bg);

  if (variables->f_keys.Esc==1) {
    variables->f_keys.Esc=0;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.OCancelgrp, variables->System.OCancelnb, 255, 128);
    else
      Buzz();
    variables->System.Ocurrentitem = 0;
    variables->System.Ocurrentitem2 = 0;
    next_state(variables);
    variables->not_show =1;
    //stop_music(&variables->System.title_music)
    return 0;
  }
  
  /* Changing a key or a button */
  if ((player_array[0].Player_input.key_waited!=0)||(player_array[1].Player_input.key_waited!=0)||(player_array[0].Player_input.buton_waited!=0)||(player_array[1].Player_input.buton_waited!=0))
    {
      if ((player_array[0].Player_input.key_waited!=0)||(player_array[1].Player_input.key_waited!=0)){
	if (player_array[0].Player_input.key_waited!=0){
	  /*
	    sprintf(message,"waiting for a key for p1\n");
	    TRON(message);
	  */
	  key_pressed = readkey()>>8;
	  if (key_not_used(player_array,0,key_pressed)){
	    player_array[0].Player_input.keys[player_array[0].Player_input.key_waited-1]=key_pressed;
	    player_array[0].Player_input.key_waited=0;
	    player_array[0].has_control = 0;
	  }
	}else{
	  /*
	    sprintf(message,"waiting for a key for p2\n");
	    TRON(message);
	  */
	  key_pressed = readkey()>>8;
	  if (key_not_used(player_array,1,key_pressed)){
	    player_array[1].Player_input.keys[player_array[1].Player_input.key_waited-1]=key_pressed;
	    player_array[1].Player_input.key_waited=0;
	    player_array[0].has_control = 0;
	  }
	}
	clear_keybuf();
      }else{
	if (player_array[0].Player_input.buton_waited!=0){
	  /*
	    sprintf(message,"waiting for a buton for p1\n");
	    TRON(message);
	  */
	  buton_pressed(player_array,0);
	  player_array[0].Player_input.buton_waited=0;
	}else{
	  /*
	    sprintf(message,"waiting for a buton for p2\n");
	    TRON(message);
	  */
	  buton_pressed(player_array,1);
	  player_array[1].Player_input.buton_waited=0;
	}

       }
      clear_keybuf();
      return 0;
    }
  
  /* moving selected item up player 1*/
  if (player_array[0].Player_input.state[0]){
    variables->System.Ocurrentitem--;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.OMvcursorgrp, variables->System.OMvcursornb, 255, 128);
    else
      Bing();
    
    if (variables->System.Ocurrentitem<0)
      variables->System.Ocurrentitem = 13;
  }
  
  /* moving item down player 1*/
  if (player_array[0].Player_input.state[1]){
    variables->System.Ocurrentitem++;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.OMvcursorgrp, variables->System.OMvcursornb, 255, 128);
    else
      Bing();
  }
  if (variables->System.Ocurrentitem>13)
    variables->System.Ocurrentitem = 0;
  
  
  /* moving selected item up player 2*/
  if (player_array[1].Player_input.state[0]){
    variables->System.Ocurrentitem2--;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.OMvcursorgrp, variables->System.OMvcursornb, 255, 128);
    else
      Bing();
    
    if (variables->System.Ocurrentitem2<0)
      variables->System.Ocurrentitem = 13;
  }
  
  /* moving item down player 2*/
  if (player_array[1].Player_input.state[1]){
    variables->System.Ocurrentitem2++;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.OMvcursorgrp, variables->System.OMvcursornb, 255, 128);
    else
      Bing();
  }

  if (variables->System.Ocurrentitem2>13)
    variables->System.Ocurrentitem = 0;
  
   if (validation(player_array)){
    if (variables->System.Ocurrentitem==13){
      if (variables->System.Sndexist)
	sndPlay(variables->System.Systemsnd, variables->System.OCancelgrp, variables->System.OCancelnb, 255, 128);
      else
	Buzz();
      rest(50);
      variables->System.Ocurrentitem = 0;
      next_state(variables);
      variables->not_show = 1;
      stop_music(&variables->System.title_music);
      return 0;
    }
   }
  
  /* moving item left */
   if ((player_array[0].Player_input.state[2])&&(variables->System.Ocurrentitem==0)){
     if (player_array[0].Player_input.use_joystick>0)
       (player_array[0].Player_input.use_joystick)--;
   }
   if ((player_array[1].Player_input.state[2])&&(variables->System.Ocurrentitem2==0)){
     if (player_array[1].Player_input.use_joystick>0)
       (player_array[1].Player_input.use_joystick)--;
   }
   
   /* moving item right */
   if ((player_array[0].Player_input.state[3])&&(variables->System.Ocurrentitem==0)){
     (player_array[0].Player_input.use_joystick++);
   }
   if ((player_array[1].Player_input.state[3])&&(variables->System.Ocurrentitem2==0)){
     (player_array[1].Player_input.use_joystick++);
   }
   
   /* item validation */
   player_choice = validation(player_array);
   if (player_choice!=0){
     /* if exit is choosen */
     if (((player_choice==1)&&(variables->System.Ocurrentitem==13))||((player_choice==2)&&(variables->System.Ocurrentitem2=13))){
       if (variables->System.Sndexist)
	 sndPlay(variables->System.Systemsnd, variables->System.OCancelgrp, variables->System.OCancelnb, 255, 128);
       else
	 Buzz();
       rest(50);
       variables->System.Ocurrentitem = 0;
       variables->System.Ocurrentitem2 = 0;
       next_state(variables);
       variables->not_show =1;
       stop_music(&variables->System.title_music);
       return 0;
     }
       
     if (variables->System.Sndexist)
       sndPlay(variables->System.Systemsnd, variables->System.ODonecursorgrp, variables->System.ODonecursornb, 255, 128);
     else
       Done();

     /* if default values is choosen */
     if ((player_choice==1)&&(variables->System.Ocurrentitem==12))
       set_default_keys(player_array,1);
     if ((player_choice==2)&&(variables->System.Ocurrentitem==12))
       set_default_keys(player_array,2);
     
     /* key changing section */
     /* If player 1 has validate a key and is using joystick */
     if ((player_choice==1)&&(player_array[0].Player_input.use_joystick!=0)){
       switch (variables->System.Ocurrentitem){
       case 5:
	 player_array[0].Player_input.buton_waited = 1;
	 break;
       case 6:
	 player_array[0].Player_input.buton_waited = 2;
	 break;
       case 7:
	 player_array[0].Player_input.buton_waited = 3;
	 break;
       case 8:
	 player_array[0].Player_input.buton_waited = 4;
	 break;
       case 9:
	 player_array[0].Player_input.buton_waited = 5;
	 break;
       case 10:
	 player_array[0].Player_input.buton_waited = 6;
	 break;
       case 11:
	 player_array[0].Player_input.buton_waited = 7;
	 break;
       default:
	 player_array[0].Player_input.buton_waited = 0;
	 break;
       }
     }
     /* if player 2 has validate a key and is using joystick */
     if ((player_choice==2)&&(player_array[1].Player_input.use_joystick!=0)){
        switch (variables->System.Ocurrentitem2){
       case 5:
	 player_array[1].Player_input.buton_waited = 1;
	 break;
       case 6:
	 player_array[1].Player_input.buton_waited = 2;
	 break;
       case 7:
	 player_array[1].Player_input.buton_waited = 3;
	 break;
       case 8:
	 player_array[1].Player_input.buton_waited = 4;
	 break;
       case 9:
	 player_array[1].Player_input.buton_waited = 5;
	 break;
       case 10:
	 player_array[1].Player_input.buton_waited = 6;
	 break;
       case 11:
	 player_array[1].Player_input.buton_waited = 7;
	 break;
       default:
	 player_array[1].Player_input.buton_waited = 0;
	 break;
       }
     }
     /* if player 1 has validate a key and is using keyboard */
     if ((player_choice==1)&&(player_array[0].Player_input.use_joystick==0)){
       if ((variables->System.Ocurrentitem>0)&&(variables->System.Ocurrentitem<12))
	 player_array[0].Player_input.key_waited = variables->System.Ocurrentitem;
     }
     /* if player 2 has validate a key and is using keyboard */
     if ((player_choice==2)&&(player_array[1].Player_input.use_joystick==0)){
       if ((variables->System.Ocurrentitem2>0)&&(variables->System.Ocurrentitem2<12))
	 player_array[1].Player_input.key_waited = variables->System.Ocurrentitem2;
     }
   }
 
   return 0;
}
