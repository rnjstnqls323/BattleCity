#include "Framework.h"

#include "Scenes/TileEditScene.h"
#include "Scenes/PlayScene.h"
#include "Scenes/InstancingScene.h"

GameManager::GameManager()
{
	Create();
		

	//SCENE->AddScene("Edit", new TileEditScene());
	//SCENE->AddScene("Game", new PlayScene());
	SCENE->AddScene("Inst", new InstancingScene());

	SCENE->ChangeScene("Inst");
}

GameManager::~GameManager()
{
	Release();
}

void GameManager::Update()
{
	Timer::Get()->Update();
	Input::Get()->Update();

	Environment::Get()->Update();

	SCENE->Update();

	InvalidateRect(hWnd, nullptr, false);
}

void GameManager::Render()
{
	SCENE->PreRender();
	
	Environment::Get()->SetViewport();
	Device::Get()->Clear();	

	SCENE->Render();

	Environment::Get()->SetUIViewBuffer();
	SCENE->PostRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	SCENE->GUIRender();	

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	Timer::Get();
	Input::Get();

	Device::Get();

	SceneManager::Get();

	Environment::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Release()
{
	Timer::Delete();
	Input::Delete();

	Device::Delete();
	Shader::Delete();
	Texture::Delete();

	SceneManager::Delete();

	Environment::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}
