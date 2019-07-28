#include "Banks/SetBank2.h"

#include "SpriteManager.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "main.h"
#include "Print.h"
#include "Math.h"

UINT8 anim_landed[] = {10, 0, 6, 0, 6, 0, 6, 0, 6, 0, 1};
UINT8 anim_idle[]   = {2, 4, 5};
UINT8 anim_flying[] = {2, 2, 3};
UINT8 anim_dying[]  = {6, 8, 9, 10, 11, 12, 12};
UINT8 anim_turning[]  = {3, 4, 6, 6};

typedef enum {
	StateLanded,
	StateFlying,
	StateDying,
}PlayerState;
PlayerState player_state;

fixed chopter_x_dec;
fixed chopter_y_dec;
INT16 chopter_vx;
INT16 chopter_vy;

extern struct Sprite* sprite_gancho;
struct Sprite* sprite_chopter;

void SetPlayerState(PlayerState _state) {
	player_state = _state;

	switch(_state) {
		case StateLanded:
			SetSpriteAnim(THIS, anim_landed, 15);
			chopter_vy = 0;
			break;

		case StateDying:
			SetSpriteAnim(THIS, anim_dying, 15);
			SPRITE_UNSET_VMIRROR(THIS);
			break;
	}
}

void Start_SpritePlayer() {
	SetPlayerState(StateLanded);
	THIS->y = 104u;
	sprite_chopter = THIS;
	//SpriteManagerAdd(SpriteTurbo, THIS->x, THIS->y);
}

void Update_SpritePlayer() {
	UINT8 tile_coll = 0;
	INT8 inc_x = 0;
	INT8 inc_y = 0;

	switch(player_state) {
		case StateLanded: {
			if(KEY_TICKED(J_A)) {
				SetPlayerState(StateFlying);
			} 
			break;
		}

		case StateFlying: {
			if(KEY_PRESSED(J_A)) {
				chopter_vy -= 20 << delta_time;
				if(chopter_vy < -200)
					chopter_vy = -200;
			} else {
				chopter_vy += 10 << delta_time;
				if(chopter_vy > 150)
					chopter_vy = 150;
			}

			if(KEY_PRESSED(J_LEFT)) {
				chopter_vx -= 3u << delta_time;
				if(chopter_vx < -300)
					chopter_vx = -300;
			} else if(KEY_PRESSED(J_RIGHT)) {
				chopter_vx += 3u << delta_time;
				if(chopter_vx > 300)
					chopter_vx = 300;
			} else {
				if(chopter_vx > 0) {
					chopter_vx -= 3 << delta_time;
					if(chopter_vx < 0)
						chopter_vx = 0;
				} else {
					chopter_vx += 3 << delta_time;
					if(chopter_vx > 0)
						chopter_vx = 0;
				}
			}

			chopter_y_dec.w += chopter_vy;
			if(chopter_y_dec.b.h) {
				inc_y = chopter_y_dec.b.h;
				chopter_y_dec.b.h = 0;
			}
			chopter_x_dec.w += chopter_vx;
			if(chopter_x_dec.b.h) {
				inc_x = chopter_x_dec.b.h;
				chopter_x_dec.b.h = 0;
			}

			tile_coll = TranslateSprite(THIS, inc_x, inc_y);
			if(U_LESS_THAN(THIS->y, 0)) {
				THIS->y = 0;
				chopter_vy = 0;
			}

			if(THIS->anim_data == anim_turning) {
				if(THIS->current_frame == 2) {
					if(SPRITE_GET_VMIRROR(THIS)) {
						SPRITE_UNSET_VMIRROR(THIS);
					} else {
						SPRITE_SET_VMIRROR(THIS);
					}
					SetSpriteAnim(THIS, anim_idle, 15);
				}
			} else {
				if(KEY_PRESSED(J_RIGHT)) {
					if(SPRITE_GET_VMIRROR(THIS)) {
						SetSpriteAnim(THIS, anim_turning, 15);
					} else {
						SetSpriteAnim(THIS, anim_flying, 15);
					}
				} else if(KEY_PRESSED(J_LEFT)) {
					if(!SPRITE_GET_VMIRROR(THIS)) {
						SetSpriteAnim(THIS, anim_turning, 15);
					} else {
						SetSpriteAnim(THIS, anim_flying, 15);
					}
				} else {
					SetSpriteAnim(THIS, anim_idle, 15);
				}
			}

			if(!sprite_gancho && KEY_TICKED(J_B)) {
				SpriteManagerAdd(SpriteGancho, THIS->x, THIS->y);
			}
			break;
		}

		case StateDying: {
			if(THIS->current_frame == 5) {
				SetState(StateGame);
			}
			break;
		}
	}

	//check collisions with bg
	if(tile_coll) {
		if(tile_coll == 6) {
			SetPlayerState(StateLanded);
		} else {
			SetPlayerState(StateDying);
		}
	}

	//DPRINT_POS(0, 0);
	//DPrintf("x:%d y:%d  ", (UINT16)chopter_vx, (UINT16)chopter_vy);
}

void Destroy_SpritePlayer() {
	sprite_chopter = 0;
}