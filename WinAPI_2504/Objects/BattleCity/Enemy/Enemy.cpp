#include "Framework.h"

Enemy::Enemy()
{
	stat.life = 1;
	stat.tag = "enemy";
	stat.spawnPoint = {300,300};

	SetLocalPosition(stat.spawnPoint);
	UpdateWorld();
	CreateAnimation();

	//curPos = GetLocalPosition();
	//prePos = curPos;
	speed = 50.0f;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Move();
	UpdateAnimation();
	UpdateWorld();
	animationTransform->UpdateWorld();
}

void Enemy::CreateAnimation()
{
	animation->LoadClip("Resources/Textures/BattleCity/Enemy/", "ENEMY_DOWN.xml", true);
	animation->LoadClip("Resources/Textures/BattleCity/Enemy/", "ENEMY_UP.xml", true);
	animation->LoadClip("Resources/Textures/BattleCity/Enemy/", "ENEMY_DOWN.xml", true);
	animation->LoadClip("Resources/Textures/BattleCity/Enemy/", "ENEMY_LEFT.xml", true);
	animation->LoadClip("Resources/Textures/BattleCity/Enemy/", "ENEMY_RIGHT.xml", true);
	animation->LoadClip("Resources/Textures/BattleCity/Enemy/", "ENEMY_DEAD.xml", true);
}

void Enemy::Move()
{
	switch (dirState)
	{
	case DirUp:
		dir = Vector2::Up();
		curState = GoToUp;
		break;
	case DirDown:
		dir = Vector2::Down();
		curState = GoToDown;
		break;
	case DirLeft:
		dir = Vector2::Left();
		curState = GoToLeft;
		break;
	case DirRight:
		dir = Vector2::Right();
		curState = GoToRight;
		break;
	}
	
	Translate(dir * speed * DELTA);
}
