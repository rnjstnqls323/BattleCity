#pragma once

class WallTile : public Tile
{
public:
	WallTile();
	~WallTile();

	void BulletCollision(Bullet* bullet) override;
};