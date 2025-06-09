#pragma once

class TreeTile : public Tile
{
public:
	TreeTile();
	~TreeTile() {}

	void Collision(RectCollider* rect, const Vector2& overlap) override;
};