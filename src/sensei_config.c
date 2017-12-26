#include "sensei_config.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "background_process.h"
#include "mp3.h"

#include "macros.h"
#include "logger.h"
#include "loads.h"
#include "allegro.h"
#include "global.h"

/** \file sensei_config.c
 * \brief configuration routines (source) to fix Allegro's config.c lakes
 *
 * Like a degraded config.c but with space support in section names and ';' used for comments and usefull function to dealds with Sensei Global_add.h structs
*/

/** \brief Function to know if a system font exists
    usefull because system fonts aren't stored yet in an array
*/
int system_font_exists(Game_variables variables,int font_number){
  switch (font_number){
  case 0:
    return (variables->System.font0exist);
    break;
  case 1:
    return (variables->System.font1exist);
    break;
  case 2:
    return (variables->System.font2exist);
    break; 
  case 3:
    return (variables->System.font3exist);
    break;
  case 4:
    return (variables->System.font4exist);
    break;
  case 5:
    return (variables->System.font5exist);
    break;
  case 6:
    return (variables->System.font6exist);
    break; 
  case 7:
    return (variables->System.font7exist);
    break;
  case 8:
    return (variables->System.font8exist);
    break;
  case 9:
    return (variables->System.font9exist);
    break;
  default:
    return 0;
    break;
  }
  return 0;
}// end of system_font_exists

/** \brief Function that return a pointer to the system font wanted
 */
FNTInfo * link_system_font(Game_variables variables,int font_number){
  switch (font_number){
  case 0:
    return (variables->System.fontInfo0);
    break;
  case 1:
    return (variables->System.fontInfo1);
    break;
  case 2:
    return (variables->System.fontInfo2);
    break;
  case 3:
    return (variables->System.fontInfo3);
    break;
  case 4:
    return (variables->System.fontInfo4);
    break;
  case 5:
    return (variables->System.fontInfo5);
    break;
  case 6:
    return (variables->System.fontInfo6);
    break;
  case 7:
    return (variables->System.fontInfo7);
    break;
  case 8:
    return (variables->System.fontInfo8);
    break;
  case 9:
    return (variables->System.fontInfo9);
    break; 
  default :
    return NULL;
  }
  return NULL;
}// link_system_font

/** \brief function to convert into minus a char
 */
char to_minus(char a_char)
{
  return (tolower(a_char));
}

char * string_to_minus(char * a_string){
  char * result;
  int length;
  int i;
  result = (char*)calloc(255,sizeof(char));
  length = strlen(a_string);
  for (i=0;i<strlen(a_string);i++)
    result[i]=to_minus(a_string[i]);
  result[i+1]='\0';
  return result;
}

/** \brief function to extract relative path from a .def path
 */
char * extract_path(char * a_path){
  char * retour;
  int index;
  retour = (char*)calloc(255,sizeof(char));
  index = strlen(a_path) - 1;
  while ((index>0)&&(a_path[index]!='/')&&(a_path[index]!='\\'))
    index--;
  retour = strncpy((char*)calloc(255,sizeof(char)),a_path,index*sizeof(char));
  retour[index]='\0';
  return retour;
}// extract_path

/** \brief function to remove spaces at the end of a line
 *
 */
char * remove_end_spaces(char * line){
  char * retour;
  int i;
  int length = strlen(line);
  length--;
  retour = (char*)calloc(255,sizeof(char));
  while (((line[length]==' ')||(line[length]=='\0')||(line[length]=='\n')||(line[length]=='\t'))&&(length>1))
    length--;
  for (i=0;i<=length;i++)
    retour[i]=line[i];
  retour[i]='\0';
  //TRON(retour);
  return retour;
}


/**
 *  \brief function to remove comments from a ligne (and spaces at the beginning too)
*/
char * remove_comments(char * a_string){
  char * result;
  int read_index;
  int write_index;
  result = (char*)calloc(255,sizeof(char));
  
  read_index = 0;
  write_index = 0;
  while (a_string[read_index]==' ')
    read_index++;
  
  while ((a_string[read_index]!='\n')&&(a_string[read_index]!='\r')&&(a_string[read_index]!='\0')&&(a_string[read_index]!=';')){
    result[write_index] = a_string[read_index];
    write_index++;
    read_index++;
  }
  write_index++;
  result[write_index]='\0';
  result = remove_end_spaces(result);
  return result;
}

/** \brief function to know if a line is a section tag
 *
*/
int is_section(char * buff,char * section_name){
  int i;
  int result = 0;
  // char * message; //debug with fprintf
  
  //TRON("beginning is bg element");
  if (buff[0]!='['){
    //message = (char*)calloc(255,sizeof(char));
    //sprintf(message,"is section(%s), char[%i]!='['\n",section_name,0);
    //fprintf(stdout,message);
    return 0;
  }
  for (i=0;i<strlen(section_name);i++){
    if (to_minus(buff[1+i])!=to_minus(section_name[i])){
      //message = (char*)calloc(255,sizeof(char));
      //sprintf(message,"is section(%s), char[%i]==%c != %c\n",section_name,i,buff[i+1],section_name[i]);
      //fprintf(stdout,message);
      return 0;
    }
  }
  if (buff[strlen(section_name)+1]!=']')
    return 0;
  result = 1;
  //message = (char*)calloc(255,sizeof(char));
  //sprintf(message,"is section(%s) = %i\n",section_name,result);
  //fprintf(stdout,message);
  return result;
}

int degraded_is_section(char * buff,char * section_name){
  int i;
  int result = 0;
  // char * message; //debug with fprintf
  
  //TRON("beginning is bg element");
  if (buff[0]!='['){
    //message = (char*)calloc(255,sizeof(char));
    //sprintf(message,"is section(%s), char[%i]!='['\n",section_name,0);
    //fprintf(stdout,message);
    return 0;
  }
  for (i=0;i<strlen(section_name);i++){
    if (to_minus(buff[1+i])!=to_minus(section_name[i])){
      //message = (char*)calloc(255,sizeof(char));
      //sprintf(message,"is section(%s), char[%i]==%c != %c\n",section_name,i,buff[i+1],section_name[i]);
      //fprintf(stdout,message);
      return 0;
    }
  }
  
  if (buff[strlen(section_name)+1]!=' ')
    return 0;
  
  result = 1;
  
  return result;
}// end of degraded_is_section



/** \brief function that return a int var value if there's one
 *
 */
int int_var_value(char * var, int default_value){
  int retour = default_value;
  int var_found = 0;
  int read_index = 0;
  int write_index;
  int good_char = 1;
  char * int_to_convert;
  char * message; // debug with fprintf
  int_to_convert = (char*)calloc(255,sizeof(char));
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(var_found==0)){
    read_index = 0;
    good_char = 1;

    //exception, if we begin another section
    if (SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]=='[')
      return retour;

    // reading var name
    while ((read_index<strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE]))&&(read_index<strlen(var))&&(good_char==1)){
      //message = (char*)calloc(255,sizeof(char)); 
      //sprintf(message,"reading var name=%s , %i line ,%i char\n",var,CURRENT_LINE,read_index);
      //fprintf(stdout,message);
      if (to_minus(SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index])!=to_minus(var[read_index]))
	good_char = 0;
      read_index++;
      message = (char*)calloc(255,sizeof(char)); 
    }
    if (read_index<strlen(var))
      good_char = 0;
    //message = (char*)calloc(255,sizeof(char)); 
    //sprintf(message,"reading var name=%s , %i line ,%i char and good_char = %i current char is '%c'\n",var,CURRENT_LINE,read_index, good_char,SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]);
    //fprintf(stdout,message);
    if (good_char==1){
      //read_index++;
      if ((SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]==' ')||(SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]=='=')||(SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]=='\t')){
       	while ((read_index<strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE]))&&((SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]==' ')||( SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]=='\t'))){
	  //message = (char*)calloc(255,sizeof(char));
	  //sprintf(message,"reading passing spaces 1\n");
	  //fprintf(stdout,message);
	  read_index++;
	}
	if (read_index!=strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE])){
	  if (SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]=='='){
	    read_index++;
	    if (SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]==' '){
	      while ((read_index<strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE]))&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]==' ')){
		read_index++;
	      }
	    }
	    write_index = 0;
	    while ((read_index<strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE]))&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]!=' ')){
	      int_to_convert[write_index] = SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index];
		write_index++;
		read_index++;
	    }
	    retour = atoi(int_to_convert);
	    var_found = 1;
	  }
	}
      }
    }else{
      CURRENT_LINE++;
      read_index = 0;
    }
  }
  if (var_found==0){
    CURRENT_LINE = 0;
    return retour;
  }
  
  CURRENT_LINE = 0;
  return retour;
}

/** \brief like get_config_int but with spaces
 */
