#ifndef SFF_LOADER
#define SFF_LOADER

#include <allegro.h>
/** \file loader.h
 * \brief Mugen SFF, FNT, SND Loader (Header) by Lennart Steinke 
 *
 * written by Lennart Steinke (http://www.steinke.net) 
 */
typedef struct {
    char magic[12];
    char version[4];
    int  countGroups;
    int  countImages;
    int  offsetFirstSubFile;
    int  sizeOfSubfileHeader;
    char palType;
    char padding[3];
    char comment[476];
} SFFHeader;

typedef struct {
    int   nextSubFile;
    int   sizeOfData;
    short x;
    short y;
    short group;
    short curIndex;
    short prevIndex;
    char  reusePalette;
    char  comment[13];   
    char  pcxData[1];
} SFFSubFileHeader;

typedef struct SFFEntryStruct {
    short   x, y, group, curIndex, prevIndex;
    char    isLinkedImage;
    RGB*    pal;
    BITMAP* image;
    char    comment[13];
    
    struct SFFEntryStruct *next;
} SFFEntry;

typedef struct {
    FONT* font;
    RGB*  pal;
    int   colors;
} FNTInfo;

typedef struct {
    SAMPLE **sounds;
    int maxGroupIndex;
    int maxSoundIndex;
} SNDCollection;


#define SFF_LOAD_RET_TYPE SFFEntry*

SFF_LOAD_RET_TYPE sffLoad(const char* filename);
SFF_LOAD_RET_TYPE sffLoadFromMemory(void *memory);
void sffFree(SFF_LOAD_RET_TYPE a_sff);

FNTInfo* fntLoadFont(const char* filename);
PALETTE* fntGetPaletteForBank(FNTInfo* info, int bank);

SNDCollection* sndLoadSound(const char* filename);
int sndPlay(SNDCollection* snd, int group, int sound, int volume, int pan);
void sndStop(SNDCollection* snd, int group, int sound);
SNDCollection* sndFreeSound(SNDCollection* snd);

RGB* load_act_pal(const char* filename);
#endif

