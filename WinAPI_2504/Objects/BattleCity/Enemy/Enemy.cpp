#include "Framework.h"

Enemy::Enemy()
{
	stat.life = 1;
	stat.tag = "enemy";
	stat.spawnPoint = { 250,700 };

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

void Enemy::Fire()
{
	switch (curState)
	{
	case Character::Idle:
		BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Right(),"enemy");
		break;
	case Character::GoToUp:
		BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Up(),"enemy");
		break;
	case Character::GoToDown:
		BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Down(), "enemy");
		break;
	case Character::GoToLeft:
		BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Left(), "enemy");
		break;
	case Character::GoToRight:
		BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Right(), "enemy");
		break;
	}
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
	if (path.empty())
		return;

	Vector2 destPos = path.back();

	velocity = destPos - localPosition;

	if (velocity.Magnitude() < 1.0f)
	{
		path.pop_back();
	}
	else
	{
		velocity.Normalize();

	}
	
	const float threshold = 0.9f; // 1.0에 가까울수록 정방향에 가까움 + gpt도움 내적이용하는 방법

	if (velocity.Dot(velocity,Vector2::Up()) > threshold)
	{
		curState = GoToUp;
	}
	else if (velocity.Dot(velocity, Vector2::Down()) > threshold)
	{
		curState = GoToDown;
	}
	else if (velocity.Dot(velocity, Vector2::Left()) > threshold)
	{
		curState = GoToLeft;
	}
	else if (velocity.Dot(velocity, Vector2::Right()) > threshold)
	{
		curState = GoToRight;
	}

	Translate(velocity * speed * DELTA);
}

