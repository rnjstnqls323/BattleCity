﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define CENTER_X (SCREEN_WIDTH >> 1)
#define CENTER_Y (SCREEN_HEIGHT >> 1)

#define CENTER Vector2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f)

#define PI 3.141592f

#define DELTA Timer::Get()->GetElapsedTime()
#define SCENE SceneManager::Get()

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define CAM Environment::Get()->GetMainCamera()

#define DIALOG ImGuiFileDialog::Instance()

#define TILE_NUM 25
#define TILE_SIZE 25

#define PLAYER_HOME Vector2(287,151);

#include <windows.h>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <functional>
#include <fstream>
#include <assert.h>
#include <algorithm>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//ImGui
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <ImGuiFileDialog.h>

#pragma comment(lib, "ImGui.lib")

//DirectXTex
#include <DirectXTex/DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;
typedef XMVECTOR Vector4;
typedef XMFLOAT4X4 Float4x4;

typedef function<void()> Event;

#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Input.h"
#include "Framework/Utilities/tinyxml2.h"
#include "Framework/Utilities/BinaryReader.h"
#include "Framework/Utilities/BinaryWriter.h"

#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/GameMath.h"

#include "Framework/Device/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBffer.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/Mesh.h"
#include "Framework/Render/Material.h"
#include "Framework/Render/Frame.h"
#include "Framework/Render/Clip.h"
#include "Framework/Render/RenderTarget.h"

#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"

#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Quad.h"

#include "Objects/Collider/Collider.h"
#include "Objects/Collider/CircleCollider.h"
#include "Objects/Collider/RectCollider.h"
#include "Objects/Collider/LineCollider.h"

#include "Objects/Manger/DataManager.h"
#include "Objects/Manger/EventManager.h"

#include "Objects/Algorithm/DNode.h"
#include "Objects/Algorithm/Dijkstra.h"
#include "Objects/Algorithm/Node.h"
#include "Objects/Algorithm/Heap.h"
#include "Objects/Algorithm/AStar.h"

#include "Objects/BattleCity/EditTile.h"
#include "Objects/BattleCity/Tile/WallTile.h"
#include "Objects/BattleCity/Tile/TreeTile.h"
#include "Objects/BattleCity/Tile/SteelTile.h"
#include "Objects/BattleCity/Tile/WaterTile.h"

#include "Objects/TileFactory.h"

#include "Objects/BattleCity/Character/Bullet.h"

#include "Objects/BattleCity/Character/CharacterAnimation.h"
#include "Objects/BattleCity/Character/Character.h"

#include "Objects/BattleCity/Player/Player.h"
#include "Objects/BattleCity/Enemy/Enemy.h"

#include "Objects/Manger/TileManager.h"
#include "Objects/Manger/BulletManager.h"

#include "Scenes/Scene.h"
#include "Framework/Manager/SceneManager.h"
#include "Framework/Manager/GameManager.h"

extern HWND hWnd;
extern Vector2 mousePos;