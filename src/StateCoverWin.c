#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Print.h"

IMPORT_TILES(font);
IMPORT_MAP(win);

extern UINT8 current_level;
extern UINT8 num_levels;

void START() {
	InitScroll(BANK(win), &win, 0, 0);

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

void UPDATE() {
	if(current_level == num_levels) {

	} else {
		if(KEY_TICKED(0xFF)) {
			SetState(StateGame);
		}
	}
}