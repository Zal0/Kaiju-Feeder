#include "Banks/SetBank2.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Print.h"

#include "../res/src/font.h"


extern unsigned char cover_dat[];
extern unsigned char cover_map[];

extern UINT8 current_level;

void Start_StateCover() {
	InitScrollTilesLEGACY(0, 93, cover_dat, 3);
	InitScroll(20, 18, cover_map, 0, 0, 3);
	SHOW_BKG;
	HIDE_WIN;

	INIT_FONT(font, PRINT_BKG);
	PRINT(0, 14, "EMILIO J. DOMINGUEZ");
	PRINT(7, 15, "ZALO");
	PRINT(4, 17, "ZGBJAM2 2019");

	current_level = 0;
}

void Update_StateCover() {
	if(keys != 0) {
		SetState(StateCoverWin);
	}
}