#include <allegro.h>
#include <allegro/internal/aintern.h>
#include <stdio.h>
//#include <mem.h>
#include "loader.h"
#include <string.h>
/** \file loader.c
 * \brief Mugen SFF, FNT, SND Loader (source) by Lennart Steinke
 *
 * written by Lennart Steinke (http://www.steinke.net) 
 */

/****************************************************************************/
/*                                                                          */
/*               SFF ROUTINES                                               */
/*                                                                          */
/****************************************************************************/
int sff_memloadInt(unsigned char *data, int *ofs) {
  int a,b;
  // fprintf(stdout,"sff_memloadInt\n");
  a = data[*ofs];
  (*ofs)++;
  b = data[*ofs];
  (*ofs)++;
  return a + (b <<8);
}

RGB* sffLoadPaletteFromMemory(unsigned char *data) {
  RGB* pal = (RGB*) malloc(sizeof(RGB) * 256);
  // fprintf(stdout,"sffLoadPaletteFromMemory\n");
  int  a, ofs;
  ofs = 0;
  for (a=0; a < 256; ++a) {
    pal[a].r = data[ofs++] / 4;
    pal[a].g = data[ofs++] / 4;
    pal[a].b = data[ofs++] / 4;
  }
  return pal;
}

BITMAP* sffLoadPcxFromMemory(char* data) {
  BITMAP *bmp = NULL;
  char * message;
 
  // fprintf(stdout,"sffLoadPcxFrmMemory\n");
  /* skip the first 3 bytes */
  int     ofs = 3;
  char    planes = data[ofs++];
  int     width  = -sff_memloadInt(data, &ofs);
  int     height = -sff_memloadInt(data, &ofs);
  int     bpp  = 0;
  int     bytesPerLine = 0;
  int     x,y;
  int     value;
  int     count;
     message = (char*)calloc(255,sizeof(char));
  width += sff_memloadInt(data, &ofs) +1;
  height+= sff_memloadInt(data, &ofs) +1;
    
  /* skip 4 bytes (dpi) */
  ofs += 4;
    
  /* skip 16 color palette */
  ofs += 48;
    
  /* padding */
  ofs++;
    
  bpp  = data[ofs++] *8;
    
  if (bpp != 8) { // || bpp != 24) {
    //// fprintf(stdout,"not a good depth pcx\n");
    return NULL;
  }
    
  bytesPerLine = sff_memloadInt(data, &ofs);
  // fprintf(stdout,"After bytesPerLine\n");
  /* image data starts at ofs 128*/
  ofs = 128;
  // sprintf(message,"bpp=%i width=%i height=%i\n",bpp,width,height);
  // fprintf(stdout,message);
  // bmp = create_bitmap_ex(bpp, width, height);
  bmp = create_bitmap_ex(8, width, height);
  // fprintf(stdout,"After create_bitmap_ex\n");
  for (y=0; y < height; ++y) {
    x = 0;	
    while (x < bytesPerLine) {
      // sprintf(message,"y=%i x=%i\n",y,x);
      // // fprintf(stdout,message);
      value = data[ofs++];
            
      /* check if upper 2 bit are set */
      if ((value & 0xc0) == 0xc0) {
	/* bits are set, that means the
	   lower 6 bit contain the repeat count,
	   and the color is stored in the next byte
	*/
	// // fprintf(stdout,"bit are set\n");
	count = value & 0x3f;
	value = data[ofs++];
      } else {
	/* value contains the color already */
	// // fprintf(stdout,"bit are not set\n");
	count = 1;
      }
      if (bpp == 8) {
	while (count > 0) {
	  if (x < bmp->w) {
	    bmp->line[y][x] = value;                        
	  }
	  ++x;
	  --count;
	}
      }
    }
  }
 // fprintf(stdout,"after filling bmp\n"); 
    
  free(message);
  return bmp;
}

