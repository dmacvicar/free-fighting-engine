#ifndef MAIN_PROCESS_H
#define MAIN_PROCESS_H

#include "global_add.h"
#include "input_reader.h"

int main_process(Game_variables variables,Player_variables * player_array,int time);
int next_state(Game_variables variables);
int validation(Player_variables * player_array);

#endif /* MAIN_PROCESS_H */
