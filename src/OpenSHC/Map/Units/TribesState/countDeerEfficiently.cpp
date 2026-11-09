#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005236A0
        void TribesState::countDeerEfficiently()
        {
            DAT_GameState::instance.mapAndTime.aliveDeerCount = 0;
            for (int i = 1; i < (int)_countof(DAT_UnitsState::instance.units); ++i) {
                if (DAT_UnitsState::instance.units[i].logicalState == Map::Units::ULS_NORMAL
                    && !DAT_UnitsState::instance.units[i].dying
                    && DAT_UnitsState::instance.units[i].unitType == Map::Units::UT_ANTELOPESHDEER) {
                    ++DAT_GameState::instance.mapAndTime.aliveDeerCount;
                }
            }
        }

    }
}
}
