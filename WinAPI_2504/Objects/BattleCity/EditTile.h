#pragma once

enum TileType
{
	Wall, Steel, Tree, None
};

struct TileStat
{
	int life = 0;
	TileType type = None;
};

class Tile : public RectCollider
{

public:
	Tile();
	~Tile();

	void UpdateWorld();
	void Render();

	virtual void Collision(Character* character, const Vector2& overlap);
	
	Quad* GetImage() { return image; }

	static bool IsCompare(Tile* a, Tile* b)
	{
		return a->GetLocalPosition().y > b->GetLocalPosition().y;
	}

	TileType GetTileType() { return stat.type; }


protected:
	
	TileStat stat;
	Vector2 overlap;
	Quad* image;
};