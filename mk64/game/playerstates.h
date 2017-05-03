typedef struct { //3544 bytes (0xDD8)
   /* 0x0000 - 800F6990 */ u32 state_00;
       //I think this is the highest byte:
       //0x80: 1=exists, 0=doesn't
       //0x40: 1=human controlled (allows controller to pause game)
       //0x20: 1=frozen in place because race hasn't started yet
       //0x10: 1=CPU controlled (even when 0x40 also set)
       //0x08: 1=has finished race
       //0x04: ?
       //0x02: 1=is driving to starting line
       //0x01: 1=is a ghost
   /* 0x0004 - 800F6994 */ u32 unk_04;
   /* 0x0008 - 800F6998 */ u32 unk_08;
   /* 0x000C - 800F699C */ u32 stateActivator;
       //0x 8000 0000:
       //0x 4000 0000:
       //0x 2000 0000:
       //0x 1000 0000: spin out
       //0x 0800 0000:
       //0x 0400 0000: Boo (invisible)
       //0x 0200 0000: start boost
       //0x 0100 0000: hit by shell
       //0x 0080 0000: dash zone
       //0x 0040 0000: hit by chomp, bomb, train etc
       //0x 0020 0000: hit by spiny/crab
       //0x 0010 0000:
       //0x 0008 0000: hit by boat
       //0x 0004 0000: towing item
       //0x 0002 0000: large feather jump (unused)
       //0x 0001 0000:
       //0x 0000 8000: weak shroom (unused?)
       //0x 0000 4000: lightning
       //0x 0000 2000: star
       //0x 0000 1000: small feather jump (unused)
       //0x 0000 0800: Boo (translucent)
       //0x 0000 0400:
       //0x 0000 0200: shroom
       //0x 0000 0100: squished
       //0x 0000 0080: spinout start
       //0x 0000 0040:
       //0x 0000 0020:
       //0x 0000 0010:
       //0x 0000 0008:
       //0x 0000 0004: hit by green shell
       //0x 0000 0002: hit by mole
       //0x 0000 0001: spin out (again?)
   /* 0x0010 - 800F69A0 */ u32 unk_10;
   /* 0x0014 - 800F69A4 */ vec3f    position;
   /* 0x0020 - 800F69B0 */ u32 unk_20;
   /* 0x0024 - 800F69B4 */ u32 unk_24;
   /* 0x0028 - 800F69B8 */ u32 unk_28;
   /* 0x002C - 800F69BC */ u16 unk_2C;
   /* 0x002E - 800F69BE */ u16 rotationV;
   /* 0x0030 - 800F69C0 */ u32 unk_30;
   /* 0x0034 - 800F69C4 */ u32 unk_34;
   /* 0x0038 - 800F69C8 */ float    velY;
   /* 0x003C - 800F69CC */ u32 unk_3C;
   /* 0x0040 - 800F69D0 */ u32 unk_40;
   /* 0x0044 - 800F69D4 */ u32 trophyAnim; //set to 24 during trophy seq
   /* 0x0048 - 800F69D8 */ u32 unk_48;
   /* 0x004C - 800F69DC */ u32 unk_4C;
   /* 0x0050 - 800F69E0 */ u32 unk_50;
   /* 0x0054 - 800F69E4 */ u32 unk_54;
   /* 0x0058 - 800F69E8 */ u32 unk_58;
   /* 0x005C - 800F69EC */ u32 unk_5C;
   /* 0x0060 - 800F69F0 */ u32 unk_60;
   /* 0x0064 - 800F69F4 */ u32 unk_64;
   /* 0x0068 - 800F69F8 */ u32 unk_68;
   /* 0x006C - 800F69FC */ u32 unk_6C;
   /* 0x0070 - 800F6A00 */ float    cameraY_unknown;
   /* 0x0074 - 800F6A04 */ u32 unk_74;
   /* 0x0078 - 800F6A08 */ u32 unk_78;
   /* 0x007C - 800F6A0C */ u32 unk_7C;
   /* 0x0080 - 800F6A10 */ float    minSpeed; //used when boosting
   /* 0x0084 - 800F6A14 */ u32 unk_84;
   /* 0x0088 - 800F6A18 */ u32 unk_88;
   /* 0x008C - 800F6A1C */ u32 unk_8C;
   /* 0x0090 - 800F6A20 */ u32 unk_90;
   /* 0x0094 - 800F6A24 */ u32 unk_94;
   /* 0x0098 - 800F6A28 */ u32 unk_98;
   /* 0x009C - 800F6A2C */ float    speed;
   /* 0x00A0 - 800F6A30 */ u32 unk_A0;
   /* 0x00A4 - 800F6A34 */ u32 unk_A4;
   /* 0x00A8 - 800F6A38 */ u32 unk_A8;
   /* 0x00AC - 800F6A3C */ u32 unk_AC;
   /* 0x00B0 - 800F6A40 */ u16 shrinkTimer;
   /* 0x00B2 - 800F6A42 */ u16 unk_B2; //"feather use sequence/some spinouts"
   /* 0x00B4 - 800F6A44 */ u32 animState_B4; //XXX name
       //0x 0000 1000: shell hit
       //0x 0000 0800: BOING!
       //0x 0000 0100: POOMP!
       //0x 0000 0040: CRASH
       //0x 0000 0020: music note (avoided spinout)
   /* 0x00B8 - 800F6A48 */ u32 unk_B8;
   /* 0x00BC - 800F6A4C */ u32 animState_BC; //XXX name
       //0x 8000 0000: Boo active
       //0x 4000 0000: hit by lightning
       //0x 2000 0000: sliding outward
       //0x 1000 0000:
       //0x 0800 0000: un-flattening
       //0x 0400 0000: flattened
       //0x 0200 0000: tumbling from green shell
       //0x 0100 0000: tumbling from fake item
       //0x 0080 0000: large feather jump active (unused)
       //0x 0040 0000: "REVERSE"
       //0x 0020 0000: draft boost
       //0x 0010 0000: dash zone boost
       //0x 0008 0000: small feather jump active (unused)
       //0x 0004 0000:
       //0x 0002 0000: slightly off ground
       //0x 0001 0000: wall tumble
       //0x 0000 8000: hit a penguin
       //0x 0000 4000:
       //0x 0000 2000: shrooming
       //0x 0000 1000: CPU controlled after losing race
       //0x 0000 0800: spinning out from banana
       //0x 0000 0400: tumble rotation
       //0x 0000 0200: star power
       //0x 0000 0100: mini turbo boosting
       //0x 0000 0080: spinning out from object hit
       //0x 0000 0040: spin out "WHIRRR!"
       //0x 0000 0020: A+B spinning
       //0x 0000 0010: fast enough to slide/BOING!
       //0x 0000 0008: off ground
       //0x 0000 0004: zipper boost
       //0x 0000 0002: jumped (pressed R)
       //0x 0000 0001: braking
   /* 0x00C0 - 800F6A50 */ u32 unk_C0;
   /* 0x00C4 - 800F6A50 */ u32 unk_C4;
   /* 0x00C8 - 800F6A58 */ u32 animState_C8; //XXX name
       //0x 0000 2000: dripping water
       //0x 0000 1000: smoking
       //0x 0000 0100: over out-of-bounds
       //0x 0000 0080: frozen
       //0x 0000 0020: defrosting
       //0x 0000 0010: frosty after thawing
       //0x 0000 0008: stuck out of bounds (waiting for lakitu)
       //0x 0000 0004: fading out (from lakitu)
       //0x 0000 0002: held by lakitu
       //0x 0000 0001: out of bounds in water
   /* 0x00CC - 800F6A5C */ u32 unk_CC;
   /* 0x00D0 - 800F6A60 */ u32 unk_D0;
   /* 0x00D4 - 800F6A64 */ u32 unk_D4;
   /* 0x00D8 - 800F6A68 */ u32 unk_D8;
   /* 0x00DC - 800F6A6C */ u32 unk_DC;
   /* 0x00E0 - 800F6A70 */ u32 unk_E0;
   /* 0x00E4 - 800F6A74 */ u32 unk_E4;
   /* 0x00E8 - 800F6A78 */ u32 unk_E8;
   /* 0x00EC - 800F6A7C */ u32 unk_EC;
   /* 0x00F0 - 800F6A80 */ u32 unk_F0;
   /* 0x00F4 - 800F6A84 */ u32 unk_F4;
   /* 0x00F8 - 800F6A88 */ u32 unk_F8;
   /* 0x00FC - 800F6A8C */ float    weight;
   /* 0x0100 - 800F6A90 */ u32 unk_100;
   /* 0x0104 - 800F6A94 */ u32 unk_104;
   /* 0x0108 - 800F6A98 */ u32 unk_108;
   /* 0x010C - 800F6A9C */ u32 unk_10C;
   /* 0x0110 - 800F6AA0 */ u32 unk_110;
   /* 0x0114 - 800F6AA4 */ u32 unk_114;
   /* 0x0118 - 800F6AA8 */ u32 unk_118;
   /* 0x011C - 800F6AAC */ u32 unk_11C;
   /* 0x0120 - 800F6AB0 */ u32 unk_120;
   /* 0x0124 - 800F6AB4 */ u32 unk_124;
   /* 0x0128 - 800F6AB8 */ u32 unk_128;
   /* 0x012C - 800F6ABC */ u32 unk_12C;
   /* 0x0130 - 800F6AC0 */ u32 unk_130;
   /* 0x0134 - 800F6AC4 */ u32 unk_134;
   /* 0x0138 - 800F6AC8 */ u32 unk_138;
   /* 0x013C - 800F6ACC */ u32 unk_13C;
   /* 0x0140 - 800F6AD0 */ u32 unk_140;
   /* 0x0144 - 800F6AD4 */ u32 animState_144;
       //0x40: spin-out swerve
       //0x20: "no kart roll"
       //0x10: bonk
       //0x08: freeze in air, sets 0x10
       //0x04: spin-out bonk, sets 0x08
       //0x02: smoke from activating Boo
       //0x01: smoke from landing huge jump
   /* 0x0148 - 800F6AD8 */ u32 unk_148;
   /* 0x014C - 800F6ADC */ u32 unk_14C;
   /* 0x0150 - 800F6AE0 */ u32 unk_150;
   /* 0x0154 - 800F6AE4 */ u32 unk_154;
   /* 0x0158 - 800F6AE8 */ u32 unk_158;
   /* 0x015C - 800F6AEC */ u32 unk_15C;
   /* 0x0160 - 800F6AF0 */ u32 unk_160;
   /* 0x0164 - 800F6AF4 */ u32 unk_164;
   /* 0x0168 - 800F6AF8 */ u32 unk_168;
   /* 0x016C - 800F6AFC */ u32 unk_16C;
   /* 0x0170 - 800F6B00 */ u32 unk_170;
   /* 0x0174 - 800F6B04 */ u32 unk_174;
   /* 0x0178 - 800F6B08 */ u32 unk_178;
   /* 0x017C - 800F6B0C */ u32 unk_17C;
   /* 0x0180 - 800F6B10 */ u32 unk_180;
   /* 0x0184 - 800F6B14 */ u32 unk_184;
   /* 0x0188 - 800F6B18 */ u32 unk_188;
   /* 0x018C - 800F6B1C */ u32 unk_18C;
   /* 0x0190 - 800F6B20 */ u32 unk_190;
   /* 0x0194 - 800F6B24 */ u32 unk_194;
   /* 0x0198 - 800F6B28 */ u32 unk_198;
   /* 0x019C - 800F6B2C */ u32 unk_19C;
   /* 0x01A0 - 800F6B30 */ u32 unk_1A0;
   /* 0x01A4 - 800F6B34 */ u32 unk_1A4;
   /* 0x01A8 - 800F6B38 */ u32 unk_1A8;
   /* 0x01AC - 800F6B3C */ u32 unk_1AC;
   /* 0x01B0 - 800F6B40 */ u32 unk_1B0;
   /* 0x01B4 - 800F6B44 */ u32 unk_1B4;
   /* 0x01B8 - 800F6B48 */ u32 unk_1B8;
   /* 0x01BC - 800F6B4C */ u32 unk_1BC;
   /* 0x01C0 - 800F6B50 */ u32 unk_1C0;
   /* 0x01C4 - 800F6B54 */ u32 unk_1C4;
   /* 0x01C8 - 800F6B58 */ u32 unk_1C8;
   /* 0x01CC - 800F6B5C */ u32 unk_1CC;
   /* 0x01D0 - 800F6B60 */ u32 unk_1D0;
   /* 0x01D4 - 800F6B64 */ u32 unk_1D4;
   /* 0x01D8 - 800F6B68 */ u32 unk_1D8;
   /* 0x01DC - 800F6B6C */ u32 unk_1DC;
   /* 0x01E0 - 800F6B70 */ u32 unk_1E0;
   /* 0x01E4 - 800F6B74 */ float    slightTilt;
   /* 0x01E8 - 800F6B78 */ u32 unk_1E8;
   /* 0x01EC - 800F6B7C */ u32 unk_1EC;
   /* 0x01F0 - 800F6B80 */ u32 unk_1F0;
   /* 0x01F4 - 800F6B84 */ u32 unk_1F4;
   /* 0x01F8 - 800F6B88 */ u32 unk_1F8;
   /* 0x01FC - 800F6B8C */ u32 unk_1FC;
   /* 0x0200 - 800F6B90 */ u32 unk_200;
   /* 0x0204 - 800F6B94 */ u32 unk_204;
   /* 0x0208 - 800F6B98 */ u32 unk_208;
   /* 0x020C - 800F6B9C */ u32 unk_20C;
   /* 0x0210 - 800F6BA0 */ u32 unk_210;
   /* 0x0214 - 800F6BA4 */ float    maxSpeed;
   /* 0x0218 - 800F6BA8 */ u32 unk_218;
   /* 0x021C - 800F6BAC */ u32 unk_21C;
   /* 0x0220 - 800F6BB0 */ u32 unk_220;
   /* 0x0224 - 800F6BB4 */ float    size;
   /* 0x0228 - 800F6BB8 */ u32 unk_228;
   /* 0x022C - 800F6BBC */ u32 unk_22C;
   /* 0x0230 - 800F6BC0 */ u16 rotationH;
   /* 0x0232 - 800F6BC2 */ u16 unk_232;
   /* 0x0234 - 800F6BC4 */ u32 unk_234;
   /* 0x0238 - 800F6BC8 */ u32 unk_238;
   /* 0x023C - 800F6BCC */ u32 unk_23C;
   /* 0x0240 - 800F6BD0 */ u32 unk_240;
   /* 0x0244 - 800F6BD4 */ u32 unk_244;
   /* 0x0248 - 800F6BD8 */ u32 unk_248;
   /* 0x024C - 800F6BDC */ u32 unk_24C;
   /* 0x0250 - 800F6BE0 */ u32 unk_250;
   /* 0x0254 - 800F6BE4 */ u32 unk_254; //merge characters thing
   /* 0x0258 - 800F6BE8 */ u32 unk_258;
   /* 0x025C - 800F6BEC */ u32 unk_25C;
   /* 0x0260 - 800F6BF0 */ u32 unk_260;
   /* 0x0264 - 800F6BF4 */ float    smokeSize;
   /* 0x0268 - 800F6BF8 */ u32 unk_268;
   /* 0x026C - 800F6BFC */ u32 unk_26C;
   /* 0x0270 - 800F6C00 */ u32 unk_270;
   /* 0x0274 - 800F6C04 */ u32 unk_274;
   /* 0x0278 - 800F6C08 */ u32 unk_278;
   /* 0x027C - 800F6C0C */ u32 unk_27C;
   /* 0x0280 - 800F6C10 */ u32 unk_280;
   /* 0x0284 - 800F6C14 */ u32 unk_284;
   /* 0x0288 - 800F6C18 */ u32 unk_288;
   /* 0x028C - 800F6C1C */ u32 unk_28C;
   /* 0x0290 - 800F6C20 */ u32 unk_290;
   /* 0x0294 - 800F6C24 */ u32 unk_294;
   /* 0x0298 - 800F6C28 */ u32 unk_298;
   /* 0x029C - 800F6C2C */ u32 unk_29C;
   /* 0x02A0 - 800F6C30 */ u32 unk_2A0;
   /* 0x02A4 - 800F6C34 */ u32 unk_2A4;
   /* 0x02A8 - 800F6C38 */ u32 unk_2A8;
   /* 0x02AC - 800F6C3C */ u32 unk_2AC;
   /* 0x02B0 - 800F6C40 */ u32 unk_2B0;
   /* 0x02B4 - 800F6C44 */ u32 unk_2B4;
   /* 0x02B8 - 800F6C48 */ u32 unk_2B8;
   /* 0x02BC - 800F6C4C */ u32 unk_2BC;
   /* 0x02C0 - 800F6C80 */ u32 unk_2C0;
   /* 0x02C4 - 800F6C84 */ u32 unk_2C4;
   /* 0x02C8 - 800F6C88 */ u32 unk_2C8;
   /* 0x02CC - 800F6C8C */ u32 unk_2CC;
   /* 0x02D0 - 800F6C90 */ u32 unk_2D0;
   /* 0x02D4 - 800F6C94 */ u32 unk_2D4;
   /* 0x02D8 - 800F6C98 */ u32 unk_2D8;
   /* 0x02DC - 800F6C9C */ u32 unk_2DC;
   /* 0x02E0 - 800F6CA0 */ u32 unk_2E0;
   /* 0x02E4 - 800F6CA4 */ u32 unk_2E4;
   /* 0x02E8 - 800F6CA8 */ u32 unk_2E8;
   /* 0x02EC - 800F6CAC */ u32 unk_2EC;
   /* 0x02F0 - 800F6CB0 */ u32 unk_2F0;
   /* 0x02F4 - 800F6CB4 */ u32 unk_2F4;
   /* 0x02F8 - 800F6CB8 */ u32 unk_2F8;
   /* 0x02FC - 800F6CBC */ u32 unk_2FC;

   /* 0x0300 - 800F6CC0 */
   u32 unk_300, unk_304, unk_308, unk_30C;
   u32 unk_310, unk_314, unk_318, unk_31C;
   u32 unk_320, unk_324, unk_328, unk_32C;
   u32 unk_330, unk_334, unk_338, unk_33C;
   u32 unk_340, unk_344, unk_348, unk_34C;
   u32 unk_350, unk_354, unk_358, unk_35C;
   u32 unk_360, unk_364, unk_368, unk_36C;
   u32 unk_370, unk_374, unk_378, unk_37C;
   u32 unk_380, unk_384, unk_388, unk_38C;
   u32 unk_390, unk_394, unk_398, unk_39C;
   u32 unk_3A0, unk_3A4, unk_3A8, unk_3AC;
   u32 unk_3B0, unk_3B4, unk_3B8, unk_3BC;
   u32 unk_3C0, unk_3C4, unk_3C8, unk_3CC;
   u32 unk_3D0, unk_3D4, unk_3D8, unk_3DC;
   u32 unk_3E0, unk_3E4, unk_3E8, unk_3EC;
   u32 unk_3F0, unk_3F4, unk_3F8, unk_3FC;

   /* 0x0400 - 800F6DC0 */
   u32 unk_400, unk_404, unk_408, unk_40C;
   u32 unk_410, unk_414, unk_418, unk_41C;
   u32 unk_420, unk_424, unk_428, unk_42C;
   u32 unk_430, unk_434, unk_438, unk_43C;
   u32 unk_440, unk_444, unk_448, unk_44C;
   u32 unk_450, unk_454, unk_458, unk_45C;
   u32 unk_460, unk_464, unk_468, unk_46C;
   u32 unk_470, unk_474, unk_478, unk_47C;
   u32 unk_480, unk_484, unk_488, unk_48C;
   u32 unk_490, unk_494, unk_498, unk_49C;
   u32 unk_4A0, unk_4A4, unk_4A8, unk_4AC;
   u32 unk_4B0, unk_4B4, unk_4B8, unk_4BC;
   u32 unk_4C0, unk_4C4, unk_4C8, unk_4CC;
   u32 unk_4D0, unk_4D4, unk_4D8, unk_4DC;
   u32 unk_4E0, unk_4E4, unk_4E8, unk_4EC;
   u32 unk_4F0, unk_4F4, unk_4F8, unk_4FC;

   /* 0x0500 - 800F6EC0 */
   u32 unk_500, unk_504, unk_508, unk_50C;
   u32 unk_510, unk_514, unk_518, unk_51C;
   u32 unk_520, unk_524, unk_528, unk_52C;
   u32 unk_530, unk_534, unk_538, unk_53C;
   u32 unk_540, unk_544, unk_548, unk_54C;
   u32 unk_550, unk_554, unk_558, unk_55C;
   u32 unk_560, unk_564, unk_568, unk_56C;
   u32 unk_570, unk_574, unk_578, unk_57C;
   u32 unk_580, unk_584, unk_588, unk_58C;
   u32 unk_590, unk_594, unk_598, unk_59C;
   u32 unk_5A0, unk_5A4, unk_5A8, unk_5AC;
   u32 unk_5B0, unk_5B4, unk_5B8, unk_5BC;
   u32 unk_5C0, unk_5C4, unk_5C8, unk_5CC;
   u32 unk_5D0, unk_5D4, unk_5D8, unk_5DC;
   u32 unk_5E0, unk_5E4, unk_5E8, unk_5EC;
   u32 unk_5F0, unk_5F4, unk_5F8, unk_5FC;

   /* 0x0600 - 800F6FC0 */
   u32 unk_600, unk_604, unk_608, unk_60C;
   u32 unk_610, unk_614, unk_618, unk_61C;
   u32 unk_620, unk_624, unk_628, unk_62C;
   u32 unk_630, unk_634, unk_638, unk_63C;
   u32 unk_640, unk_644, unk_648, unk_64C;
   u32 unk_650, unk_654, unk_658, unk_65C;
   u32 unk_660, unk_664, unk_668, unk_66C;
   u32 unk_670, unk_674, unk_678, unk_67C;
   u32 unk_680, unk_684, unk_688, unk_68C;
   u32 unk_690, unk_694, unk_698, unk_69C;
   u32 unk_6A0, unk_6A4, unk_6A8, unk_6AC;
   u32 unk_6B0, unk_6B4, unk_6B8, unk_6BC;
   u32 unk_6C0, unk_6C4, unk_6C8, unk_6CC;
   u32 unk_6D0, unk_6D4, unk_6D8, unk_6DC;
   u32 unk_6E0, unk_6E4, unk_6E8, unk_6EC;
   u32 unk_6F0, unk_6F4, unk_6F8, unk_6FC;

   /* 0x0700 - 800F70C0 */
   u32 unk_700, unk_704, unk_708, unk_70C;
   u32 unk_710, unk_714, unk_718, unk_71C;
   u32 unk_720, unk_724, unk_728, unk_72C;
   u32 unk_730, unk_734, unk_738, unk_73C;
   u32 unk_740, unk_744, unk_748, unk_74C;
   u32 unk_750, unk_754, unk_758, unk_75C;
   u32 unk_760, unk_764, unk_768, unk_76C;
   u32 unk_770, unk_774, unk_778, unk_77C;
   u32 unk_780, unk_784, unk_788, unk_78C;
   u32 unk_790, unk_794, unk_798, unk_79C;
   u32 unk_7A0, unk_7A4, unk_7A8, unk_7AC;
   u32 unk_7B0, unk_7B4, unk_7B8, unk_7BC;
   u32 unk_7C0, unk_7C4, unk_7C8, unk_7CC;
   u32 unk_7D0, unk_7D4, unk_7D8, unk_7DC;
   u32 unk_7E0, unk_7E4, unk_7E8, unk_7EC;
   u32 unk_7F0, unk_7F4, unk_7F8, unk_7FC;

   /* 0x0800 - 800F71C0 */
   u32 unk_800, unk_804, unk_808, unk_80C;
   u32 unk_810, unk_814, unk_818, unk_81C;
   u32 unk_820, unk_824, unk_828, unk_82C;
   u32 unk_830, unk_834, unk_838, unk_83C;
   u32 unk_840, unk_844, unk_848, unk_84C;
   u32 unk_850, unk_854, unk_858, unk_85C;
   u32 unk_860, unk_864, unk_868, unk_86C;
   u32 unk_870, unk_874, unk_878, unk_87C;
   u32 unk_880, unk_884, unk_888, unk_88C;
   u32 unk_890, unk_894, unk_898, unk_89C;
   u32 unk_8A0, unk_8A4, unk_8A8, unk_8AC;
   u32 unk_8B0, unk_8B4, unk_8B8, unk_8BC;
   u32 unk_8C0, unk_8C4, unk_8C8, unk_8CC;
   u32 unk_8D0, unk_8D4, unk_8D8, unk_8DC;
   u32 unk_8E0, unk_8E4, unk_8E8, unk_8EC;
   u32 unk_8F0, unk_8F4, unk_8F8, unk_8FC;

   /* 0x0900 - 800F72C0 */
   u32 unk_900, unk_904, unk_908, unk_90C;
   u32 unk_910, unk_914, unk_918, unk_91C;
   u32 unk_920, unk_924, unk_928, unk_92C;
   u32 unk_930, unk_934, unk_938, unk_93C;
   u32 unk_940, unk_944, unk_948, unk_94C;
   u32 unk_950, unk_954, unk_958, unk_95C;
   u32 unk_960, unk_964, unk_968, unk_96C;
   u32 unk_970, unk_974, unk_978, unk_97C;
   u32 unk_980, unk_984, unk_988, unk_98C;
   u32 unk_990, unk_994, unk_998, unk_99C;
   u32 unk_9A0, unk_9A4, unk_9A8, unk_9AC;
   u32 unk_9B0, unk_9B4, unk_9B8, unk_9BC;
   u32 unk_9C0, unk_9C4, unk_9C8, unk_9CC;
   u32 unk_9D0, unk_9D4, unk_9D8, unk_9DC;
   u32 unk_9E0, unk_9E4, unk_9E8, unk_9EC;
   u32 unk_9F0, unk_9F4, unk_9F8, unk_9FC;

   /* 0x0A00 - 800F73C0 */
   u32 unk_A00, unk_A04, unk_A08, unk_A0C;
   u32 unk_A10, unk_A14, unk_A18, unk_A1C;
   u32 unk_A20, unk_A24, unk_A28, unk_A2C;
   u32 unk_A30, unk_A34, unk_A38, unk_A3C;
   u32 unk_A40, unk_A44, unk_A48, unk_A4C;
   u32 unk_A50, unk_A54, unk_A58, unk_A5C;
   u32 unk_A60, unk_A64, unk_A68, unk_A6C;
   u32 unk_A70, unk_A74, unk_A78, unk_A7C;
   u32 unk_A80, unk_A84, unk_A88, unk_A8C;
   u32 unk_A90, unk_A94, unk_A98, unk_A9C;
   u32 unk_AA0, unk_AA4, unk_AA8, unk_AAC;
   u32 unk_AB0, unk_AB4, unk_AB8, unk_ABC;
   u32 unk_AC0, unk_AC4, unk_AC8, unk_ACC;
   u32 unk_AD0, unk_AD4, unk_AD8, unk_ADC;
   u32 unk_AE0, unk_AE4, unk_AE8, unk_AEC;
   u32 unk_AF0, unk_AF4, unk_AF8, unk_AFC;

   /* 0x0B00 - 800F74C0 */
   u32 unk_B00, unk_B04, unk_B08, unk_B0C;
   u32 unk_B10, unk_B14, unk_B18, unk_B1C;
   u32 unk_B20, unk_B24, unk_B28, unk_B2C;
   u32 unk_B30, unk_B34, unk_B38, unk_B3C;
   u32 unk_B40, unk_B44, unk_B48, unk_B4C;
   u32 unk_B50, unk_B54, unk_B58, unk_B5C;
   u32 unk_B60, unk_B64, unk_B68, unk_B6C;
   u32 unk_B70, unk_B74, unk_B78, unk_B7C;
   u32 unk_B80, unk_B84, unk_B88, unk_B8C;
   u32 unk_B90, unk_B94, unk_B98, unk_B9C;
   u32 unk_BA0, unk_BA4, unk_BA8, unk_BAC;
   u32 unk_BB0, unk_BB4, unk_BB8, unk_BBC;
   u32 unk_BC0, unk_BC4, unk_BC8, unk_BCC;
   u32 unk_BD0, unk_BD4, unk_BD8, unk_BDC;
   u32 unk_BE0, unk_BE4, unk_BE8, unk_BEC;
   u32 unk_BF0, unk_BF4, unk_BF8, unk_BFC;

   /* 0x0C00 - 800F75C0 */
   u32 unk_C00, unk_C04, unk_C08, unk_C0C;
   u32 unk_C10, unk_C14, unk_C18, unk_C1C;
   u32 unk_C20, unk_C24, unk_C28, unk_C2C;
   u32 unk_C30, unk_C34, unk_C38, unk_C3C;
   u32 unk_C40, unk_C44, unk_C48, unk_C4C;
   u32 unk_C50, unk_C54, unk_C58, unk_C5C;
   u32 unk_C60, unk_C64, unk_C68, unk_C6C;
   u32 unk_C70, unk_C74, unk_C78, unk_C7C;
   u32 unk_C80, unk_C84, unk_C88, unk_C8C;
   u32 unk_C90, unk_C94, unk_C98, unk_C9C;
   u32 unk_CA0, unk_CA4, unk_CA8, unk_CAC;
   u32 unk_CB0, unk_CB4, unk_CB8, unk_CBC;
   u32 unk_CC0, unk_CC4, unk_CC8, unk_CCC;
   u32 unk_CD0, unk_CD4, unk_CD8, unk_CDC;
   u32 unk_CE0, unk_CE4, unk_CE8, unk_CEC;
   u32 unk_CF0, unk_CF4, unk_CF8, unk_CFC;

   /* 0x0D00 - 800F76C0 */
   u32 unk_D00, unk_D04, unk_D08, unk_D0C;
   u32 unk_D10, unk_D14, unk_D18, unk_D1C;
   u32 unk_D20, unk_D24, unk_D28, unk_D2C;
   u32 unk_D30, unk_D34, unk_D38, unk_D3C;
   u32 unk_D40, unk_D44, unk_D48, unk_D4C;
   u32 unk_D50, unk_D54, unk_D58, unk_D5C;
   u32 unk_D60, unk_D64, unk_D68, unk_D6C;
   u32 unk_D70, unk_D74, unk_D78, unk_D7C;
   u32 unk_D80, unk_D84, unk_D88, unk_D8C;
   u32 unk_D90, unk_D94, unk_D98, unk_D9C;
   u32 unk_DA0, unk_DA4, unk_DA8, unk_DAC;
   u32 unk_DB0, unk_DB4, unk_DB8, unk_DBC;
   u32 unk_DC0, unk_DC4, unk_DC8, unk_DCC;
   u32 unk_DD0, unk_DD4;
} Player;
extern Player player[NUM_RACERS];

extern s16 player1_character;
extern int player1_underwater;
