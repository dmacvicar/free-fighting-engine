#ifndef SELECT_PROCESS_H
#define SELECT_PROCESS_H

#include "global.h"

int select_process(Game_variables variables, Player_variables * player_array, int time);
BITMAP * make_faces_screen(Game_variables variables, Player_variables * player_array);
int make_lists(Game_variables variables, Player_variables * player_array);

#endif //SELECT_PROCESS_H;
