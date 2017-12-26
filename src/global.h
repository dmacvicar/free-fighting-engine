#ifndef MAIN_H
#ifndef GLOBAL_H
#define GLOBAL_H

#include "config.h"
#include <allegro.h>
#include "almp3.h"
#include "time.h"
#include "global_add.h"
#include "loader.h"

/** \file global.h
 * \brief global vars and struct definitions used by old KOF 91
 */
extern struct
{
  struct
  {
    int port;
    int volume;
    char *name;
  }
    output;
}
Options;

/******************** mp3 is back ******************/
typedef struct {
  PACKFILE *f;
  ALMP3_MP3STREAM *s;
} MP3FILE;

extern MP3FILE *mp3 ;
extern int mp3status;
extern int mp3_loop;
/*****************************************/

/******************* Necessary for the font loader *********/
extern FNTInfo* fontInfo;
extern PALETTE* pal[16];
/******************************************************/

// global variables

extern DATAFILE *creditflic ;
extern DATAFILE *fonts_dat ;
extern FONT *small_font ;

extern MIDI *music ;

extern SAMPLE *rd1 ;
extern SAMPLE *rd2 ;
extern SAMPLE *rd3 ;

extern SAMPLE *fight ;

extern SAMPLE *hit_alwa ;
extern SAMPLE *hit_good ;

extern SAMPLE *wp_alwa ;
extern SAMPLE *wk_alwa ;
extern SAMPLE *sp_alwa ;
extern SAMPLE *sk_alwa ;

extern SAMPLE *hit1 ;
extern SAMPLE *hit2 ;

extern SAMPLE *block_snd ;

extern SAMPLE *hadoken1 ;
extern SAMPLE *hadoken2 ;
extern SAMPLE *copter1 ;
extern SAMPLE *copter2 ;
extern SAMPLE *dragon1 ;
extern SAMPLE *dragon2 ;

extern SAMPLE *hadokenx1 ;
extern SAMPLE *hadokenx2 ;
extern SAMPLE *copterx1 ;
extern SAMPLE *copterx2 ;
extern SAMPLE *dragonx1 ;
extern SAMPLE *dragonx2 ;

extern SAMPLE *done ;
extern SAMPLE *bing ;
extern SAMPLE *buzz ;

extern SAMPLE *ko_snd ;

extern SAMPLE *prfct_snd ;
extern SAMPLE *to_snd ;

extern SAMPLE *argh_snd ;
extern SAMPLE *female_snd ;

extern BITMAP *virtscreen ;             /* virtual screen                   */

extern BITMAP *zoomscreen ;

extern BITMAP *scanliner ;              /* blit screen for scanlines        */


extern PALLETE Pal ;
extern PALLETE TPal ;

extern BITMAP *Title ;

extern BITMAP *Selecteur1 ;
extern BITMAP *Selecteur2 ;

extern BITMAP *LBbanner;
extern BITMAP *LBbanner2;


extern BITMAP *Bar ;
extern BITMAP *Bar2 ;

extern BITMAP *Power ;

extern BITMAP *PBar ;

extern BITMAP *WImpact[ 11 ] ;
extern BITMAP *SImpact[ 11 ] ;
extern BITMAP *BlockImpact[ 11 ] ;
extern BITMAP *B_Temp ;

extern BITMAP *Carton_R1 ;
extern BITMAP *Carton_R2 ;
extern BITMAP *Carton_R3 ;

extern BITMAP *Carton_FT ;

extern BITMAP *Carton_WN ;

extern BITMAP *Carton_KO ;

#if TIMEOVER == 1
BITMAP *Carton_TO ;
#endif

extern BITMAP *novic0 ;
extern BITMAP *novic1 ;

extern BITMAP *avic0 ;
extern BITMAP *avic1 ;

extern BITMAP *Face1 ;
extern BITMAP *Face2 ;

extern BITMAP *Icon1 ;
extern BITMAP *Icon2 ;

extern BITMAP *Lock ;


extern BITMAP *Bkgd ;

extern BITMAP *Frgd ;

/* BITMAPS das caras ao lado da barra de LIFE ! */

extern BITMAP *tface1;
extern BITMAP *tface2;

extern char buffer[100];
extern char file2[200];

extern int opt; /* para as novas opções, intro, display, winner e etc. */
extern int t_clock;

/* extern BITMAP *Blood ; */

#if TIMEOVER > 0
BITMAP *B_clock[ 11 ];
#endif

#if PERFECT == 1
BITMAP *B_prfct;
#endif


