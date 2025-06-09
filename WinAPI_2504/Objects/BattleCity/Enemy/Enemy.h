#pragma once

enum Direction
{
	DirUp,DirDown,DirLeft,DirRight
};
class Enemy :public Character
{
public:
	Enemy();
	~Enemy();

	void Update() override;
	void ChangeDir(int num)
	{
		dirState = (Direction)num;
	}

private:
	void CreateAnimation() override;
	void Move() override;

private:
	int randNum = 0;

	Direction dirState = DirUp;
	Vector2 dir = Vector2::Up();
};