#include "Framework.h"

Player::Player()
{
	CreateAnimation();
}

Player::~Player()
{
}

void Player::Update()
{
	Fire();
	Character::Update();
}

void Player::CreateAnimation()
{
	animation->LoadClip("Resources/Textures/BattleCity/Player/", "PLAYER_DOWN.xml", true);
	animation->LoadClip("Resources/Textures/BattleCity/Player/", "PLAYER_UP.xml", true);
	animation->LoadClip("Resources/Textures/BattleCity/Player/", "PLAYER_DOWN.xml", true);
	animation->LoadClip("Resources/Textures/BattleCity/Player/", "PLAYER_LEFT.xml", true);
	animation->LoadClip("Resources/Textures/BattleCity/Player/", "PLAYER_RIGHT.xml", true);
	animation->LoadClip("Resources/Textures/BattleCity/Player/", "PLAYER_DEAD.xml", true);
}

void Player::Fire()
{
	if (Input::Get()->IsKeyDown(VK_SPACE))
	{
		switch (curState)
		{
		case Character::Idle:
			BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Right());
			break;
		case Character::GoToUp:
			BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Up());
			break;
		case Character::GoToDown:
			BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Down());
			break;
		case Character::GoToLeft:
			BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Left());
			break;
		case Character::GoToRight:
			BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Right());
			break;
		}
		
	}
}
