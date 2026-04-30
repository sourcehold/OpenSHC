/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/UnitPropertiesDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Map/AnimationFrameData.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"
#include "OpenSHC/Util/FunctionTypes/NoArgCallback.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::AnimationFrameData;
        using OpenSHC::Map::Navigation::Algorithms::XYPair;
        using OpenSHC::Util::FunctionTypes::NoArgCallback;

#pragma pack(push, 1)
        // SIZE: 0x0001226C
        typedef struct UnitPropertiesDefinedData {

            byte ANIM_Frames_Shared_UnitClimbingDown[20]; // 0x00000000 length: 20
            NoArgCallback* PTR_UpdateUnitFunctions[80]; // 0x00000014 length: 320
            int DAT_SPRITE_ID[80]; // 0x00000154 length: 320
            int DAT_GRAPHIC_SIZE[80]; // 0x00000294 length: 320
            int DAT_COMPUTER_CONTROLLED[80]; // 0x000003D4 length: 320
            int DAT_COMPUTER_MANAGED[80]; // 0x00000514 length: 320
            int DAT_UNIT_MOVEMENT_SPEED_ARRAY[80]; // 0x00000654 length: 320
            int DAT_ABLE_TO_CLIMB_TOWERS[80]; // 0x00000794 length: 320
            int DAT_UNIT_MOVABLE[80]; // 0x000008D4 length: 320
            int DAT_BASE_HP[80]; // 0x00000A14 length: 320
            int DAT_ARROW_DAMAGE[80]; // 0x00000B54 length: 320
            int DAT_STONE_DAMAGE[80]; // 0x00000C94 length: 320
            int DAT_BOLT_DAMAGE[80]; // 0x00000DD4 length: 320
            int DAT_MELEE_DAMAGE[80][80]; // 0x00000F14 length: 25600
            int DAT_EuroUnitResourceCosts[7][4]; // 0x00007314 length: 112
            undefined1 padding_0x7384[48]; // 0x00007384 length: 48
            int DAT_UNIT_CLIMB[80]; // 0x000073B4 length: 320
            int DAT_SomeUnitStatMatrix4[80]; // 0x000074F4 length: 320
            int field65_0x7634[80]; // 0x00007634 length: 320
            int field66_0x7774[80]; // 0x00007774 length: 320
            int DAT_SomeUnitStatMatrix5[80]; // 0x000078B4 length: 320
            int DAT_NotBlessableUnits[80]; // 0x000079F4 length: 320
            int DAT_UNIT_CAN_MELEE[80]; // 0x00007B34 length: 320
            int DAT_UNIT_ENEMY_NOTICE_RANGE[80]; // 0x00007C74 length: 320
            int DAT_UnitClimbStateFlags[7][80]; // 0x00007DB4 length: 2240
            int DAT_UNIT_SPRITE_DIMENSIONS[80][2]; // 0x00008674 length: 640
            int ANIM_FadeAlpha_Values_1_2[46]; // 0x000088F4 length: 184
            int ANIM_FadeAlpha_Values_3[54]; // 0x000089AC length: 216
            int ANIM_FadeAlpha_Values_4[61]; // 0x00008A84 length: 244
            AnimationFrameData ANIM_Frames_Shared_UnitClimbingUp; // 0x00008B78 length: 33748
            int field77_0x10f4c[328][2]; // 0x00010F4C length: 2624
            int DAT_UnitOrientationRelatedOffset[8][2]; // 0x0001198C length: 64
            int field79_0x119cc[22]; // 0x000119CC length: 88
            int field80_0x11a24[18]; // 0x00011A24 length: 72
            int field81_0x11a6c[110]; // 0x00011A6C length: 440
            int field82_0x11c24[20]; // 0x00011C24 length: 80
            XYPair field83_0x11c74[8]; // 0x00011C74 length: 64
            int field84_0x11cb4[8]; // 0x00011CB4 length: 32
            undefined1 padding_0x11cd4[32]; // 0x00011CD4 length: 32
            int field117_0x11cf4[9][24]; // 0x00011CF4 length: 864
            XYPair field118_0x12054[24]; // 0x00012054 length: 192
            int DAT_UnitVisionBonus[10]; // 0x00012114 length: 40
            XYPair field120_0x1213c[9]; // 0x0001213C length: 72
            XYPair field121_0x12184[9]; // 0x00012184 length: 72
            XYPair field122_0x121cc[9]; // 0x000121CC length: 72
            XYPair field123_0x12214[9]; // 0x00012214 length: 72
            int field124_0x1225c; // 0x0001225C length: 4
            int field125_0x12260; // 0x00012260 length: 4
            int field126_0x12264; // 0x00012264 length: 4
            int field127_0x12268; // 0x00012268 length: 4

        } UnitPropertiesDefinedData;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(UnitPropertiesDefinedData) == 74348, UnitPropertiesDefinedData);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