/******************************************/
struct PLAYER_BMP_STRUCT
{
	BITMAP *Static[ 999 ];
	BITMAP *Walk[ 999 ];
	BITMAP *Single[ 999 ];
	BITMAP *Punch[ 999 ];
	BITMAP *WPunch[ 999 ];
	BITMAP *Kick[ 999 ];
	BITMAP *WKick[ 999 ];
	BITMAP *Jump[ 999 ];
	BITMAP *KO[ 999 ];
	BITMAP *Hurt[ 999 ];
	BITMAP *GHurt[ 999 ];
	BITMAP *AKick[ 999 ];
	BITMAP *APunch[ 999 ];
	BITMAP *GKick[ 999 ];
	BITMAP *GPunch[ 999 ];
	BITMAP *FireB[ 999 ];
	BITMAP *FBall[ 999 ];
	BITMAP *Rush[ 999 ];
	BITMAP *SMove[ 999 ];
	BITMAP *FireBX[ 999 ];
	BITMAP *FBallX[ 999 ];
	BITMAP *RushX[ 999 ];
	BITMAP *SMoveX[ 999 ];
	BITMAP *NMoves[ 999 ][ 999 ];
};


struct MOVE
{
	int w ;
	char nbf, spd ;
	int defx , defy ;
};

struct AMOVE
{
	int w ;
	char nbf, spd ;
	int defx , defy ;

	char hit, dmg ;
	int offx , offy ;
};

struct SMOVE
{
	int w ;
	char nbf, spd ;
	int defx , defy ;

	char hit, dmg ;
	int offx , offy ;

	char flg, rot, pix, end, succ, spec, sflg ;
	char exec[255] ;
	char seq[ 40 ] ;
	char nb ;

};

struct PLAYER_DATA_STRUCT
{
	char flag ;
	int height, width ;

	int limoffx , limoffy ;
	int limdefx , limdefy ;

	int wimpact_ct ;
	int simpact_ct ;
	int bimpact_ct ;

	struct MOVE statik ;
	struct MOVE walk ;
	struct MOVE crouch ;
	struct MOVE hurt ;
	struct MOVE ghurt ;
	struct MOVE jump ;
	struct MOVE intro ;
	struct MOVE outwin ;
	struct MOVE ko ;

	struct AMOVE wpunch ;
	struct AMOVE spunch ;
	struct AMOVE apunch ;
	struct AMOVE gpunch ;
	struct AMOVE wkick ;
	struct AMOVE skick ;
	struct AMOVE gkick ;
	struct AMOVE akick ;

	struct SMOVE fireb ;
	struct SMOVE fball ;
	struct SMOVE rush ;
	struct SMOVE smove ;

	struct SMOVE firebx ;
	struct SMOVE fballx ;
	struct SMOVE rushx ;
	struct SMOVE smovex ;

};

extern struct PLAYER_BMP_STRUCT Player1 ;
extern struct PLAYER_BMP_STRUCT Player2 ;

extern struct PLAYER_DATA_STRUCT p1 ;
extern struct PLAYER_DATA_STRUCT p2 ;




/******************************************/

extern char animated ;
extern char foreground ;

extern char bkgd_counter ;
extern char bkgd_delay ;

extern int bkgdlim ;
extern int zoomsup ;
extern int zoomwidth;

extern unsigned char j ;
extern int gmode;
extern char diff ;


// story variables
extern char story ;
extern int sel1, sel2 ;
extern char debug ;

// string and key variables
extern char charname [ 1000 ][ 30 ] ;
extern char bkgdname [ 200 ][ 30 ] ;
extern char flcname [ 100 ][ 30 ] ;

extern int nbchar ;
extern int nbbkgd ;
extern int nbflc ;

extern char defeated[ 1000 ];
extern char present[ 1000 ];
extern char secretchar[ 1000 ];

extern int num ;
extern char tilenum[ 4 ] ;

extern char charn1[ 40 ] ;
extern char charn2[ 40 ] ;

extern char bkgdnum[ 4 ] ;

extern char file[ 200 ] ;
extern char passeur[ 100 ] ;
extern char sectn[ 50 ] ;

extern char temp_strg[ 2 ] ;

extern char last_char ;

extern char get_kstatus ( char strg[] ) ;

extern char check_kstatus1 ( char ctrl_key ) ;
extern char check_kstatus2 ( char ctrl_key ) ;

extern char last_status1 ;
extern char last_status2 ;

extern int fball_h1 , fball_h2 ;
extern int fballx_h1 , fballx_h2 ;

extern char autho_ht1 , autho_ht2 ;

extern char wimpact_nbf ;
extern char simpact_nbf ;
extern char bimpact_nbf ;

// control keys variables

extern int p1_up , p2_up ;
extern int p1_down , p2_down ;
extern int p1_left , p2_left ;
extern int p1_right , p2_right ;
extern int p1_wpunch , p2_wpunch ;
extern int p1_spunch , p2_spunch ;
extern int p1_wkick , p2_wkick ;
extern int p1_skick , p2_skick ;

// AI variables

extern int offense , defense ;

