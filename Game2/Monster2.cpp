#include "stdafx.h"
#include "Mon.h"
#include "Monster2.h"

Monster2::Monster2()
{
	idle = new ObImage(L"BigWhiteSkelIdle.png");
	idle->scale.x = idle->imageSize.x * 2.f / 6.0f;
	idle->scale.y = idle->imageSize.y * 2.f;
	idle->maxFrame.x = 6;
	idle->pivot = OFFSET_B;

	move = new ObImage(L"BigWhiteSkelMove.png");
	move->scale.x = move->imageSize.x * 2.f / 6.0f;
	move->scale.y = move->imageSize.y * 2.f;
	move->maxFrame.x = 6;
	move->pivot = OFFSET_B;

	attack = new ObImage(L"BigWhiteSkelAttack.png");
	attack->scale.x = attack->imageSize.x * 2.f / 12.0f;
	attack->scale.y = attack->imageSize.y * 2.f;
	attack->SetLocalPos(Vector2(35, 0));
	attack->maxFrame.x = 12;
	attack->pivot = OFFSET_B;

	col = new ObRect();
	col->scale.x = idle->imageSize.x / 4;
	col->scale.y = idle->imageSize.y * 2;
	col->isFilled = false;
	col->pivot = OFFSET_B;

	idle->SetParentRT(*col);
	move->SetParentRT(*col);
	attack->SetParentRT(*col);

	col_Attack = new ObRect();
	col_Attack->pivot = OFFSET_LB;
	col_Attack->SetParentRT(*col);

	is_atk = false;

	HpBarScale = Vector2(100.f, 20.f);

	Maxhp = 150;
	hp = 150;
	has_Attack = false;
	isDebug = false;

}

Monster2::~Monster2()
{
	delete idle;
	TEXTURE->DeleteTexture(L"BigWhiteSkelIdle.png");
	delete move;
	TEXTURE->DeleteTexture(L"BigWhiteSkelMove.png");

	delete attack;
	TEXTURE->DeleteTexture(L"BigWhiteSkelAttack.png");

	delete col;
}

void Monster2::Init(Vector2 spawn)
{
	Mon::Init();
	HpBarSetParentRT(col);
	HpBarSetPos(Vector2(-MaxHp->scale.x / 2, col->scale.y + 30));
	col->SetWorldPos(spawn);
	M_State = State::IDLE;
}

void Monster2::Update()
{
	Mon::Update();
	col->Update();
	idle->Update();
	move->Update();
	attack->Update();
	col_Attack->Update();

	if (overPower > 0.0f)
	{
		overPower -= DELTA;
		//                          -1 ~ 0
		col->color.w = RANDOM->Float(0.0f, 0.5f);
		idle->color.w = RANDOM->Float(0.0f, 0.5f);
	}
	else
	{
		col->color.w = 0.5f;
		idle->color.w = 0.5f;
	}
	if (TIMER->GetTick(timer, 5.0f)) {
		if (M_State == State::ATTACK && attack->frame.x == 0) {
			M_State = State::IDLE;
			is_atk = false;
			is_atk2 = false;
			has_Attack = false;
		}
	}
	
	if (has_Attack) {
		col_Attack->scale.x = col->scale.x + 30;
		col_Attack->scale.y = col->scale.y;
	}
	else {
		col_Attack->scale.x = 0;
		col_Attack->scale.y = 0;
	}

}

void Monster2::LateUpdate()
{
	switch (M_State) {
	case State::IDLE:
		idle->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		break;
	case State::MOVE:
		move->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		break;
	case State::ATTACK:
		Attack();
		break;
	}

}

void Monster2::Render()
{
	Mon::Render();
	switch (M_State) {
	case State::IDLE:
		idle->Render();
		break;
	case State::MOVE:
		move->Render();
		break;
	case State::ATTACK:
		attack->Render();
		break;
	}

	if (isDebug) {
		col->Render();
		col_Attack->Render();
	}
}

void Monster2::Attack()
{
	ImGui::Text("is fream : %d", attack->frame.x);
	if (M_State == State::ATTACK && is_atk) {
		static int  A = 0;
			if (A == 0) {
				attack->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
			}
		A++;
			if (attack->frame.x > 1 && attack->frame.x < 6) {
				has_Attack = true;
			}
			else {
				has_Attack = false;
			}
		if (attack->frame.x + 1 == attack->maxFrame.x) {
			has_Attack = false;
			is_atk = false;
			M_State = State::IDLE;
			A = 0;
			return;
		}
	}
	
}