SFF_LOAD_RET_TYPE sffLoadFromMemory(void *memory) {
  char*      data       = (char*) memory;
  SFFHeader* header     = (SFFHeader*) memory;
  SFFSubFileHeader *sub = NULL;
  int        index      = 0;
  SFFEntry*  first      = NULL;
  SFFEntry*  cur        = NULL;
  char * message;
  SFFEntry**  sprArray   = NULL;
  // fprintf(stdout,"sffLoadFromMemory\n");
  sprArray = calloc(header->countImages, sizeof(SFFEntry*));
    
  message = (char*)calloc(255,sizeof(char));
  
  sub = (SFFSubFileHeader*) &data[header->offsetFirstSubFile];
  while (sub != NULL) {        
    if (first == NULL) {
      first = (SFFEntry*) calloc(1, sizeof(SFFEntry));
      cur   = first;
    } else {
      cur->next = (SFFEntry*) calloc(1, sizeof(SFFEntry));
      cur = cur->next;
    }
    cur->x = sub->x;
    cur->y = sub->y;
    cur->group = sub->group;
    cur->curIndex = sub->curIndex;
    cur->prevIndex = sub->prevIndex;        
        
    if (sub->sizeOfData == 0) {
      // fprintf(stdout,"Linked image\n");
      // This is just a link to another image
      cur->isLinkedImage = TRUE;            
      cur->image = sprArray[sub->prevIndex]->image;
    } else {            
      // // fprintf(stdout,"Not Linked image\n");
      cur->isLinkedImage = FALSE;
      cur->image = sffLoadPcxFromMemory(sub->pcxData);
      memcpy(cur->comment, sub->comment, 13);
      if (!sub->reusePalette) {
	/* Tha palette is stored in the last 768 bytes
	   of the pcx data
	*/
	// // fprintf(stdout,"Owned palette\n");
	cur->pal = sffLoadPaletteFromMemory((unsigned char*) &(sub->pcxData[sub->sizeOfData - 768]) );
      }else{
	// fprintf(stdout,"Shared palette\n");
	cur->pal = sprArray[index-1]->pal;
	// fprintf(stdout,"after shared pal\n");
      }
    }
    sprArray[index] = cur;
        
    /*
      According to the docs, the last subfile is indicated by a 0.
      During tests it became obvious that this is not the case.
      Thus I'm checking both for 0 and check if the index is 
      smaller than the number of sprites in the file.
    */
    ++index;
    sprintf(message,"Pix %i\n",index);
    // fprintf(stdout,message);
    
    if (sub->nextSubFile != 0 && index < header->countImages) {
      sub = (SFFSubFileHeader*) &data[sub->nextSubFile];
    } else {
      sub = NULL;
    }                
  }
    
  /* NOTE: You might want to return the sprArray instead;
     if so, don't free it here :)
  */
  free(sprArray);
  free(message);  
  return first;
}

SFF_LOAD_RET_TYPE sffLoad(const char* filename) {
  long size  = file_size(filename);
  long toGo  = size;
  long start = 0;
  long count = 0;
  FILE *f    = NULL;
  char *data = NULL;
  SFF_LOAD_RET_TYPE ret = NULL;
    
  if (size > 0) {
    f = fopen(filename, "rb");
    data = malloc(size);
    while (toGo > 0 && !feof(f)) {
      count  = fread(&(data[start]),1,toGo, f);
      if (count == 0) {
	exit(0);
      }
                
      toGo  -= count;
      start += count;
    }
    fclose(f);        
    ret =  sffLoadFromMemory(data);
    free(data);
  }
  return ret;
}

void sffFree(SFF_LOAD_RET_TYPE a_sff){
  SFFEntry * cur = NULL;
  cur = a_sff;
  while (cur->next){
    cur = cur->next;
    if (cur->image!=NULL){
      destroy_bitmap(cur->image);
    }
  }
  return;
}

