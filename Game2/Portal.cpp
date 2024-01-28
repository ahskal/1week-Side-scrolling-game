#include "stdafx.h"
#include "Mon.h"
#include "Portal.h"

Portal::Portal()
{
	portal = new ObImage(L"LavaArea.png");
	portal->scale.x = portal->imageSize.x * 2.0f / 11.0f;
	portal->scale.y = portal->imageSize.y * 2.0f;
	portal->maxFrame.x = 11;

	Effect = new ObImage(L"BerserkFX0_7x1.png");
	Effect->scale.x = Effect->imageSize.x * 3.0f / 7.0f;
	Effect->scale.y = Effect->imageSize.y * 3.0f;
	Effect->maxFrame.x = 7;

	portal->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	Effect->ChangeAnim(ANIMSTATE::LOOP, 0.1f);


	col = new ObRect();
	col->scale.x = portal->imageSize.x * 2.0f / 11.0f;
	col->scale.y = portal->imageSize.y * 2.0f;
	col->isFilled = false;

	portal->SetParentRT(*col);
	Effect->SetParentRT(*col);

	HpBarScale = Vector2(100.f, 20.f);
	Maxhp = 500;
	hp = 500;

	isDebug = false;
}

Portal::~Portal()
{
}

void Portal::Init(Vector2 spawn)
{
	col->SetWorldPos(spawn);
	HpBarSetParentRT(col);
	HpBarSetPos(Vector2(-MaxHp->scale.x / 2, col->scale.y + 30));

}

void Portal::Update()
{
	Hp->Update();
	MaxHp->Update();
	col->Update();
	portal->Update();
	Effect->Update();



	if (INPUT->KeyDown(VK_F1)) {
		isDebug = !isDebug;
	}

	if (overPower > 0.0f)
	{
		overPower -= DELTA;
		//                          -1 ~ 0
		col->color.w = RANDOM->Float(0.0f, 0.5f);
	}
	else
	{
		col->color.w = 0.5f;
	}
}

void Portal::LateUpdate()
{


}

void Portal::Render()
{
	Hp->Render();
	MaxHp->Render();
	portal->Render();
	Effect->Render();
	if (isDebug)
		col->Render();
}