#pragma once
class MonsterManager : public Singleton<MonsterManager>
{
private:
	vector<class Mon*> monster;
public:
	MonsterManager();
	~MonsterManager();

	void Init();
	void Update();
	void LateUpdate();
	void Render();

	void Create(Vector2 Pos);
	void CreatePortal(Vector2 Pos);

	void TagetPos(Vector2 Pos);

	vector<class Mon*> GetMonsterVector() { return monster; };

	bool isDebug;
};

