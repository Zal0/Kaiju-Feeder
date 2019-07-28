#include "Banks/SetBank2.h"

#include "SpriteManager.h"
UINT8 mouth_anim[] = {2, 0, 1};

void Start_SpriteMouth() {
	SetSpriteAnim(THIS, mouth_anim, 1);
}

void Update_SpriteMouth() {
}

void Destroy_SpriteMouth() {
}