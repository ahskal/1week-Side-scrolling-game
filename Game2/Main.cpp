#include "stdafx.h"
#include "Adventurer.h"
#include "Player.h"
#include "Tile.h"
#include "ImageUi.h"
#include "Map.h"
#include "Collision.h"
#include "Mon.h"
#include "Monster1.h"
#include "Monster2.h"
#include "BackGround.h"
#include "Portal.h"
#include "Main.h"

Main::Main()
{
	scale = 1.0f;

	TileUi = new ImageUi;
	TileUi->Init(L"TileMap1.png", Int2(4, 9));
	TileUi->Init(L"TileMap2.png", Int2(6, 12));
	TileUi->Init(L"TileMap3.png", Int2(6, 8));
	TileUi->Init(L"TileMap4.png", Int2(5, 16));
	TileUi->Init(L"TileMap5.png", Int2(7, 18));
	TileUi->Init(L"BlackSmith_11x9.png", Int2(11, 9));

	tiles = new Tile();
	scene = SceneNum::main;

	map = new Map();

	player = new Player();
	light = new ObImage(L"PinkTresureClosed00_12x1.png");
	light->scale.x = light->imageSize.x * 2.0f / 12.0f;
	light->scale.y = light->imageSize.y * 2.0f;
	light->maxFrame.x = 12;
	light->SetWorldPosY(-330);
	light->ChangeAnim(ANIMSTATE::LOOP, 0.1f);

	bg = new BackGround;

	LIGHT->select = true;
	LIGHT->outColor = Color(0.3, 0.3, 0.3);

	main = new ObImage(L"main.png");
	main->scale.x = app.GetWidth();
	main->scale.y = app.GetHeight();
	main->space = SPACE::SCREEN;

	button1 = new ObRect();
	button1->scale.x = 120;
	button1->scale.y = 30;
	button1->SetWorldPosX(0);
	button1->SetWorldPosY(-80);
	button1->isFilled = false;
	button1->color.x = 1;
	button1->color.y = 0.5;
	button1->color.z = 0.5;

	button2 = new ObRect();
	button2->scale.x = 120;
	button2->scale.y = 30;
	button2->SetWorldPosX(0);
	button2->SetWorldPosY(-127);
	button2->isFilled = false;
	button2->color.x = 1;
	button2->color.y = 0.5;
	button2->color.z = 0.5;

	button3 = new ObRect();
	button3->scale.x = 120;
	button3->scale.y = 30;
	button3->SetWorldPosX(0);
	button3->SetWorldPosY(-170);
	button3->isFilled = false;
	button3->color.x = 1;
	button3->color.y = 0.5;
	button3->color.z = 0.5;

	button4 = new ObRect();
	button4->scale.x = 120;
	button4->scale.y = 30;
	button4->SetWorldPosX(0);
	button4->SetWorldPosY(-210);
	button4->isFilled = false;
	button4->color.x = 1;
	button4->color.y = 0.5;
	button4->color.z = 0.5;
	



	thankyou = new ObImage(L"ThankYou.korean.png");
	thankyou->scale.x = thankyou->imageSize.x * 10;
	thankyou->scale.y = thankyou->imageSize.y * 10;

}

Main::~Main()
{

}

void Main::Init()
{
	tiles->Init();
	map->Init();
	player->Init(Vector2(0, -420));
	MONSTER->CreatePortal(Vector2(2000.f, -270));
}

void Main::Release()
{
}

void Main::Update()
{
	if (scene == SceneNum::main) {
		main->Update();
		button1->Update();
		button2->Update();
		button3->Update();
		button4->Update();
	}
	else if (scene == SceneNum::debug) {
		ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());
		ImGui::Text("Mouse X : %f, Y : %f", INPUT->GetWorldMousePos().x, INPUT->GetWorldMousePos().y);
		ImGui::SliderFloat("Cam Scale", &scale, 0.0f, 2.0f);
		CAM->scale.x = scale;
		CAM->scale.y = scale;

		ImGui::SameLine();
		if (ImGui::Button("Reset")) {
			scale = 1.0f;
		}


		tiles->Update();
		TileUi->Update();
	}
	else if (scene == SceneNum::release) {
		ImGui::Text("RELEASE : %d", TIMER->GetFramePerSecond());
		//ImGui::Text("Mouse X : %f, Y : %f", INPUT->GetWorldMousePos().x, INPUT->GetWorldMousePos().y);
		//ImGui::Text("cam Pos: (%.2f, %.2f)", CAM->position.x, CAM->position.y);


		const float halfTileSize = static_cast<float>(map->TileSize) / 2;
		const float halfWidth = app.GetHalfWidth();
		const float halfHeight = app.GetHalfHeight();
		//todo: 플레이어 객체가 게임오브젝트를 상속받기때문에 col,img를 퍼블릭에서 내부로 감춰두고
		//      플레이어클레스를 움직이면 내부에 있는 객체를 제어하게 변경할것
		Vector2 lerpedPos = Vector2::Lerp(CAM->position, player->col->GetWorldPos(), 1.f);
		float saturatedX = Utility::Saturate(lerpedPos.x, -(float)(map->TileSize * map->GetTileSizeXY().x) / 2 + app.GetHalfWidth(), (float)(map->TileSize * map->GetTileSizeXY().x) / 2 - app.GetHalfWidth());
		float saturatedY = Utility::Saturate(lerpedPos.y, -(float)(map->TileSize * map->GetTileSizeXY().y) / 2 + app.GetHalfHeight(), (float)(map->TileSize * map->GetTileSizeXY().y) / 2 - app.GetHalfHeight());

		CAM->position.x = saturatedX;
		CAM->position.y = saturatedY;


		map->Update();
		player->Update();
		light->Update();

		if (player->isEnd || is_broken) {
			thankyou->SetWorldPosX(CAM->position.x);
			thankyou->SetWorldPosY(CAM->position.y + 150);
			thankyou->Update();
		}

		LIGHT->radius = player->hp < 0 ? 0 : player->hp / player->Maxhp * 500.f;
		is_broken = true;
		bool foundPortal = false;
		for (Mon* monPtr : MONSTER->GetMonsterVector()) {
			Portal* portalPtr = dynamic_cast<Portal*>(monPtr);
			if (portalPtr != nullptr) {
				foundPortal = true;
				is_broken = false;
				break;  // 포탈을 찾았으므로 더 이상 반복할 필요가 없습니다.
			}
		}


		if (foundPortal && TIMER->GetTick(MonsterSpawnTime, 3.0f) || player->hp == 0) {
			MONSTER->Create(Vector2(RANDOM->Float(-400, 1900.f), -420));
		}

		if (is_broken) {
			static int a = 0;
			if (a == 0) {
				spawn();
			}
			a++;
		}

		if (is_broken) {
			//ImGui::Text("Effect pos %f, %f ", Effect->GetWorldPos().x, Effect->GetWorldPos().y);
			Vector2 direction = Vector2(Vector2(2000.f, 300) - Effect->GetWorldPos());
			direction.Normalize();

			Effect->MoveWorldPos(direction * 100.f * DELTA);

			Effect->Update();
		}

		MONSTER->Update();
		MONSTER->TagetPos(player->col->GetWorldPos());



		Vector2 lightPos = Vector2::Lerp(light->GetWorldPos(), player->obj->GetWorldPos(), 0.01f);
		LIGHT->screenPos = Utility::WorldToScreen(light->GetWorldPos());
		light->SetWorldPos(lightPos);
		bg->Update();

	}

}


