#ifndef __FONT_H__
#define __FONT_H__

#include "Defs.h"
#include "Point.h"

#include "SDL/include/SDL.h"

#define MAX_CHARACTERS 128

class Font
{
public:

    Font(SDL_Texture* atlas, int count, int rows, int cols, iPoint textSize, const char* lookTable);

    ~Font();

    void SetFirstCharacter(int value);

    SDL_Rect GetCharRec(int value);

	
    char table[MAX_CHARACTERS];

    SDL_Texture* texture;

    uint totalLength;
    uint rows, columns;
    uint charW, charH;



    int baseSize;
    int charsCount;
    SDL_Rect charsRecs[128];

    int firstChar;
};

#endif //__FONT_H__