/****************************************************************************/
/*                                                                          */
/*               FNT ROUTINES                                               */
/*                                                                          */
/****************************************************************************/
static int fntReadLine(char* txt, int toGo, char *buf) {
  int count = 0;
  int comment = 0;

  /* skip all eol chars at the start */
  while (*txt < 32 && toGo > 0) {
    count++;
    txt++;
    toGo--;
  }
    
  /* copy the chars */
  while (*txt >= 32 && toGo > 0) {        
    if (*txt == ';') {
      /* comment till eol */
      comment = 1;
    }
    if (!comment) {
      *buf = *txt;        
      buf++;
    }
    count++;
    txt++;        
    toGo--;
  }
  /* terminate the line */
  *buf = '\0';
    
  /* skip all eol chars at the end */
  while (*txt < 32 && toGo > 0) {
    count++;
    txt++;
    toGo--;
  }
    
  return count;
}

static int fntSkipSpaceAndComma(const char *lineBuf, int p) {
  /* search the comma */
  while (lineBuf[p] && lineBuf[p] != ',') {
    ++p;
  }
  if (!lineBuf[p]) {
    return p;
  }
  /* skip the comma */
  ++p;
  /* skip spaces */
  while (lineBuf[p] && lineBuf[p] == ' ') {
    ++p;
  }
  return p;
}

