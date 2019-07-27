#include "Banks/SetBank2.h"

#include "SpriteManager.h"

struct Sprite* sprite_gancho = 0;
extern struct Sprite* sprite_chopter;

struct GanchoInfo {
	INT8 y;
	INT8 vy;
};

void Start_SpriteGancho() {
	struct GanchoInfo* data = (struct GanchoInfo*)THIS->custom_data;
	data->y = sprite_chopter->y;
	data->vy = 1;
	sprite_gancho = THIS;
}

void Update_SpriteGancho() {
	INT16 new_x;
	INT16 new_y;

	struct GanchoInfo* data = (struct GanchoInfo*)THIS->custom_data;
	data->y += data->vy;

	new_x = sprite_chopter->x;
	new_y = data->y;
	if(data->vy > 0) {
		if(TranslateSprite(THIS, new_x - THIS->x, new_y - THIS->y)) {
			data->vy = -3;
		}
	} else {
		THIS->x = new_x;
		THIS->y = new_y;
		if(THIS->y < sprite_chopter->y) {
			SpriteManagerRemove(THIS_IDX);
		}
	}
	//if((data->y - sprite_chopter->y) > 60) {
	//	data->y = sprite_chopter->y + 60;
	//}
}

void Destroy_SpriteGancho() {
	sprite_gancho = 0;
}
