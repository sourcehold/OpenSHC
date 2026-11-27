/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Player/UnknownPlayerDataStructure.hpp'
*/

#pragma once

#include "OpenSHC/Coordinates/XYPairShort.hpp"

namespace OpenSHC {
namespace Game {
    namespace Player {

        using OpenSHC::Coordinates::XYPairShort;

#pragma pack(push, 1)
        // SIZE: 0x000006C0
        typedef struct UnknownPlayerDataStructure {

            XYPairShort mercenaryOutpostCampgroundLocations[6][3][24]; // 0x00000000 length: 1728

        } UnknownPlayerDataStructure;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(UnknownPlayerDataStructure) == 1728, UnknownPlayerDataStructure);
    } // namespace Player
} // namespace Game
} // namespace OpenSHC
