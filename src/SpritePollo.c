#include "Banks/SetBank2.h"

#include "SpriteManager.h"
#include "Scroll.h"

UINT8 anim_pollo_dying[] = {6, 1, 2, 3, 4, 5, 5};

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
	UINT8 tile_coll;

	if(THIS->anim_data) {
		if(THIS->current_frame == 5) {
			SpriteManagerRemove(THIS_IDX);
		}
	} else {
		if(data->vy) {
			if(tile_coll = TranslateSprite(THIS, 0, data->vy)) {
				if(tile_coll == 25 || tile_coll == 26 || tile_coll == 39 || tile_coll == 3) {
					THIS->y += 2;
				} else {
					SetSpriteAnim(THIS, anim_pollo_dying, 15);
				}
			}
		}
	}
}

void Destroy_SpritePollo() {
}