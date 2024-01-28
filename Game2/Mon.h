#pragma once
enum class State
{
	IDLE,
	MOVE,
	ATTACK,
	CRUSH
};

enum class Pattern {
	TAGET_IDLE,
	TAGET_MOVE,
	TAGET_ATTACK,
	TAGET_ATTACK2,
};

class Mon
{
protected:

	
	ObRect* col;
	ObRect* MaxHp;

	Vector2 HpBarScale = Vector2(1, 1);

	Pattern M_Pattern;

	Vector2 TagetPos;

	float speed;

	float timer = 0;

	
	float overPower;

	

public:
	State   M_State;


	ObRect* Hp;
	float hp;
	float Maxhp;
	
	bool is_atk;
	bool is_atk2;
	bool is_move; 

	bool isDebug;


public:
	Mon();
	~Mon();

	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Pattern();
	
	void SetTagetPos(Vector2 pos) { TagetPos = pos; };

	void HpBarSetParentRT(GameObject* obj);
	void HpBarSetPos(Vector2 pos);

	void Damage(int damage) {
		if (overPower <= 0.0f)
		{
			hp -= damage;
			Hp->scale.x = hp /Maxhp * MaxHp->scale.x;
			overPower = 0.5f;
		}
	}

	Mon* CreateClone() { return new Mon(*this); }
	ObRect* GetCol() { return col; };



};