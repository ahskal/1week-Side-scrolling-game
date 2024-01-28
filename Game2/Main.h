#pragma once

enum class SceneNum {
	main,
	debug,
	release,
	release2
};



class Main : public Scene
{
private:
	//전체 화면 크기
	SceneNum scene;
	float scale;

	class ImageUi* TileUi;
	class Tile* tiles;



	class Player* player;
	class Map* map;
	ObImage* light;

	class BackGround* bg;

	float MonsterSpawnTime = 0;

	class Portal* portal;

	ObImage* main;

	ObImage* Effect;


	ObRect* button1;
	ObRect* button2;
	ObRect* button3;
	ObRect* button4;


	ObImage* thankyou;

	bool is_broken;


public:
	Main();
	~Main();

	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void spawn();

};