FNTInfo* fntLoadFromMem(char *data) {
  char *defNames[]= {
    "Size", "Spacing", "Colors", "Offset", "Type",
    NULL
  };
  int defLen[5] = { 0, 0, 0, 0, 0 };
  int pcxOfs = *((int*) &data[16]);
  int pcxLen = *((int*) &data[20]);
  int txtOfs = *((int*) &data[24]);
  int txtLen = *((int*) &data[28]);
  int sizeW  = 0;
  int sizeH = 0;
  int spacingX = 0;
  int spacingY = 0;
  int offsetX = 0;
  int offsetY = 0;
  int fixedFont = 1;
  int colsUsed = 1;
    
  int map = 0;
    
  int curChar = 0;    
  int xPos[255];
  int width[255];
  int first = 255;
  int last  = 0;
  int curGlyph = 0;
  int autoOffset  = 0;
    
  RGB    *pal = NULL;
  BITMAP *pcx = NULL;    
  char lineBuff[255];
    
  FONT_COLOR_DATA *colorFont = NULL;
  FONT* theFont = NULL;
  FNTInfo *fontInfo = NULL;
  int conv = _color_conv;
  int count;
    
  set_color_conversion(COLORCONV_NONE);
  pcx = sffLoadPcxFromMemory(&data[pcxOfs]);

  /* the palette is the last 768 bytes of the pcx */
  pal = sffLoadPaletteFromMemory((unsigned char*) &(data[pcxOfs + pcxLen - 768]) );
  set_color_conversion(conv);
    
    
  for (curChar=0; curChar < 255; ++curChar) {
    xPos[curChar] = -1;
  }
    
  count = fntReadLine(&(data[txtOfs]), txtLen, lineBuff);
  while (count > 0) {        
    if (lineBuff[0] == '[') {
      if (stricmp(lineBuff, "[map]") == 0) {
	map = 1;
      }
    } else if (!map) {
      int a = 0;
      while (defNames[a]) {
	if (defLen[a] == 0) {
	  defLen[a] = strlen(defNames[a]);
	}
	if (strncmp(lineBuff, defNames[a], defLen[a]) == 0) {
	  /* ignore spaces and the '=' */
	  int p = defLen[a];
	  while (lineBuff[p] == ' ' || lineBuff[p] == '=') {
	    ++p;
	  }
	  switch (a) {
	    /* Size: Width and height separated by comma */
	  case 0:
	    sizeW = atoi(&lineBuff[p]);
	    p = fntSkipSpaceAndComma(lineBuff, p);                            
	    sizeH = atoi(&lineBuff[p]);
	    break;
                        
	    /* Spacing: X and Y separated by comma */
	  case 1:
	    spacingX = atoi(&lineBuff[p]);
	    p = fntSkipSpaceAndComma(lineBuff, p);                            
	    spacingY = atoi(&lineBuff[p]);
	    break;
                        
	    /* Colors: Number of colors used in this font */
	  case 2:
	    colsUsed = atoi(&lineBuff[p]);
	    break;
                        
	    /* Offset: Where the font data starts in the pcx
	       X and Y separated by comma 
	    */
	  case 3:
	    offsetX = atoi(&lineBuff[p]);
	    p = fntSkipSpaceAndComma(lineBuff, p);                            
	    offsetY = atoi(&lineBuff[p]);
	    break;
                        
	    /* type of font: if the value starts with a 'v' it's a variable font */
	  case 4:
	    fixedFont = !(lineBuff[p] == 'V' || lineBuff[p] == 'v');  
	    break;
	  }
	}
	++a;
      }
    } else {            
      char *txt = NULL;
      curChar = 0;
      /* map */
      /* Each line consists of the char followed by and optional offset and optional width] */
      if (lineBuff[0] == '0' && (lineBuff[1] == 'x' || lineBuff[1] == 'X')) {
	/* character is listed as hex value */
	curChar = strtol(lineBuff, &txt, 0);
      } else {
	curChar = lineBuff[0];
	txt = &lineBuff[1];
      }
      /* skip space */
      while (*txt && *txt == ' ') {
	txt++;
      }
      if (*txt) {
	xPos[curChar] = strtol(txt, &txt, 0);
      } else {
	xPos[curChar] = autoOffset;
      }
      if (fixedFont) {
	width[curChar] = sizeW;
      } else {
	/* skip space */
	while (*txt && *txt == ' ') {
	  txt++;
	}
	width[curChar] = atoi(txt);
      }
      autoOffset += width[curChar];
            
      /* check first and last, so we can later use it
	 to determine the range of the font
      */
      if (curChar < first) {
	first= curChar;
      }
      if (curChar > last) {
	last = curChar;
      }            
    }
        
        
    txtOfs += count;
    txtLen  -= count;
        
    count = fntReadLine(&(data[txtOfs]), txtLen, lineBuff);
  }
    
  /* creation of the actual font */    
  colorFont = (FONT_COLOR_DATA*) calloc(1, sizeof(FONT_COLOR_DATA));
    
  /* if there's no space, we need to add it. */
  if (first > 32) {
    first = 32;        
  }
  colorFont->begin = first;
  colorFont->end   = last+1;    
  colorFont->bitmaps = calloc(last - first +1, sizeof(BITMAP*));
    
  for (curChar = colorFont->begin; curChar < colorFont->end; ++curChar) {
        
    curGlyph = curChar - colorFont->begin;
        
    /* char not in font ? */
    if (xPos[curChar] == -1) {            
      colorFont->bitmaps[curGlyph] = create_bitmap_ex(8, sizeW + spacingX, sizeH + spacingY);
      clear_to_color(colorFont->bitmaps[curGlyph], 0);            
    } else {
      colorFont->bitmaps[curGlyph] = create_bitmap_ex(8, width[curChar] + spacingX, sizeH + spacingY);
      clear_to_color(colorFont->bitmaps[curGlyph], 0);            
      blit(pcx, colorFont->bitmaps[curGlyph], xPos[curChar] + offsetX, offsetY, 0, 0, width[curChar], sizeH);
    }
        
  }
  theFont = (FONT*) calloc(1, sizeof(FONT));
  theFont->data = colorFont;
  theFont->height = sizeH + spacingY;
  theFont->vtable = font_vtable_color;
    
  destroy_bitmap(pcx);
    
  fontInfo = (FNTInfo *)calloc(1, sizeof(FNTInfo));
  fontInfo->font = theFont;
  fontInfo->colors = colsUsed;
  fontInfo->pal = pal;
    
  return fontInfo;
}


FNTInfo* fntLoadFont(const char* filename) {
  long size  = file_size(filename);
  long toGo  = size;
  long start = 0;
  long count = 0;
  FILE *f    = NULL;
  char *data = NULL;
  FNTInfo *info = NULL;
    
  if (size > 0) {
    f = fopen(filename, "rb");
    data = malloc(size);
    while (toGo > 0 && !feof(f)) {
      count  = fread(&(data[start]),1,toGo, f);
      if (count == 0) {
	exit(0);
      }
                
      toGo  -= count;
      start += count;
    }
    fclose(f);     
    
    info = fntLoadFromMem(data);
    free(data);
  }
  return info;
}