int sensei_get_config_int(char * section_name,char * var,int default_value){
  int section_found;
  int retour;
  // char * message;// for debugging fprintf
  CURRENT_LINE = 0;
  section_found = 0;
  retour =  default_value;
  //fprintf(stdout,"int SENSEI_NB_LINES %i\n",SENSEI_NB_LINES);
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(section_found==0)){
    //message=(char*)calloc(255,sizeof(char));
    //sprintf(message,"int analyze : %s \n",SENSEI_BUFFERED_FILE[CURRENT_LINE]);
    //fprintf(stdout,message);
    if (is_section(SENSEI_BUFFERED_FILE[CURRENT_LINE],section_name)!=0)
      section_found=1;
    CURRENT_LINE++;
  }
  if (section_found==0){
    CURRENT_LINE = 0;
    return retour;
  }
  
  retour = int_var_value(var,default_value);
  return retour;
}

/** \brief function that return a char * var value if there's one
 *
 */
char * char_var_value(char * var, char * default_value){
  char * retour;
  int var_found = 0;
  int read_index = 0;
  int write_index;
  int good_char = 1;
  char * message; // debug with fprintf
  retour = (char*)calloc(255,sizeof(char));
  retour = strcpy(retour,default_value);
  
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(var_found==0)){
    read_index = 0;
    good_char = 1;
    
    //exception, if we begin another section
    if (SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]=='[')
      return retour;
    
    // reading var name
    while ((read_index<strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE]))&&(read_index<strlen(var))&&(good_char==1)){
      message = (char*)calloc(255,sizeof(char)); 
      //sprintf(message,"reading var name=%s , %i line ,%i char\n",var,CURRENT_LINE,read_index);
      //TRON(message);
      if (to_minus(SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index])!=to_minus(var[read_index]))
	good_char = 0;
      read_index++;
      message = (char*)calloc(255,sizeof(char)); 
    }
    if (read_index<strlen(var))
      good_char = 0;
    //message = (char*)calloc(255,sizeof(char)); 
    //sprintf(message,"reading var name=%s , %i line ,%i char and good_char = %i current char is '%c'\n",var,CURRENT_LINE,read_index, good_char,SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]);
    //fprintf(stdout,message);
    if (good_char==1){
      //read_index++;
      if ((SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]==' ')||(SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]=='=')||(SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]=='\t')){
       	while ((read_index<strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE]))&&((SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]==' ')||(SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]=='\t'))){
	  //message = (char*)calloc(255,sizeof(char));
	  //sprintf(message,"reading passing spaces 1\n");
	  //fprintf(stdout,message);
	  read_index++;
	}
	
	if (read_index!=strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE])){
	  //TRON("have read var and and end of line");
	  
	  if (SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]=='=')
	    read_index++;
	  
	  if (SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]==' '){
	    while ((read_index<strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE]))&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]==' ')){
	      read_index++;
	    }
	  }
	  
	  if (SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]==' '){
	    while ((read_index<strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE]))&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index]==' ')){
	      read_index++;
	    }
	  }
	  
	  // Here we begin to read the var value
	  write_index = 0;
	  while ((read_index<strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE]))){
	    retour[write_index] = SENSEI_BUFFERED_FILE[CURRENT_LINE][read_index];
	    write_index++;
	    read_index++;
	  }
	  
	  if (write_index<strlen(default_value))
	    retour[write_index]='\0';
	  
	  //TRON("before remove end spaces2");
	  //sprintf(message,"passing %s to remove end spaces",retour);
	  //TRON(message);
	  retour = remove_end_spaces(retour);
	  var_found = 1;
	  return retour;
	}
      }
    }
    
    CURRENT_LINE++;
    read_index = 0;
  }
  
  if (var_found==0){
    CURRENT_LINE = 0;
    return retour;
  }
  
  CURRENT_LINE = 0;
  return retour;
}

/** \brief like get_config_string but with spaces
 */
char * sensei_get_config_string(char * section_name,char * var, char * default_value){
  char * retour;
  char * message; // for debugging fprintf
  int section_found = 0;
  CURRENT_LINE = 0;
  retour = (char *)calloc(255,sizeof(char));
  retour = strcpy(retour,default_value);
  message = (char*)calloc(255,sizeof(char));
  //sprintf(message,"looking for [%s] and var = %s",section_name,var);
  //TRON(message);
  //fprintf(stdout,"char * SENSEI_NB_LINES %i\n",SENSEI_NB_LINES);
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(section_found==0)){
    //message=(char*)calloc(255,sizeof(char));
    //sprintf(message,"char * analyze : %s \n",SENSEI_BUFFERED_FILE[CURRENT_LINE]);
    //fprintf(stdout,message);
    if (is_section(SENSEI_BUFFERED_FILE[CURRENT_LINE],section_name))
      section_found=1;
    CURRENT_LINE++;
  }
  if (section_found==0){
    CURRENT_LINE = 0;
    //sprintf(message,"nothing found");
    //TRON(message);
    return retour;
  }
  //TRON("bfore char var value");
  retour = char_var_value(var,default_value);
  
  //TRON("end of sensei_get_config_string");
  return retour;
}

/** \brief like Allegro's set config_file
 *
 * Open the config file and stock it in a Buffer to search for vars with sensei_get_config_string and sensei_get_config_int
 */
int sensei_set_config_file(char * path){
  char * message;
  char * line;
  int total_lines;
  FILE * config_file;
  message = (char*)calloc(255,sizeof(char));
  line = (char*)calloc(255,sizeof(char));
  SENSEI_NB_LINES = 0;
  //SENSEI_BUFFERED_FILE = NULL;
  total_lines = 0;
  config_file = fopen(path,"r");
  if (config_file==NULL){
    message = (char*)calloc(255,sizeof(char));
    sprintf(message,"No %s config found\n",path);
    fprintf(stderr,message);
    return -1;
  }else{
    //fprintf(stdout,"config file open\n");
  }
  while (fgets(line,255*sizeof(char),config_file)!=NULL){
    line = remove_comments(line);
    line = remove_end_spaces(line);
    total_lines++; // just for fun
    if (strlen(line)>=1){
      SENSEI_NB_LINES++;
      SENSEI_BUFFERED_FILE = (char**)realloc(SENSEI_BUFFERED_FILE,SENSEI_NB_LINES*sizeof(char*));
      SENSEI_BUFFERED_FILE[SENSEI_NB_LINES-1] = (char*)calloc(255,sizeof(char));
      SENSEI_BUFFERED_FILE[SENSEI_NB_LINES-1] = strcpy(SENSEI_BUFFERED_FILE[SENSEI_NB_LINES-1],line);
    }
  }
  fclose(config_file);
  //message = (char*)calloc(255,sizeof(char));
  //sprintf(message,"after sensei_set_config_file SENSEI_NB_LINES = %i\n",SENSEI_NB_LINES);
  //fprintf(stdout,message);
  free(message);
  free(line);
  return 0;
}

int sensei_unset_config_file(){
  CURRENT_LINE = 0;
  while (CURRENT_LINE<SENSEI_NB_LINES){
    free(SENSEI_BUFFERED_FILE[CURRENT_LINE]);
    CURRENT_LINE++;
  }
  free(SENSEI_BUFFERED_FILE);
  CURRENT_LINE = 0;
  SENSEI_NB_LINES = 0;
  return 0;
}

/** \brief a little parser to convert colon seprated values (x,y,z,...) into a table of integers
 */
int * convert_string(char * to_parse){
  int * int_tab;
  int begin;
  int end;
  int level;
  int index;
  char * convert;
  int_tab = (int*)calloc(5,sizeof(int));
  convert = (char*)calloc(255,sizeof(char));
  begin = 0;
  end = 0;
  level = 0;
  index = 0;
  while (to_parse[begin]==' ')
    begin++;
  
  end = begin;
  while ((to_parse[end]!='\n')&&(to_parse[end]!='\r')&&(to_parse[end]!=';')&&(to_parse[end]!=' ')&&(to_parse[end]!='\0')){
    //fprintf(stderr," end = %i\n",end);
    while ((to_parse[end]!=',')&&(to_parse[end]!='\n')&&(to_parse[end]!='\r')&&(to_parse[end]!=';')&&(to_parse[end]!=' ')&&(to_parse[end]!='\0')){
      convert[index] = to_parse[end];
      index++;
      end++;
    }
    
    convert[index]='\0';
    
    //fprintf(stdout,"level=%i and convert=%s\n",level,convert);
    int_tab[level]=atoi(convert);
    level++;
    if (to_parse[end]==','){
      end++;
      while (to_parse[end]==' ')
	end++;
    }
    index=0;
    convert = (char*)calloc(255,sizeof(char));
  }
  free(convert);
  
  return int_tab;
}//convert_string

/** \brief a little parser to convert colon seprated values (x,y,z,...) into a table of double
 */
