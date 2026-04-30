/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/State/UnitSelectionHotKeyEntry.hpp'
*/

#pragma once

#include "OpenSHC/Game/State/UnitIDUIDPair.hpp"

namespace OpenSHC {
namespace Game {
    namespace State {

        using OpenSHC::Game::State::UnitIDUIDPair;

#pragma pack(push, 1)
        // SIZE: 0x00004E20
        typedef struct UnitSelectionHotKeyEntry {

            UnitIDUIDPair units[2500]; // 0x00000000 length: 20000

        } UnitSelectionHotKeyEntry;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(UnitSelectionHotKeyEntry) == 20000, UnitSelectionHotKeyEntry);
    } // namespace State
} // namespace Game
} // namespace OpenSHC
