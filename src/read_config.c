#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "allegro.h"
#include "read_config.h"
#include "global.h"
#include "2xsai.h"
#include "config.h"
#include "macros.h"
#include "logger.h"



/** \file read_config.c
 * \brief functions (sources) to read mugen.cfg and system.def
 */


#ifdef ALLEGRO_DOS
/** \brief Function to convert music drivers whatever OS its compile on
 */
int convert_digi_driver(int a_driver){
  int driver_return;
  switch (a_driver){
  case 0:
    driver_return = DIGI_NONE;
    break;
  case 1:
    driver_return = DIGI_AUTODETECT;
    break;
  case 11:
    driver_return = DIGI_SB;
    break;
  case 12:
    driver_return = DIGI_AUDIODRIVE;
    break;
  case 13:
    driver_return = DIGI_SOUNDSCAPE;
    break;
  case 14:
    driver_return = DIGI_WINSOUNDSYS;
    break;
  default:
    driver_return = DIGI_AUTODETECT;
    break;
  }
  return driver_return;
}
int convert_midi_driver(int a_driver){
  int driver_return;
  switch (a_driver){
  case 0:
    driver_return = MIDI_NONE;
    break;
  case 1:
    driver_return = MIDI_AUTODETECT;
    break;
  default:
    driver_return = MIDI_AUTODETECT;
    break;
  }
  return driver_return;
}
#endif
#ifdef ALLEGRO_WINDOWS
int convert_digi_driver(int a_driver){
  int driver_return;
  switch (a_driver){
  case 0:
    driver_return = DIGI_NONE;
    break;
  case 1:
    driver_return = DIGI_AUTODETECT;
    break;
  case 21:
    driver_return = DIGI_DIRECTX(1);
    break;
  case 22:
    driver_return = DIGI_DIRECTX(2);
    break;
  case 23:
    driver_return = DIGI_DIRECTAMX(1);
    break;
  case 24:
    driver_return = DIGI_DIRECTAMX(2);
    break;
  case 25:
    driver_return = DIGI_WAVOUTID(0);
    break;
  case 26:
    driver_return = DIGI_WAVOUTID(1);
    break;
  default:
    driver_return = DIGI_AUTODETECT;
    break;
  }
  return driver_return;
}

int convert_midi_driver(int a_driver){
  int driver_return;
  switch (a_driver){
  case 0:
    driver_return = MIDI_NONE;
    break;
  case 1:
    driver_return = MIDI_AUTODETECT;
    break;
  case 21:
    driver_return = MIDI_WIN32MAPPER;
    break;
  case 22:
    driver_return = MIDI_WIN32(1);
    break;
  case 23:
    driver_return = MIDI_WIN32(2);
    break;
  case 24:
    driver_return = MIDI_DIGMID;
    break;
  default:
    driver_return = MIDI_NONE;
    break;
  }
  return driver_return;
}
#endif
#ifdef ALLEGRO_LINUX
int convert_digi_driver(int a_driver){
  int driver_return;
  switch (a_driver){
  case 0:
    driver_return = DIGI_NONE;
    break;
  case 1:
    driver_return = DIGI_AUTODETECT;
    break;
  case 31:
#ifdef DIGI_OSS
    driver_return = DIGI_OSS;
#else
    driver_return = DIGI_AUTODETECT;
#endif
    break;
  case 32:
#ifdef DIGI_ESD
    driver_return = DIGI_ESD;
#else
    driver_return = DIGI_AUTODETECT;
#endif
    break;
  case 33:
#ifdef DIGI_ARTS
    driver_return = DIGI_ARTS;
#else
    driver_return = DIGI_AUTODETECT;
#endif
    break;
  case 34:
#ifdef DIGI_ALSA
    driver_return = DIGI_ALSA;
#else
    driver_return = DIGI_AUTODETECT;
#endif
    break;
  default:
    driver_return = DIGI_AUTODETECT;
    break;
  }
  return driver_return;
}
int convert_midi_driver(int a_driver){
  int driver_return;
  switch (a_driver){
  case 0:
    driver_return = MIDI_NONE;
    break;
  case 1:
    driver_return = MIDI_AUTODETECT;
    break;
  case 31:
#ifdef MIDI_OSS
    driver_return = MIDI_OSS;
#else
    driver_return = MIDI_AUTODETECT;
#endif
    break;
  case 32:
#ifdef MIDI_DIGMID
    driver_return = MIDI_DIGMID;
#else
    driver_return = MIDI_AUTODETECT;
#endif
    break;
  case 33:
#ifdef MIDI_ALSA
    driver_return = MIDI_ALSA;
#else
    driver_return = MIDI_AUTODETECT;
#endif
    break;
  default:
    driver_return = MIDI_NONE;
    break;
  }
  return driver_return;
}
#endif
/*********************** End of OS specifs *************/

int convert_mugen_driver(char * a_driver){
  if (strstr(string_to_minus(a_driver),"auto")!=NULL)
    return 1;
  if (strstr(string_to_minus(a_driver),"none")!=NULL)
    return 0;
  if (strstr(a_driver,"0")!=NULL)
    return 0;
  if (strstr(a_driver,"1")!=NULL)
    return 1;
  return 1;
}

/** \brief function to apply args
 */
int read_arguments(int argc, char * argv[], Game_variables variables){
  int i;
  i = 1;
  while (i<argc){
    if (strcasecmp(argv[i],"-r")==0){
      variables->Path = strcat(variables->Path,argv[i+1]);
      put_backslash(variables->Path);
    }
    if (strcasecmp(argv[i],"-st")==0){
      variables->Game_state = atoi(argv[i+1])+100;
      gmode = 0;
    }
    if (strcasecmp(argv[i],"-storyboard")==0){
      variables->Game_state = 101;
      variables->System.Intro.Path = strcpy((char*)calloc(255,sizeof(char)),argv[i+1]);
      variables->System.Intro.storyboard.path = strcpy((char*)calloc(255,sizeof(char)),argv[i+1]);
      variables->System.Intro.Story_type = 2;
      variables->System.Intro.StoryExist = 1;
      variables->System.Intro.storyboard.loaded = 0;
    }
    i++;
  }
  
  return 0;
}//End Of read_arguments


/** \brief function to read config file
 * function that read config file (kof91.cfg or mugen.cfg) and the store it in a config_struct
 */
