#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004015D0
        void EntityState::processFireDamageToUnitsAtTile(int tileUnk, int playerID, int fireLowIntensity)
        {
            for (int unitID = (short)DAT_TileMapState::instance.UnitLayer[tileUnk]; unitID != 0;
                unitID = (short)DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::processFireDamageToUnit, DAT_UnitsState::ptr)(
                    unitID, playerID, fireLowIntensity);
            }
        }

    }
}
}
