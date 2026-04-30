/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Matrices/TranslationMatrixTriplet.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Matrices {

#pragma pack(push, 1)
        // SIZE: 0x0000000C
        typedef struct TranslationMatrixTriplet {

            int distanceToCenter; // 0x00000000 length: 4
            int firstTileOfRow; // 0x00000004 length: 4
            int addXgetTile; // 0x00000008 length: 4

        } TranslationMatrixTriplet;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(TranslationMatrixTriplet) == 12, TranslationMatrixTriplet);
    } // namespace Matrices
} // namespace Map
} // namespace OpenSHC
