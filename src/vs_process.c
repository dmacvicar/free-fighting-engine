#include "main_process.h"
#include "vs_process.h"
#include "string.h"
#include <stdio.h>

#include "sound_fx_manager.h"
#include "mp3.h"
#include "macros.h"
#include "logger.h"
#include "background_process.h"
#include "load_characters.h"
#include "global.h"
#include "loads.h"
#include "sensei_config.h"

/** \file vs_process.c
 * \brief Functions to deal with vs_screen and to load chars sprite
 */

int fill_character(Game_variables variables, Player_variables * player_array, int player);
int fill_bg(Game_variables variables);
char check_kstatus1 ( char ctrl_key );
char check_kstatus2 ( char ctrl_key );
char get_kstatus ( char strg[] );
int kof91_initfight_vars(Game_variables variables);
int kof91_load_fightfx(Game_variables variables);

/** \brief Function to play music at vs screen, process vs BG and then fill characters and bgs
 */
int vs_process(Game_variables variables, Player_variables * player_array, int time){
  char * message;
  int i;
  message = (char*)calloc(255,sizeof(char));
  
  
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
  
  play_music(&variables->System.vs_music);
  
  if (variables->f_keys.Esc==1) {
    variables->f_keys.Esc=0;
    if (variables->System.Sndexist)
      sndPlay(variables->System.Systemsnd, variables->System.OCancelgrp, variables->System.OCancelnb, 255, 128);
    else
      Buzz();
    rest(1);
    variables->System.Ocurrentitem = 0;
    next_state(variables);
    variables->not_show =1;
    stop_music(&variables->System.vs_music);
  }
  
  /*
    Background management
  */
  background_process(&variables->System.Vs_bg);

  if (variables->System.Vs_struct.state>=1){
    for (i=0;i<5;i++){
      sprintf(message,"Filling player %i",i);
      TRON(message);
      fill_character(variables,player_array,i);
      sprintf(message,"Loading player %i  ",i);
      TRON(message);
      load_character(player_array,i);
    }
    TRON("Filling BG");
    fill_bg(variables);
    
    kof91_initfight_vars(variables);
    kof91_load_fightfx(variables);
    stop_music(&variables->System.vs_music);
    variables->battle.fixed_players = 0;
    variables->Game_state = 9;
  }

  variables->System.Vs_struct.currenttime++;
  if (variables->System.Vs_struct.currenttime>(variables->System.Vs_struct.time-2)){
    variables->System.Vs_struct.state = 1;
  }
  
  if (validation(player_array))
    variables->System.Vs_struct.state = 1;
     
  free(message);
  return 0;
} // Vs process

/** \brief function to fill player arrays with vars taken from select struct
 */
