/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map.func.hpp'
*/

#pragma once

#include "OpenSHC/Map.hpp"
namespace OpenSHC {
namespace Map_Func {

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int miniTileX, int miniTileY, int tileHeightMin8, int two),
        false, Address::SHC_3BB0A8C1_0x00407130, &OpenSHC::Map::IgniteFireAtMiniTile_Convenience)
    IgniteFireAtMiniTile_Convenience;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1, int buildingID, int value, int buildingUID), false,
        Address::SHC_3BB0A8C1_0x004653B0, &OpenSHC::Map::OpenOrCloseDrawbridge)
    OpenOrCloseDrawbridge;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 playerID, int buildingID, int newGateState, int buildingUID),
        false, Address::SHC_3BB0A8C1_0x004654F0, &OpenSHC::Map::GateOpenOrClose)
    GateOpenOrClose;

} // namespace Map_Func
} // namespace OpenSHC
