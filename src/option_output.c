#include "global.h"
#include "global_add.h"
#include "option_output.h"
#include "allegro.h"
#include "background_output.h"
#include "macros.h"
#include "logger.h"
#include "string.h"
#include <stdio.h>

/** \file option_output.c
 * \brief Functions to show option screen (where you can change game config)
 */

int option_output(Game_variables variables,Player_variables * player_array,int time){
  /* RGB -> color mapping table. Not needed, but speeds things up */
  RGB_MAP rgb_table;
  char * message;
  
  int textcolor,error;
  int truecolor = 0;
  FNTInfo * fontInfo_temp; //temp fnt for truecolor font
  FONT * font_temp;
  
  /* translucency color mapping table */
  COLOR_MAP trans_table;
  
  int boxcoordy;
  message = (char*)calloc(255,sizeof(char));
  error = 0;
  switch (variables->System.Ocurrentitem){
  case 0:
    boxcoordy = 40;
    break;
  case 1:
    boxcoordy = 57;
    break;
  case 2:
    boxcoordy = 74;
    break;
  case 3:
    boxcoordy = 91;
    break;
  case 4:
    boxcoordy = 108;
    break;
  case 5:
    boxcoordy = 125;
    break;
  case 6:
    boxcoordy = 142;
    break;
  case 7:
    boxcoordy = 159;
    break;
  case 8:
    boxcoordy = 176;
    break;
  case 9:
    boxcoordy = 193;
    break;
  default:
    boxcoordy = 40;
    break;
  }

  /*
   * showing Option BG (back)
   */
  error += background_output(&(variables->System.Option_bg),0);
  if (error!=0) {
    sprintf(message,"In Option_output bg_output error");
    ERROR(message);
    return -1;
  }else{
    //fprintf(stdout,"after bg output\n");
  }

  message = (char*)calloc(255,sizeof(char));
  create_rgb_table(&rgb_table, Pal, NULL);
  rgb_map = &rgb_table;
  textcolor = makecol(255,255,255);

  create_trans_table(&trans_table, Pal, 128, 128, 128, NULL);

  // if transparency hadn't start
  if (variables->System.Otransadd == 0)
    variables->System.Otransadd = 15;

  variables->System.Otranseffect = (variables->System.Otranseffect)+variables->System.Otransadd;
  if ((variables->System.Otranseffect<0)||(variables->System.Otranseffect>200)){
    variables->System.Otransadd = -(variables->System.Otransadd);
    if (variables->System.Otranseffect<0)
      variables->System.Otranseffect = 0;
    else
      variables->System.Otranseffect = 200;
  }

  set_trans_blender(0, 0, 0, 128);
  
  drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
  rectfill(virtscreen,55,35,260,215,makecol(10,30,190));
  line(virtscreen,54,36,54,214,makecol(30,50,210));
  line(virtscreen,56,34,259,34,makecol(30,50,210));
  line(virtscreen,261,36,261,214,makecol(30,50,210));
  line(virtscreen,56,216,259,216,makecol(30,50,210));

  /*
  // putting cursor box
  set_trans_blender(0, 0, 0, variables->System.Otranseffect);
  rectfill(virtscreen, 60, boxcoordy , 255 , boxcoordy+10, makecol(50,160,220));
  */
  
  set_trans_blender(0, 0, 0, 255);
  solid_mode();
  
  if (variables->System.font2exist)
    font_temp = variables->System.fontInfo2->font;
  else
    font_temp = font;
  
  if (truecolor==1){
    select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
    textcolor = -1;
  }
  
  textprintf_ex(virtscreen,font_temp,160,15,makecol(255,255,255),-1,"Options");
  
  if (truecolor==1)
    unselect_palette();
  
  // Showing options
  if (variables->System.Ocurrentitem == 0)
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
      textcolor = -1;
    }
    else
      textcolor = makecol(255,255,255);
  else
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,1)));
      textcolor = -1;
    }
    else
      textcolor = makecol(128,128,128);
  textprintf_ex(virtscreen,font_temp,65,35,textcolor,-1,"Difficulty");
  textprintf_right_ex(virtscreen,font_temp,250,35,textcolor,-1,"%i",variables->Game_config.Difficulty);
  if (truecolor==1)
    unselect_palette();

  if (variables->System.Ocurrentitem == 1)
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
      textcolor = -1;
    }
    else
      textcolor = makecol(255,255,255);
  else
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,1)));
      textcolor = -1;
    }
    else
      textcolor = makecol(128,128,128);
  textprintf_ex(virtscreen,font_temp,65,52,textcolor,-1,"Life");
  textprintf_right_ex(virtscreen,font_temp,250,52,textcolor,-1,"%i",variables->Game_config.Life);
  if (truecolor==1)
    unselect_palette();
  
  if (variables->System.Ocurrentitem == 2)
   if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
      textcolor = -1;
    }
    else
      textcolor = makecol(255,255,255);
  else
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,1)));
      textcolor = -1;
    }
    else
      textcolor = makecol(128,128,128);
  textprintf_ex(virtscreen,font_temp,65,69,textcolor,-1,"Time Limit");
  textprintf_right_ex(virtscreen,font_temp,250,69,textcolor,-1,"%i",variables->Game_config.Time);
  if (truecolor==1)
    unselect_palette();

  if (variables->System.Ocurrentitem == 3)
   if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
      textcolor = -1;
    }
    else
      textcolor = makecol(255,255,255);
  else
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,1)));
      textcolor = -1;
    }
    else
      textcolor = makecol(128,128,128);
  textprintf_ex(virtscreen,font_temp,65,86,textcolor,-1,"Game Speed");
  textprintf_right_ex(virtscreen,font_temp,250,86,textcolor,-1,"%i",variables->Game_config.Game_speed);
  if (truecolor==1)
    unselect_palette();

  if (variables->System.Ocurrentitem == 4)
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
      textcolor = -1;
    }
    else
      textcolor = makecol(255,255,255);
  else
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,1)));
      textcolor = -1;
    }
    else
      textcolor = makecol(128,128,128);
  textprintf_ex(virtscreen,font_temp,65,103,textcolor,-1,"Wav volume");
  textprintf_right_ex(virtscreen,font_temp,250,103,textcolor,-1,"%i",variables->Game_config.WavVolume);
  if (truecolor==1)
    unselect_palette();
  
  if (variables->System.Ocurrentitem == 5)
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
      textcolor = -1;
    }
    else
      textcolor = makecol(255,255,255);
  else
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,1)));
      textcolor = -1;
    }
    else
      textcolor = makecol(128,128,128);
  textprintf_ex(virtscreen,font_temp,65,120,textcolor,-1,"Midi volume");
  textprintf_right_ex(virtscreen,font_temp,250,120,textcolor,-1,"%i",variables->Game_config.MidiVolume);
  if (truecolor==1)
    unselect_palette();
  
  if (variables->System.Ocurrentitem == 6)
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
      textcolor = -1;
    }
    else
      textcolor = makecol(255,255,255);
  else
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,1)));
      textcolor = -1;
    }
    else
      textcolor = makecol(128,128,128);
  textprintf_ex(virtscreen,font_temp,65,137,textcolor,-1,"Input Config");
  textprintf_right_ex(virtscreen,font_temp,250,137,textcolor,-1,"( F2 )");
  if (truecolor==1)
    unselect_palette();
  
  if (variables->System.Ocurrentitem == 7)
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
      textcolor = -1;
    }
    else
      textcolor = makecol(255,255,255);
  else
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,1)));
      textcolor = -1;
    }
    else
      textcolor = makecol(128,128,128);
  textprintf_ex(virtscreen,font_temp,65,154,textcolor,-1,"Save Config");
  if (truecolor==1)
    unselect_palette();
  
  if (variables->System.Ocurrentitem == 8)
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
      textcolor = -1;
    }
    else
      textcolor = makecol(255,255,255);
  else
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,1)));
      textcolor = -1;
    }
    else
      textcolor = makecol(128,128,128);
  textprintf_ex(virtscreen,font_temp,65,171,textcolor,-1,"Default Values");
  if (truecolor==1)
    unselect_palette();

  if (variables->System.Ocurrentitem == 9)
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
      textcolor = -1;
    }
    else
      textcolor = makecol(255,255,255);
  else
    if (truecolor==1){
      select_palette(*(fntGetPaletteForBank(fontInfo_temp,1)));
      textcolor = -1;
    }
    else
      textcolor = makecol(128,128,128);
  textprintf_ex(virtscreen,font_temp,65,188,textcolor,-1,"Return to main menu"); 
  
  /*
   * showing Option BG (front)
   */
  error += background_output(&(variables->System.Option_bg),1);
  if (error!=0) {
    sprintf(message,"In Option_output bg_output error");
    ERROR(message);
    return -1;
  }else{
    //fprintf(stdout,"after bg output\n");
  }

  if (truecolor==1)
    unselect_palette();

  free(message);
  return 0;
}