double * convert_stringd(char * to_parse){
  double * int_tab;
  int begin;
  int end;
  int level;
  int index;
  char * convert;
  int_tab = (double*)calloc(7,sizeof(double));
  convert = (char*)calloc(255,sizeof(char));
  begin = 0;
  end = 0;
  level = 0;
  index = 0;
  while (to_parse[begin]==' ')
    begin++;
  
  end = begin;
  while ((to_parse[end]!='\n')&&(to_parse[end]!='\r')&&(to_parse[end]!=';')&&(to_parse[end]!=' ')&&(to_parse[end]!='\0')){
    //fprintf(stderr," end = %i\n",end);
    while ((to_parse[end]!=',')&&(to_parse[end]!='\n')&&(to_parse[end]!='\r')&&(to_parse[end]!=';')&&(to_parse[end]!=' ')&&(to_parse[end]!='\0')){
      convert[index] = to_parse[end];
      index++;
      end++;
    }
    
    convert[index]='\0';
    
    //fprintf(stdout,"level=%i and convert=%s\n",level,convert);
    int_tab[level]=atof(convert);
    level++;
    if (to_parse[end]==','){
      end++;
      while (to_parse[end]==' ')
	end++;
    }
    index=0;
    convert = (char*)calloc(255,sizeof(char));
  }
  free(convert);
  
  return int_tab;
}//convert_stringd



/** \brief function to chek and fix a path accroding to Mugen's path priority
 *
 * Check if the file is in the specified path, then in the 'system_path' dir, then in data dir and then at the root dir 
 * Change error into -1 if the file is not found , return the good path if founded
 */
char * check_path(char * a_path, char * system_path, char * var_name, int * error){
  char * message;
  char * result;
  char * path;
  message = (char*)calloc(255,sizeof(char));
  result = (char*)calloc(255,sizeof(char));
  path = (char*)calloc(255,sizeof(char));
  //TRON("check path");
  result = remove_comments(a_path);
  //TRON("removed comments");
  result = fix_filename_slashes(result);
  
  // Test if system_path/a_path works
  path = strcpy((char*)calloc(255,sizeof(char)),system_path);
  put_backslash(path);
  path = strcat(path,result);
  if (exists(path)){
    if (SENSEI_DEBUG_ON){
      sprintf(message,"%s at %s found",var_name,path);
      TRON(message);
    }
     free(message); 
  free(result); 
     error[0] = 0;
    return path;
  }
  
  // Test if data/a_path works
  path = (char*)calloc(255,sizeof(char));
  path = strcat(path,"data");
  put_backslash(path);
  path = strcat(path,result);
  if (exists(path)){
    if (SENSEI_DEBUG_ON){
      sprintf(message,"%s at %s found",var_name,path);
      TRON(message);
    }
     free(message); 
  free(result); 
  
    error[0] = 0;
    return path;
  }
  
  // Test if a_path works
  path = strcpy((char*)calloc(255,sizeof(char)),result);
  if (exists(path)){
    if (SENSEI_DEBUG_ON){
      sprintf(message,"%s at %s found",var_name,path);
      TRON(message);
    }
    free(message); 
  free(result); 
  
    error[0] = 0;
    return path; 
  }
  
  sprintf(message,"No %s at %s found",var_name,result);
  TRON(message);
  error[0] = -1;
  free(message);
    free(result); 
  free(path); 
    return (char*)calloc(1,sizeof(char));
}// End of check_path

/** \brief Function that return the number of actions found in the SENSEI_BUFFERED_FILE
 */
action_struct * init_actions(action_struct * action_array,int * nb){
  char * message;
  action_struct * act_buffer = NULL;
  int nb_actions = 0;
  CURRENT_LINE = 0;
  message = (char*)calloc(255,sizeof(char));
  if (SENSEI_DEBUG_ON)
    TRON("init_actions");
  while (CURRENT_LINE<SENSEI_NB_LINES){
    if (degraded_is_section(SENSEI_BUFFERED_FILE[CURRENT_LINE],"begin action")){
      nb_actions++;
      act_buffer = realloc(act_buffer,nb_actions*sizeof(action_struct));
      act_buffer[nb_actions-1].number = action_nb(SENSEI_BUFFERED_FILE[CURRENT_LINE]);
      if (SENSEI_DEBUG_ON){
	sprintf(message,"filling %i action with number %i",nb_actions,act_buffer[nb_actions-1].number);
	TRON(message);
      }
    }
    CURRENT_LINE++;
  }
  
  if (SENSEI_DEBUG_ON)
    TRON("after init actions");
  CURRENT_LINE = 0;
  free(message);
  nb[0]=nb_actions;
  return act_buffer;
} // init_actions
  

/** \brief function to return the number of an action
 * Take a uncommented line as input and return the number of the action as written in the section [Begin Action n]
*/
int action_nb(char * input){
  char * number_to_convert;
  int pos = 0;
  int i = 1;
  number_to_convert = (char*)calloc(255,sizeof(char));
  i = i + strlen("begin action");
  while (input[i]==' ') i++;
  while ((input[i]!=']')&&(input[i]!='\0')){
    number_to_convert[pos]=input[i];
    pos++;
    i++;
  }
  pos++;
  number_to_convert[pos]='\0';
  return atoi(number_to_convert);
}//action_nb


int action_elt_count(){
  int counter = 0;
  int i = 0;
  int current_line = CURRENT_LINE;
  while ((current_line<SENSEI_NB_LINES)&&(SENSEI_BUFFERED_FILE[current_line][0]!='[')){
    while ((i<strlen(SENSEI_BUFFERED_FILE[current_line]))&&(SENSEI_BUFFERED_FILE[current_line][i]==' '))
      i++;
    if ((SENSEI_BUFFERED_FILE[current_line][i]>='0')&&(SENSEI_BUFFERED_FILE[current_line][i]<='9'))
      counter++;
    i=0;
    current_line++;
  }
  return counter;
}

/** \brief function to analyze the line of an element action and return a tab of value corresponding
*/
int * analyse_act_elt(char * line){
  int * tab;
  int index;
  int level;
  char * to_convert;
  int index_conv;
  index = 0;
  level = 0;
  index_conv = 0;
  tab = (int*)calloc(10,sizeof(int));
  to_convert = (char*)calloc(255,sizeof(char));
  while (index<strlen(line)){
    if ((line[index]==',')&&(level<5)){
      to_convert[index_conv]='\0';
      tab[level]=atoi(to_convert);
      index++;
      level++;
      index_conv = 0;
      to_convert = (char*)calloc(255,sizeof(char));
    }
    if (to_minus(line[index])=='h'){
      tab[5] = (tab[5])+1;
    }
    if (to_minus(line[index])=='v')
      tab[5] = (tab[5])+2;
    if (to_minus(line[index])=='a')
      tab[6] = 50;
    if (to_minus(line[index])=='s')
      tab[6] = -1;
    to_convert[index_conv]=line[index];
    index++;
    index_conv++;
  } 
  if (level<5) 
    tab[level]=atoi(to_convert);
  free(to_convert);
  return tab;
}// end analyse act elt

/** \brief Function to check if a line define the entry of clsndefault ; return -1 if not 1 or 2 depending of clsn type founded or not (-1)
 */
int is_default_clsn(char * line){
  int retour = -1;
  if (strstr(string_to_minus(line),"clsn2default")!=NULL)
    return 2;
  if (strstr(string_to_minus(line),"clsn1default")!=NULL)
    return 1;
  return retour;
}

/** same as is_default_clsn but without default
*/
int is_clsn(char * line){
  int retour = -1;
  if (strstr(string_to_minus(line),"clsn1")!=NULL)
    return 1;
  if (strstr(string_to_minus(line),"clsn2")!=NULL)
    return 2;
  return retour;
}

int default_clsn_nb(char * line){
  int retour = 0;
  int i = 0;
  int j = 0;
  char * number;
  number = (char*)calloc(32,sizeof(char));
  while ((i<strlen(line))&&(line[i]!=':'))
    i++;
  
  if (i==strlen(line))
    return -1;
  i++;
  while ((i<strlen(line))){
    number[j]=line[i];
    i++;
    j++;
  }
  number[j+1]='\0';
  retour = atoi(number);
  return retour;
}

/** \brief Function to fill collision boxes
 */
clsn_struct * fill_collision(clsn_struct * clsn_array,int pos,int * nb){
  int line;
  int nb_clsn = 0;
  int i = 0;
  int k = 0;
   char * buffer;
  char * message;
  clsn_struct * buff = NULL;
  int * coords;
  buffer = (char*)calloc(255,sizeof(char));
  message = (char*)calloc(255,sizeof(char));
  if (is_default_clsn(SENSEI_BUFFERED_FILE[CURRENT_LINE]))
    CURRENT_LINE++; // passing the line  
  // TRON(SENSEI_BUFFERED_FILE[CURRENT_LINE]);
  line = CURRENT_LINE;
  while ((line<SENSEI_NB_LINES)&&(is_clsn(SENSEI_BUFFERED_FILE[line])==pos)){
    nb_clsn++;
    line++;
  }
  buff = (clsn_struct *)calloc(nb_clsn+1,sizeof(clsn_struct));
  
  for (j=0;j<nb_clsn;j++){
    i = 0;
    // TRON(SENSEI_BUFFERED_FILE[CURRENT_LINE]);
    while ((SENSEI_BUFFERED_FILE[CURRENT_LINE][k]!='=')&&(k<strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE]))){
      // sprintf(message,"Looking at '%c'",SENSEI_BUFFERED_FILE[CURRENT_LINE][k]);
      // TRON(message);
      k++;
    }
    
    k++;
    while (k<strlen(SENSEI_BUFFERED_FILE[CURRENT_LINE])){
      buffer[i]=SENSEI_BUFFERED_FILE[CURRENT_LINE][k];
      k++;
      i++;
    } 
    
    buffer[i+1] = '\0';
    coords = convert_string(buffer);
    buff[j].border1.x = coords[0];
    buff[j].border1.y = coords[1];
    buff[j].border2.x = coords[2];
    buff[j].border2.y = coords[3];
    // sprintf(message,"x1:%i y1:%i x2:%i y2:%i",buff[j].border1.x,buff[j].border1.y,buff[j].border2.x,buff[j].border2.y);
    // TRON(message);
    CURRENT_LINE++;
    k = 0;
  }
  
  free(message);
  nb[0] = nb_clsn;
  free(buffer);
  return buff;
}

