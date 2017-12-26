#include "choice_output.h"
#include "global.h"
#include <stdio.h>
#include "string.h"
#include "allegro.h"
#include "background_output.h"
#include "sensei_config.h"
#include "macros.h"
#include "logger.h"

/** \file choice_output.c
 * \brief Part of the engine that show the Menu screen (BG + fonts)
 */

int choice_output(Game_variables variables, int time){

  int i,current,levelx,levely;
  int error = 0;
  int posx,posy; /* position to write text */
  char * message;
  /* RGB -> color mapping table. Not needed, but speeds things up */
  RGB_MAP rgb_table;

  /* translucency color mapping table */
  COLOR_MAP trans_table;
  
  //temp system fonts data used to show items
  FNTInfo* fontInfo1_temp; //temp fnt
  message = (char*)calloc(255,sizeof(char));
  error = 0;
  /*
    title bg output (back)
  */
  error += background_output(&variables->System.Title_bg,0);
  if (error!=0) {
    fprintf(stderr,"In choice_output bg_output error\n");
    return -1;
  }else{
    //fprintf(stdout,"after bg output\n");
  }
  
  // TRON("before box");
  // For box translucy
  /* this isn't needed, but it speeds up the color table calculations */
  if (variables->System.boxvisible){
    create_rgb_table(&rgb_table, Pal, NULL);
    rgb_map = &rgb_table;
  }
  
  if (variables->System.boxvisible)
    /* build a color lookup table for translucent drawing */
    create_trans_table(&trans_table, Pal, 128, 128, 128, NULL);
  
  // if transparency hadn't start
  if (variables->System.transadd == 0)
    variables->System.transadd = 15;
  
  variables->System.transeffect = (variables->System.transeffect)+variables->System.transadd;
  if ((variables->System.transeffect<0)||(variables->System.transeffect>240)){
    variables->System.transadd = -(variables->System.transadd);
    if (variables->System.transeffect<0)
      variables->System.transeffect = 0;
    else
      variables->System.transeffect =240;
  }
  
  if (variables->System.boxvisible)
    /* select translucency blender */
    set_trans_blender(0, 0, 0, variables->System.transeffect);

  posx = (variables->System.posx);
  posy = (variables->System.posy);

  current = variables->System.firstitem;
  i = 0;
  levelx = ((variables->System.boxposition)*(variables->System.itemspacingx))+variables->System.posx;
  levely = ((variables->System.boxposition)*(variables->System.itemspacingy))+variables->System.posy;
  if (variables->System.boxvisible){
    drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
    rectfill(virtscreen,levelx+variables->System.boxcoordsx,levely+variables->System.boxcoordsy,levelx+variables->System.boxcoordsw,levely+variables->System.boxcoordsh,makecol(255,255,255));
  }


  // TRON("before fonts");
  while(i<(variables->System.visibleitems))
    {
      if ((variables->System.itemname[current]!=NULL)&&(strcmp(variables->System.itemname[current],"")!=0)){ // If active font
	if (current==variables->System.currentitem){
	  if (system_font_exists(variables,variables->System.itemactivefontnumber)){
	    // TRON("active font");
	    fontInfo1_temp = link_system_font(variables,variables->System.itemactivefontnumber);
	    // TRON("after assign");
	    // sprintf(message,"itemactivefontcolor = %i and option = %s",variables->System.itemactivefontcolor,variables->System.itemname[current]);
	    // TRON(message);
	    select_palette(*(fntGetPaletteForBank(fontInfo1_temp,variables->System.itemactivefontcolor)));
	    // TRON("after palette");
	    switch (variables->System.itemfontalignement){
	    case -1:
	      textprintf_ex(virtscreen,fontInfo1_temp->font,posx,posy-(text_height(fontInfo1_temp->font)),-1,-1,"%s",variables->System.itemname[current]);
	      break;
	    case 0:
	      textprintf_centre_ex(virtscreen,fontInfo1_temp->font,posx,posy-(text_height(fontInfo1_temp->font)),-1,-1,"%s",variables->System.itemname[current]);
	      break;
	    case 1:
	      textprintf_right_ex(virtscreen,fontInfo1_temp->font,posx,posy-(text_height(fontInfo1_temp->font)),-1,-1,"%s",variables->System.itemname[current]);
	      break;
	    }
	    unselect_palette();
	  }else{
	    textprintf_centre_ex(virtscreen,font,posx,posy-(int)(0.5*(text_height(font))),makecol(255,0,0),-1,"%s",variables->System.itemname[current]);
	  }
	}
	else{ // Inactive font
	  if (system_font_exists(variables,variables->System.itemfontnumber)){
	    // TRON("inactive font");
	    fontInfo1_temp = link_system_font(variables,variables->System.itemfontnumber);
	    select_palette(*(fntGetPaletteForBank(fontInfo1_temp,variables->System.itemfontcolor)));
	    switch (variables->System.itemfontalignement){
	    case -1:
	      textprintf_ex(virtscreen,fontInfo1_temp->font,posx,posy-(text_height(fontInfo1_temp->font)),-1,-1,"%s",variables->System.itemname[current]);
	      break;
	    case 0:
	      textprintf_centre_ex(virtscreen,fontInfo1_temp->font,posx,posy-(text_height(fontInfo1_temp->font)),-1,-1,"%s",variables->System.itemname[current]);
	      break;
	    case 1:
	      textprintf_right_ex(virtscreen,fontInfo1_temp->font,posx,posy-(text_height(fontInfo1_temp->font)),-1,-1,"%s",variables->System.itemname[current]);
	      break;
	     }
	    unselect_palette();
	  }else{
	    textprintf_centre_ex(virtscreen,font,posx,posy-(int)(0.5*(text_height(font))),makecol(100,100,100),-1,"%s",variables->System.itemname[current]);
	  }
	}
	posx = posx+(variables->System.itemspacingx);
	posy = posy+(variables->System.itemspacingy);
	i++;
      }
      current++;
      if (current>ITEM_NUMBER) current=0;
    }
  
  // TRON("after fonts");
  if (variables->System.boxvisible)
    /* select translucency blender */
    set_trans_blender(0, 0, 0, 255);
  
  /**
    title bg output (front)
  */
  error += background_output(&variables->System.Title_bg,1);
  if (error!=0) {
    fprintf(stderr,"In choice_output bg_output error\n");
    return 1;
  }else{
    //fprintf(stdout,"after bg output\n");
  }
  free(message);
  return 0;
}