int fill_character(Game_variables variables, Player_variables * player_array, int player){
  int p1 = 0;  
  int p1_ref = 0;
  char * message;
  char * buffer;
  char * result;
  int error = 0;
  
  message = (char*)calloc(255,sizeof(char));
  buffer = (char*)calloc(255,sizeof(char));
  result = (char*)calloc(255,sizeof(char));
  
  // Testing if there's need to fill the player
  if (player<3){
    // Filling p1 team
    if (player+1>variables->System.Select_struct.p1_max_selecter){
      player_array[player].type = 0;
      return 0;
    }
  }else{
    if (player-2>variables->System.Select_struct.p2_max_selecter){
      player_array[player].type = 0;
      return 0;
    }
  }
  if (player<3){
    p1 = variables->System.Select_struct.p1_selected[player];
    p1_ref = variables->System.Select_struct.char_list[p1];
    p1_ref--;
  }else{
    p1 = variables->System.Select_struct.p2_selected[player-3];
    p1_ref = variables->System.Select_struct.char_list[p1];
    p1_ref--;
  }
  switch (variables->System.Select_struct.char_ref_array[p1_ref].type){
  case 0: // no char
    player_array[player].type = 0;
    break;
  case 1: // KOF 91 char
    if (SENSEI_DEBUG_ON)
      TRON("filling kof 91 char");
    player_array[player].type = 1;
    player_array[player].name = strcpy((char*)calloc(255,sizeof(char)),variables->System.Select_struct.char_ref_array[p1_ref].display_name);
    player_array[player].display_name = strcpy((char*)calloc(255,sizeof(char)),variables->System.Select_struct.char_ref_array[p1_ref].display_name);
    player_array[player].def_path = strcpy((char*)calloc(255,sizeof(char)),variables->System.Select_struct.char_ref_array[p1_ref].path);
    break;
  case 2: // Mugen's char
    if (SENSEI_DEBUG_ON)
      TRON("filling mugen char");
    player_array[player].type = 2;
    player_array[player].display_name = strcpy((char*)calloc(255,sizeof(char)),variables->System.Select_struct.char_ref_array[p1_ref].display_name);
    player_array[player].name = strcpy((char*)calloc(255,sizeof(char)),variables->System.Select_struct.char_ref_array[p1_ref].name);
    player_array[player].def_path = strcpy((char*)calloc(255,sizeof(char)),variables->System.Select_struct.char_ref_array[p1_ref].path);
    TRON(player_array[player].def_path);
    // Buffer will store relative char path (ex chars/kfm/ for chars/kfm/kfm.def )
    set_config_file(player_array[player].def_path);
    buffer = extract_path(player_array[player].def_path);
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","cmd",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player cmd file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing cmd file");
      return -1;
    }else{
      player_array[player].cmd_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","cns",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player cns file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing cns file");
      return -1;
    }else{
      player_array[player].cns_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","st",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player st file",&error));
    if (error!=0){
      player_array[player].st_path = strcpy((char*)calloc(1,sizeof(char)),"");
    }else{
      player_array[player].st_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","stcommon",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player stcommon file",&error));
    if (error!=0){
      result = strcpy((char*)calloc(255,sizeof(char)),check_path("data","common1.cns","player stcommon file",&error));
      if (error!=0){
	TRON("really no common1.cns");
      }
    }else{
      player_array[player].stcommon_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","sprite",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player sprite file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing sprite file");
      return -1;
    }else{
      player_array[player].sprite_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }

    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","anim",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player anim file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing anim file");
      return -1;
    }else{
      player_array[player].anim_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }

    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","sound",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player sound file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing sound file");
      return -1;
    }else{
      player_array[player].sound_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }

    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","pal1",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player pal1 file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing pal1 file");
    }else{
      player_array[player].pal1_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","pal2",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player pal2 file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing pal2 file");
    }else{
      player_array[player].pal2_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","pal3",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player pal3 file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing pal3 file");
      return -1;
    }else{
      player_array[player].pal3_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }

    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","pal4",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player pal4 file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing pal4 file");
    }else{
      player_array[player].pal4_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","pal5",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player pal5 file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing pal5 file");
    }else{
      player_array[player].pal5_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }

    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","pal6",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player pal6 file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing pal6 file");
    }else{
      player_array[player].pal6_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","pal7",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player pal7 file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing pal7 file");
    }else{
      player_array[player].pal7_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","pal8",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player pal8 file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing pal8 file");
    }else{
      player_array[player].pal8_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","pal9",""));
    result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player pal9 file",&error));
    if (error!=0){
      if (SENSEI_DEBUG_ON)
	TRON("missing pal9 file");
    }else{
      player_array[player].pal9_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }

    if (strlen(player_array[player].pal1_path)>3)
      player_array[player].pal = load_act_pal(player_array[player].pal1_path);
    else{
      if (SENSEI_DEBUG_ON)
	TRON("Missing pal for player");
      player_array[player].pal = default_palette;
    }
    
    break;
  default:
    player_array[player].type = 0;
    break;
  }
  
  free(result);
  free(message);
  free(buffer);
  return 0;
}// fill_characters

