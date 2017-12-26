#include "load_characters.h"
#include "global.h"
#include "string.h"
#include <stdio.h>
#include "macros.h"
#include "load_sprites.h"
#include "sensei_config.h"
#include "initfiles.h"
#include "loads.h"

/** \file load_characters.c
 * \brief Functions to load sprites, musics, datas, of a player
 */

int load_kof91_p1(char * name);
int load_mugenchar(Player_variables * a_player);
int load_kof91char(Player_variables * a_player);

int load_character(Player_variables * player_array,int player){
  char * result;
  result = (char*)calloc(255,sizeof(char));
  switch (player_array[player].type){
  case 0: // None
    break;
  case 1: // KOF 91
    load_kof91char(&player_array[player]);
    break;
  case 2: // Mugen's chars
    load_mugenchar(&player_array[player]);
    break;
  default :
    break;
  }
  free(result);
  return 0;
} // load_character

int load_kof91_p1(char * name){
 
  /******* GET CHARACTER 1 INFO *********************/
  char * passeur;
  passeur = strcpy((char*)calloc(255,sizeof(char)),name);
  put_backslash(passeur);
  passeur = strcat(passeur,"char.ini");
  
  set_config_file (passeur);
  sprintf (sectn,name);

  p1.width = get_config_int (sectn, "static_w", 100);
  p1.spunch.w = get_config_int (sectn, "spunch_w", 150);
  p1.wpunch.w = get_config_int (sectn, "wpunch_w", 150);
  p1.skick.w = get_config_int (sectn, "skick_w", 150);
  p1.wkick.w = get_config_int (sectn, "wkick_w", 150);
  p1.apunch.w = get_config_int (sectn, "apunch_w", 150);
  p1.gpunch.w = get_config_int (sectn, "gpunch_w", 150);
  p1.akick.w = get_config_int (sectn, "akick_w", 150);
  p1.gkick.w = get_config_int (sectn, "gkick_w", 150);
  p1.intro.w = get_config_int (sectn, "intro_w", 150);
  p1.ko.w = get_config_int (sectn, "ko_w", 150);
  p1.outwin.w = get_config_int (sectn, "outwin_w", 150);
  p1.height = get_config_int (sectn, "height", 130);
  p1.statik.nbf = get_config_int (sectn, "static_nbf", 4);
  p1.walk.nbf = get_config_int (sectn, "walk_nbf", 5);
  p1.spunch.nbf = get_config_int (sectn, "spunch_nbf", 3);
  p1.wpunch.nbf = get_config_int (sectn, "wpunch_nbf", 3);
  p1.skick.nbf = get_config_int (sectn, "skick_nbf", 4);
  p1.wkick.nbf = get_config_int (sectn, "wkick_nbf", 4);
  p1.apunch.nbf = get_config_int (sectn, "apunch_nbf", 1);
  p1.gpunch.nbf = get_config_int (sectn, "gpunch_nbf", 4);
  p1.akick.nbf = get_config_int (sectn, "akick_nbf", 1);
  p1.gkick.nbf = get_config_int (sectn, "gkick_nbf", 4);
  p1.hurt.nbf = get_config_int (sectn, "hurt_nbf", 1);
  p1.ghurt.nbf = get_config_int (sectn, "ghurt_nbf", 1);
  p1.intro.nbf = get_config_int (sectn, "intro_nbf", 1);
  p1.outwin.nbf = get_config_int (sectn, "outwin_nbf", 1);
  p1.statik.spd = get_config_int (sectn, "static_spd", 8);
  p1.walk.spd = get_config_int (sectn, "walk_spd", 8);
  p1.spunch.spd = get_config_int (sectn, "spunch_spd", 8);
  p1.wpunch.spd = get_config_int (sectn, "wpunch_spd", 8);
  p1.skick.spd = get_config_int (sectn, "skick_spd", 8);
  p1.wkick.spd = get_config_int (sectn, "wkick_spd", 8);
  p1.apunch.spd = get_config_int (sectn, "apunch_spd", 8);
  p1.gpunch.spd = get_config_int (sectn, "gpunch_spd", 8);
  p1.akick.spd = get_config_int (sectn, "akick_spd", 8);
  p1.gkick.spd = get_config_int (sectn, "gkick_spd", 8);
  p1.outwin.spd = get_config_int (sectn, "outwin_spd", 10);
  p1.spunch.hit = get_config_int (sectn, "spunch_hit", 2);
  p1.wpunch.hit = get_config_int (sectn, "wpunch_hit", 2);
  p1.skick.hit = get_config_int (sectn, "skick_hit", 2);
  p1.wkick.hit = get_config_int (sectn, "wkick_hit", 2);
  p1.apunch.hit = get_config_int (sectn, "apunch_hit", 1);
  p1.gpunch.hit = get_config_int (sectn, "gpunch_hit", 2);
  p1.akick.hit = get_config_int (sectn, "akick_hit", 1);
  p1.gkick.hit = get_config_int (sectn, "gkick_hit", 2);
  p1.spunch.dmg = get_config_int (sectn, "spunch_dmg", 2);
  p1.wpunch.dmg = get_config_int (sectn, "wpunch_dmg", 1);
  p1.skick.dmg = get_config_int (sectn, "skick_dmg", 2);
  p1.wkick.dmg = get_config_int (sectn, "wkick_dmg", 1);
  p1.apunch.dmg = get_config_int (sectn, "apunch_dmg", 1);
  p1.gpunch.dmg = get_config_int (sectn, "gpunch_dmg", 1);
  p1.akick.dmg = get_config_int (sectn, "akick_dmg", 2);
  p1.gkick.dmg = get_config_int (sectn, "gkick_dmg", 2);
  p1.spunch.offx = get_config_int (sectn, "spunch_offx", p1.spunch.w);
  p1.wpunch.offx = get_config_int (sectn, "wpunch_offx", p1.wpunch.w);
  p1.skick.offx = get_config_int (sectn, "skick_offx", p1.skick.w);
  p1.wkick.offx = get_config_int (sectn, "wkick_offx", p1.wkick.w);
  p1.apunch.offx = get_config_int (sectn, "apunch_offx", p1.apunch.w);
  p1.gpunch.offx = get_config_int (sectn, "gpunch_offx", p1.gpunch.w);
  p1.akick.offx = get_config_int (sectn, "akick_offx", p1.akick.w);
  p1.gkick.offx = get_config_int (sectn, "gkick_offx", p1.gkick.w);
  p1.spunch.offy = get_config_int (sectn, "spunch_offy", p1.height - 50);
  p1.wpunch.offy = get_config_int (sectn, "wpunch_offy", p1.height - 50);
  p1.skick.offy = get_config_int (sectn, "skick_offy", p1.height - 50);
  p1.wkick.offy = get_config_int (sectn, "wkick_offy", p1.height - 50);
  p1.apunch.offy = get_config_int (sectn, "apunch_offy", p1.height - 50);
  p1.gpunch.offy = get_config_int (sectn, "gpunch_offy", p1.height - 50);
  p1.akick.offy = get_config_int (sectn, "akick_offy", p1.height - 50);
  p1.gkick.offy = get_config_int (sectn, "gkick_offy", p1.height - 50);
  p1.statik.defx = get_config_int (sectn, "static_defx", p1.width);
  p1.walk.defx = get_config_int (sectn, "walk_defx", p1.width);
  p1.jump.defx = get_config_int (sectn, "jump_defx", p1.width);
  p1.crouch.defx = get_config_int (sectn, "crouch_defx", p1.width);
  p1.spunch.defx = get_config_int (sectn, "spunch_defx", p1.width);
  p1.wpunch.defx = get_config_int (sectn, "wpunch_defx", p1.width);
  p1.skick.defx = get_config_int (sectn, "skick_defx", p1.width);
  p1.wkick.defx = get_config_int (sectn, "wkick_defx", p1.width);
  p1.apunch.defx = get_config_int (sectn, "apunch_defx", p1.width);
  p1.gpunch.defx = get_config_int (sectn, "gpunch_defx", p1.width);
  p1.akick.defx = get_config_int (sectn, "akick_defx", p1.width);
  p1.gkick.defx = get_config_int (sectn, "gkick_defx", p1.width);
  p1.statik.defy = get_config_int (sectn, "static_defy", p1.height - 50);
  p1.walk.defy = get_config_int (sectn, "walk_defy", p1.height - 50);
  p1.jump.defy = get_config_int (sectn, "jump_defy", p1.height - 50);
  p1.crouch.defy = get_config_int (sectn, "crouch_defy", p1.height - 50);
  p1.spunch.defy = get_config_int (sectn, "spunch_defy", p1.height - 50);
  p1.wpunch.defy = get_config_int (sectn, "wpunch_defy", p1.height - 50);
  p1.skick.defy = get_config_int (sectn, "skick_defy", p1.height - 50);
  p1.wkick.defy = get_config_int (sectn, "wkick_defy", p1.height - 50);
  p1.apunch.defy = get_config_int (sectn, "apunch_defy", p1.height - 50);
  p1.gpunch.defy = get_config_int (sectn, "gpunch_defy", p1.height - 50);
  p1.akick.defy = get_config_int (sectn, "akick_defy", p1.height - 50);
  p1.gkick.defy = get_config_int (sectn, "gkick_defy", p1.height - 50);
  female1 = get_config_int (sectn, "female", 0);
  
  for (i = 0; i < 2; i++)
    temp_strg[i] = 0;

  p1.fireb.flg = get_config_int (sectn, "fireb", 0);

  if (p1.fireb.flg){
      fball_h1 = get_config_int (sectn, "fball_h", 1);
      p1.fball.w = get_config_int (sectn, "fball_w", 1);
      p1.fball.nbf = get_config_int (sectn, "fball_nbf", 1);
      p1.fball.spd = get_config_int (sectn, "fball_spd", 1);
      p1.fball.pix = get_config_int (sectn, "fball_pix", 1);
      fball_cx1 = get_config_int (sectn, "fball_cx", 1);
      fball_cy1 = get_config_int (sectn, "fball_cy", 1);
      p1.fball.offx = get_config_int (sectn, "fball_offx", p1.fball.w);
      p1.fball.offy = get_config_int (sectn, "fball_offy", 10);

      p1.fireb.w = get_config_int (sectn, "fireb_w", 1);
      p1.fireb.nbf = get_config_int (sectn, "fireb_nbf", 1);
      p1.fireb.spd = get_config_int (sectn, "fireb_spd", 1);
      p1.fireb.hit = get_config_int (sectn, "fireb_hit", 1);
      sprintf (p1.fireb.exec, "%s",
	       get_config_string (sectn, "fireb_exec", ""));

      /*
	p1.fireb.exec=
	get_config_string(sectn, "fireb_exec", "");
      */

      p1.fireb.dmg = get_config_int (sectn, "fireb_dmg", 3);

      cx = 1;
      nb = 0;
      i = 0;
      y = 0;

      while (cx){
	  c = p1.fireb.exec[i];
	  if (c != ' '){
	    if (c == '*'){
	      p1.fireb.end = nb;
	      cx = 0;
	    }
	    
	    temp_strg[y] = c;
	    y++;
	  }else{
	    // p1.fireb.seq[nb] = get_kstatus (temp_strg);
	    nb++;
	    y = 0;
	  }
	  
	  i++;
      }
  }
  
  for (i = 0; i < 2; i++)
    temp_strg[i] = 0;
  
  p1.rush.flg = get_config_int (sectn, "rush", 0);

  if (p1.rush.flg){
      p1.rush.w = get_config_int (sectn, "rush_w", 1);
      p1.rush.nbf = get_config_int (sectn, "rush_nbf", 1);
      p1.rush.spd = get_config_int (sectn, "rush_spd", 1);
      p1.rush.hit = get_config_int (sectn, "rush_hit", 1);
      p1.rush.rot = get_config_int (sectn, "rush_rot", 1);
      p1.rush.pix = get_config_int (sectn, "rush_pix", 1);
      sprintf (p1.rush.exec, "%s",get_config_string (sectn, "rush_exec", ""));
      
      /*
	p1.rush.exec=
	get_config_string(sectn, "rush_exec", "");
      */

      p1.rush.dmg = get_config_int (sectn, "rush_dmg", 3);
      p1.rush.offx = get_config_int (sectn, "rush_offx", p1.rush.w);
      p1.rush.offy = get_config_int (sectn, "rush_offy", 10);

      cx = 1;
      nb = 0;
      i = 0;
      y = 0;

      while (cx)
	{
	  c = p1.rush.exec[i];

	  if (c != ' ')
	    {
	      if (c == '*')
		{
		  p1.rush.end = nb;
		  cx = 0;
		}

	      temp_strg[y] = c;
	      y++;
	    }
	  else
	    {
	      // p1.rush.seq[nb] = get_kstatus (temp_strg);
	      nb++;
	      y = 0;
	    }

	  i++;
	}

    }



  for (i = 0; i < 2; i++)
    temp_strg[i] = 0;

  p1.smove.flg = get_config_int (sectn, "smove", 0);

  if (p1.smove.flg)
    {
      p1.smove.w = get_config_int (sectn, "smove_w", 1);
      p1.smove.nbf = get_config_int (sectn, "smove_nbf", 1);
      p1.smove.spd = get_config_int (sectn, "smove_spd", 1);
      p1.smove.hit = get_config_int (sectn, "smove_hit", 1);
      p1.smove.rot = get_config_int (sectn, "smove_rot", 1);


      sprintf (p1.smove.exec, "%s",
	       get_config_string (sectn, "smove_exec", ""));

      /*
	p1.smove.exec=
	get_config_string(sectn, "smove_exec", "");

      */
      p1.smove.dmg = get_config_int (sectn, "smove_dmg", 3);
      p1.smove.offx = get_config_int (sectn, "smove_offx", p1.smove.w);
      p1.smove.offy = get_config_int (sectn, "smove_offy", 10);

      cx = 1;
      nb = 0;
      i = 0;
      y = 0;

      while (cx)
	{
	  c = p1.smove.exec[i];

	  if (c != ' ')
	    {
	      if (c == '*')
		{
		  p1.smove.end = nb;
		  cx = 0;
		}

	      temp_strg[y] = c;
	      y++;
	    }
	  else
	    {
	      // p1.smove.seq[nb] = get_kstatus (temp_strg);
	      nb++;
	      y = 0;
	    }

	  i++;
	}

    }
  /* SPECIALS */

  for (i = 0; i < 2; i++)
    temp_strg[i] = 0;

  p1.firebx.flg = get_config_int (sectn, "firebx", 0);

  if (p1.firebx.flg)
    {
      fballx_h1 = get_config_int (sectn, "fballx_h", 1);
      p1.fballx.w = get_config_int (sectn, "fballx_w", 1);
      p1.fballx.nbf = get_config_int (sectn, "fballx_nbf", 1);
      p1.fballx.spd = get_config_int (sectn, "fballx_spd", 1);
      p1.fballx.pix = get_config_int (sectn, "fballx_pix", 1);
      fballx_cx1 = get_config_int (sectn, "fballx_cx", 1);
      fballx_cy1 = get_config_int (sectn, "fballx_cy", 1);
      p1.fballx.offx = get_config_int (sectn, "fballx_offx", p1.fballx.w);
      p1.fballx.offy = get_config_int (sectn, "fballx_offy", 10);

      p1.firebx.w = get_config_int (sectn, "firebx_w", 1);
      p1.firebx.nbf = get_config_int (sectn, "firebx_nbf", 1);
      p1.firebx.spd = get_config_int (sectn, "firebx_spd", 1);
      p1.firebx.hit = get_config_int (sectn, "firebx_hit", 1);


      sprintf (p1.firebx.exec, "%s",
	       get_config_string (sectn, "firebx_exec", ""));
      /*
	p1.firebx.exec=
	get_config_string(sectn, "firebx_exec", "");
      */

      p1.firebx.spec = get_config_int (sectn, "firebx_spec", 0);
      p1.firebx.dmg =
	get_config_int (sectn, "firebx_dmg", p1.firebx.spec ? 5 : 3);


      if (!p1.firebx.spec)
	p1.firebx.sflg = 1;

      else
	p1.firebx.sflg = 0;

      cx = 1;
      nb = 0;
      i = 0;
      y = 0;

      while (cx)
	{
	  c = p1.firebx.exec[i];

	  if (c != ' ')
	    {
	      if (c == '*')
		{
		  p1.firebx.end = nb;
		  cx = 0;
		}

	      temp_strg[y] = c;
	      y++;
	    }
	  else
	    {
	      // p1.firebx.seq[nb] = get_kstatus (temp_strg);
	      nb++;
	      y = 0;
	    }

	  i++;
	}

    }



  for (i = 0; i < 2; i++)
    temp_strg[i] = 0;

  p1.rushx.flg = get_config_int (sectn, "rushx", 0);

  if (p1.rushx.flg)
    {
      p1.rushx.w = get_config_int (sectn, "rushx_w", 1);
      p1.rushx.nbf = get_config_int (sectn, "rushx_nbf", 1);
      p1.rushx.spd = get_config_int (sectn, "rushx_spd", 1);
      p1.rushx.hit = get_config_int (sectn, "rushx_hit", 1);
      p1.rushx.rot = get_config_int (sectn, "rushx_rot", 1);
      p1.rushx.pix = get_config_int (sectn, "rushx_pix", 1);
      sprintf (p1.rushx.exec, "%s",get_config_string (sectn, "rushx_exec", ""));

      /*
	p1.rushx.exec=
	get_config_string(sectn, "rushx_exec", "");
      */

      p1.rushx.spec = get_config_int (sectn, "rushx_spec", 0);
      p1.rushx.dmg =
	get_config_int (sectn, "rushx_dmg", p1.rushx.spec ? 5 : 3);
      p1.rushx.offx = get_config_int (sectn, "rushx_offx", p1.rushx.w);
      p1.rushx.offy = get_config_int (sectn, "rushx_offy", 10);

      if (!p1.rushx.spec)
	p1.rushx.sflg = 1;

      else
	p1.rushx.sflg = 0;

      cx = 1;
      nb = 0;
      i = 0;
      y = 0;

      while (cx)
	{
	  c = p1.rushx.exec[i];

	  if (c != ' ')
	    {
	      if (c == '*')
		{
		  p1.rushx.end = nb;
		  cx = 0;
		}

	      temp_strg[y] = c;
	      y++;
	    }
	  else
	    {
	      // p1.rushx.seq[nb] = get_kstatus (temp_strg);
	      nb++;
	      y = 0;
	    }

	  i++;
	}
    }

  for (i = 0; i < 2; i++)
    temp_strg[i] = 0;

  p1.smovex.flg = get_config_int (sectn, "smovex", 0);

  if (p1.smovex.flg)
    {
      p1.smovex.w = get_config_int (sectn, "smovex_w", 1);
      p1.smovex.nbf = get_config_int (sectn, "smovex_nbf", 1);
      p1.smovex.spd = get_config_int (sectn, "smovex_spd", 1);
      p1.smovex.hit = get_config_int (sectn, "smovex_hit", 1);
      p1.smovex.rot = get_config_int (sectn, "smovex_rot", 1);

      sprintf (p1.smovex.exec, "%s",
	       get_config_string (sectn, "smovex_exec", ""));
      /*
	p1.smovex.exec=
	get_config_string(sectn, "smovex_exec", "");
      */

      p1.smovex.spec = get_config_int (sectn, "smovex_spec", 0);
      p1.smovex.dmg =
	get_config_int (sectn, "smovex_dmg", p1.smovex.spec ? 5 : 3);
      p1.smovex.offx = get_config_int (sectn, "smovex_offx", p1.smovex.w);
      p1.smovex.offy = get_config_int (sectn, "smovex_offy", 10);
      if (!p1.smovex.spec)
	p1.smovex.sflg = 1;
      else
	p1.smovex.sflg = 0;
      cx = 1;
      nb = 0;
      i = 0;
      y = 0;
      while (cx)
	{
	  c = p1.smovex.exec[i];
	  if (c != ' ')
	    {
	      if (c == '*')
		{
		  p1.smovex.end = nb;
		  cx = 0;
		}

	      temp_strg[y] = c;
	      y++;
	    }
	  else
	    {
	      // p1.smovex.seq[nb] = get_kstatus (temp_strg);
	      nb++;
	      y = 0;
	    }
	  i++;
	}
    }
  tol1 = (p1.statik.defx);

  /*********** LOAD SPRITES1 *********************/
  return 0;
} // load_kof91_p1

