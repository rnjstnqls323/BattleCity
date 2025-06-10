#include "Framework.h"

TreeTile::TreeTile()
{
	type = Tree;
}

void TreeTile::Collision(RectCollider* rect, const Vector2& overlap)
{
	TileManager::Get()->SetHide(true);
}

