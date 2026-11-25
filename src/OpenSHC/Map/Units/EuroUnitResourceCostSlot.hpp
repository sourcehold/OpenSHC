/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/EuroUnitResourceCostSlot.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Units {
        typedef enum EuroUnitResourceCostSlot {

            EURCS_WEAPON = 0, // 0x00000000
            EURCS_ARMOUR = 1, // 0x00000001
            EURCS_UNKNOWN = 2, // 0x00000002
            EURCS_HORSE = 3 // 0x00000003

        } EuroUnitResourceCostSlot;

        static_assert_cpp98_obj(sizeof(EuroUnitResourceCostSlot) == 4, EuroUnitResourceCostSlot);
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
