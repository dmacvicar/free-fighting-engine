#ifndef BACKGROUND_PROCESS_H
#define BACKGROUND_PROCESS_H

#include "global.h"

int background_process(background_struct * a_background);
char * bg_elt_name(char * Bg_name,char * input);
int fix_players(Game_variables variables, Player_variables * player_array);

#endif //BACKGROUND_PROCESS_H
