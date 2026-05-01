/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/Market/BuySellPair.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Market {

#pragma pack(push, 1)
        // SIZE: 0x00000008
        typedef struct BuySellPair {

            int buyPrice; // 0x00000000 length: 4
            int salesPrice; // 0x00000004 length: 4

        } BuySellPair;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(BuySellPair) == 8, BuySellPair);
    } // namespace Market
} // namespace Game
} // namespace OpenSHC
