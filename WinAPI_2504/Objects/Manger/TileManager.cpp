#include "Framework.h"

TileManager::TileManager()
{
	//CreateTiles();
}

TileManager::~TileManager()
{
	DeleteTiles();
}

//void TileManager::UpdateTile()
//{
//}
void TileManager::RenderOBJTile()
{
	for (Tile* tile : objEditTiles)
	{
		tile->Render();
		tile->RectCollider::Render();
	}
}

void TileManager::RenderBGTile()
{
	for (Tile* tile : bgEditTiles)
	{
		tile->Render();
	}

}

void TileManager::LoadTextures(wstring path)
{
	WIN32_FIND_DATA findData;

	HANDLE handle = FindFirstFile((path + L"*.png").c_str(), &findData);

	bool result = true;

	while (result)
	{
		Texture* texture = Texture::Add(path + findData.cFileName);
		sampleTextures.push_back(texture);

		result = FindNextFile(handle, &findData);
	}
}

void TileManager::CreateTiles()
{
	DeleteTiles();

	Vector2 size = { 25,25 };
	Vector2 startPos = Vector2(size.x * 0.5f, SCREEN_HEIGHT - size.y * 0.5f);

	for (int y = 0; y < mapRow; y++)
	{
		for (int x = 0; x < mapCol; x++)
		{
			Tile* tile = new Tile();
			Vector2 pos = startPos + Vector2(x * tile->Size().x, -y * tile->Size().y);
			tile->SetLocalPosition(pos);
			tile->UpdateWorld();

			bgEditTiles.push_back(tile);
		}
	}
}

void TileManager::DeleteTiles()
{
	for (Tile* tile : bgEditTiles)
	{
		delete tile;
	}

	bgEditTiles.clear();

	for (Tile* tile : objEditTiles)
	{
		delete tile;
	}
	objEditTiles.clear();
}

void TileManager::SaveTile(string file)
{
	BinaryWriter* writer = new BinaryWriter(file);

	writer->UInt(bgEditTiles.size());
	writer->UInt(objEditTiles.size());

	for (Tile* tile : bgEditTiles)
		writer->WString(tile->GetImage()->GetMaterial()->GetBaseMap()->GetFile());

	for (Tile* tile : objEditTiles)
	{
		writer->WString(tile->GetImage()->GetMaterial()->GetBaseMap()->GetFile());
		Vector2 pos = tile->GetLocalPosition();
		writer->Vector({ pos.x, pos.y });
	}
	delete writer;
}

void TileManager::LoadTile(string file)
{
	BinaryReader* reader = new BinaryReader(file);

	if (reader->IsFailed())
	{
		delete reader;
		return;
	}

	UINT bgCount = reader->UInt();
	UINT objCount = reader->UInt();

	for (UINT i = 0; i < bgCount; i++)
	{
		wstring file = reader->WString();
		bgEditTiles[i]->GetImage()->GetMaterial()->SetBaseMap(file);

		Tile* tile = nullptr;  // Tile은 공통 부모 클래스라고 가정

		if (file.find(L"trees") != wstring::npos)
			tile = new TreeTile();
		else if (file.find(L"wall_brick") != wstring::npos)
			tile = new WallTile();
		else if (file.find(L"wall_steel") != wstring::npos)
			tile = new SteelTile();
		else if (file.find(L"water") != wstring::npos)
			tile = new WaterTile();
		else
			tile = new Tile(); // 기본 타입 처리 (선택사항)
		
		delete bgEditTiles[i];
		bgEditTiles[i] = tile;
	}

	for (UINT i = 0; i < objCount; i++)
	{
		wstring file = reader->WString();

		Vector2 xy = reader->Vector();

		Tile* tile = nullptr;
		
		if (file.find(L"trees") != wstring::npos)
			tile = new TreeTile();
		else if (file.find(L"wall_brick") != wstring::npos)
			tile = new WallTile();
		else if (file.find(L"wall_steel") != wstring::npos)
			tile = new SteelTile();
		else if (file.find(L"water") != wstring::npos)
			tile = new WaterTile();
		
		tile->GetImage()->GetMaterial()->SetBaseMap(file);
		tile->SetLocalPosition(xy);
		tile->UpdateWorld(); // 위치 적용
		objEditTiles.push_back(tile);
	}
}

void TileManager::EditOBJTile()
{
	if (Input::Get()->IsKeyPress(VK_RBUTTON) == false)
		return;

	for (Tile* tile : bgEditTiles)
	{
		if (tile->IsPointCollision(mousePos))
		{
			Vector2 pos = tile->GetLocalPosition();

			// 기존 obj 타일이 같은 위치에 있다면 삭제
			for (auto it = objEditTiles.begin(); it != objEditTiles.end(); ++it)
			{
				if ((*it)->GetLocalPosition() == pos)
				{
					delete* it;
					objEditTiles.erase(it);
					break;
				}
			}

			// 새로운 타일 생성
			Tile* objTile = new Tile();;

			wstring filePath = selectTexture->GetFile();


			objTile->GetImage()->GetMaterial()->SetBaseMap(selectTexture);
			objTile->SetLocalPosition(pos);
			objTile->UpdateWorld();

			objEditTiles.push_back({ objTile });

			sort(objEditTiles.begin(), objEditTiles.end(), Tile::IsCompare);
		}
	}
}

void TileManager::EditBGTile()
{
	if (Input::Get()->IsKeyPress(VK_LBUTTON) == false)
		return;

	for (Tile* tile : bgEditTiles)
	{
		if (tile->IsPointCollision(mousePos))
		{
			tile->GetImage()->GetMaterial()->SetBaseMap(selectTexture);
		}
	}
}

void TileManager::CheckCollider(Character* character)
{
	for (Tile* tile : objEditTiles)
	{
		Vector2 overlap;
		bool isCollision = tile->IsRectCollision(character, &overlap);

		if (!isCollision)
			continue;
		
		tile->Collision(character,overlap);
	}
}

void TileManager::CheckBulletCollider(AStar*& aStar)
{
	for (Tile* tile : objEditTiles)
	{
		if (!tile->IsActive())
			continue;
		BulletManager::Get()->ResolveBallTileCollision(tile, aStar);
	}
}

void TileManager::MakeNodes(vector<Node*>& nodes)
{
	for (Tile* tile : bgEditTiles)
	{
		//Vector2 tilePos = tile->GetGlobalPosition() + Vector2::Up() * tileSize.y * 0.25f;
		Vector2 tilePos = tile->GetGlobalPosition();
		Node* node = new Node(tilePos, nodes.size());

		for (Tile* obj : objEditTiles)
		{
			if (obj->GetTileType() == Tree)
				continue;
			if (obj->IsPointCollision(tilePos))
			{
				node->SetState(Node::Obstacle);
			}
		}

		nodes.push_back(node);
	}
}

bool TileManager::IsPointCollision(Vector2 point)
{
	for (Tile* tile : objEditTiles)
	{
		if (tile->GetTileType() != Tree && tile->IsPointCollision(point))
			return true;
	}
	return false;
}

