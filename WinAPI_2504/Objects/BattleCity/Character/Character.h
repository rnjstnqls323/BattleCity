#pragma once


class Character :public RectCollider
{
protected:
	enum CharacterState
	{
		Idle, GoToUp, GoToDown, GoToLeft, GoToRight, Dead, CharacterStateEnd
	};
public:
	Character();
	~Character();

	virtual void Update();
	virtual void Render();

	bool IsDead() { return isDead; }
	void SetIsDead(bool dead) 
	{ 
		isDead ? curState = Dead : curState = Idle;
	}

	// ÃÑ¾Ë ½î´Â°Å ±¸ÇöÇÏ±â 

protected:
	virtual void Move();
	virtual void CreateAnimation() = 0;
	void UpdateAnimation();

protected:
	bool isDead = false;
	bool isKeyPress = false;

	float speed = 100.0f;

	CharacterState curState = Idle;
	CharacterAnimation* animation;
	Transform* animationTransform;
};