#include "Framework.h"

Player::Player()
{
	CreateAnimation();
}

Player::~Player()
{
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
