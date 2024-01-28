#include "stdafx.h"
#include "Mon.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Portal.h"
#include "MonsterManager.h"

MonsterManager::MonsterManager()
{
	isDebug = false;
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::Init()
{
	
}

void MonsterManager::Update()
{
	for (auto it = monster.begin(); it != monster.end(); ) {
		Mon* monPtr = *it;
		monPtr->Update();
		//ImGui::Text("HP : %f", monPtr->hp);
		//ImGui::Text("State : %lu", monPtr->M_State);
		if (monPtr->hp <= 0) {
			delete monPtr; // �ʿ信 ���� �޸𸮸� �����ϴ� �۾��� �����մϴ�.
			it = monster.erase(it); // ���Ҹ� �����ϰ� ���� ���Ҹ� ����Ű���� �ݺ��ڸ� ������Ʈ�մϴ�.
		}
		else {
			++it;
		}
	}

	if (INPUT->KeyDown(VK_F1)) {
		isDebug = !isDebug;

		for (Mon* monPtr : monster) {
			monPtr->isDebug = isDebug;
		}



	}




}
 
void MonsterManager::LateUpdate()
{
	for (Mon* monPtr : monster) {
		monPtr->LateUpdate();
	}
}

void MonsterManager::Render()
{
	for (Mon* monPtr : monster) {
		monPtr->Render();
	}
}

void MonsterManager::Create(Vector2 Pos)
{
	for (Mon* monPtr : monster) {
		if (monPtr) {
			if (Pos.x <= monPtr->GetCol()->GetWorldPos().x + monPtr->GetCol()->scale.x && Pos.x >= monPtr->GetCol()->GetWorldPos().x - monPtr->GetCol()->scale.x) {
				// �̹� �ش� ��ǥ�� ���Ͱ� �����ϹǷ� �������� ����
				return;
			}
		}
	}
	if (RANDOM->Int()) {
		Monster1* m = new Monster1;
		m->Init(Pos);
		m->isDebug = isDebug;
		monster.push_back(m);
	}
	else {
		Monster2* m = new Monster2;
		m->Init(Pos);
		m->isDebug = isDebug;
		monster.push_back(m);
	}
	
}

void MonsterManager::CreatePortal(Vector2 Pos)
{
	Portal* m = new Portal;
	m->Init(Pos);
	m->isDebug = isDebug;
	monster.push_back(m);
}

void MonsterManager::TagetPos(Vector2 Pos)
{
	for (auto it = monster.begin(); it != monster.end(); ) {
		Mon* monPtr = *it;
		monPtr->SetTagetPos(Pos);
		it++;
	}
}
