#include "Framework.h"
#include "PlayScene.h"

PlayScene::PlayScene()
{
	BulletManager::Get();
	TileManager::Get()->CreateTiles();
	TileManager::Get()->LoadTile("Resources/TextData/Stage1.map");

	player = new Player;
	enemy = new Enemy;
}

PlayScene::~PlayScene()
{
	delete player;
	delete enemy;
}

void PlayScene::Update()
{
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

}

void PlayScene::CheckCollision()
{
	TileManager::Get()->CheckCollider(enemy);
	TileManager::Get()->CheckCollider(player);

	BulletManager::Get()->ResolveBallCharacterCollision(player);
	BulletManager::Get()->ResolveBallCharacterCollision(enemy);

	TileManager::Get()->CheckBulletCollider();
}
