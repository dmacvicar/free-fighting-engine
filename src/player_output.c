#include "player_output.h"
#include "background_output.h"
#include "macros.h"
#include "logger.h"
#include "allegro.h"
#include "sensei_config.h"

int player_output(Game_variables variables,Player_variables * player_array,int time){
  char * message;
  BITMAP * test = NULL;
  int act_index = -1;
  int x = 0;
  int y = 0;
  int i;
  int k;
  int group;
  int number;
  int element;

  message = (char*)calloc(255,sizeof(char));
  if (SENSEI_DEBUG_ON)
    TRON("begin player_output");
  for (i=0;i<4;i++){
    if (player_array[i].type!=0){
      act_index = -1;
      for (j=0;j<player_array[i].action_number;j++){
	if (player_array[i].action_array[j].number==0)
	  act_index = j;
      }
      if (act_index!=-1){
	element = player_array[i].action_array[act_index].current_element;
	group = player_array[i].action_array[act_index].animation_array[element].groupeno;
	number = player_array[i].action_array[act_index].animation_array[element].spriteno;
	switch (player_array[i].type){
	case 1: // KOF 91
	  test = sensei_kof91_fill_bmp(player_array[i].KOF91_sprites,group,number,player_array[i].max_KOF91_sprites,&x,&y,player_array[i].facing);
	  break;
	case 2 : // Mugen
	  test = sensei_fill_bmp_uncolored(player_array[i].player_sff,group,number,1,&x,&y,player_array[i].pal,player_array[i].facing);
	  break;
	default :
	  test = NULL;
	  break;
	}
	
	if (player_array[i].facing>0){
	  draw_sprite(virtscreen,test,160 + player_array[i].posx - x, player_array[i].posy - y);
	  if (SENSEI_DEBUG_ON){
	    for (k=0;k<player_array[i].action_array[act_index].animation_array[element].nb_clsn2;k++){
	      TRON("Showing clsn2");
	      drawing_mode(DRAW_MODE_SOLID,NULL,0,0);
	      rect(virtscreen,160 + player_array[i].posx + player_array[i].action_array[act_index].animation_array[element].clsn2[k].border1.x,player_array[i].posy + player_array[i].action_array[act_index].animation_array[element].clsn2[k].border1.y,160 + player_array[i].posx + player_array[i].action_array[act_index].animation_array[element].clsn2[k].border2.x,player_array[i].posy + player_array[i].action_array[act_index].animation_array[element].clsn2[k].border2.y,makecol(0,0,255));
	    }
	  }
	}
	else{
	  draw_sprite(virtscreen,test,160 + player_array[i].posx + x - test->w, player_array[i].posy - y);
	  if (SENSEI_DEBUG_ON){
	    for (k=0;k<player_array[i].action_array[act_index].animation_array[element].nb_clsn2;k++){
	      TRON("Showing clsn2"),
		rect(virtscreen,160 + player_array[i].posx - player_array[i].action_array[act_index].animation_array[element].clsn2[k].border1.x,player_array[i].posy + player_array[i].action_array[act_index].animation_array[element].clsn2[k].border1.y,160 + player_array[i].posx - player_array[i].action_array[act_index].animation_array[element].clsn2[k].border2.x,player_array[i].posy + player_array[i].action_array[act_index].animation_array[element].clsn2[k].border2.y,makecol(0,0,255));
	    }
	  }
	}
      }
      if (test!=NULL)
	destroy_bitmap(test);
    }
    x = 0;
    y = 0;
  }
  
  free(message);
  return 0;
}// player_output
