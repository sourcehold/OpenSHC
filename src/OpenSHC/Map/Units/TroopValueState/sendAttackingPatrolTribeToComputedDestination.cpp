#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D0D0
        void TroopValueState::sendAttackingPatrolTribeToComputedDestination(int tribeID)
        {
            int const targetUnitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                1);
            // widen the search until a reachable tile is found
            dword destinationTile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20,
                DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[targetUnitID].x,
                DAT_UnitsState::instance.units[targetUnitID].y, DAT_UnitsState::instance.units[targetUnitID].owner, 12,
                1);
            if ((int)destinationTile <= 0) {
                destinationTile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20,
                    DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[targetUnitID].x,
                    DAT_UnitsState::instance.units[targetUnitID].y, DAT_UnitsState::instance.units[targetUnitID].owner,
                    30, 1);
                if ((int)destinationTile <= 0) {
                    destinationTile = MACRO_CALL_MEMBER(
                        Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20, DAT_PathFindingState::ptr)(
                        DAT_UnitsState::instance.units[targetUnitID].x, DAT_UnitsState::instance.units[targetUnitID].y,
                        DAT_UnitsState::instance.units[targetUnitID].owner, 50, 1);
                }
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                0);
            if (0 < (int)destinationTile) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                    destinationTile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[destinationTile]]
                            .addXgetTile,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[destinationTile], 0, 0,
                    Map::Units::Instructions::UMSE_0);
            }
        }

    }
}
}
