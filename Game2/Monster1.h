#pragma once
class Monster1 : public Mon
{
private:

	ObImage* idle;
	ObImage* move;
	ObImage* attack;
	ObImage* crush;

	ObImage* effect;


	

	float Crush_timer;


	float timer2 = 0;

	bool has_Attack;
	bool has_Attack2;


public:

	float atk = 30;
	float atk2 = 50;
	ObRect* col_Attack;
	ObRect* col_Crush;

	Monster1();
	~Monster1();

	void Init(Vector2 spawn);
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Pattern()override;
	void Attack();
	void Attack2();

};

