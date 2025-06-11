#pragma once

struct TileMatrix
{
	Matrix matrix;
	TileType type;
};
class TileFactory
{
private:
	const int TILE_TYPE_SIZE = 5;
public:
	TileFactory();
	~TileFactory();

	void SetTileInfo(Tile* tile);

	void TileRender();
	void SetInstanceBuffer();
private:
	void CreateNewTiles();
	
private:
	vector<Quad*> tiles;

	vector<TileMatrix> tileInfo;
	vector<Matrix> tilePos;

	VertexBuffer* instanceBuffer;
};