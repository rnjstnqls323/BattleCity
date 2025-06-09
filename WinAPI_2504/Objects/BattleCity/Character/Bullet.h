#pragma once

class Bullet : public RectCollider
{
private:
	const float BULLET_SPEED = 200.0f;
public:
	Bullet();
	~Bullet();

	void Fire(Vector2 pos, Vector2 dir ,string tag);

	void Render();
	void Update();

	void Move();

	string GetBulletTag() { return bulletTag; }
private:
	Quad* quad;
	string bulletTag;

	Vector2 direction;
};