#pragma once

class PlayScene : public Scene
{
private:
	const float CHASE_TIME = 3.0f;
	const float FIRE_TIME = 2.0f;
public:
	PlayScene();
	~PlayScene();

	void Update() override;

	void Render() override;

	void CheckCollision();

	void EnemyChase();

	void PlayTimer();

private:
	double timer = 0.0;
	double chaseTimer = 0.0;
	double enemyFireTimer = 0.0;

	Player* player;
	Enemy* enemy;

	AStar* aStar;
};