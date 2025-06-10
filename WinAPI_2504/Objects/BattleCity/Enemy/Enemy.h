#pragma once

enum ChaseMode
{
	NoneMode, Patrol, Chase, Attack
};

class Enemy :public Character
{
public:
	Enemy();
	~Enemy();

	void Update() override;
	void SetPath(const vector<Vector2>& path) { this->path = path; }

	void Fire() override;
	void SetMode(ChaseMode mode) { this->mode = mode; }

	ChaseMode GetMode() { return mode; }

private:
	void CreateAnimation() override;
	void Move() override;

	

private:
	int randNum = 0;


	ChaseMode mode = NoneMode;
	Vector2 dir = Vector2::Up();
	vector<Vector2> path;
	Vector2 velocity;
};