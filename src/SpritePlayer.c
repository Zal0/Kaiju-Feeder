#include "Banks/SetBank2.h"

#include "SpriteManager.h"
#include "Keys.h"
#include "ZGBMain.h"
#include "main.h"

UINT8 anim_landed[] = {10, 0, 6, 0, 6, 0, 6, 0, 6, 0, 1};
UINT8 anim_idle[]   = {2, 4, 5};
UINT8 anim_flying[] = {2, 2, 3};
UINT8 anim_dying[]  = {6, 8, 9, 10, 11, 12, 12};

typedef enum {
	StateLanded,
	StateFlying,
	StateDying,
}PlayerState;
PlayerState player_state;

void SetPlayerState(PlayerState _state) {
	player_state = _state;

	switch(_state) {
		case StateLanded:
			SetSpriteAnim(THIS, anim_landed, 15);
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
}

void Update_SpritePlayer() {
	UINT8 tile_coll = 0;
	INT8 inc_x = 0;
	INT8 inc_y = 0;

	switch(player_state) {
		case StateLanded: {
			if(KEY_TICKED(J_UP)) {
				SetPlayerState(StateFlying);
			} 
			break;
		}

		case StateFlying: {
			if(KEY_PRESSED(J_UP)) {
				inc_y = -1;
				SetSpriteAnim(THIS, anim_flying, 15);
			} 
			if(KEY_PRESSED(J_DOWN)) {
				inc_y = 1;
				SetSpriteAnim(THIS, anim_flying, 15);
			}
			if(KEY_PRESSED(J_LEFT)) {
				inc_x = -1;
				SetSpriteAnim(THIS, anim_flying, 15);
				SPRITE_SET_VMIRROR(THIS);
			}
			if(KEY_PRESSED(J_RIGHT)) {
				inc_x = 1;
				SetSpriteAnim(THIS, anim_flying, 15);
				SPRITE_UNSET_VMIRROR(THIS);
			}
			
			tile_coll = TranslateSprite(THIS, inc_x, inc_y);
			
			if(keys == 0) {
				SetSpriteAnim(THIS, anim_idle, 15);
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
}

void Destroy_SpritePlayer() {
}