#pragma once

enum class AdventurerState {
	IDLE,
	RUN,
	JUMP,
	SLIDE,
	DROP,
};

class Adventurer
{
private:

public:
	ObImage* idle;
	ObImage* run;
	ObImage* jump;
	ObImage* slide;

	ObRect* col;
	AdventurerState state;
	float		gravity;
	bool isjump = false;;


public:
	Adventurer();
	~Adventurer();

	void Init();
	void Update();
	void Render();

	void changeState(AdventurerState state) { this->state = state; }

};