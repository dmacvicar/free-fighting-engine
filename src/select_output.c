#include "select_output.h"
#include "background_output.h"
#include "macros.h"
#include "logger.h"
#include "sensei_config.h"

#include "stdio.h"

/** \file select_output.c
 * \brief Functions to show character select screen KOF 91 and Mugen's style
 */

int kof91_select_output (Game_variables variables,Player_variables * player_array);

int select_output(Game_variables variables,Player_variables * player_array,int time){
  int error,i,j,k,xposition,yposition;
  int current_char_index; // index of char in the list
  int current_char;
  int portraitw,portraith; // To calculate portrait heigh and width before stretching it
  char * message;
  BITMAP * a_sprite = NULL; // for emptybox sprite
  BITMAP * buffer = NULL;
  FNTInfo* fontInfo1_temp; // To stock fonts
  int xaxis = 0;
  int yaxis = 0;
  error = 0;
  message = (char*)malloc(255*sizeof(char));
  
  
  if (variables->System.Select_bg.type!=1){
    /*
     * showing Select BG (back)
     */
    error += background_output(&(variables->System.Select_bg),0);
    if (error!=0) {
      sprintf(message,"In Select_output bg_output error");
      ERROR(message);
      return -1;
    }else{
      //fprintf(stdout,"after bg output\n");
    }
    
    draw_sprite(virtscreen,variables->System.Select_struct.faces,0,0);
  
    /**
     * putting the boxes and chars faces
     */
    current_char_index = 0;
    yposition = variables->System.Select_struct.posy;
    for (i=0;i<variables->System.Select_struct.rows;i++){
      xposition = variables->System.Select_struct.posx;
      TRON("Looping rows");
      for (j=0;j<variables->System.Select_struct.columns;j++){
	// Putting selected boxes if the char have been already selected
	// p1 selected chars
	if (variables->System.Select_struct.p1_showed){
	  for (k=0;k<variables->System.Select_struct.p1_max_selecter;k++){
	    if (variables->System.Select_struct.p1_selected[k]==current_char_index){
	      a_sprite = sensei_fill_bmp(variables->System.Select_struct.select_sff,variables->System.Select_struct.p1doneg,variables->System.Select_struct.p1donei,1,&xaxis,&yaxis);
	      draw_sprite(virtscreen,a_sprite,xposition+xaxis,yposition+yaxis);
	    }
	  }
	}
	if (variables->System.Select_struct.p2_showed){
	  for (k=0;k<variables->System.Select_struct.p2_max_selecter;k++){
	    if (variables->System.Select_struct.p2_selected[k]==current_char_index){
	      a_sprite = sensei_fill_bmp(variables->System.Select_struct.select_sff,variables->System.Select_struct.p2doneg,variables->System.Select_struct.p2donei,1,&xaxis,&yaxis); 
	      draw_sprite(virtscreen,a_sprite,xposition+xaxis,yposition+yaxis);
	    }
	  }
	}
	
	current_char_index++;
	xposition = xposition + variables->System.Select_struct.cellsizex + variables->System.Select_struct.cellspacing;
      }
      yposition = yposition + variables->System.Select_struct.cellsizey + variables->System.Select_struct.cellspacing;
    }
    destroy_bitmap(a_sprite);
    
    /**
     * putting player's active cursor's
     */
    TRON("player active cursor");
    if (variables->System.Select_struct.p1_showed){
      a_sprite = sensei_fill_bmp(variables->System.Select_struct.select_sff,variables->System.Select_struct.p1activeg,variables->System.Select_struct.p1activei,1,&xaxis,&yaxis);
      xposition = variables->System.Select_struct.posx + variables->System.Select_struct.p1_position.x * (variables->System.Select_struct.cellsizex + variables->System.Select_struct.cellspacing) + xaxis;
      yposition = variables->System.Select_struct.posy + variables->System.Select_struct.p1_position.y * (variables->System.Select_struct.cellsizey + variables->System.Select_struct.cellspacing) + yaxis;
      draw_sprite(virtscreen,a_sprite,xposition,yposition);
      destroy_bitmap(a_sprite);
    }
   

    if (variables->System.Select_struct.p2_showed){
      a_sprite = sensei_fill_bmp(variables->System.Select_struct.select_sff,variables->System.Select_struct.p2activeg,variables->System.Select_struct.p2activei,1,&xaxis,&yaxis);
      xposition = variables->System.Select_struct.posx + variables->System.Select_struct.p2_position.x * (variables->System.Select_struct.cellsizex + variables->System.Select_struct.cellspacing)+xaxis;
      yposition = variables->System.Select_struct.posy + variables->System.Select_struct.p2_position.y * (variables->System.Select_struct.cellsizey + variables->System.Select_struct.cellspacing)+yaxis;
      // sprintf(message,"x = %i y=%i",xposition,yposition);
      // TRON(message);
      draw_sprite(virtscreen,a_sprite,xposition,yposition);
      destroy_bitmap(a_sprite);
    }
    
    /**
     * Putting Title
     */
    if (variables->System.Select_struct.titlefonti!=-1){
      if (system_font_exists(variables,variables->System.Select_struct.titlefonti)){
	fontInfo1_temp = link_system_font(variables,variables->System.Select_struct.titlefonti);
	select_palette(*(fntGetPaletteForBank(fontInfo1_temp,variables->System.Select_struct.titlefontcolor)));
	switch (variables->System.Select_struct.titlefontjust){
	case 1:
	  textprintf_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.titleoffsetx,variables->System.Select_struct.titleoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.itemname[gmode]);
	  break;
	case 0:
	  textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.titleoffsetx,variables->System.Select_struct.titleoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.itemname[gmode]);
	  break;
	case -1:
	  textprintf_right_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.titleoffsetx,variables->System.Select_struct.titleoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.itemname[gmode]);
	  break;
	default:
	  textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.titleoffsetx,variables->System.Select_struct.titleoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.itemname[gmode]);
	  break;
	}
	unselect_palette();
      }
    }
    
    /**
     * Putting Faces (big portrait)
     */
    if (variables->System.Select_struct.p1_showed){
      //
      current_char_index = variables->System.Select_struct.p1_position.x + variables->System.Select_struct.p1_position.y*variables->System.Select_struct.columns;
      current_char = (variables->System.Select_struct.char_list[current_char_index]);
      if (current_char!=-1){ // != random
	if (current_char!=0){ // != empty
	  current_char--;
	  switch (variables->System.Select_struct.char_ref_array[current_char].type){
	  case 0:
	    TRON("No char face");
	    break;
	  case 1:
	    TRON("KOF 91 face");
	    portraitw = (int)(variables->System.Select_struct.char_ref_array[current_char].b_pic->w * variables->System.Select_struct.p1facescalex);
	    portraith = (int)(variables->System.Select_struct.char_ref_array[current_char].b_pic->h * variables->System.Select_struct.p1facescaley);
	    a_sprite = create_bitmap_ex(bitmap_color_depth(variables->System.Select_struct.char_ref_array[current_char].b_pic),portraitw,portraith);
	    select_palette(variables->System.Select_struct.char_ref_array[current_char].b_pic_pal);
	    set_color_conversion(COLORCONV_NONE);
	    stretch_blit(variables->System.Select_struct.char_ref_array[current_char].b_pic,a_sprite,0,0,variables->System.Select_struct.char_ref_array[current_char].b_pic->w,variables->System.Select_struct.char_ref_array[current_char].b_pic->h,0,0,portraitw,portraith);
	    buffer = create_bitmap(a_sprite->w,a_sprite->h);
	    blit(a_sprite,buffer,0,0,0,0,a_sprite->w,a_sprite->h);
	    if (variables->System.Select_struct.p1facefacing==1){
	      draw_sprite(virtscreen,buffer,variables->System.Select_struct.p1faceoffsetx, variables->System.Select_struct.p1faceoffsety);
	    }else{
	      draw_sprite_h_flip(virtscreen,buffer,variables->System.Select_struct.p1faceoffsetx-buffer->w, variables->System.Select_struct.p1faceoffsety);
	    }
	    // destroy_bitmap(buffer);
	    unselect_palette();
	    break;
	  case 2:
	    if (SENSEI_DEBUG_ON)
	      TRON("Mugen's face");
	    xaxis = variables->System.Select_struct.char_ref_array[current_char].big_xaxis;
	    yaxis = variables->System.Select_struct.char_ref_array[current_char].big_yaxis;
	    portraitw = (int)(variables->System.Select_struct.char_ref_array[current_char].b_pic->w * variables->System.Select_struct.p1facescalex);
	    portraith = (int)(variables->System.Select_struct.char_ref_array[current_char].b_pic->h * variables->System.Select_struct.p1facescaley);
	    a_sprite = create_bitmap_ex(bitmap_color_depth(variables->System.Select_struct.char_ref_array[current_char].b_pic),portraitw,portraith);
	    select_palette(variables->System.Select_struct.char_ref_array[current_char].b_pic_pal);
	    set_color_conversion(COLORCONV_NONE);
	    stretch_blit(variables->System.Select_struct.char_ref_array[current_char].b_pic,a_sprite,0,0,variables->System.Select_struct.char_ref_array[current_char].b_pic->w,variables->System.Select_struct.char_ref_array[current_char].b_pic->h,0,0,portraitw,portraith);
	    buffer = create_bitmap(a_sprite->w,a_sprite->h);
	    blit(a_sprite,buffer,0,0,0,0,a_sprite->w,a_sprite->h);
	    if (variables->System.Select_struct.p1facefacing==1){
	      draw_sprite(virtscreen,buffer,variables->System.Select_struct.p1faceoffsetx - xaxis, variables->System.Select_struct.p1faceoffsety - yaxis);
	    }else{
	      draw_sprite_h_flip(virtscreen,buffer,variables->System.Select_struct.p1faceoffsetx-buffer->w + xaxis, variables->System.Select_struct.p1faceoffsety - yaxis);
	    }
	    break;
	  default :
	    TRON("strange face");
	    break;
	  }
	}
      }
    }
    TRON("after p1 face");
    if (variables->System.Select_struct.p2_showed){
      // current_char_index = (variables->System.Select_struct.p2_position.x+1) * (variables->System.Select_struct.p2_position.y+1)-1;
      current_char_index = variables->System.Select_struct.p2_position.x + variables->System.Select_struct.p2_position.y*variables->System.Select_struct.columns;
      TRON("before current char");
      current_char = (variables->System.Select_struct.char_list[current_char_index]);
      if (current_char!=-1){ // != random
	if (current_char!=0){ // != empty
	  current_char--;
	  switch (variables->System.Select_struct.char_ref_array[current_char].type){
	  case 0:
	    TRON("No char face");
	    break;
	  case 1:
	    TRON("KOF 91 face p2");
	    portraitw = (int)(variables->System.Select_struct.char_ref_array[current_char].b_pic->w * variables->System.Select_struct.p2facescalex);
	    portraith = (int)(variables->System.Select_struct.char_ref_array[current_char].b_pic->h * variables->System.Select_struct.p2facescaley);
	    a_sprite = create_bitmap_ex(bitmap_color_depth(variables->System.Select_struct.char_ref_array[current_char].b_pic),portraitw,portraith);
	    TRON("after a sprite");
	    select_palette(variables->System.Select_struct.char_ref_array[current_char].b_pic_pal);
	    set_color_conversion(COLORCONV_NONE);
	    stretch_blit(variables->System.Select_struct.char_ref_array[current_char].b_pic,a_sprite,0,0,variables->System.Select_struct.char_ref_array[current_char].b_pic->w,variables->System.Select_struct.char_ref_array[current_char].b_pic->h,0,0,portraitw,portraith);
	    buffer = create_bitmap(a_sprite->w,a_sprite->h);
	    blit(a_sprite,buffer,0,0,0,0,a_sprite->w,a_sprite->h);
	    if (variables->System.Select_struct.p2facefacing==1){
	      draw_sprite(virtscreen,buffer,variables->System.Select_struct.p2faceoffsetx, variables->System.Select_struct.p2faceoffsety);
	    }else{
	      draw_sprite_h_flip(virtscreen,buffer,variables->System.Select_struct.p2faceoffsetx-buffer->w, variables->System.Select_struct.p2faceoffsety);
	    }
	    // destroy_bitmap(buffer);
	    unselect_palette();
	    break;
	  case 2:
	    if (SENSEI_DEBUG_ON)
	      TRON("Mugen's face");
	    xaxis = variables->System.Select_struct.char_ref_array[current_char].big_xaxis;
	    yaxis = variables->System.Select_struct.char_ref_array[current_char].big_yaxis;
	    portraitw = (int)(variables->System.Select_struct.char_ref_array[current_char].b_pic->w * variables->System.Select_struct.p2facescalex);
	    portraith = (int)(variables->System.Select_struct.char_ref_array[current_char].b_pic->h * variables->System.Select_struct.p2facescaley);
	    a_sprite = create_bitmap_ex(bitmap_color_depth(variables->System.Select_struct.char_ref_array[current_char].b_pic),portraitw,portraith);
	    select_palette(variables->System.Select_struct.char_ref_array[current_char].b_pic_pal);
	    set_color_conversion(COLORCONV_NONE);
	    stretch_blit(variables->System.Select_struct.char_ref_array[current_char].b_pic,a_sprite,0,0,variables->System.Select_struct.char_ref_array[current_char].b_pic->w,variables->System.Select_struct.char_ref_array[current_char].b_pic->h,0,0,portraitw,portraith);
	    buffer = create_bitmap(a_sprite->w,a_sprite->h);
	    blit(a_sprite,buffer,0,0,0,0,a_sprite->w,a_sprite->h);
	    if (variables->System.Select_struct.p2facefacing==1){
	      draw_sprite(virtscreen,buffer,variables->System.Select_struct.p2faceoffsetx, variables->System.Select_struct.p2faceoffsety);
	    }else{
	      draw_sprite_h_flip(virtscreen,buffer,variables->System.Select_struct.p2faceoffsetx-buffer->w, variables->System.Select_struct.p2faceoffsety);
	    }
	    break;
	  default :
	    TRON("strange face");
	    break;
	  }
	}
      }
    }
    
    /**
     * Showing player's name
     */
    TRON("player'sname");
    if (variables->System.Select_struct.p1_showed){
      if (variables->System.Select_struct.p1namefonti!=-1){
	// current_char_index = (variables->System.Select_struct.p1_position.x+1) * (variables->System.Select_struct.p1_position.y+1)-1;
	current_char_index = variables->System.Select_struct.p1_position.x + variables->System.Select_struct.p1_position.y*variables->System.Select_struct.columns;
	
	current_char = (variables->System.Select_struct.char_list[current_char_index]);
	if (current_char!=-1){
	  if (current_char!=0){
	    current_char--;
	    if (system_font_exists(variables,variables->System.Select_struct.p1namefonti)){
	      fontInfo1_temp = link_system_font(variables,variables->System.Select_struct.p1namefonti);
	      select_palette(*(fntGetPaletteForBank(fontInfo1_temp,variables->System.Select_struct.p1namefontcolor)));
	      switch (variables->System.Select_struct.p1namefontjust){
	      case 1:
		textprintf_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.p1nameoffsetx,variables->System.Select_struct.p1nameoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[current_char].display_name);
		break;
	      case 0:
		textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.p1nameoffsetx,variables->System.Select_struct.p1nameoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[current_char].display_name);
		break;
	      case -1:
		textprintf_right_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.p1nameoffsetx,variables->System.Select_struct.p1nameoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[current_char].display_name);
		break;
	      default:
		textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.p1nameoffsetx,variables->System.Select_struct.p1nameoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[current_char].display_name);
		break;
	      }
	      unselect_palette();
	    }
	
	  }
	}
      }
    }
    
    // Showing p2 name
    if (variables->System.Select_struct.p2_showed){
      if (variables->System.Select_struct.p2namefonti!=-1){
	// current_char_index = (variables->System.Select_struct.p2_position.x+1) * (variables->System.Select_struct.p2_position.y+1)-1;
	current_char_index = variables->System.Select_struct.p2_position.x + variables->System.Select_struct.p2_position.y*variables->System.Select_struct.columns;
	
	current_char = (variables->System.Select_struct.char_list[current_char_index]);
	if (current_char!=-1){
	  if (current_char!=0){
	    current_char--;
	    if (system_font_exists(variables,variables->System.Select_struct.p2namefonti)){
	      fontInfo1_temp = link_system_font(variables,variables->System.Select_struct.p2namefonti);
	      select_palette(*(fntGetPaletteForBank(fontInfo1_temp,variables->System.Select_struct.p2namefontcolor)));
	      switch (variables->System.Select_struct.p2namefontjust){
	      case 1:
		textprintf_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.p2nameoffsetx,variables->System.Select_struct.p2nameoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[current_char].display_name);
		break;
	      case 0:
		textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.p2nameoffsetx,variables->System.Select_struct.p2nameoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[current_char].display_name);
		break;
	      case -1:
		textprintf_right_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.p2nameoffsetx,variables->System.Select_struct.p2nameoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[current_char].display_name);
		break;
	      default:
		textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.p2nameoffsetx,variables->System.Select_struct.p2nameoffsety-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[current_char].display_name);
		break;
	      }
	      unselect_palette();
	    }
	
	  }
	}
      }
    }
    
    
    /*
     * Showing bg name
     */
    TRON("Bg name");
    if (variables->System.Select_struct.stage_showed){
      if (!variables->System.Select_struct.bg_selected){
	if (!variables->System.Select_struct.bg_blinked){
	  if (variables->System.Select_struct.stageactivefonti!=-1){
	    if (system_font_exists(variables,variables->System.Select_struct.stageactivefonti)){
	      fontInfo1_temp = link_system_font(variables,variables->System.Select_struct.stageactivefonti);
	      select_palette(*(fntGetPaletteForBank(fontInfo1_temp,variables->System.Select_struct.stageactivefontcolor)));
	      switch (variables->System.Select_struct.stageactivefontjust){
	      case 1:
		textprintf_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
		break;
	      case 0:
		textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
		break;
	      case -1:
		textprintf_right_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
		break;
	      default:
		textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
		break;
	      }
	      unselect_palette();
	    }else{
	      textprintf_centre_ex(virtscreen,font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(font)),makecol(10,10,100),-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
	    }
	  }
	}else{
	  if (variables->System.Select_struct.stageactive2fonti!=-1){
	    if (system_font_exists(variables,variables->System.Select_struct.stageactive2fonti)){
	      fontInfo1_temp = link_system_font(variables,variables->System.Select_struct.stageactive2fonti);
	      select_palette(*(fntGetPaletteForBank(fontInfo1_temp,variables->System.Select_struct.stageactive2fontcolor)));
	      switch (variables->System.Select_struct.stageactive2fontjust){
	      case 1:
		textprintf_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
		break;
	      case 0:
		textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
		break;
	      case -1:
		textprintf_right_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
		break;
	      default:
		textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
		break;
	      }
	      unselect_palette();
	    }else{
	      textprintf_centre_ex(virtscreen,font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(font)),makecol(100,10,10),-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
	    }
	    
	  }
	}
      }else{
	if (variables->System.Select_struct.stagedonefonti!=-1){
	  if (system_font_exists(variables,variables->System.Select_struct.stagedonefonti)){
	    fontInfo1_temp = link_system_font(variables,variables->System.Select_struct.stagedonefonti);
	    select_palette(*(fntGetPaletteForBank(fontInfo1_temp,variables->System.Select_struct.stagedonefontcolor)));
	    switch (variables->System.Select_struct.stagedonefontjust){
	    case 1:
	      textprintf_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
	      break;
	    case 0:
	      textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
	      break;
	    case -1:
	      textprintf_right_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
	      break;
	    default:
	      textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
	      break;
	    }
	    unselect_palette();
	  }else{
	    textprintf_centre_ex(virtscreen,font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(font)),makecol(100,10,100),-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
	  }
	}
      }
    }
    
    /*
     * showing Select BG (front)
     */
    error += background_output(&(variables->System.Select_bg),1);
    if (error!=0) {
      sprintf(message,"In Select_output bg_output error");
      ERROR(message);
      return -1;
    }else{
      //fprintf(stdout,"after bg output\n");
    }
    /*
      if (a_sprite!=NULL)
      destroy_bitmap(a_sprite);
    */
  }else{ // Old KOF 91 select screen
    kof91_select_output(variables,player_array);
  }
  return 0;
} // end select output

