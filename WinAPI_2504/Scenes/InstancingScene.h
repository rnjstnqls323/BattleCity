#pragma once

class InstancingScene : public Scene
{
private:
	const UINT SIZE = 100;

	struct InstanceData
	{
		Matrix world;

		Float2 curFrame;
		Float2 maxFrame;
	};

public:
	InstancingScene();
	~InstancingScene();

	void Update() override;
	void Render() override;

public:
	//vector<Quad*> quads;

	Quad* quad;

	TileFactory* tileFactory;

	vector<Matrix> matrix;
	VertexBuffer* instanceBuffer;
};