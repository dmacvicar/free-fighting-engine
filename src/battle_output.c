#include "battle_output.h"
#include "background_output.h"
#include "player_output.h"

#include "global.h"

int battle_output(Game_variables variables,Player_variables * player_array,int time){
  int error = 0;
  error += background_output(&variables->Fight_bg,0);
  
  error += player_output(variables,player_array,time);
 
  error += background_output(&variables->Fight_bg,1);
  return 0;
} // battle_output
