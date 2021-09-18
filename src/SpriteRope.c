#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"

extern Sprite* sprite_chopter;
extern Sprite* sprite_gancho;
Sprite* sprite_rope = 0;


typedef struct {
	INT8 inc_y;
} CUSTOM_DATA;

void START() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	sprite_rope = THIS;
	data->inc_y = 0;
}

void UPDATE() {
	UINT16 start_y = sprite_chopter->y + 16;
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
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

void DESTROY() {
	sprite_rope = 0;
}