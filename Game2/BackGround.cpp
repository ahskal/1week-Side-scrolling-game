#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{

	bg.push_back(ObImage(L"1.png"));
	bg.push_back(ObImage(L"2.png"));
	bg.push_back(ObImage(L"3.png"));
	bg.push_back(ObImage(L"10.png"));
	bg.push_back(ObImage(L"4.png"));
	bg.push_back(ObImage(L"8.png"));

	for (int i = 3; i < bg.size(); i++) {
		bg[i].SetWorldPosY(+50);

	}

	for (int i = 0; i < bg.size(); i++) {
		bg[i].space = SPACE::SCREEN;
		bg[i].scale.x = app.GetWidth();
		bg[i].scale.y = app.GetHeight();

		bg[i].color.x = color;
		bg[i].color.y = color;
		bg[i].color.z = color;
	}
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{

	for (int i = 0; i < bg.size(); i++) {
		bg[i].Update();
	}

	bg[1].uv.x += 30 * DELTA / bg[1].imageSize.x;
	bg[1].uv.z += 30 * DELTA / bg[1].imageSize.x;


	if (INPUT->KeyPress(VK_LEFT)) {
		bg[2].uv.x -= 60 * DELTA / bg[2].imageSize.x;
		bg[2].uv.z -= 60 * DELTA / bg[2].imageSize.x;
		bg[4].uv.x -= 90 * DELTA / bg[4].imageSize.x;
		bg[4].uv.z -= 90 * DELTA / bg[4].imageSize.x;
		bg[5].uv.x -= 120 * DELTA / bg[4].imageSize.x;
		bg[5].uv.z -= 120 * DELTA / bg[4].imageSize.x;
	}
	if (INPUT->KeyPress(VK_RIGHT)) {
		bg[2].uv.x += 60 * DELTA / bg[2].imageSize.x;
		bg[2].uv.z += 60 * DELTA / bg[2].imageSize.x;
		bg[4].uv.x += 90 * DELTA / bg[4].imageSize.x;
		bg[4].uv.z += 90 * DELTA / bg[4].imageSize.x;
		bg[5].uv.x += 120 * DELTA / bg[4].imageSize.x;
		bg[5].uv.z += 120 * DELTA / bg[4].imageSize.x;
	}
}

void BackGround::Render()
{
	for (int i = 0; i < bg.size(); i++) {
		bg[i].Render();
	}
}
