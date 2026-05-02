/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/Trading/AIResourceTradeCategory.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    namespace Trading {
        typedef enum AIResourceTradeCategory {

            AIRTC_IRONPITCHFLOUR = 0, // 0x00000000
            AIRTC_WOOD = 1, // 0x00000001
            AIRTC_FOOD = 2, // 0x00000002
            AIRTC_STONE = 3, // 0x00000003
            AIRTC_WEAPONS = 4, // 0x00000004
            AIRTC_ALE = 5, // 0x00000005
            AIRTC_HOPS = 6 // 0x00000006

        } AIResourceTradeCategory;

        static_assert_cpp98_obj(sizeof(AIResourceTradeCategory) == 4, AIResourceTradeCategory);
    } // namespace Trading
} // namespace AI
} // namespace OpenSHC