int load_kof91char(Player_variables * a_player){
  int error = 0;
  int pcx_nb = 0;
  char * message;
  char * path;
  char * buffer;
  char * buffer2;
  char ** pcx_files;
  int nb = 0;
  int speed = 0;
  int offx = 0;
  int offy = 0;
  int defx = 0;
  int defy = 0;
  int i = 0;
  int sprite_index = 0;
  message = (char*)calloc(255,sizeof(char));
  buffer = (char*)calloc(255,sizeof(char));
  buffer2 = (char*)calloc(255,sizeof(char));
  
  /** First we allocate the good memory size for pcx storage
   */
  path = strcpy((char*)calloc(255,sizeof(char)),extract_path(a_player->def_path));
  pcx_files =  sensei_list_files(&pcx_nb,path,".pcx");
  a_player->max_KOF91_sprites = pcx_nb;
  a_player->KOF91_sprites = (KOF91Sprites*)calloc((pcx_nb+1),sizeof(KOF91Sprites));
  a_player->action_array = (action_struct*)calloc(100,sizeof(action_struct));
  a_player->action_number = 100;
  for (i=0;i<100;i++){
    a_player->action_array[i].number = -1;
  }
  set_config_file(a_player->def_path);
  /** Here begin the laborious stuff
      could be shorter but it's more re-usable as is (no ;)  )
  */
  // Load standing pcx
  nb = get_config_int(a_player->name,"static_nbf",4);
  for (i=1;i<nb+1;i++){
    buffer = strcpy((char*)calloc(255,sizeof(char)),path);
    put_backslash(buffer);
    sprintf(buffer2,"static%i.pcx",i);
    buffer = strcat(buffer,buffer2);
    a_player->KOF91_sprites[sprite_index].sprite = xload_pcx(buffer,a_player->KOF91_sprites[sprite_index].pal);
    a_player->KOF91_sprites[sprite_index].group = 0;
    a_player->KOF91_sprites[sprite_index].index = i-1;
	sprite_index++;
  }
  speed = get_config_int(a_player->name,"static_spd",8);
  offx = get_config_int(a_player->name,"static_offx",0);
  offy = get_config_int(a_player->name,"static_offy",0);
  defx = get_config_int(a_player->name,"static_defx",0);
  defy = get_config_int(a_player->name,"static_defy",0);
  kof91_fill_action(&a_player->action_array[0],0,nb,speed,offx,offy,defx,defy);
  
  free(message);
  free(buffer);
  free(buffer2);
  return error;
}// load_kof91char

int load_mugenchar(Player_variables * a_player){
  char * message;
  int i;
  
  message = (char*)calloc(255,sizeof(char));
  TRON("loading mugen char");
  sprintf(message,"Path to load %s",a_player->sprite_path);
  TRON(message);
  a_player->player_sff = sffLoad(a_player->sprite_path);
  TRON("after loading sff");
  free(message);
  
  /* Dealing with air file */
  sensei_set_config_file(a_player->anim_path);
  a_player->action_array = init_actions(a_player->action_array,&a_player->action_number);
  for (i=0;i<a_player->action_number;i++){
    fill_action(&a_player->action_array[i]);
  }
  
  return 0;
}
