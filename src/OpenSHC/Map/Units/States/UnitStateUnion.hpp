/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Units/States/UnitStateUnion.hpp'
*/

#pragma once

#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_AppleFarmerShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_ArabianArcherShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_DogUnitShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_FireThrowerShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_FletcherShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_HorseArcherShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_MillerShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_OxStateShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_PeasantShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_PitchManShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_QuarryMasonShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_SlingerUnitShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_TunnelerShort.hpp"
#include "OpenSHC/Map/Units/States/WheatFarmerStateEnumShort.hpp"
#include "OpenSHC/Map/Units/States/WoodcutterStateEnumShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {

            using OpenSHC::Map::Units::States::UnitState_AppleFarmerShort;
            using OpenSHC::Map::Units::States::UnitState_ArabianArcherShort;
            using OpenSHC::Map::Units::States::UnitState_DogUnitShort;
            using OpenSHC::Map::Units::States::UnitState_FireThrowerShort;
            using OpenSHC::Map::Units::States::UnitState_FletcherShort;
            using OpenSHC::Map::Units::States::UnitState_HorseArcherShort;
            using OpenSHC::Map::Units::States::UnitState_MillerShort;
            using OpenSHC::Map::Units::States::UnitState_OxStateShort;
            using OpenSHC::Map::Units::States::UnitState_PeasantShort;
            using OpenSHC::Map::Units::States::UnitState_PitchManShort;
            using OpenSHC::Map::Units::States::UnitState_QuarryMasonShort;
            using OpenSHC::Map::Units::States::UnitState_SlingerUnitShort;
            using OpenSHC::Map::Units::States::UnitState_TunnelerShort;
            using OpenSHC::Map::Units::States::UnitStateShort;
            using OpenSHC::Map::Units::States::WheatFarmerStateEnumShort;
            using OpenSHC::Map::Units::States::WoodcutterStateEnumShort;

#pragma pack(push, 1)
            // SIZE: 0x00000002
            typedef union UnitStateUnion {

                UnitStateShort generic; // 0x00000000 length: 2
                UnitState_DogUnitShort dog; // 0x00000000 length: 2
                UnitState_AppleFarmerShort appleFarmer; // 0x00000000 length: 2
                UnitState_SlingerUnitShort slinger; // 0x00000000 length: 2
                UnitState_OxStateShort ox; // 0x00000000 length: 2
                UnitState_ArabianArcherShort arabianArcher; // 0x00000000 length: 2
                UnitState_HorseArcherShort horseArcher; // 0x00000000 length: 2
                UnitState_FireThrowerShort fireThrower; // 0x00000000 length: 2
                UnitState_MillerShort miller; // 0x00000000 length: 2
                UnitState_PeasantShort peasant; // 0x00000000 length: 2
                WheatFarmerStateEnumShort wheatFarmer; // 0x00000000 length: 2
                UnitState_FletcherShort fletcher; // 0x00000000 length: 2
                WoodcutterStateEnumShort woodcutter; // 0x00000000 length: 2
                UnitState_TunnelerShort tunneler; // 0x00000000 length: 2
                UnitState_QuarryMasonShort quarryMason; // 0x00000000 length: 2
                UnitState_PitchManShort pitchMan; // 0x00000000 length: 2

            } UnitStateUnion;
#pragma pack(pop)

            static_assert_cpp98_obj(sizeof(UnitStateUnion) == 2, UnitStateUnion);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
