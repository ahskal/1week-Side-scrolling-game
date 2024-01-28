#include "stdafx.h"
#include "ImageUi.h"

ImageUi::ImageUi()
{
	idx = 0;
	TileLookSize = 60;
}

ImageUi::~ImageUi()
{
}

void ImageUi::Init(wstring fileName, Int2 maxfream, Int2 fream)
{
	Ui.push_back(ImageUiDesc(fileName, ImVec2(maxfream.x, maxfream.y), ImVec2(fream.x, fream.y)));
}

void ImageUi::Update()
{

	//todo: 제작툴쪽에서 타입을 지정하여 마우스 타입에 따라서 클릭 조건 처리
	ImGui::Begin("Sprite Sheet Example");
	ImGui::SliderInt("TileStyle", &idx, 0, max(0, Ui.size()));
	ImGui::SliderInt("TileLookSize", &TileLookSize, 0, 100);
	ImGui::Text("Terrain Type : %d", INPUT->Terrain);
	int Vi = max(0, idx - 1);
	if (idx == 0) {
		ImGui::Text("Terrain Type");
		if (ImGui::Button("None", ImVec2(70, 50))) {
			INPUT->Terrain = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Floor", ImVec2(70, 50))) {
			INPUT->Terrain = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button("Wall", ImVec2(70, 50))) {
			INPUT->Terrain = 2;
		}
		INPUT->FileName = L"";
	}
	else {
		INPUT->Terrain = 0;
	}

	for (int y = 0; y < Ui[Vi].maxfream.y; y++) {
		for (int x = 0; x < Ui[Vi].maxfream.x; x++) {
			ImVec2 uv0(x / Ui[Vi].maxfream.x, y / Ui[Vi].maxfream.y);
			ImVec2 uv1((x + 1) / Ui[Vi].maxfream.x, (y + 1) / Ui[Vi].maxfream.y);

			int index = y * Ui[Vi].maxfream.x + x;
			ImGui::PushID(index);
			if (ImGui::ImageButton(ImTextureID(TEXTURE->LoadTexture(Ui[Vi].fileName)), ImVec2(TileLookSize, TileLookSize), uv0, uv1)) {
				cout << " X : " << x << " Y : " << y << endl;
				INPUT->FileName = Ui[Vi].fileName;
				INPUT->fream = Int2(x, y);
				INPUT->maxFrame = Int2(Ui[Vi].maxfream.x, Ui[Vi].maxfream.y);
			}
			ImGui::PopID();

			ImGui::SameLine();
		}
		ImGui::NewLine();
	}
	ImGui::End();

}