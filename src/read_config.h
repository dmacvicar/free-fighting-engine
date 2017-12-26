#ifndef READ_CONFIG_H
#define READ_CONFIG_H

#include "global_add.h"
#include "sensei_config.h"

/** \file read_config.h
 * \brief functions (headers) to read mugen.cfg and system.def
 */
int read_config(Game_variables variables,Player_variables * player_array);
int apply_config(config a_config);
int read_arguments(int argc, char * argv[], Game_variables variables);
int read_system(Game_variables variables);
void print_config(config a_config,Player_variables * player_array);
int set_default_config(Game_variables variables);
int set_default_keys(Player_variables * player_array, int player);
int save_config (Game_variables variables,Player_variables * player_array);

#endif /* READ_CONFIG_H */

