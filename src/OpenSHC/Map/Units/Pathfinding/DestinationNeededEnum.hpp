/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace Pathfinding {
            typedef enum DestinationNeededEnum {

                DNE_DESTINATION_HAS_BEEN_SET = 0, // 0x00000000
                DNE_DESTINATION_NEEDED = 1, // 0x00000001
                DNE_FLETCHER_SPECIFIC_COUNTDOWN = 5, // 0x00000005
                DNE_OX_SPECIFIC_COUNTDOWN = 20 // 0x00000014

            } DestinationNeededEnum;

            static_assert_cpp98_obj(sizeof(DestinationNeededEnum) == 4, DestinationNeededEnum);
        } // namespace Pathfinding
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
