/*
    logger.h
    //template//
*/

#ifndef LOGGER_H
#define LOGGER_H

#include "config.h"
#include <stdio.h>

FILE * logfile;

#if GAME_DEBUG > 0
void __tron__( char *log_mess, char *n_file , int n_line );
void __tronstart__( char *log_mess, char *n_file , int n_line );
#endif
void __error__( char *log_mess, char *n_file , int n_line );
void TRONSTOP();

#endif //LOGGER_H
