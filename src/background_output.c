#include <stdio.h>
#include <stdlib.h>
#include "allegro.h"

#include "background_output.h"

#include "global.h"
#include "sensei_config.h"
#include "macros.h"
#include "logger.h"

/** \file background_output.c
 * \brief Put each layer on the virtscreen (src)
 */

/** \brief function to blit a mapped bg on virtscreen
 */
int mugen_tiled_bg(background_struct * a_background,int i,BITMAP * a_sprite, RGB * a_pal){
  char * message;
  int j,xposition,yposition,blitx,blity;
  int patternx,patterny;
  int nb_tilex,nb_tiley;
  int spacex,spacey;
  
  message = (char*)calloc(255,sizeof(char));
  
  xposition = a_background->bg_elt_array[i].adj_xposition;
  yposition = a_background->bg_elt_array[i].adj_yposition;
  
  spacex = a_background->bg_elt_array[i].tilespacex;
  spacey = a_background->bg_elt_array[i].tilespacey;
  
  blitx = 0;
  blity = 0;
  if (SENSEI_DEBUG_ON){
    TRON("tiling");
    sprintf(message,"xposition = %i, yposition = %i, spacex = %i, spacey = %i",xposition,yposition,spacex,spacey);
    TRON(message);
  }
  
  // simplest part : no infinite tiling i.e tilex!=1 and tiley!=1
  if ((a_background->bg_elt_array[i].tilex!=1)&&(a_background->bg_elt_array[i].tiley!=1)){
    if (SENSEI_DEBUG_ON)
      TRON("simplest tiling");
    patternx = xposition;
    patterny = yposition;
    if (a_background->bg_elt_array[i].tilex==0)
      nb_tilex = 1;
    else
      nb_tilex = a_background->bg_elt_array[i].tilex;
    if (a_background->bg_elt_array[i].tiley==0)
      nb_tiley = 1;
    else
      nb_tiley = a_background->bg_elt_array[i].tiley;
    
    for (i=0;i<nb_tilex;i++)
      for (j=0;j<nb_tiley;j++)
	if ((a_background->bg_elt_array[i].trans==0)&&(a_background->bg_elt_array[i].mask==0)){
	  blit(a_sprite,virtscreen,0,0,patternx+j*(a_sprite->w+spacex),patterny+i*(a_sprite->h+spacey),a_sprite->w,a_sprite->h);
	}else{
	  if (a_background->bg_elt_array[i].trans==0){
	    draw_sprite(virtscreen,a_sprite,patternx+j*(a_sprite->w+spacex),patterny+i*(a_sprite->h+spacey));
	  }else{
	    draw_trans_sprite(virtscreen,a_sprite,patternx+j*(a_sprite->w+spacex),patterny+i*(a_sprite->h+spacey));
	  }
	}
  }// end of simplest part
  
  // a bit harder , horizontal infinite tiles
  if ((a_background->bg_elt_array[i].tilex==1)&&(a_background->bg_elt_array[i].tiley!=1)){
    //TRON("infinite blit horizontal");
    blitx = xposition;

    if (xposition+a_sprite->w+spacex<=0)
      blitx = -(abs(xposition)%(a_sprite->w+spacex));
    
    if (xposition-spacex>0)
      blitx = xposition - (((xposition/(a_sprite->w+spacex))+1)*(a_sprite->w+spacex));
    
    if (a_background->bg_elt_array[i].tiley==0)
      nb_tiley = 1;
    else
      nb_tiley = a_background->bg_elt_array[i].tiley;
    
    for (j=0;j<nb_tiley;j++){
      xposition = blitx;
      if ((a_background->bg_elt_array[i].trans==0)&&(a_background->bg_elt_array[i].mask==0)){
	blit(a_sprite,virtscreen,0,0,xposition,yposition+j*(a_sprite->h+spacey),a_sprite->w,a_sprite->h);
      }else{
	if (a_background->bg_elt_array[i].trans==0){
	  draw_sprite(virtscreen,a_sprite,xposition,yposition+j*(a_sprite->h+spacey));
	}else{
	  draw_trans_sprite(virtscreen,a_sprite,xposition,yposition+j*(a_sprite->h+spacey));
	}
      }
      
      xposition = xposition + a_sprite->w + spacex;
      while (xposition<virtscreen->w){
	if ((a_background->bg_elt_array[i].trans==0)&&(a_background->bg_elt_array[i].mask==0)){
	  blit(a_sprite,virtscreen,0,0,xposition,yposition+j*(a_sprite->h+spacey),a_sprite->w,a_sprite->h);
	}else{
	  if (a_background->bg_elt_array[i].trans==0){
	    draw_sprite(virtscreen,a_sprite,xposition,yposition+j*(a_sprite->h+spacey));
	  }else{
	    draw_trans_sprite(virtscreen,a_sprite,xposition,yposition+j*(a_sprite->h+spacey));
	  }
	}
	xposition = xposition + a_sprite->w + spacex;
      }
    }
  }
  
  // same but with verticle infinite tiles
  if ((a_background->bg_elt_array[i].tiley==1)&&(a_background->bg_elt_array[i].tilex!=1)){
    //TRON("infinite verticle");
    blity = yposition;
    
    if (yposition+a_sprite->h+spacey<=0)
      blity = -(abs(yposition)%(a_sprite->h+spacey));
    
    if (yposition-spacey>0)
      blity = yposition - (((yposition/(a_sprite->h+spacey))+1)*(a_sprite->h+spacey));
    
    if (a_background->bg_elt_array[i].tilex==0)
      nb_tilex = 1;
    else
      nb_tilex = a_background->bg_elt_array[i].tilex;
    
    for (j=0;j<nb_tilex;j++){
      yposition = blity;
      if ((a_background->bg_elt_array[i].trans==0)&&(a_background->bg_elt_array[i].mask==0)){
	blit(a_sprite,virtscreen,0,0,xposition+j*(a_sprite->w+spacex),yposition,a_sprite->w,a_sprite->h);
      }else{
	if (a_background->bg_elt_array[i].trans==0){
	  draw_sprite(virtscreen,a_sprite,xposition+j*(a_sprite->w+spacex),yposition);
	}else{
	  draw_trans_sprite(virtscreen,a_sprite,xposition+j*(a_sprite->w+spacex),yposition);
	}
      }
      
      yposition = yposition + a_sprite->h + spacey;
      while (yposition<virtscreen->h){
	if ((a_background->bg_elt_array[i].trans==0)&&(a_background->bg_elt_array[i].mask==0)){
	  blit(a_sprite,virtscreen,0,0,xposition+j*(a_sprite->w+spacex),yposition,a_sprite->w,a_sprite->h);
	}else{
	  if (a_background->bg_elt_array[i].trans==0){
	    draw_sprite(virtscreen,a_sprite,xposition+j*(a_sprite->w+spacex),yposition);
	  }else{
	    draw_trans_sprite(virtscreen,a_sprite,xposition+j*(a_sprite->w+spacex),yposition);
	  }
	  //masked_blit(a_sprite,virtscreen,0,0,xposition+j*a_sprite->w,yposition,a_sprite->w,a_sprite->h);
	}
	yposition = yposition + a_sprite->h + spacey;
      }
    }
  }
  
  // last but not least : infinite tiling evreywhere
  if ((a_background->bg_elt_array[i].tiley==1)&&(a_background->bg_elt_array[i].tilex==1)){
    //TRON("infinite both");
    blitx = xposition;
    blity = yposition;
    
    if (xposition+a_sprite->w+spacex<=0)
      blitx = -(abs(xposition)%(a_sprite->w+spacex));
    
    if (xposition-spacex>0)
      blitx = xposition - (((xposition/(a_sprite->w+spacex))+1)*(a_sprite->w+spacex));
    
    if (yposition+a_sprite->h+spacey<=0)
      blity = -(abs(yposition)%(a_sprite->h+spacey));
    
    if (yposition-spacey>0)
      blity = yposition - (((yposition/(a_sprite->h+spacey))+1)*(a_sprite->h+spacey));
    
    yposition = blity;
    while (yposition<virtscreen->h){
      xposition = blitx;
      while (xposition<virtscreen->w){
	if ((a_background->bg_elt_array[i].trans==0)&&(a_background->bg_elt_array[i].mask==0)){
	  blit(a_sprite,virtscreen,0,0,xposition,yposition,a_sprite->w,a_sprite->h);
	}else{
	  if (a_background->bg_elt_array[i].trans==0){
	    draw_sprite(virtscreen,a_sprite,xposition,yposition);
	  }else{
	    draw_trans_sprite(virtscreen,a_sprite,xposition,yposition);
	  }
	}
	xposition = xposition + a_sprite->w + spacex;
      }
      yposition = yposition + a_sprite->h + spacey;
    }
  }
  //TRON("end of tiling");

  return 0;
}// mugen_tiled_bg

