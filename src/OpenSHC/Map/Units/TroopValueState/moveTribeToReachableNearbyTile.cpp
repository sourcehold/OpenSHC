#include "OpenSHC/Map.func.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D1C0
        void TroopValueState::moveTribeToReachableNearbyTile(int param_1)
        {
            dword _tile;
            int const _unitID = DAT_TribesState::instance.tribes[param_1].selectionTargetUnitID;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                1);
            _tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20,
                DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[_unitID].x,
                (uint)(DAT_UnitsState::instance.units[_unitID].y), (int)(DAT_UnitsState::instance.units[_unitID].owner),
                0xc, 0);
            if ((int)_tile <= 0) {
                _tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20,
                    DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[_unitID].x,
                    (uint)(DAT_UnitsState::instance.units[_unitID].y),
                    (int)(DAT_UnitsState::instance.units[_unitID].owner), 0x1e, 0);
                if ((int)_tile <= 0) {
                    _tile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::pathfindingRelated49ff20,
                        DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[_unitID].x,
                        (uint)(DAT_UnitsState::instance.units[_unitID].y),
                        (int)(DAT_UnitsState::instance.units[_unitID].owner), 0x32, 0);
                }
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                0);
            if (0 < (int)_tile) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(param_1,
                    (uint)(_tile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[_tile]]
                            .addXgetTile),
                    (uint)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile]), 0, 0,
                    Map::Units::Instructions::UMSE_0);
            }
        }

    }
}
}
