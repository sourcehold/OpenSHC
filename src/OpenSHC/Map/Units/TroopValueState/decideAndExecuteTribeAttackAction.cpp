#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;
        using Map::Units::Instructions::UnitMatchSpeedEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D2B0
        void TroopValueState::decideAndExecuteTribeAttackAction(int tribeID)
        {
            int _buildingID;
            int _unitID;
            dword _targetTile;
            int const _targetUnitID = (int)DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            _buildingID
                = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findNearestEnemyBuildingWithinDistance,
                    DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner,
                    (int)(DAT_UnitsState::instance.units[_targetUnitID].x),
                    (int)(DAT_UnitsState::instance.units[_targetUnitID].y), 0xf);
            _unitID = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findNearestEnemyUnitWithinDistance,
                DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner,
                (int)(DAT_UnitsState::instance.units[_targetUnitID].x),
                (int)(DAT_UnitsState::instance.units[_targetUnitID].y), 10);
            if (_buildingID && ((byte)SEC_RNG::instance.currentNumber2 & 1)) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(tribeID,
                    Map::Units::UIT_ATTACK_BUILDING, _buildingID,
                    DAT_BuildingsState::instance.buildings[_buildingID].uid, 0);
                return;
            }
            if (_unitID && ((byte)SEC_RNG::instance.currentNumber2 & 1)) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                    tribeID, Map::Units::UIT_UNIT_ATTACK_UNIT, _unitID, DAT_UnitsState::instance.units[_unitID].uid, 0);
                return;
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                tribeID, Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk, 0, 0, 0);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                1);
            _targetTile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findBestAttackTileByPathCost,
                DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[_targetUnitID].x,
                (uint)(DAT_UnitsState::instance.units[_targetUnitID].y),
                (int)(DAT_UnitsState::instance.units[_targetUnitID].owner), 6);
            if ((int)_targetTile <= 0) {
                _targetTile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findBestAttackTileByPathCost,
                    DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[_targetUnitID].x,
                    (uint)(DAT_UnitsState::instance.units[_targetUnitID].y),
                    (int)(DAT_UnitsState::instance.units[_targetUnitID].owner), (uint)(30));
                if ((int)_targetTile <= 0) {
                    _targetTile
                        = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findBestAttackTileByPathCost,
                            DAT_PathFindingState::ptr)((int)DAT_UnitsState::instance.units[_targetUnitID].x,
                            (uint)(DAT_UnitsState::instance.units[_targetUnitID].y),
                            (int)(DAT_UnitsState::instance.units[_targetUnitID].owner), (uint)(50));
                }
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                0);
            if (0 < (int)_targetTile) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                    (uint)(_targetTile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[_targetTile]]
                            .addXgetTile),
                    (uint)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_targetTile]), 0, 0,
                    Map::Units::Instructions::UMSE_0);
            }
        }

    }
}
}
