#include "Banks/SetBank2.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Print.h"

#include "../res/src/font.h"


extern struct TilesInfo win_tiles;
extern struct MapInfo win;

extern UINT8 current_level;
extern UINT8 num_levels;

void Start_StateCoverWin() {
	InitScrollTiles(0, &win_tiles);
	InitScroll(&win, 0, 0);
	SHOW_BKG;
	HIDE_WIN;

	INIT_FONT(font, PRINT_BKG);
	if(current_level == num_levels){
		PRINT(2, 12, "CONGRATULATIONS!!");
		PRINT(5, 14, "THANKS FOR");
		PRINT(7, 15, "PLAYING");
	} else {
		PRINT_POS(7, 15);
		Printf("Level %d", (UINT16)(current_level + 1));
	}
}

void Update_StateCoverWin() {
	if(current_level == num_levels) {

	} else {
		if(KEY_TICKED(0xFF)) {
			SetState(StateGame);
		}
	}
}