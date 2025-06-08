#pragma once

class Player :public Character
{
public :
	Player();
	~Player();

private:
	void CreateAnimation() override;

private:
	int life = 5;
};