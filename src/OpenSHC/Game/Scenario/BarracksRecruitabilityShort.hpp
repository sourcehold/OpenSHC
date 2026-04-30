/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/Scenario/BarracksRecruitabilityShort.hpp'
*/

#pragma once

#include "OpenSHC/Game/Scenario/BarracksRecruitabilityShortArray.hpp"
#include "OpenSHC/Game/Scenario/BarracksRecruitabilityShortStruct.hpp"

namespace OpenSHC {
namespace Game {
    namespace Scenario {

        using OpenSHC::Game::Scenario::BarracksRecruitabilityShortArray;
        using OpenSHC::Game::Scenario::BarracksRecruitabilityShortStruct;

#pragma pack(push, 1)
        // SIZE: 0x0000000E
        typedef union BarracksRecruitabilityShort {

            BarracksRecruitabilityShortStruct recruitability; // 0x00000000 length: 14
            BarracksRecruitabilityShortArray array; // 0x00000000 length: 14

        } BarracksRecruitabilityShort;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(BarracksRecruitabilityShort) == 14, BarracksRecruitabilityShort);
    } // namespace Scenario
} // namespace Game
} // namespace OpenSHC
