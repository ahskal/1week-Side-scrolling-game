#include "stdafx.h"
#include "Map.h"

Map::Map()
{
	load();



	TileSize = 60;

	TilePos.x = 0;
	TilePos.y = 0;


	TilePos.mx = 5;
	TilePos.my = 5;
	isDebug = false;
}

Map::~Map()
{
}

void Map::load()
{
	//cout << "로드 완료" << endl;
	ifstream fin;
	string file = "TileMap.txt";
	fin.open(file.c_str(), ios::in);
	vector<string> lines;
	if (fin.is_open()) {
		string X;
		int x;
		string Y;
		int y;
		fin >> X >> x >> Y >> y;
		TileX = x;
		TileY = y;
		Map::Init();
		for (int i = 0; i < TileX; i++) {
			for (int j = 0; j < TileY; j++) {
				Int2 fream;
				Int2 Maxfream;
				string FileName;
				int terrain;
				fin >> FileName >> fream.x >> fream.y >> Maxfream.x >> Maxfream.y >> terrain;
				Tilemap[i][j].img->ChangeImg(wstring(FileName.begin(), FileName.end()));
				Tilemap[i][j].img->maxFrame = Maxfream;
				Tilemap[i][j].img->frame = fream;
				Tilemap[i][j].terrain = Terrain(terrain);
			}
		}
		fin.close();
	}
	Map::Init();
}

void Map::Init()
{
	float startX = -app.GetHalfWidth() + app.GetHalfWidth() - (TileX * TileSize) / 2.0f;
	float startY = -app.GetHalfHeight() + app.GetHalfHeight() - (TileY * TileSize) / 2.0f;

	Tilemap.resize(TileX);
	for (int i = 0; i < Tilemap.size(); i++) {
		Tilemap[i].resize(TileY);
	}

	for (int i = 0; i < TileX; i++) {
		for (int j = 0; j < TileY; j++) {

			float xPos = startX + i * TileSize;
			float yPos = startY + j * TileSize;

			Tilemap[i][j].col->SetWorldPos(Vector2(xPos, yPos));
			Tilemap[i][j].col->scale = Vector2(TileSize - 5, TileSize - 5);
			Tilemap[i][j].col->isFilled = false;

			Tilemap[i][j].img->SetWorldPos(Vector2(xPos, yPos));
			Tilemap[i][j].img->scale = Vector2(TileSize, TileSize);

			Tilemap[i][j].img->color.x = color;
			Tilemap[i][j].img->color.y = color;
			Tilemap[i][j].img->color.z = color;
		}
	}
}

void Map::Update()
{
	float camLeft = CAM->position.x - app.GetHalfWidth();
	float camRight = CAM->position.x + app.GetHalfWidth();
	float camTop = CAM->position.y - app.GetHalfHeight();
	float camBottom = CAM->position.y + app.GetHalfHeight();
	for (int i = 0; i < TileX; i++) {
		for (int j = 0; j < TileY; j++) {
			Vector2 tilePos = Tilemap[i][j].col->GetWorldPos();
			float tilePosX = tilePos.x;
			float tilePosY = tilePos.y;

			if (tilePosX > camLeft - TileSize && tilePosX < camRight &&
				tilePosY > camTop - TileSize && tilePosY < camBottom) {

				Tilemap[i][j].col->Update();
				Tilemap[i][j].img->Update();
			}
		}
	}

	if (INPUT->KeyDown(VK_F2)) {
		isDebug = !isDebug;
	}


}

void Map::LateUpdate()
{


}

void Map::Render()
{
	float camLeft = CAM->position.x - app.GetHalfWidth();
	float camRight = CAM->position.x + app.GetHalfWidth();
	float camTop = CAM->position.y - app.GetHalfHeight();
	float camBottom = CAM->position.y + app.GetHalfHeight();

	for (int i = 0; i < TileX; i++) {
		for (int j = 0; j < TileY; j++) {
			Vector2 tilePos = Tilemap[i][j].col->GetWorldPos();
			float tilePosX = tilePos.x;
			float tilePosY = tilePos.y;

			if (tilePosX > camLeft - TileSize && tilePosX < camRight &&
				tilePosY > camTop - TileSize && tilePosY < camBottom) {
				Tilemap[i][j].img->Render();
				if (isDebug) {
					Tilemap[i][j].col->Render();
				}
			}
		}
	}

	



}