int fill_bg(Game_variables variables){
    int error = 0;
    if (SENSEI_DEBUG_ON)
      TRON("Filling BG");
  switch (variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].type){
  case 1:
    TRON("Vs filling bg kof91");
    variables->Fight_bg.type = 1;
    variables->Fight_bg.bg_path = strcpy((char*)calloc(255,sizeof(char)),"bkgds");
    put_backslash(variables->Fight_bg.bg_path);
    variables->Fight_bg.bg_path = strcat(variables->Fight_bg.bg_path,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
    break;
  case 3:
    TRON("Vs filling bg mugen");
    variables->Fight_bg.type = 3;
    variables->Fight_bg.bg_path = strcpy((char*)calloc(255,sizeof(char)),variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].path);
    variables->Fight_bg.name = strcpy((char*)calloc(255,sizeof(char)),variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
    set_config_file(variables->Fight_bg.bg_path);
    variables->Fight_bg.bg_sff_path = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Bgdef","spr",""));
    variables->Fight_bg.bg_sff_path = remove_comments(variables->Fight_bg.bg_sff_path);
    variables->Fight_bg.bg_sff_path = remove_end_spaces(variables->Fight_bg.bg_sff_path);
    variables->Fight_bg.bg_sff_path = strcpy((char*)calloc(255,sizeof(char)),check_path(variables->Fight_bg.bg_sff_path,"stages","bg sprite sff",&error));
    if (exists(variables->Fight_bg.bg_sff_path))
      variables->Fight_bg.bg_sff_path_known = 1;
    else
      variables->Fight_bg.bg_sff_path_known = 0;
    /**
       little hack for compatibility with standards bgs
     */
    variables->Fight_bg.name = strcpy((char*)calloc(25,sizeof(char)),"bg");
    break;
  default:
    TRON("Strange bg type in fill_bg");
    break;
  }
  return 0;
} // Fill bg

int  kof91_initfight_vars(Game_variables variables){
  sel1 = 1;
  cx = 1;
  sel2 = 1;
  cy = 1;
  oldsel1 = 2;
  oldsel2 = 2;
  flag = 0;
  flag2 = 0;
  sens1 = 0;
  sens2 = 0;
  frameskip = 0;
  vic1 = vic2 = 0;
  actual = 0;
  actual2 = 0;
  last_char = 0;
  ak = ak2 = 0;
  apch = apch2 = 0;
  limak = limak2 = 1;
  limp1 = 1;
  limp2 = 1;
  clone = (variables->System.Select_struct.p1_selected[0] == variables->System.Select_struct.p2_selected[0] );

  sol2 = (zoomsup + 225) - p2.height;
  jump_how2 = (zoomsup + 125) - p2.height;
  sol1 = (zoomsup + 225) - p1.height;
  jump_how1 = (zoomsup + 125) - p1.height;
  /******/
  cx = (int) (bkgdlim / 2);
  cy = zoomsup;
  zoomwidth = 320;
  spr1x = ((cx + 75) - (p1.width / 2)), spr1y = sol1;
  spr2x = ((cx + 250) - (p2.width / 2)), spr2y = sol2;
  fx = fy = 1;
  flag = flag2 = 1;
  fball1 = fball2 = 0;
  fballx1 = fballx2 = 0;
  spower1 = spower2 = 0;
  p1.fireb.succ = p2.fireb.succ = 0;
  p1.rush.succ = p2.rush.succ = 0;
  rush_stop1 = rush_stop2 = 0;
  smove_stop1 = smove_stop2 = 0;
  p1.firebx.succ = p2.firebx.succ = 0;
  p1.rushx.succ = p2.rushx.succ = 0;
  rushx_stop1 = rushx_stop2 = 0;
  smovex_stop1 = smovex_stop2 = 0;
  p1.wimpact_ct = p2.wimpact_ct = 0;
  p1.simpact_ct = p2.simpact_ct = 0;
  p1.bimpact_ct = p2.bimpact_ct = 0;
  damag1 = damag2 = 1;
  autho_ht1 = autho_ht2 = 0;
  life1 = life2 = 501;
  // PUT_t_clock (xget_config_int ("timer", "t_clock", 1));
  inverted = 0;
  deb = 1;
  vic1 = vic2 = 0;
  vsynch = 1;
  ok = 1;
  vic_flag = 1;
  
  return 0;
}


