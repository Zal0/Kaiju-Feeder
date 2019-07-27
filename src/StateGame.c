#include "Banks/SetBank2.h"

#include "..\res\src\tiles_beach.h"
#include "..\res\src\beach.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Print.h"
#include "../res/src/font.h"

UINT8 collision_tiles[] = {1, 2, 3, 4, 5, 6, 0};

void Start_StateGame() {
	UINT8 i;

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);

	InitScrollTiles(0, &tiles_beach, bank_tiles_beach);
	InitScroll(beachWidth, beachHeight, beach, collision_tiles, 0, 3);
	SHOW_BKG;

	INIT_CONSOLE(font, 3, 2);
}

void Update_StateGame() {
}