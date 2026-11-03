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
            for (int i = 1; i < 2500; ++i) {
                if (DAT_UnitsState::instance.units[i].logicalState == Map::Units::ULS_NORMAL
                    && DAT_UnitsState::instance.units[i].dying == 0
                    && DAT_UnitsState::instance.units[i].unitType == Map::Units::UT_ANTELOPESHDEER) {
                    ++DAT_GameState::instance.mapAndTime.aliveDeerCount;
                }
            }
        }

    }
}
}
