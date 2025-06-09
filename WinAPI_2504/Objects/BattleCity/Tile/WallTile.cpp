#include "Framework.h"

WallTile::WallTile()
{
}

WallTile::~WallTile()
{
}

void WallTile::BulletCollision(Bullet* bullet)
{
	bullet->SetActive(false);
	this->SetActive(false);
}
