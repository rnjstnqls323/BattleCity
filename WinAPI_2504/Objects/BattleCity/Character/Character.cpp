#include "Framework.h"

Character::Character():RectCollider({20,20})
{
	animation = new CharacterAnimation();
	animationTransform = new Transform();

	animationTransform->SetParent(this);
	animationTransform->UpdateWorld();

	worldBuffer = new MatrixBuffer();
}

Character::~Character()
{
	delete animation;
	delete animationTransform;
	delete worldBuffer;
}

void Character::Update()
{
	UpdateAnimation();

	Move();
	UpdateWorld();
	animationTransform->UpdateWorld();
}

void Character::Render()
{
	if (isDead)
		return;
	else
	{
		worldBuffer->Set(animationTransform->GetWorld());
		worldBuffer->SetVS(0);

		animation->Render(curState);
	}
}

void Character::ResolveBallCollision()
{
	stat.life--;
	isDead = true;
	curState = Dead;
}

void Character::Fire()
{
	if (Input::Get()->IsKeyDown(VK_SPACE))
	{
		switch (curState)
		{
		case Character::Idle:
			BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Right());
			break;
		case Character::GoToUp:
			BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Up());
			break;
		case Character::GoToDown:
			BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Down());
			break;
		case Character::GoToLeft:
			BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Left());
			break;
		case Character::GoToRight:
			BulletManager::Get()->Fire(this->GetLocalPosition(), Vector2::Right());
			break;
		}

	}
}

void Character::Move()
{
	Vector2 curPos = GetLocalPosition();
	isKeyPress = false;

	if (Input::Get()->IsKeyPress(VK_UP))
	{
		isKeyPress = true;
		Vector2 nextPos = curPos + Vector2::Up() * DELTA * speed;
		if (!IsCharacterOut(nextPos))
			Translate(Vector2::Up() * DELTA * speed);
		curState = GoToUp;
	}
	else if (Input::Get()->IsKeyPress(VK_DOWN))
	{
		isKeyPress = true;
		Vector2 nextPos = curPos + Vector2::Down() * DELTA * speed;
		if (!IsCharacterOut(nextPos))
			Translate(Vector2::Down() * DELTA * speed);
		curState = GoToDown;
	}
	else if (Input::Get()->IsKeyPress(VK_LEFT))
	{
		isKeyPress = true;
		Vector2 nextPos = curPos + Vector2::Left() * DELTA * speed;
		if (!IsCharacterOut(nextPos))
			Translate(Vector2::Left() * DELTA * speed);
		curState = GoToLeft;
	}
	else if (Input::Get()->IsKeyPress(VK_RIGHT))
	{
		isKeyPress = true;
		Vector2 nextPos = curPos + Vector2::Right() * DELTA * speed;
		if (!IsCharacterOut(nextPos))
			Translate(Vector2::Right() * DELTA * speed);
		curState = GoToRight;
	}
}

void Character::UpdateAnimation()
{

	switch (curState)
	{
	case Character::Idle:
		isDead = false;
		animation->Update(Idle);
		break;
	case Character::GoToUp:
		if (isKeyPress)
			animation->Update(GoToUp);
		break;
	case Character::GoToDown:
		if (isKeyPress)
			animation->Update(GoToDown);
		break;
	case Character::GoToLeft:
		if (isKeyPress)
			animation->Update(GoToLeft);
		break;
	case Character::GoToRight:
		if (isKeyPress)
			animation->Update(GoToRight);
		break;
	case Character::Dead:
		isDead = true;
		animation->Update(Dead);
		//죽으면 애니메이션 재생하고 아예 사라져버려야되는디 팔라독때 어케했는지 참고하자
		break;
	}
}

bool Character::IsCharacterOut(Vector2 pos)
{
	float minY = SCREEN_HEIGHT - TILE_NUM * TILE_SIZE;
	float maxX = SCREEN_WIDTH - TILE_NUM * TILE_SIZE;

	if (pos.x < 0)
		return true;
	if (pos.y < minY)
		return true;
	if (pos.x > maxX)
		return true;
	if (pos.y > SCREEN_HEIGHT)
		return true;
	return false;
}