int read_config(Game_variables variables,Player_variables * player_array){
  char * cfg_path; 
  
  //Set kof91.cfg as config file
  cfg_path = strcpy((char*)calloc(255,sizeof(char)),"data");
  put_backslash(cfg_path);
  cfg_path = strcat(cfg_path,"kof91.cfg");
  
  if (!exists(cfg_path)){
    // test if mugen.cfg exist and take it if so
    cfg_path = strcpy((char*)calloc(255,sizeof(char)),"data");
    put_backslash(cfg_path);
    cfg_path = strcat(cfg_path,"mugen.cfg");
    
    if (!exists(cfg_path))
      fprintf(stderr,"no %s\n",cfg_path);
  }
  
  set_config_file(cfg_path);
  
  /* get config options */
  variables->Game_config.Game_speed = get_config_int("Config","GameSpeed",60);
  variables->Game_config.Difficulty = get_config_int("Options","Difficulty",4);
  variables->Game_config.Life = get_config_int("Options","Life",100);
  variables->Game_config.Time = get_config_int("Options","Time",99);
  
  /* get debug options */
  variables->Game_config.Debug_on = get_config_int("Debug","Debug",1);
  variables->Game_config.Allow_debug = get_config_int("Debug","AllowDebugMode",1);
  
  /* get video options */
  variables->Game_config.Width = get_config_int("Video","Width",320);
  variables->Game_config.Height = get_config_int("Video","Height",240);
  variables->Game_config.Fullscreen = get_config_int("Video","Fullscreen",0);
  variables->Game_config.Doubleres = get_config_int("Video","Doubleres",0);
  if (variables->Game_config.Doubleres!=4){
    variables->Game_config.Buffer_w = 320;
    variables->Game_config.Buffer_h = 240;
  }
  variables->Game_config.Stretch = get_config_int("Video","stretch",0);
   
  /* get sound options */
  variables->Game_config.Sound = get_config_int("Sound","Sound",1);
  variables->Game_config.Midi_driver = convert_mugen_driver(strcpy((char*)calloc(255,sizeof(char)),get_config_string("Sound","MidiDevice","auto")));
  variables->Game_config.Midi_driver = convert_midi_driver(variables->Game_config.Midi_driver);
  variables->Game_config.Digi_driver = convert_mugen_driver(strcpy((char*)calloc(255,sizeof(char)),get_config_string("Sound","WavDevice","auto")));
  variables->Game_config.Digi_driver = convert_digi_driver(variables->Game_config.Digi_driver);
  variables->Game_config.WavVolume = get_config_int("Sound","WavVolume",255);
  variables->Game_config.MidiVolume = get_config_int("Sound","MidiVolume",128);
  
  /* get input options */
  player_array[0].Player_input.use_joystick = get_config_int("Input","P1.UseJoystick",0);
  player_array[1].Player_input.use_joystick = get_config_int("Input","P2.UseJoystick",0);
  
  player_array[0].Player_input.keys[0] = get_config_int("P1_Keys","Jump",84);
  player_array[0].Player_input.keys[1] = get_config_int("P1_Keys","Crouch",85);
  player_array[0].Player_input.keys[2] = get_config_int("P1_Keys","Left",82);
  player_array[0].Player_input.keys[3] = get_config_int("P1_Keys","right",83);
  player_array[0].Player_input.keys[4] = get_config_int("P1_Keys","A",41);
  player_array[0].Player_input.keys[5] = get_config_int("P1_Keys","B",42);
  player_array[0].Player_input.keys[6] = get_config_int("P1_Keys","C",43);
  player_array[0].Player_input.keys[7] = get_config_int("P1_Keys","X",38);
  player_array[0].Player_input.keys[8] = get_config_int("P1_Keys","Y",39);
  player_array[0].Player_input.keys[9] = get_config_int("P1_Keys","Z",40);
  player_array[0].Player_input.keys[10] = get_config_int("P1_Keys","start",45);
   
  player_array[0].Player_input.joybuton[0] = get_config_int("P1_Joystick","A",0);
  player_array[0].Player_input.joybuton[1] = get_config_int("P1_Joystick","B",1);
  player_array[0].Player_input.joybuton[2] = get_config_int("P1_Joystick","C",2);
  player_array[0].Player_input.joybuton[3] = get_config_int("P1_Joystick","X",3);
  player_array[0].Player_input.joybuton[4] = get_config_int("P1_Joystick","Y",4);
  player_array[0].Player_input.joybuton[5] = get_config_int("P1_Joystick","Z",5);
  player_array[0].Player_input.joybuton[6] = get_config_int("P1_Joystick","start",6);
  player_array[0].Player_input.wait_input = 0;
  
  player_array[1].Player_input.keys[0] = get_config_int("P2_Keys","jump",26);
  player_array[1].Player_input.keys[1] = get_config_int("P2_Keys","crouch",23);
  player_array[1].Player_input.keys[2] = get_config_int("P2_Keys","left",17);
  player_array[1].Player_input.keys[3] = get_config_int("P2_Keys","right",19);
  player_array[1].Player_input.keys[4] = get_config_int("P2_Keys","A",6);
  player_array[1].Player_input.keys[5] = get_config_int("P2_Keys","B",7);
  player_array[1].Player_input.keys[6] = get_config_int("P2_Keys","C",8);
  player_array[1].Player_input.keys[7] = get_config_int("P2_Keys","X",22);
  player_array[1].Player_input.keys[8] = get_config_int("P2_Keys","Y",2);
  player_array[1].Player_input.keys[9] = get_config_int("P2_Keys","Z",14);
  player_array[1].Player_input.keys[10] = get_config_int("P2_Keys","start",11);     
  
  player_array[1].Player_input.joybuton[0] = get_config_int("P2_Joystick","A",0);
  player_array[1].Player_input.joybuton[1] = get_config_int("P2_Joystick","B",1);
  player_array[1].Player_input.joybuton[2] = get_config_int("P2_Joystick","C",2);
  player_array[1].Player_input.joybuton[3] = get_config_int("P2_Joystick","X",3);
  player_array[1].Player_input.joybuton[4] = get_config_int("P2_Joystick","Y",4);
  player_array[1].Player_input.joybuton[5] = get_config_int("P2_Joystick","Z",5);
  player_array[1].Player_input.joybuton[6] = get_config_int("P2_Joystick","start",6);
  player_array[1].Player_input.wait_input = 0;
  
  /* Reading old AI configuration */

  easy_def = get_config_int ( "AI config", "easy_def" , 60 );
  easy_off = get_config_int ( "AI config", "easy_off" , 30 );
  medium_def = get_config_int ( "AI config", "medium_def" , 70 );
  medium_off = get_config_int ( "AI config", "medium_off" , 50 );
  hard_def = get_config_int ( "AI config", "hard_def" , 60 );
  hard_off = get_config_int ( "AI config", "hard_off" , 80 );
  
  /* Reading old fight_fx conf */
  intro_delay = get_config_int ( "fight fx" , "intro_delay" , 125 );
  wimpact_nbf = get_config_int ( "fight fx" , "wimpact_nbf" , 6 );
  simpact_nbf = get_config_int ( "fight fx" , "simpact_nbf" , 6 );
  bimpact_nbf = get_config_int ( "fight fx" , "bimpact_nbf" , 8 );
  
  return 0;
}//read_config()

/** \brief function that apply the config read in Mugen's config file
 *
 * Use the config_struct as defined in the global_add.h
 */
