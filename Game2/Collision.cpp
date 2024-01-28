#include "stdafx.h"
#include "Player.h"
#include "Map.h"
#include "Collision.h"

void Collision::CollisionMaptoPlayer(Player* p, Map* m)
{
	int tileSize = m->TileSize;
	auto tiles = m->GetTiles();
	static int A = 0;
	if (A != 0){
	for (int i = 0; i < m->GetTileSizeXY().x; i++) {
		for (int j = 0; j < m->GetTileSizeXY().y; j++) {
			if (tiles[i][j].terrain == Terrain::None)
				continue;
			Vector2 pos = tiles[i][j].col->GetWorldPos();

			if (p->col->Intersect(tiles[i][j].col) && tiles[i][j].terrain == Terrain::Floor) {
				p->gravity = 0;
				p->col->SetWorldPosY(pos.y + tileSize);
				if (INPUT->KeyPress(VK_LEFT) && INPUT->KeyPress(VK_RIGHT))
					p->SetState(1);
				else
					p->SetState(0);

				p->isgravity = false;
				p->isjump = false;

			}
		}
	}
	}
	A++;

}
