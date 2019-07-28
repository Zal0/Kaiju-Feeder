#include "Banks/SetBank2.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Print.h"

#include "../res/src/font.h"


extern unsigned char win_dat[];
extern unsigned char win_map[];

extern UINT8 current_level;
extern UINT8 num_levels;

void Start_StateCoverWin() {
	InitScrollTilesLEGACY(0, 46, win_dat, 3);
	InitScroll(20, 18, win_map, 0, 0, 3);
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
		if(keys != 0) {
			SetState(StateGame);
		}
	}
}