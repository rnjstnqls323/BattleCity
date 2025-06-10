#include "Framework.h"

WallTile::WallTile()
{
	type = Wall;
}

WallTile::~WallTile()
{
}

void WallTile::BulletCollision(Bullet* bullet)
{
	bullet->SetActive(false);
	this->SetActive(false);
}
