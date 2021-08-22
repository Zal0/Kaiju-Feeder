#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Keys.h"

struct Sprite* sprite_gancho = 0;
extern struct Sprite* sprite_chopter;
extern struct Sprite* sprite_rope;

struct GanchoInfo {
	INT16 y;
	INT16 vy;
};

void Start_SpriteGancho() {
	struct GanchoInfo* data = (struct GanchoInfo*)THIS->custom_data;
	data->y = sprite_chopter->y + 16;
	data->vy = 1;
	sprite_gancho = THIS;

	SpriteManagerAdd(SpriteRope, THIS->x, THIS->y);
}

void Update_SpriteGancho() {
	INT16 new_x;
	INT16 new_y;
	UINT8 i;
	struct Sprite* spr;

	struct GanchoInfo* data = (struct GanchoInfo*)THIS->custom_data;
	data->y += data->vy;

	new_x = sprite_chopter->x + 12;
	new_y = data->y;
	if(data->vy > 0) { //going down
		if(TranslateSprite(THIS, new_x - THIS->x, new_y - THIS->y)) {
			data->vy = -3;
		} else {
			SPRITEMANAGER_ITERATE(i, spr) {
				if(spr->type == SpritePollo) {
					if(CheckCollision(spr, THIS)) {
						SpriteManagerRemove(i);
						SetFrame(THIS, 1);
						data->vy = -1;
					}
				}
			}
		}
	} else { //going up
		if(THIS->anim_frame == 1) { //pollo grabbed
			if(TranslateSprite(THIS, new_x - THIS->x, new_y - THIS->y)) { //Gancho with pollo has collided
				SetFrame(THIS, 0);
				SpriteManagerAdd(SpritePollo, THIS->x - 12, THIS->y + 12);
			}
		} else { //no pollo, just go up
			THIS->x = new_x;
			THIS->y = new_y;
		}

		if(THIS->y < sprite_chopter->y + 16) { //Gancho is on chopter pos
			SpriteManagerRemoveSprite(sprite_rope);
			if(THIS->anim_frame == 1) { //Pollo grabbed, keep the gancho
				data->y = sprite_chopter->y + 16;
			} else { //No pollo, remove gancho
				SpriteManagerRemove(THIS_IDX);
			}
		}

		if(KEY_TICKED(J_B) && THIS->anim_frame == 1) {
			//Drop the pollo
			SetFrame(THIS, 0);
			SpriteManagerAdd(SpritePollo, THIS->x - 12, THIS->y + 12);
		}
	}

	//Dont' move beyond chopter->y + 60
	if((data->y - sprite_chopter->y) > 60) {
		data->y = sprite_chopter->y + 60;
	}
}

void Destroy_SpriteGancho() {
	sprite_gancho = 0;
}
