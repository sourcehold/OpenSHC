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

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D1C0
        void TroopValueState::moveTribeToReachableNearbyTile(int param_1)
        {
            int const unitID = DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                1);
            int tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20,
                DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                DAT_UnitsState::instance.units[unitID].y, DAT_UnitsState::instance.units[unitID].owner, 12, 0);
            if (tile <= 0) {
                tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20,
                    DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                    DAT_UnitsState::instance.units[unitID].y, DAT_UnitsState::instance.units[unitID].owner, 30, 0);
                if (tile <= 0) {
                    tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20,
                        DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                        DAT_UnitsState::instance.units[unitID].y, DAT_UnitsState::instance.units[unitID].owner, 50, 0);
                }
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                0);
            if (0 < tile) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(param_1,
                    tile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                            .addXgetTile,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile], 0, 0,
                    Map::Units::Instructions::UMSE_0);
            }
        }

    }
}
}