int apply_config(config a_config){
  int modes[]={16,32,24,-1};
  int a = 0;
  int ok = 0; 
  int passed = 0;

  if (install_keyboard()!=0) 
    return -1;
  
  if (install_joystick(JOY_TYPE_AUTODETECT)!=0) 
    return -1;
  
  if (install_timer()!=0)
    return -1;
  
  /** Special hack for windows users, tring to use hardware accel
   */
  #ifdef ALLEGRO_WINDOWS
  if (a_config.Fullscreen){
    while ((!ok)&&(modes[a])!=-1){
      set_color_depth(modes[a]);	  
      ok = (set_gfx_mode(GFX_DIRECTX,a_config.Width,a_config.Height,0,0) == 0);
      a++;
    }
    if (!ok){
      fprintf(stderr,"Error setting Fullscreen videomode\n");
    }
    else{
      screen_depth = modes[a];
      passed = 1;
    }
  }
  
  /**
  if ((passed==0)||(!a_config.Fullscreen)){
    a = 0;
    while ((!ok)&&(modes[a])!=-1){
      set_color_depth(modes[a]);	  
      ok = (set_gfx_mode(GFX_AUTODETECT_WINDOWED,a_config.Width,a_config.Height,0,0) == 0);
      a++;
    }
    if (!ok){
      fprintf(stderr,"Error setting videomode\n");
      return -1;
    }
    screen_depth = modes[a];
  }
  */
#endif
  
  if (a_config.Fullscreen){
    while ((!ok)&&(modes[a])!=-1){
      set_color_depth(modes[a]);	  
      ok = (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,a_config.Width,a_config.Height,0,0) == 0);
      a++;
    }
    if (!ok){
      fprintf(stderr,"Error setting Fullscreen videomode\n");
    }
    else{
      screen_depth = modes[a];
      passed = 1;
    }
  }

  if ((passed==0)||(!a_config.Fullscreen)){
    a = 0;
    while ((!ok)&&(modes[a])!=-1){
      set_color_depth(modes[a]);	  
      ok = (set_gfx_mode(GFX_AUTODETECT_WINDOWED,a_config.Width,a_config.Height,0,0) == 0);
      a++;
    }
    if (!ok){
      fprintf(stderr,"Error setting videomode\n");
      return -1;
    }
    screen_depth = modes[a];
  }
  if (a_config.Sound){
    /* Apply sound config */
    //set_volume_per_voice(0);
    set_volume ( a_config.WavVolume , a_config.MidiVolume );
    if ( install_sound( a_config.Digi_driver,a_config.Midi_driver, 0 ) != 0 )
      return -1;
  }
  
  if ( gfmode==3 ) 
    scanliner = create_bitmap( screen_width, screen_height );
  else
    scanliner = create_bitmap( 10, 10 );
  // set_color_depth(8);	 
  return 0;
}//apply_config()

int set_default_config(Game_variables variables){
  variables->Game_config.Game_speed = 60;
  variables->Game_config.Difficulty = 4;
  variables->Game_config.Life = 100;
  variables->Game_config.Time = 99;
  variables->Game_config.WavVolume = get_config_int("Sound","WavVolume",255);
  variables->Game_config.MidiVolume = get_config_int("Sound","MidiVolume",128);
  return 0;
}//end set_default_config()

int set_default_keys(Player_variables * player_array,int player){
  if (player==1){
    player_array[0].Player_input.keys[0] = 84;
    player_array[0].Player_input.keys[1] = 85;
    player_array[0].Player_input.keys[2] = 82;
    player_array[0].Player_input.keys[3] = 83;
    player_array[0].Player_input.keys[4] = 41;
    player_array[0].Player_input.keys[5] = 42;
    player_array[0].Player_input.keys[6] = 43;
    player_array[0].Player_input.keys[7] = 38;
    player_array[0].Player_input.keys[8] = 39;
    player_array[0].Player_input.keys[9] = 40;
    player_array[0].Player_input.keys[10] = 45;
    
    player_array[0].Player_input.joybuton[0] = 0;
    player_array[0].Player_input.joybuton[1] = 1;
    player_array[0].Player_input.joybuton[2] = 2;
    player_array[0].Player_input.joybuton[3] = 3;
    player_array[0].Player_input.joybuton[4] = 4;
    player_array[0].Player_input.joybuton[5] = 5;
    player_array[0].Player_input.joybuton[6] = 6;
  }
  
  if (player==2){
    player_array[1].Player_input.keys[0] = 26;
    player_array[1].Player_input.keys[1] = 23;
    player_array[1].Player_input.keys[2] = 17;
    player_array[1].Player_input.keys[3] = 19;
    player_array[1].Player_input.keys[4] = 6;
    player_array[1].Player_input.keys[5] = 7;
    player_array[1].Player_input.keys[6] = 8;
    player_array[1].Player_input.keys[7] = 22;
    player_array[1].Player_input.keys[8] = 2;
    player_array[1].Player_input.keys[9] = 14;
    player_array[1].Player_input.keys[10] = 11;     
  
  player_array[1].Player_input.joybuton[0] = 0;
  player_array[1].Player_input.joybuton[1] = 1;
  player_array[1].Player_input.joybuton[2] = 2;
  player_array[1].Player_input.joybuton[3] = 3;
  player_array[1].Player_input.joybuton[4] = 4;
  player_array[1].Player_input.joybuton[5] = 5;
  player_array[1].Player_input.joybuton[6] = 6;
  }
  return 0;
} //end set_default_keys()

