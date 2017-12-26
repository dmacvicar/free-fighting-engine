#include "storyboard_output.h"

#include "macros.h"
#include "logger.h"
#include "stdio.h"

/** \file storyboard_output.c
 * \brief functions to show Mugen's storyboard
 */

int storyboard_output(storyboard_struct * a_storyboard){
  char * message;
  static SFFEntry * cur;
  static SFFEntry * pal_cur;
  int i,j,xposition,yposition,ze_scene;
  BITMAP * a_sprite = NULL;
  int act_index = 0;
  RGB trans = { 63 , 0 , 63 }; //magenta for translucy in true color mode
  /* RGB -> color mapping table. Not needed, but speeds things up */
  int spr_position = 0; // to find the right pal juste before the unfounded one
  RGB * a_pal;
  TRON("storyboard output");
  message = (char*)calloc(255,sizeof(char));
  i=0;
  cur = malloc(sizeof(SFFEntry));
  pal_cur = malloc(sizeof(SFFEntry));
  ze_scene = a_storyboard->current_scene;
  sprintf(message,"loading for %i g = %i et i = %i",i,a_storyboard->scene_array[ze_scene].bg_array[i].spritenog,a_storyboard->scene_array[ze_scene].bg_array[i].spritenoi);
  TRON(message);
  for (i=0;i<10;i++){// for each layer
    
    // finding the right sprite
    cur = a_storyboard->storyboard_sff;
    while ((cur->next)&&((cur->group!=a_storyboard->scene_array[ze_scene].bg_array[i].spritenog)||(cur->curIndex!=a_storyboard->scene_array[ze_scene].bg_array[i].spritenoi))){
      cur = cur->next;
      spr_position++;
    }
    sprintf(message,"loaded for %i , grp = %i and index = %i (and prevIndex = %i) and were looking for g = %i et i = %i",i,cur->group,cur->curIndex,cur->prevIndex,a_storyboard->scene_array[ze_scene].bg_array[i].spritenog,a_storyboard->scene_array[ze_scene].bg_array[i].spritenoi);
    TRON(message);
    
    /*
     * Little fix for missing sprites
     */
    if ((cur->group!=a_storyboard->scene_array[ze_scene].bg_array[i].spritenog)||(cur->curIndex!=a_storyboard->scene_array[ze_scene].bg_array[i].spritenoi)){
      if (SENSEI_DEBUG_ON){
	sprintf(message,"No sprite for %i, %i",a_storyboard->scene_array[ze_scene].bg_array[i].spritenog,a_storyboard->scene_array[ze_scene].bg_array[i].spritenoi);
	TRON(message);
      }
      continue;
    }else{
      if ((cur->image==NULL)){
	sprintf(message,"No image for %i, %i",a_storyboard->scene_array[ze_scene].bg_array[i].spritenog,a_storyboard->scene_array[ze_scene].bg_array[i].spritenoi);
	TRON(message);
	continue;
      }
      else
	a_sprite = create_bitmap(cur->image->w,cur->image->h);
      //TRON("after create bitmap");
    }
    
    // looking for a pal 
    if ((cur->pal)&&(cur->image!=NULL)){
      //TRON("a pal");
      set_palette(cur->pal);
      a_pal = cur->pal;
    }else{ // finding a valid pal
      if (cur->image==NULL)
	{
	  set_palette(default_palette);
	  a_pal = default_palette;
	}else{
	TRON("not a pal");
	pal_cur = cur;
	while ((!pal_cur->pal)&&(spr_position>=0)){
	  TRON("searching a pal");
	  pal_cur = a_storyboard->storyboard_sff;
	  for (j=0;j<spr_position;j++)
	    pal_cur = pal_cur->next;
	  spr_position--;
	}
	
	if (pal_cur->pal){
	  TRON("waow a pal");
	  set_palette(pal_cur->pal);
	  a_pal = pal_cur->pal;
	}else{
	  set_palette(default_palette);
	  a_pal = default_palette;
	}
      }
    }
    
    // For storyboard there's only anim
    set_color(0,&trans);
    set_color_conversion(COLORCONV_NONE);

    // looking in action array to find the right index
    act_index = -1;
    for (j=0;j<a_storyboard->nb_actions;j++){
      if (a_storyboard->action_array[j].number==a_storyboard->scene_array[ze_scene].bg_array[i].actionno)
	act_index = j;
    }
  
    if (act_index!=-1){
      TRON("act index!=-1");
      a_storyboard->scene_array[ze_scene].bg_array[i].adj_xposition = a_storyboard->scene_array[ze_scene].bg_array[i].xposition - cur->x; // + 160; 
      a_storyboard->scene_array[ze_scene].bg_array[i].adj_yposition = a_storyboard->scene_array[ze_scene].bg_array[i].yposition - cur->y; 	  
      a_storyboard->scene_array[ze_scene].bg_array[i].adj_xposition = a_storyboard->scene_array[ze_scene].bg_array[i].adj_xposition + a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].x;
      a_storyboard->scene_array[ze_scene].bg_array[i].adj_yposition = a_storyboard->scene_array[ze_scene].bg_array[i].adj_yposition + a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].y;
    
      xposition =  a_storyboard->scene_array[ze_scene].bg_array[i].adj_xposition;
      yposition =  a_storyboard->scene_array[ze_scene].bg_array[i].adj_yposition;

      if ((cur->image!=NULL)&&(cur->group==a_storyboard->scene_array[ze_scene].bg_array[i].spritenog)&&(cur->curIndex==a_storyboard->scene_array[ze_scene].bg_array[i].spritenoi)){
	if (a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].flipping==0){
	  draw_sprite(virtscreen,cur->image,xposition,yposition);
	}else{
	  switch (a_storyboard->action_array[act_index].animation_array[a_storyboard->action_array[act_index].current_element].flipping){
	  case 1:
	    draw_sprite_h_flip(virtscreen,cur->image,xposition,yposition);
	    break;
	  case 2:
	    draw_sprite_v_flip(virtscreen,cur->image,xposition,yposition);
	    break;
	  case 3:
	    draw_sprite_vh_flip(virtscreen,cur->image,xposition,yposition);
	    break;
	  default:
	    break;
	  }
	}
      }
    }
  
  }//end of each layer
  
  destroy_bitmap(a_sprite);
  cur = a_storyboard->storyboard_sff;
  free(message);
  free(cur);
  
  return 0;
}
