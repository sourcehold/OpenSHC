/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units/States/UnitStateUnion.hpp'
*/

#pragma once

#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_AppleFarmerShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_ArabianArcherShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_DairyFarmerShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_DogUnitShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_FireThrowerShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_FletcherShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_HopsFarmerShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_HorseArcherShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_HunterShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_MillerShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_OxStateShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_PeasantShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_PitchManShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_QuarryMasonShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_QuarryWorkerShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_SlingerUnitShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_TunnelerShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_WheatFarmerShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState_WoodcutterShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {
        namespace States {

            using OpenSHC::Map::Units::States::UnitState_AppleFarmerShort;
            using OpenSHC::Map::Units::States::UnitState_ArabianArcherShort;
            using OpenSHC::Map::Units::States::UnitState_DairyFarmerShort;
            using OpenSHC::Map::Units::States::UnitState_DogUnitShort;
            using OpenSHC::Map::Units::States::UnitState_FireThrowerShort;
            using OpenSHC::Map::Units::States::UnitState_FletcherShort;
            using OpenSHC::Map::Units::States::UnitState_HopsFarmerShort;
            using OpenSHC::Map::Units::States::UnitState_HorseArcherShort;
            using OpenSHC::Map::Units::States::UnitState_HunterShort;
            using OpenSHC::Map::Units::States::UnitState_MillerShort;
            using OpenSHC::Map::Units::States::UnitState_OxStateShort;
            using OpenSHC::Map::Units::States::UnitState_PeasantShort;
            using OpenSHC::Map::Units::States::UnitState_PitchManShort;
            using OpenSHC::Map::Units::States::UnitState_QuarryMasonShort;
            using OpenSHC::Map::Units::States::UnitState_QuarryWorkerShort;
            using OpenSHC::Map::Units::States::UnitState_SlingerUnitShort;
            using OpenSHC::Map::Units::States::UnitState_TunnelerShort;
            using OpenSHC::Map::Units::States::UnitState_WheatFarmerShort;
            using OpenSHC::Map::Units::States::UnitState_WoodcutterShort;
            using OpenSHC::Map::Units::States::UnitStateShort;

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
                UnitState_WheatFarmerShort wheatFarmer; // 0x00000000 length: 2
                UnitState_FletcherShort fletcher; // 0x00000000 length: 2
                UnitState_WoodcutterShort woodcutter; // 0x00000000 length: 2
                UnitState_TunnelerShort tunneler; // 0x00000000 length: 2
                UnitState_QuarryMasonShort quarryMason; // 0x00000000 length: 2
                UnitState_PitchManShort pitchMan; // 0x00000000 length: 2
                UnitState_HunterShort hunter; // 0x00000000 length: 2
                UnitState_QuarryWorkerShort quarryWorker; // 0x00000000 length: 2
                UnitState_HopsFarmerShort hopsFarmer; // 0x00000000 length: 2
                UnitState_DairyFarmerShort dairyFarmer; // 0x00000000 length: 2

            } UnitStateUnion;
#pragma pack(pop)

            static_assert_cpp98_obj(sizeof(UnitStateUnion) == 2, UnitStateUnion);
        } // namespace States
    } // namespace Units
} // namespace Map
} // namespace OpenSHC
