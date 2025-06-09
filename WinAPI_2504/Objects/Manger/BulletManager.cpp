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
