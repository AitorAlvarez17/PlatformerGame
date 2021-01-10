#include "Font.h"
#include "SString.h"

Font::Font(SDL_Texture* atlas, int count, int rown, int cols, iPoint texSize, const char* lookTable)
{
    // NOTE: To load a bitmap font atlas we must adjust to some constraints:
    // - Characters are ordered: Start at first char value and consecutive values follow
    // - All characters width is the same
    // - All characters have the same padding surrounding them
    // - A maximum of 128 characters are supported


    //count es igual al numero maximo de characters que hay en la look up table
    texture = atlas;
    strcpy_s(table, lookTable);
    

    totalLength = count;
    rows = rown;
    columns = cols;

    charW = texSize.x/columns;
    charH = texSize.y/rows;


    charsCount = count;
    firstChar = 32;         // Default to space
    //baseSize = ((atlas->width / rows) - 2 * padding);

    // TODO: Define the multiple SDL_Recs, one for every character
    for (int i = 0; i < 128; i++)
    {
        //charsRecs[i] = SDL_Rect()
    }
}

Font::~Font()
{
}

void Font::SetFirstCharacter(int value)
{
    firstChar = value;
}

SDL_Rect Font::GetCharRec(int value)
{
    SDL_Rect rec = { 0 };

    // TODO: Get character rectangle corresponding to introduced value

    return rec;
}
