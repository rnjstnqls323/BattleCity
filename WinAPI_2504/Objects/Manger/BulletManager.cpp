#include "Framework.h"

BulletManager::BulletManager()
{
	bullets.resize(BULLET_POOL_SIZE);

	for (Bullet*& bullet : bullets)
	{
		bullet = new Bullet();
		bullet->SetActive(false);
	}
}

BulletManager::~BulletManager()
{
	for (Bullet* bullet : bullets)
	{
		delete bullet;
	}
	bullets.clear();
}

void BulletManager::Update()
{
	for (Bullet* bullet : bullets)
	{
		if (!bullet->IsActive())
			continue;
		bullet->Update();
		if (IsOut(bullet))
			bullet->SetActive(false);
	}
}

void BulletManager::Render()
{
	for (Bullet* bullet : bullets)
	{
		if (!bullet->IsActive())
			continue;
		bullet->Render();
	}
}

void BulletManager::Fire(Vector2 pos, Vector2 dir, string tag)
{
	for (Bullet* bullet : bullets)
	{
		if (bullet->IsActive())
			continue;
		bullet->SetActive(true);
		bullet->Fire(pos, dir, tag);
		return;
	}
}

void BulletManager::ResolveBallTileCollision(Tile* tile)
{
	for (Bullet* bullet : bullets)
	{
		if (!bullet->IsActive())
			continue;

		if (!bullet->IsRectCollision(tile, nullptr))
			continue;

		tile->BulletCollision(bullet);
	}
}

void BulletManager::ResolveBallCharacterCollision(Character* character)
{
	for (Bullet* bullet : bullets)
	{
		if (!bullet->IsActive())
			continue;

		CharacterStat stat = character->GetStat();

		if (!bullet->IsRectCollision(character, nullptr) || stat.tag == bullet->GetBulletTag())
			continue;

		character->ResolveBallCollision();
		bullet->SetActive(false);
	}
}

bool BulletManager::IsOut(Bullet* bullet)
{
	if (bullet->GetLocalPosition().x < 0)
		return true;
	if (bullet->GetLocalPosition().y < 0)
		return true;
	if (bullet->GetLocalPosition().x > CENTER_X)
		return true;
	if (bullet->GetLocalPosition().y > SCREEN_HEIGHT)
		return true;
	return false;
}



