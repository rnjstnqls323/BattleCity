#pragma once

class BulletManager : public Singleton<BulletManager>
{
	friend class Singleton;

private:
	const int BULLET_POOL_SIZE = 100;
private:
	BulletManager();
	~BulletManager();

public:
	void Update();
	void Render();

	void Fire(Vector2 pos, Vector2 dir, string tag="player");

private:
	vector<Bullet*> bullets;
};