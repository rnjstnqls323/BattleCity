#include "Framework.h"
#include "TileEditScene.h"

TileEditScene::TileEditScene()
{
	LoadTextures();

	//Collider::SwitchDraw();
	TileManager::Get();
	sampleTextures = TileManager::Get()->GetSampleTextures();

}

TileEditScene::~TileEditScene()
{
	DeleteEditTiles();
}

void TileEditScene::Update()
{
	switch (editType)
	{
	case TileEditScene::BG:
		EditBGTiles();
		break;
	case TileEditScene::OBJ:
		EditObjTiles();
		break;	
	}	
}

void TileEditScene::Render()
{
	TileManager::Get()->RenderTile();
}

void TileEditScene::GUIRender()
{
	ImGui::Text("Map Editor");
	SaveDialog();	
	ImGui::SameLine();
	LoadDialog();

	ImGui::DragInt("Cols", &mapCols, 1, 1, TILE_NUM);
	ImGui::DragInt("Rows", &mapRows, 1, 1, TILE_NUM);

	const char* editTypeNames[] = { "BG", "OBJ" };

	ImGui::ListBox("Edit Type", (int*)&editType, editTypeNames, 2);
	
	if (ImGui::Button("Create Tiles"))
	{
		CreateEditTiles();
	}
	
	RenderSampleButtons();
}

void TileEditScene::LoadTextures()
{
	TileManager::Get()->LoadTextures(L"Resources/Textures/BattleCity/BackGround/");
}

void TileEditScene::RenderSampleButtons()
{
	ImGui::DragInt("Col", &sampleButtonCols);

	if (ImGui::TreeNode("Sample Buttons"))
	{
		int count = 0;

		for (Texture* texture : sampleTextures)
		{
			string key = Utility::ToString(texture->GetFile());
			ImTextureID imguiTextureID = (ImTextureID)texture->GetSRV();

			if (ImGui::ImageButton(key.c_str(), imguiTextureID, ImVec2(50, 50)))
			{
				TileManager::Get()->SetSelectTexture(texture);
			}

			count++;

			if(count % sampleButtonCols)
			{
				ImGui::SameLine();
			}
		}

		ImGui::TreePop();
	}
}

void TileEditScene::CreateEditTiles()
{
	TileManager::Get()->CreateTiles();
}

void TileEditScene::DeleteEditTiles()
{
	TileManager::Get()->DeleteTiles();
}

void TileEditScene::EditBGTiles()
{
	TileManager::Get()->EditBGTile();
}

void TileEditScene::EditObjTiles()
{
	TileManager::Get()->EditOBJTile();
}

void TileEditScene::Save(string file)
{
	TileManager::Get()->SaveTile(file);
}

void TileEditScene::Load(string file)
{
	TileManager::Get()->LoadTile(file);
}

void TileEditScene::SaveDialog()
{
	string key = "Save";

	if (ImGui::Button(key.c_str()))
	{
		DIALOG->OpenDialog(key, key, ".map");
	}

	if (DIALOG->Display(key))
	{
		if (DIALOG->IsOk())
		{
			char temp[256] = {};
			GetCurrentDirectoryA(256, temp);
			string path = temp;
			string file = DIALOG->GetFilePathName();
			file = file.substr(path.size() + 1);
			Save(file);
		}
		
		DIALOG->Close();
	}
}

void TileEditScene::LoadDialog()
{
	string key = "Load";

	if (ImGui::Button(key.c_str()))
	{
		DIALOG->OpenDialog(key, key, ".map");
	}

	if (DIALOG->Display(key))
	{
		if (DIALOG->IsOk())
		{
			char temp[256] = {};
			GetCurrentDirectoryA(256, temp);
			string path = temp;
			string file = DIALOG->GetFilePathName();
			file = file.substr(path.size() + 1);
			Load(file);
		}

		DIALOG->Close();
	}
}
