/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/UnitInstructionType.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        typedef enum UnitInstructionType {

            UIT_NO_INSTRUCTION_OR_MOVEUnk = 3, // 0x00000003
            UIT_UNIT_ATTACK_UNIT = 4, // 0x00000004
            UIT_ATTACK_LAND = 5, // 0x00000005
            UIT_DIG_MOAT = 6, // 0x00000006
            UIT_FILL_MOAT = 7, // 0x00000007
            UIT_ATTACK_BUILDING = 9, // 0x00000009
            UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED = 15, // 0x0000000F
            UIT_MAN_SIEGE_EQUIPMENT = 16, // 0x00000010
            UIT_EXIT_SIEGE_EQUIPMENT = 17, // 0x00000011
            UIT_THROW_OIL = 20, // 0x00000014
            UIT_THROW_COW = 22, // 0x00000016
            UIT_ATTACK_WALL = 23, // 0x00000017
            UIT_SET_LADDER = 24, // 0x00000018
            UIT_DISBAND = 30, // 0x0000001E
            UIT_STOP = 31, // 0x0000001F
            UIT_SHOOT_TARGETUnk = 33, // 0x00000021
            UIT_LIGHT_PITCH = 34 // 0x00000022

        } UnitInstructionType;

        static_assert_cpp98_obj(sizeof(UnitInstructionType) == 4, UnitInstructionType);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
