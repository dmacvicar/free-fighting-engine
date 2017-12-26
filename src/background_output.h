#ifndef BACKGROUND_OUTPUT_H
#define BACKGROUND_OUTPUT_H

#include "global.h"

int background_output(background_struct * a_background, int layer);
BITMAP * fill_bmp(SFFEntry * a_sff,int a_group,int an_index,int masked);

#endif //BACKGROUND_OUTPUT_H
