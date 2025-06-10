#pragma once


enum TileType
{
	Wall, Steel, Tree, None
};

class Bullet;

class Tile : public RectCollider
{

public:
	Tile();
	~Tile();

	void UpdateWorld();
	void Render();

	virtual void Collision(RectCollider* rect, const Vector2& overlap);
	virtual void BulletCollision(Bullet* bullet);
	
	Quad* GetImage() { return image; }

	static bool IsCompare(Tile* a, Tile* b)
	{
		return a->GetLocalPosition().y > b->GetLocalPosition().y;
	}

	TileType GetTileType() { return type; }

protected:
	TileType type = None;
	Vector2 overlap;
	Quad* image;
};