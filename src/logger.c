#include "global.h"
#include "macros.h"
#include "config.h"
#include  <stdio.h>
#include "logger.h"

/** \file logger.c
 * \brief Functions by Ricleite to write Warnings, message, errors, in a log file
 */

/*************************************************************************
 
 patch: ric@asbyte.com.br
 
**************************************************************************/
#if GAME_DEBUG > 0
void __tron__( char *log_mess, char *n_file , int n_line )
{
  if (  logfile == ( FILE* ) NULL ){
    fprintf( stderr, "\nWARNING! Can't open log file.\n" );
    fprintf( stderr, "TRON() ERROR in: %s LINE:%d\n",n_file,n_line );
  }
  else{
    fprintf( logfile, "FILE: %s LINE:%d: %s\n",n_file, n_line, log_mess );
  }
}

void __tronstart__( char *log_mess, char *n_file , int n_line )
{
  if ( ( logfile = fopen( "kof91.log", "a" ) ) == ( FILE* ) NULL ){
    fprintf( stderr, "\nWARNING!. Can't open log file.\n" );
    fprintf( stderr, "TRONSTART() ERROR in: %s LINE:%d\n",n_file,n_line );
  }else{
    fprintf( logfile, "******************************************\n<TRONSTART> FILE:%s LINE:%d: %s\n",n_file, n_line, log_mess );
  }
}
#endif

void TRONSTOP(){
  fclose(logfile);
}

/*******************************/
void __error__( char *log_mess, char *n_file , int n_line )
{
  static FILE * logfile;
  
  if ( ( logfile = fopen( "kof91.log", "a" ) ) == ( FILE* ) NULL ){
    fprintf( stderr, "\n(ER)WARNING!. Can't open log file.\n" );
    fprintf( stderr, "ERROR() ERROR in: %s LINE:%d\n",n_file,n_line );
    allegro_exit();
    exit( 0 );
  }
  else
    {
      fprintf( logfile, "<ERROR> FILE:%s LINE:%d:\n  ***ERROR: %s\n\n", n_file, n_line, log_mess );
    }
  fclose( logfile );
  return;
}

