#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "Keys.h"

extern struct Sprite* sprite_chopter;
struct Sprite* sprite_turbo = 0;

const UINT8 anim_turbo[] = {2, 0, 1};

void Start_SpriteTurbo() {
	sprite_turbo = THIS;
	SetSpriteAnim(THIS, anim_turbo, 15);
}

void Update_SpriteTurbo() {
	THIS->y = sprite_chopter->y;
	if(sprite_chopter->mirror == V_MIRROR) {
		THIS->x = sprite_chopter->x + 16;
		THIS->mirror = V_MIRROR;
	} else {
		THIS->x = sprite_chopter->x - 8;
		THIS->mirror = NO_MIRROR;
	}
}

void Destroy_SpriteTurbo() {
	sprite_turbo = 0;
}