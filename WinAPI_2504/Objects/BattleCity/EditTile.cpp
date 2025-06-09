#include "Framework.h"

Tile::Tile() : RectCollider(Vector2(TILE_SIZE, TILE_SIZE))
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
    if (!isActive)
        return;
	image->Render();
	//RectCollider::Render();
}

void Tile::Collision(RectCollider* rect, const Vector2& overlap)
{
    if (!isActive)
        return;
    Vector2 pos = rect->GetLocalPosition();
    Vector2 tilePos = GetLocalPosition();

    float diffX = pos.x - tilePos.x;
    float diffY = pos.y - tilePos.y;

    if (overlap.x < overlap.y)
    {
        if (diffX > 0)
            pos.x += overlap.x;  
        else
            pos.x -= overlap.x;  
    }
    else
    {
        if (diffY > 0)
            pos.y += overlap.y;  
        else
            pos.y -= overlap.y;  
    }

    rect->SetLocalPosition(pos);
    rect->UpdateWorld();
}

void Tile::BulletCollision(Bullet* bullet)
{
    bullet->SetActive(false);
}




