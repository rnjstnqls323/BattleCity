#pragma once

class Tile;
class Character;
class Node;
class AStar;

class TileManager :public Singleton<TileManager>
{
	friend class Singleton;

private:
	TileManager();
	~TileManager();

public:

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

	void CheckBulletCollider(AStar*& aStar);

	//Vector2 GetTileSize() { return bgEditTiles[0]->Size(); }

	void MakeNodes(vector<Node*>& nodes);

	bool IsPointCollision(Vector2 point);
	
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