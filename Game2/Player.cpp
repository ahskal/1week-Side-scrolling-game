#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	idle = new ObImage(L"adventurer-idle.png");
	idle->scale.x = idle->imageSize.x * 3.0f / 4.0f;
	idle->scale.y = idle->imageSize.y * 3.0f;
	idle->maxFrame.x = 4;
	idle->pivot = OFFSET_B;

	jump = new ObImage(L"adventurer-jump.png");
	jump->scale.x = jump->imageSize.x * 3.0f / 4.0f;
	jump->scale.y = jump->imageSize.y * 3.0f;
	jump->maxFrame.x = 4;
	jump->pivot = OFFSET_B;

	run = new ObImage(L"adventurer-run.png");
	run->scale.x = run->imageSize.x * 3.0f / 6.0f;
	run->scale.y = run->imageSize.y * 3.0f;
	run->maxFrame.x = 6;
	run->pivot = OFFSET_B;

	slide = new ObImage(L"adventurer-slide.png");
	slide->scale.x = slide->imageSize.x * 3.0f / 2.0f;
	slide->scale.y = slide->imageSize.y * 3.0f;
	slide->maxFrame.x = 2;
	slide->pivot = OFFSET_B;

	atk1 = new ObImage(L"adventurer-attack-1.png");
	atk1->scale.x = atk1->imageSize.x * 3.0f / 5.0f;
	atk1->scale.y = atk1->imageSize.y * 3.0f;
	atk1->maxFrame.x = 5;
	atk1->pivot = OFFSET_B;

	atk2 = new ObImage(L"adventurer-attack-2.png");
	atk2->scale.x = atk2->imageSize.x * 3.0f / 6.0f;
	atk2->scale.y = atk2->imageSize.y * 3.0f;
	atk2->maxFrame.x = 6;
	atk2->pivot = OFFSET_B;

	atk3 = new ObImage(L"adventurer-attack-3.png");
	atk3->scale.x = atk3->imageSize.x * 3.0f / 6.0f;
	atk3->scale.y = atk3->imageSize.y * 3.0f;
	atk3->maxFrame.x = 6;
	atk3->pivot = OFFSET_B;

	die = new ObImage(L"adventurer-die-00_7x1.png");
	die->scale.x = die->imageSize.x * 3.0f / 7.0f;
	die->scale.y = die->imageSize.y * 3.0f;
	die->maxFrame.x = 7;
	die->pivot = OFFSET_B;


	isEnd = false;



	c_atk1 = new ObRect();
	c_atk1->pivot = OFFSET_LB;

	col = new ObRect();
	col->SetWorldPos(Vector2(-500, 200));
	col->scale.x = idle->imageSize.x / 2;
	col->scale.y = idle->imageSize.y;
	col->isFilled = false;
	col->pivot = OFFSET_B;

	obj = new GameObject();
	obj->SetParentRT(*col);
	obj->SetLocalPos(Vector2(-50, 70));

	idle->SetParentRT(*col);
	jump->SetParentRT(*col);
	run->SetParentRT(*col);
	slide->SetParentRT(*col);
	atk1->SetParentRT(*col);
	atk2->SetParentRT(*col);
	atk3->SetParentRT(*col);
	c_atk1->SetParentRT(*col);
	die->SetParentRT(*col);

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

	atkCount = 0;

	aniPlay1 = false;
	aniPlay2 = false;
	aniPlay3 = false;

	HpBarScale = Vector2(100.f, 20.f);
	speed = 300;
	Maxhp = 200;
	hp = 200;
	overPower = 0;

	isDebug = false;

}

Player::~Player()
{
	delete col;
}

void Player::Init(Vector2 spawn)
{
	HpBarSetParentRT(col);
	HpBarSetPos(Vector2(-MaxHp->scale.x / 2, col->scale.y * 4));
	col->SetWorldPos(spawn);
	state = AdventurerState::IDLE;
	isjump = false;
	isgravity = false;
	is_Attack = false;
}

void Player::Update()
{
	col->Update();
	obj->Update();


	Hp->Update();
	MaxHp->Update();

	idle->Update();
	run->Update();
	jump->Update();
	slide->Update();
	atk1->Update();
	atk2->Update();
	atk3->Update();
	c_atk1->Update();
	die->Update();
	if (overPower > 0.0f)
	{
		overPower -= DELTA;
		//                          -1 ~ 0
		col->color.w = RANDOM->Float(0.0f, 0.5f);
		idle->color.w = RANDOM->Float(0.0f, 0.5f);
		jump->color.w = RANDOM->Float(0.0f, 0.5f);
		run->color.w = RANDOM->Float(0.0f, 0.5f);
		slide->color.w = RANDOM->Float(0.0f, 0.5f);
		atk1->color.w = RANDOM->Float(0.0f, 0.5f);
		atk2->color.w = RANDOM->Float(0.0f, 0.5f);
		atk3->color.w = RANDOM->Float(0.0f, 0.5f);
	}
	else
	{
		col->color.w = 0.5f;
		idle->color.w = 0.5f;
		jump->color.w = 0.5f;
		run->color.w = 0.5f;
		slide->color.w = 0.5f;
		atk1->color.w = 0.5f;
		atk2->color.w = 0.5f;
		atk3->color.w = 0.5f;
	}

	if (is_Attack) {
		c_atk1->scale.x = col->scale.x + 25;
		c_atk1->scale.y = col->scale.y;
	}
	else {
		c_atk1->scale.x = 0;
		c_atk1->scale.y = 0;
	}

}

