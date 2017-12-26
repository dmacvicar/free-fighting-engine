#include "global_add.h"
#include "allegro.h"
#include "global.h"
#include "string.h"
#include "macros.h"
#include "logger.h"
#include "stdio.h"
#include "background_output.h"

/** \file keyconfig_output.c
 * \brief function to show the Option Key Configuration screen
 */

int keyconfig_output(Game_variables variables,Player_variables * player_array,int time){
 
  /* RGB -> color mapping table. Not needed, but speeds things up */
  RGB_MAP rgb_table;
  char * message;
  char * path;
  int textcolor,error;
  FONT * font_temp;
  FNTInfo* fontInfo_temp; //temp fnt for truecolor font
  int truecolor = 0;

  /* translucency color mapping table */
  COLOR_MAP trans_table;
  
  int boxcoordy;
  int boxcoordy2;
  error = 0;
  path = (char*)calloc(20,sizeof(char));
  switch (variables->System.Ocurrentitem){
  case 0:
    boxcoordy = 40;
    break;
  case 1:
    boxcoordy = 53;
    break;
  case 2:
    boxcoordy = 66;
    break;
  case 3:
    boxcoordy = 79;
    break;
  case 4:
    boxcoordy = 92;
    break;
  case 5:
    boxcoordy = 105;
    break;
  case 6:
    boxcoordy = 118;
    break;
  case 7:
    boxcoordy = 131;
    break;
  case 8:
    boxcoordy = 143;
    break;
  case 9:
    boxcoordy = 156;
    break;
  case 10:
    boxcoordy = 169;
    break;
  case 11:
    boxcoordy = 182;
    break;
  case 12:
    boxcoordy = 195;
    break;
  case 13:
    boxcoordy = 206;
    break;
  default:
    boxcoordy = 40;
    break;
  }

  switch (variables->System.Ocurrentitem2){
  case 0:
    boxcoordy2 = 40;
    break;
  case 1:
    boxcoordy2 = 53;
    break;
  case 2:
    boxcoordy2 = 66;
    break;
  case 3:
    boxcoordy2 = 79;
    break;
  case 4:
    boxcoordy2 = 92;
    break;
  case 5:
    boxcoordy2 = 105;
    break;
  case 6:
    boxcoordy2 = 118;
    break;
  case 7:
    boxcoordy2 = 131;
    break;
  case 8:
    boxcoordy2 = 143;
    break;
  case 9:
    boxcoordy2 = 156;
    break;
  case 10:
    boxcoordy2 = 169;
    break;
  case 11:
    boxcoordy2 = 182;
    break;
  case 12:
    boxcoordy2 = 195;
    break;
  case 13:
    boxcoordy2 = 206;
    break;
  default:
    boxcoordy2 = 40;
    break;
  }
  
  message = (char*)calloc(255,sizeof(char));

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
  
  create_rgb_table(&rgb_table, Pal, NULL);
  rgb_map = &rgb_table;
  textcolor = makecol(128,128,128);

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
  
  /*
  select_palette(Pal);
  blit(Title,virtscreen,0,0,0,0,320,240);
  unselect_palette();
  */

  drawing_mode(DRAW_MODE_TRANS,NULL,0,0);
  rectfill(virtscreen,55,35,260,215,makecol(10,30,190));
  line(virtscreen,54,36,54,214,makecol(30,50,210));
  line(virtscreen,56,34,259,34,makecol(30,50,210));
  line(virtscreen,261,36,261,214,makecol(30,50,210));
  line(virtscreen,56,216,259,216,makecol(30,50,210));
  
  set_trans_blender(0, 0, 0, 255);
 
  if (variables->System.font2exist)
    font_temp = variables->System.fontInfo2->font;
  else
    font_temp = font;
  
  if (truecolor==1){
    select_palette(*(fntGetPaletteForBank(fontInfo_temp,0)));
      textcolor = -1;
  }
  else
    textcolor = makecol(255,255,255);
  textprintf_centre_ex(virtscreen,font_temp,160,10,textcolor,-1,"Input Config");
  if (truecolor==1)
    unselect_palette();
    
  /*
  // putting cursor boxes
  set_trans_blender(0, 0, 0, variables->System.Otranseffect);
  // Player 1 box
  rectfill(virtscreen, 60, boxcoordy , 150 , boxcoordy+10, makecol(50,160,220));
  // player 2 box
  rectfill(virtscreen, 165, boxcoordy2, 255, boxcoordy2+10, makecol(50,160,220));
  */
  
  // Showing options p1
  if (player_array[0].Player_input.use_joystick == 0)
    message = strcpy(message,"Key");
  else{
    sprintf(message,"Joy %i",player_array[0].Player_input.use_joystick);
  }
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
  textprintf_centre_ex(virtscreen,font_temp,105,35,textcolor,-1,"P1 :%s",message);
  if (truecolor==1)
    unselect_palette();

  message = (char*)calloc(255,sizeof(char));
  if (player_array[0].Player_input.use_joystick == 0)
    sprintf(message,"Up : %i",player_array[0].Player_input.keys[0]);
  else{
    sprintf(message,"J up");
  }
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
  textprintf_centre_ex(virtscreen,font_temp,105,48,textcolor,-1,"%s",message);
  
  message = (char*)calloc(255,sizeof(char));
  if (player_array[0].Player_input.use_joystick == 0)
    sprintf(message,"Down : %i",player_array[0].Player_input.keys[1]);
  else{
    sprintf(message,"J down");
  }
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
  textprintf_centre_ex(virtscreen,font_temp,105,61,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[0].Player_input.use_joystick == 0)
    sprintf(message,"Left : %i",player_array[0].Player_input.keys[2]);
  else{
    sprintf(message,"J left");
  }
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
  textprintf_centre_ex(virtscreen,font_temp,105,74,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[0].Player_input.use_joystick == 0)
    sprintf(message,"Right : %i",player_array[0].Player_input.keys[3]);
  else{
    sprintf(message,"J right");
  }
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
  textprintf_centre_ex(virtscreen,font_temp,105,87,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[0].Player_input.use_joystick == 0)
    sprintf(message,"A : %i",player_array[0].Player_input.keys[4]);
  else{
    sprintf(message,"A : %i",player_array[0].Player_input.joybuton[0]);
  }
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
  textprintf_centre_ex(virtscreen,font_temp,105,100,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[0].Player_input.use_joystick == 0)
    sprintf(message,"B : %i",player_array[0].Player_input.keys[5]);
  else{
    sprintf(message,"B : %i",player_array[0].Player_input.joybuton[1]);
  }
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
  textprintf_centre_ex(virtscreen,font_temp,105,113,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[0].Player_input.use_joystick == 0)
    sprintf(message,"C : %i",player_array[0].Player_input.keys[6]);
  else{
    sprintf(message,"C : %i",player_array[0].Player_input.joybuton[2]);
  }
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
  textprintf_centre_ex(virtscreen,font_temp,105,126,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[0].Player_input.use_joystick == 0)
    sprintf(message,"X : %i",player_array[0].Player_input.keys[7]);
  else{
    sprintf(message,"X : %i",player_array[0].Player_input.joybuton[3]);
  }
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
  textprintf_centre_ex(virtscreen,font_temp,105,139,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[0].Player_input.use_joystick == 0)
    sprintf(message,"Y : %i",player_array[0].Player_input.keys[8]);
  else{
    sprintf(message,"Y : %i",player_array[0].Player_input.joybuton[4]);
  }
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
  textprintf_centre_ex(virtscreen,font_temp,105,152,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[0].Player_input.use_joystick == 0)
    sprintf(message,"Z : %i",player_array[0].Player_input.keys[9]);
  else{
    sprintf(message,"Z : %i",player_array[0].Player_input.joybuton[5]);
  }
  if (variables->System.Ocurrentitem == 10)
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
  textprintf_centre_ex(virtscreen,font_temp,105,165,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[0].Player_input.use_joystick == 0)
    sprintf(message,"Start : %i",player_array[0].Player_input.keys[10]);
  else{
    sprintf(message,"Start : %i",player_array[0].Player_input.joybuton[6]);
  }
  if (variables->System.Ocurrentitem == 11)
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
  textprintf_centre_ex(virtscreen,font_temp,105,178,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  sprintf(message,"Default");
  if (variables->System.Ocurrentitem == 12)
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
  textprintf_centre_ex(virtscreen,font_temp,105,191,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  sprintf(message,"Exit");
  if (variables->System.Ocurrentitem == 13)
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
  textprintf_centre_ex(virtscreen,font_temp,105,204,textcolor,-1,"%s",message);

   // Showing options p2
  if (player_array[1].Player_input.use_joystick == 0)
    message = strcpy(message,"Key");
  else{
    sprintf(message,"Joy %i",player_array[1].Player_input.use_joystick);
  }
  if (variables->System.Ocurrentitem2 == 0)
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
  textprintf_centre_ex(virtscreen,font_temp,210,35,textcolor,-1,"P2 :%s",message);
  if (truecolor==1)
    unselect_palette();

  message = (char*)calloc(255,sizeof(char));
  if (player_array[1].Player_input.use_joystick == 0)
    sprintf(message,"Up : %i",player_array[1].Player_input.keys[0]);
  else{
    sprintf(message,"J up");
  }
  if (variables->System.Ocurrentitem2 == 1)
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
  textprintf_centre_ex(virtscreen,font_temp,210,48,textcolor,-1,"%s",message);
  
  message = (char*)calloc(255,sizeof(char));
  if (player_array[1].Player_input.use_joystick == 0)
    sprintf(message,"Down : %i",player_array[1].Player_input.keys[1]);
  else{
    sprintf(message,"J down");
  }
  if (variables->System.Ocurrentitem2 == 2)
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
  textprintf_centre_ex(virtscreen,font_temp,210,61,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[1].Player_input.use_joystick == 0)
    sprintf(message,"Left : %i",player_array[1].Player_input.keys[2]);
  else{
    sprintf(message,"J left");
  }
  if (variables->System.Ocurrentitem2 == 3)
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
  textprintf_centre_ex(virtscreen,font_temp,210,74,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[1].Player_input.use_joystick == 0)
    sprintf(message,"Right : %i",player_array[1].Player_input.keys[3]);
  else{
    sprintf(message,"J right");
  }
  if (variables->System.Ocurrentitem2 == 4)
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
  textprintf_centre_ex(virtscreen,font_temp,210,87,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[1].Player_input.use_joystick == 0)
    sprintf(message,"A : %i",player_array[1].Player_input.keys[4]);
  else{
    sprintf(message,"A : %i",player_array[1].Player_input.joybuton[0]);
  }
  if (variables->System.Ocurrentitem2 == 5)
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
  textprintf_centre_ex(virtscreen,font_temp,210,100,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[1].Player_input.use_joystick == 0)
    sprintf(message,"B : %i",player_array[1].Player_input.keys[5]);
  else{
    sprintf(message,"B : %i",player_array[1].Player_input.joybuton[1]);
  }
  if (variables->System.Ocurrentitem2 == 6)
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
  textprintf_centre_ex(virtscreen,font_temp,210,113,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[1].Player_input.use_joystick == 0)
    sprintf(message,"C : %i",player_array[1].Player_input.keys[6]);
  else{
    sprintf(message,"C : %i",player_array[1].Player_input.joybuton[2]);
  }
  if (variables->System.Ocurrentitem2 == 7)
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
  textprintf_centre_ex(virtscreen,font_temp,210,126,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[1].Player_input.use_joystick == 0)
    sprintf(message,"X : %i",player_array[1].Player_input.keys[7]);
  else{
    sprintf(message,"X : %i",player_array[1].Player_input.joybuton[3]);
  }
  if (variables->System.Ocurrentitem2 == 8)
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
  textprintf_centre_ex(virtscreen,font_temp,210,139,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[1].Player_input.use_joystick == 0)
    sprintf(message,"Y : %i",player_array[1].Player_input.keys[8]);
  else{
    sprintf(message,"Y : %i",player_array[1].Player_input.joybuton[4]);
  }
  if (variables->System.Ocurrentitem2 == 9)
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
  textprintf_centre_ex(virtscreen,font_temp,210,152,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[1].Player_input.use_joystick == 0)
    sprintf(message,"Z : %i",player_array[1].Player_input.keys[9]);
  else{
    sprintf(message,"Z : %i",player_array[1].Player_input.joybuton[5]);
  }
  if (variables->System.Ocurrentitem2 == 10)
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
  textprintf_centre_ex(virtscreen,font_temp,210,165,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  if (player_array[1].Player_input.use_joystick == 0)
    sprintf(message,"Start : %i",player_array[1].Player_input.keys[10]);
  else{
    sprintf(message,"Start : %i",player_array[1].Player_input.joybuton[6]);
  }
  if (variables->System.Ocurrentitem2 == 11)
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
  textprintf_centre_ex(virtscreen,font_temp,210,178,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  sprintf(message,"Default");
  if (variables->System.Ocurrentitem2 == 12)
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
  textprintf_centre_ex(virtscreen,font_temp,210,191,textcolor,-1,"%s",message);

  message = (char*)calloc(255,sizeof(char));
  sprintf(message,"Exit");
  if (variables->System.Ocurrentitem2 == 13)
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
  textprintf_centre_ex(virtscreen,font_temp,210,204,textcolor,-1,"%s",message);

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
  
  return 0;
}
