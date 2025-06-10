#pragma once

struct CharacterStat
{
	int life = 1;
	string tag = "character";
	Vector2 spawnPoint;
};

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
		isDead = dead;
		isDead ? curState = Dead : curState = Idle;
	}

	void ResolveBallCollision();

	CharacterStat GetStat() { return stat; }
	
	
protected:
	virtual void Fire();
	virtual void Move();
	virtual void CreateAnimation() = 0;
	void UpdateAnimation();
	bool IsCharacterOut(Vector2 pos);

protected:
	bool isDead = false;
	bool isKeyPress = false;

	float speed = 100.0f;

	MatrixBuffer* worldBuffer;
	CharacterState curState = Idle;
	CharacterAnimation* animation;
	Transform* animationTransform;

	CharacterStat stat;
	
};