#include "App.h"
#include "PathFinding.h"

#include "Defs.h"
#include "Log.h"

PathFinding* PathFinding::instance = nullptr;

PathFinding* PathFinding::GetInstance()
{
	if (instance == nullptr) instance = new PathFinding();

	return instance;
}

PathFinding::PathFinding() : map(NULL), lastPath(DEFAULT_PATH_LENGTH), width(0), height(0)
{
	//name.Create("pathfinding");
}

// Destructor
PathFinding::~PathFinding()
{
	RELEASE_ARRAY(map);
	RELEASE(instance);
}

// Called before quitting
bool PathFinding::CleanUp()
{
	LOG("Freeing pathfinding library");

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
	return (pos.x  >= 0 && pos.x <= (int)width &&
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
uint PathNode::FindWalkableAdjacents(PathFinding* pathf, PathList& listToFill) const
{
	iPoint cell;
	uint before = listToFill.list.Count();

	// north
	cell.Create(pos.x, pos.y + 1);
	if (pathf->IsWalkable(cell)) listToFill.list.Add(PathNode(-1, -1, cell, this));

	// south
	cell.Create(pos.x, pos.y - 1);
	if (pathf->IsWalkable(cell)) listToFill.list.Add(PathNode(-1, -1, cell, this));

	// east
	cell.Create(pos.x + 1, pos.y);
	if (pathf->IsWalkable(cell)) listToFill.list.Add(PathNode(-1, -1, cell, this));

	// west
	cell.Create(pos.x - 1, pos.y);
	if (pathf->IsWalkable(cell)) listToFill.list.Add(PathNode(-1, -1, cell, this));

	return listToFill.list.Count();
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

void PathNode::Description(PathNode& node)
{
	LOG("position x: %d position y: %d", node.pos.x, node.pos.y);
	LOG("f score: %d g: %d h: %d", node.Score(), node.g, node.h);
}

void PathFinding::DrawPath(Render* render, DynArray<iPoint> path)
{
	int c = path.Count() ;
	for (int i = 0; i < c; i++)
	{
		SDL_Rect tmp = { path[i].x * 16,path[i].y * 16 , 16, 16 };
		render->DrawRectangle(tmp, { 255, 0, 0, 255 });
	}

}

// ----------------------------------------------------------------------------------
// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
// ----------------------------------------------------------------------------------
int PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
{
	// L12b: TODO 1: if origin or destination are not walkable, return -1


	if (!IsWalkable(origin) || !IsWalkable(destination))
		return -1;

	if (origin == destination)
		return -1;

	PathList open;
	PathList closed;

	//PathNode originNode = PathNode(0, origin.DistanceTo(destination), origin, nullptr);
	PathNode originNode = PathNode(0, origin.DistanceManhattan(destination), origin, nullptr);
	open.list.Add(originNode);

	while (open.list.Count() != 0)
	{
		// L12b: TODO 3: Move the lowest score cell from open list to the closed list
		PathNode lowestScore = open.GetNodeLowestScore()->data;
		open.list.Del(open.GetNodeLowestScore());
		closed.list.Add(lowestScore);
		//lowestScore.Description(lowestScore);

		if (closed.list.end->data.pos == destination) // We have reached the end
		{
			PathNode backtrack = closed.list.end->data;
			lastPath.PushBack(backtrack.pos);

			while (backtrack.parent != nullptr)
			{
				if (backtrack.parent != NULL)
					backtrack = closed.Find(backtrack.parent->pos)->data;
				lastPath.PushBack(backtrack.pos);
			}

			lastPath.Flip();
			return 0;
		}

		// L12b: TODO 5: Fill a list of all adjancent nodes
		PathList adjcNodes;
		closed.list.end->data.FindWalkableAdjacents(GetInstance(), adjcNodes);

		for (ListItem<PathNode>* list = adjcNodes.list.start; list != NULL; list = list->next)
		{
			if (closed.Find(list->data.pos) != NULL)
			{
				continue;
			}
			else if (open.Find(list->data.pos) != NULL) //NOT FOUND
			{
				/*int F = list->data.CalculateF(destination);
				open.list.Add(list->data);*/
				PathNode tmp = open.Find(list->data.pos)->data;
				list->data.CalculateF(destination);
				if (list->data.g < tmp.g)
				{
					tmp.parent = list->data.parent;
				}
			}
			else
			{
				list->data.CalculateF(destination);
				open.list.Add(list->data);
			}

		}
		adjcNodes.list.Clear();
	}
	return -1;

}

