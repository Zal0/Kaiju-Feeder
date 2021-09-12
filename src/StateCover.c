#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Print.h"

IMPORT_TILES(font);

IMPORT_MAP(cover);
IMPORT_TILES(font);

extern UINT8 current_level;

void Start_StateCover() {
	InitScroll(BANK(cover), &cover, 0, 0);

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