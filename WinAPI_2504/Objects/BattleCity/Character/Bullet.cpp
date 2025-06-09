#include "Framework.h"
#include "Bullet.h"

Bullet::Bullet():RectCollider({20,20})
{	
	quad = new Quad(L"Resources/Textures/BattleCity/Bullet.png");
	quad->SetParent(this);
	quad->UpdateWorld();
}

Bullet::~Bullet()
{
	delete quad;
}

void Bullet::Fire(Vector2 pos, Vector2 dir, string tag)
{
	this->bulletTag = tag;
	if(bulletTag == "player")
		SetColor(1, 1, 0);
	else
		SetColor(1, 0, 0);
	direction = dir;

	SetLocalPosition(pos);
}


void Bullet::Render()
{
	RectCollider::Render();
	quad->Render();
}

void Bullet::Update()
{
	if (isActive)
		Move();
	UpdateWorld();
	quad->UpdateWorld();
}

void Bullet::Move()
{
	Translate(direction * BULLET_SPEED * DELTA);
}
