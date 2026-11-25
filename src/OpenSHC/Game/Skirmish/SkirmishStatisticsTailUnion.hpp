/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Skirmish/SkirmishStatisticsTailUnion.hpp'
*/

#pragma once

#include "OpenSHC/Game/Skirmish/SkirmishStatisticsTail1.hpp"
#include "OpenSHC/Game/Skirmish/SkirmishStatisticsTail2.hpp"

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

        using OpenSHC::Game::Skirmish::SkirmishStatisticsTail1;
        using OpenSHC::Game::Skirmish::SkirmishStatisticsTail2;

#pragma pack(push, 1)
        // SIZE: 0x0000006C
        typedef union SkirmishStatisticsTailUnion {

            SkirmishStatisticsTail1 tail1; // 0x00000000 length: 108
            SkirmishStatisticsTail2 tail2; // 0x00000000 length: 108

        } SkirmishStatisticsTailUnion;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SkirmishStatisticsTailUnion) == 108, SkirmishStatisticsTailUnion);
    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
