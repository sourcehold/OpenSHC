#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
        using Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051CBD0
        void TroopValueState::redeployArchersToDefensivePositions()
        {
            if (DAT_TroopValueState::instance.attackInfo.unitsSentToKeepFlag
                || DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c <= 0) {
                return;
            }
            for (int index = 0; index < DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2c520; ++index) {
                int const postedUnitID = DAT_TroopValueState::instance.attackInfo.unitIDArray_0x2c070[index];
                if (postedUnitID
                    && DAT_UnitsState::instance.units[postedUnitID].uid
                        == DAT_TroopValueState::instance.attackInfo.uidArray_0x2c200[index]) {
                    continue;
                }
                int const tile = DAT_TroopValueState::instance.attackInfo.tileArray_0x2bd50[index];
                if (!(DAT_TileMapState::instance.LogicLayer[tile] & (L_KEEP_NON_MANOR_HOUSE | L_WALL_OR_GATEHOUSE))) {
                    continue;
                }
                int const y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                --DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c;
                int const unitID
                    = DAT_TroopValueState::instance.attackInfo
                          .unitIDArray_0x2b57c[DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c];
                int const rowStartTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                DAT_TroopValueState::instance.attackInfo.uidArray_0x2c200[index]
                    = DAT_UnitsState::instance.units[unitID].uid;
                DAT_TroopValueState::instance.attackInfo.unitIDArray_0x2c070[index] = unitID;
                DAT_UnitsState::instance.units[unitID].state.generic = Map::Units::States::US_MOVE_TO_DESTINATION;
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, tile - rowStartTile, y, 0);
            }
        }

    }
}
}