/** \brief function to fill an action
 * Read the sensei_buffered_file, look for the action, allocate the good number of action elements
 * and after that parse them and store them in the array struct
*/
int fill_action(action_struct * an_action){
  char * message;
  int * result_tab;
  char * action_name;
  int section_found;
  int nb_act_elt;
  int current_elt;
  int clsn = -1;
  int clsn_nb = 0;
  int i;
  
  CURRENT_LINE = 0;
  section_found = 0;
  current_elt = 0;
  result_tab = (int*)calloc(10,sizeof(int));
  message = (char*)calloc(255,sizeof(char));
  action_name = (char*)calloc(255,sizeof(char));
  if (SENSEI_DEBUG_ON){
    sprintf(message,"Filling action n %i",an_action->number);
    TRON(message);
  }
  sprintf(action_name,"begin action %i",an_action->number);
 
  
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(section_found==0)){
    //message=(char*)calloc(255,sizeof(char));
    //sprintf(message,"char * analyze : %s \n",SENSEI_BUFFERED_FILE[CURRENT_LINE]);
    //fprintf(stdout,message);
    if (is_section(SENSEI_BUFFERED_FILE[CURRENT_LINE],action_name))
      section_found=1;
    CURRENT_LINE++;
  }
  
  if (section_found==0){
    CURRENT_LINE = 0;

    if (SENSEI_DEBUG_ON){
      sprintf(message,"************* No elements found for action %i ****",an_action->number);
      TRON(message);
    }
    
    an_action->animation_array = (animation_elt_struct*)calloc(1,sizeof(animation_elt_struct));
    an_action->nb_elt = 0;
    return -1;
  }
  
  nb_act_elt = action_elt_count();
  
  if (SENSEI_DEBUG_ON){
    // sprintf(message,"finding %i elt for action %i",nb_act_elt,an_action->number);
    sprintf(message,"finding %i elt for action %i",nb_act_elt,an_action->number);
    TRON(message);
  }
  an_action->nb_elt = nb_act_elt;
  an_action->animation_array = (animation_elt_struct*)calloc(nb_act_elt+1,sizeof(animation_elt_struct));
  an_action->current_element = 0;
  an_action->loop_start = 0;
  an_action->frame_defaultclsn1 = -1;
  an_action->frame_defaultclsn2 = -1;
  an_action->nb_defaultclsn1 = 0;
  an_action->nb_defaultclsn2 = 0;
  
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][0]!='[')){
    an_action->animation_array[current_elt].nb_clsn1 = 0;
    an_action->animation_array[current_elt].nb_clsn2 = 0;
    
    // Little simplification, assuming that each line begining by a  'l' is a loopstart 
    if (to_minus(SENSEI_BUFFERED_FILE[CURRENT_LINE][0])=='l'){
      an_action->loop_start = current_elt;
    }
    
    while ((clsn=is_default_clsn(SENSEI_BUFFERED_FILE[CURRENT_LINE]))!=-1){
      if (SENSEI_DEBUG_ON){
	sprintf(message,"Clsn%idefault finded",clsn);
	TRON(message);
      }
      if (clsn==1){
	an_action->frame_defaultclsn1 = current_elt;
	an_action->defaultclsn1 = fill_collision(an_action->defaultclsn1,1,&clsn_nb);
	an_action->nb_defaultclsn1 = clsn_nb;
      }else{
	an_action->frame_defaultclsn2 = current_elt;
	an_action->defaultclsn2 = fill_collision(an_action->defaultclsn2,2,&clsn_nb);
	an_action->nb_defaultclsn2 = clsn_nb;
      }
    }
    
    // if clsn 1 or 2 fill collision
    while ((clsn=is_clsn(SENSEI_BUFFERED_FILE[CURRENT_LINE]))!=-1){
      if (SENSEI_DEBUG_ON){
	sprintf(message,"Clsn%i findedd",clsn);
	TRON(message);
      }
      if (clsn==1){
	an_action->animation_array[current_elt].clsn1 = fill_collision(an_action->animation_array[current_elt].clsn1,1,&clsn_nb);
	an_action->animation_array[current_elt].nb_clsn1 = clsn_nb;
      }else{
	an_action->animation_array[current_elt].clsn2 = fill_collision(an_action->animation_array[current_elt].clsn2,2,&clsn_nb);
	an_action->animation_array[current_elt].nb_clsn2 = clsn_nb;
      }
    }
    
    if ((SENSEI_BUFFERED_FILE[CURRENT_LINE][0]>='0')&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][0]<='9')){
      result_tab = analyse_act_elt(SENSEI_BUFFERED_FILE[CURRENT_LINE]);
      // fprintf(stdout,"action %i and elt %i result = %i,%i, %i,%i, %i,%i, %i\n",an_action->number,current_elt,result_tab[0],result_tab[1],result_tab[2],result_tab[3],result_tab[4],result_tab[5],result_tab[6]);
      // TRON(message);
      an_action->animation_array[current_elt].groupeno = result_tab[0];
      an_action->animation_array[current_elt].spriteno = result_tab[1];
      an_action->animation_array[current_elt].x = result_tab[2];
      an_action->animation_array[current_elt].y = result_tab[3];
      an_action->animation_array[current_elt].time = result_tab[4];
      an_action->animation_array[current_elt].flipping = result_tab[5];
      an_action->animation_array[current_elt].trans = result_tab[6];
      an_action->animation_array[current_elt].current_time = 0;
   
      if ((an_action->animation_array[current_elt].nb_clsn1 == 0)&&(an_action->frame_defaultclsn1!=-1)&&(an_action->frame_defaultclsn1<=current_elt)){
	an_action->animation_array[current_elt].clsn1 = (clsn_struct*)calloc(an_action->nb_defaultclsn1+1,sizeof(clsn_struct));
	an_action->animation_array[current_elt].nb_clsn1 = an_action->nb_defaultclsn1;
	for (i=0;i<an_action->nb_defaultclsn1;i++){
	  an_action->animation_array[current_elt].clsn1[i].border1.x = an_action->defaultclsn1[i].border1.x;
	  an_action->animation_array[current_elt].clsn1[i].border1.y = an_action->defaultclsn1[i].border1.y;
	  an_action->animation_array[current_elt].clsn1[i].border2.x = an_action->defaultclsn1[i].border2.x;
	  an_action->animation_array[current_elt].clsn1[i].border2.y = an_action->defaultclsn1[i].border2.y;
	}
      }
      
      if ((an_action->animation_array[current_elt].nb_clsn2 == 0)&&(an_action->frame_defaultclsn2!=-1)&&(an_action->frame_defaultclsn2<=current_elt)){
	// TRON("Filling clsn2 with default");
	an_action->animation_array[current_elt].clsn2 = (clsn_struct*)calloc(an_action->nb_defaultclsn2+1,sizeof(clsn_struct));
	an_action->animation_array[current_elt].nb_clsn2 = an_action->nb_defaultclsn2;
	for (i=0;i<an_action->nb_defaultclsn2;i++){
	  // TRON("really fillin");
	  an_action->animation_array[current_elt].clsn2[i].border1.x = an_action->defaultclsn2[i].border1.x;
	  an_action->animation_array[current_elt].clsn2[i].border1.y = an_action->defaultclsn2[i].border1.y;
	  an_action->animation_array[current_elt].clsn2[i].border2.x = an_action->defaultclsn2[i].border2.x;
	  an_action->animation_array[current_elt].clsn2[i].border2.y = an_action->defaultclsn2[i].border2.y;
	}
      }
      current_elt++;
    }
    CURRENT_LINE++;
  }
  
  
  if (SENSEI_DEBUG_ON)
    TRON("after filling action");
  
  free(message);
  free(action_name);
  return 0;
}//fill action

