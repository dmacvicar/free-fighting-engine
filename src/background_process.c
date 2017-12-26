#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "background_process.h"

#include "global.h"

#include "macros.h"
#include "loads.h"
#include "logger.h"
#include "sensei_config.h"

/** \file background_process.c
 * \brief loading backgrounds and processing them.
 *
 * Functions that test BG syntaxes, load BG, fill BG elements.
 * Functions that process the bg elements assuming that their called each tick of game
*/


/** \brief Function that fill players base value (starting xposition, scaling ...) with bag values
 */
int fix_players(Game_variables variables, Player_variables * player_array){
  player_array[0].posx = variables->Fight_bg.p1startx;
  player_array[0].posy = variables->Fight_bg.p1starty + variables->Fight_bg.zoffset;
  player_array[3].posx = variables->Fight_bg.p2startx;
  player_array[3].posy = variables->Fight_bg.p2starty + variables->Fight_bg.zoffset;
  return 0;
}// fix_players


/**
  \brief function to have the name of the bg element take form a line
*/
char * bg_elt_name(char * Bg_name,char * input){
  char * name;
  char * message;
  int i = 1;
  int pos = 0;
  name = (char*)calloc(255,sizeof(char));
  message = (char*)calloc(255,sizeof(char));
  i = i + strlen(Bg_name);
  while (input[i]==' ') i++;
  while ((input[i]!=']')&&(input[i]!='\0')){
    name[pos]=input[i];
    pos++;
    i++;
  }
  pos++;
  name[pos]='\0';
  /*sprintf(message,"adding [%s %s] to array",Bg_name,name);
  TRON(message);
  */
  return name;
}


/** \brief function to know if a line is the beginning of a bg element
 *
*/
int is_bg_element(char * buff,char * Bg_name){
  int result = 0;
  //TRON("beginning is bg element");
  if (buff[0]!='['){
    return 0;
  }
  for (i=0;i<strlen(Bg_name);i++){
    if (to_minus(buff[1+i])!=to_minus(Bg_name[i]))
      return 0;
  }
  if (buff[strlen(Bg_name)+1]!=' ')
    return 0;
  result = 1;
  return result;
}

/** \brief function to convert a string into a bg_elt type
 */
int convert_bg_type(char * buf){
  int retour=0;
  if (strstr(string_to_minus(buf),"anim")!=NULL)
    retour = 1;
  if (strstr(string_to_minus(buf),"parallax")!=NULL)
    retour = 0;
  return retour;
}

/** \brief function to convert a trans mode into a % of transparency
*/
int convert_trans_mode(char * buf){
  int retour = 0;
  if (strstr(string_to_minus(buf),"add")!=NULL)
    retour = 25;
  if (strstr(string_to_minus(buf),"add1")!=NULL)
    retour = 50;
  if (strstr(string_to_minus(buf),"sub")!=NULL)
    retour = -1;
  return retour;
}

/** \brief general background process
 *
 */
