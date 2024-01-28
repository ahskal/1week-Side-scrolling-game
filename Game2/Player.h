#pragma once

class Player : public ObRect
{
private:
	enum class AdventurerState {
		IDLE,
		RUN,
		JUMP,
		SLIDE,
		DROP,
		ATK1,
		ATK2,
		ATK3,
		DIE
	};
	ObImage* idle;
	ObImage* run;
	ObImage* jump;
	ObImage* slide;
	ObImage* atk1;
	ObImage* atk2;
	ObImage* atk3;
	ObImage* die;

	
	

	AdventurerState state;

	int atkCount;

	bool aniPlay1;
	bool aniPlay2;
	bool aniPlay3;

public:
	bool isEnd;
	bool is_Attack;

	ObRect* Hp;
	ObRect* MaxHp;

	Vector2 HpBarScale = Vector2(1, 1);

	float hp;
	float Maxhp;

	ObRect* c_atk1;
	ObRect* col;
	GameObject* obj;

	bool isjump;
	bool isgravity;
	float jumpPower;
	float gravity;

	float speed;
	int Atk = 50;

	float overPower;

	bool isDebug;

public:

	Player();
	~Player();

	void Init(Vector2 spawn);
	void Update();
	void LateUpdate();
	void Render();
	void SetState(int A) { state = AdventurerState(A); };


	void HpBarSetParentRT(GameObject* obj);
	void HpBarSetPos(Vector2 pos);

	void Damage(int damage) {
		if (overPower <= 0.0f)
		{
			hp -= damage;
			if (hp < 0) {
				hp = 0;
				state = AdventurerState::DIE;
			}
			Hp->scale.x = hp / Maxhp * MaxHp->scale.x;
			overPower = 1.5f;
		}
	}



//	const Vector2 GetPos() { return col->GetWorldPos(); };
};

