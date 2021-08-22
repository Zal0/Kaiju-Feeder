#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "main.h"
#include "Print.h"
#include "Math.h"
#include "Scroll.h"

const UINT8 anim_landed[] = {10, 0, 6, 0, 6, 0, 6, 0, 6, 0, 1};
const UINT8 anim_idle[]   = {2, 4, 5};
const UINT8 anim_flying[] = {2, 2, 3};
const UINT8 anim_dying[]  = {6, 8, 9, 10, 11, 12, 12};
const UINT8 anim_turning[]  = {4, 4, 15, 6, 6};
const UINT8 anim_win[]      = {1, 7};

typedef enum {
	StateLanded,
	StateFlying,
	StateDying
}PlayerState;
PlayerState player_state;

fixed chopter_x_dec;
fixed chopter_y_dec;
INT16 chopter_vx;
INT16 chopter_vy;

extern struct Sprite* sprite_gancho;
extern struct Sprite* sprite_turbo;
struct Sprite* sprite_chopter;

extern UINT16 level_done;

void SetPlayerState(PlayerState _state) {
	player_state = _state;

	switch(_state) {
		case StateFlying:
			chopter_vx = 0;
			chopter_vy = 0;
			break;

		case StateLanded:
			SetSpriteAnim(THIS, anim_landed, 15);
			chopter_vy = 0;
			break;

		case StateDying:
			SetSpriteAnim(THIS, anim_dying, 15);
			THIS->mirror = NO_MIRROR;
			break;
	}
}

void Start_SpritePlayer() {
	SetPlayerState(StateLanded);
	sprite_chopter = THIS;
	chopter_y_dec.w = 0;
	chopter_x_dec.w = 0;
}

void Update_SpritePlayer() {
	UINT8 tile_coll = 0;
	INT8 inc_x = 0;
	INT8 inc_y = 0;

	if(level_done) {
		SetSpriteAnim(THIS, anim_win, 13);

		return;
	}
	

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
				if(chopter_vx < -300) {
					chopter_vx = -300;
					if(!sprite_turbo) {
						SpriteManagerAdd(SpriteTurbo, 0, 0);
					}
				}
			} else if(KEY_PRESSED(J_RIGHT)) {
				chopter_vx += 3u << delta_time;
				if(chopter_vx > 300) {
					chopter_vx = 300;
					if(!sprite_turbo) {
						SpriteManagerAdd(SpriteTurbo, 0, 0);
					}
				}
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

				if(sprite_turbo) {
					SpriteManagerRemoveSprite(sprite_turbo);
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
				if(THIS->anim_frame == 3) {
					if(THIS->mirror == V_MIRROR) {
						THIS->mirror = NO_MIRROR;
					} else {
						THIS->mirror = V_MIRROR;
					}
					SetSpriteAnim(THIS, anim_idle, 15);
				}
			} else {
				if(KEY_PRESSED(J_RIGHT)) {
					if(THIS->mirror == V_MIRROR) {
						SetSpriteAnim(THIS, anim_turning, 15);
					} else {
						SetSpriteAnim(THIS, anim_flying, 15);
					}
				} else if(KEY_PRESSED(J_LEFT)) {
					if(THIS->mirror == NO_MIRROR) {
						SetSpriteAnim(THIS, anim_turning, 15);
					} else {
						SetSpriteAnim(THIS, anim_flying, 15);
					}
				} else {
					SetSpriteAnim(THIS, anim_idle, 15);
				}
			}

			if(!sprite_gancho && KEY_TICKED(J_B)) {
				SpriteManagerAdd(SpriteGancho, THIS->x + 12, THIS->y);
			}
			break;
		}

		case StateDying: {
			if(THIS->anim_frame == 5) {
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