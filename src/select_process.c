#include <stdio.h>
#include "string.h"

#include "main_process.h"
#include "select_process.h"
#include "background_process.h"
#include "initfiles.h"
#include "loads.h"
#include "sensei_config.h"

#include "global.h"
#include "macros.h"
#include "logger.h"
#include "mp3.h"
#include "sound_fx_manager.h"
#include "allegro.h"

/** \file select_process.c
 * \brief Function to deal with player select_sreen
 */

int select_process_mugen(Game_variables variables, Player_variables * player_array, int time);
int select_bg(Game_variables variables, Player_variables * player_array, int time);
int change_vars(Game_variables variables, Player_variables * player_array, int player);
int make_vs_list(Game_variables variables);
int kof91_make_characters_list(Game_variables variables);
int mugen_make_characters_list(Game_variables variables);
int kof91_make_bgs_list(Game_variables variables);
int mugen_make_bgs_list(Game_variables variables);
// int kof91_load_fightfx(Game_variables variables);

int empty_box(Game_variables variables,int x, int y){
  int player_position;
  player_position = x + y*variables->System.Select_struct.columns;
  if (variables->System.Select_struct.char_list[player_position]==0)
    return 1;
  return 0;
}

BITMAP * make_faces_screen(Game_variables variables, Player_variables * player_array){
  int error,i,j,xposition,yposition;
  int current_char_index; // index of char in the list
  int current_char;
  int xaxis = 0;
  int yaxis = 0;
  int portraitw,portraith; // To calculate portrait heigh and width before stretching it
  char * message;
  BITMAP * a_sprite = NULL; // for emptybox sprite
  BITMAP * buffer = NULL;
  BITMAP * faces; // Where the faces_select_screen will be build
  error = 0;
  message = (char*)malloc(255*sizeof(char));
  TRON("Begin make faces");
  faces = create_bitmap(virtscreen->w,virtscreen->h);
  clear_to_color(faces,makecol(255,0,255));
  
  a_sprite = sensei_fill_bmp(variables->System.Select_struct.select_sff,variables->System.Select_struct.cellbgsprg,variables->System.Select_struct.cellbgspri,1,&xaxis,&yaxis);
  /**
   * putting the boxes and chars faces
   */
  current_char_index = 0;
  yposition = variables->System.Select_struct.posy;
  for (i=0;i<variables->System.Select_struct.rows;i++){
    xposition = variables->System.Select_struct.posx;
    TRON("Looping rows");
    for (j=0;j<variables->System.Select_struct.columns;j++){
      TRON("Looping columns");
      a_sprite = sensei_fill_bmp(variables->System.Select_struct.select_sff,variables->System.Select_struct.cellbgsprg,variables->System.Select_struct.cellbgspri,1,&xaxis,&yaxis); // fill a_sprite with empty_box sprite
      if (variables->System.Select_struct.char_list[current_char_index]==0){ // No character in the box
	TRON("No char in the box");
	if (variables->System.Select_struct.showemptyboxes){
	  draw_sprite(faces,a_sprite,xposition,yposition);
	}
      }else{
	draw_sprite(faces,a_sprite,xposition,yposition);
	// Draw portrait
	current_char = (variables->System.Select_struct.char_list[current_char_index]);
	sprintf(message,"current_char = %i",current_char);
	TRON(message);
	if (current_char!=-1){
	  if (current_char!=0)
	    current_char--;
	  switch (variables->System.Select_struct.char_ref_array[current_char].type){
	  case 0 :
	    // Putting No face
	    TRON("No face to show");
	    break;
	  case 1:
	    TRON("KOF 91 face");
	    // Putting KOF 91 portrait
	    portraitw = (int)(variables->System.Select_struct.char_ref_array[current_char].s_pic->w * variables->System.Select_struct.portraitscalex);
	    portraith = (int)(variables->System.Select_struct.char_ref_array[current_char].s_pic->h * variables->System.Select_struct.portraitscaley);
	    a_sprite = create_bitmap_ex(bitmap_color_depth(variables->System.Select_struct.char_ref_array[current_char].s_pic),portraitw,portraith);
	    select_palette(variables->System.Select_struct.char_ref_array[current_char].s_pic_pal);
	    set_color_conversion(COLORCONV_NONE);
	    stretch_blit(variables->System.Select_struct.char_ref_array[current_char].s_pic,a_sprite,0,0,variables->System.Select_struct.char_ref_array[current_char].s_pic->w,variables->System.Select_struct.char_ref_array[current_char].s_pic->h,0,0,portraitw,portraith);
	    buffer = create_bitmap(a_sprite->w,a_sprite->h);
	    blit(a_sprite,buffer,0,0,0,0,a_sprite->w,a_sprite->h);
	    draw_sprite(faces,buffer,xposition + variables->System.Select_struct.portraitoffsetx, yposition + variables->System.Select_struct.portraitoffsety);
	    unselect_palette();
	    destroy_bitmap(buffer);
	    break;
	  case 2:
	    // Putting Mugen's face
	    TRON("Mugen's face");
	    // Putting KOF 91 portrait
	    portraitw = (int)(variables->System.Select_struct.char_ref_array[current_char].s_pic->w * variables->System.Select_struct.portraitscalex);
	    portraith = (int)(variables->System.Select_struct.char_ref_array[current_char].s_pic->h * variables->System.Select_struct.portraitscaley);
	    a_sprite = create_bitmap_ex(bitmap_color_depth(variables->System.Select_struct.char_ref_array[current_char].s_pic),portraitw,portraith);
	    select_palette(variables->System.Select_struct.char_ref_array[current_char].s_pic_pal);
	    set_color_conversion(COLORCONV_NONE);
	    stretch_blit(variables->System.Select_struct.char_ref_array[current_char].s_pic,a_sprite,0,0,variables->System.Select_struct.char_ref_array[current_char].s_pic->w,variables->System.Select_struct.char_ref_array[current_char].s_pic->h,0,0,portraitw,portraith);
	    buffer = create_bitmap(a_sprite->w,a_sprite->h);
	    blit(a_sprite,buffer,0,0,0,0,a_sprite->w,a_sprite->h);
	    draw_sprite(faces,buffer,xposition + variables->System.Select_struct.portraitoffsetx, yposition + variables->System.Select_struct.portraitoffsety);
	    unselect_palette();
	    destroy_bitmap(buffer);
	    break;
	  default:
	    TRON("strange face to show");
	    break;
	  }
	}else{
	  // Put random char sprite
	}
      }
      current_char_index++;
      xposition = xposition + variables->System.Select_struct.cellsizex + variables->System.Select_struct.cellspacing;
    }
    yposition = yposition + variables->System.Select_struct.cellsizey + variables->System.Select_struct.cellspacing;
  }
  destroy_bitmap(a_sprite);
  
  free(message);
  return faces;
}// make_faces_screen

