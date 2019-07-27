#include "Banks/SetBank2.h"

#include "SpriteManager.h"
#include "Keys.h"

UINT8 anim_landed[] = {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
UINT8 anim_idle[]   = {2, 4, 5};
UINT8 anim_flying[] = {2, 2, 3};

typedef enum {
	StateLanded,
	StateFlying
}PlayerState;
PlayerState player_state;

void SetState(PlayerState _state) {
	player_state = _state;

	switch(_state) {
		case StateLanded:
			SetSpriteAnim(THIS, anim_landed, 15);
			break;
	}
}

void Start_SpritePlayer() {
	SetState(StateLanded);
	THIS->y = 64u;
}

void Update_SpritePlayer() {
	UINT8 tile_coll = 0;

	switch(player_state) {
		case StateLanded: {
			if(KEY_TICKED(J_UP)) {
				SetState(StateFlying);
			} 
			break;
		}

		case StateFlying: {
			if(KEY_PRESSED(J_UP)) {
				TranslateSprite(THIS, 0, -1);
				SetSpriteAnim(THIS, anim_flying, 15);
			} 
			if(KEY_PRESSED(J_DOWN)) {
				if(tile_coll = TranslateSprite(THIS, 0, 1)) {
					if(tile_coll == 6) {
						SetState(StateLanded);
						return;
					}
				}
				SetSpriteAnim(THIS, anim_flying, 15);
			}
			if(KEY_PRESSED(J_LEFT)) {
				TranslateSprite(THIS, -1, 0);
				SetSpriteAnim(THIS, anim_flying, 15);
				SPRITE_SET_VMIRROR(THIS);
			}
			if(KEY_PRESSED(J_RIGHT)) {
				TranslateSprite(THIS, 1, 0);
				SetSpriteAnim(THIS, anim_flying, 15);
				SPRITE_UNSET_VMIRROR(THIS);
			}
			if(keys == 0) {
				SetSpriteAnim(THIS, anim_idle, 15);
			}
			break;
		}
	}

	
}

void Destroy_SpritePlayer() {
}