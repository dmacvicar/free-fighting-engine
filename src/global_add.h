#ifndef GLOBAL_ADD_H
#define GLOBAL_ADD_H

#include "allegro.h"
#include "loader.h"

#define MAX_OF_PLAYERS 6
#define ITEM_NUMBER 11 
/** \file global_add.h
 * \brief new vars and struct used by Ze sensei's KOF 91
 */

int SENSEI_DEBUG_ON; 

typedef struct coordo_struct{
  int x;
  int y;
}coordo_struct;

/**
 * \brief Struct to know players input with booleans.
 *
 *  Struct to simply know human player input, without having to know if it's joy, key or anything<br>
 *  use : after called input_reader just test the state array that contain booleans
 *  call input->state[x]!=0 to know in witch state is the controller<br>
 *  state[0] = up ; state[1] = down ; state[2] = left ; state[3]=  right ;<br>
 *  state[4] = a ; state[5] = b ; state[6] = c ;<br>
 *  state[7] = x ; state[8] = y ; state[9] = z ;<br>
 *  state[10] = start
 */
typedef struct input{
  /* state def */
  /* 
     call input->state[x]!=0 to know in witch state is the controller<br>
     state[0] = up ; state[1] = down ; state[2] = left ; state[3]=  right<br>
     state[4] = a ; state[5] = b ; state[6] = c<br>
     state[7] = x ; state[8] = y ; state[9] = z<br>
     state[10] = start<br>
  */
  
  int state[11];
  /* key def */
  int keys[11];
  int joybuton[7];
  int use_joystick;

  int key_waited;
  int buton_waited;
  int wait_input;
}input;

/** \brief Music struct to stock music vars
 */
typedef struct music_struct{
  int type; // 0 = none ; 1 = midi ; 2 = mp3 ; 3 = cda
  int loaded;
  int loop;
  char * path;
}music_struct;

/**
 * \brief Structure to stock infos on engine configuration, needed by Game_variables struct
 */
typedef struct config{
  int Difficulty;
  int Life;
  int Time;
  int Game_speed; 

  int Debug_on; /* 0 or 1 */
  int Allow_debug; /* 0 or 1 */
  
  int Width; /* window/screen width */
  int Height; /* window/sceen height */
  int Depth;

  int Buffer_w; /* buffer/virutal-screen width */
  int Buffer_h; /* buffer/virtual-screen height */
  int Fullscreen; /* fullscreen or windowed */
  int Doubleres;	/* DoubleResolution mode */
  int Stretch; /* Stretch image or not */
  
  int Sound; /* do you want to install sound or not */
  int Midi_driver;
  int Digi_driver;
  int WavVolume;
  int MidiVolume;
}config;

/**
 * \brief Structure for backgrounds elements
 */
typedef struct background_elt_struct{
  char * elt_name;
  int elt_type; // 0 = normal ; 1 = anim , 3 = parallax
  int actionno;
  int spritenog; // sprite group
  int spritenoi; // sprite index
  int layerno;
  int startx;
  int starty;
  int deltax;
  int deltay;
  int trans;
  int mask;
  int tilex;
  int tiley;
  int tilespacex;
  int tilespacey;
  int windowx;
  int windowy;
  int windoww;
  int windowh;
  int xposition; //add : current absolute x position, changed by velset or axes in anim 
  int yposition; //add : current absolute y position, changed by velset or axes in anim
  int adj_xposition; // add : adjusted x position with sprite axis
  int adj_yposition; // add : adjusted y position with sprite axis;
  int tilew; // add
  int tileh; // add
  int velocityx;
  int velocityy;
}background_elt_struct; 

/**
 * \brief Structure to stock a Scene
 */
typedef struct scene_struct{
  char * name;
  int starttime;
  int currenttime;
  int endtime;
  char * bgm_path;
  int fadeintime;
  int fadeouttime;
  int layerallx;
  int layerally;
  background_elt_struct bg_array[10];
}scene_struct;

typedef struct clsn_struct{
  coordo_struct border1;
  coordo_struct border2;
}clsn_struct;

/**
 * \brief Structure to stock an Animation Element
 */
typedef struct animation_elt_struct{
  clsn_struct * clsn1;
  int nb_clsn1;
  clsn_struct * clsn2;
  int nb_clsn2;

  int spriteno;
  int groupeno;
  int x;
  int y;
  int time;
  int flipping; // 0:none 1:H 2:V 3:HV
  int trans;
  int current_time;
}animation_elt_struct;

/**
 * \brief Structure to stock an action
 */
