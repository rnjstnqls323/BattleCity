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

	Vector2 size = sampleTextures[0]->GetSize();
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
	}

	for (UINT i = 0; i < objCount; i++)
	{
		wstring file = reader->WString();

		Vector2 xy = reader->Vector();

		Tile* tile;
		if (file.find(L"trees") != wstring::npos)
			tile = new TreeTile();
		else if (file.find(L"wall_brick") != wstring::npos)
			tile = new WallTile();
		else if (file.find(L"wall_steel") != wstring::npos)
			tile = new SteelTile();
		else
			tile = new Tile();

		
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
	isHide = false;
	for (Tile* tile : objEditTiles)
	{
		Vector2 overlap;
		bool isCollision = tile->IsRectCollision(character, &overlap);

		if (!isCollision)
			continue;
		
		tile->Collision(character,overlap);
		if (character->GetStat().tag == "enemy")
		{
			Enemy* enemy = (Enemy*)character;
			int num = rand() % 4;
			enemy->ChangeDir(num);
		}
		//불렛 콜리젼 어케할지고민하쇼
	}
}

void TileManager::CheckBulletCollider()
{
	for (Tile* tile : objEditTiles)
	{
		if (!tile->IsActive())
			continue;
		BulletManager::Get()->ResolveBallTileCollision(tile);
	}
}


