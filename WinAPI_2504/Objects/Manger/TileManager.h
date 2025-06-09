#pragma once

class Tile;
class Character;

class TileManager :public Singleton<TileManager>
{
	friend class Singleton;

private:
	TileManager();
	~TileManager();

public:
	
	//void UpdateTile();
	void RenderOBJTile();
	void RenderBGTile();
	
	void LoadTextures(wstring path);


	void CreateTiles();
	void DeleteTiles();

	void SaveTile(string file);
	void LoadTile(string file);

	void EditOBJTile();
	void EditBGTile();

	vector<Texture*>& GetSampleTextures() { return sampleTextures; }
	void SetSelectTexture(Texture* texture) { selectTexture = texture; }

	void CheckCollider(Character* character);
	bool IsHide() { return isHide; }
	void SetHide(bool hide) { isHide = hide; }

private:
	int mapCol = TILE_NUM;
	int mapRow = TILE_NUM;

	bool isObjTile = false;
	bool isHide = false;

	vector<Texture*> sampleTextures;
	vector<Tile*> bgEditTiles;
	vector<Tile*> objEditTiles;


	Texture* selectTexture;
};