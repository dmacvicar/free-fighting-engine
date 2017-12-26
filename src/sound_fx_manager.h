#ifndef SOUND_FX_MANAGER_H
#define SOUND_FX_MANAGER_H

#include "global_add.h"

int loadsounds(Game_variables variables);
void freesounds(void);
void Buzz (void);
void Bing (void);
void Done (void);
void Block (void);
void Paf (char gana);
void Hurt (char gana);
void Round (char which);
void Fight(void);

#endif //SOUND_FX_MANAGER_H