PALETTE* fntGetPaletteForBank(FNTInfo* info, int bank) {
  RGB* pal = (RGB*) malloc(sizeof(RGB)*256);
  int start = bank * info->colors;
  int a; 
  if ((bank<0)||(bank>info->colors))
    return &default_palette;
   
  memcpy(pal, info->pal, sizeof(RGB)*256);
  for (a=0; a < info->colors; ++a, ++start) {
    pal[255-a].r = info->pal[255-start].r;
    pal[255-a].g = info->pal[255-start].g;
    pal[255-a].b = info->pal[255-start].b;
  }
  return (PALETTE*) pal;
}

/****************************************************************************/
/*                                                                          */
/*               SND ROUTINES                                               */
/*                                                                          */
/****************************************************************************/

SAMPLE *sndLoadWAV(const char *filename, unsigned int offset)
{
  PACKFILE *f;
  char buffer[25];
  int i;
  int length, len;
  int freq = 22050;
  int bits = 8;
  int channels = 1;
  signed short s;
  SAMPLE *spl = NULL;

  f = pack_fopen(filename, F_READ);
  if (!f)
    return NULL;

  pack_fseek(f, offset);
  pack_fread(buffer, 12, f);          /* check RIFF header */
  if (memcmp(buffer, "RIFF", 4) || memcmp(buffer+8, "WAVE", 4))
    goto getout;

  while (!pack_feof(f)) {
    if (pack_fread(buffer, 4, f) != 4)
      break;

    length = pack_igetl(f);          /* read chunk length */

    if (memcmp(buffer, "fmt ", 4) == 0) {
      i = pack_igetw(f);            /* should be 1 for PCM data */
      length -= 2;
      if (i != 1) 
	goto getout;

      channels = pack_igetw(f);     /* mono or stereo data */
      length -= 2;
      if ((channels != 1) && (channels != 2))
	goto getout;

      freq = pack_igetl(f);         /* sample frequency */
      length -= 4;

      pack_igetl(f);                /* skip six bytes */
      pack_igetw(f);
      length -= 6;

      bits = pack_igetw(f);         /* 8 or 16 bit data? */
      length -= 2;
      if ((bits != 8) && (bits != 16))
	goto getout;
    }
    else if (memcmp(buffer, "data", 4) == 0) {
      len = length / channels;

      if (bits == 16)
	len /= 2;

      spl = create_sample(bits, ((channels == 2) ? TRUE : FALSE), freq, len);

      if (spl) { 
	if (bits == 8) {
	  pack_fread(spl->data, length, f);
	}
	else {
	  for (i=0; i<len*channels; i++) {
	    s = pack_igetw(f);
	    ((signed short *)spl->data)[i] = s^0x8000;
	  }
	}

	length = 0;

	if (*allegro_errno) {
	  destroy_sample(spl);
	  spl = NULL;
	}
      }
    }

    while (length > 0) {             /* skip the remainder of the chunk */
      if (pack_getc(f) == EOF)
	break;

      length--;
    }
  }

 getout:
  pack_fclose(f);
  return spl;
}

