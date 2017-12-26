#include <stdio.h>
#include "storyboard_process.h"
#include "main_process.h"
#include "sensei_config.h"
#include "string.h"

#include "macros.h"
#include "logger.h"
/** \file storyboard_process.c
 * \brief Functions to deal with Mugen's storyboard stored in storyboard_struct
 */

int process_storyboard(storyboard_struct * a_storyboard){
  char * message;
  //char * sff_path;
  char * result;
  int * tab_result;
  int nb_scenes,i,j,ze_scene,act_index;
  char ** scenes_names;
  char * real_scene_name;
  char * real_layer_name;
  int * action_nb; //array with the index of each action find
  int action_max;
  char * real_sff_path;
  
  message = (char*)calloc(255,sizeof(char));
  real_scene_name = (char*)calloc(255,sizeof(char));
  real_layer_name = (char*)calloc(255,sizeof(char));
  scenes_names = NULL;
  action_nb = NULL;
  action_max = 0;
  tab_result = NULL;

  TRON("begin storyboard");
  if (!a_storyboard->loaded){
    //TRON("loading storyboard");
    //sff_path = strcpy((char*)calloc(255,sizeof(char)),extract_path(a_storyboard->path));
    //sprintf(message,"storyboard file = %s",a_storyboard->path);
    //TRON(message);
    sensei_set_config_file(a_storyboard->path);
    //TRON("after sensei_set...");
    real_sff_path = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("scenedef","spr",""));
    
    if (exists(real_sff_path)){
      if (SENSEI_DEBUG_ON){
	sprintf(message,"Loading %s for scenedef",real_sff_path);
	TRON(message);
      }
      a_storyboard->storyboard_sff = sffLoad(real_sff_path);
      TRON("after sff loading");
    }
    else{
      real_sff_path = strcpy((char*)calloc(255,sizeof(char)),extract_path(a_storyboard->path));
      put_backslash(real_sff_path);
      real_sff_path = strcat(real_sff_path,sensei_get_config_string("scenedef","spr",""));
      if (exists(real_sff_path)){
	if (SENSEI_DEBUG_ON){
	  sprintf(message,"Loading %s for scenedef",real_sff_path);
	  TRON(message);
	}
	a_storyboard->storyboard_sff = sffLoad(real_sff_path);
	TRON("after sff loading");
      }else{
	sprintf(message,"warning no %s for bg sff",real_sff_path);
	TRON(message);
	a_storyboard->ended = 1;
	return 0;
      }
    }
    
    scenes_names = fill_scenes_names(&nb_scenes);
    a_storyboard->nb_scene = nb_scenes;
    a_storyboard->scene_array = (scene_struct*)realloc(a_storyboard->scene_array,nb_scenes*sizeof(scene_struct));
    action_nb = fill_action_nb(&action_max);
    a_storyboard->nb_actions = action_max;
    a_storyboard->action_array = (action_struct*)realloc(a_storyboard->action_array,nb_scenes*sizeof(action_struct));
    sprintf(message,"find %i scenes and %i actions in %s",nb_scenes,action_max,a_storyboard->path);
    TRON(message);
    a_storyboard->ended = 0;
    
    
    for (i=0;i<action_max;i++){
      a_storyboard->action_array[i].number = action_nb[i];
      sprintf(message,"putting index = %i for the %i action_array.number",action_nb[i],i);
      TRON(message);
      fill_action(&a_storyboard->action_array[i]);
    }
    
    a_storyboard->startscene = sensei_get_config_int("scenedef","startscene",0);

    // filling each scene
    for (i=0;i<nb_scenes;i++){
      a_storyboard->scene_array[i].name = strcpy((char*)calloc(255,sizeof(char)),scenes_names[i]);
      sprintf(real_scene_name,"scene %s",a_storyboard->scene_array[i].name);
      TRON(real_scene_name);
      a_storyboard->scene_array[i].currenttime = 0;
      a_storyboard->scene_array[i].endtime = sensei_get_config_int(real_scene_name,"end.time",0);
      result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string(real_scene_name,"layerall.pos","0,0"));
      tab_result = convert_string(result);
      a_storyboard->scene_array[i].layerallx = tab_result[0];
      a_storyboard->scene_array[i].layerally = tab_result[1];
      // filling each layer of a scene
      for (j=0;j<10;j++){
	real_layer_name = (char*)calloc(255,sizeof(char));
	sprintf(real_layer_name,"layer%i.anim",j);
	a_storyboard->scene_array[i].bg_array[j].actionno = sensei_get_config_int(real_scene_name,real_layer_name,-1);
	sprintf(real_layer_name,"layer%i.offset",j);
	result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string(real_scene_name,real_layer_name,"0,0"));
	tab_result = convert_string(result);
	a_storyboard->scene_array[i].bg_array[j].xposition = a_storyboard->scene_array[i].layerallx + tab_result[0];
	a_storyboard->scene_array[i].bg_array[j].yposition = a_storyboard->scene_array[i].layerally + tab_result[1];
	a_storyboard->scene_array[i].bg_array[i].elt_type = 1;
      }
    }
    
    // litle debug function
    if (SENSEI_DEBUG_ON){
      for (i=0;i<a_storyboard->nb_scene;i++){
        sprintf(message,"scene %i",i);
	TRON(message);
	sprintf(message,"layerall.pos = %i, %i",a_storyboard->scene_array[i].layerallx,a_storyboard->scene_array[i].layerally);
	TRON(message);
	sprintf(message,"end.time = %i",a_storyboard->scene_array[i].endtime);
	TRON(message);
	for (j=0;j<10;j++){
	  sprintf(message,"layer%i.anim = %i",j,a_storyboard->scene_array[i].bg_array[j].actionno);
	  TRON(message);
	  sprintf(message,"layer real offset = %i,%i",a_storyboard->scene_array[i].bg_array[j].xposition,a_storyboard->scene_array[i].bg_array[j].yposition);
	  TRON(message);
	}
      }
    }
    
    sensei_unset_config_file();
    a_storyboard->loaded = 1;
    free(real_layer_name);
  }
  
  ze_scene = a_storyboard->current_scene;
  
  if (a_storyboard->loaded){
    TRON("processing storyboard");
    a_storyboard->scene_array[ze_scene].currenttime++;
    sprintf(message,"scene %i time %i",a_storyboard->current_scene,a_storyboard->scene_array[ze_scene].currenttime);
    TRON(message);
    if (a_storyboard->scene_array[ze_scene].currenttime>a_storyboard->scene_array[ze_scene].endtime)
      a_storyboard->current_scene++;
    if (a_storyboard->current_scene>a_storyboard->nb_scene){
      a_storyboard->ended = 1;
      return 0;
    }
    // Deal with each layer of the scene
    for (i=0;i<10;i++){
      act_index = -1;
      if (a_storyboard->scene_array[ze_scene].currenttime>0){
	for (j=0;j<a_storyboard->nb_actions;j++){
	    if (a_storyboard->action_array[j].number==a_storyboard->scene_array[ze_scene].bg_array[i].actionno)
	      act_index = j;
	  }
	sprintf(message,"act index = %i and were looking for %i",act_index,a_storyboard->scene_array[ze_scene].bg_array[i].actionno);
	TRON(message);
	if (act_index!=-1){
	   if (a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].time>=0){
	    TRON("time>=0");
	  a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].current_time++;
	  if  (a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].current_time>a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].time){
	    TRON("current_element++");
	    a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].current_time = 0;
	    a_storyboard->action_array[act_index].current_element++;
	  }
	  if (a_storyboard->action_array[act_index].current_element>=a_storyboard->action_array[act_index].nb_elt)
	    a_storyboard->action_array[act_index].current_element = a_storyboard->action_array[act_index].loop_start;
	  }
	  
	  a_storyboard->scene_array[ze_scene].bg_array[i].spritenoi = a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].spriteno;
	  a_storyboard->scene_array[ze_scene].bg_array[i].spritenog = a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].groupeno;
	  //sprintf(message,"puting sprite %i,%i, into scene %i layer %i", a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].spriteno,a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].groupeno,ze_scene,i);
	  sprintf(message,"putting sprite %i,%i, into scene %i, layer %i", a_storyboard->scene_array[ze_scene].bg_array[i].spritenog,  a_storyboard->scene_array[ze_scene].bg_array[i].spritenoi, ze_scene, i);
	  TRON(message);
	}else{
	  a_storyboard->scene_array[ze_scene].bg_array[i].spritenoi = -1;
	  a_storyboard->scene_array[ze_scene].bg_array[i].spritenog = -1;
	  sprintf(message,"putting sprite %i,%i, into scene %i, layer %i", a_storyboard->scene_array[ze_scene].bg_array[i].spritenog,  a_storyboard->scene_array[ze_scene].bg_array[i].spritenoi, ze_scene, i);
	  //sprintf(message,"puting sprite %i,%i, into scene %i layer %i", a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].spriteno,a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].groupeno,ze_scene,i);
	  TRON(message);
	}
      }
    }
  }else{
    TRON("warning a storyboard not loaded");
  }
  
  free(message);
  free(real_layer_name);
  free(real_scene_name);
  if (action_nb!=NULL)
    free(action_nb);
  if (scenes_names!=NULL){
    for (i=0;i<nb_scenes;i++){
      free(scenes_names[i]);
    }
    free(scenes_names);
  }
  return 0;
}
