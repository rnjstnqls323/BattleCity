#include "Framework.h"
#include "PlayScene.h"

PlayScene::PlayScene()
{
	TileManager::Get();
	TileManager::Get()->CreateTiles();
	TileManager::Get()->LoadTile("Resources/TextData/Test3.map");

	player = new Player;
	player->SetLocalPosition(50, 50);
	player->UpdateWorld();
}

PlayScene::~PlayScene()
{
	delete player;
}

void PlayScene::Update()
{
	player->Update();
	TileManager::Get()->CheckCollider(player);
}

void PlayScene::Render()
{
	TileManager::Get()->RenderTile();
	player->Render();
}
