#pragma once

class Player :public Character
{
public :
	Player();
	~Player();

	void Update() override;

private:
	void CreateAnimation() override;

};