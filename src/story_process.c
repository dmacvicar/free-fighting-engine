#include "story_process.h"
#include "storyboard_process.h"
#include "main_process.h"
#include "global_add.h"
#include "global.h"
#include "mp3.h"
#include "logger.h"
#include "macros.h"
#include "config.h"

#include <stdio.h>

/** \file story_process.c
 * \brief functiosn to deal with storys : KOF 91 flc and Mugen's one
 */

int init_story(story_struct * a_story, Player_variables * player_array, int time){
  mp3status = 0;
  
  if (a_story->Mp3Exist){
    MP3_Open(a_story->Mp3Path);
    MP3_Play();
    mp3status = 1;
  }
  
  switch (a_story->Story_type){
  case 1:
    if (open_fli(a_story->Path)!=FLI_OK){
      TRON("Error opening story");
      return -1;
    }
    else
      TRON("Initialisation of story");
    break;
  default:
  TRON("Initialisation of this story type impossible");
  break;
  }

  a_story->StoryEnded = 0;
  a_story->Running = 1;
  return 0;
}//init_story

int continue_story(story_struct * a_story, Player_variables * player_array, int time){
  if (mp3status)
    poll_mp3_file(mp3);
  
  switch (a_story->Story_type){
  case 1:
    if (next_fli_frame(0)==FLI_OK){
      if (fli_timer>=0)
	reset_fli_variables();
    }else{
      a_story->StoryEnded = 1;
    }
    break;
  default:
    break;
  }
  return 0;
} //continue_story

int free_story(story_struct * a_story){
  TRON("Free story");
  if (mp3status){
     MP3_Close();
     mp3status=0;
  }
  
  switch (a_story->Story_type){
  case 1:
    close_fli();
    break;
  case 2:
    free(a_story->storyboard.storyboard_sff);
    break;
  default:
    break;
  }
  
  a_story->StoryEnded = 1;
  return 0;
} //free_story

int story_process(Game_variables variables, Player_variables * player_array, story_struct * a_story, int time){
  int error;
  char * message;
  message = (char*)malloc(255*sizeof(char));
  error = 0;  
  if (SENSEI_DEBUG_ON){
    sprintf(message,"Story process State %d",variables->Game_state);
    TRON(message);
  }
  
  if (a_story->StoryExist==1){
    if (SENSEI_DEBUG_ON){
      sprintf(message,"A story exists");
      TRON(message);
    }
    switch (a_story->Story_type){
    case 1 :
      if (SENSEI_DEBUG_ON)
	TRON("FLC story");
      if (a_story->Running==0){
	if (SENSEI_DEBUG_ON){
	  sprintf(message,"Initialisation %s",a_story->Path);
	  TRON(message);
	  error = init_story(a_story,player_array,time);
	  variables->not_show = 1;
	}
      }else{
	if (a_story->StoryEnded==0)
	  error = continue_story(a_story,player_array,time);
	else{
	  error = free_story(a_story);
	  next_state(variables);
	  variables->not_show=1;
	} 
      }
      break;
    case 2:
      if (SENSEI_DEBUG_ON)
	TRON("Mugen's storyboard");
      process_storyboard(&a_story->storyboard);
      break;
    default :
      if (SENSEI_DEBUG_ON)
	TRON("Strange story type");
      break;
    }
  }
  else{
    if (SENSEI_DEBUG_ON){
      sprintf(message,"A story %s not exists",a_story->Path);
      TRON(message);
    }
    next_state(variables);
    variables->not_show=1;
    return 0;
  }
  
  if ((variables->f_keys.Esc==1)||(validation(player_array))||(a_story->storyboard.ended)){
    TRON("story ended");
    variables->f_keys.Esc=0;
    error = free_story(a_story);
    rest(50);
    next_state(variables);
    variables->not_show =1;
  }
  
  free(message);

  if (error)
    return -1;
  else
    return 0;
}