int save_config (Game_variables variables,Player_variables * player_array){
  char * cfg_path; 
  cfg_path = (char*)calloc(255,sizeof(char));
  cfg_path = strcpy(cfg_path,"data");
  put_backslash(cfg_path);
  cfg_path = strcat(cfg_path,"kof91.cfg");
  
  
  /* test if data/kof91e.cfg file exist */
  if (!exists(cfg_path))
    fprintf(stderr,"no %s\n",cfg_path);
  
  set_config_file(cfg_path);
  
  /* set config options */
  set_config_int("Options","GameSpeed",variables->Game_config.Game_speed);
  set_config_int("Options","Difficulty",variables->Game_config.Difficulty);
  set_config_int("Options","Life", variables->Game_config.Life);
  set_config_int("Options","Time",variables->Game_config.Time);
 
  // set sound options 
  set_config_int("Sound","WavVolume", variables->Game_config.WavVolume);
  set_config_int("Sound","MidiVolume",variables->Game_config.MidiVolume);

  //set input options 
  set_config_int("Input","P1.UseJoystick",player_array[0].Player_input.use_joystick);
  set_config_int("Input","P2.UseJoystick", player_array[1].Player_input.use_joystick);
  
  //set keys option
  set_config_int("P1_Keys","Jump", player_array[0].Player_input.keys[0]);
  set_config_int("P1_Keys","Crouch", player_array[0].Player_input.keys[1]);
  set_config_int("P1_Keys","Left",player_array[0].Player_input.keys[2]);
  set_config_int("P1_Keys","right",player_array[0].Player_input.keys[3]);
  set_config_int("P1_Keys","A", player_array[0].Player_input.keys[4]);
  set_config_int("P1_Keys","B", player_array[0].Player_input.keys[5]);
  set_config_int("P1_Keys","C",player_array[0].Player_input.keys[6]);
  set_config_int("P1_Keys","X",player_array[0].Player_input.keys[7]);
  set_config_int("P1_Keys","Y",player_array[0].Player_input.keys[8]);
  set_config_int("P1_Keys","Z",player_array[0].Player_input.keys[9]);
  set_config_int("P1_Keys","start",player_array[0].Player_input.keys[10]);
   
  set_config_int("P1_Joystick","A",player_array[0].Player_input.joybuton[0]);
  set_config_int("P1_Joystick","B", player_array[0].Player_input.joybuton[1]);
  set_config_int("P1_Joystick","C",player_array[0].Player_input.joybuton[2]);
  set_config_int("P1_Joystick","X",player_array[0].Player_input.joybuton[3]);
  set_config_int("P1_Joystick","Y", player_array[0].Player_input.joybuton[4]);
  set_config_int("P1_Joystick","Z",player_array[0].Player_input.joybuton[5]);
  set_config_int("P1_Joystick","start", player_array[0].Player_input.joybuton[6]);
  
  set_config_int("P2_Keys","jump",player_array[1].Player_input.keys[0]);
  set_config_int("P2_Keys","crouch",player_array[1].Player_input.keys[1]);
  set_config_int("P2_Keys","left",player_array[1].Player_input.keys[2]);
  set_config_int("P2_Keys","right",player_array[1].Player_input.keys[3]);
  set_config_int("P2_Keys","A",player_array[1].Player_input.keys[4]);
  set_config_int("P2_Keys","B", player_array[1].Player_input.keys[5]);
  set_config_int("P2_Keys","C",player_array[1].Player_input.keys[6]);
  set_config_int("P2_Keys","X",player_array[1].Player_input.keys[7]);
  set_config_int("P2_Keys","Y",player_array[1].Player_input.keys[8]);
  set_config_int("P2_Keys","Z",player_array[1].Player_input.keys[9]);
  set_config_int("P2_Keys","start",player_array[1].Player_input.keys[10]);     
  
  set_config_int("P2_Joystick","A",player_array[1].Player_input.joybuton[0]);
  set_config_int("P2_Joystick","B",player_array[1].Player_input.joybuton[1]);
  set_config_int("P2_Joystick","C",player_array[1].Player_input.joybuton[2]);
  set_config_int("P2_Joystick","X",player_array[1].Player_input.joybuton[3]);
  set_config_int("P2_Joystick","Y",player_array[1].Player_input.joybuton[4]);
  set_config_int("P2_Joystick","Z",player_array[1].Player_input.joybuton[5]);
  set_config_int("P2_Joystick","start",player_array[1].Player_input.joybuton[6]);
  
  flush_config_file();
  return 0;
} //end save_config()

/*************************************************************/
/* System part */

/** \brief function to remove quotes from options in menu screen
 */
char * remove_quotes(char * a_string){
  char * result;
  int read_index;
  int write_index;
  result = (char*)calloc(255,sizeof(char));
  
  read_index = 0;
  write_index = 0;

  while (a_string[read_index]==' ')
    read_index++;

  if (a_string[read_index]=='"')
    read_index++;
      
  while ((a_string[read_index]!='\n')&&(a_string[read_index]!='\r')&&(a_string[read_index]!='"')&&(a_string[read_index]!='\0')&&(a_string[read_index]!=';'))
    {
      result[write_index] = a_string[read_index];
      write_index++;
      read_index++;
    }
	 
  write_index++;
  result[write_index]='\0';
  return result;
}

/** \brief function to convert a music filename extension to an integer support by the engine
 */
int music_type(char * music_filename){
  int type = 0;
  if ((strstr(music_filename,".mid")!=NULL)||(strstr(music_filename,".MID")!=NULL))
    type = 1;
  if ((strstr(music_filename,".mp3")!=NULL)||(strstr(music_filename,".MP3")!=NULL))
    type = 2;
  return type;
}

/** \brief main function that read system.def
 */
