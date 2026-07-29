/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Skirmish/MaxLordHealthMapEntry.hpp'
*/

#pragma once

#include "OpenSHC/AI/AITypeAInt.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        using OpenSHC::AI::AITypeAInt;

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct MaxLordHealthMapEntry {

            AITypeAInt aiTypeA; // 0x00000000 length: 4
            int maxHealthMultiplier; // 0x00000004 length: 4

        } MaxLordHealthMapEntry;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(MaxLordHealthMapEntry) == 8, MaxLordHealthMapEntry);
    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