int make_lists(Game_variables variables, Player_variables * player_array){
  switch (variables->System.Select_struct.type){
  case 0: // KOF 91 Select screen loading
    kof91_make_characters_list(variables);
    kof91_make_bgs_list(variables);
    variables->System.Select_struct.loaded = 1;
    break;
  case 1: // Mugen's select screen loading
    if (SENSEI_DEBUG_ON)
      TRON("Select_process before loading sff");
    variables->System.Select_struct.select_sff =  sffLoad(variables->System.Select_struct.sff_path);
    if (SENSEI_DEBUG_ON)
      TRON("Select process after loading sff");
    mugen_make_characters_list(variables);
    mugen_make_bgs_list(variables);
    variables->System.Select_struct.loaded = 1;
    break;
  default:
    TRON("strange select.type found");
    break;
  }
  return 0;
}// Make lists

/**   \brief function to select a character (and game mode in team mode) on select screen_ character
 */
int select_process(Game_variables variables, Player_variables * player_array, int time){
  int i;
  char * message;
  message = (char*)calloc(255,sizeof(char));
  if ((variables->System.Select_struct.loaded==0)){
    make_lists(variables,player_array);
    if (variables->System.Select_struct.type==1)
      variables->System.Select_struct.faces = make_faces_screen(variables,player_array);
    variables->System.Select_struct.loaded = 1;
  }
  
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
  
  play_music(&variables->System.select_music);
  
  if (variables->f_keys.Esc==1) {
    variables->f_keys.Esc=0;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.OCancelgrp, variables->System.OCancelnb, 255, 128);
    else
      Buzz();
    variables->System.Ocurrentitem = 0;
    next_state(variables);
    player_array[0].has_control=0;
    player_array[1].has_control=0;
    rest(1);
    variables->not_show =1;
    player_array[0].computer_input = 0;
    player_array[1].computer_input = 0;
    stop_music(&variables->System.select_music);
  }
  
  /*
    Background management
  */
  background_process(&variables->System.Select_bg);
  
  // misc : no team mode config now
  if (variables->System.Select_struct.state == 0)
    variables->System.Select_struct.state = 1;
  
  switch (variables->System.Select_struct.state){
  case 0:
    // function to deal with team config
    break;
  case 1:
     // function to deal with Select screen cursor moving and select
    select_process_mugen(variables,player_array,time);
    break;
  case 2:
    // function to deal with Stage select
    select_process_mugen(variables,player_array,time);
    select_bg(variables,player_array,time);
    break;
  case 3:
    // function to exit from Select process
    stop_music(&variables->System.select_music);
    player_array[0].has_control = 0;
    player_array[1].has_control = 0;
    variables->Game_state = 7;
    variables->not_show = 1;
    break;
  default:
    TRON("strange select.state in select_process");
    break;
  }
  return 0;
}// end of select_process