int read_system(Game_variables variables){
  char * system_path;
  char * result;
  char * message;
  int * int_tab;
  double * float_tab;
  int error;
  //int * error_ptr;
  char * path;
  int system_exist = 0;
  result = (char*)calloc(255,sizeof(char));
  message = (char*)calloc(255,sizeof(char));
  int_tab = (int*)calloc(5,sizeof(int));
  path = (char*)calloc(255,sizeof(char));
  system_path = (char*)calloc(255,sizeof(char));
  error = 0;
  
  system_path = check_path("system.def",variables->Path,"system_path",&error);
  
  if (error==0){
    set_config_file(system_path);
    sensei_set_config_file(system_path);
    system_exist = 1;
  }
  else{
    system_exist = 0;
  }
  
  
  /********** Getting files info **********************************/
  
  // snd part
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","snd",""));
  result = check_path(result,variables->Path,"variables->System.Systemsnd",&error);
  if (error==0){
    variables->System.Systemsnd = sndLoadSound(result); 
    variables->System.Sndexist = 1;
  }else{
    variables->System.Sndexist = 0;
  }
    
  // sff loading part
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","spr",""));
  result = check_path(result,variables->Path,"variables->System.Title_bg.bg_sff_path",&error);
  if (error==0){
    variables->System.Title_bg.bg_sff_path_known = 1;
    variables->System.Title_bg.bg_sff_path = strcpy((char*)calloc(255,sizeof(char)),result);
    variables->System.Option_bg.bg_sff_path_known = 1;
    variables->System.Option_bg.bg_sff_path = strcpy((char*)calloc(255,sizeof(char)),result);
    variables->System.Select_bg.bg_sff_path_known = 1;
    variables->System.Select_bg.bg_sff_path = strcpy((char*)calloc(255,sizeof(char)),result);
    variables->System.Vs_bg.bg_sff_path_known = 1;
    variables->System.Vs_bg.bg_sff_path = strcpy((char*)calloc(255,sizeof(char)),result);
    variables->System.Select_struct.sff_path = strcpy((char*)calloc(255,sizeof(char)),result);
  }else{
    variables->System.Title_bg.bg_sff_path_known = 0;
    variables->System.Option_bg.bg_sff_path_known = 0;
    variables->System.Select_bg.bg_sff_path_known = 0;
    variables->System.Vs_bg.bg_sff_path_known = 0;
  }

  // Global system file
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","select",""));
  result = check_path(result,variables->Path,"variables->System.select_path",&error);
  if (error==0){
    variables->System.select_path = strcpy((char*)calloc(255,sizeof(char)),result);
  }else{
    variables->System.Select_struct.type = 0;
  }
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","fight",""));
  result = check_path(result,variables->Path,"variables->System.fight_path",&error);
  if (error==0){
    variables->System.fight_path = strcpy((char*)calloc(255,sizeof(char)),result);
  }else{
    variables->System.fight_path = NULL;
  }


  // font part
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","font0",""));
  result = check_path(result,variables->Path,"variables->System.fontInfo0",&error);
  if (error==0){
    variables->System.fontInfo0 = fntLoadFont(result);
    variables->System.font0exist = 1;
  }else{
    variables->System.font0exist = 0;
  }

  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","font1","font/f-4x6.fnt"));
  result = check_path(result,variables->Path,"variables->System.fontInfo1",&error);
  if (error==0){
    variables->System.fontInfo1 = fntLoadFont(result);
    variables->System.font1exist = 1;
  }else{
    variables->System.font1exist = 0;
  }
  
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","font2","font/f-6x9.fnt"));
  result = check_path(result,variables->Path,"variables->System.fontInfo2",&error);
  if (error==0){
    variables->System.fontInfo2 = fntLoadFont(result);
    variables->System.font2exist = 1;
  }else{
    variables->System.font2exist = 0;
  }
  
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","font3",""));
  result = check_path(result,variables->Path,"variables->System.fontInfo3",&error);
  if (error==0){
    variables->System.fontInfo3 = fntLoadFont(result);
    variables->System.font3exist = 1;
  }else{
    variables->System.font3exist = 0;
  }
  
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","font4",""));
  result = check_path(result,variables->Path,"variables->System.fontInfo4",&error);
  if (error==0){
    variables->System.fontInfo4 = fntLoadFont(result);
    variables->System.font4exist = 1;
  }else{
    variables->System.font4exist = 0;
  }
  
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","font5",""));
  result = check_path(result,variables->Path,"variables->System.fontInfo5",&error);
  if (error==0){
    variables->System.fontInfo5 = fntLoadFont(result);
    variables->System.font5exist = 1;
  }else{
    variables->System.font5exist = 0;
  }
  
  //TRON("before strcpy fnt6");
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","font6",""));
  result = check_path(result,variables->Path,"variables->System.fontInfo6",&error);
  if (error==0){
    variables->System.fontInfo6 = fntLoadFont(result);
    variables->System.font6exist = 1;
  }else{
    variables->System.font6exist = 0;
  }
  
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","font7",""));
  result = check_path(result,variables->Path,"variables->System.fontInfo7",&error);
  if (error==0){
    variables->System.fontInfo7 = fntLoadFont(result);
    variables->System.font7exist = 1;
  }else{
    variables->System.font7exist = 0;
  }
  
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","font8",""));
  result = check_path(result,variables->Path,"variables->System.fontInfo8",&error);
  if (error==0){
    variables->System.fontInfo8 = fntLoadFont(result);
    variables->System.font8exist = 1;
  }else{
    variables->System.font8exist = 0;
  }

  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Files","font9",""));
  result = check_path(result,variables->Path,"variables->System.fontInfo9",&error);
  if (error==0){
    variables->System.fontInfo9 = fntLoadFont(result);
    variables->System.font9exist = 1;
  }else{
    variables->System.font9exist = 0;
  }
  
  /******************* Getting title_info *************************************/
 
  variables->System.itemname[0] = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Title Info","menu.itemname.arcade","ARCADE"));
  variables->System.itemname[0] = remove_quotes(variables->System.itemname[0]);
 
  variables->System.itemname[1] = strcpy(variables->System.itemname[1],sensei_get_config_string("Title Info","menu.itemname.versus","VERSUS"));
  variables->System.itemname[1] = remove_quotes(variables->System.itemname[1]);
  variables->System.itemname[2] = strcpy(variables->System.itemname[2],sensei_get_config_string("Title Info","menu.itemname.teamarcade","TEAM ARCADE"));
  variables->System.itemname[2] = remove_quotes(variables->System.itemname[2]);
  variables->System.itemname[3] = strcpy(variables->System.itemname[3],sensei_get_config_string("Title Info","menu.itemname.teamversus","TEAM VS"));
  variables->System.itemname[3] = remove_quotes(variables->System.itemname[3]);
  variables->System.itemname[4] = strcpy(variables->System.itemname[4],sensei_get_config_string("Title Info","menu.itemname.teamcoop","TEAM CO-OP"));
  variables->System.itemname[4] = remove_quotes(variables->System.itemname[4]);
  variables->System.itemname[5] = strcpy(variables->System.itemname[5],sensei_get_config_string("Title Info","menu.itemname.survival","SURVIVAL"));
  variables->System.itemname[5] = remove_quotes(variables->System.itemname[5]);
  variables->System.itemname[6] = strcpy(variables->System.itemname[6],sensei_get_config_string("Title Info","menu.itemname.survivalcoop","SURVIVAL CO-OP"));
  variables->System.itemname[6] = remove_quotes(variables->System.itemname[6]);
  variables->System.itemname[7] = strcpy(variables->System.itemname[7],sensei_get_config_string("Title Info","menu.itemname.training","TRAINING"));
  variables->System.itemname[7] = remove_quotes(variables->System.itemname[7]);
  variables->System.itemname[8] = strcpy(variables->System.itemname[8],sensei_get_config_string("Title Info","menu.itemname.watch","WATCH"));
  variables->System.itemname[8] = remove_quotes(variables->System.itemname[8]);
  variables->System.itemname[9] = strcpy(variables->System.itemname[9],sensei_get_config_string("Title Info","menu.itemname.options","OPTIONS"));
  variables->System.itemname[9] = remove_quotes(variables->System.itemname[9]);
  variables->System.itemname[10] = strcpy(variables->System.itemname[10],sensei_get_config_string("Title Info","menu.itemname.exit","EXIT"));
  variables->System.itemname[10] = remove_quotes(variables->System.itemname[10]);
    
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Title Info","menu.pos","159,158"));
  int_tab = convert_string(result);
  variables->System.posx = int_tab[0];
  variables->System.posy = int_tab[1];

  int_tab = (int*)calloc(5,sizeof(int));
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Title Info","menu.item.font","3,0,0"));
  int_tab = convert_string(result);
  variables->System.itemfontnumber = int_tab[0];
  variables->System.itemfontcolor = int_tab[1];
  variables->System.itemfontalignement = int_tab[2];
  
  int_tab = (int*)calloc(5,sizeof(int));
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Title Info","menu.item.active.font","3,5,0"));
  int_tab = convert_string(result);
  variables->System.itemactivefontnumber = int_tab[0];
  variables->System.itemactivefontcolor = int_tab[1];
  variables->System.itemactivefontalignement = int_tab[2];

  int_tab = (int*)calloc(5,sizeof(int));
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Title Info","menu.item.spacing","0,13"));
  int_tab = convert_string(result);
  variables->System.itemspacingx = int_tab[0];
  variables->System.itemspacingy = int_tab[1];
 

  int_tab = (int*)calloc(5,sizeof(int));
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Title Info","menu.window.margins.y","12,8"));
  int_tab = convert_string(result);
  variables->System.windowsmarginx = int_tab[0];
  variables->System.windowsmarginy = int_tab[1];

  variables->System.boxvisible = sensei_get_config_int("Title Info","menu.boxcursor.visible",1);
  variables->System.boxposition = 0;
  variables->System.visibleitems = sensei_get_config_int("Title Info","menu.window.visibleitems",4);
  
  int_tab = (int*)calloc(5,sizeof(int));
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Title Info","menu.boxcursor.coords","-58,-10,57,2"));
  int_tab = convert_string(result);
  variables->System.boxcoordsx = int_tab[0];
  variables->System.boxcoordsy = int_tab[1];
  variables->System.boxcoordsw = int_tab[2];
  variables->System.boxcoordsh = int_tab[3];
  
  variables->System.currentitem = 0;
  variables->System.firstitem = 0;
  variables->System.transadd = 0; 

  int_tab = (int*)calloc(5,sizeof(int));
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Title Info","cursor.move.snd","100,0"));
  int_tab = convert_string(result);
  variables->System.Mvcursorgrp = int_tab[0];
  variables->System.Mvcursornb = int_tab[1];

  int_tab = (int*)calloc(5,sizeof(int));
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Title Info","cursor.done.snd","100,1"));
  int_tab = convert_string(result);
  variables->System.Donecursorgrp = int_tab[0];
  variables->System.Donecursornb = int_tab[1];

  int_tab = (int*)calloc(5,sizeof(int));
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Title Info","cancel.snd","100,2"));
  int_tab = convert_string(result);
  variables->System.Cancelgrp = int_tab[0];
  variables->System.Cancelnb = int_tab[1];

  int_tab = (int*)calloc(5,sizeof(int));
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Option Info","cursor.move.snd","100,0"));
  int_tab = convert_string(result);
  variables->System.OMvcursorgrp = int_tab[0];
  variables->System.OMvcursornb = int_tab[1];

  result = (char*)calloc(255,sizeof(char));
  int_tab = (int*)calloc(5,sizeof(int));
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Option Info","cursor.done.snd","100,1"));
  int_tab = convert_string(result);
  variables->System.ODonecursorgrp = int_tab[0];
  variables->System.ODonecursornb = int_tab[1];

  int_tab = (int*)calloc(5,sizeof(int));
  result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Option Info","cancel.snd","100,2"));
  int_tab = convert_string(result);
  variables->System.OCancelgrp = int_tab[0];
  variables->System.OCancelnb = int_tab[1];
  
  variables->System.Otransadd = 0; 
  variables->System.Ocurrentitem = 0;
  variables->System.Otranseffect = 0;
  variables->System.Ocurrentitem2 = 0;
  
  if (system_exist){
    // storyboard part
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","logo.storyboard",""));
    result = check_path(result,variables->Path,"variables->System.Intro (logo)",&error);
    if (error==0){
      variables->System.Intro.storyboard.path = strcpy((char*)calloc(255,sizeof(char)),result);
      variables->System.Intro.Story_type = 2;
      variables->System.Intro.StoryExist = 1;
      variables->System.Intro.storyboard.loaded = 0;
    }else{
      variables->System.Intro.Story_type = 0;
      variables->System.Intro.StoryExist = 0;
    }
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","intro.storyboard",""));
    result = check_path(result,variables->Path,"variables->System.Open (intro)",&error);
    if (error==0){
      variables->System.Open.storyboard.path = strcpy((char*)calloc(255,sizeof(char)),result);
      variables->System.Open.Story_type = 2;
      variables->System.Open.StoryExist = 1;
      variables->System.Open.storyboard.loaded = 0;
    }else{
      variables->System.Intro.Story_type = 0;
      variables->System.Intro.StoryExist = 0;
    }
    
    /*
     * Music datas
     */
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Music","title.bgm",""));
    result = check_path(result,variables->Path,"title_music.path",&error);
    if (error==0){
      variables->System.title_music.path = strcpy((char*)calloc(255,sizeof(char)),result);
      variables->System.title_music.type = music_type(variables->System.title_music.path);
    }else{
      variables->System.title_music.type = 0;  
    }
    variables->System.title_music.loop = get_config_int("Music","title.bgm.loop",0);
    variables->System.title_music.loaded = 0;
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Music","select.bgm",""));
    result = check_path(result,variables->Path,"Selectbgm_path",&error);
    if (error==0){
      variables->System.select_music.path = strcpy((char*)calloc(255,sizeof(char)),result);
      variables->System.select_music.type = music_type(variables->System.select_music.path);
    }else{
      variables->System.select_music.type = 0;
    }
    variables->System.select_music.loop = get_config_int("Music","select.bgm.loop",0);
    variables->System.select_music.loaded = 0;
    
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Music","vs.bgm",""));
    result = check_path(result,variables->Path,"Vsbgm_path",&error);
    if (error==0){
      variables->System.vs_music.path = strcpy((char*)calloc(255,sizeof(char)),result);
      variables->System.vs_music.type = music_type(variables->System.vs_music.path);
    }else{
      variables->System.vs_music.type = 0;
    }
    variables->System.vs_music.loop = get_config_int("Music","vs.bgm.loop",0);
    variables->System.vs_music.loaded = 0;
    
    sprintf(message,"Giving bg names with Title.sff_path = %s",  variables->System.Title_bg.bg_sff_path);
    TRON(message);
    variables->System.Title_bg.type = 3;
    variables->System.Title_bg.name = strcpy((char*)calloc(255,sizeof(char)),"TitleBG");
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("TitleBGdef","spr",""));
    result = check_path(result,variables->Path,"Title_bg.bg_sff_path",&error);
    if (error==0){
      variables->System.Title_bg.bg_sff_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    variables->System.Title_bg.bg_path = strcpy((char*)calloc(255,sizeof(char)),system_path);
    variables->System.Title_bg.loaded = 0;
    
    variables->System.Option_bg.type = 3;
    variables->System.Option_bg.name = strcpy((char*)calloc(255,sizeof(char)),"OptionBG");
   
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("OptionBGdef","spr",""));
    result = check_path(result,variables->Path,"Option_bg.bg_sff_path",&error);
    if (error==0){
      variables->System.Option_bg.bg_sff_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    variables->System.Option_bg.bg_path = strcpy((char*)calloc(255,sizeof(char)),system_path);
    variables->System.Option_bg.loaded = 0;
    
    variables->System.Select_bg.type = 3;
    variables->System.Select_bg.name = strcpy((char*)calloc(255,sizeof(char)),"SelectBG");
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("SelectBGdef","spr",""));
    result = check_path(result,variables->Path,"Select_bg.bg_sff_path",&error);
    if (error==0){
      variables->System.Select_bg.bg_sff_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    variables->System.Select_bg.bg_path = strcpy((char*)calloc(255,sizeof(char)),system_path);
    variables->System.Select_bg.loaded = 0;
    
    variables->System.Vs_bg.type = 3;
    variables->System.Vs_bg.name = strcpy((char*)calloc(255,sizeof(char)),"VersusBG");
    result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("VersusBGdef","spr",""));
    result = check_path(result,variables->Path,"Vs_bg.bg_sff_path",&error);
    if (error==0){
      variables->System.Vs_bg.bg_sff_path = strcpy((char*)calloc(255,sizeof(char)),result);
    }
    variables->System.Vs_bg.bg_path = strcpy((char*)calloc(255,sizeof(char)),system_path);
    variables->System.Vs_bg.loaded = 0;
    
    /**
     * Select screen infos
     */
    variables->System.Select_struct.type = 1;
    variables->System.Select_struct.rows = sensei_get_config_int("Select Info","rows",2);
    variables->System.Select_struct.columns = sensei_get_config_int("Select Info","columns",5);
    variables->System.Select_struct.s_nb_char = variables->System.Select_struct.columns * variables->System.Select_struct.rows;
    variables->System.Select_struct.char_list = (int*)calloc(variables->System.Select_struct.s_nb_char,sizeof(int));
    variables->System.Select_struct.wrapping = sensei_get_config_int("Select Info","wrapping",0);
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","pos","90,170"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.posx = int_tab[0];
    variables->System.Select_struct.posy = int_tab[1];
    variables->System.Select_struct.showemptyboxes = sensei_get_config_int("Select Info","showemptyboxes",0);
    variables->System.Select_struct.moveoveremptyboxes = sensei_get_config_int("Select Info","moveoveremptyboxes",0);
    variables->System.Select_struct.loaded = 0;
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","cell.bg.spr","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.cellbgsprg = int_tab[0];
    variables->System.Select_struct.cellbgspri = int_tab[1];
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","cell.size","0,0"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.cellsizex = int_tab[0];
    variables->System.Select_struct.cellsizey = int_tab[1];
    variables->System.Select_struct.cellspacing = sensei_get_config_int("Select Info","cell.spacing",0);
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p1.cursor.active.spr","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p1activeg = int_tab[0];
    variables->System.Select_struct.p1activei = int_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p2.cursor.active.spr","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p2activeg = int_tab[0];
    variables->System.Select_struct.p2activei = int_tab[1];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p1.cursor.startcell","0,0"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p1starty = int_tab[0];
    variables->System.Select_struct.p1startx = int_tab[1];
    variables->System.Select_struct.p1_position.y = int_tab[0];
    variables->System.Select_struct.p1_position.x = int_tab[1];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p2.cursor.startcell","0,0"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p2starty = int_tab[0];
    variables->System.Select_struct.p2startx = int_tab[1];
    variables->System.Select_struct.p2_position.y = int_tab[0];
    variables->System.Select_struct.p2_position.x = int_tab[1];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p1.cursor.done.spr","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p1doneg = int_tab[0];
    variables->System.Select_struct.p1donei = int_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p2.cursor.done.spr","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p2doneg = int_tab[0];
    variables->System.Select_struct.p2donei = int_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p1.cursor.move.snd","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p1movesndg = int_tab[0];
    variables->System.Select_struct.p1movesndi = int_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p2.cursor.move.snd","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p2movesndg = int_tab[0];
    variables->System.Select_struct.p2movesndi = int_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p1.cursor.done.snd","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p1donesndg = int_tab[0];
    variables->System.Select_struct.p1donesndi = int_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p2.cursor.done.snd","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p2donesndg = int_tab[0];
    variables->System.Select_struct.p2donesndi = int_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p1.random.move.snd","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p1randomsndg = int_tab[0];
    variables->System.Select_struct.p1randomsndi = int_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p2.random.move.snd","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p2randomsndg = int_tab[0];
    variables->System.Select_struct.p2randomsndi = int_tab[1];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","portrait.offset","0,0"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.portraitoffsetx = int_tab[0];
    variables->System.Select_struct.portraitoffsety = int_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","portrait.scale","1,1"));
    float_tab = (double*)calloc(5,sizeof(double));
    float_tab = convert_stringd(result);
    variables->System.Select_struct.portraitscalex = float_tab[0];
    variables->System.Select_struct.portraitscaley = float_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","title.offset","159,13"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.titleoffsetx = int_tab[0];
    variables->System.Select_struct.titleoffsety = int_tab[1];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","title.font","3,0,0"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.titlefonti = int_tab[0];
    variables->System.Select_struct.titlefontcolor = int_tab[1];
    variables->System.Select_struct.titlefontjust = int_tab[2];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p1.face.offset","18,13"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p1faceoffsetx = int_tab[0];
    variables->System.Select_struct.p1faceoffsety = int_tab[1];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p2.face.offset","301,13"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p2faceoffsetx = int_tab[0];
    variables->System.Select_struct.p2faceoffsety = int_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p1.face.scale","1,1"));
    float_tab = (double*)calloc(2,sizeof(double));
    float_tab = convert_stringd(result);
    variables->System.Select_struct.p1facescalex = float_tab[0];
    variables->System.Select_struct.p1facescaley = float_tab[1];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p2.face.scale","1,1"));
    float_tab = (double*)calloc(2,sizeof(double));
    float_tab = convert_stringd(result);
    variables->System.Select_struct.p2facescalex = float_tab[0];
    variables->System.Select_struct.p2facescaley = float_tab[1];
    
    variables->System.Select_struct.p1facefacing = sensei_get_config_int("Select Info","p1.face.facing",1);
    variables->System.Select_struct.p2facefacing = sensei_get_config_int("Select Info","p2.face.facing",-1);

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p1.name.offset","10,162"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p1nameoffsetx = int_tab[0];
    variables->System.Select_struct.p1nameoffsety = int_tab[1];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p1.name.font","3,4,1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p1namefonti = int_tab[0];
    variables->System.Select_struct.p1namefontcolor = int_tab[1];
    variables->System.Select_struct.p1namefontjust = int_tab[2];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p2.name.offset","10,162"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p2nameoffsetx = int_tab[0];
    variables->System.Select_struct.p2nameoffsety = int_tab[1];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","p2.name.font","3,4,1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.p2namefonti = int_tab[0];
    variables->System.Select_struct.p2namefontcolor = int_tab[1];
    variables->System.Select_struct.p2namefontjust = int_tab[2];

    variables->System.Select_struct.p1_showed = 1;
    variables->System.Select_struct.p2_showed = 1;
    variables->System.Select_struct.p1_controller = 1;
    variables->System.Select_struct.p2_controller = 2;
    variables->System.Select_struct.p1_selecter = 0;
    variables->System.Select_struct.p2_selecter = 0;
    variables->System.Select_struct.p1_max_selecter = 1;
    variables->System.Select_struct.p2_max_selecter = 1;

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","stage.move.snd","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.stagemovesndg = int_tab[0];
    variables->System.Select_struct.stagemovesndi = int_tab[1];
    
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","stage.done.snd","-1,-1"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.stagedonesndg = int_tab[0];
    variables->System.Select_struct.stagedonesndi = int_tab[1];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","stage.pos","160,237"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.stageposx = int_tab[0];
    variables->System.Select_struct.stageposy = int_tab[1];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","stage.active.font","3,0,0"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.stageactivefonti = int_tab[0];
    variables->System.Select_struct.stageactivefontcolor = int_tab[1];
    variables->System.Select_struct.stageactivefontjust = int_tab[2];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","stage.active2.font","3,2,0"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.stageactive2fonti = int_tab[0];
    variables->System.Select_struct.stageactive2fontcolor = int_tab[1];
    variables->System.Select_struct.stageactive2fontjust = int_tab[2];

    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Select Info","stage.done.font","3,0,0"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Select_struct.stagedonefonti = int_tab[0];
    variables->System.Select_struct.stagedonefontcolor = int_tab[1];
    variables->System.Select_struct.stagedonefontjust = int_tab[2];
    
    variables->System.Select_struct.bg_selected = 0;
    variables->System.Select_struct.bg_blinked = 0;
    variables->System.Select_struct.current_bg = 0;

    variables->System.Vs_struct.time = sensei_get_config_int("Vs Screen","time",150);
    variables->System.Vs_struct.currenttime = 0;
    variables->System.Vs_struct.fadeintime = sensei_get_config_int("Vs Screen","fadein.time",15);
    variables->System.Vs_struct.fadeouttime = sensei_get_config_int("Vs Screen","fadeout.time",15);
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Vs Screen","p1.pos","20,31"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Vs_struct.p1pos.x = int_tab[0];
    variables->System.Vs_struct.p1pos.y = int_tab[1];
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Vs Screen","p2.pos","299,31"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Vs_struct.p2pos.x = int_tab[0];
    variables->System.Vs_struct.p2pos.y = int_tab[1];
    variables->System.Vs_struct.p1facing = sensei_get_config_int("Vs Screen","p1.facing",1);
    variables->System.Vs_struct.p2facing = sensei_get_config_int("Vs Screen","p2.facing",-1);
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Vs Screen","p1.scale","1,1"));
    float_tab = (double*)calloc(2,sizeof(double));
    float_tab = convert_stringd(result);
    variables->System.Vs_struct.p1scalex = float_tab[0];
    variables->System.Vs_struct.p1scaley = float_tab[1];
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Vs Screen","p2.scale","1,1"));
    float_tab = (double*)calloc(2,sizeof(double));
    float_tab = convert_stringd(result);
    variables->System.Vs_struct.p2scalex = float_tab[0];
    variables->System.Vs_struct.p2scaley = float_tab[1];
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Vs Screen","p1.name.pos","78,190"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Vs_struct.p1namepos.x = int_tab[0];
    variables->System.Vs_struct.p1namepos.y = int_tab[1];
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Vs Screen","p2.name.pos","241,190"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Vs_struct.p2namepos.x = int_tab[0];
    variables->System.Vs_struct.p2namepos.y = int_tab[1];
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Vs Screen","p1.name.font","3,0,0"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Vs_struct.p1namefonti = int_tab[0];
    variables->System.Vs_struct.p1namefontcolor = int_tab[1];
    variables->System.Vs_struct.p1namefontjust = int_tab[2];
    result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("Vs Screen","p2.name.font","3,0,0"));
    int_tab = (int*)calloc(5,sizeof(int));
    int_tab = convert_string(result);
    variables->System.Vs_struct.p2namefonti = int_tab[0];
    variables->System.Vs_struct.p2namefontcolor = int_tab[1];
    variables->System.Vs_struct.p2namefontjust = int_tab[2];
  }else{
    variables->System.Sndexist = 0;

    // 200 chars max, temporary while using kof91 routines for Mugen's character screen
    variables->System.Select_struct.char_list = (int*)calloc(200,sizeof(int));

    variables->System.Select_struct.type = 0;
    variables->System.Select_struct.posx = 0;
    variables->System.Select_struct.posy = 0;
    variables->System.Select_struct.loaded = 0;
    variables->System.Select_struct.p1_showed = 1;
    variables->System.Select_struct.p2_showed = 1;
    variables->System.Select_struct.p1_controller = 1;
    variables->System.Select_struct.p2_controller = 2;
    variables->System.Select_struct.p1startx = 0;
    variables->System.Select_struct.p1starty = 0;
    variables->System.Select_struct.p2startx = 0;
    variables->System.Select_struct.p2starty = 0;
    variables->System.Select_struct.p1_position.x = 0;
    variables->System.Select_struct.p1_position.y = 0;
    variables->System.Select_struct.p2_position.x = 0;
    variables->System.Select_struct.p2_position.y = 0;
    variables->System.Select_struct.p1_selecter = 0;
    variables->System.Select_struct.p2_selecter = 0;
    variables->System.Select_struct.p1_max_selecter = 1;
    variables->System.Select_struct.p2_max_selecter = 1;
    variables->System.Select_struct.bg_selected = 0;
    variables->System.Select_struct.bg_blinked = 0;
    variables->System.Select_struct.current_bg = 0;
    variables->System.Select_struct.stageposx = 160;
    variables->System.Select_struct.stageposy = 210;
    variables->System.Select_struct.stageactivefonti=0;
    variables->System.Select_struct.stageactive2fonti=0;
    variables->System.Select_struct.stagedonefonti=0;
    
    variables->System.Vs_struct.time = 100;
    variables->System.Vs_struct.currenttime = 0;
    variables->System.Vs_struct.fadeintime = 15;
    variables->System.Vs_struct.fadeouttime = 15;
    variables->System.Vs_struct.p1pos.x = 20;
    variables->System.Vs_struct.p1pos.y = 31;
    variables->System.Vs_struct.p2pos.x = 299;
    variables->System.Vs_struct.p2pos.y = 31;
    variables->System.Vs_struct.p1facing = 1;
    variables->System.Vs_struct.p2facing = -1;
    variables->System.Vs_struct.p1scalex = 1;
    variables->System.Vs_struct.p1scaley = 1;
    variables->System.Vs_struct.p2scalex = 1;
    variables->System.Vs_struct.p2scaley = 1;
    variables->System.Vs_struct.p1namepos.x = 79;
    variables->System.Vs_struct.p1namepos.y = 190;
    variables->System.Vs_struct.p2namepos.x = 240;
    variables->System.Vs_struct.p2namepos.y = 190;
  }
  
  free(message);
  //sensei_unset_config_file();

  return 0;
}//Read_system()