int background_process(background_struct * a_background){
  char * front_path;
  char * message;
  char * result;
  char * real_bg_name;
  FILE * bg_file;
  char * line;
  int nb_bg_element = 0;
  int nb_action = 0;
  int total_lines = 0;
  int buffered_lines = 0;
  char ** Bg_elt_names;
  int * Action_nb;
  int * int_array;
  int error = 0;
  int i;
  int act_index; // to find the right index in action_array corresponding to act_nb
  if (SENSEI_DEBUG_ON)
    TRON("beginning background_process");
  message = (char*)calloc(255,sizeof(char));
  front_path = (char*)calloc(255,sizeof(char));
  line = (char*)calloc(255,sizeof(char));
  result = (char*)calloc(255,sizeof(char));
  int_array = (int*)calloc(8,sizeof(int));
  Bg_elt_names = NULL;
  Action_nb = NULL;
  
  if (a_background->loaded==0){
    switch (a_background->type){
    case 0:
      TRON("no bg");
      a_background->loaded = 1;
      break;
    case 1: // KOF 91 PCX
      a_background->Pcx_back = xload_pcx(a_background->bg_path,a_background->Pal_back);
      a_background->camerax = (int)(a_background->Pcx_back->w / 2);
      a_background->cameray = a_background->Pcx_back->h-virtscreen->h;
      /* Take from startmenu.c for compatibility with old kof 91 batle.c*/
      foreground = animated = 0;
      Bkgd = xload_pcx (a_background->bg_path, 0);
      bkgdlim = Bkgd->w - 320;
      zoomsup = Bkgd->h - 240;
      bkgd_delay = 15;
      zoomscreen = create_bitmap (Bkgd->w, Bkgd->h);
      result = strcpy ((char*)calloc(255,sizeof(char)), "midi");
      put_backslash(result);
      ustrncat (result, a_background->bg_path, y - 4);
      strcat (result, ".mid");
      music = xload_midi (file);
      /*************************/
      message = (char*)calloc(255,sizeof(char));
      sprintf(message,"Background %s loaded",a_background->bg_path);
      TRON(message);
      front_path = strcpy(front_path,"frgds/");
      front_path = strcat(front_path,a_background->bg_path);
      front_path = fix_filename_slashes(front_path);
      if (exists(front_path)){
	a_background->Pcx_front = load_pcx(front_path,a_background->Pal_front);
	Frgd = xload_pcx (front_path, 0); 
	TRON("foreground too");
      }else{
	a_background->type_front = 0;
      }
      a_background->loaded = 1;
      break;

    case 2: // KOF 91 flc
      break;
    case 3: // Mugen's bg.def
      message = (char*)calloc(255,sizeof(char));
      if (SENSEI_DEBUG_ON){
	sprintf(message,"Loading %s bg at %s",a_background->name,a_background->bg_path);
	TRON(message);
      }
      sensei_set_config_file(a_background->bg_path);
      //TRON("after sensei_set_config_file");
      a_background->bg_elt_nb = 0;
      // loading sff file if possible
     
	if (exists(a_background->bg_sff_path)){
	  if (SENSEI_DEBUG_ON){
	    sprintf(message,"Loading %s for %s",a_background->bg_sff_path,a_background->name);
	    TRON(message);
	  }
	  a_background->bg_sff = sffLoad(a_background->bg_sff_path);
	  TRON("after sff loading");
	}
	else{
	 sprintf(message,"warning no %s for bg sff",a_background->bg_sff_path);
	 TRON(message);
	  a_background->type = 0;
	  a_background->loaded = 1;
	  break;
	}
           
      // Filling BG with values
      a_background->startx = sensei_get_config_int("camera","startx",0);
      a_background->starty = sensei_get_config_int("camera","starty",0);
      a_background->p1startx = sensei_get_config_int("PlayerInfo","p1startx",-70);
      a_background->p2startx = sensei_get_config_int("PlayerInfo","p2startx",70);
      a_background->p1starty = sensei_get_config_int("PlayerInfo","p1starty",0);
      a_background->p2starty = sensei_get_config_int("PlayerInfo","p2starty",0);
      a_background->zoffset = sensei_get_config_int("StageInfo","zoffset",220);
     
      // Filling Bg music
      result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string("music","bgmusic",""));
      result = check_path(result,"sound","Bg Music",&error);
      if (error==0){
	a_background->bg_music.type = sensei_music_type(result);
	a_background->bg_music.path = strcpy((char*)calloc(255,sizeof(char)),result);
	a_background->bg_music.loaded = 0;
      }else{
	a_background->bg_music.type = 0;
      }

      // loading bg.def file to count the number and name of Bg elt
      bg_file = fopen(a_background->bg_path,"r");
      if (bg_file==NULL){
	message = (char*)calloc(255,sizeof(char));
	sprintf(message,"No %s bg found",a_background->bg_path);
	ERROR(message);
	return -1;
      }else{
	//TRON("file open");
      }

      // First find the number of Bg element and Action, and file the arrays with their names or numbers
      while (fgets(line,255*sizeof(char),bg_file)!=NULL){
	line = remove_comments(line);
	total_lines++; // just for stats
	if (strlen(line)>1){
	  buffered_lines++;
	  if (is_bg_element(line,a_background->name)){
	    nb_bg_element++;
	    Bg_elt_names = (char**)realloc(Bg_elt_names,nb_bg_element*sizeof(char*));
	    Bg_elt_names[nb_bg_element-1] = strcpy((char*)calloc(255,sizeof(char)),bg_elt_name(a_background->name,line));
	  }
	  if (is_bg_element(line,"begin action")){
	    nb_action++;
	    Action_nb = (int*)realloc(Action_nb,nb_action*sizeof(int));
	    Action_nb[nb_action-1] = action_nb(line);
	  }
	}
      }
      
      fclose(bg_file);
      //TRON("file closed");
      message=(char*)calloc(255,sizeof(char));
      if (SENSEI_DEBUG_ON){
	sprintf(message,"%i bg element, %i action found for %s with %i lines readed and %i lines usables ",nb_bg_element,nb_action,a_background->name,total_lines,buffered_lines);
	TRON(message);
      }
      
      // Filling each Bg elt with his vars
      a_background->bg_elt_nb = nb_bg_element;
      a_background->bg_elt_array = (background_elt_struct*)calloc(nb_bg_element,sizeof(background_elt_struct));
      for (i=0;i<nb_bg_element;i++){
	a_background->bg_elt_array[i].elt_name=strcpy((char*)calloc(255,sizeof(char)), Bg_elt_names[i]);
	real_bg_name = (char*)calloc(255,sizeof(char));
	sprintf(real_bg_name,"%s %s",a_background->name,Bg_elt_names[i]);
	if (SENSEI_DEBUG_ON){
	  sprintf(message,"looking into %s in %s",real_bg_name,a_background->bg_path);
	  TRON(message);
	}
	result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string(real_bg_name,"type","normal"));
	a_background->bg_elt_array[i].elt_type = convert_bg_type(result);
	result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string(real_bg_name,"start","0,0"));
	int_array = convert_string(result);
	a_background->bg_elt_array[i].startx = int_array[0];
	a_background->bg_elt_array[i].xposition = int_array[0] + a_background->startx;
	a_background->bg_elt_array[i].starty = int_array[1];
	a_background->bg_elt_array[i].yposition = int_array[1] + a_background->starty;
	a_background->bg_elt_array[i].layerno = sensei_get_config_int(real_bg_name,"layerno",0);
	result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string(real_bg_name,"spriteno","-1,-1"));
	int_array = convert_string(result);
	a_background->bg_elt_array[i].spritenog = int_array[0];
	a_background->bg_elt_array[i].spritenoi = int_array[1];
	a_background->bg_elt_array[i].actionno = sensei_get_config_int(real_bg_name,"actionno",-1);
	result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string(real_bg_name,"trans","none"));
	a_background->bg_elt_array[i].trans = convert_trans_mode(result);
	result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string(real_bg_name,"velocity","0,0"));
	int_array = convert_string(result);
	a_background->bg_elt_array[i].velocityx = int_array[0];
	a_background->bg_elt_array[i].velocityy = int_array[1];
	a_background->bg_elt_array[i].mask = sensei_get_config_int(real_bg_name,"mask",0);
	if (a_background->bg_elt_array[i].elt_type== 1)
	  a_background->bg_elt_array[i].mask = 1;
	result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string(real_bg_name,"tile","0,0"));
	int_array = convert_string(result);
	a_background->bg_elt_array[i].tilex = int_array[0];
	a_background->bg_elt_array[i].tiley = int_array[1];
	result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string(real_bg_name,"tilespacing","0,0"));
	int_array = convert_string(result);
	a_background->bg_elt_array[i].tilespacex = int_array[0];
	a_background->bg_elt_array[i].tilespacey = int_array[1];
	result = strcpy((char*)calloc(255,sizeof(char)),sensei_get_config_string(real_bg_name,"window","0,0,320,240"));
	int_array = convert_string(result);
	a_background->bg_elt_array[i].windowx = int_array[0];
	a_background->bg_elt_array[i].windowy = int_array[1];
	a_background->bg_elt_array[i].windoww = int_array[2];
	a_background->bg_elt_array[i].windowh = int_array[3];
      }
      
      // Filling each action with his elements
      a_background->action_nb = nb_action;
      a_background->action_array = (action_struct*)realloc(a_background->action_array,nb_action*sizeof(action_struct));
     
      for (i=0;i<nb_action;i++){
	a_background->action_array[i].number = Action_nb[i];
	if (SENSEI_DEBUG_ON){
	  sprintf(message,"putting index = %i for the %i action_array.number",Action_nb[i],i);
	  TRON(message);
	}
	fill_action(&a_background->action_array[i]);
      }
      
      // little debug loop
      for (i=0;i<nb_bg_element;i++){
	message = (char*)calloc(255,sizeof(char));
	sprintf(message,"name of %i bg_element = %s",i,a_background->bg_elt_array[i].elt_name);
	TRON(message);
	message = (char*)calloc(255,sizeof(char));
	sprintf(message,"type is %i",a_background->bg_elt_array[i].elt_type);
	TRON(message);
	sprintf(message,"start is %i,%i",a_background->bg_elt_array[i].startx,a_background->bg_elt_array[i].starty);
	TRON(message);
	sprintf(message,"layer is %i",a_background->bg_elt_array[i].layerno);
	TRON(message);
	sprintf(message,"spriteno is %i,%i",a_background->bg_elt_array[i].spritenog,a_background->bg_elt_array[i].spritenoi);
	TRON(message);
	sprintf(message,"actionno is %i",a_background->bg_elt_array[i].actionno);
	TRON(message);
	sprintf(message,"transmode is %i",a_background->bg_elt_array[i].trans);
	TRON(message);
	sprintf(message,"velocity = %i , %i",a_background->bg_elt_array[i].velocityx,a_background->bg_elt_array[i].velocityy);
	TRON(message);
	sprintf(message,"mask = %i",a_background->bg_elt_array[i].mask);
	TRON(message);
	sprintf(message,"Tile = %i , %i",a_background->bg_elt_array[i].tilex,a_background->bg_elt_array[i].tiley);
	TRON(message);
	sprintf(message,"Tilespacing = %i , %i",a_background->bg_elt_array[i].tilespacex,a_background->bg_elt_array[i].tilespacey);
	TRON(message);
	sprintf(message,"Window = %i,%i,%i,%i",a_background->bg_elt_array[i].windowx,a_background->bg_elt_array[i].windowy,a_background->bg_elt_array[i].windoww,a_background->bg_elt_array[i].windowh);
      }
      
      a_background->loaded = 1;
      break;
    default :
      a_background->loaded = 1;
      break;
    }
  }
  
  if (a_background->loaded!=0){
    switch (a_background->type){
    case 0: // no bg
      break;
    case 1 : // kof91.pcx
      break;
    case 2 : // KOF 91 FLC
      break;
    case 3: //Mugen's def
      for (i=0;i<a_background->bg_elt_nb;i++){
	switch (a_background->bg_elt_array[i].elt_type){
	case 0: // normal
	  a_background->bg_elt_array[i].xposition =  a_background->bg_elt_array[i].xposition + a_background->bg_elt_array[i].velocityx;
	  a_background->bg_elt_array[i].yposition =  a_background->bg_elt_array[i].yposition + a_background->bg_elt_array[i].velocityy;
	  break;
	case 1: // anim
	  TRON("processing animation");
	  act_index = -1;
	  for (j=0;j<a_background->action_nb;j++){
	    if (a_background->action_array[j].number==a_background->bg_elt_array[i].actionno)
	      act_index = j;
	  }
	  if (SENSEI_DEBUG_ON){
	    sprintf(message,"act index = %i",act_index);
	    TRON(message);
	  }
	  a_background->bg_elt_array[i].xposition = a_background->bg_elt_array[i].xposition + a_background->bg_elt_array[i].velocityx;
	  a_background->bg_elt_array[i].yposition = a_background->bg_elt_array[i].yposition + a_background->bg_elt_array[i].velocityy;
	  
	  // sprintf(message,"err n %i x= %i",i,a_background->bg_elt_array[i].xposition);
	  // TRON(message);

	  if (act_index!=-1){
	    process_action(&a_background->action_array[act_index]);
	    a_background->bg_elt_array[i].spritenoi = a_background->action_array[act_index].animation_array[a_background->action_array[act_index].current_element].spriteno;
	    a_background->bg_elt_array[i].spritenog = a_background->action_array[act_index].animation_array[a_background->action_array[act_index].current_element].groupeno;
	  }else{
	    a_background->bg_elt_array[i].spritenoi = -1;
	    a_background->bg_elt_array[i].spritenog = -1;
	  }
	  break;
      case 2: // parallax
	break;
      default:
	break;
      }
    }
    break;
  default :
    break;
  }
}
  if (SENSEI_DEBUG_ON)
    TRON("after bg process");
   free(message); 
  free(front_path); 
  free(line); 
  free(result);
  return 0;
}