int select_process_mugen(Game_variables variables, Player_variables * player_array, int time){
  int player;
  int char_ref;
  int char_index;
  TRON("select_process_mugen");
  
  /*
   * move char selection cursor on select screen
   */
  if (variables->System.Select_struct.p1_controller != 0){ // if a player control p1 cursor
    TRON("p1 controller");
    player = variables->System.Select_struct.p1_controller-1;
    if (player_array[player].Player_input.state[0]){
      variables->System.Select_struct.p1_position.y--;
      if (variables->System.Select_struct.p1_position.y<0){
	if (variables->System.Select_struct.wrapping){
	  variables->System.Select_struct.p1_position.y = variables->System.Select_struct.rows - 1;
	  if ((empty_box(variables,variables->System.Select_struct.p1_position.x,variables->System.Select_struct.p1_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	    variables->System.Select_struct.p1_position.y = 0;
	  else
	    if (variables->System.Sndexist)
	      sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p1movesndg, variables->System.Select_struct.p1movesndi, 255, 128);
	    else
	      Bing();
	}
	else
	  variables->System.Select_struct.p1_position.y = 0;
      }else{
	if ((empty_box(variables,variables->System.Select_struct.p1_position.x,variables->System.Select_struct.p1_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	  variables->System.Select_struct.p1_position.y++;
	else
	  if (variables->System.Sndexist)
	    sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p1movesndg, variables->System.Select_struct.p1movesndi, 255, 128);
	  else
	    Bing();
      }
    }
    
    if (player_array[player].Player_input.state[1]){
      variables->System.Select_struct.p1_position.y++;
      if (variables->System.Select_struct.p1_position.y >= variables->System.Select_struct.rows ){
	if (variables->System.Select_struct.wrapping){
	  variables->System.Select_struct.p1_position.y = 0;
	  if ((empty_box(variables,variables->System.Select_struct.p1_position.x,variables->System.Select_struct.p1_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	    variables->System.Select_struct.p1_position.y = variables->System.Select_struct.rows - 1;
	  else
	    if (variables->System.Sndexist)
	      sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p1movesndg, variables->System.Select_struct.p1movesndi, 255, 128);
	    else
	      Bing();
	}
	else
	  variables->System.Select_struct.p1_position.y = variables->System.Select_struct.rows - 1;
      }else{
	if ((empty_box(variables,variables->System.Select_struct.p1_position.x,variables->System.Select_struct.p1_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	  variables->System.Select_struct.p1_position.y--;
	else
	  if (variables->System.Sndexist)
	    sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p1movesndg, variables->System.Select_struct.p1movesndi, 255, 128);
	  else
	    Bing();
      }
    }
    
    if (player_array[player].Player_input.state[2]){
      variables->System.Select_struct.p1_position.x--;
      if (variables->System.Select_struct.p1_position.x < 0){
	if (variables->System.Select_struct.wrapping){
	  variables->System.Select_struct.p1_position.x = variables->System.Select_struct.columns - 1;
	  if ((empty_box(variables,variables->System.Select_struct.p1_position.x,variables->System.Select_struct.p1_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	    variables->System.Select_struct.p1_position.x = 0;
	  else
	    if (variables->System.Sndexist)
	      sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p1movesndg, variables->System.Select_struct.p1movesndi, 255, 128);
	    else
	      Bing();
	}else{
	  variables->System.Select_struct.p1_position.x = 0;
	}
      }else{
	if ((empty_box(variables,variables->System.Select_struct.p1_position.x,variables->System.Select_struct.p1_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	  variables->System.Select_struct.p1_position.x++;
	else
	  if (variables->System.Sndexist)
	    sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p1movesndg, variables->System.Select_struct.p1movesndi, 255, 128);
	  else
	    Bing();
      }
    }
    
    if (player_array[player].Player_input.state[3]){
      variables->System.Select_struct.p1_position.x++;
      // TRON("p1_position.x++");
      if (variables->System.Select_struct.p1_position.x >= variables->System.Select_struct.columns){
	// TRON("x>=columns");
	if (variables->System.Select_struct.wrapping){
	  variables->System.Select_struct.p1_position.x = 0;
	  if ((empty_box(variables,variables->System.Select_struct.p1_position.x,variables->System.Select_struct.p1_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	    variables->System.Select_struct.p1_position.x = variables->System.Select_struct.columns - 1;
	  else
	    if (variables->System.Sndexist)
	      sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p1movesndg, variables->System.Select_struct.p1movesndi, 255, 128);
	      else
		Bing();
	}else{
	  variables->System.Select_struct.p1_position.x = variables->System.Select_struct.columns -1;
	}
      }else{
	// TRON("before empty_box");
	if ((empty_box(variables,variables->System.Select_struct.p1_position.x,variables->System.Select_struct.p1_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	  variables->System.Select_struct.p1_position.x--;
	else
	  if (variables->System.Sndexist)
	    sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p1movesndg, variables->System.Select_struct.p1movesndi, 255, 128);
	  else
	    Bing();
      }
    }
    
    // Testing players validations
    char_ref = variables->System.Select_struct.p1_position.x + variables->System.Select_struct.p1_position.y*variables->System.Select_struct.columns;
    char_index = (variables->System.Select_struct.char_list[char_ref]);
    if ((validation(player_array)==1)&&(char_index!=0)){
      if (char_index!=-1){
	if (variables->System.Select_struct.p1_selecter<variables->System.Select_struct.p1_max_selecter){
	  variables->System.Select_struct.p1_selected[variables->System.Select_struct.p1_selecter] = char_ref;
	  variables->System.Select_struct.p1_selecter++;
	  if (variables->System.Sndexist){
	    sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p1donesndg, variables->System.Select_struct.p1donesndi, 255, 128);
	  }else
	    Done();
	  change_vars(variables,player_array,1);
	}//
      }else{
	TRON("p1 random select");
      }
    }
  }
  
  if (variables->System.Select_struct.p2_controller != 0){ // if a player control p2 cursor
    
    // TRON("p2 controller");
    player = variables->System.Select_struct.p2_controller-1;
    if (player_array[player].Player_input.state[0]){
      variables->System.Select_struct.p2_position.y--;
      if (variables->System.Select_struct.p2_position.y<0){
	if (variables->System.Select_struct.wrapping){
	  variables->System.Select_struct.p2_position.y = variables->System.Select_struct.rows - 1;
	  if ((empty_box(variables,variables->System.Select_struct.p2_position.x,variables->System.Select_struct.p2_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	    variables->System.Select_struct.p2_position.y = 0;
	  else
	    if (variables->System.Sndexist)
	      sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p2movesndg, variables->System.Select_struct.p2movesndi, 255, 128);
	    else
	      Bing();
	}
	else
	  variables->System.Select_struct.p2_position.y = 0;
      }else{
	if ((empty_box(variables,variables->System.Select_struct.p2_position.x,variables->System.Select_struct.p2_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	  variables->System.Select_struct.p2_position.y++;
	else
	  if (variables->System.Sndexist)
	    sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p2movesndg, variables->System.Select_struct.p2movesndi, 255, 128);
	  else
	    Bing();
      }
    }
    
    if (player_array[player].Player_input.state[1]){
      variables->System.Select_struct.p2_position.y++;
      if (variables->System.Select_struct.p2_position.y >= variables->System.Select_struct.rows ){
	if (variables->System.Select_struct.wrapping){
	  variables->System.Select_struct.p2_position.y = 0;
	  if ((empty_box(variables,variables->System.Select_struct.p2_position.x,variables->System.Select_struct.p2_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	    variables->System.Select_struct.p2_position.y = variables->System.Select_struct.rows - 1;
	  else
	    if (variables->System.Sndexist)
	      sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p2movesndg, variables->System.Select_struct.p2movesndi, 255, 128);
	    else
	      Bing();
	}
	else
	  variables->System.Select_struct.p2_position.y = variables->System.Select_struct.rows - 1;
      }else{
	if ((empty_box(variables,variables->System.Select_struct.p2_position.x,variables->System.Select_struct.p2_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	  variables->System.Select_struct.p2_position.y--;
	else
	  if (variables->System.Sndexist)
	    sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p2movesndg, variables->System.Select_struct.p2movesndi, 255, 128);
	  else
	    Bing();
      }
    }
    
    if (player_array[player].Player_input.state[2]){
      variables->System.Select_struct.p2_position.x--;
      if (variables->System.Select_struct.p2_position.x < 0){
	if (variables->System.Select_struct.wrapping){
	  variables->System.Select_struct.p2_position.x = variables->System.Select_struct.columns - 1;
	  if ((empty_box(variables,variables->System.Select_struct.p2_position.x,variables->System.Select_struct.p2_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	    variables->System.Select_struct.p2_position.x = 0;
	  else
	    if (variables->System.Sndexist)
	      sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p2movesndg, variables->System.Select_struct.p2movesndi, 255, 128);
	    else
	      Bing();
	}else{
	  variables->System.Select_struct.p2_position.x = 0;
	}
      }else{
	if ((empty_box(variables,variables->System.Select_struct.p2_position.x,variables->System.Select_struct.p2_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	  variables->System.Select_struct.p2_position.x++;
	else
	  if (variables->System.Sndexist)
	    sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p2movesndg, variables->System.Select_struct.p2movesndi, 255, 128);
	  else
	    Bing();
      }
    }
    
    if (player_array[player].Player_input.state[3]){
      variables->System.Select_struct.p2_position.x++;
      // TRON("p2_position.x++");
      if (variables->System.Select_struct.p2_position.x >= variables->System.Select_struct.columns){
	// TRON("x>=columns");
	if (variables->System.Select_struct.wrapping){
	  variables->System.Select_struct.p2_position.x = 0;
	  if ((empty_box(variables,variables->System.Select_struct.p2_position.x,variables->System.Select_struct.p2_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	    variables->System.Select_struct.p2_position.x = variables->System.Select_struct.columns - 1;
	  else
	    if (variables->System.Sndexist)
	      sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p2movesndg, variables->System.Select_struct.p2movesndi, 255, 128);
	      else
		Bing();
	}else{
	  variables->System.Select_struct.p2_position.x = variables->System.Select_struct.columns -1;
	}
      }else{
	// TRON("before empty_box");
	if ((empty_box(variables,variables->System.Select_struct.p2_position.x,variables->System.Select_struct.p2_position.y))&&(variables->System.Select_struct.moveoveremptyboxes==0))
	  variables->System.Select_struct.p2_position.x--;
	else
	  if (variables->System.Sndexist)
	    sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p2movesndg, variables->System.Select_struct.p2movesndi, 255, 128);
	  else
	    Bing();
      }
    }
    
    // Testing players validations
    char_ref = variables->System.Select_struct.p2_position.x + variables->System.Select_struct.p2_position.y*variables->System.Select_struct.columns;
    char_index = (variables->System.Select_struct.char_list[char_ref]);
    if ((validation(player_array)==2)&&(char_index!=0)){
      if (char_index!=-1){
	if (variables->System.Select_struct.p2_selecter<variables->System.Select_struct.p2_max_selecter){
	  variables->System.Select_struct.p2_selected[variables->System.Select_struct.p2_selecter] = char_ref;
	  variables->System.Select_struct.p2_selecter++;
	  if (variables->System.Sndexist){
	    sndPlay(variables->System.Systemsnd, variables->System.Select_struct.p2donesndg, variables->System.Select_struct.p2donesndi, 255, 128);
	  }else
	    Done();
	  change_vars(variables,player_array,2);
	}//
      }else{
	TRON("p2 random select");
      }
    }
    
  }
  // end of character selection
  
  TRON("end of select process mugen");
  return 0;
}// end of select_process_mugen

/** Function to deal with stage selection and player choice (IA part)
 */
int select_bg(Game_variables variables, Player_variables * player_array, int time){
  int player;
  player = variables->System.Select_struct.stage_controller-1;
  if ((gmode==0)||(gmode==2)||(gmode==4)||(gmode==5)||(gmode==6)){
    if (variables->System.Select_struct.p1_controller!=0)
      variables->System.Select_struct.p2_selected[0] = make_vs_list(variables); 
    else
      variables->System.Select_struct.p1_selected[0] = make_vs_list(variables);
    variables->System.Select_struct.state = 3;
    return 0;
  }
  
  if (validation(player_array)==(player+1)){
    variables->System.Select_struct.bg_selected = 1;
    if (variables->System.Sndexist){
      sndPlay(variables->System.Systemsnd, variables->System.Select_struct.stagedonesndg, variables->System.Select_struct.stagedonesndi, 255, 128);
    }else
      Done();
    variables->System.Select_struct.stage_controller = 0;
  }
  
  if (variables->System.Select_struct.bg_selected == 0){
    variables->System.Select_struct.bg_blinked++;
    if (variables->System.Select_struct.bg_blinked>5)
      variables->System.Select_struct.bg_blinked = 0;
    if (player_array[player].Player_input.state[2]){
      variables->System.Select_struct.current_bg--;
      if (variables->System.Sndexist){
	sndPlay(variables->System.Systemsnd, variables->System.Select_struct.stagemovesndg, variables->System.Select_struct.stagemovesndi, 255, 128);
      }else
	Bing();
      if (variables->System.Select_struct.current_bg<0)
	variables->System.Select_struct.current_bg=variables->System.Select_struct.nb_bg-1;
    }
    if (player_array[player].Player_input.state[3]){
      variables->System.Select_struct.current_bg++;
      if (variables->System.Sndexist){
	sndPlay(variables->System.Systemsnd, variables->System.Select_struct.stagemovesndg, variables->System.Select_struct.stagemovesndi, 255, 128);
      }else
	Bing();
      if (variables->System.Select_struct.current_bg>=variables->System.Select_struct.nb_bg)
	variables->System.Select_struct.current_bg=0;
    }
  }
  
  // Testing if all is done (stage selected and nobody controlle a character)
  if ((variables->System.Select_struct.bg_selected==1)&&(variables->System.Select_struct.p1_controller==0)&&(variables->System.Select_struct.p2_controller==0))
    variables->System.Select_struct.state = 3;

  return 0;
} // end of bg process

/** \brief Function to change select variables (such as player_controller) after a selection is done
    
 */
int change_vars(Game_variables variables, Player_variables * player_array, int player){
  switch (gmode){
  case 0: // arcade mode
    variables->System.Select_struct.state = 2;
    break;
  case 1: // vs mode
    if ((player==1)&&(variables->System.Select_struct.stage_controller==0)){
      variables->System.Select_struct.stage_controller = 1;
      variables->System.Select_struct.p1_controller = 0;
      variables->System.Select_struct.state = 2;
    }
    if ((player==2)&&(variables->System.Select_struct.stage_controller==0)){
      variables->System.Select_struct.stage_controller = 2;
      variables->System.Select_struct.p2_controller = 0;
      variables->System.Select_struct.state = 2;
    }
    break;
  case 2: // Team mode
    if (player==1){
      if (variables->System.Select_struct.p1_selecter>=variables->System.Select_struct.p1_max_selecter){
	variables->System.Select_struct.p1_controller = 0;
	if (variables->System.Select_struct.stage_controller==0){
	  variables->System.Select_struct.stage_controller=1;
	  variables->System.Select_struct.state = 2;
	}
      }
    }
    if (player==2){
      if (variables->System.Select_struct.p2_selecter>=variables->System.Select_struct.p2_max_selecter){
	variables->System.Select_struct.p2_controller = 0;
	if (variables->System.Select_struct.stage_controller==0){
	  variables->System.Select_struct.stage_controller=2;
	  variables->System.Select_struct.state = 2;
	}
      }
    }
    break;
  case 3 : // Team VS
      if (player==1){
      if (variables->System.Select_struct.p1_selecter>=variables->System.Select_struct.p1_max_selecter){
	variables->System.Select_struct.p1_controller = 0;
	if (variables->System.Select_struct.stage_controller==0){
	  variables->System.Select_struct.stage_controller=1;
	  variables->System.Select_struct.state = 2;
	}
      }
    }
    if (player==2){
      if (variables->System.Select_struct.p2_selecter>=variables->System.Select_struct.p2_max_selecter){
	variables->System.Select_struct.p2_controller = 0;
	if (variables->System.Select_struct.stage_controller==0){
	  variables->System.Select_struct.stage_controller=2;
	  variables->System.Select_struct.state = 2;
	}
      }
    }
    break;
  case 4 : // Team coop
    if ((player==1)&&(variables->System.Select_struct.stage_controller==0)){
      variables->System.Select_struct.stage_controller = 1;
      variables->System.Select_struct.p1_controller = 0;
      variables->System.Select_struct.state = 2;
    }
    if ((player==2)&&(variables->System.Select_struct.stage_controller==0)){
      variables->System.Select_struct.stage_controller = 2;
      variables->System.Select_struct.p2_controller = 0;
      variables->System.Select_struct.state = 2;
    }
    break;
  case 5 : // Survival
    variables->System.Select_struct.state = 2;
    break;
  case 6 : // Survival coop
     if ((player==1)&&(variables->System.Select_struct.stage_controller==0)){
      variables->System.Select_struct.stage_controller = 1;
      variables->System.Select_struct.p1_controller = 0;
      variables->System.Select_struct.state = 2;
    }
    if ((player==2)&&(variables->System.Select_struct.stage_controller==0)){
      variables->System.Select_struct.stage_controller = 2;
      variables->System.Select_struct.p2_controller = 0;
      variables->System.Select_struct.state = 2;
    }
    break;
  case 7 : // Training
    if (player==1){
      if (variables->System.Select_struct.p2_selecter>=variables->System.Select_struct.p2_max_selecter){
	variables->System.Select_struct.p1_controller = 0;
	variables->System.Select_struct.stage_controller = 1;
	variables->System.Select_struct.state = 2;
      }else{
	variables->System.Select_struct.p2_controller = 1;
	variables->System.Select_struct.p1_controller = 0;
      }
    }
    if (player==2){
      if (variables->System.Select_struct.p1_selecter>=variables->System.Select_struct.p1_max_selecter){
	variables->System.Select_struct.p2_controller = 0;
	variables->System.Select_struct.stage_controller = 1;
	variables->System.Select_struct.state = 2;
      }else{
	variables->System.Select_struct.p1_controller = 1;
	variables->System.Select_struct.p2_controller = 0;
      }
    }
    break; 
  case 8 : // Watch
     if (player==1){
      if (variables->System.Select_struct.p2_selecter>=variables->System.Select_struct.p2_max_selecter){
	variables->System.Select_struct.p1_controller = 0;
	variables->System.Select_struct.stage_controller = 1;
	variables->System.Select_struct.state = 2;
      }else{
	variables->System.Select_struct.p2_controller = 1;
	variables->System.Select_struct.p1_controller = 0;
      }
    }
    if (player==2){
      if (variables->System.Select_struct.p1_selecter>=variables->System.Select_struct.p1_max_selecter){
	variables->System.Select_struct.p2_controller = 0;
	variables->System.Select_struct.stage_controller = 1;
	variables->System.Select_struct.state = 2;
      }else{
	variables->System.Select_struct.p1_controller = 1;
	variables->System.Select_struct.p2_controller = 0;
      }
    }
    break;
  default :
    break;
  }
  return 0;
} // Change vars

/** \brief Function that build the list of opponents with char_list and system_vars return the first opponent (in char_list)
*/
int make_vs_list(Game_variables variables){
  int ok = 0;
  int number = 0;
  while (!ok){
    number = (int)((float)variables->System.Select_struct.s_nb_char*rand()/RAND_MAX);
    if (variables->System.Select_struct.char_list[number]!=0)
      ok = 1;
  }
  return number;
} // make_vs_list

/** \brief fill the KOF 91 chars list and load the portraits and small pics
 */
int kof91_make_characters_list(Game_variables variables){
  char ** kof91_chars;
  int nb = 0;
  char * path;
  char * file_path;
  kof91_chars = sensei_list_files(&nb,"sprites","");
  variables->System.Select_struct.char_ref_array = (char_ref_struct*)calloc(nb,sizeof(char_ref_struct));
  variables->System.Select_struct.nb_char = nb;
  for (i=0;i<nb;i++){
    variables->System.Select_struct.char_ref_array[i].display_name = strcpy((char*)calloc(255,sizeof(char)),kof91_chars[i]);
    path = strcpy((char*)calloc(255,sizeof(char)),"sprites");
    put_backslash(path);
    path = strcat(path,kof91_chars[i]);
    put_backslash(path);
    file_path = strcpy((char*)calloc(100,sizeof(char)),path);
    file_path = strcat(file_path,"char.ini");
    if (exists(file_path))
      variables->System.Select_struct.char_ref_array[i].type = 1;
    else
      variables->System.Select_struct.char_ref_array[i].type = 0;
    file_path = strcpy((char*)calloc(100,sizeof(char)),path);
    file_path = strcat(file_path,"selsmall.pcx");
    variables->System.Select_struct.char_ref_array[i].s_pic = xload_pcx(file_path,variables->System.Select_struct.char_ref_array[i].s_pic_pal);
    file_path = strcpy((char*)calloc(100,sizeof(char)),path);
    file_path = strcat(file_path,"selbig.pcx");
    variables->System.Select_struct.char_ref_array[i].b_pic = xload_pcx(file_path,variables->System.Select_struct.char_ref_array[i].b_pic_pal);
  }
  variables->System.Select_struct.columns = nb;
  variables->System.Select_struct.rows = 1;
  variables->System.Select_struct.wrapping = 1;
  variables->System.Select_struct.moveoveremptyboxes = 1;
  // variables->System.Select_struct.char_list = (int*)calloc(variables->System.Select_struct.nb_char,sizeof(int));
  for (i=0;i<nb;i++){
    variables->System.Select_struct.char_list[i] = i+1;
  }
  variables->System.Select_struct.loaded = 1;
  // Filling selected chars with -1 to avoid the 0 char list = 0 selected bug
  for (i=0;i<4;i++){
    variables->System.Select_struct.p1_selected[i]=-1;
    variables->System.Select_struct.p2_selected[i]=-1;
  }
  return 0;
}// kof91_make_characters_list

int kof91_make_bgs_list(Game_variables variables){
  char ** kof91_pcx_bgs;
  char ** kof91_flc_bgs;
  int nb;
  int nb_bg;
  kof91_pcx_bgs = sensei_list_files(&nb,"bkgds","pcx");
  kof91_flc_bgs = sensei_list_files(&nb_bg,"bkgds","flc");
  variables->System.Select_struct.bg_ref_array = (bg_ref_struct*)calloc(nb+nb_bg,sizeof(bg_ref_struct));
  variables->System.Select_struct.nb_bg = nb+nb_bg;
  for (i=0;i<nb;i++){
    variables->System.Select_struct.bg_ref_array[i].path = strcpy((char*)calloc(255,sizeof(char)),kof91_pcx_bgs[i]);
    variables->System.Select_struct.bg_ref_array[i].display_name = strcpy((char*)calloc(255,sizeof(char)),kof91_pcx_bgs[i]);
  }
  for (i=0;i<nb_bg;i++){
    variables->System.Select_struct.bg_ref_array[nb+i].path = strcpy((char*)calloc(255,sizeof(char)),kof91_flc_bgs[i]);
    variables->System.Select_struct.bg_ref_array[nb+i].display_name = strcpy((char*)calloc(255,sizeof(char)),kof91_flc_bgs[i]);
  }
  return 0;
} // kof91_make_bgs_list

int mugen_make_characters_list(Game_variables variables){
  int error = 0;
  sensei_set_config_file(variables->System.select_path);
  sensei_fill_characters_list(variables);
  for (i=0;i<4;i++){
    variables->System.Select_struct.p1_selected[i]=-1;
    variables->System.Select_struct.p2_selected[i]=-1;
  }
  return error;
}//mugen_make_characters_list

int mugen_make_bgs_list(Game_variables variables){
  int error = 0;
  sensei_set_config_file(variables->System.select_path);
  sensei_fill_bgs_list(variables);
  return error;
}

