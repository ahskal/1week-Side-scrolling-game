#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	TileX = 10;
	TileY = 10;
	TileSize = 30;

}

Tile::~Tile()
{

}


void Tile::Init()
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
			Tilemap[i][j].col->scale = Vector2(TileSize, TileSize);
			Tilemap[i][j].col->isFilled = false;
			Tilemap[i][j].img->SetWorldPos(Vector2(xPos, yPos));
			Tilemap[i][j].img->scale = Vector2(TileSize, TileSize);

		}
	}

	is_NoneTile = false;
	is_FloorTile = false;
	is_WallTile = false;

}

void Tile::Update()
{
	ImGui::Text("Tile Set");
	if (
		ImGui::SliderInt("[ TileSize ]", &TileSize, 0, 300) ||
		ImGui::SliderInt("[ X ]", &TileX, 0, 300) ||
		ImGui::SliderInt("[ Y ]", &TileY, 0, 300))
	{
		Tile::Init();
	}

	const char* valueString = Tilemap[0][0].hasCol ? "true" : "false";
	ImGui::Text("Rect Draw : %s", valueString);

	const char* valueString2 = Tilemap[0][0].hasImg ? "true" : "false";
	ImGui::Text("Image Draw : %s", valueString2);


	ImGui::Begin("SaveLoad");
	if (ImGui::Button("SAVE", ImVec2(70, 30)))
	{
		save();
	}
	ImGui::SameLine();
	if (ImGui::Button("SAVE AS", ImVec2(70, 30)))
	{
		save(true);
	}
	if (ImGui::Button("LOAD", ImVec2(70, 30)))
	{
		load();
	}
	ImGui::SameLine();
	if (ImGui::Button("LOAD SIZE", ImVec2(70, 30)))
	{
		load(true);
	}
	ImGui::End();
	if (INPUT->KeyDown(VK_F1)) {
		for (int i = 0; i < TileX; i++) {
			for (int j = 0; j < TileY; j++) {
				Tilemap[i][j].col->isFilled = !Tilemap[i][j].col->isFilled;
			}
		}
	}
	if (INPUT->KeyDown(VK_F2)) {
		for (int i = 0; i < TileX; i++) {
			for (int j = 0; j < TileY; j++) {
				Tilemap[i][j].hasCol = !Tilemap[i][j].hasCol;
			}
		}
	}
	if (INPUT->KeyDown(VK_F3)) {
		for (int i = 0; i < TileX; i++) {
			for (int j = 0; j < TileY; j++) {
				Tilemap[i][j].hasImg = !Tilemap[i][j].hasImg;
			}
		}
	}

	if (INPUT->KeyDown('1')) {
		is_NoneTile = !is_NoneTile;
	}
	if (INPUT->KeyDown('2')) {
		is_FloorTile = !is_FloorTile;
	}
	if (INPUT->KeyDown('3')) {
		is_WallTile = !is_WallTile;
	}


	for (int i = 0; i < TileX; i++) {
		for (int j = 0; j < TileY; j++) {
			if (is_NoneTile && Tilemap[i][j].terrain == Terrain::None) {
				Tilemap[i][j].img->color.x = 0.7;
				Tilemap[i][j].col->color.x = 0.7;
			}
			else {
				Tilemap[i][j].img->color.x = 0.5;
				Tilemap[i][j].col->color.x = 0.5;
			}
			if (is_FloorTile && Tilemap[i][j].terrain == Terrain::Floor) {
				Tilemap[i][j].img->color.y = 0.7;
				Tilemap[i][j].col->color.y = 0.7;
			}
			else {
				Tilemap[i][j].img->color.y = 0.5;
				Tilemap[i][j].col->color.y = 0.5;
			}
			if (is_WallTile && Tilemap[i][j].terrain == Terrain::Wall) {
				Tilemap[i][j].img->color.z = 0.7;
				Tilemap[i][j].col->color.z = 0.7;
			}
			else {
				Tilemap[i][j].img->color.z = 0.5;
				Tilemap[i][j].col->color.z = 0.5;
			}
		}
	}
	
	if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('A')) {
		CAM->position.x -= 300 * DELTA;
	}
	if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D')) {
		CAM->position.x += 300 * DELTA;
	}
	if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W')) {
		CAM->position.y += 300 * DELTA;
	}
	if (INPUT->KeyPress(VK_DOWN) || INPUT->KeyPress('S')) {
		CAM->position.y -= 300 * DELTA;
	}

	for (int i = 0; i < TileX; i++) {
		for (int j = 0; j < TileY; j++) {
			if (Tilemap[i][j].hasImg)
				Tilemap[i][j].col->Update();
			if (Tilemap[i][j].hasCol)
				Tilemap[i][j].img->Update();
		}
	}
}

