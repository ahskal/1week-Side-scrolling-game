#include "stdafx.h"
#include "Mon.h"


Mon::Mon()
{
	col = new ObRect();
	Hp = new ObRect();
	MaxHp = new ObRect();

	Hp->scale = HpBarScale;
	MaxHp->scale = HpBarScale;

	Hp->color.y = 1;
	MaxHp->isFilled = false;

	Hp->scale.x = 100;
	Hp->scale.y = 20;
	MaxHp->scale.x = 100;
	MaxHp->scale.y = 20;

	Hp->color.y = 1.f;
	MaxHp->isFilled = false;

	Hp->pivot = OFFSET_L;
	MaxHp->pivot = OFFSET_L;

	speed = 100;

	is_atk = false;
	is_atk2 = false;
	is_move = false;
}

Mon::~Mon()
{
	delete Hp;
	delete MaxHp;
}

void Mon::Init()
{
}

void Mon::Update()
{
	Hp->Update();
	MaxHp->Update();
	if (is_atk == false) {
		Pattern();
	}
}

void Mon::LateUpdate()
{

}

void Mon::Render()
{
	Hp->Render();
	MaxHp->Render();
}


void Mon::HpBarSetParentRT(GameObject* obj)
{
	Hp->SetParentT(*obj);
	MaxHp->SetParentT(*obj);
}

void Mon::HpBarSetPos(Vector2 pos)
{
	Hp->SetLocalPos(pos);
	MaxHp->SetLocalPos(pos);
}


void Mon::Pattern()
{
	float Length = (TagetPos - col->GetWorldPos()).Length();

	Vector2 direction = Vector2(TagetPos.x - col->GetWorldPos().x, 0);
	direction.Normalize();

	if (direction == LEFT) {
		col->rotation.y = PI;
	}
	else {
		col->rotation.y = 0;
	}

	
	if (Length < 400 && Length >= 100) {
		M_State = State::MOVE;
		col->MoveWorldPos(direction * speed * DELTA);
	}
	else if (Length < 100) {
		M_State = State::ATTACK;
		is_atk = true;
	}
	else {
		M_State = State::IDLE;
	}
}
