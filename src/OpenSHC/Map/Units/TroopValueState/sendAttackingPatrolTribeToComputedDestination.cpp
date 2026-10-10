#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

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

        using Map::Units::Instructions::UnitMatchSpeedEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D0D0
        void TroopValueState::sendAttackingPatrolTribeToComputedDestination(int tribeID)
        {
            short sVar1;
            dword _tile;
            sVar1 = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            MACRO_CALL_MEMBER(
                Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(1);
            _tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20,
                DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[sVar1].x,
                (uint)((int)((int)DAT_UnitsState::instance.units[sVar1].y)),
                (int)((int)(DAT_UnitsState::instance.units[sVar1].owner)), (uint)((int)(12)), 1);
            if ((int)_tile < 1) {
                _tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20,
                    DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[sVar1].x,
                    (uint)((int)((int)DAT_UnitsState::instance.units[sVar1].y)),
                    (int)((int)(DAT_UnitsState::instance.units[sVar1].owner)), (uint)((int)(30)), 1);
                if ((int)_tile < 1) {
                    _tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20,
                        DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[sVar1].x,
                        (uint)((int)((int)DAT_UnitsState::instance.units[sVar1].y)),
                        (int)((int)(DAT_UnitsState::instance.units[sVar1].owner)), (uint)((int)(50)), 1);
                }
            }
            MACRO_CALL_MEMBER(
                Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(0);
            if (0 < (int)_tile) {
                MACRO_CALL_MEMBER(
                    Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                    (uint)((int)(_tile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[_tile]]
                            .addXgetTile)),
                    (uint)((int)((int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile])), 0, 0,
                    Map::Units::Instructions::UMSE_0);
            }
        }

    }
}
}
