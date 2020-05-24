#include "Banks/SetBank2.h"

#include "SpriteManager.h"
#include "Scroll.h"

const UINT8 anim_pollo_dying[] = {6, 1, 2, 3, 4, 5, 5};
extern struct Sprite* sprite_gancho;

struct PolloInfo {
	INT8 vy;
};

void Start_SpritePollo() {
	struct PolloInfo* data = (struct PolloInfo*)THIS->custom_data;
	UINT8 coll_tile;

	if(sprite_gancho && sprite_gancho->anim_frame != 0) {
		SpriteManagerRemove(THIS_IDX);
		return;
	}

	THIS->coll_h = 4;
	THIS->coll_y = 12;

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
		if(THIS->anim_frame == 5) {
			SpriteManagerRemove(THIS_IDX);
		}
	} else {
		if(data->vy) {
			if(tile_coll = TranslateSprite(THIS, 0, data->vy)) {
				//SetSpriteAnim(THIS, anim_pollo_dying, 15);
			}
		}
	}
}

void Destroy_SpritePollo() {
}