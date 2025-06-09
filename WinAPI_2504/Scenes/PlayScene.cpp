#include "Framework.h"
#include "PlayScene.h"

PlayScene::PlayScene()
{
	BulletManager::Get();
	TileManager::Get()->CreateTiles();
	TileManager::Get()->LoadTile("Resources/TextData/Stage1.map");

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
	BulletManager::Get()->Update();
}

void PlayScene::Render()
{
	if (TileManager::Get()->IsHide())
	{
		TileManager::Get()->RenderBGTile();
		player->Render();
		TileManager::Get()->RenderOBJTile();
	}
	else
	{
		TileManager::Get()->RenderBGTile();
		TileManager::Get()->RenderOBJTile();
		player->Render();
	}

	BulletManager::Get()->Render();
}
