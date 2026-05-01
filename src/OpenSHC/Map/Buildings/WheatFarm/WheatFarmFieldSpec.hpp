/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Buildings/WheatFarm/WheatFarmFieldSpec.hpp'
*/

#pragma once

#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {
        namespace WheatFarm {

            using OpenSHC::Map::Navigation::Algorithms::XYPair;

#pragma pack(push, 1)
            // SIZE: 0x0000000C
            typedef struct WheatFarmFieldSpec {

                XYPair offset; // 0x00000000 length: 8
                int property; // 0x00000008 length: 4

            } WheatFarmFieldSpec;
#pragma pack(pop)

            static_assert_cpp98_obj(sizeof(WheatFarmFieldSpec) == 12, WheatFarmFieldSpec);
        } // namespace WheatFarm
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
