#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"


#include "Log.h"

#include "PugiXml\src\pugixml.hpp"

// L03: TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!

struct Tile {

    int id;
    int terrain[4];

};

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
    int	tileWidth;
    int	tileHeight;

    SDL_Texture* texture;
    int	texWidth;
    int	texHeight;
    int	numTilesWidth;
    int	numTilesHeight;
    int	offsetX;
    int	offsetY;
    Tile tId[45];

    SDL_Rect GetTileRect(int id) const;


};

struct Properties
{

    struct Property
    {
        //...
        SString name;
        SString type;
        int value;
    };


    ~Properties()
    {
        //...
    }
    List<Property*> list;

    // L06: TODO 7: Method to ask for the value of a custom property
    int GetProperty(const char* name, int defaultValue = 0) const;
       
};

struct MapLayer
{
    SString	name;
    int width;
    int height;
    uint* data;

    Properties prop;

    int tileNumber;
    int gids[13000];

    MapLayer() : data(NULL) {}

    ~MapLayer()
    {
        RELEASE(data);
    }

    // L04: TODO 6: Short function to get the value of x,y
    uint Get(int x, int y) const
    {

        uint result = data[(y * width) + x];
        return result;
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
    List<TileSet*> tileSets;

    List<MapLayer*> layers;

    int maxLayers = 0;
    int maxTilesets = 0;




};

class Map : public Module
{
public:

    Map(bool startEnabled);

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

    bool StoreId(pugi::xml_node& node, MapLayer* layer, int index);

    iPoint MapToWorld(int x, int y) const;
    void LoadColliders();


    // L03: TODO 1: Add your struct for map info as public for now
    MapData data;


private:
    bool LoadMap();
    bool LoadTileSet(pugi::xml_node& tilesetNode, TileSet* tileSet);
    bool LoadTileSetImage(pugi::xml_node& tilesetNode, TileSet* tileSet);
    bool LoadTileSetDetails(pugi::xml_node& tilesetNode, TileSet* set);
    bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
    
    

    TileSet tSet;
    pugi::xml_document mapFile;
    pugi::xml_node mapNode;
    pugi::xml_node tileNode;
    pugi::xml_node imageNode;

    bool LoadProperties(pugi::xml_node& node, Properties& properties);

    TileSet* GetTilesetFromTileId(int id) const;


    SString folder;
    bool mapLoaded = false;
};

#endif // __MAP_H__