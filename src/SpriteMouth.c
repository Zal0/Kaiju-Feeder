#include "Banks/SetBank2.h"

#include "SpriteManager.h"
UINT8 mouth_anim[] = {10, 0, 0, 0, 0, 1, 2, 2, 2, 2, 1};

void Start_SpriteMouth() {
	SetSpriteAnim(THIS, mouth_anim, 13);
}

void Update_SpriteMouth() {
}

void Destroy_SpriteMouth() {
}