/** \brief Function to fill a KOF 91 (old version) chars action according to mugen's action format
    As args it take :<br>
    action_struct * an_action = the struct to fill
    int number = number of the action
    int nb_frames = number of frames of the action
    int speed = number of tocks between each frame
    int offx = x position of offensive box
    int offy = y position of offensive box
    int defx = x position of defensive box
    int defy = y position of defensive box
*/
int kof91_fill_action(action_struct * an_action,int number,int nb_frames,int speed,int offx, int offy, int defx, int defy){
  int error = 0;
  int i;
  an_action->number = number;
  an_action->animation_array = (animation_elt_struct*)calloc(nb_frames+1,sizeof(animation_elt_struct));
  an_action->nb_elt = nb_frames;
  an_action->current_element = 0;
  an_action->loop_start = 0;
  for (i=0;i<nb_frames;i++){
    an_action->animation_array[i].groupeno = number;
    an_action->animation_array[i].spriteno = i;
    an_action->animation_array[i].x = 0;
    an_action->animation_array[i].y = 0;
    an_action->animation_array[i].time = speed;
    an_action->animation_array[i].flipping = 0;
    an_action->animation_array[i].trans = 0;
    an_action->animation_array[i].current_time = 0;
    an_action->animation_array[i].clsn1 = (clsn_struct*)calloc(1,sizeof(clsn_struct));
    an_action->animation_array[i].nb_clsn1 = 1;
    an_action->animation_array[i].clsn1[0].border1.x = offx;
    an_action->animation_array[i].clsn1[0].border1.y = offy;
    an_action->animation_array[i].clsn1[0].border2.x = -offx;
    an_action->animation_array[i].clsn1[0].border2.y = 0;
    an_action->animation_array[i].clsn2 = (clsn_struct*)calloc(1,sizeof(clsn_struct));
    an_action->animation_array[i].nb_clsn2 = 1;
    an_action->animation_array[i].clsn2[0].border1.x = offx;
    an_action->animation_array[i].clsn2[0].border1.y = offy;
    an_action->animation_array[i].clsn2[0].border2.x = -offx;
    an_action->animation_array[i].clsn2[0].border2.y = 0;
  }
  return error;
}// kof91_fill_action

// Story board section
/** \brief function to fill an array of char * with scenes names, return the number of scenes found
 */
char ** fill_scenes_names(int * nb){
  int nb_scenes;
  char ** scene_tab;
  nb_scenes = 0;
  scene_tab = NULL;
  CURRENT_LINE = 0;
  while (CURRENT_LINE<SENSEI_NB_LINES){
    if (degraded_is_section(SENSEI_BUFFERED_FILE[CURRENT_LINE],"scene")){
      nb_scenes++;
      scene_tab = (char**)realloc(scene_tab,nb_scenes*sizeof(char*));
      scene_tab[nb_scenes-1] = strcpy((char*)calloc(255,sizeof(char)),bg_elt_name("scene",SENSEI_BUFFERED_FILE[CURRENT_LINE]));
    }
    CURRENT_LINE++;
  }
  
  nb[0] = nb_scenes;
  return scene_tab;
}

int * fill_action_nb(int * nb){
  int nb_actions;
  int * tab_actions;
  nb_actions = 0;
  tab_actions = NULL;
  CURRENT_LINE = 0;
  while (CURRENT_LINE<SENSEI_NB_LINES){
    if (degraded_is_section(SENSEI_BUFFERED_FILE[CURRENT_LINE],"begin action")){
      nb_actions++;
      tab_actions = (int*)realloc(tab_actions,nb_actions*sizeof(char*));
      tab_actions[nb_actions-1] = action_nb(SENSEI_BUFFERED_FILE[CURRENT_LINE]);
    }
    CURRENT_LINE++;
  }
  nb[0] = nb_actions;
  return tab_actions;
} // fill_action_nb

/** \brief Function to process an action (move from an element to aother if needed
 */
int process_action(action_struct * an_action){
  int error =0;
  char * message;
  message = (char*)calloc(255,sizeof(char));
  if (SENSEI_DEBUG_ON){
    sprintf(message,"processing action %i",an_action->number);
    TRON(message);
  }  
  
  an_action->anim_time++;
  if (an_action->animation_array[an_action->current_element].time!=-1){
    an_action->animation_array[an_action->current_element].current_time++;
    if (an_action->animation_array[an_action->current_element].current_time>an_action->animation_array[an_action->current_element].time){
      if (SENSEI_DEBUG_ON){
	TRON("next element in animation");
      }
      an_action->animation_array[an_action->current_element].current_time = 0;
      an_action->current_element++;
      if (an_action->current_element>=an_action->nb_elt){
	if (SENSEI_DEBUG_ON){
	  TRON("Looping in animation");
	}
	an_action->current_element=an_action->loop_start;
      }
    }
  }
  free(message);
  return error;
}//process_action


/** \brief Function to convert a char path into a char type (none,kof91 or Mugen)
 */
int convert_char_type(char * path){
  int type = 0;
  if ((strstr(path,".ini")!=NULL)||(strstr(path,".INI")!=NULL))
    type = 1;
  if ((strstr(path,".def")!=NULL)||(strstr(path,".DEF")!=NULL))
    type = 2;
  return type;
}// convert char type

/** \brief function to check path of a character and return the right path of character founded and the right type
*/
char * check_character_path(char * name, int * type){
  char * message;
  char * result;
  char * path;
  message = (char*)calloc(255,sizeof(char));
  result = (char*)calloc(255,sizeof(char));
  // TRON("check character path");
  path = strcpy((char*)calloc(255,sizeof(char)),name);
  result = fix_filename_slashes(name);
  // test if the char is at the exact path
  if (exists(path)){
    if (SENSEI_DEBUG_ON){
      sprintf(message,"%s at %s found",name,path);
      TRON(message);
    }
    type[0] = convert_char_type(path);
    free(message);
    free(result);
    return path;
  }
  
  // Test if chars/name.def works
  path = strcpy((char*)calloc(255,sizeof(char)),"chars");
  put_backslash(path);
  path = strcat(path,name);
  put_backslash(path);
  path = strcat(path,name);
  path = strcat(path,".def");
  if (exists(path)){
    if (SENSEI_DEBUG_ON){
      sprintf(message,"%s at %s found",name,path);
      TRON(message);
    }
    type[0] = 2;
    free(message);
    free(result);
    return path;
  }

  // Test if chars/path works
  path = strcpy((char*)calloc(255,sizeof(char)),"chars");
  put_backslash(path);
  path = strcat(path,name);
  if (exists(path)){
    if (SENSEI_DEBUG_ON){
      sprintf(message,"%s at %s found",name,path);
      TRON(message);
    }
    type[0] = 2;
    free(message);
    free(result);
    return path;
  }
  
  // Test if sprites/name.ini works
  path = strcpy((char*)calloc(255,sizeof(char)),"sprites");
  put_backslash(path);
  path = strcat(path,name);
  put_backslash(path);
  path = strcat(path,"char.ini");
  if (exists(path)){
    if (SENSEI_DEBUG_ON){
      sprintf(message,"%s at %s found",name,path);
      TRON(message);
    }
    type[0] = 1;
    free(message);
    free(result);
    return path;
  }
  
  if (SENSEI_DEBUG_ON){
    sprintf(message,"No %s found",name);
    TRON(message);
  }
  type[0] = 0;
  path = (char*)calloc(1,sizeof(char));
  free(message);
  free(result);
  return path;
}// check_character_path

/** \brief Function to extract the name of a character from a select.def char ligne, take the line to parse, and a names to fill and return the type of char founded
 */
char * extract_char_name(char * line, int * type){
  int pos = 0;
  int result_pos = 0;
  int size;
  char * result;
  char * message;
  result = (char*)calloc(255,sizeof(char));
  message = (char*)calloc(255,sizeof(char));
  
  size = strlen(line);
  while ((pos<size)&&(line[pos]==' '))
    pos++;
  while ((pos<size)&&(line[pos]!=',')&&(line[pos]!=' ')){
    result[result_pos]=line[pos];
    pos++;
    result_pos++;
  }
  remove_end_spaces(result);
  sprintf(message,"Found %s char",result);
  TRON(message);
  result = strcpy((char*)calloc(255,sizeof(char)),check_character_path(result,&(*type)));
  free(message);
  return result;
} // extract char name

/** \brief Function to extract the name of a background from a select.def char ligne, take the line to parse, and fill the type with bg typen, character is a boolean that show if it's a character line or not
 */
char * extract_bg_name(char * line, int * type, int character){
  int pos = 0;
  int result_pos = 0;
  int size;
  char * result;
  char * message;
  result = (char*)calloc(255,sizeof(char));
  message = (char*)calloc(255,sizeof(char));
  
  size = strlen(line);
  while ((pos<size)&&(line[pos]==' '))
    pos++;
  if (character){
    while ((pos<size)&&(line[pos]!=',')){
      // result[result_pos]=line[pos];
      pos++;
      // result_pos++;
    }
  }
  
  if (((character)&&(line[pos]==','))||(!character)){
    if (character)
      pos++;
    while ((pos<size)&&(line[pos]!=',')){
      while ((pos<size)&&(line[pos]==' '))
	pos++;
      if (pos<size){
	result[result_pos]=line[pos];
	pos++;
	result_pos++;
      }
    }
  }else{
    type[0]=0;
    return result;
  }
  result = remove_end_spaces(result);
  sprintf(message,"Found %s bg",result);
  TRON(message);
  if (!exists(result)){
    TRON("Stage not found");
    type[0]=0;
    return result;
  }
  type[0] = 3;
  // result = strcpy((char*)calloc(255,sizeof(char)),check_character_path(result,&(*type)));
  free(message);
  return result;
}//extract bg name

