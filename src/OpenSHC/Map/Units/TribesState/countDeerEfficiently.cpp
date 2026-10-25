#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x005236A0
        void TribesState::countDeerEfficiently()
        {
            DAT_GameState::instance.mapAndTime.aliveDeerCount = 0;
            /*
              The original walks the unit array three at a time with the test written out once
              per unit, so the three blocks below are kept separate rather than folded.
             */
            for (int i = 1; i < 2500; i += 3) {
                Unit* unit = &DAT_UnitsState::instance.units[i];
                if (unit[0].logicalState == Map::Units::ULS_NORMAL && unit[0].dying == 0
                    && unit[0].unitType == Map::Units::UT_ANTELOPESHDEER) {
                    DAT_GameState::instance.mapAndTime.aliveDeerCount
                        = DAT_GameState::instance.mapAndTime.aliveDeerCount + 1;
                }
                if (unit[1].logicalState == Map::Units::ULS_NORMAL && unit[1].dying == 0
                    && unit[1].unitType == Map::Units::UT_ANTELOPESHDEER) {
                    DAT_GameState::instance.mapAndTime.aliveDeerCount
                        = DAT_GameState::instance.mapAndTime.aliveDeerCount + 1;
                }
                if (unit[2].logicalState == Map::Units::ULS_NORMAL && unit[2].dying == 0
                    && unit[2].unitType == Map::Units::UT_ANTELOPESHDEER) {
                    DAT_GameState::instance.mapAndTime.aliveDeerCount
                        = DAT_GameState::instance.mapAndTime.aliveDeerCount + 1;
                }
            }
        }
    }
}
}
