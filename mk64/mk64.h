#ifndef _MK64_H_
#define _MK64_H_

extern "C" {

#include <n64.h>
#include "types.h"

#define NUM_RACERS  8
#define MAX_PLAYERS 4

#include "audio/audio.h"
#include "characters/characters.h"
#include "controls/controls.h"
#include "courses/courses.h"
#include "courses/courseObjects.h"
#include "courses/surfaces.h"
#include "courses/trackload.h"
#include "debug/debug.h"
#include "game/ai.h"
#include "game/gamestate.h"
#include "game/physics.h"
#include "game/playerstates.h"
#include "game/race.h"
#include "items/items.h"
#include "math/random.h"
#include "memory/eeprom.h"
#include "memory/memory.h"
#include "memory/rsp.h"
#include "menus/menus.h"
#include "menus/text.h"
#include "video/camera.h"
#include "video/gfx.h"
#include "video/hud.h"
#include "video/tkmk.h"

} //extern "C"

#endif //_MK64_H_