/** \brief Filling kof char_ref struct
 */
int kof91_fill_char_ref(char_ref_struct * char_ref){
  char * message;
  char * result;
  char * file_path;
  int i = 0;
  message = (char*)calloc(255,sizeof(char));
  result = (char*)calloc(255,sizeof(char));
  sprintf(message,"Filling kof91 char %s ",char_ref->path);
  TRON(message);
  
  while (i<(strlen(char_ref->path)-9)){
    result[i] = char_ref->path[i];
    i++;
  }
  char_ref->display_name = strcpy((char*)calloc(255,sizeof(char)),get_filename(result));
  put_backslash(result);
  file_path = strcpy((char*)calloc(100,sizeof(char)),result);
  file_path = strcat(file_path,"selsmall.pcx");
  char_ref->s_pic = xload_pcx(file_path,char_ref->s_pic_pal);
  file_path = strcpy((char*)calloc(100,sizeof(char)),result);
  file_path = strcat(file_path,"selbig.pcx");
  char_ref->b_pic = xload_pcx(file_path,char_ref->b_pic_pal);
  
  TRON(result);
  free(result);
  free(message);
  free(file_path);
  return 0;
} // kof91_fill_char_ref

/** \brief function to remove quotes
 */
char * sensei_remove_quotes(char * a_string){
  char * result;
  int read_index;
  int write_index;
  result = (char*)calloc(255,sizeof(char));
  
  read_index = 0;
  write_index = 0;

  while (a_string[read_index]==' ')
    read_index++;

  if (a_string[read_index]=='"')
    read_index++;
      
  while ((a_string[read_index]!='\n')&&(a_string[read_index]!='\r')&&(a_string[read_index]!='"')&&(a_string[read_index]!='\0')&&(a_string[read_index]!=';'))
    {
      result[write_index] = a_string[read_index];
      write_index++;
      read_index++;
    }
	 
  write_index++;
  result[write_index]='\0';
  return result;
}

/** \brief Filling mugen's char_ref struct
 */
int mugen_fill_char_ref(char_ref_struct * char_ref){
  char * message;
  char * result;
  char * buffer;
  int error = 0;
  SFFEntry * char_sff;
  
  message = (char*)calloc(255,sizeof(char));
  buffer = (char*)calloc(255,sizeof(char));
  sprintf(message,"Filling mugencharef %s ",char_ref->path);
  TRON(message);
  set_config_file(char_ref->path);

  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Info","name",""));
  result = sensei_remove_quotes(result);
  char_ref->name = strcpy((char*)calloc(255,sizeof(char)),result);

  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Info","displayname",""));
  result = sensei_remove_quotes(result);
  // char_ref->display_name = strcpy((char*)calloc(255,sizeof(char)),sensei_remove_quotes(get_config_string("Info","displayname","")));
  if (strlen(result)>1){
    char_ref->display_name = strcpy((char*)calloc(255,sizeof(char)),result);
  }else{
    char_ref->display_name = strcpy((char*)calloc(255,sizeof(char)),char_ref->name);
  }
  // Need to fill with the small pic and the big pic
  buffer = extract_path(char_ref->path);
  // TRON(buffer);
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("files","sprite",""));
  result = strcpy((char*)calloc(255,sizeof(char)),check_path(result,buffer,"player sprite file",&error));
  if (error!=0){
    if (SENSEI_DEBUG_ON)
      TRON("missing sprite file");
    return -1;
  }
  if (SENSEI_DEBUG_ON){
    sprintf(message,"Sff Loading %s ",result);
    TRON(message);
  }
  char_sff = sffLoad(result);
  char_ref->s_pic = sensei_fill_bmp(char_sff,9000,0,1,&char_ref->small_xaxis,&char_ref->small_yaxis);
  char_ref->b_pic = sensei_fill_bmp(char_sff,9000,1,1,&char_ref->big_xaxis,&char_ref->big_yaxis);
  //   BITMAP * sensei_fill_bmp(SFFEntry * a_sff,int a_group,int an_index,int masked, int * xaxis, int * yaxis){
  
  // TRON(message);
  free(char_sff);
  free(buffer);
  free(message);
  return 0;
} // mugen_fill_char_ref

/** \brief Filling Mugen's bg_ref struct
 */
int mugen_fill_bg_ref(bg_ref_struct * bg_ref){
  char * message;
  char * result;
  char * buffer;
  int error = 0;
  
  message = (char*)calloc(255,sizeof(char));
  buffer = (char*)calloc(255,sizeof(char));
  sprintf(message,"Filling mugenbgref %s ",bg_ref->path);
  TRON(message);
  set_config_file(bg_ref->path);
  result = strcpy((char*)calloc(255,sizeof(char)),get_config_string("Info","name",""));
  result = sensei_remove_quotes(result);
  bg_ref->display_name = strcpy((char*)calloc(255,sizeof(char)),result);
  
  // TRON(message);
  free(buffer);
  free(message);
  free(result);
  return error;
} // mugen_fill_bg_ref


/** \brief Function that take the char_ref_array and add the char_path to it if it's not already, return the index where he put/found the char ; max is the size of the array
 */
char_ref_struct * is_not_indexed(char_ref_struct * char_ref_array,char * char_path,int max, int * index,int char_type){
  int i = 0;
  while (i<max){
    if (strcmp(string_to_minus(char_ref_array[i].path),string_to_minus(char_path))==0){
      index[0] = i;
      return char_ref_array;
    }
    else
      i++;
  }
  if (i==max){
    if (i==0)
      char_ref_array = calloc(1,sizeof(char_ref_struct));
    else
      char_ref_array = realloc(char_ref_array,(i+1)*sizeof(char_ref_struct));
    char_ref_array[i].path = strcpy((char*)calloc(255,sizeof(char)),char_path);
    char_ref_array[i].type = char_type;
    switch (char_type){
    case 1:
      kof91_fill_char_ref(&char_ref_array[i]);
      break;
    case 2:
      mugen_fill_char_ref(&char_ref_array[i]);
      break;
    default:
      break;
    }
  }
  index[0] = i;
  return char_ref_array;
}// is not indexed

/** \brief Function to read select.def file and extract chars list
 */
int sensei_fill_characters_list(Game_variables variables){
  int nb_char = 0;
  // int i;
  int nb_diff_chars = 0;
  int section_found = 0;
  int char_indexed = 0;
  int char_type = 0;
  char * message;
  char * char_name = NULL;
  char * char_path = NULL;
  int char_line = 0; // line where the first char is set 
  TRON("filling mugen's chars");
  message = (char*)calloc(255,sizeof(char));
  CURRENT_LINE = 0;
  section_found = 0;
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(section_found==0)){
    if (is_section(SENSEI_BUFFERED_FILE[CURRENT_LINE],"characters"))
      section_found = 1;
    CURRENT_LINE++;
  }
  if (section_found==0){
    TRON("Malformed select.def");
    CURRENT_LINE = 0;
    variables->System.Select_struct.type = 0;
    return 0;
  }
  
  char_line = CURRENT_LINE;
  
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][0]!='[')&&(nb_char<=variables->System.Select_struct.s_nb_char)){
    nb_char++;
    CURRENT_LINE++;
  }
  
  if (nb_char==0){
    variables->System.Select_struct.type = 0;
    TRON("no chars");
    return 0;
  }
  sprintf(message,"Total nb char founded = %i",nb_char);
  TRON(message);
  variables->System.Select_struct.type = 1;
  variables->System.Select_struct.loaded = 0;
  variables->System.Select_struct.state = 0;
  variables->System.Select_struct.s_nb_char = nb_char;
  variables->System.Select_struct.char_ref_array = NULL;
  CURRENT_LINE = char_line; // back to the top of char list
  nb_diff_chars = 0;
  char_name = (char*)calloc(255,sizeof(char));
  char_path = (char*)calloc(255,sizeof(char));
  nb_char = 0;
  // Construct char_ref_array by the char_names
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][0]!='[')){
    char_path = strcpy((char*)calloc(255,sizeof(char)),extract_char_name(SENSEI_BUFFERED_FILE[CURRENT_LINE],&char_type));
    if ((char_type!=0)&&(char_type!=-1)){
      variables->System.Select_struct.char_ref_array = is_not_indexed(variables->System.Select_struct.char_ref_array,char_path,nb_diff_chars,&char_indexed,char_type);
      if (char_indexed==nb_diff_chars){
	nb_diff_chars++;
	TRON("nb_diff_chars++");
      }else{
	TRON("already in list");
	// get index(char_names[nb_diff_chars]);
      }
      variables->System.Select_struct.char_list[nb_char]=char_indexed+1;
    }else{
      TRON("empty char or random char");
      variables->System.Select_struct.char_list[nb_char]=0;
    }
    CURRENT_LINE++;
    nb_char++;
  }

  CURRENT_LINE = 0;
  free(char_name);
  free(char_path);
  free(message);
  return 0;
} //sensei_fill_characters_list

