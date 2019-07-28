#include "Banks/SetBank2.h"

#include "..\res\src\tiles_beach.h"
#include "..\res\src\beach.h"
#include "..\res\src\beach_lvl2.h"
#include "..\res\src\beach_lvl3.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"

#include "Print.h"
#include "../res/src/font.h"

UINT8 collision_tiles[] = {1, 2, 3, 6, 12, 13, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 33, 39, 0};
extern struct Sprite* sprite_chopter;

struct LevelData {
	UINT16 w;
	UINT16 h;
	UINT8* data;
	UINT8 bank;
};

UINT8 current_level = 0;
UINT16 level_done = 0;
struct LevelData level_datas[] = {
	{beachWidth, beachHeight, beach, 3},
	{beach_lvl2Width, beach_lvl2Height, beach_lvl2, 3},
	{beach_lvl3Width, beach_lvl3Height, beach_lvl3, 3}
};
UINT8 num_levels = 3;

void Start_StateGame() {
	UINT8 i;
	struct LevelData* level = &level_datas[current_level];

	level_done = 0;

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	InitScrollTiles(0, &tiles_beach, bank_tiles_beach);
	InitScroll(level->w, level->h, level->data, collision_tiles, 0, level->bank);

	scroll_target = sprite_chopter;
	InitScroll(level->w, level->h, level->data, collision_tiles, 0, level->bank); //Init again with the camera placed in the right position
	SHOW_BKG;

	INIT_CONSOLE(font, 3, 2);
}

void Update_StateGame() {
#ifndef NDEBUG
	if(KEY_TICKED(J_START)) {
		current_level ++;
		SetState(StateGame);
	}
#endif
	if(level_done) {
		level_done ++;
		if(level_done > 120) {
			level_done = 0;
			current_level ++;
			SetState(StateCoverWin);
		}
	}
}