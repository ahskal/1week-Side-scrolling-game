#pragma once
class Portal : public Mon
{
private:
	ObImage* portal;
	ObImage* Effect;


public:

	Portal();
	~Portal();
	void Init(Vector2 spawn);
	void Update();
	void LateUpdate();
	void Render();
};

