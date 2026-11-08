/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Skirmish/SkirmishStatisticsTail1.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

#pragma pack(push, 1)
        // SIZE: 0x0000006C
        typedef struct SkirmishStatisticsTail1 {

            int yearStart; // 0x00000000 length: 4
            int monthStart; // 0x00000004 length: 4
            int yearEnd; // 0x00000008 length: 4
            int monthEnd; // 0x0000000C length: 4
            byte padding3[92]; // 0x00000010 length: 92

        } SkirmishStatisticsTail1;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SkirmishStatisticsTail1) == 108, SkirmishStatisticsTail1);
    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