typedef struct action_struct{
  clsn_struct * defaultclsn1;
  int nb_defaultclsn1;
  int frame_defaultclsn1;
  
  clsn_struct * defaultclsn2;
  int nb_defaultclsn2;
  int frame_defaultclsn2;

  int number;
  int loop_start;
  int anim_time;
  int current_element;
  int nb_elt;
  animation_elt_struct * animation_array;
}action_struct;


/** \brief Struct to store players cns vars, rules, etc...
 */
typedef struct cns_struct{
  int scalex;
  int scaley;
  
  int state;
  int statetime;
  
  int action; // current player action (anim)
  int elementno;
  int maxelement;
  int elementtime;
  int maxelementtime;
  int spri;
  int sprg;
  
  int ctrl;
  int type;
  int movetype;
  int time;
}cns_struct;

typedef struct KOF91Sprites{
  int group;
  int index;
  BITMAP * sprite;
  PALETTE pal;
}KOF91Sprites;

/** \brief players vars (input, datas (snd, pals...) and common vars
 *
 *  player variables , means both input entry , datas (sound, pals...) and vars
 */
typedef struct Player_variables{
  int loaded; // 0 = no ; 1 = yes
  input Player_input;
  int computer_input; // Is the player computer or not 
  int facing; // -1 facing left ; +1 facing right
  int has_control;
  int type; // 0 = no player ; 1 = KOF 91 char ; 2 = Mugen's Char
  char * def_path; // Or ini for KOF 91 chars

  KOF91Sprites * KOF91_sprites;
  int max_KOF91_sprites;
  SFFEntry * player_sff;
  char * name;
  char * display_name;
  char * author;
  
  char * cmd_path;
  char * cns_path;
  cns_struct cns;
  char * st_path;
  char * stcommon_path;
  char * sprite_path;
  char * anim_path;
  char * sound_path;
  char * pal1_path;
  char * pal2_path;
  char * pal3_path;
  char * pal4_path;
  char * pal5_path;
  char * pal6_path;
  char * pal7_path;
  char * pal8_path;
  char * pal9_path;

  action_struct * action_array;
  int action_number; // Size of action_array 

  int posx;
  int posy;
  
  RGB * pal; // Current pal
}Player_variables;

/**
 * \brief Structure for backgrounds
 */
typedef struct background_struct{
  SFFEntry * bg_sff;
  char * bg_path; // pcx, flc or .def path
  char * bg_sff_path;
  int bg_sff_path_known;
  char * name; //[BGnamedef]
  background_elt_struct * bg_elt_array;
  action_struct * action_array;
  int bg_elt_nb;
  int action_nb;
  int type; // 0 = none ; 1 = KOF 91 pcx ; 2 = KOF 91 flc ; 3 = Mugen's def
  int type_front; //(KOF 91 boolean)
  
  BITMAP * Pcx_back;
  BITMAP * Pcx_front;
  PALETTE Pal_back;
  PALETTE Pal_front;

  music_struct bg_music;

  int startx;
  int starty;

  int screenleft;
  int screenright;
  
  int camerax;
  int cameray;

  int p1startx;
  int p2startx;
  int p1starty;
  int p2starty;
  int p1facing;
  int p2facing;
  
  int zoffset;

  int loaded;
}background_struct;

/**
 * \brief Structure to stock a Mugen's storyboard
 */
typedef struct storyboard_struct{
  char * path;
  int startscene;
  SFFEntry * storyboard_sff;
  int nb_scene; // number of scenes in the storyboard
  int nb_actions; // number of actions in the storyboard
  int current_scene;
  scene_struct * scene_array;
  action_struct * action_array;
  int loaded;
  int ended;
}storyboard_struct;

/**
   \brief Structure for story variables (intro, ending, open...)
*/
typedef struct story_struct{
  char * Path;
  int Story_type; // 0 = none ; 1=flc; 2=*.def
  int StoryExist;
  int StoryEnded;
  int Running;
  char * Mp3Path;
  int Mp3Exist;
  music_struct story_music;
  storyboard_struct storyboard;
}story_struct;


/**
 * \brief Structure to references charcaters at select screen
 */
typedef struct char_ref_struct{
  int type; // 0 = none, 1 = KOF91, 2 = mugen
  char * path; // path to find .ini or .def file of the char
  char * name;
  char * display_name;
  BITMAP * b_pic; // Big picture
  BITMAP * s_pic; // Small picture
  PALETTE b_pic_pal; // for KOF 91 pcx
  PALETTE s_pic_pal; // for KOF 91 PCX
  RGB * b_pal; // from mugen's sff
  RGB * s_pal; // from mugen's sff
  int big_xaxis; // x axis (Mugen)
  int big_yaxis; // y axis (Mugen)
  int small_xaxis;
  int small_yaxis;
}char_ref_struct;

/** \brief Structure to references infos about bgs for select screen
 */
