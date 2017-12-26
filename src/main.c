#include <stdlib.h>
#include <stdio.h>
#include "allegro.h"
#include <string.h>
#include "macros.h"
#include "main.h"
#include "config.h"
#include "refresh.h" 
#include "logger.h"
#include "initfiles.h"
#include "global_add.h"
#include "read_config.h"
#include "2xsai.h"
#include "sound_fx_manager.h"
#include "load_fight_fx.h"
#include "loader.h"
#include "auto_conf.h"
#include "main_process.h"
#include "main_output.h"
#include "sensei_config.h"


/** \file main.c
 * \brief core of the engine
 *
 * Initialize the engine and the loop it until game_state = 666 (state of exit)
 */

/* ************* miscellanous functions added by Laurent Dufour (zesensei@free.fr) *************** */
volatile int kof91_time = 0;

/* this 2 counters are for count the fps */
volatile int frame_count, fps;

/* Timer callback for the speed counter */
void inc_time(){
  kof91_time++;
}
END_OF_FUNCTION(inc_time);

/* Timer callback for measuring the frames per second */
void fps_proc(void)
{
  fps = frame_count;
  frame_count = 0;
}                                                                               
END_OF_FUNCTION(fps_proc);
/* ****************************************************** */

int main(int argc, char * argv[]){
  //int error;
  int i,total_ticks,later;
  Game_variables main_game_variables;
  Player_variables * players;
  TRONSTART( "\n  **WARNING: Initializing KOF91..." );
  SENSEI_DEBUG_ON = 1;
  allegro_init(); // initialazing lib Allegro
 
  main_game_variables = (Game_variables)calloc(1,sizeof(struct Game_variables));		
  main_game_variables->Path = (char*)calloc(255,sizeof(char));
  main_game_variables->System.itemname = (char**)malloc((ITEM_NUMBER+1)*sizeof(char*));
  main_game_variables->System.Title_bg.bg_elt_array = NULL;
  main_game_variables->System.Option_bg.bg_elt_array = NULL;
  main_game_variables->System.Select_bg.bg_elt_array = NULL;
  main_game_variables->System.Vs_bg.bg_elt_array = NULL;
  mp3 = (MP3FILE *)malloc(sizeof(MP3FILE *));
  for (i=0;i<ITEM_NUMBER;i++){   
    main_game_variables->System.itemname[i] = (char*)calloc(255,sizeof(char));
  }

  players = (Player_variables*)calloc(MAX_OF_PLAYERS,sizeof(Player_variables));
  
  /***************** end of memory allocation ******************************/
  
  main_game_variables->Game_state = 0;
  main_game_variables->Path = strcpy(main_game_variables->Path,"data");
  put_backslash(main_game_variables->Path);
  players[0].facing = 1;
  players[1].facing = -1;
  players[3].facing = -1;
  players[0].has_control = 1;
  players[1].has_control = 1;
  
  if (read_config(main_game_variables,players)!=0) 
    {
      ERROR( "Pb in read config");
      allegro_exit();
      return 1;
    }   
  else 
    if (SENSEI_DEBUG_ON)
      TRON("Config read");
  
  /* for compatibility */
  set_config_file("game.ini");
  set_window_title ( TITLE );
  
  /*
  allegro_message(
		  "Based on KOF91 engine v.1.2 by Nicolas Sevez\n"
		  "KOF91 is FREEWARE and CANNOT BE SOLD\n"
		  );
  */

  if (apply_config(main_game_variables->Game_config)!=0){
    ERROR("Error applying config files");
    allegro_exit();
    return -1; 
  } 
  else
    if (SENSEI_DEBUG_ON)
      TRON("Config was applied");
  
 
  LOCK_VARIABLE(kof91_time);
  LOCK_FUNCTION(inc_time);
  LOCK_VARIABLE(fps);
  LOCK_VARIABLE(frame_count);
  LOCK_FUNCTION(fps_proc);
   
  if (install_int_ex(inc_time, BPS_TO_TIMER(main_game_variables->Game_config.Game_speed))){
    ERROR("main.c : Can't install timer at game_speed bps\n");
    allegro_exit();
    return -1;
  }
  //fprintf(stderr,"Game speed %i\n",main_game_variables->Game_config->Game_speed);
  if (install_int(fps_proc, 1000)) ERROR(" Can't install fps");
 
  frame_count = fps = 0;
  total_ticks = 0;

  if (gfmode==1) //If 2xsai is used this part is needed
    {
      set_color_depth(16);
      Init_2xSaI(16);
      if (SENSEI_DEBUG_ON)
	TRON("Starting double resolution mode");
    }
  
  virtscreen = create_bitmap(main_game_variables->Game_config.Buffer_w, main_game_variables->Game_config.Buffer_h );
  read_arguments(argc,argv,main_game_variables); //From 'read_config.h' Read arguments in command line
  get_env(main_game_variables); //From 'auto_conf.h' get environnement vars
  read_system(main_game_variables); //From 'read_config.h' Read system.def if it exists
  
  loadsounds(main_game_variables); //from sound_fx_manager.h load kof91 sounds
  load_fight_fx(main_game_variables); // from load_fight_fx.h
  
  players[0].computer_input = 0;
  players[1].computer_input = 0;
  
  /*************************** Main loop of the engine **************************/

  while ((main_game_variables->Game_state!=666)&&(main_game_variables->Game_state!=766)){
    main_process(main_game_variables,players,total_ticks);
    later = kof91_time;
    while (later>=kof91_time){  
    } 
    main_game_variables->fps = fps;
    //virtscreen = create_bitmap(main_game_variables->Game_config->Buffer_w+5, main_game_variables->Game_config->Buffer_h+5 );
    main_output(main_game_variables,players,total_ticks);
    //if (virtscreen!=NULL)
    //  destroy_bitmap(virtscreen);
    frame_count++;
    total_ticks++;
  }
  
  /****************************** Memory free ************************/
    
  TRON( "**WARNING: END OF PROGRAM" );
  TRONSTOP();
  allegro_exit();
  return 0;
} /*eof main() */
END_OF_MAIN();
