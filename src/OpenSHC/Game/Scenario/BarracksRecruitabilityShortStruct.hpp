/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/Scenario/BarracksRecruitabilityShortStruct.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Scenario {

#pragma pack(push, 1)
        // SIZE: 0x0000000E
        typedef struct BarracksRecruitabilityShortStruct {

            short archers; // 0x00000000 length: 2
            short crossbowmen; // 0x00000002 length: 2
            short spearmen; // 0x00000004 length: 2
            short pikemen; // 0x00000006 length: 2
            short macemen; // 0x00000008 length: 2
            short swordsmen; // 0x0000000A length: 2
            short knights; // 0x0000000C length: 2

        } BarracksRecruitabilityShortStruct;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(BarracksRecruitabilityShortStruct) == 14, BarracksRecruitabilityShortStruct);
    } // namespace Scenario
} // namespace Game
} // namespace OpenSHC
