#include "Framework.h"
#include "InstancingScene.h"

InstancingScene::InstancingScene()
{
	TileManager::Get()->CreateTiles();
	TileManager::Get()->LoadTextures(L"Resources/TextData/Stage1.map");


	tileFactory = new TileFactory;
	vector<Tile*> tiles = TileManager::Get()->GetBgTile();

	for (Tile* tile : tiles)
	{
		tileFactory->SetTileInfo(tile);
	}
	tileFactory->SetInstanceBuffer();
}

InstancingScene::~InstancingScene()
{
	//for (Quad* quad : quads)
	//	delete quad;
}

void InstancingScene::Update()
{
}

void InstancingScene::Render()
{
	//for (Quad* quad : quads)
	//{
	//	quad->Render();
	//}

	//instanceBuffer->Set(1);
	//
	//quad->GetMaterial()->Set();
	//
	//quad->GetMesh()->DrawInstanced(SIZE);

	tileFactory->TileRender();
}