void Tile::LateUpdate()
{
	for (int i = 0; i < TileX; i++) {
		for (int j = 0; j < TileY; j++) {
			if (Tilemap[i][j].col->Intersect(INPUT->GetWorldMousePos())) {
				//Tilemap[i][j].col->color = Color(1, 0, 0);

				if (INPUT->KeyPress(VK_LBUTTON)) {
					if (INPUT->FileName != L"") {
						Tilemap[i][j].img->ChangeImg(INPUT->FileName);
						Tilemap[i][j].img->frame = INPUT->fream;
						Tilemap[i][j].img->maxFrame = INPUT->maxFrame;
						Tile::Init();
						break;
					}
					else {
						Tilemap[i][j].terrain = Terrain(INPUT->Terrain);
						Tile::Init();
						break;
					}
				}
				if (INPUT->KeyPress(VK_RBUTTON)) {
					Tilemap[i][j].img->ChangeImg(L"Tile_NONE.png");
					Tilemap[i][j].img->frame = Int2(0, 0);
					Tilemap[i][j].img->maxFrame = Int2(1, 1);
					Tile::Init();
					break;
				}
			}

		}
	}






}

void Tile::Render()
{
	for (int i = 0; i < TileX; i++) {
		for (int j = 0; j < TileY; j++) {
			if (Tilemap[i][j].hasImg)
				Tilemap[i][j].col->Render();
			if (Tilemap[i][j].hasCol)
				Tilemap[i][j].img->Render();
		}
	}
}

void Tile::save(bool saveAs)
{
	if (saveAs) {
		cout << "저장완료2" << endl;
	}
	else
	{
		cout << "저장완료" << endl;
		ofstream fout;
		string file = "TileMap.txt";

		fout.open(file.c_str(), ios::out);
		fout << "X: " << TileX << " " << "Y: " << TileY << " " << endl;
		for (int i = 0; i < TileX; i++) {
			for (int j = 0; j < TileY; j++) {
				string ImgName;
				ImgName.append(Tilemap[i][j].img->imageAddr.begin(), Tilemap[i][j].img->imageAddr.end());
				if (fout.is_open())
				{
					string Addr;
					fout << ImgName << " "
						<< Tilemap[i][j].img->frame.x << " " << Tilemap[i][j].img->frame.y << " "
						<< Tilemap[i][j].img->maxFrame.x << " " << Tilemap[i][j].img->maxFrame.y << " "
						<< int(Tilemap[i][j].terrain) << endl;
				}
			}
		}
		fout.close();
	}

}

void Tile::load(bool saveAs)
{
	cout << "로드 완료" << endl;
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
		if (saveAs) {
			TileX = x;
			TileY = y;
			Tile::Init();
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
		}
		else {
			for (int i = 0; i < min(x, TileX); i++) {
				for (int j = 0; j < min(y, TileY); j++) {
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
		}
		fin.close();
	}
	else {
		cout << "파일을 열 수 없습니다." << endl;
		return;
	}

	Tile::Init();
}
