/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Siege/SiegeGameModeRelatedSection.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Siege {

#pragma pack(push, 1)
        // SIZE: 0x0000001C
        typedef struct SiegeGameModeRelatedSection {

            int siegeConfigValue0; // 0x00000000 length: 4
            int siegeConfigValue1; // 0x00000004 length: 4
            int siegeConfigValue2; // 0x00000008 length: 4
            int siegeConfigValue3; // 0x0000000C length: 4
            int siegeConfigValue4; // 0x00000010 length: 4
            int siegeConfigValue5; // 0x00000014 length: 4
            int siegeStartTroopValue; // 0x00000018 length: 4

        } SiegeGameModeRelatedSection;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SiegeGameModeRelatedSection) == 28, SiegeGameModeRelatedSection);
    } // namespace Siege
} // namespace Game
} // namespace OpenSHC
