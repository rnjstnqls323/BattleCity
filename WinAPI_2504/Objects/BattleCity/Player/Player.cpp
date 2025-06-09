#include "Framework.h"

Player::Player()
{
	stat.life = 5;
	stat.tag = "player";
	stat.spawnPoint = PLAYER_HOME;

	SetLocalPosition(stat.spawnPoint);
	UpdateWorld();
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