/** \brief Function that show charcater select screen as the old KOF 91 does
 */
int kof91_select_output(Game_variables variables,Player_variables * player_array){
  char * message;
  int xposition = virtscreen->w/2 - 13;
  int current_char_index,current_char_index2,current_player,current_player2;
  TRON("begin kof91_select_output");
  current_char_index = variables->System.Select_struct.p1_position.x + variables->System.Select_struct.p1_position.y*variables->System.Select_struct.columns;
  current_player = (variables->System.Select_struct.char_list[current_char_index]);
  current_char_index2 = variables->System.Select_struct.p2_position.x + variables->System.Select_struct.p2_position.y*variables->System.Select_struct.columns;
  current_player2 = (variables->System.Select_struct.char_list[current_char_index]);
  current_player--;
  current_player2--;
  
  message = (char*)calloc(255,sizeof(char));
  
  /** Showing moving bg */
  if (variables->System.Select_bg.Pcx_back!=NULL){
    if (variables->System.Select_struct.posx < variables->System.Select_bg.Pcx_back->w - 1)
      variables->System.Select_struct.posx++;
    else
      variables->System.Select_struct.posx = 0;
    if (variables->System.Select_struct.posy > 0)
      variables->System.Select_struct.posy --;
    else
      variables->System.Select_struct.posy = variables->System.Select_bg.Pcx_back->h - 1;
    drawing_mode(DRAW_MODE_COPY_PATTERN,variables->System.Select_bg.Pcx_back,variables->System.Select_struct.posx,variables->System.Select_struct.posy);
    rectfill(virtscreen,0,0,virtscreen->w,virtscreen->h,-1);
    drawing_mode (DRAW_MODE_SOLID, 0, 0, 0);
  }
  sprintf(message, "center to right p1 = %i and p2 = %i",current_player,current_player2);
  TRON(message);
  /** Showing faces from center to right */
  while (xposition < virtscreen->w){
    // Showing 1 p faces
    if (variables->System.Select_struct.p1_showed){
      select_palette(variables->System.Select_struct.char_ref_array[current_player].s_pic_pal);
      draw_sprite(virtscreen,variables->System.Select_struct.char_ref_array[current_player].s_pic,xposition,0);
      unselect_palette();
    }

    // Showing 2 p faces
    if (variables->System.Select_struct.p2_showed){
      select_palette(variables->System.Select_struct.char_ref_array[current_player2].s_pic_pal);
      draw_sprite(virtscreen,variables->System.Select_struct.char_ref_array[current_player2].s_pic,xposition,virtscreen->h-26);
      unselect_palette();
    }
    xposition = xposition + 36;
    current_player++;
    current_player2++;
    if (current_player>=variables->System.Select_struct.nb_char)
      current_player = 0;
    if (current_player2>=variables->System.Select_struct.nb_char)
      current_player2 = 0;
  }
  
  // Putting active cursors
  if (variables->System.Select_struct.p1_showed){
    rect(virtscreen,virtscreen->w/2-13,0,virtscreen->w/2+13,26,makecol(255,0,0));
  }
  if (variables->System.Select_struct.p2_showed){
    rect(virtscreen,virtscreen->w/2-13,virtscreen->h-26,virtscreen->w/2+13,virtscreen->h,makecol(0,0,255));
  }

  TRON("showing faces form center to left");
  /** Showing faces from center to left */
  current_char_index = variables->System.Select_struct.p1_position.x + variables->System.Select_struct.p1_position.y*variables->System.Select_struct.columns;
  current_player = (variables->System.Select_struct.char_list[current_char_index]);
  current_char_index2 = variables->System.Select_struct.p2_position.x + variables->System.Select_struct.p2_position.y*variables->System.Select_struct.columns;
  current_player2 = (variables->System.Select_struct.char_list[current_char_index]);
  current_player--;
  current_player2--;
  
  xposition = virtscreen->w/2 - 13;
  while (xposition > -36){
    // Showing 1 p faces
    if (variables->System.Select_struct.p1_showed){
      select_palette(variables->System.Select_struct.char_ref_array[current_player].s_pic_pal);
      draw_sprite(virtscreen,variables->System.Select_struct.char_ref_array[current_player].s_pic,xposition,0);
      unselect_palette();
    }
    if (variables->System.Select_struct.p2_showed){
      select_palette(variables->System.Select_struct.char_ref_array[current_player2].s_pic_pal);
      draw_sprite(virtscreen,variables->System.Select_struct.char_ref_array[current_player2].s_pic,xposition,virtscreen->h-26);
      unselect_palette();
    }
    
    xposition = xposition - 36;
    current_player --;
    current_player2--;
    if (current_player<0)
      current_player = variables->System.Select_struct.nb_char - 1;
    if (current_player2<0)
      current_player2 = variables->System.Select_struct.nb_char - 1;
  }
    
  // Showing big faces and names
  if (variables->System.Select_struct.p1_showed){
    current_char_index = variables->System.Select_struct.p1_position.x + variables->System.Select_struct.p1_position.y*variables->System.Select_struct.columns;
    current_player = (variables->System.Select_struct.char_list[current_char_index]);
    current_player--;
    
    select_palette(variables->System.Select_struct.char_ref_array[current_player].b_pic_pal);
    draw_sprite(virtscreen,variables->System.Select_struct.char_ref_array[current_player].b_pic,0,50);
    unselect_palette();
    textout_ex(virtscreen,font,variables->System.Select_struct.char_ref_array[current_player].display_name,0,50+variables->System.Select_struct.char_ref_array[current_player].b_pic->h+text_height(font),makecol(255,0,0),-1);
  }
  
  if (variables->System.Select_struct.p2_showed){
    current_char_index = variables->System.Select_struct.p2_position.x + variables->System.Select_struct.p2_position.y*variables->System.Select_struct.columns;
    current_player = (variables->System.Select_struct.char_list[current_char_index]);
    current_player--;
   
    select_palette(variables->System.Select_struct.char_ref_array[current_player].b_pic_pal);
    draw_sprite_h_flip(virtscreen,variables->System.Select_struct.char_ref_array[current_player].b_pic,virtscreen->w-(variables->System.Select_struct.char_ref_array[current_player].b_pic->w),50);
    textout_right_ex(virtscreen,font,variables->System.Select_struct.char_ref_array[current_player].display_name,virtscreen->w,50+variables->System.Select_struct.char_ref_array[current_player].b_pic->h+text_height(font),makecol(0,0,255),-1);
    unselect_palette();
  }
  
  /*
   * Showing bg name
   */
  TRON("Bg name");
  if (variables->System.Select_struct.stage_showed){
    if (!variables->System.Select_struct.bg_selected){
      if (!variables->System.Select_struct.bg_blinked){
	textprintf_centre_ex(virtscreen,font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(font)),makecol(10,10,100),-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
      }else{
	  textprintf_centre_ex(virtscreen,font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(font)),makecol(100,10,10),-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
      }
    }else{
      textprintf_centre_ex(virtscreen,font,variables->System.Select_struct.stageposx,variables->System.Select_struct.stageposy-(text_height(font)),makecol(100,10,100),-1,variables->System.Select_struct.bg_ref_array[variables->System.Select_struct.current_bg].display_name);
    }
  }
  
  free(message);
  return 0;
} // end kof91_select_output
