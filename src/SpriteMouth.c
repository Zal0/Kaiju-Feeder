#include "Banks/SetBank2.h"

#include "SpriteManager.h"
#include "ZGBMain.h"
UINT8 mouth_anim[] = {18, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1};
UINT8 mouth_anim_munch[] = {4, 0, 1, 2, 1};

extern UINT16 level_done;

void Start_SpriteMouth() {
	SetSpriteAnim(THIS, mouth_anim, 13);
}

void Update_SpriteMouth() {
	UINT8 i;
	struct Sprite* spr;

	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SpritePollo) {
			if(!spr->anim_data && CheckCollision(THIS, spr)) {
				if(THIS->anim_data[THIS->anim_frame] == 0) {
					SpriteManagerRemove(i);
					SetSpriteAnim(THIS, mouth_anim_munch, 32);
					level_done = 1;
				}
			}
 		}
	}
}

void Destroy_SpriteMouth() {
}