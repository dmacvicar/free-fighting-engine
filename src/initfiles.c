#include "global.h"
#include "stdio.h"

#include "config.h"
#include <string.h>
#include "allegro.h"

#include "macros.h"
#include "initfiles.h"


#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

/** \file initfiles.c
 * \brief function to list files in a directory
 */
/***************************************************************************/

/** \brief New KOF 91 function to list files
 * Mostly a copy of the original one, but use an unconstrained array
 */
char ** sensei_list_files(int * nb, char * directory, char * name){
  int number;
  DIR *dirp;
  struct dirent *dp;
  // struct stat buf;
  int f;
  char ** result;
  
  result = NULL;
  dirp = opendir( directory );
  number=0;
  while (dp = readdir(dirp)) {
    if( strlen( name )==0 ){ // searching dirs
      if( !strchr(dp->d_name,'.') ){
	result = (char**)realloc(result,(number+1)*sizeof(char*));
	result[number++] = strcpy((char*)calloc(100,sizeof(char)),dp->d_name);
	//sprintf( xret[i++],"%s",dp->d_name);
      }
    }else{
      if( strcmp(dp->d_name,".")&&strcmp(dp->d_name,"..")&&strstr(dp->d_name, name)){
	result = (char**)realloc(result,(number+1)*sizeof(char*));
	result[number++] = strcpy((char*)calloc(100,sizeof(char)),dp->d_name);
	//sprintf( xret[i++],"%s",dp->d_name);
      }
    }
  }
  closedir(dirp);
  
  sprintf( log_mess,"dir:%s name:%s",directory,name);
  TRON( log_mess );
  for(f=0;f<number;f++){
    sprintf( log_mess, "result[%d]=%s",f,result[f]);
    TRON( log_mess );
  }
  
  // TRON("leaving list files");
  nb[0] = number;
  return result;
}
