#pragma once

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	void Update() override;

	void Render() override;

	void CheckCollision();

private:
	Player* player;
	Enemy* enemy;
};