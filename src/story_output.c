#include "story_output.h"
#include "storyboard_output.h"

#include "global.h"
#include "global_add.h"
#include "refresh.h"

/** \file story_output.c
 * \brief Main function that display kof91 story file or Mugen's story type
 */

int story_output(story_struct a_story,int time){
  clear ( virtscreen );
  switch (a_story.Story_type){
  case 1:
    set_palette (fli_palette);
    blit ( fli_bitmap, virtscreen, 0,0, 0,0, 320,200);
    break;
  case 2:
    storyboard_output(&a_story.storyboard);
    break;
  default:
    break;
  }
  return 0;
}