/** \brief Function that take the char_ref_array and add the char_path to it if it's not already, return the index where he put/found the char ; max is the size of the array
 */
bg_ref_struct * bg_is_not_indexed(bg_ref_struct * bg_ref_array,char * bg_path,int max, int * index,int bg_type){
  int i = 0;
  while (i<max){
    if (strcmp(string_to_minus(bg_ref_array[i].path),string_to_minus(bg_path))==0){
      index[0] = i;
      return bg_ref_array;
    }
    else
      i++;
  }
  if (i==max){
    if (i==0)
      bg_ref_array = calloc(1,sizeof(bg_ref_struct));
    else
      bg_ref_array = realloc(bg_ref_array,(i+1)*sizeof(bg_ref_struct));
    bg_ref_array[i].path = strcpy((char*)calloc(255,sizeof(char)),bg_path);
    bg_ref_array[i].type = bg_type;
    switch (bg_type){
    case 1:
      // kof91_fill_bg_ref(&char_ref_array[i]);
      break;
    case 3:
      mugen_fill_bg_ref(&bg_ref_array[i]);
      break;
    default:
      mugen_fill_bg_ref(&bg_ref_array[i]);
      break;
    }
  }
  index[0] = i;
  return bg_ref_array;
}// is not indexed

/** \brief Function to fill background list (lot like fill char list)
 */
int sensei_fill_bgs_list(Game_variables variables){
  int error = 0;
  int nb_bg = 0;
  int tot_nb_bg = 0;
  int nb_diff_bgs = 0;
  int section_found = 0;
  int bg_indexed = 0;
  int bg_type = 0;
  char * message;
  char * bg_name = NULL;
  char * bg_path = NULL;
  int bg_line = 0; // line where the first char is set 
  
  message = (char*)calloc(255,sizeof(char));
  if (SENSEI_DEBUG_ON)
    TRON("filling mugen's bgs");
  // First filling bgs in character list : re-read char list
  CURRENT_LINE = 0;
  section_found = 0;
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(section_found==0)){
    if (is_section(SENSEI_BUFFERED_FILE[CURRENT_LINE],"characters"))
      section_found = 1;
    CURRENT_LINE++;
  }
  if (section_found==0){
    TRON("Malformed select.def");
    CURRENT_LINE = 0;
    variables->System.Select_struct.type = 0;
    return 0;
  }
  
  bg_line = CURRENT_LINE;
  
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][0]!='[')){
    nb_bg++;
    CURRENT_LINE++;
  }
  
  tot_nb_bg = nb_bg;
  variables->System.Select_struct.bg_list = (int*)calloc(nb_bg,sizeof(int));
  if (SENSEI_DEBUG_ON){
    sprintf(message,"Total nb char founded = %i for bgs",nb_bg);
    TRON(message);
  }
  variables->System.Select_struct.bg_ref_array = NULL;
  CURRENT_LINE = bg_line; // back to the top of char list
  nb_diff_bgs = 0;
  bg_name = (char*)calloc(255,sizeof(char));
  bg_path = (char*)calloc(255,sizeof(char));
  nb_bg = 0;
  // Construct bg_ref_array by the char_names
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][0]!='[')){
    bg_path = strcpy((char*)calloc(255,sizeof(char)),extract_bg_name(SENSEI_BUFFERED_FILE[CURRENT_LINE],&bg_type,1));
    if (bg_type!=0){
      variables->System.Select_struct.bg_ref_array = bg_is_not_indexed(variables->System.Select_struct.bg_ref_array,bg_path,nb_diff_bgs,&bg_indexed,bg_type);
      if (bg_indexed==nb_diff_bgs){
	nb_diff_bgs++;
	TRON("nb_diff_bgs++");
      }else{
	TRON("already in list");
	// get index(char_names[nb_diff_chars]);
      }
      variables->System.Select_struct.bg_list[nb_bg]=bg_indexed+1;
    }else{
      TRON("empty char or random char");
      variables->System.Select_struct.bg_list[nb_bg]=0;
    }
    CURRENT_LINE++;
    nb_bg++;
  }

  /* Looking into extra stages
   */
  section_found = 0;
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(section_found==0)){
    if (is_section(SENSEI_BUFFERED_FILE[CURRENT_LINE],"ExtraStages"))
      section_found = 1;
    CURRENT_LINE++;
  }
  if (section_found==0){
    if (SENSEI_DEBUG_ON)
      TRON("No Extra stages");
    variables->System.Select_struct.nb_bg = nb_diff_bgs;
    
    CURRENT_LINE = 0;
    free(bg_name);
    free(bg_path);
    
    free(message);
    return error;
  }
  
  bg_line = CURRENT_LINE;
  nb_bg = 0;
  
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][0]!='[')){
    nb_bg++;
    CURRENT_LINE++;
  }
  
  tot_nb_bg = tot_nb_bg + nb_bg;
  variables->System.Select_struct.bg_list = (int*)realloc(variables->System.Select_struct.bg_list,tot_nb_bg*sizeof(int));
  if (SENSEI_DEBUG_ON){
    sprintf(message,"Total nb extra bg founded = %i",tot_nb_bg);
    TRON(message);
  }
  // variables->System.Select_struct.bg_ref_array = NULL;
  CURRENT_LINE = bg_line; // back to the top of char list
  bg_name = (char*)calloc(255,sizeof(char));
  bg_path = (char*)calloc(255,sizeof(char));
  nb_bg = 0;
  // Construct bg_ref_array by the char_names
  while ((CURRENT_LINE<SENSEI_NB_LINES)&&(SENSEI_BUFFERED_FILE[CURRENT_LINE][0]!='[')){
    bg_path = strcpy((char*)calloc(255,sizeof(char)),extract_bg_name(SENSEI_BUFFERED_FILE[CURRENT_LINE],&bg_type,0));
    if (bg_type!=0){
      variables->System.Select_struct.bg_ref_array = bg_is_not_indexed(variables->System.Select_struct.bg_ref_array,bg_path,nb_diff_bgs,&bg_indexed,bg_type);
      if (bg_indexed==nb_diff_bgs){
	nb_diff_bgs++;
	TRON("nb_diff_bgs++");
      }else{
	TRON("already in list");
	// get index(char_names[nb_diff_chars]);
      }
      variables->System.Select_struct.bg_list[nb_bg]=bg_indexed+1;
    }else{
      TRON("empty bg");
      variables->System.Select_struct.bg_list[nb_bg]=0;
    }
    CURRENT_LINE++;
    nb_bg++;
  }
  
  variables->System.Select_struct.nb_bg = nb_diff_bgs;
  
  CURRENT_LINE = 0;
  free(bg_name);
  free(bg_path);

  free(message);
  return error;
} // sensei_fill_bgs_list

int sensei_music_type(char * music_filename){
  int type = 0;
  if ((strstr(music_filename,".mid")!=NULL)||(strstr(music_filename,".MID")!=NULL))
    type = 1;
  if ((strstr(music_filename,".mp3")!=NULL)||(strstr(music_filename,".MP3")!=NULL))
    type = 2;
  return type;
}// sensei_music_type

/** \brief Function to play music struct
 */
int play_music(music_struct * a_music){
  if (a_music->loaded==0){
    switch (a_music->type){
    case 0:
      break;
    case 1:
      music = load_midi(a_music->path);
      break;
    case 2:
      MP3_Open(a_music->path);
      MP3_Play();
      break;
    default:
      break;
    }
    a_music->loaded =1;
  }else{
    switch (a_music->type){
    case 0:
      break;
    case 1:
      play_midi(music,a_music->loop);
      break;
    case 2:
#if 0
      if ((poll_mp3_file(mp3)== ALMP3_POLL_NOTPLAYING)&&(a_music->loop==1)){
	// ugly but working
	MP3_Close();
	MP3_Open(a_music->path);
	MP3_Play();
      }
#endif
      break;
    default:
      break;
    }
  }
  return 0;
}

/** \brief Function to stop playing music struct
 */
int stop_music(music_struct * a_music){
  switch (a_music->type){
  case 0:
    break;
  case 1:
    stop_midi();
    break;
  case 2:
    MP3_Close();
    break;
  default:
    break;
  }
  a_music->loaded = 0;
  return 0;
} // stop music

/** \brief function to fill an Allegro's bmp with a sprite included in a sff, an set the palette to the good one, and change the axis
 
 */
