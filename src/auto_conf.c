#include "auto_conf.h"
#include "global.h"
#include <string.h>
#include "allegro.h"
#include "config.h"
#include "macros.h"
#include "logger.h"
#include "loads.h"
#include "sensei_config.h"
#include <stdio.h>

/** \file auto_conf.c
 * \brief initialize old KOF 91 vars depending of the environnement
 *
 * Initialize debug font, intro.flc , open.flc , title.pcx
 */

/** \brief function that initialize Game_variables
 *
 */
int get_env(Game_variables variables){
  char * a_path;
  char * message;
  int error = 0;
  a_path = (char*)calloc(255,sizeof(char));
  message = (char*)calloc(255,sizeof(char));
  
  /************************* LOAD fonts **************************/
  //TRON("Loads debug font");
  if (exists("fonts.dat")){
    fonts_dat = load_datafile ( "fonts.dat" );
    font = fonts_dat[ 0 ].dat;
  }

  if (exists("font/f-4x6.fnt")){
    fontInfo = fntLoadFont("font/f-4x6.fnt");
    font = fontInfo->font;
  }
  
  small_font = font;
  /****************************************************************/
  
  // Testing if intro.flc is in base directory or in 'motif' directory
  a_path = check_path("intro.flc",variables->Path,"Intro.flc",&error);
  if (error==0){
    variables->System.Intro.Path = strcpy((char*)calloc(255,sizeof(char)),a_path);
    variables->System.Intro.Story_type = 1;
    variables->System.Intro.StoryExist = 1;
    variables->System.Intro.Running = 0;
  }else{
    variables->System.Intro.Story_type = 0;
    variables->System.Intro.StoryExist = 0;
    variables->System.Intro.Running = 0;
  }

  // Testing if open.flc is in base directory or in 'motif' directory
  a_path = check_path("open.flc",variables->Path,"Open.flc",&error);
  if (error==0){
    variables->System.Intro.Path = strcpy((char*)calloc(255,sizeof(char)),a_path);
    variables->System.Intro.Story_type = 1;
    variables->System.Intro.StoryExist = 1;
    variables->System.Intro.Running = 0;
  }else{
    variables->System.Intro.Story_type = 0;
    variables->System.Intro.StoryExist = 0;
    variables->System.Intro.Running = 0;
  }
  
  // Testing if intro.mp3 is in base directory or in 'motif' directory
  a_path = check_path("intro.mp3",variables->Path,"Intro.mp3",&error);
  if (error==0){
    variables->System.Intro.story_music.path = strcpy((char*)calloc(255,sizeof(char)),a_path);
    variables->System.Intro.story_music.type = 2;
    variables->System.Intro.story_music.loop = 0;
    variables->System.Intro.story_music.loaded = 0;
  }else{
    variables->System.Intro.story_music.type = 0;
  }
  
  // Testing if title.pcx exists and then implement it
  a_path = check_path("title.pcx",variables->Path,"Title.pcx",&error);
  if (error==0){
    variables->System.Title_bg.type = 1;
    variables->System.Title_bg.bg_path = strcpy((char*)calloc(255,sizeof(char)),a_path);
    variables->System.Title_bg.loaded = 0;
    variables->System.Option_bg.type = 1;
    variables->System.Option_bg.bg_path = strcpy((char*)calloc(255,sizeof(char)),a_path);
    variables->System.Option_bg.loaded = 0;
  }else{
    variables->System.Title_bg.type = 0;
    variables->System.Option_bg.type = 0;
  }
  
  // Testing if vs.pcx exists and then implement it
  variables->System.Vs_bg.type = 0;
  a_path = check_path("vs.pcx",variables->Path,"Vs.pcx",&error);
  if (error==0){
    variables->System.Vs_bg.type = 1;
    variables->System.Vs_bg.bg_path = strcpy((char*)calloc(255,sizeof(char)),a_path);
    variables->System.Vs_bg.loaded = 0;
  }else{
    variables->System.Vs_bg.type = 0;
  }
  
  // Testing if there's a pattern pcx for select screen and then implement it
  variables->System.Select_bg.type = 0;
  a_path = strcpy((char*)calloc(255,sizeof(char)),"sprites/pattern.pcx");
  a_path = fix_filename_slashes(a_path);
  if (exists(a_path)){
    variables->System.Select_bg.type = 1;
    variables->System.Select_bg.bg_path = strcpy((char*)calloc(255,sizeof(char)),a_path);
    variables->System.Select_bg.loaded = 0;
  }else{
    a_path = check_path("pattern.pcx",variables->Path,"Pattern.pcx",&error);
    if (error==0){
      variables->System.Select_bg.type = 1;
      variables->System.Select_bg.bg_path = strcpy((char*)calloc(255,sizeof(char)),a_path);
      variables->System.Select_bg.loaded = 0;
    }
  }
  
  // testing if there's a title/select bgm
  message = (char*)calloc(255,sizeof(char));
  a_path = strcpy((char*)calloc(255,sizeof(char)),"midi/select.mid\0");
  a_path = fix_filename_slashes(a_path);
  if (exists(a_path)!=0){
    variables->System.title_music.path = strcpy((char*)calloc(255,sizeof(char)),a_path);
    variables->System.title_music.type = 1;
    variables->System.title_music.loop = 1;
    variables->System.select_music.path = strcpy((char*)calloc(255,sizeof(char)),a_path);
    variables->System.select_music.type = 1;
    variables->System.select_music.loop = 1;
    if (SENSEI_DEBUG_ON){
      sprintf(message,"Select.mid found at %s",a_path);
      TRON(message);
    }
  }else{
    a_path = check_path("select.mid",variables->Path,"Select.mid",&error);
    if (error==0){
      variables->System.title_music.path = strcpy((char*)calloc(255,sizeof(char)),a_path);
      variables->System.title_music.type = 1;
      variables->System.title_music.loop = 1;
      variables->System.select_music.path = strcpy((char*)calloc(255,sizeof(char)),a_path);
      variables->System.select_music.type = 1;
      variables->System.select_music.loop = 1;
    }else{
      variables->System.title_music.type = 0;
      variables->System.select_music.type = 0;
    }
  }
  
  free(message);
  free(a_path);
  
  return 0;
} //get_env()