int kof91_load_fightfx(Game_variables variables){
  int p1,p1_ref;
  int p2,p2_ref;
  char * player1name;
  char * player2name;
  p1 = variables->System.Select_struct.p1_selected[0];
  p1_ref = variables->System.Select_struct.char_list[p1];
  p1_ref--;
  player1name = strcpy((char*)calloc(255,sizeof(char)),variables->System.Select_struct.char_ref_array[p1_ref].display_name);
  p2 = variables->System.Select_struct.p2_selected[0];
  p2_ref = variables->System.Select_struct.char_list[p2];
  p2_ref--;
  player2name = strcpy((char*)calloc(255,sizeof(char)),variables->System.Select_struct.char_ref_array[p1_ref].display_name);
  /*
  LBbanner = xload_pcx ("sprites" DIR_BAR "lifebars.pcx", 0);
  LBbanner2 = xload_pcx ("sprites" DIR_BAR "lifebars2.pcx", 0);
  
  Bar = xload_pcx ("sprites" DIR_BAR "bar.pcx", 0);
  Bar2 = create_bitmap(Bar->w,Bar->h);
  draw_sprite_h_flip (Bar2, Bar, 0, 0);
  sprintf (file2, "sprites" DIR_BAR "%s" DIR_BAR "selsmall.pcx",player1name);
  tface1 = xload_pcx (file2, Pal);
  sprintf (file2, "sprites" DIR_BAR "%s" DIR_BAR "selsmall.pcx",player2name);
  tface2 = xload_pcx (file2, Pal);
  
  novic0 = xload_pcx ("sprites" DIR_BAR "novic0.pcx", 0);
  novic1 = xload_pcx ("sprites" DIR_BAR "novic1.pcx", 0);

  avic0 = xload_pcx ("sprites" DIR_BAR "vic0.pcx", 0);
  avic1 = xload_pcx ("sprites" DIR_BAR "vic1.pcx", 0);

  Carton_R1 = xload_pcx ("sprites" DIR_BAR "round1.pcx", 0);
  Carton_R2 = xload_pcx ("sprites" DIR_BAR "round2.pcx", 0);
  Carton_R3 = xload_pcx ("sprites" DIR_BAR "round3.pcx", 0);
  Carton_FT = xload_pcx ("sprites" DIR_BAR "fight.pcx", 0);
  Carton_WN = xload_pcx ("sprites" DIR_BAR "winner.pcx", 0);
  Carton_KO = xload_pcx ("sprites" DIR_BAR "ko.pcx", 0);
  Power = xload_pcx ("sprites" DIR_BAR "power.pcx", 0);
  PBar = xload_pcx ("sprites" DIR_BAR "pbar.pcx", 0);
  
  TRON ("Loading timeborder.pcx...");
  if (file_missing("sprites" DIR_BAR "timeborder.pcx") ){
    B_clock[10] = create_bitmap( 29,21 );
    rectfill( B_clock[10],0,0,29,21, makecol( 0, 0, 0 ) );
  }else{
    B_clock[10] = xload_pcx ("sprites" DIR_BAR "timeborder.pcx", 0);
  }

  TRON ("Loading numbers 0.pcx - 9.pcx");
  B_clock[0] = xload_pcx ("sprites" DIR_BAR "0.pcx", 0);
  B_clock[1] = xload_pcx ("sprites" DIR_BAR "1.pcx", 0);
  B_clock[2] = xload_pcx ("sprites" DIR_BAR "2.pcx", 0);
  B_clock[3] = xload_pcx ("sprites" DIR_BAR "3.pcx", 0);
  B_clock[4] = xload_pcx ("sprites" DIR_BAR "4.pcx", 0);
  B_clock[5] = xload_pcx ("sprites" DIR_BAR "5.pcx", 0);
  B_clock[6] = xload_pcx ("sprites" DIR_BAR "6.pcx", 0);
  B_clock[7] = xload_pcx ("sprites" DIR_BAR "7.pcx", 0);
  B_clock[8] = xload_pcx ("sprites" DIR_BAR "8.pcx", 0);
  B_clock[9] = xload_pcx ("sprites" DIR_BAR "9.pcx", 0);
  TRON ("ok");

  B_prfct = xload_pcx ("sprites" DIR_BAR "perfect.pcx", 0);
  */
  return 0;
}// load_fight_fx
