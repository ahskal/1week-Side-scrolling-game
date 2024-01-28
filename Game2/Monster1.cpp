#include "stdafx.h"
#include "Mon.h"
#include "Monster1.h"


//#ifndef MONSTER_H
//#define MONSTER_H
//
//// 다른 헤더 파일 및 필요한 내용들...
//
//static bool has_atk = false;  // 정적 변수 선언과 정의
//
//#endif  // MONSTER_H

Monster1::Monster1()
{
	idle = new ObImage(L"AbyssGuardianIdle.png");
	idle->scale.x = idle->imageSize.x * 3.f / 3.0f;
	idle->scale.y = idle->imageSize.y * 3.f;
	idle->maxFrame.x = 3;
	idle->pivot = OFFSET_B;

	move = new ObImage(L"AbyssGuardianCrushMove.png");
	move->scale.x = move->imageSize.x * 3.f / 4.0f;
	move->scale.y = move->imageSize.y * 3.f;
	move->maxFrame.x = 4;
	move->pivot = OFFSET_B;

	attack = new ObImage(L"AbyssGuardianAttack.png");
	attack->scale.x = attack->imageSize.x * 3.f / 8.0f;
	attack->scale.y = attack->imageSize.y * 3.f;
	attack->SetLocalPos(Vector2(10, 0));
	attack->maxFrame.x = 8;
	attack->pivot = OFFSET_B;

	crush = new ObImage(L"AbyssGuardianCrush.png");
	crush->scale.x = crush->imageSize.x * 3.f / 8.0f;
	crush->scale.y = crush->imageSize.y * 3.f;
	crush->maxFrame.x = 8;
	crush->pivot = OFFSET_B;

	col = new ObRect();
	col->scale.x = idle->imageSize.x ;
	col->scale.y = idle->imageSize.y * 2;
	col->isFilled = false;
	col->pivot = OFFSET_B;

	effect = new ObImage(L"BossSwordHitFX0_8x1.png");
	effect->scale.x = effect->imageSize.x * 3.f / 8.0f;
	effect->scale.y = effect->imageSize.y * 3.f;
	effect->maxFrame.x = 8;					
	effect->pivot = OFFSET_RB;

	idle->SetParentRT(*col);
	move->SetParentRT(*col);
	crush->SetParentRT(*col);
	attack->SetParentRT(*col);


	col_Attack = new ObRect();
	col_Attack->pivot = OFFSET_LB;
	col_Attack->SetParentRT(*col);

	col_Crush = new ObRect();
	col_Crush->pivot = OFFSET_B;
	col_Crush->SetParentRT(*col);

	effect->SetParentRT(*col_Crush);

	HpBarScale = Vector2(100.f, 20.f);
	speed = 100;

	Maxhp = 300;
	hp = 300;
	has_Attack = false;
	has_Attack2 = false;
	isDebug = false;
}

Monster1::~Monster1()
{
	delete idle;
	TEXTURE->DeleteTexture(L"AbyssGuardianIdle.png");
	delete move;
	TEXTURE->DeleteTexture(L"AbyssGuardianCrushMove.png");

	delete crush;
	TEXTURE->DeleteTexture(L"AbyssGuardianCrush.png");

	delete attack;
	TEXTURE->DeleteTexture(L"AbyssGuardianAttack.png");

	delete col;
}

void Monster1::Init(Vector2 spawn)
{
	Mon::Init();
	HpBarSetParentRT(col);
	HpBarSetPos(Vector2(-MaxHp->scale.x / 2, col->scale.y + 30));
	col->SetWorldPos(spawn);
	M_State = State::IDLE;
}

void Monster1::Update()
{
	Hp->Update();
	MaxHp->Update();
	if (is_atk == false && is_atk2 == false) {
		Pattern();
	}

	col->Update();
	idle->Update();
	move->Update();
	crush->Update();
	attack->Update();
	effect->Update();
	col_Attack->Update();
	col_Crush->Update();
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

	if (TIMER->GetTick(timer, 3.0f)) {
		if ((M_State == State::ATTACK || M_State == State::CRUSH) && attack->frame.x == 0) {
			M_State = State::IDLE;
			is_atk = false;
			is_atk2 = false;
			has_Attack = false;
			has_Attack2 = false;
		}
	}
	if (has_Attack) {
		col_Attack->scale.x = col->scale.x/1.5;
		col_Attack->scale.y = col->scale.y;
	}
	else {
		col_Attack->scale.x = 0;
		col_Attack->scale.y = 0;
	}
	if (has_Attack2) {
		col_Crush->scale.x = col->scale.x *1.3;
		col_Crush->scale.y = col->scale.y;
	}
	else {
		col_Crush->scale.x = 0;
		col_Crush->scale.y = 0;
	}
}



void Monster1::LateUpdate()
{
	switch (M_State) {
	case State::IDLE:
		idle->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		break;
	case State::MOVE:
		move->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		break;
	case State::CRUSH:
		Attack2();
		break;
	case State::ATTACK:
		Attack();
		break;
	}
}

void Monster1::Render()
{
	Hp->Render();
	MaxHp->Render();
	
	switch (M_State) {
	case State::IDLE:
		idle->Render();
		break;
	case State::MOVE:
		move->Render();
		break;
	case State::CRUSH:
		//col_Crush->Render();
		crush->Render();
		effect->Render();
		break;
	case State::ATTACK:
		//col_Attack->Render();
		attack->Render();
		break;
	}
	if (isDebug) {
		col->Render();
		col_Attack->Render();
		col_Crush->Render();
	}
	
}

void Monster1::Pattern()
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
		if (!(is_atk && is_atk2)) {
			if (RANDOM->Int() == 0) { // RANDOM->Int()가 0일 때 1번 공격 실행
				M_State = State::ATTACK;
				is_atk = true;
				is_atk2 = false; // 2번 공격 비활성화
			}
			else { // RANDOM->Int()가 1일 때 2번 공격 실행
				M_State = State::CRUSH;
				is_atk = false; // 1번 공격 비활성화
				is_atk2 = true;
			}
		}
	}
	else {
		M_State = State::IDLE;
		is_atk = false; // 1번 공격 비활성화
		is_atk2 = false; // 2번 공격 비활성화
	}
}
void Monster1::Attack()
{
	ImGui::Text("is fream : %d", attack->frame.x);
	if (M_State == State::ATTACK && is_atk) {
		static int  A = 0;
		if (A == 0) {
			attack->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
		}
		A++;
		col_Attack->Update();
		if (attack->frame.x > 3) {
			has_Attack = true;
		}
		else {
			has_Attack = false;
		}
		if (attack->frame.x + 1 == attack->maxFrame.x) {

			has_Attack = false;
			is_atk = false;
			is_atk2 = false;
			M_State = State::IDLE;
			A = 0;
			return;
		}
	}


}

void Monster1::Attack2()
{
	if (M_State == State::CRUSH && is_atk2) {
		static int  A = 0;
		if (A == 0) {
			crush->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
			effect->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
		}
		A++;
		col_Crush->Update();
		if (crush->frame.x > 4) {
			has_Attack2 = true;
		}
		else {
			has_Attack2 = false;
		}
		if (crush->frame.x + 1 == crush->maxFrame.x) {
			has_Attack2 = false;
			is_atk = false;
			is_atk2 = false;
			M_State = State::IDLE;
			A = 0;
			return;
		}
	}

}

