#include "Banks/SetBank2.h"

#include "SpriteManager.h"
#include "Scroll.h"

struct PolloInfo {
	INT8 vy;
};

void Start_SpritePollo() {
	struct PolloInfo* data = (struct PolloInfo*)THIS->custom_data;
	UINT8 coll_tile;

	data->vy = 0;
	coll_tile = GetScrollTile(THIS->x >> 3, (THIS->y + 16) >> 3);
	if(!scroll_collisions[coll_tile]) {
		data->vy = 1;
	}
}

void Update_SpritePollo() {
	struct PolloInfo* data = (struct PolloInfo*)THIS->custom_data;

	if(data->vy) {
		if(TranslateSprite(THIS, 0, data->vy)) {
			//SpriteManagerRemove(THIS_IDX);
		}
	}
}

void Destroy_SpritePollo() {
}