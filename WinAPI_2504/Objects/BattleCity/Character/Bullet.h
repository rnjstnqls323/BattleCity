#pragma once

class Bullet : public CircleCollider
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
private:
	string tag;

	Vector2 direction;
};