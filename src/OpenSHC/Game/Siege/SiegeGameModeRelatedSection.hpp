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

            int siegeEngineCounts[6]; // 0x00000000 length: 24
            int tunnelersCount; // 0x00000018 length: 4

        } SiegeGameModeRelatedSection;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SiegeGameModeRelatedSection) == 28, SiegeGameModeRelatedSection);
    } // namespace Siege
} // namespace Game
} // namespace OpenSHC