typedef struct bg_ref_struct{
  int type; // 0 = none, 1 = KOF91 PCX, 2 = KOF91 FLC, 3 = Mugen
  char * path; // path to find the pcx,flc or .def file for bgs
  char * display_name;
}bg_ref_struct;

/**
   \brief Structure to stock character_select screen vars
*/
typedef struct select_struct{
  int type; // 0 = kof91 ; 1 = mugen's type
  int loaded;
  int state; // 0 = select mode (team config) ; 1 = select character ; 2 = select stage
  SFFEntry * select_sff;
  char * sff_path;
  char_ref_struct * char_ref_array;
  bg_ref_struct * bg_ref_array;
  int * char_list; // list of chars as build with auto conf or read from select.def, to fill the tab index
  // Ex : 0 1 -1 2 0 1 1 mean the first char is empty, 2nd is the 1st entry of the char_ref_array , 3rd is the random select , etc...
  int * bg_list; // Same list but with backgrounds ref
  int nb_char; // number of characters in char_ref_array
  int s_nb_char; // number of chars in char_list
  int nb_bg; // nb of bgs
  
  coordo_struct p1_position; // current position of p1 cursor in select screen
  coordo_struct p2_position; // current position of p2 cursor in select screen
  int p1_showed; // 1 If p1 cursor and portrait have to be shown
  int p2_showed; // 1 If p2 cursor and portrait have to be shown
  int p1_controller; // 0 = computer , other = index of player who control p1 cursor
  int p2_controller; // 0 = computer , other = index of player who control p2 cursor
  int rows;
  int columns;
  int wrapping;
  int posx; // Used for mugen box and for KOF 91 moving blit
  int posy; // Used for mugen box and for KOF 91 moving blit
  int showemptyboxes;
  int moveoveremptyboxes;
  int cellsizex;
  int cellsizey;
  int cellspacing;
  int cellbgspri;
  int cellbgsprg;
  int cellrandi;
  int cellrandg;

  int p1startx;
  int p1starty;
  int p1activei;
  int p1activeg;
  int p1donei;
  int p1doneg;
  int p1movesndg;
  int p1movesndi;
  int p1donesndg;
  int p1donesndi;
  int p1randomsndg;
  int p1randomsndi;

  int p2startx;
  int p2starty;
  int p2activei;
  int p2activeg;
  int p2donei;
  int p2doneg;
  int p2movesndg;
  int p2movesndi;
  int p2donesndg;
  int p2donesndi;
  int p2randomsndg;
  int p2randomsndi;
  
  int stagemovesndg;
  int stagemovesndi;
  int stagedonesndg;
  int stagedonesndi;
  int cancelsndg;
  int cancelsndi;
  
  int portraitoffsetx;
  int portraitoffsety;
  double portraitscalex;
  double portraitscaley;

  int titleoffsetx;
  int titleoffsety;
  int titlefonti;
  int titlefontcolor;
  int titlefontjust;

  int p1faceoffsetx;
  int p1faceoffsety;
  double p1facescalex;
  double p1facescaley;
  int p1facefacing;
  int p1nameoffsetx;
  int p1nameoffsety;
  int p1namefonti;
  int p1namefontcolor;
  int p1namefontjust;
  
  int p2faceoffsetx;
  int p2faceoffsety;
  int p2facescalex;
  double p2facescaley;
  double p2facefacing;
  int p2nameoffsetx;
  int p2nameoffsety;
  int p2namefonti;
  int p2namefontcolor;
  int p2namefontjust;

  int p1_max_selecter; // Max of players that player 1 can select
  int p1_selected[4]; // ref to index of players selected by player 1 as stored in the char_list
  int p1_selecter; //range of the player as selected by player 1 (1st of the group or 2nd...)
  int p2_max_selecter; // Max of players that player 2 can select
  int p2_selected[4]; // same but for player 2
  int p2_selecter;
  
  int stage_showed;
  int stageposx;
  int stageposy;
  int stageactivefonti;
  int stageactivefontcolor;
  int stageactivefontjust;
  int stageactive2fonti;
  int stageactive2fontcolor;
  int stageactive2fontjust;
  int stagedonefonti;
  int stagedonefontcolor;
  int stagedonefontjust;
  int bg_blinked; // !=0 if the blinked color is used
  int current_bg; // index of the selected bg ; after select_screen it became the bg to load
  int bg_selected; //0 = no
  int stage_controller; // 0=IA ; 1=P1 ; 2=P2
  int * bg_used; // array of bgs to use numbers refers to bg_ref_array

  BITMAP * faces;
}select_struct;

/** \brief structure to stock infos on vs screen
 */
