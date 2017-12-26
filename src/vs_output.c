#include "vs_output.h"
#include "background_output.h"
#include "macros.h"
#include "logger.h"
#include "sensei_config.h"

#include "stdio.h"

/** \file vs_output.c
 * \brief Functions to show vs_screen
 */

int vs_output(Game_variables variables,Player_variables * player_array,int time){
  int error;
  int p1scalex,p1scaley,p2scalex,p2scaley,p1_ref,p2_ref;
  int p1,p2;
  int xaxis = 0;
  int yaxis = 0;
  char * message;
  BITMAP * a_sprite = NULL;
  BITMAP * buffer = NULL;
  FNTInfo* fontInfo1_temp; // To stock fonts
  error = 0;
  message = (char*)malloc(255*sizeof(char));
  /*
   * showing Vs BG (back)
   */
  // fprintf(stdout,"beofr vs bg output\n");
  error += background_output(&(variables->System.Vs_bg),0);
  // fprintf(stdout,"after vs bg output\n");
  if (error!=0) {
    sprintf(message,"In Vs_output bg_output error");
    ERROR(message);
    return -1;
  }else{
    //fprintf(stdout,"after bg output\n");
  }
  
  // Showing p1 and p2 faces
  // Showing p1 face
  p1 = variables->System.Select_struct.p1_selected[0];
  p1_ref = variables->System.Select_struct.char_list[p1];
  p1_ref--;
  switch (variables->System.Select_struct.char_ref_array[p1_ref].type){
  case 0: // no char
    break;
  case 1: // kof 91 char
    p1scalex = (int)(variables->System.Select_struct.char_ref_array[p1_ref].b_pic->w*variables->System.Vs_struct.p1scalex);
    p1scaley = (int)(variables->System.Select_struct.char_ref_array[p1_ref].b_pic->h*variables->System.Vs_struct.p1scaley);
    a_sprite = create_bitmap_ex(bitmap_color_depth(variables->System.Select_struct.char_ref_array[p1_ref].b_pic),p1scalex,p1scaley);
    select_palette(variables->System.Select_struct.char_ref_array[p1_ref].b_pic_pal);
    set_color_conversion(COLORCONV_NONE);
    stretch_blit(variables->System.Select_struct.char_ref_array[p1_ref].b_pic,a_sprite,0,0,variables->System.Select_struct.char_ref_array[p1_ref].b_pic->w,variables->System.Select_struct.char_ref_array[p1_ref].b_pic->h,0,0,p1scalex,p1scaley);
    buffer = create_bitmap(a_sprite->w,a_sprite->h);
    blit(a_sprite,buffer,0,0,0,0,a_sprite->w,a_sprite->h);
    if (variables->System.Vs_struct.p1facing==1)
      draw_sprite(virtscreen,buffer,variables->System.Vs_struct.p1pos.x,variables->System.Vs_struct.p1pos.y);
    else
      draw_sprite_h_flip(virtscreen,buffer,variables->System.Vs_struct.p1pos.x-buffer->w,variables->System.Vs_struct.p1pos.y);
    unselect_palette();
    destroy_bitmap(buffer);
    break;
  case 2: // Mugen's char
    xaxis = variables->System.Select_struct.char_ref_array[p1_ref].big_xaxis;
    yaxis = variables->System.Select_struct.char_ref_array[p1_ref].big_yaxis;
    p1scalex = (int)(variables->System.Select_struct.char_ref_array[p1_ref].b_pic->w*variables->System.Vs_struct.p1scalex);
    p1scaley = (int)(variables->System.Select_struct.char_ref_array[p1_ref].b_pic->h*variables->System.Vs_struct.p1scaley);
    a_sprite = create_bitmap_ex(bitmap_color_depth(variables->System.Select_struct.char_ref_array[p1_ref].b_pic),p1scalex,p1scaley);
    select_palette(variables->System.Select_struct.char_ref_array[p1_ref].b_pic_pal);
    set_color_conversion(COLORCONV_NONE);
    stretch_blit(variables->System.Select_struct.char_ref_array[p1_ref].b_pic,a_sprite,0,0,variables->System.Select_struct.char_ref_array[p1_ref].b_pic->w,variables->System.Select_struct.char_ref_array[p1_ref].b_pic->h,0,0,p1scalex,p1scaley);
    buffer = create_bitmap(a_sprite->w,a_sprite->h);
    blit(a_sprite,buffer,0,0,0,0,a_sprite->w,a_sprite->h);
    if (variables->System.Vs_struct.p1facing==1)
      draw_sprite(virtscreen,buffer,variables->System.Vs_struct.p1pos.x-xaxis,variables->System.Vs_struct.p1pos.y-yaxis);
    else
      draw_sprite_h_flip(virtscreen,buffer,variables->System.Vs_struct.p1pos.x-buffer->w+xaxis,variables->System.Vs_struct.p1pos.y-yaxis);
    unselect_palette();
    destroy_bitmap(buffer);
    break;
  default:
    TRON("strange big face to show in vs screen");
    break;
  }
  
   // Showing p2 face
  p2 = variables->System.Select_struct.p2_selected[0];
  p2_ref = variables->System.Select_struct.char_list[p2];
  p2_ref--;
  switch (variables->System.Select_struct.char_ref_array[p2_ref].type){
  case 0: // no char
    break;
  case 1: // kof 91 char
    p2scalex = (int)(variables->System.Select_struct.char_ref_array[p2_ref].b_pic->w*variables->System.Vs_struct.p2scalex);
    p2scaley = (int)(variables->System.Select_struct.char_ref_array[p2_ref].b_pic->h*variables->System.Vs_struct.p2scaley);
    a_sprite = create_bitmap_ex(bitmap_color_depth(variables->System.Select_struct.char_ref_array[p2_ref].b_pic),p2scalex,p2scaley);
    select_palette(variables->System.Select_struct.char_ref_array[p2_ref].b_pic_pal);
    set_color_conversion(COLORCONV_NONE);
    stretch_blit(variables->System.Select_struct.char_ref_array[p2_ref].b_pic,a_sprite,0,0,variables->System.Select_struct.char_ref_array[p2_ref].b_pic->w,variables->System.Select_struct.char_ref_array[p2_ref].b_pic->h,0,0,p2scalex,p2scaley);
    buffer = create_bitmap(a_sprite->w,a_sprite->h);
    blit(a_sprite,buffer,0,0,0,0,a_sprite->w,a_sprite->h);
    if (variables->System.Vs_struct.p2facing==1)
      draw_sprite(virtscreen,buffer,variables->System.Vs_struct.p2pos.x,variables->System.Vs_struct.p2pos.y);
    else
      draw_sprite_h_flip(virtscreen,buffer,variables->System.Vs_struct.p2pos.x-buffer->w,variables->System.Vs_struct.p2pos.y);
    unselect_palette();
    destroy_bitmap(buffer);
    break;
  case 2: // Mugen's char
    xaxis = variables->System.Select_struct.char_ref_array[p2_ref].big_xaxis;
    yaxis = variables->System.Select_struct.char_ref_array[p2_ref].big_yaxis;
    p2scalex = (int)(variables->System.Select_struct.char_ref_array[p2_ref].b_pic->w*variables->System.Vs_struct.p2scalex);
    p2scaley = (int)(variables->System.Select_struct.char_ref_array[p2_ref].b_pic->h*variables->System.Vs_struct.p2scaley);
    a_sprite = create_bitmap_ex(bitmap_color_depth(variables->System.Select_struct.char_ref_array[p2_ref].b_pic),p2scalex,p2scaley);
    select_palette(variables->System.Select_struct.char_ref_array[p2_ref].b_pic_pal);
    set_color_conversion(COLORCONV_NONE);
    stretch_blit(variables->System.Select_struct.char_ref_array[p2_ref].b_pic,a_sprite,0,0,variables->System.Select_struct.char_ref_array[p2_ref].b_pic->w,variables->System.Select_struct.char_ref_array[p2_ref].b_pic->h,0,0,p2scalex,p2scaley);
    buffer = create_bitmap(a_sprite->w,a_sprite->h);
    blit(a_sprite,buffer,0,0,0,0,a_sprite->w,a_sprite->h);
    if (variables->System.Vs_struct.p2facing==1)
      draw_sprite(virtscreen,buffer,variables->System.Vs_struct.p2pos.x-xaxis,variables->System.Vs_struct.p2pos.y-yaxis);
    else
      draw_sprite_h_flip(virtscreen,buffer,variables->System.Vs_struct.p2pos.x-buffer->w+xaxis,variables->System.Vs_struct.p2pos.y-yaxis);
    unselect_palette();
    break;
  default:
    TRON("strange big face to show in vs screen");
    break;
  }

  
  TRON("showing p1 name");
  // Showing p1 name
  if (variables->System.Vs_struct.p1namefonti!=-1){
    if (system_font_exists(variables,variables->System.Vs_struct.p1namefonti)){
      fontInfo1_temp = link_system_font(variables,variables->System.Vs_struct.p1namefonti);
      select_palette(*(fntGetPaletteForBank(fontInfo1_temp,variables->System.Vs_struct.p1namefontcolor)));
      switch (variables->System.Vs_struct.p1namefontjust){
      case 1:
	textprintf_ex(virtscreen,fontInfo1_temp->font,variables->System.Vs_struct.p1namepos.x,variables->System.Vs_struct.p1namepos.y-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[p1_ref].display_name);
	break;
      case 0:
	textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Vs_struct.p1namepos.x,variables->System.Vs_struct.p1namepos.y-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[p1_ref].display_name);
	break;
      case -1:
	textprintf_right_ex(virtscreen,fontInfo1_temp->font,variables->System.Vs_struct.p1namepos.x,variables->System.Vs_struct.p1namepos.y-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[p1_ref].display_name);
	break;
      default:
	textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Vs_struct.p1namepos.x,variables->System.Vs_struct.p1namepos.y-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[p1_ref].display_name);
	break;
      }
      unselect_palette();
    }else{ // No system font
      textprintf_centre_ex(virtscreen,font,variables->System.Vs_struct.p1namepos.x,variables->System.Vs_struct.p1namepos.y-(text_height(font)),makecol(255,0,0),-1,variables->System.Select_struct.char_ref_array[p1_ref].display_name);
    }
  }

  
  // Showing p2 name
  if (variables->System.Vs_struct.p2namefonti!=-1){
    if (system_font_exists(variables,variables->System.Vs_struct.p2namefonti)){
      fontInfo1_temp = NULL;
      fontInfo1_temp = link_system_font(variables,variables->System.Vs_struct.p2namefonti);
      select_palette(*(fntGetPaletteForBank(fontInfo1_temp,variables->System.Vs_struct.p2namefontcolor)));
      switch (variables->System.Vs_struct.p2namefontjust){
      case 1:
	textprintf_ex(virtscreen,fontInfo1_temp->font,variables->System.Vs_struct.p2namepos.x,variables->System.Vs_struct.p2namepos.y-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[p2_ref].display_name);
	break;
      case 0:
	textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Vs_struct.p2namepos.x,variables->System.Vs_struct.p2namepos.y-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[p2_ref].display_name);
	break;
      case -1:
	textprintf_right_ex(virtscreen,fontInfo1_temp->font,variables->System.Vs_struct.p2namepos.x,variables->System.Vs_struct.p2namepos.y-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[p2_ref].display_name);
	break;
      default:
	textprintf_centre_ex(virtscreen,fontInfo1_temp->font,variables->System.Vs_struct.p2namepos.x,variables->System.Vs_struct.p2namepos.y-(text_height(fontInfo1_temp->font)),-1,-1,variables->System.Select_struct.char_ref_array[p2_ref].display_name);
	break;
      }
      unselect_palette();
    }else{ // No system font
      textprintf_centre_ex(virtscreen,font,variables->System.Vs_struct.p2namepos.x,variables->System.Vs_struct.p2namepos.y-(text_height(font)),makecol(255,0,0),-1,variables->System.Select_struct.char_ref_array[p2_ref].display_name);
    }
  }
  
  // Showing progress
  if (variables->System.Vs_struct.state>=1)
    textprintf_ex(virtscreen,font,160,200-(text_height(font)),makecol(255,255,255),-1,"Loading ...");
  
  /*
   * showing Vs BG (front)
   */
  error += background_output(&(variables->System.Vs_bg),1);
  if (error!=0) {
    sprintf(message,"In Vs_output bg_output error");
    ERROR(message);
    return -1;
  }else{
    //fprintf(stdout,"after bg output\n");
  }

  return 0;
}
