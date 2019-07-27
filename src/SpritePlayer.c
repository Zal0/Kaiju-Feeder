#include "Banks/SetBank2.h"

#include "SpriteManager.h"

UINT8 anim_idle[]   = {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
UINT8 anim_flying[] = {2, 2, 3};

void Start_SpritePlayer() {
	SetSpriteAnim(THIS, anim_flying, 32);
}

void Update_SpritePlayer() {
}

void Destroy_SpritePlayer() {
}