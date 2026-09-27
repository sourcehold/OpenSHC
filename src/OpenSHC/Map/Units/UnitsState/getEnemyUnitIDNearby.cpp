#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053CAE0
        int UnitsState::getEnemyUnitIDNearby(int unitID, int tileUnk, int unitHeight)
        {
            int _otherUnitID = (short)DAT_TileMapState::instance.UnitLayer[tileUnk];
            if (_otherUnitID == 0) {
                return 0;
            }
            for (int _visited = 0; _visited <= 1999; ++_visited) {
                if (this->units[_otherUnitID].dying == 0 && this->units[_otherUnitID].unknownTestAgainst0_2 == 0
                    && this->units[_otherUnitID].moveRelatedFlag != 1) {
                    int _otherHeight
                        = this->units[_otherUnitID].buildingHeight + this->units[_otherUnitID].terrainOrClimbHeight;
                    if (_otherHeight <= unitHeight + 0x20 && unitHeight + -0x20 <= _otherHeight
                        && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::shouldUnitsEngageInMelee, this)(
                               unitID, _otherUnitID)
                            == FALSE
                        && (DAT_GameState::instance.mapAndTime.playerTeams[this->units[_otherUnitID].owner]
                                != DAT_GameState::instance.mapAndTime.playerTeams[this->units[unitID].owner]
                            || this->units[unitID].owner == 0)) {
                        return _otherUnitID;
                    }
                }
                _otherUnitID = (short)this->units[_otherUnitID].nextUnitOnTheSameTile;
                if (_otherUnitID <= 0) {
                    return 0;
                }
            }
            return 0;
        }

    }
}
}