SNDCollection* sndLoadSound(const char* filename) {
  FILE  *f          = NULL;
  char  magic[12]   = "ElecbyteSnd";
  int   version     = 0;
  int   countSounds = 0;
  int   group       = 0;
  int   sample      = 0;
  int   size        = 0;
  int   sndsRead    = 0;
  int   index       = 0;
    
  int *groups;
  int *sounds;
  int *offsets;
    
  unsigned int firstOffset = 0;    
  unsigned int offset      = 0;    
  SNDCollection *snd = calloc(1, sizeof(SNDCollection));
    
  if (!snd) {
    return NULL;
  }
    
  f = fopen(filename, "rb");
  if (f == NULL) {
    free(snd);
    return NULL;
  }
  fread(magic, 1, 12, f);
  magic[11] = '\0';
  if (strcmp(magic,  "ElecbyteSnd") != 0) {
    free(snd);
    return NULL;
  }
    
  fread(&version    , 4, 1, f);
  fread(&countSounds, 4, 1, f);
  fread(&firstOffset, 4, 1, f);
    
  sounds  = calloc(countSounds, sizeof(int));
  groups  = calloc(countSounds, sizeof(int));
  offsets = calloc(countSounds, sizeof(int));
    
    
  offset = firstOffset;    
  while (offset > 0 && sndsRead < countSounds) {
    fseek(f, offset, SEEK_SET);
    offsets[sndsRead] = offset+16;
    fread(&offset, 4, 1, f);
    fread(&size  , 4, 1, f);
    fread(&group , 4, 1, f);
    fread(&sample, 4, 1, f);
        
    groups[sndsRead]  = group;
    sounds[sndsRead]  = sample;
        
    snd->maxGroupIndex  = MAX(snd->maxGroupIndex, group);
    snd->maxSoundIndex  = MAX(snd->maxSoundIndex, group);
    ++sndsRead;
  }
    
  snd->maxGroupIndex++;
  snd->maxSoundIndex++;
    
  snd->sounds = calloc( snd->maxGroupIndex * snd->maxSoundIndex, sizeof(SAMPLE*));
  fclose(f);
    
  sndsRead = 0;
  for (sndsRead = 0; sndsRead < countSounds; ++sndsRead) {
    index = groups[sndsRead] * snd->maxSoundIndex + sounds[sndsRead];
    snd->sounds[index] = sndLoadWAV(filename, offsets[sndsRead]);        
    //printf("loading %i.%i at %i (%u)= %s\n", groups[sndsRead], sounds[sndsRead], group * snd->maxSoundIndex + sample, offsets[sndsRead], snd->sounds[index] == NULL ? "NULL" : "OK");
  }
    
  free(offsets);
  free(groups);
  free(sounds);
    
  return snd;
}

int sndPlay(SNDCollection* snd, int group, int sound, int volume, int pan) {
  int index = 0;
  if (group < snd->maxGroupIndex && sound < snd->maxSoundIndex) {
    index = group *snd->maxSoundIndex + sound;
    if (snd->sounds[index] != NULL) {
      return play_sample(snd->sounds[index], volume, pan, 1000, 0);
    }
  } 
  return -1;
}

void sndStop(SNDCollection* snd, int group, int sound) {
  int index = 0;
  if (group < snd->maxGroupIndex && sound < snd->maxSoundIndex) {
    index = group *snd->maxSoundIndex + sound;
    if (snd->sounds[index] != NULL) {
      stop_sample(snd->sounds[index]);
    }
  }
}

SNDCollection* sndFreeSound(SNDCollection* snd) {
  int size = 0;
  int a    = 0;
    
  if (snd != NULL) {
    size = (snd->maxGroupIndex+1) * (snd->maxSoundIndex+1);
    for (a=0; a < size; ++a) {
      if (snd->sounds[a] != NULL) {
	destroy_sample(snd->sounds[a]);
      }
    }
    free(snd);
  }
    
  return NULL;
}

/****************************************************************************/
/*                                                                          */
/*               PAL ROUTINES                                               */
/*                                                                          */
/****************************************************************************/
RGB* load_act_pal(const char* filename) {
  size_t size;
  FILE*  f;
  RGB*   pal = NULL;
  unsigned char*  buf = NULL;
  int int_buf;
  size = file_size(filename);
  if (size == 768) {
    buf = malloc(size);
    if (!buf) {
      return NULL;
    }

    f = fopen(filename, "rb");
    if (fread(buf, size, 1, f)) {
      int pos;
      int a;
      pal = calloc(256, sizeof(RGB));
      if (pal) {
	for (a=255,pos = 0; a>= 0; --a, pos+=3){
	  int_buf = (int)buf[pos];
	  int_buf = (int_buf*63)/255;
	  pal[a].r = int_buf; 
	  int_buf = (int)buf[pos+1];
	  int_buf = (int_buf*63)/255;
	  pal[a].g = int_buf;
	  int_buf = (int)buf[pos+2];
	  int_buf = (int_buf*63)/255;
	  pal[a].b = int_buf;
	}
      }
    }
    fclose(f);
    free(buf);
  }
  return pal;
}
