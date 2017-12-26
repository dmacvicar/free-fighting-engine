#include <stdio.h>
#include <stdlib.h>

#include "allegro.h"
#include "input_reader.h"

/** \file input_reader.c
 * \brief Functions to tests inputs without having to know if it's joy or not
 */

/**
   \brief function to test if a function key is pressed and change the variables struct
*/
void test_function_keys(Game_variables variables){
  if (key[KEY_ESC])
    (variables->f_keys.Esc) = 1;
  else
    (variables->f_keys.Esc) = 0;
   
  if (key[KEY_F1])
    (variables->f_keys.F1) = 1;
  else
    (variables->f_keys.F1) = 0;

  if (key[KEY_F2])
    (variables->f_keys.F2) = 1;
  else
    (variables->f_keys.F2) = 0;

  if (key[KEY_F12])
    (variables->f_keys.F12) = 1;
  else
    (variables->f_keys.F12) = 0;
      
}

/* absolutely not optimized, I was lazy */
int test_player_input(Game_variables variables,Player_variables * player_array){
  int current_key,current_player;
  current_player=0;
  current_key=0;
        
  for (current_player = 0; current_player<2;current_player++){
	
    //fprintf(stdout,"player %d usejoystick = %d\n",current_player,player_array[current_player].Player_input.use_joystick);
	
    if (!(player_array[current_player].computer_input)){
      if ((player_array[current_player]).Player_input.use_joystick==0){
	for (current_key = 0;current_key<11;current_key++){
	  if (key[(player_array[current_player].Player_input.keys[current_key])])
	    {
	      player_array[current_player].Player_input.state[current_key]=1;
	    }
	  else
	    { 
	      player_array[current_player].Player_input.state[current_key]=0;
	    }
	}
      }
      else
	{
	  poll_joystick();
	  for (current_key = 0;current_key<7;current_key++){
	    if (joy[(player_array[current_player]).Player_input.use_joystick-1].button[(player_array[current_player].Player_input.joybuton[current_key])].b) (player_array[current_player]).Player_input.state[current_key+4]=1;
	    else
	      (player_array[current_player]).Player_input.state[current_key+4]=0;
	  }
	  if (joy[(player_array[current_player]).Player_input.use_joystick-1].stick[0].axis[1].d1)
	    (player_array[current_player]).Player_input.state[0] = 1;
	  else
	    (player_array[current_player]).Player_input.state[0] = 0;
	  if (joy[(player_array[current_player]).Player_input.use_joystick-1].stick[0].axis[1].d2)
	    (player_array[current_player]).Player_input.state[1] = 1;
	  else
	    (player_array[current_player]).Player_input.state[1] = 0;
	  if (joy[(player_array[current_player]).Player_input.use_joystick-1].stick[0].axis[0].d1)
	    (player_array[current_player]).Player_input.state[2] = 1;
	  else
	    (player_array[current_player]).Player_input.state[2] = 0;
	  if (joy[(player_array[current_player]).Player_input.use_joystick-1].stick[0].axis[0].d2)
	    (player_array[current_player]).Player_input.state[3] = 1;
	  else
	    (player_array[current_player]).Player_input.state[3] = 0;
	}
    }
    else
      fprintf(stdout,"Computer input not yet implemented\n");
  }
  return 0;
}

int input_reader(Game_variables variables, Player_variables * player_array){
  test_function_keys(variables);
  test_player_input(variables,player_array);
  return 0;
}

/** \brief function to know if a buton has been pressed, usefull for menu validation
 */
int buton_pressed(Player_variables * player_array,int player){
  int not_pressed = 1;
  int current_buton = 0;
  while (not_pressed==1){
    poll_joystick();
    while (current_buton<joy[(player_array[player]).Player_input.use_joystick-1].num_buttons){
      if (joy[(player_array[player]).Player_input.use_joystick-1].button[current_buton].b){
	(player_array[player]).Player_input.joybuton[player_array[player].Player_input.buton_waited-1]=current_buton;
	not_pressed = 0;
      }
      current_buton++;
      //fprintf(stdout,"current button = %i, player = %i joystick= %i\n",current_buton,player,player_array[player].Player_input.use_joystick-1);
    }
    //fprintf(stdout,"One cycle through\n");
    current_buton = 0;
  }
  return 0;
}


/** \brief function to know if a player want to move
 * chek for the player input and return 0 if the player do not want to move else 1
 */
int want_move(Player_variables * player_array,int a_player){
  int i;
  for (i=0;i<11;i++){
    if (player_array[a_player].Player_input.state[i]!=0)
      return 1;
    if (key[KEY_ESC])
      return 1;
  }
  return 0;
}

/** \brief function to clear player input state
 * caution : highly dangerous, use only if you have checked that the player has no control (player[i]->has_control == 0)
 */
void clear_input_states(Player_variables * player_array,int a_player){
  int i;
  for (i=0;i<11;i++){
    player_array[a_player].Player_input.state[i]=0;
  }
}
