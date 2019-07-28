#include "Banks/SetBank2.h"

#include "..\res\src\tiles_beach.h"
#include "..\res\src\beach.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "Print.h"
#include "../res/src/font.h"

UINT8 collision_tiles[] = {1, 2, 6, 10, 11, 12, 13, 15, 16, 17, 18, 19, 20, 22, 23, 24, 27, 28, 29, 30, 0};
extern struct Sprite* sprite_chopter;

void Start_StateGame() {
	UINT8 i;

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	InitScrollTiles(0, &tiles_beach, bank_tiles_beach);
	InitScroll(beachWidth, beachHeight, beach, collision_tiles, 0, 3);

	scroll_target = sprite_chopter;
	InitScroll(beachWidth, beachHeight, beach, collision_tiles, 0, 3); //Init again with the camera placed in the right position
	SHOW_BKG;

	INIT_CONSOLE(font, 3, 2);
}

void Update_StateGame() {
}