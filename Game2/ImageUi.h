#pragma once

struct ImageUiDesc {
	wstring fileName;
	ImVec2 fream;
	ImVec2 maxfream;
	ImageUiDesc(wstring fileName, ImVec2 maxfream, ImVec2 fream)
	{
		this->fileName = fileName;
		this->fream = fream;
		this->maxfream = maxfream;
	}
};

class ImageUi
{
private:
	vector<ImageUiDesc> Ui;
	int idx;
	int TileLookSize;

public:
	ImageUi();
	~ImageUi();

	void Init(wstring fileName, Int2 maxfream, Int2 fream = Int2(0, 0));
	void Update();
};
