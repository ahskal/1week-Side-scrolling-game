#pragma once
enum class Terrain {
	None,
	Floor,
	Wall,
};

class Map
{
private:


	struct Tiles {
		ObImage* img;
		ObRect* col;
		Terrain terrain;

		Tiles() {
			col = new ObRect();
			img = new ObImage(L"Tile_NONE.png");
			terrain = Terrain::None;
			col->pivot = OFFSET_LB;
			img->pivot = OFFSET_LB;
		}
	};
	struct LookTile {
		int x;
		int y;
		int mx;
		int my;
	};


	vector <vector<Tiles>> Tilemap;

	int TileX;
	int TileY;


	LookTile TilePos;

	float color = 0.4;

	ObImage* BlackSmith;
	
	bool isDebug;
	bool isDebug2;

public:
	int TileSize;

	Map();
	~Map();
	void load();

	void Init();
	void Update();
	void LateUpdate();
	void Render();

	const vector <vector<Tiles>> GetTiles() { return Tilemap; }
	const int GetTileSize() { return TileSize; }
	const Int2 GetTileSizeXY() { return Int2(TileX, TileY); }
};

