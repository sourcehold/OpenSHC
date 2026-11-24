#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004015D0
        void EntityState::processFireDamageToUnitsAtTile(int tile, int playerID, int fireLowIntensity)
        {
            ushort _unitID;
            int _unitID2;
            _unitID = DAT_TileMapState::instance.UnitLayer[tile];
            while (_unitID2 = (int)(short)_unitID, _unitID2) {
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::processFireDamageToUnit, DAT_UnitsState::ptr)(
                    _unitID2, playerID, fireLowIntensity);
                _unitID = DAT_UnitsState::instance.units[_unitID2].nextUnitOnTheSameTile;
            }
        }

    }
}
}
