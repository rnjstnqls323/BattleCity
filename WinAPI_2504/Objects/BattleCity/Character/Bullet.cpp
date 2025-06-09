#include "Framework.h"
#include "Bullet.h"

Bullet::Bullet():CircleCollider(5)
{	
}

Bullet::~Bullet()
{
}

void Bullet::Fire(Vector2 pos, Vector2 dir, string tag)
{
	this->tag = tag;
	if(tag == "player")
		SetColor(1, 1, 0);
	else
		SetColor(1, 0, 0);
	direction = dir;

	SetLocalPosition(pos);
}


void Bullet::Render()
{
	CircleCollider::Render();
}

void Bullet::Update()
{
	if (isActive)
		Move();
	UpdateWorld();
}

void Bullet::Move()
{
	Translate(direction * BULLET_SPEED * DELTA);
}