int mugen_bg(background_struct * a_background,int i, BITMAP * a_sprite, RGB * a_pal){
  char * message;
  int xposition,yposition;

  message = (char*)calloc(255,sizeof(char));
  if (SENSEI_DEBUG_ON)
    TRON("no Tiling");
  
  xposition =  a_background->bg_elt_array[i].adj_xposition;
  yposition =  a_background->bg_elt_array[i].adj_yposition;
  
  // Putting on virtscreen
  // No trans No mask
  if ((a_background->bg_elt_array[i].mask == 0)&&(a_background->bg_elt_array[i].trans == 0)){
    blit(a_sprite,virtscreen, 0,0, xposition, yposition, a_sprite->w, a_sprite->h);
    return 0;
  }
  
  //set_color_conversion(COLORCONV_TOTAL);
  if (a_background->bg_elt_array[i].trans==0){
    draw_sprite(virtscreen,a_sprite,xposition,yposition);
  }else{
    draw_trans_sprite(virtscreen,a_sprite,xposition,yposition);
  }
  
  unselect_palette();
  return 0;
} // mugen_bg


/** \brief function to to show all background structs
 */
int background_output(background_struct * a_background, int layer){
  char * message;
  // SFFEntry * cur;
  // SFFEntry * pal_cur;
  int i,j;
  int xaxis = 0;
  int yaxis = 0;
  int masked = 0;
  BITMAP * a_sprite;
  BITMAP * buffer = NULL;
  int act_index = 0;
  int flipped = 0;
  // int spr_position = 0;
  
  // RGB trans = { 63 , 0 , 63 }; //magenta for translucy in true color mode
  /* RGB -> color mapping table. Not needed, but speeds things up */
  RGB_MAP rgb_table;
  
  /* translucency color mapping table */
  COLOR_MAP trans_table;
  int trans_level = 0;
  RGB * a_pal;
  int current_element = 0; // simplification for animations
  message = (char*)calloc(255,sizeof(char));
  // cur = malloc(sizeof(SFFEntry));
  // pal_cur = malloc(sizeof(SFFEntry));
  
  if (SENSEI_DEBUG_ON){
    sprintf(message,"entering background_output layer %i and bg_type = %i",layer,a_background->type);
    TRON(message);
  }
  
  switch (a_background->type){
  case 1: // KOF 91 pcx
    if (SENSEI_DEBUG_ON)
      TRON("Bg output pcx");
    if (layer<1){
      select_palette(a_background->Pal_back);
      blit(a_background->Pcx_back,virtscreen,a_background->camerax,a_background->cameray,0,0,virtscreen->w,virtscreen->h);
      unselect_palette();
    }else{
      if (a_background->type_front!=0){
	select_palette(a_background->Pal_front);
	blit(a_background->Pcx_front,virtscreen,0,0,0,0,320,240);
	unselect_palette();
      }
    }
    break;
  case 2: // KOF 91 flc
    TRON("bg Output flc");
    break;
  case 3: // Mugen's bg
    if (SENSEI_DEBUG_ON)
      TRON("bg output mugen");
    for (i=0;i<a_background->bg_elt_nb;i++){ // for each bg_elt
      if (a_background->bg_elt_array[i].layerno==layer){
	//TRON("good layer bg");
	
	if ((a_background->bg_elt_array[i].mask!=0)||(a_background->bg_elt_array[i].trans!=0)){
	  masked = 1;
	}
	
	// Definition of good space to draw into
	set_clip_rect(virtscreen,a_background->bg_elt_array[i].windowx,a_background->bg_elt_array[i].windowy,a_background->bg_elt_array[i].windoww,a_background->bg_elt_array[i].windowh);
	
	a_sprite = sensei_fill_bmp(a_background->bg_sff,a_background->bg_elt_array[i].spritenog,a_background->bg_elt_array[i].spritenoi,masked,&xaxis,&yaxis);
	
	a_pal = sensei_fill_pal(a_background->bg_sff,a_background->bg_elt_array[i].spritenog,a_background->bg_elt_array[i].spritenoi,0,masked);
	
	
	// Dealing with translucy of BG elements
	if (a_background->bg_elt_array[i].trans!=0){
	  //TRON("dealing translucy");
	  if (a_background->bg_elt_array[i].trans!=-1){
	    // add translucy
	    create_rgb_table(&rgb_table, a_pal, NULL);
	    rgb_map = &rgb_table;
	    //create_light_table(&trans_table, a_pal, 128, 128, 128, NULL);
	    create_trans_table(&trans_table, a_pal, 255, 255, 255, NULL);
	    trans_level = (int)255*(a_background->bg_elt_array[i].trans)/100;
	    if (SENSEI_DEBUG_ON){
	      sprintf(message,"trans level = %i",trans_level);
	      TRON(message);
	    }
	    set_add_blender(255, 255, 255, trans_level);
	  }else{
	    // sub translucy
	    create_rgb_table(&rgb_table, a_pal, NULL);
	    rgb_map = &rgb_table;
	    create_trans_table(&trans_table, a_pal, 255, 255, 255, NULL);
	    //trans_level = (int)255*(a_background->bg_elt_array[i].trans)/100;
	    //sprintf(message,"trans level = %i",trans_level);
	    //TRON(message);
	    set_difference_blender(128, 128, 128, 128);
	  }
	}else{
	  set_trans_blender(0,0,0,255);
	}
	

	// TRON("after trans blender");
	switch (a_background->bg_elt_array[i].elt_type){
	case 0: // Mugen's bg normal
	  // fprintf(stdout,"Normral bg output\n");
	  if (SENSEI_DEBUG_ON)
	    TRON("normal bg elt_type");
	  // Adjusting with center of screen and sprite axis
	  a_background->bg_elt_array[i].adj_xposition = a_background->bg_elt_array[i].xposition - xaxis + 160;
	  a_background->bg_elt_array[i].adj_yposition = a_background->bg_elt_array[i].yposition - yaxis;

	  if ((a_background->bg_elt_array[i].tilex!=0)||(a_background->bg_elt_array[i].tiley!=0)){ // tiling
	    mugen_tiled_bg(a_background,i,a_sprite,a_pal);
	    break;
	  }
	  else{ // no tiling
	    mugen_bg(a_background,i,a_sprite,a_pal);
	  }
	  break;
	case 1: // Mugen's bg anim
	  // fprintf(stdout,"anim bg output\n");
	  if (SENSEI_DEBUG_ON)
	    TRON("bg elt anim");
	  // getting the good index by inspection of animations
	  act_index = -1;
	  for (j=0;j<a_background->action_nb;j++){
	    if (a_background->action_array[j].number==a_background->bg_elt_array[i].actionno)
	      act_index = j;
	  }
	  if (act_index!=-1){
	    // Adjusting with center of screen and sprite axis
	    current_element = a_background->action_array[act_index].current_element;
	    a_background->bg_elt_array[i].adj_xposition = a_background->bg_elt_array[i].xposition - xaxis + 160; 
	    a_background->bg_elt_array[i].adj_yposition = a_background->bg_elt_array[i].yposition - yaxis; 	  
	    a_background->bg_elt_array[i].adj_xposition = a_background->bg_elt_array[i].adj_xposition + a_background->action_array[act_index].animation_array[current_element].x;
	    a_background->bg_elt_array[i].adj_yposition = a_background->bg_elt_array[i].adj_yposition + a_background->action_array[act_index].animation_array[current_element].y;
	    
	    if (a_background->action_array[act_index].animation_array[a_background->action_array[act_index].current_element].flipping!=0){
	      // fprintf(stdout,"anim flipp\n");
	      switch (a_background->action_array[act_index].animation_array[a_background->action_array[act_index].current_element].flipping){
	      case 1:
		// TRON("I've founded flipping h");
		buffer = create_bitmap_ex(bitmap_color_depth(a_sprite),a_sprite->w,a_sprite->h);
		clear_to_color(buffer,makecol(255,0,255));
		draw_sprite_h_flip(buffer,a_sprite,0,0);
		flipped = 1;
		a_background->bg_elt_array[i].adj_xposition = a_background->bg_elt_array[i].adj_xposition - buffer->w;
		break;
	      case 2:
		// TRON("I've founded flipping v");
		buffer = create_bitmap_ex(bitmap_color_depth(a_sprite),a_sprite->w,a_sprite->h);
		clear_to_color(buffer,makecol(255,0,255));
		draw_sprite_v_flip(buffer,a_sprite,0,0);
		flipped = 1;
		break;
	      case 3:
		buffer = create_bitmap_ex(bitmap_color_depth(a_sprite),a_sprite->w,a_sprite->h);
		clear_to_color(buffer,makecol(255,0,255));
		draw_sprite_vh_flip(buffer,a_sprite,0,0);
		flipped = 1;
		a_background->bg_elt_array[i].adj_xposition = a_background->bg_elt_array[i].adj_xposition - buffer->w;
		break;
	      default:
		
		break;
	      }
	    }
	    
	    if ((a_background->bg_elt_array[i].tilex!=0)||(a_background->bg_elt_array[i].tiley!=0)){ // tiling
	      if (flipped==0){
		mugen_tiled_bg(a_background,i,a_sprite,a_pal);
	      }else{
		mugen_tiled_bg(a_background,i,buffer,a_pal);
		destroy_bitmap(buffer);
	      }
	      break;
	    }
	    else{ // no tiling
	      // fprintf(stdout,"No tiling\n");
	      if (flipped==0){
		// fprintf(stdout,"No tiling No flipping\n");
		mugen_bg(a_background,i,a_sprite,a_pal);
	      }else{
		// TRON("flipped simple bg zz");
		mugen_bg(a_background,i,buffer,a_pal);
		destroy_bitmap(buffer);
	      }
	    }
	  }
	  break;
	case 2: //Mugen's parallax
	  TRON("bg elt parrallax");
	  break;
	default:
	  TRON("strange mugen bg elt type");
	  break;
	}
	destroy_bitmap(a_sprite);
	set_clip_rect(virtscreen,0,0,virtscreen->w,virtscreen->h);
	set_trans_blender(0,0,0,255);
	set_difference_blender(0,0,0,255);
	flipped = 0;
      }else{
	//TRON("wrong layer");
      }
    }
    //TRON("after the for");
    break;
  default : // bg type
    TRON("strange bg type");
    break;
  }

  return 0;
}
    
