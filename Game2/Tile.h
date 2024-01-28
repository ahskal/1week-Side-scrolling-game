#pragma once
class Tile
{
private:
	enum class Terrain {
		None,
		Floor,
		Wall,

	};
	struct Tiles {
		ObImage* img;
		ObRect* col;
		Terrain terrain;

		bool hasImg;
		bool hasCol;

		Tiles() {
			col = new ObRect();
			img = new ObImage(L"Tile_NONE.png");
			terrain = Terrain::None;
			//img->SetParentRT(*col);
			col->pivot = OFFSET_LB;
			img->pivot = OFFSET_LB;
			hasImg = true;
			hasCol = true;
		}
	};
	vector<vector<Tiles>> Tilemap;


	int TileX;
	int TileY;

	int TileSize;

	bool is_NoneTile;
	bool is_FloorTile;
	bool is_WallTile;



public:



public:

	wstring ImgAddress;
	Tile();
	~Tile();

	void save(bool saveAs = false);
	void load(bool saveAs = false);

	void Init();
	void Update();
	void LateUpdate();
	void Render();

};