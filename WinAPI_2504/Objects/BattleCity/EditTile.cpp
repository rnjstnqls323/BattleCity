#include "Framework.h"

Tile::Tile() : RectCollider(Vector2(16, 16))
{
	image = new Quad(L"Resources/Textures/BattleCity/BackGround/BackGround.png");
	image->SetParent(this);
	//image->SetLocalPosition(Vector2(0, 50));
}

Tile::~Tile()
{
}

void Tile::UpdateWorld()
{
	RectCollider::UpdateWorld();
	image->UpdateWorld();	
}

void Tile::Render()
{
	image->Render();
	RectCollider::Render();
}

void Tile::Collision(Character* character, const Vector2& overlap)
{
    Vector2 pos = character->GetLocalPosition();
    Vector2 tilePos = GetLocalPosition();

    float diffX = pos.x - tilePos.x;
    float diffY = pos.y - tilePos.y;

    if (overlap.x < overlap.y)
    {
        if (diffX > 0)
            pos.x += overlap.x;  // 캐릭터가 타일 오른쪽에 있으니 오른쪽으로 밀기
        else
            pos.x -= overlap.x;  // 캐릭터가 타일 왼쪽에 있으니 왼쪽으로 밀기
    }
    else
    {
        if (diffY > 0)
            pos.y += overlap.y;  // 캐릭터가 타일 위쪽에 있으니 위쪽으로 밀기
        else
            pos.y -= overlap.y;  // 캐릭터가 타일 아래쪽에 있으니 아래쪽으로 밀기
    }

    character->SetLocalPosition(pos);
    character->UpdateWorld();
}



