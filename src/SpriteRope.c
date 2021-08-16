#include "Banks/SetBank2.h"

#include "SpriteManager.h"

extern struct Sprite* sprite_chopter;
extern struct Sprite* sprite_gancho;
struct Sprite* sprite_rope = 0;


struct RopeInfo {
	INT8 inc_y;
};

void Start_SpriteRope() {
	struct RopeInfo* data = (struct RopeInfo*)THIS->custom_data;
	sprite_rope = THIS;
	data->inc_y = 0;
}

void Update_SpriteRope() {
	UINT16 start_y = sprite_chopter->y + 16;
	struct RopeInfo* data = (struct RopeInfo*)THIS->custom_data;
	THIS->x = sprite_gancho->x - 8;

	data->inc_y += 8;
	THIS->y = start_y + data->inc_y;
	if(sprite_gancho->y > start_y) {
		while(THIS->y > sprite_gancho->y) {
			data->inc_y = THIS->y - sprite_gancho->y;
			THIS->y = start_y + data->inc_y;
		}
	}
}

void Destroy_SpriteRope() {
	sprite_rope = 0;
}