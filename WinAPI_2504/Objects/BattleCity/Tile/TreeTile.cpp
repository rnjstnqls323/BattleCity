#include "Framework.h"

TreeTile::TreeTile()
{
	stat.life = -1;
	stat.type = Tree;
}

void TreeTile::Collision(RectCollider* rect, const Vector2& overlap)
{
	TileManager::Get()->SetHide(true);


}

