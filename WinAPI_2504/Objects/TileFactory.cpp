#include "Framework.h"

//Wall, Steel, Tree, None, Water
TileFactory::TileFactory()
{
	tiles.resize(TILE_TYPE_SIZE);
		
	CreateNewTiles();
		

}

TileFactory::~TileFactory()
{
	for (Quad* tile : tiles)
	{
		delete tile;
	}

	delete instanceBuffer;
}

void TileFactory::SetTileInfo(Tile* tile)
{
	Vector2 pos = tile->GetGlobalPosition();
	Matrix world = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	TileMatrix tileMatrix = { world, tile->GetTileType() };

	tileInfo.push_back(tileMatrix);
	tilePos.push_back(XMMatrixTranspose(world));
}

void TileFactory::TileRender()
{
	instanceBuffer->Set(1);
	//int count = 0;

	//for (Quad* tile : tiles)
	//{
	//	tile->GetMaterial()->Set(count++);
	//	tile->GetMesh()->DrawInstanced(tileInfo.size());
	//}
	tiles[0]->GetMaterial()->Set();
	tiles[0]->GetMesh()->DrawInstanced(tileInfo.size());
}

void TileFactory::CreateNewTiles()
{
	tiles[0] = new Quad(L"Resources/Textures/BattleCity/BackGround/wall_brick.png", Vector2(),
		Vector2(1.0f, 1.0f));
	tiles[1] = new Quad(L"Resources/Textures/BattleCity/BackGround/wall_steel.png");
	tiles[2] = new Quad(L"Resources/Textures/BattleCity/BackGround/trees.png");
	tiles[3] = new Quad(L"Resources/Textures/BattleCity/BackGround/BackGround.png");
	tiles[4] = new Quad(L"Resources/Textures/BattleCity/BackGround/water_2.png");


	//for (Quad* tile : tiles)
	//{
	//	tile->GetMaterial()->SetShader(L"Instancing.hlsl");
	//}

	tiles[0]->GetMaterial()->SetShader(L"Instancing.hlsl");
}

void TileFactory::SetInstanceBuffer()
{
	instanceBuffer = new VertexBuffer(tilePos.data(), sizeof(Matrix), tilePos.size());
}
