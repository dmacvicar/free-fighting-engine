/*
    config.h
    //template//
 */

#ifndef CONFIG_H
#define CONFIG_H

/*   GAME_DEBUG
     0 = NOT debug mode 
     1 = debug mode level 1
     2 = debug mode level 2 (verbose)
     *Motive of change: binary small and faster
*/
#define GAME_DEBUG 2 

/*
    CHEAT
    0 = NOT allow change in monitor life and time and power bar
    1 = allow change...
 */

#define CHEAT 1

/*
  TIMEOVER
   0 = disable
   1 = enable
   *Exibe cronometer and interrupt figth if time is ZERO.
   * Exibe Time Up message (timeup.pcx) if time over.
*/
#define TIMEOVER 1

/*
    PERFECT
     0 - disable 
     1 - enable
     * If player wins and get zero damage then
      Exibe sprite perfect.pcx and play perfect.wav 
*/
#define PERFECT 1

/*
  SCREENSHOT
  0 - disable
  1 - enable
  * press <F2> and save a screenshot *
*/
#define SCREENSHOT 1

/*
  TEMP
  0 - disable
  1 - enable
  * activate of features in development *
*/
#define TEMP 0 

#define DEF_MAX_MONITOR_VARS 150
#define DEF_MAX_USER_VARS 50 
#define DEF_MAX_CICLES 10000

/* END OF CONFIG FLAGS */

/*******************************/
/* This redefinitions is necessary for TRON() ...*/
#define BRDATE  __DATE__
#define BRTIME  __TIME__

#endif //CONFIG_H
