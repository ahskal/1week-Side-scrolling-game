#include "stdafx.h"
#include "Adventurer.h"

Adventurer::Adventurer()
{
	idle = new ObImage(L"adventurer-idle-00_4x1.png");
	idle->scale.x = idle->imageSize.x * 3.0f / 4.0f;
	idle->scale.y = idle->imageSize.y * 3.0f;
	idle->maxFrame.x = 4;
	idle->pivot = OFFSET_B;

	jump = new ObImage(L"adventurer-jump-00_4x1.png");
	jump->scale.x = jump->imageSize.x * 3.0f / 4.0f;
	jump->scale.y = jump->imageSize.y * 3.0f;
	jump->maxFrame.x = 4;
	jump->pivot = OFFSET_B;

	run = new ObImage(L"adventurer-run-00_6x1.png");
	run->scale.x = run->imageSize.x * 3.0f / 6.0f;
	run->scale.y = run->imageSize.y * 3.0f;
	run->maxFrame.x = 6;
	run->pivot = OFFSET_B;

	slide = new ObImage(L"adventurer-slide-00_2x1.png");
	slide->scale.x = slide->imageSize.x * 3.0f / 2.0f;
	slide->scale.y = slide->imageSize.y * 3.0f;
	slide->maxFrame.x = 2;
	slide->pivot = OFFSET_B;

	col = new ObRect();
	col->scale.x = run->imageSize.x / 2;
	col->scale.y = run->imageSize.y;
	col->isFilled = false;
	col->pivot = OFFSET_B;
	col->hasAxis = true;

	idle->SetParentRT(*col);
	jump->SetParentRT(*col);
	run->SetParentRT(*col);
	slide->SetParentRT(*col);
}

Adventurer::~Adventurer()
{
	delete idle;
	delete jump;
	delete run;
	delete col;
}

void Adventurer::Init()
{
	col->SetWorldPos(Vector2(-300.0f, -200.0f));
	state = AdventurerState::IDLE;
	//run->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	isjump = false;
}

void Adventurer::Update()
{
	if (state == AdventurerState::IDLE) {
		col->scale.y = idle->scale.y;
		if (INPUT->KeyDown(VK_UP))
		{
			state = AdventurerState::JUMP;
			gravity = -200.0f;
			isjump = true;
			jump->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
		//run -> spin
		if (INPUT->KeyPress(VK_LEFT)) {
			col->rotation.y = PI;
			state = AdventurerState::RUN;
			run->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
		if (INPUT->KeyPress(VK_RIGHT))
		{
			col->rotation.y = 0;
			state = AdventurerState::RUN;
			run->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
	}
	if (state == AdventurerState::RUN) {
		col->scale.y = run->scale.y;

		//run -> jump
		if (INPUT->KeyDown(VK_UP))
		{
			state = AdventurerState::JUMP;
			gravity = -200.0f;
			isjump = true;
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
		
		//run -> slide
	
		if (INPUT->KeyDown(VK_DOWN))
		{
			state = AdventurerState::SLIDE;
		}
	}
	else if (state == AdventurerState::JUMP) {
		col->scale.y = jump->scale.y;
		gravity += 300.0f * DELTA;
		col->MoveWorldPos(DOWN * gravity * DELTA);


		//jump -> run
		if (col->GetWorldPos().y < -200.0f)
		{
			col->SetWorldPosY(-200.0f);
			state = AdventurerState::IDLE;
			isjump = false;
		}
	}
	else if (state == AdventurerState::SLIDE) {
		slide->ChangeAnim(ANIMSTATE::LOOP, 0.1f);

		//slide -> run
		if (INPUT->KeyUp(VK_DOWN))
		{
			state = AdventurerState::IDLE;
		}
	}
	//else if (state == AdventurerState::DROP) {
	//
	//	col->MoveWorldPos(DOWN * 200.f * DELTA);
	//}


	col->Update();
	idle->Update();
	run->Update();
	jump->Update();
	slide->Update();
}

void Adventurer::Render()
{
	col->Render();
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
	default:
		run->Render();
		break;
	}

}