void Main::LateUpdate() {
	if (scene == SceneNum::main)
	{
		if (button1->Intersect(INPUT->GetWorldMousePos())) {
			button1->color = Color(1.0f, 0, 0);
			if (INPUT->KeyUp(VK_LBUTTON))
			{
				scene = SceneNum::release;
			}
		}
		else button1->color = Color(1, 1, 1);
		if (button2->Intersect(INPUT->GetWorldMousePos())) {
			button2->color = Color(1.0f, 0, 0);
			if (INPUT->KeyUp(VK_LBUTTON))
			{
				scene = SceneNum::debug;
			}
		}
		else button2->color = Color(1, 1, 1);
		if (button3->Intersect(INPUT->GetWorldMousePos())) {
			button3->color = Color(1.0f, 0, 0);
			if (INPUT->KeyUp(VK_LBUTTON))
			{
				cout << "미구현입니다" << endl;
			}
		}
		else button3->color = Color(1, 1, 1);
		if (button4->Intersect(INPUT->GetWorldMousePos())) {
			button4->color = Color(1.0f, 0, 0);
			if (INPUT->KeyUp(VK_LBUTTON))
			{
				PostQuitMessage(0);
			}
		}
		else button4->color = Color(1, 1, 1);
	}
	else if (scene == SceneNum::debug)
	{
		tiles->LateUpdate();
	}
	else if (scene == SceneNum::release) {
		map->LateUpdate();
		player->LateUpdate();

		Collision::CollisionMaptoPlayer(player, map);


		for (Mon* monPtr : MONSTER->GetMonsterVector()) {
			if (player->c_atk1->Intersect(monPtr->GetCol())) {
				if (player->c_atk1->scale.x != 0)
					monPtr->Damage(player->Atk);
			}
			Monster1* monsterPtr1 = dynamic_cast<Monster1*>(monPtr);
			Monster2* monsterPtr2 = dynamic_cast<Monster2*>(monPtr);
			if (monsterPtr1 == nullptr && monsterPtr2 == nullptr) {
				// 잘못된 타입의 객체이므로 건너뜁니다.
				continue;
			}

			if (monsterPtr1 != nullptr && monsterPtr1->col_Attack->Intersect(player->col)) {
				if (monsterPtr1->col_Attack->scale.x != 0)
					player->Damage(monsterPtr1->atk);
			}
			if (monsterPtr1 != nullptr && monsterPtr1->col_Crush->Intersect(player->col)) {
				if (monsterPtr1->col_Crush->scale.x != 0)
					player->Damage(monsterPtr1->atk2);
			}
			if (monsterPtr2 != nullptr && monsterPtr2->col_Attack->Intersect(player->col)) {
				if (monsterPtr2->col_Attack->scale.x != 0)
					player->Damage(monsterPtr2->atk);
			}
		}
		MONSTER->LateUpdate();
	}
}

void Main::Render() {

	if (scene == SceneNum::main)
	{
		main->Render();

		button1->Render();
		button2->Render();
		button3->Render();
		button4->Render();
	}
	else if (scene == SceneNum::debug)
	{
		tiles->Render();
	}
	else if (scene == SceneNum::release) {
		bg->Render();
		map->Render();
		light->Render();
		player->Render();
		MONSTER->Render();
		if (is_broken) {
			Effect->Render();
		}

		if (player->isEnd || is_broken) {
			thankyou->Render();
		}

	}

}

void Main::ResizeScreen()
{
}

void Main::spawn()
{
	Effect = new ObImage(L"DemonBerserkFX0_7x1.png");
	Effect->scale.x = Effect->imageSize.x * 4.0f / 7.0f;
	Effect->scale.y = Effect->imageSize.y * 4.0f;
	Effect->maxFrame.x = 7;
	Effect->SetWorldPosX(2000);
	Effect->SetWorldPosY(-330);
	Effect->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1000.0f, 640.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}