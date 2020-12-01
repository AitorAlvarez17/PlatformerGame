#include "App.h"
#include "Render.h"
#include "Collisions.h"
#include "Textures.h"
#include "Map.h"

#include "Defs.h"


#include <math.h>

Map::Map(bool startEnabled) : Module(startEnabled), mapLoaded(false)
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
        if (orientation == "orthogonal")
        {
            data.type = MAPTYPE_ORTHOGONAL;

        }
        else if (orientation == "isometric")
        {
            data.type = MAPTYPE_ISOMETRIC;


        }
        else if (orientation == "staggered")
        {
            data.type = MAPTYPE_STAGGERED;
        }
        else
        {
            data.type = MAPTYPE_UNKNOWN;
        }



    }

    return true;
}


void Map::Draw()
{
    if (mapLoaded == false) return;

    ListItem<MapLayer*>* L = data.layers.start;
    ListItem<TileSet*>* T = data.tilesets.start;
    TileSet* tileSet = data.tilesets.start->data;
    while (L != nullptr)
    {
        MapLayer* layer = L->data;
        if (layer->prop.GetProperty("Draw", 1) == 0)
        {
            

            L = L->next;
            continue;
            

        }
       
        for (int y = 0; y < layer->height; y++)
        {
            for (int x = 0; x < layer->width; x++)
            {


                int u = layer->Get(x, y);
                iPoint pos = MapToWorld(x, y);
                tileSet = GetTilesetFromTileId(u);
                SDL_Rect n = tileSet->GetTileRect(u);

                

                app->render->DrawTexture(tileSet->texture, pos.x, pos.y, &n);
                
            }
        }


        L = L->next;
    }
}




void Map::LoadColliders()
{
    if (mapLoaded == false) return;


    ListItem<MapLayer*>* L = data.layers.start;
    ListItem<TileSet*>* T = data.tilesets.start;
    TileSet* tileSet = data.tilesets.start->data;
    while (L != nullptr)
    {
        MapLayer* layer = L->data;
        if (layer->prop.GetProperty("Collisions", 1) == 0)
        {

            L = L->next;
            continue;


        }

        for (int y = 0; y < layer->height; y++)
        {
            for (int x = 0; x < layer->width; x++)
            {
               

                int u = layer->Get(x, y);
                iPoint pos = MapToWorld(x, y);
                SDL_Rect n = { pos.x, pos.y, data.tileWidth, data.tileHeight };
                SDL_Rect coin = { pos.x + 4, pos.y + 4, 24, 24 };

               
                if (u != 0)
                {
                    if (layer->prop.GetProperty("Collisions", 1) == 1)
                    {
                        app->collisions->AddCollider(n, Collider::Type::FLOOR, this);
                    }
                    if (layer->prop.GetProperty("Collisions", 1) == 2)
                    {
                        app->collisions->AddCollider(n, Collider::Type::DEATH, this);
                    }
                    if (layer->prop.GetProperty("Collisions", 1) == 3)
                    {
                        app->collisions->AddCollider(coin, Collider::Type::COIN, this);

                    }
                }
                
            }
        }
        L = L->next;
    }
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

// L04: DONE 8: Create a method that translates x,y coordinates from map positions to world positions
iPoint Map::MapToWorld(int x, int y) const
{
    iPoint ret;

    ret.x = x * data.tileWidth;
    ret.y = y * data.tileHeight;

    return ret;
}

TileSet* Map::GetTilesetFromTileId(int id) const
{
    ListItem<TileSet*>* item = data.tilesets.start;
    TileSet* set = item->data;

    while (id > set->firstgid)
    {
        /* LOG("%d", id);
         LOG("%d", set->firstgid);*/
        item = item->next;
        set = item->data;

        if (id <= set->firstgid)
        {
            if (id == set->firstgid)
            {
                /*LOG("%d", id);
                LOG("%d", set->firstgid);*/
                return set;
            }
            else if (id < set->firstgid)
            {
                /*LOG("%d", id);
                LOG("%d", set->firstgid);*/

                item = item->prev;
                set = item->data;
                return set;
            }


        }

    }






    //...

    return set;
}

// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int id) const
{
    SDL_Rect rect = { 0 };
    
    // L04: TODO 7: Get relative Tile rectangle
    iPoint p = { 0,this->margin };
    int targetId = firstgid;
    for (int i = 0; i < this->numTilesHeight; ++i)
    {
        p.x = this->spacing;
        for (int j = 0; j < this->numTilesWidth; ++j)
        {
            if (id == targetId)
                return SDL_Rect({ p.x,p.y,this->tileWidth,tileHeight });
            p.x += this->tileWidth + this->spacing;
            ++targetId;
        }
        p.y += this->tileHeight + this->spacing;
    }

    return rect;
}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // L03: DONE 2: Make sure you clean up any memory allocated from tilesets/map
    // Remove all tilesets
    ListItem<TileSet*>* item;
    item = data.tilesets.start;

    while (item != NULL)
    {
        RELEASE(item->data);
        item = item->next;
    }
    data.tilesets.clear();

    ListItem<MapLayer*>* layersP;
    layersP = data.layers.start;
    // L04: TODO 2: clean up all layer data
    while (layersP != NULL)
    {
        RELEASE(layersP->data);
        layersP = layersP->next;
    }
    // Remove all layers
    data.layers.clear();


    // Clean up the pugui tree
    mapFile.reset();

    return true;
}


// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if (result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

    if (ret == true)
    {
        // L03: DONE 3: Create and call a private function to load and fill all your map data
        ret = LoadMap();
    }

    // L03: DONE 4: Create and call a private function to load a tileset
    // remember to support more any number of tilesets!
    pugi::xml_node tileset;
    pugi::xml_node layers;

    for (tileset = mapFile.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
    {
        TileSet* set = new TileSet();

        if (ret == true) ret = LoadTileset(tileset, set);

        if (ret == true) ret = LoadTilesetImage(tileset, set);

        data.tilesets.Add(set);


    }
    // L04: TODO 4: Iterate all layers and load each of them
    
    pugi::xml_node layer;
    for (layer = mapFile.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
    {
        MapLayer* lay = new MapLayer();

        ret = LoadLayer(layer, lay);


        if (ret == true)
            data.layers.Add(lay);
    }

    if (ret == true)
    {
        // L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything
        LOG("Successfully parsed map XML file : %s", filename);
        LOG("width %d", data.width, " height %d", data.height);
        LOG("tile_width %d", data.tileWidth, " tile_height", "%d", data.tileHeight);
        LOG("Tileset----");
        

        // L04: TODO 4: LOG the info for each loaded layer
        ListItem<MapLayer*>* layerList = data.layers.start;
        while (layerList != nullptr) {

            LOG("name : %s", layerList->data->name);
            LOG("width %d", layerList->data->width);
            LOG("height %d", layerList->data->height);
            //max value tiene que ser implementado 
            for (int i = 0; i < layerList->data->tileNumber; i++)
            {
                if (layerList->data->gids == NULL)
                {
                    LOG("Gids %d missing", i);

                }

            }
            layerList = layerList->next;
        }

    }


    mapLoaded = ret;

    return ret;
}

// L04: TODO 3: Create the definition for a function that loads a single layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
    // L04: TODO 3: Load a single layer
    //gids start

    layer->name = node.attribute("name").as_string();
    layer->width = node.attribute("width").as_int();
    layer->height = node.attribute("height").as_int();

    layer->data = new uint[(data.width * data.height * sizeof(uint))];
    memset(layer->data, 0, size_t(data.width * data.height * sizeof(uint)));

    LoadProperties(node, layer->prop);

    pugi::xml_node gidNode;
    int i = 0;
    for (gidNode = node.child("data").child("tile"); gidNode; gidNode = gidNode.next_sibling("tile"))
    {
        StoreId(gidNode, layer, i);
        ++i;
    }

    //gids por layer
    layer->tileNumber = layer->width * layer->height;

    //layer->gids =  layer->gids[layer->tileNumber];
    memset(layer->gids, 0, layer->tileNumber);


    pugi::xml_node& layerData = node.child("data");

   
    int j = 0;
    for (pugi::xml_node& tilegid = layerData.first_child(); tilegid; tilegid = tilegid.next_sibling())
    {
        //Storage
        layer->gids[j] = tilegid.attribute("gid").as_int();

        //siguiente gid
        j++;
    }

    bool ret = true;


    /*data.maxLayers++;*/

    return ret;
}
bool Map::LoadTileset(pugi::xml_node& tilesetNode, TileSet* ts)
{

    bool ret = true;
    SString tmp("%s%s", folder.GetString(), tilesetNode);

    //no sense
    if (tilesetNode == NULL)
    {
        LOG("Could not load tileset %s. pugi error: %s", tilesetNode, "no tileset");
        ret = false;
    }

    if (ret == true) 
    {

        ts->firstgid = tilesetNode.attribute("firstgid").as_int();
        ts->name = tilesetNode.attribute("name").as_string();
        ts->tileWidth = tilesetNode.attribute("tilewidth").as_int();
        ts->tileHeight = tilesetNode.attribute("tileheight").as_int();
        ts->spacing = tilesetNode.attribute("spacing").as_int();
        ts->margin = tilesetNode.attribute("margin").as_int();
        ts->numTilesWidth = tilesetNode.attribute("columns").as_int();
        ts->numTilesHeight = tilesetNode.attribute("tilecount").as_int() / ts->numTilesWidth;
    }



    int i = 0;
    LOG("HI");
    for (pugi::xml_node& TileId = mapFile.child("map").child("tileset").child("tile"); TileId && ret; TileId = TileId.next_sibling("tile")) 
    {

        ts->tId[i].id = TileId.attribute("id").as_int();
        LOG("ID: %d", ts->tId[i].id);
        i++;

    }



    return ret;
}


bool Map::StoreId(pugi::xml_node& node, MapLayer* layer, int index)
{
    bool ret = true;

    layer->data[index] = node.attribute("gid").as_uint();

    return ret;
}

bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
    bool ret = true;
    pugi::xml_node propNode = node.child("properties").child("property");


    for (propNode; propNode && ret; propNode = propNode.next_sibling()) {

        Properties::Property* prop = new Properties::Property();

        prop->name.create(propNode.attribute("name").as_string("Not Found"));
        prop->type.create(propNode.attribute("type").as_string("Not Found"));
        prop->value = propNode.attribute("value").as_int(0);

        properties.list.Add(prop);
        //...
    }
    return ret;
}


int Properties::GetProperty(const char* name, int defaultValue ) const {
    int x = 0;
    ListItem<Property*>* props = list.start;

    while (props != NULL)
    {
        if (props->data->name == name)
            return props->data->value;
        props = props->next;
    }
    return defaultValue;
}


