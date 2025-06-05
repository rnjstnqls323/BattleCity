#include "Framework.h"

Character::Character()
{
	animation = new CharacterAnimation();
	animationTransform = new Transform();

	animationTransform->SetParent(this);
	animationTransform->UpdateWorld();
}

Character::~Character()
{
	delete animation;
	delete animationTransform;
}

void Character::Update()
{
	UpdateAnimation();
	Move();
	UpdateWorld();
}

void Character::Render()
{
	if (isDead)
		return;
	else
		animation->Render(curState);
}

void Character::Move()
{
	if (Input::Get()->IsKeyPress(VK_UP))
	{
		Translate(Vector2::Up() * DELTA * speed);
		curState = GoToUp;
	}
	else if (Input::Get()->IsKeyPress(VK_DOWN))
	{
		Translate(Vector2::Down() * DELTA * speed);
		curState = GoToDown;
	}
	else if (Input::Get()->IsKeyPress(VK_LEFT))
	{
		Translate(Vector2::Left() * DELTA * speed);
		curState = GoToLeft;
	}
	else if (Input::Get()->IsKeyPress(VK_RIGHT))
	{
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
