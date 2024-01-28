#pragma once
class Monster2 : public Mon
{
private:

	ObImage* idle;
	ObImage* move;
	ObImage* attack;

	bool has_Attack;


public:

	float atk = 20;
	ObRect* col_Attack;
	

	Monster2();
	~Monster2();
	void Init(Vector2 spawn);
	void Update();
	void LateUpdate();
	void Render();

	void Attack();




};

