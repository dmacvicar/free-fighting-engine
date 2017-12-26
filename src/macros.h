/** \file macros.h
 * \brief Macros used in the whole prog
 */

#ifndef MACROS_H
#define MACROS_H

#include "config.h"
#define TITLE "KOF 91 v1.49"


#define fill_sprite(a) rectfill(a, 0, 0, a->w, a->h, makecol(255,0,255));

#if GAME_DEBUG > 0
#define TRONSTART(a) __tronstart__( a, __FILE__, __LINE__ )
#define TRON(a) __tron__( a, __FILE__, __LINE__ )
#endif


#if GAME_DEBUG == 0
#define TRONSTART(a) /* a */
#define TRON(a)  /* a */
#endif

#define ERROR(a) __error__( a, __FILE__, __LINE__ )

#if GAME_DEBUG > 0
#define load_sprite(a,b) __load_sprite__( a, b, __FILE__, __LINE__ )
#define xload_pcx(a,b) __xload_pcx__( a, b, __FILE__, __LINE__ )
#define xload_sample(a) __xload_sample__( a, __FILE__, __LINE__ )
#define xload_midi(a) __xload_midi__( a, __FILE__, __LINE__ )
#else
#define load_sprite(a,b) __load_sprite__( a, b )
#define xload_pcx(a,b) __xload_pcx__( a, b )
#define xload_sample(a) __xload_sample__( a )
#define xload_midi(a) __xload_midi__( a )
#endif

#endif //MACROS_H
