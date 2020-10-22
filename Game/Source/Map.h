#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"

#include "PugiXml\src\pugixml.hpp"

// L03: TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
struct TileSet {
    //int firstGid;
    //const char* name;
    //int tileWidth;
    //int tileHeight;
    //int spacing;
    //int margin;
    //SDL_Texture* image;
    //const char* source;
    //int imageWidth;
    //int imageHeight;
    
        SString	name;
        int	firstgid;
        int margin;
        int	spacing;
        int	tile_width;
        int	tile_height;

        SDL_Texture* texture;
        int	texWidth;
        int	texHeight;
        int	numTilesWidth;
        int	numTilesHeight;
        int	offsetX;
        int	offsetY;

        
    
};

struct MapLayer
{
    SString	name;
    int width;
    int height;
    uint* data;

    MapLayer() : data(NULL)
    {}

    ~MapLayer()
    {
        RELEASE(data);
    }

 
};

enum MapTypes
{
    MAPTYPE_UNKNOWN = 0,
    MAPTYPE_ORTHOGONAL,
    MAPTYPE_ISOMETRIC,
    MAPTYPE_STAGGERED
};


// L03: TODO 1: Create a struct needed to hold the information to Map node
struct MapData {
 /*   const char* orientation;
    const char* renderorder;
    int width;
    int height;
    int tileWidth;
    int tileheight;
    

    List<TileSet*> tilesets;*/

   
    int width;
    int	height;
    int	tileWidth;
    int	tileHeight;
    int nextObjectId;
    int nextLayerId;
    SDL_Color backgroundColor;
    MapTypes type;
    List<TileSet*> tilesets;

        
  
   
};

class Map : public Module
{
public:

    Map();

    // Destructor
    virtual ~Map();

    // Called before render is available
    bool Awake(pugi::xml_node& conf);

    // Called each loop iteration
    void Draw();

    // Called before quitting
    bool CleanUp();

    // Load new map
    bool Load(const char* path);


    // L03: TODO 1: Add your struct for map info as public for now
    MapData data;


private:

    bool LoadTileset(pugi::xml_node& tilesetNode, TileSet* ts);
    bool LoadTilesetImage(pugi::xml_node& tilesetNode, TileSet* ts);
    bool LoadMap();


    TileSet tSet;
    pugi::xml_document mapFile;
    pugi::xml_node mapNode;
    pugi::xml_node tileNode;
    pugi::xml_node imageNode;
    
    
    

    SString folder;
    bool mapLoaded = false;
};

#endif // __MAP_H__