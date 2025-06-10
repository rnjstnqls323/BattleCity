#include "Framework.h"
#include "PlayScene.h"

PlayScene::PlayScene()
{
	BulletManager::Get();
	TileManager::Get()->CreateTiles();
	TileManager::Get()->LoadTile("Resources/TextData/Stage1.map");


	aStar = new AStar;
	player = new Player;
	enemy = new Enemy;
}

PlayScene::~PlayScene()
{
	delete player;
	delete enemy;
	delete aStar;
}

void PlayScene::Update()
{
	PlayTimer();
	TileManager::Get()->SetHide(false);
	player->Update();
	enemy->Update();

	
	BulletManager::Get()->Update();

	CheckCollision();
}

void PlayScene::Render()
{
	if (TileManager::Get()->IsHide())
	{
		TileManager::Get()->RenderBGTile();
		player->Render();
		enemy->Render();
		TileManager::Get()->RenderOBJTile();
	}
	else
	{
		TileManager::Get()->RenderBGTile();
		TileManager::Get()->RenderOBJTile();
		player->Render();
		enemy->Render();
	}

	BulletManager::Get()->Render();
	aStar->Render();
}

void PlayScene::CheckCollision()
{
	TileManager::Get()->CheckCollider(enemy);
	TileManager::Get()->CheckCollider(player);

	BulletManager::Get()->ResolveBallCharacterCollision(player);
	BulletManager::Get()->ResolveBallCharacterCollision(enemy);

	TileManager::Get()->CheckBulletCollider(aStar);
}

void PlayScene::EnemyChase()
{
	float dist = (player->GetLocalPosition() - enemy->GetLocalPosition()).Magnitude();
	if (dist > 200)
		enemy->SetMode(Patrol);
	else if (dist > 150)
		enemy->SetMode(Chase);
	else
		enemy->SetMode(Attack);

	ChaseMode mode = enemy->GetMode();

	switch (mode)
	{
	case Patrol:
	{
		Vector2 patrolPos;

		for (int i = 0; i < 50; i++)
		{
			patrolPos.x = rand() % CENTER_X;
			patrolPos.y = rand() % SCREEN_HEIGHT;

			if (!TileManager::Get()->IsPointCollision(patrolPos))
				break;
		}

		if (TileManager::Get()->IsPointCollision(patrolPos))
			patrolPos = CENTER;
		

		//patrolPos = CENTER;
		int start = aStar->FindCloseNode(enemy->GetLocalPosition());
		int end = aStar->FindCloseNode(patrolPos);
		enemy->SetPath(aStar->GetPath(start, end));

	}
	break;
	case Chase:
	case Attack:
	{
		int start = aStar->FindCloseNode(enemy->GetLocalPosition());
		int end = aStar->FindCloseNode(player->GetLocalPosition());
		enemy->SetPath(aStar->GetPath(start, end));
	}
	break;
	}
}

void PlayScene::PlayTimer()
{
	timer += DELTA;
	if (timer - chaseTimer > CHASE_TIME)
	{
		chaseTimer = timer;
		EnemyChase();
	}
		
	if (timer - enemyFireTimer > FIRE_TIME && enemy->GetMode() == Attack)
	{
		enemyFireTimer = timer;
		enemy->Fire();
	}
}
