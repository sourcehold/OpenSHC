/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/LogicHelpers/MiscDisplay.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace LogicHelpers {
        typedef enum MiscDisplay {

            MD_PILLAR_SOUTH_SIDEUnk = 1, // 0x00000001
            MD_PILLAR_EAST_SIDEUnk = 2, // 0x00000002
            MD_PILLAR_SIDESUnk = 3, // 0x00000003
            MD_BUILDING_MAIN_TILE = 4, // 0x00000004
            MD_BUILDING_SECOND_TILEUnk = 8, // 0x00000008
            MD_BUILDING_TILES = 12, // 0x0000000C
            MD_BATCHED_SPRITES = 16, // 0x00000010
            MD_GATEHOUSE_RAISED = 32, // 0x00000020
            MD_SEA_CLIFF = 64, // 0x00000040
            MD_SEA_UNNAMED_0x80 = 128, // 0x00000080
            MD_SEA_SHORE = 256, // 0x00000100
            MD_SEA_SHORE_EDGE = 512, // 0x00000200
            MD_SEA_EDGES = 960, // 0x000003C0
            MD_DESTROY_PENDING = 1024, // 0x00000400
            MD_DECORATION_ENTITY = 4096, // 0x00001000
            MD_RUBBLE_EDGEUnk = 8192, // 0x00002000
            MD_RUBBLE_INNERUnk = 16384, // 0x00004000
            MD_PREVIEW_IGNORES_PLACEMENT_FAIL = 32768 // 0x00008000

        } MiscDisplay;

        static_assert_cpp98_obj(sizeof(MiscDisplay) == 4, MiscDisplay);
    } // namespace LogicHelpers
} // namespace Map
} // namespace OpenSHC