extern char easy_def , easy_off ;
extern char medium_def , medium_off ;
extern char hard_def , hard_off ;

extern int ai_walkf , ai_walkb ;
extern int ai_static ;

// misc

extern int mp3_on ;

extern int intro_delay ;

extern int pan;
extern int pitch;

extern int snd_vol , midi_vol ;

extern int start_x , start_y ;

extern int gfmode;
extern int stretch;

extern int screen_height;
extern int screen_width;
extern int screen_depth;

extern int full_screen;
extern char autorise ;

/* Displays, lifebars, clock, powerbars, victory flas etc...*/

extern int life1, life2 ;
extern int spower1, spower2 ;
extern char vic_flag, vic1, vic2;

extern int clone;

// END OF GLOBAL DEFINITIONS

extern char c ;
extern int cx, cy;                      // Current X and Y position in the bkgd + misc
extern int x, y;                        // Used in for loops  + misc
extern int fx, fy;
extern int ok ;                         // Loop until ok==0
extern int s ;                          // Scroll speed (2 pixels per frame)
extern int misc ;
//long t1, t2,
extern long n;			      // For calculating FPS

extern int flag ;                     // sprite cycling flags
extern int flag2 ;

extern char hflag , hflag2 ;

extern int checkint ;


extern char frameskip;
extern char skp_flag;

extern int sens1 ;                     // jump flags
extern int sens2 ;
extern int i;
extern int g , h , nb ;			    // Miscellaneous variables

extern char com_block ;
extern char com_gblock ;

extern char com_walkf ;
extern char com_walkb ;

extern int spr1x , spr1y ;       // Sprites coordinates
extern int spr2x , spr2y ;

extern char oldsel1 , oldsel2 ;
extern char last_sel1, last_sel2 ; // INITIALIZING Selection of chars

extern char p2_sel ;

extern int angle ;

extern char bgd ;

extern int sel_player1 , sel_player2 ;

extern int alt_color , tcolor , bcolor ;

extern int sel_bkgd ;

extern int text_color ;

extern int deb ;
// extern char round ;

extern int actual ;			// actual sprite status
extern int actual2 ;

extern char ak , ak2 ;          // flag air-kick
extern char apch , apch2 ;      // flag air-punch

extern char limak , limak2 ;

extern signed char limp1 , limp2 ;

extern char nbpar ;

extern char vsynch ;


extern int delayer ;

// character size info

extern int sol1 , sol2 ; // INITIALIZING
extern int tol1 , tol2 ;
extern int jump_how1 , jump_how2 ;

extern int hitfram1, hitfram2 ; // INITIALIZING HIT FRAME

extern char female1 , female2 ;

// character animation info

extern int rush_stop1 , rush_stop2 ;
extern int smove_stop1 , smove_stop2 ;

extern int rushx_stop1 , rushx_stop2 ;
extern int smovex_stop1 , smovex_stop2 ;


extern char damag1 , damag2 ;

extern char fball1 , fball2 ;

extern int fb1x , fb2x ; // INITIALIZING FIREBALL X,Y COORDENATES
extern int fb1y , fb2y ; // INITIALIZING FIREBALL X,Y COORDENATES

extern int fball_cx1 , fball_cx2 ; // INITIALIZING FIREBALL X,Y COORDENATES
extern int fball_cy1 , fball_cy2 ; // INITIALIZING FIREBALL X,Y COORDENATES

extern char fball_flg1 , fball_flg2 ; // INITIALIZING FIREBALL X,Y COORDENATES

extern char fballx1 , fballx2 ;

extern int fbx1x , fbx2x ; // INITIALIZING FIREBALL X,Y COORDENATES
extern int fbx1y , fbx2y ; // INITIALIZING FIREBALL X,Y COORDENATES

extern int fballx_cx1 , fballx_cx2 ; // INITIALIZING FIREBALL X,Y COORDENATES
extern int fballx_cy1 , fballx_cy2 ; // INITIALIZING FIREBALL X,Y COORDENATES

extern char fballx_flg1 , fballx_flg2 ; // INITIALIZING FIREBALL FLAGS


extern char accel_flag , gfx_flag ;
extern char snd_flag , midi_flag ;

extern char wind_flag ;

extern char tnt2 ;

extern char open1[ 40 ] ;
extern char open2[ 40 ] ;
extern char open3[ 40 ] ;
extern char open4[ 40 ] ;
extern char open5[ 40 ] ;
extern char title[ 20 ] ;

//extern char max_nbf1, max_nbf2;
char inverted ;

#if GAME_DEBUG > 0
extern void __tron__( char *log_mess, char *n_file , int n_line );
#endif

extern char log_mess[ 80 ];
extern void __error__( char *log_mess, char *n_file , int n_line );

#endif /* GLOBAL_H */
#endif // MAIN_H
