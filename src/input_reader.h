#ifndef INPUT_READER_H
#define INPUT_READER_H

#include "global_add.h"

int input_reader(Game_variables variables, Player_variables * player_array);
int buton_pressed(Player_variables * player_array, int player);
void clear_input_states(Player_variables * player_array,int a_player);
int want_move(Player_variables * player_array,int a_player);

#endif /* INPUT_READER_H */
