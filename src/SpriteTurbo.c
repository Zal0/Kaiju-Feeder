#include "Banks/SetBank2.h"

#include "SpriteManager.h"
#include "Keys.h"

extern struct Sprite* sprite_chopter;
struct Sprite* sprite_turbo = 0;

UINT8 anim_turbo[] = {2, 0, 1};

void Start_SpriteTurbo() {
	sprite_turbo = THIS;
	SetSpriteAnim(THIS, anim_turbo, 15);
}

void Update_SpriteTurbo() {
	THIS->y = sprite_chopter->y;
	if(SPRITE_GET_VMIRROR(sprite_chopter)) {
		THIS->x = sprite_chopter->x + 16;
		SPRITE_SET_VMIRROR(THIS);
	} else {
		THIS->x = sprite_chopter->x - 8;
		SPRITE_UNSET_VMIRROR(THIS);
	}
}

void Destroy_SpriteTurbo() {
	sprite_turbo = 0;
}