void Player::LateUpdate()
{
	switch (state)
	{
	case AdventurerState::IDLE:
		idle->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		col->scale.y = idle->scale.y;
		if (INPUT->KeyDown(VK_SPACE))
		{
			state = AdventurerState::JUMP;
			gravity = -300.0f;
			isjump = true;
			isgravity = true;
			jump->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
		//run_L
		if (INPUT->KeyPress(VK_LEFT))
		{
			col->rotation.y = PI;
			state = AdventurerState::RUN;
			run->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
		//run_R
		if (INPUT->KeyPress(VK_RIGHT))
		{
			col->rotation.y = 0;
			state = AdventurerState::RUN;
			run->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
		break;
	case AdventurerState::RUN:
		col->scale.y = run->scale.y;

		if (INPUT->KeyDown(VK_SPACE))
		{
			state = AdventurerState::JUMP;
			gravity = -300.0f;
			isjump = true;
			isgravity = true;
			jump->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
		if (INPUT->KeyUp(VK_LEFT))
		{
			state = AdventurerState::IDLE;
		}
		if (INPUT->KeyUp(VK_RIGHT))
		{
			state = AdventurerState::IDLE;
		}
		if (INPUT->KeyDown(VK_DOWN))
		{
			state = AdventurerState::SLIDE;
		}

		break;
	case AdventurerState::JUMP:
		col->scale.y = jump->scale.y;

		gravity += 350.0f * DELTA;
		col->MoveWorldPos(DOWN * gravity * DELTA);

		break;
	case AdventurerState::SLIDE:
		slide->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		col->scale.y = slide->scale.y;
		speed = 400.f;
		//slide -> run
		if (INPUT->KeyUp(VK_DOWN))
		{
			state = AdventurerState::IDLE;
			speed = 300.f;
		}
		break;
	case AdventurerState::ATK1:

		if (atk1->frame.x > 1) {
			is_Attack = true;
		}
		else {
			is_Attack = false;
		}

		if (atk1->frame.x + 1 == atk1->maxFrame.x) {
			aniPlay1 = false;
			is_Attack = false;
			state = AdventurerState::IDLE;
		}
		break;
	case AdventurerState::ATK2:
		if (atk2->frame.x > 1) {
			is_Attack = true;
		}
		else {
			is_Attack = false;
		}

		if (atk2->frame.x + 1 == atk2->maxFrame.x) {
			is_Attack = false;
			aniPlay2 = false;

			state = AdventurerState::IDLE;
		}
		break;
	case AdventurerState::ATK3:
		if (atk2->frame.x > 1) {
			is_Attack = true;
		}
		else {
			is_Attack = false;
		}

		if (atk3->frame.x + 1 == atk3->maxFrame.x) {
			is_Attack = false;
			aniPlay3 = false;
			state = AdventurerState::IDLE;
		}
		break;
	case AdventurerState::DIE:
		static int a = 0;
		if (a == 0) {
			die->ChangeAnim(ANIMSTATE::ONCE, 0.4f);
		}
		a++;
		break;
	}

	//else if (isgravity){
	//
	//	gravity -= 300.0f * DELTA;
	//	col->MoveWorldPos(DOWN * gravity * DELTA);
	//}
	if (state != AdventurerState::DIE) {
		if (INPUT->KeyDown(VK_F1)) {
			isDebug = !isDebug;
		}
		if (INPUT->KeyDown('Q')) {
			hp = Maxhp;
			Hp->scale.x = MaxHp->scale.x;
		}
		if (INPUT->KeyPress(VK_LEFT))
		{
			col->MoveWorldPos(LEFT * speed * DELTA);
		}
		if (INPUT->KeyPress(VK_RIGHT))
		{
			col->MoveWorldPos(RIGHT * speed * DELTA);
		}
		if (INPUT->KeyDown('Z')) {
			if (!(aniPlay1 or aniPlay2 or aniPlay3) && !isjump) {

				switch (atkCount) {
				case 0:
					aniPlay1 = true;
					state = AdventurerState::ATK1;
					atk1->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
					break;
				case 1:
					aniPlay2 = true;
					state = AdventurerState::ATK2;
					atk2->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
					break;
				case 2:
					aniPlay3 = true;
					state = AdventurerState::ATK3;
					atk3->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
					break;
				}
				atkCount++;
				if (atkCount == 3) {
					atkCount = 0;
				}
			}
		}
		if (!(aniPlay1 or aniPlay2 or aniPlay3) && !isjump) {
			is_Attack = false;
		}
	}
	else {
		isEnd = true;		
	}

}

void Player::Render()
{
	Hp->Render();
	MaxHp->Render();
	switch (state)
	{
	case AdventurerState::IDLE:
		idle->Render();
		break;
	case AdventurerState::RUN:
		run->Render();
		break;
	case AdventurerState::JUMP:
		jump->Render();
		break;
	case AdventurerState::SLIDE:
		slide->Render();
		break;
	case AdventurerState::ATK1:

		atk1->Render();
		break;
	case AdventurerState::ATK2:

		atk2->Render();
		break;
	case AdventurerState::ATK3:

		atk3->Render();
		break;
	case AdventurerState::DIE:
		die->Render();
		
		break;
	}


	if (isDebug) {
		col->Render();
		c_atk1->Render();
	}

}

void Player::HpBarSetParentRT(GameObject* obj)
{
	Hp->SetParentT(*obj);
	MaxHp->SetParentT(*obj);
}

void Player::HpBarSetPos(Vector2 pos)
{
	Hp->SetLocalPos(pos);
	MaxHp->SetLocalPos(pos);
}