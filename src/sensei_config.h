#ifndef SENSEI_CONFIG_H
#define SENSEI_CONFIG_H

#include "global.h"
/** \file sensei_config.h
 * \brief configuration routines (header) to fix Allegro's config.c lakes
*/


char ** SENSEI_BUFFERED_FILE;
int SENSEI_NB_LINES;
int CURRENT_LINE;

int sensei_set_config_file(char * path);
int sensei_get_config_int(char * section_name,char * var,int default_value);
char * sensei_get_config_string(char * section_name,char * var,char * default_value);
int sensei_fill_characters_list(Game_variables variables);
int sensei_fill_bgs_list(Game_variables variables);
char to_minus(char a_char);
char * string_to_minus(char * a_string);
int * convert_string(char * to_parse);
double * convert_stringd(char * to_parse);
char * remove_comments(char * a_string);
char * remove_end_spaces(char * a_string);
char * check_path(char * a_path, char * system_path, char * var_name, int * error);
char * extract_path(char * a_path);

action_struct * init_actions(action_struct * action_array,int * nb);
int fill_action(action_struct * an_action);
int kof91_fill_action(action_struct * an_action,int number,int nb_frames,int speed,int offx, int offy, int defx, int defy);
char ** fill_scenes_names(int * nb);
int * fill_action_nb(int * nb);
int action_nb(char * input);
int process_action(action_struct * an_action);

int system_font_exists(Game_variables variables,int font_number);
FNTInfo * link_system_font(Game_variables variables,int font_number);

BITMAP * sensei_fill_bmp(SFFEntry * a_sff,int a_group,int an_index,int masked, int * xaxis, int * yaxis);
BITMAP * sensei_fill_bmp_uncolored(SFFEntry * a_sff,int a_group,int an_index,int masked, int * xaxis, int * yaxis,RGB * a_pal,int faced);
BITMAP * sensei_kof91_fill_bmp(KOF91Sprites * kof91_sprites,int a_group,int an_index,int max_sprites, int * xaxis, int * yaxis,int faced);
RGB * sensei_fill_pal(SFFEntry * a_sff,int a_group,int an_index,int forced, int masked);

int sensei_unset_config_file();

int sensei_music_type(char * music_filename);
int play_music(music_struct * a_music);
int stop_music(music_struct * a_music);

#endif // SENSEI_CONFIG_H