BITMAP * sensei_fill_bmp(SFFEntry * a_sff,int a_group,int an_index,int masked, int * xaxis, int * yaxis){
  SFFEntry * cur;
  SFFEntry * pal_cur;
  int j;
  BITMAP * a_sprite;
  int spr_position = 0;
  RGB * a_pal;
  char * message;
  RGB trans = { 63 , 0 , 63 }; //magenta for translucy in true color mode

  // Taking the good sprite
  message = (char*)calloc(255,sizeof(char));
  
  cur = a_sff;
  while ((cur->next)&&((cur->group!=a_group)||(cur->curIndex!=an_index))){
    cur = cur->next;
    spr_position++;
  }
  
  if (SENSEI_DEBUG_ON){
    sprintf(message,"loaded for grp = %i and index = %i (and prevIndex = %i) and were looking for g = %i et i = %i",cur->group,cur->curIndex,cur->prevIndex,a_group,an_index);
    TRON(message);
  }
  
  /*
   * Little fix for missing sprites
   */
  if ((cur->group!=a_group)||(cur->curIndex!=an_index)){
    if (SENSEI_DEBUG_ON){
      sprintf(message,"No sprite for %i, %i",a_group,an_index);
      TRON(message);
    }
    a_sprite = create_bitmap(1,1);
  }else{
    if ((cur->image==NULL)){
      // TRON("No image");
      a_sprite = create_bitmap(1,1);
    }else{
      a_sprite = create_bitmap(cur->image->w,cur->image->h);
      // a_sprite = create_bitmap_ex(bitmap_color_depth(cur->image),cur->image->w,cur->image->h);
      xaxis[0] = cur->x;
      yaxis[0] = cur->y;
    }
    //TRON("after create bitmap");
  }
  
   if (cur->pal){
    // TRON("a pal");
    select_palette(cur->pal);
    a_pal = cur->pal;
  }else{ // finding a valid pal
    // TRON("not a pal"); 
    pal_cur = cur;
    while ((!pal_cur->pal)&&(spr_position>=0)){
      // TRON("searching a pal");
      pal_cur = a_sff;
      for (j=0;j<spr_position;j++)
	pal_cur = pal_cur->next;
      spr_position--;
    }
    
    if (pal_cur->pal){
      select_palette(pal_cur->pal);
      a_pal = pal_cur->pal;
    }else{
      // TRON("Setting default palette");
      select_palette(default_palette);
      a_pal = default_palette;
    }
  }
  
  if (masked){
    set_color(0,&trans);
    // set_color_conversion(COLORCONV_NONE);
  }
  
  if ((cur->image!=NULL)&&(cur->group==a_group)&&(cur->curIndex==an_index))
    blit(cur->image,a_sprite,0,0,0,0,cur->image->w,cur->image->h);
    // draw_sprite(a_sprite,cur->image,0,0);
  
  cur = a_sff;
  pal_cur = a_sff;
  
  free(message);
  return a_sprite;
} // sensei_fill_bmp

/** \brief Function to load a kof 91 sprite
 */
BITMAP * sensei_kof91_fill_bmp(KOF91Sprites * kof91_sprites,int a_group,int an_index,int max_sprites, int * xaxis, int * yaxis,int faced){
  BITMAP * buff;
  BITMAP * reversed_bmp;
  int i = 0;
  int j = -1;
  char * message;
 
  message = (char*)calloc(255,sizeof(char));
  // fprintf(stdout,"begin to fill\n");
  while ((i<max_sprites)&&(j==-1)){
    if ((kof91_sprites[i].index == an_index)&&(kof91_sprites[i].group == a_group))
      j = i;
    i++;
  }
  
  if (j==-1){
    buff = create_bitmap(1,1);
    TRON("KOF 91 no sprite");
    return buff;
  }
  //j--;
  select_palette(kof91_sprites[j].pal);
  buff = create_bitmap(kof91_sprites[j].sprite->w,kof91_sprites[j].sprite->h);
  yaxis[0] = kof91_sprites[j].sprite->h;
  xaxis[0] = (int)(kof91_sprites[j].sprite->w/2);
  blit(kof91_sprites[j].sprite,buff,0,0,0,0,kof91_sprites[j].sprite->w,kof91_sprites[j].sprite->h);
  
  if (faced<0){
    reversed_bmp = create_bitmap(buff->w,buff->h);
    clear_to_color(reversed_bmp,makecol(255,0,255));
    draw_sprite_h_flip(reversed_bmp,buff,0,0);
    return reversed_bmp;
  }
  
  free(message);
  return buff;
}//sensei_kof91_fill_bmp

RGB * sensei_fill_pal(SFFEntry * a_sff,int a_group,int an_index,int forced, int masked){
  RGB * a_pal = NULL;
  SFFEntry * cur;
  SFFEntry * pal_cur;
  int j;
  int spr_position = 0;
  char * message;
  RGB trans = { 63 , 0 , 63 }; //magenta for translucy in true color mode

  // Taking the good sprite
  message = (char*)calloc(255,sizeof(char));
  // TRON("Finding pal");
  
  cur = a_sff;
  while ((cur->next)&&((cur->group!=a_group)||(cur->curIndex!=an_index))){
    cur = cur->next;
    spr_position++;
  }
  // sprintf(message,"loaded for grp = %i and index = %i (and prevIndex = %i) and were looking for g = %i et i = %i",cur->group,cur->curIndex,cur->prevIndex,a_group,an_index);
  // TRON(message);
  
  /*
   * Little fix for missing sprites
   */
  if ((cur->group!=a_group)||(cur->curIndex!=an_index)){
    if (SENSEI_DEBUG_ON){
      // sprintf(message,"No sprite for %i, %i",a_group,an_index);
      TRON(message);
    }
  }else{
    if ((cur->image==NULL)){
      // TRON("No image");
    }
  }
  
  if (cur->pal){
    // TRON("a pal");
    select_palette(cur->pal);
    a_pal = cur->pal;
  }else{ // finding a valid pal
    // TRON("not a pal"); 
    if (forced==0){
      pal_cur = cur;
      while ((!pal_cur->pal)&&(spr_position>=0)){
	// TRON("searching a pal");
	pal_cur = a_sff;
	for (j=0;j<spr_position;j++)
	  pal_cur = pal_cur->next;
	spr_position--;
      }
    }else
      return default_palette;
      
    
    if (pal_cur->pal){
      select_palette(pal_cur->pal);
      a_pal = pal_cur->pal;
    }else{
      if (SENSEI_DEBUG_ON)
	TRON("Setting default palette");
      select_palette(default_palette);
      a_pal = default_palette;
    }
  }
  
  if (masked){
    set_color(0,&trans);
    // set_color_conversion(COLORCONV_NONE);
  }
  
  free(message);
  return a_pal;
}// PALETTE * sensei_fill_pal

/** \brief Function to fill a bmp with the good image from a sff file, but using the pal instead of the automatic one (usefull for players one)
 */
BITMAP * sensei_fill_bmp_uncolored(SFFEntry * a_sff,int a_group,int an_index,int masked, int * xaxis, int * yaxis,RGB * a_pal, int faced){
  SFFEntry * cur;
  SFFEntry * pal_cur;
  // int j;
  BITMAP * a_sprite;
  BITMAP * a_reversed_sprite = NULL;
  int spr_position = 0;
  char * message;
  RGB trans = { 63 , 0 , 63 }; //magenta for translucy in true color mode

  // Taking the good sprite
  message = (char*)calloc(255,sizeof(char));
  
  cur = a_sff;
  while ((cur->next)&&((cur->group!=a_group)||(cur->curIndex!=an_index))){
    cur = cur->next;
    spr_position++;
  }
  
  if (SENSEI_DEBUG_ON){
    sprintf(message,"loaded for grp = %i and index = %i (and prevIndex = %i) and were looking for g = %i et i = %i",cur->group,cur->curIndex,cur->prevIndex,a_group,an_index);
    TRON(message);
  }
  /*
   * Little fix for missing sprites
   */
  if ((cur->group!=a_group)||(cur->curIndex!=an_index)){
    if (SENSEI_DEBUG_ON){
      sprintf(message,"No sprite for %i, %i",a_group,an_index);
      TRON(message);
    }
    a_sprite = create_bitmap(1,1);
  }else{
    if ((cur->image==NULL)){
      TRON("No image");
      a_sprite = create_bitmap(1,1);
    }else{
      a_sprite = create_bitmap(cur->image->w,cur->image->h);
      // a_sprite = create_bitmap_ex(bitmap_color_depth(cur->image),cur->image->w,cur->image->h);
      xaxis[0] = cur->x;
      yaxis[0] = cur->y;
    }
    //TRON("after create bitmap");
  }
  
  select_palette(a_pal);
  
  if (masked){
    set_color(0,&trans);
    set_color_conversion(COLORCONV_NONE);
  }
  
  if ((cur->image!=NULL)&&(cur->group==a_group)&&(cur->curIndex==an_index))
    blit(cur->image,a_sprite,0,0,0,0,cur->image->w,cur->image->h);
    // draw_sprite(a_sprite,cur->image,0,0);
  
  cur = a_sff;
  pal_cur = a_sff;
  
  if (faced<0){
    a_reversed_sprite = create_bitmap(a_sprite->w,a_sprite->h);
    clear_to_color(a_reversed_sprite,makecol(255,0,255));
    draw_sprite_h_flip(a_reversed_sprite,a_sprite,0,0);
    free(message);
    return a_reversed_sprite;
  }

  free(message);
  return a_sprite;
} // sensei_fill_bmp_uncolored
