
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>

Map::Map() : Module(), mapLoaded(false)
{
    name.create("map");

}

// Destructor
Map::~Map()
{}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    folder.create(config.child("folder").child_value());
    /*Load("hello2.xml");*/

    return ret;
}

bool Map::LoadMap()
{

    bool ret = true;
    pugi::xml_node map = mapFile.child("map");

    if (map == NULL)
    {
        LOG("Error parsing map xml file: Cannot find 'map' tag.");
        ret = false;
    }
    else
    {
        // L03: TODO: Load map general properties

        data.width = map.attribute("width").as_int(0);
        data.height = map.attribute("height").as_int(0);
        data.tileWidth = map.attribute("tilewidth").as_int(0);
        data.tileHeight = map.attribute("tileheight").as_int(0);
        data.nextObjectId = map.attribute("nextObjectId").as_int(0);
        data.nextLayerId = map.attribute("nextLayerId").as_int(0);


        SString orientation = map.attribute("orientation").as_string();
        if (orientation == "orthogonal") {
            data.type = MAPTYPE_ORTHOGONAL;

        }
        else if (orientation == "isometric") {
            data.type = MAPTYPE_ISOMETRIC;


        }
        else if (orientation == "staggered") {
            data.type = MAPTYPE_STAGGERED;
        }
        else {
            data.type = MAPTYPE_UNKNOWN;
        }
        

        
    }

    return true;
}


void Map::Draw()
{

    

    if(mapLoaded == false) return;

    // L03: TODO 6: Iterate all tilesets and draw all their 
    // images in 0,0 (you should have only one tileset for now)

    app->render->DrawTexture(data.tilesets[0]->texture, 0, 0);

}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // L03: TODO 2: Make sure you clean up any memory allocated from tilesets/map


    mapFile.reset();

    return true;
}



// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

    if(ret == true)
    {
        // L03: TODO 3: Create and call a private function to load and fill all your map data
        ret = LoadMap();
    }
 

    // L03: TODO 4: Create and call a private function to load a tileset
    // remember to support more any number of tilesets!
    pugi::xml_node tileset;

    for (tileset = mapFile.child("map").child("tileset"); tileset&& ret; tileset = tileset.next_sibling("tileset")) {
      
        TileSet* ts = new TileSet();

       
        if (ret == true) ret = LoadTileset(tileset, ts);

        if (ret == true) ret = LoadTilesetImage(tileset, ts);

        data.tilesets.add(ts);


    }
   

    if(ret == true)
    {
        // L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything
        
        LOG("Successfully parsed map XML file : %s", filename);
        LOG("width %d", data.width, " height %d", data.height);
        LOG("tile_width %d", data.tileWidth, " tile_height", "%d", data.tileHeight);
        LOG("Tileset----");
        /*for (int i = 1; data.tilesets[i] != nullptr; i++) {

            LOG("name : %s : %i", data.tilesets[i]->name,data.tilesets[i]->firstgid);
            LOG("tile_width %d", data.tilesets[i]->tile_width, " tile_height %d", data.tilesets[i]->tile_height);
            LOG("spacing : %d", data.tilesets[i]->spacing, " margin :%d", data.tilesets[i]->margin);
        }*/

        ListItem<TileSet*>* listPtr = data.tilesets.start;
        while (listPtr == nullptr) {
            LOG("name : %s : %i", listPtr->data->name.GetString(), listPtr->data->firstgid);
            LOG("tile_width %d", listPtr->data->tile_width, " tile_height %d", listPtr->data->tile_height);
            LOG("spacing : %d", listPtr->data->spacing, " margin :%d", listPtr->data->margin);
            listPtr = listPtr->next;
        }



    }

    mapLoaded = ret;

    return ret;
}

bool Map::LoadTileset(pugi::xml_node& tilesetNode, TileSet* ts)
{

    bool ret = true;
    SString tmp("%s%s", folder.GetString(), tilesetNode);

    //no sense
    if ( tilesetNode == NULL)
    {
        LOG("Could not load tileset %s. pugi error: %s", tilesetNode, "no tileset");
        ret = false;
    }

    if (ret == true) {

        ts->firstgid = tilesetNode.attribute("firstgid").as_int();
        ts->name = tilesetNode.attribute("name").as_string();
        ts->tile_width = tilesetNode.attribute("tilewidth").as_int();
        ts->tile_height = tilesetNode.attribute("tileheight").as_int();
        ts->spacing = tilesetNode.attribute("spacing").as_int();
        ts->margin = tilesetNode.attribute("margin").as_int();
    }

    return ret;
}

bool Map::LoadTilesetImage(pugi::xml_node& tilesetNode, TileSet* ts)
{
    bool ret = true;
  /*  SString tmp("%s%s", folder.GetString(), tilesetNode);*/
    pugi::xml_node imageNode = tilesetNode.child("image");


    if (imageNode == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", tilesetNode, "no image");
        ret = false;
    }

    if (ret == true) {

        SString path("%s%s", folder.GetString(), imageNode.attribute("source").as_string());

        ts->texture = app->tex->Load(path.GetString());
        ts->texWidth = imageNode.attribute("width").as_int();
        ts->texHeight = imageNode.attribute("height").as_int();



  
    }
   
   
    return ret;
}




