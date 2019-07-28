#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, helo)\
_SPRITE_DMG(SpriteGancho, gancho)\
_SPRITE_DMG(SpriteRope, bolita)\
_SPRITE_DMG(SpritePollo, pollo)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif