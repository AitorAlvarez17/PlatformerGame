#include "App.h"
#include "PathFinding.h"

#include "Defs.h"
#include "Log.h"


PathFinding::PathFinding(bool startEnabled) : Module(startEnabled), map(NULL), lastPath(DEFAULT_PATH_LENGTH), width(0), height(0)
{
	name.create("pathfinding");
}

// Destructor
PathFinding::~PathFinding()
{
	RELEASE_ARRAY(map);
}

// Called before quitting
bool PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

	lastPath.Clear();
	RELEASE_ARRAY(map);

	return true;
}

// Sets up the walkability map
void PathFinding::SetMap(uint width, uint height, uchar* data)
{
	this->width = width;
	this->height = height;

	RELEASE_ARRAY(map);
	map = new uchar[width * height];
	memcpy(map, data, width * height);
}

// Utility: return true if pos is inside the map boundaries
bool PathFinding::CheckBoundaries(const iPoint& pos) const
{
	return (pos.x >= 0 && pos.x <= (int)width &&
		pos.y >= 0 && pos.y <= (int)height);
}

// Utility: returns true is the tile is walkable
bool PathFinding::IsWalkable(const iPoint& pos) const
{
	uchar t = GetTileAt(pos);
	return t != INVALID_WALK_CODE && t > 0;
}

// Utility: return the walkability value of a tile
uchar PathFinding::GetTileAt(const iPoint& pos) const
{
	if (CheckBoundaries(pos))
		return map[(pos.y * width) + pos.x];

	return INVALID_WALK_CODE;
}

// To request all tiles involved in the last generated path
const DynArray<iPoint>* PathFinding::GetLastPath() const
{
	return &lastPath;
}

// PathList ------------------------------------------------------------------------
// Looks for a node in this list and returns it's list node or NULL
// ---------------------------------------------------------------------------------
const ListItem<PathNode>* PathList::Find(const iPoint& point) const
{
	ListItem<PathNode>* item = list.start;
	while (item)
	{
		if (item->data.pos == point)
			return item;
		item = item->next;
	}
	return NULL;
}

// PathList ------------------------------------------------------------------------
// Returns the Pathnode with lowest score in this list or NULL if empty
// ---------------------------------------------------------------------------------
ListItem<PathNode>* PathList::GetNodeLowestScore() const
{
	ListItem<PathNode>* ret = NULL;
	int min = 65535;

	ListItem<PathNode>* item = list.end;
	while (item)
	{
		if (item->data.Score() < min)
		{
			min = item->data.Score();
			ret = item;
		}
		item = item->prev;
	}
	return ret;
}

// PathNode -------------------------------------------------------------------------
// Convenient constructors
// ----------------------------------------------------------------------------------
PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
{}

PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
{}

PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
{}

// PathNode -------------------------------------------------------------------------
// Fills a list (PathList) of all valid adjacent pathnodes
// ----------------------------------------------------------------------------------
uint PathNode::FindWalkableAdjacents(PathList& listToFill) const
{
	iPoint cell;
	uint before = listToFill.list.count();

	// north
	cell.create(pos.x, pos.y + 1);
	if (app->pathfinding->IsWalkable(cell))
		listToFill.list.Add(PathNode(-1, -1, cell, this));

	// south
	cell.create(pos.x, pos.y - 1);
	if (app->pathfinding->IsWalkable(cell))
		listToFill.list.Add(PathNode(-1, -1, cell, this));

	// east
	cell.create(pos.x + 1, pos.y);
	if (app->pathfinding->IsWalkable(cell))
		listToFill.list.Add(PathNode(-1, -1, cell, this));

	// west
	cell.create(pos.x - 1, pos.y);
	if (app->pathfinding->IsWalkable(cell))
		listToFill.list.Add(PathNode(-1, -1, cell, this));

	return listToFill.list.count();
}

// PathNode -------------------------------------------------------------------------
// Calculates this tile score
// ----------------------------------------------------------------------------------
int PathNode::Score() const
{
	return g + h;
}

// PathNode -------------------------------------------------------------------------
// Calculate the F for a specific destination tile
// ----------------------------------------------------------------------------------
int PathNode::CalculateF(const iPoint& destination)
{
	g = parent->g + 1;
	h = pos.DistanceTo(destination);

	return g + h;
}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int PathFinding::CreatePath(const iPoint& origin, const iPoint& destination, int maxLength, int maxNodes)
{
	// L12b: TODO 1: if origin or destination are not walkable, return -1
	if (app->pathfinding->IsWalkable(origin) || app->pathfinding->IsWalkable(destination))return -1;

	// L12b: TODO 2: Create two lists: open, close
	PathList open;
	PathList close;
	// Add the origin tile to open
	PathNode _origin(-1, -1, origin, NULL);/* = new PathNode(-1, -1, origin, NULL);*/
	open.list.Add(_origin);
	// Iterate while we have tile in the open list
	int _nodes = 0;
	while (open.list.count() > 0)
	{
		// L12b: TODO 3: Move the lowest score cell from open list to the closed list
		ListItem<PathNode>* lowestScore = open.GetNodeLowestScore();

		if (lowestScore->data.g > maxLength)
		{
			open.list.del(lowestScore);
			continue;
		}
		close.list.Add(lowestScore->data);
		open.list.del(lowestScore);

		// L12b: TODO 4: If we just added the destination, we are done!
		// Backtrack to create the final path
		// Use the Pathnode::parent and Flip() the path when you are finish

		if (lowestScore->data.pos == destination)
		{
			lastPath.PushBack(close.list[close.list.count() - 1].pos);//-1 for placing it in front of the player.
			PathNode _parent = *close.list[close.list.count() - 1].parent;
			lastPath.PushBack(_parent.pos);

			while (_parent.pos != origin) 
			{
				_parent = *_parent.parent;
				lastPath.PushBack(_parent.pos);
			}
			lastPath.Flip();
			break;
		}
		_nodes++;
		if (_nodes == maxNodes)break;

		// L12b: TODO 5: Fill a list of all adjancent nodes
		PathList adjacents;
		close.list[close.list.count() - 1].FindWalkableAdjacents(adjacents);

		//Da error de compilacion en la funcion de find en list.h el codigo de abajo ns porque
		for (int i = 0; i < adjacents.list.count(); i++)
		{
			// ignore nodes in the closed list
			/*if (close.list.find(adjacents.list[i]) != -1)
			{
				continue;
			}

			// If it is NOT found, calculate its F and add it to the open list
			PathNode adjacentNode = adjacents.list[i];
			adjacentNode.CalculateF(destination);

			int index = open.list.find(adjacentNode);
			if (index != -1)
			{
				// If it is already in the open list, check if it is a better path (compare G)
				if (open.list[index].g > adjacentNode.g)
				{
					// If it is a better path, Update the parent
					open.list[index].parent = adjacentNode.parent;
					open.list[index].g = adjacentNode.g;
				}
			}
			else
			{
				open.list.Add(adjacentNode);
			}*/
		}
	}

	if (lastPath.Count() == 0)
	{
		return -1;
	}

	return lastPath.Count();

}