typedef struct vs_struct{
  int state; // 0 = showing faces ; 1 = loading p1 ; 2 = loading p2 ; 3 = loading p3 etc...
  int time;
  int currenttime;
  int fadeintime;
  int fadeouttime;
  coordo_struct p1pos;
  int p1facing;
  double p1scalex;
  double p1scaley;
  coordo_struct p1namepos;
  int p1namefonti;
  int p1namefontcolor;
  int p1namefontjust;
  coordo_struct p2pos;
  int p2facing;
  double p2scalex;
  double p2scaley;
  coordo_struct p2namepos;
  int p2namefonti;
  int p2namefontcolor;
  int p2namefontjust;
}vs_struct;

/**
 * \brief Structure to stock infos on menu screen, used in Game_variables struct
 */
typedef struct system_struct{
  char ** itemname;
  int posx;
  int posy;
  int itemfontnumber;
  int itemfontcolor;
  int itemfontalignement;
  int itemactivefontnumber;
  int itemactivefontcolor;
  int itemactivefontalignement;
  int itemspacingx;
  int itemspacingy;
  int windowsmarginx;
  int windowsmarginy;
  int boxvisible;
  int visibleitems;
  int boxcoordsx;
  int boxcoordsy;
  int boxcoordsw;
  int boxcoordsh;
  int currentitem;
  int firstitem; /* first item in list to show */
   
  int transeffect; //how much the box is transparent 
  int transadd;  //do we wish to increase or decrease transparency 
  int boxposition; // how many item do we pass through
   
  //Same for option
  int Ocurrentitem; //Option item (2 players)
  int Ocurrentitem2; //Option item (player 2 only)
  int Otranseffect; //how much the box is transparent 
  int Otransadd;  //do we wish to increase or decrease transparency 
   
  story_struct Intro; //ie Mugen's logo
  story_struct Open;  //ie Mugen's intro
  story_struct Ending;
  story_struct Credits;   

  //system fonts data, max 9 fonts, not an array cause I was lazy
  FNTInfo* fontInfo0;
  int font0exist;
  FNTInfo* fontInfo1;
  int font1exist;
  FNTInfo* fontInfo2;
  int font2exist;
  FNTInfo* fontInfo3;
  int font3exist;
  FNTInfo* fontInfo4;
  int font4exist;
  FNTInfo* fontInfo5;
  int font5exist;
  FNTInfo* fontInfo6;
  int font6exist;
  FNTInfo* fontInfo7;
  int font7exist;
  FNTInfo* fontInfo8;
  int font8exist;
  FNTInfo* fontInfo9;
  int font9exist;
 
  // system infos
  char * select_path; //Path to find select.def file
  char * fight_path; //Path to find fight.def file

  //System sound
  char * Sndpath;
  SNDCollection *Systemsnd;
  int Sndexist;

  // Menu sounds
  int Mvcursorgrp;
  int Mvcursornb;
  int Donecursorgrp;
  int Donecursornb;
  int Cancelgrp;
  int Cancelnb;

  //Option sound
  int OMvcursorgrp;
  int OMvcursornb;
  int ODonecursorgrp;
  int ODonecursornb;
  int OCancelgrp;
  int OCancelnb;

  //System musics
  music_struct title_music;
  music_struct select_music;
  music_struct vs_music;
  
  //Title Background
  background_struct Title_bg;
   
  //Option Background
  background_struct Option_bg;

  //Seelect Background
  background_struct Select_bg;
   
  //Vs background
  background_struct Vs_bg;

  // Structure to stock info on character select screen
  select_struct Select_struct;

  // Structure to stock info on character vs screen
  vs_struct Vs_struct;

}system_struct;

/** \brief   Structure to know state of specials keys, needed by Game_variables struct
 */
typedef struct function_keys{
  int Esc; /* boolean to know if esc is pressed or not */
  int F1; // debug on/of
  int F2; // Change keys in key config
  int F12; // Take screenshot
}function_keys;

/** \brief Struct to know how the battle is going on
 */
typedef struct battle_struct{
  int current_round;
  int fixed_players; // Fill players vars with bgs values (pos, scale...)
  int round_loaded;
  int round_over;
  int time;
}battle_struct;

/** \brief main structure of game vars
 */
struct Game_variables{
  int Game_state; /* state of the engine see docs/automat.gif for details*/
  char * Path; /* Root to find data files see 'motif' in readme*/
  config Game_config; /* game config from 'kof91.cfg' file*/
  system_struct System; /* values from 'system.def' file*/
  
  //Title Background
  background_struct Fight_bg; /* BG to fight in */
  
  //Battle infos
  battle_struct battle;
  
  function_keys f_keys; // values of functions keys 
  int not_show; // debug variable 'cause code isn't clean 
  int fps; // Frame per second, for info
  
};
typedef struct Game_variables * Game_variables;
#endif /* GLOBAL_ADD_H */
