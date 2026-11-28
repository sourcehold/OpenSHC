#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D2B0
        void TroopValueState::decideAndExecuteTribeAttackAction(int tribeID)
        {
            int const targetUnitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            int const enemyBuildingID
                = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findNearestEnemyBuildingWithinDistance,
                    DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner,
                    DAT_UnitsState::instance.units[targetUnitID].x, DAT_UnitsState::instance.units[targetUnitID].y, 15);
            int const enemyUnitID
                = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findNearestEnemyUnitWithinDistance,
                    DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner,
                    DAT_UnitsState::instance.units[targetUnitID].x, DAT_UnitsState::instance.units[targetUnitID].y, 10);
            if (enemyBuildingID && (SEC_RNG::instance.currentNumber2 & 1)) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(tribeID,
                    Map::Units::UIT_ATTACK_BUILDING, enemyBuildingID,
                    DAT_BuildingsState::instance.buildings[enemyBuildingID].uid, 0);
                return;
            }
            if (enemyUnitID && (SEC_RNG::instance.currentNumber2 & 1)) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(tribeID,
                    Map::Units::UIT_UNIT_ATTACK_UNIT, enemyUnitID, DAT_UnitsState::instance.units[enemyUnitID].uid, 0);
                return;
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                tribeID, Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk, 0, 0, 0);
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                1);
            int targetTile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findBestAttackTileByPathCost,
                DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[targetUnitID].x,
                DAT_UnitsState::instance.units[targetUnitID].y, DAT_UnitsState::instance.units[targetUnitID].owner, 6);
            if (targetTile <= 0) {
                targetTile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findBestAttackTileByPathCost,
                    DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[targetUnitID].x,
                    DAT_UnitsState::instance.units[targetUnitID].y, DAT_UnitsState::instance.units[targetUnitID].owner,
                    30);
                if (targetTile <= 0) {
                    targetTile = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findBestAttackTileByPathCost,
                        DAT_PathFindingState::ptr)(DAT_UnitsState::instance.units[targetUnitID].x,
                        DAT_UnitsState::instance.units[targetUnitID].y,
                        DAT_UnitsState::instance.units[targetUnitID].owner, 50);
                }
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(
                0);
            if (0 < targetTile) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                    targetTile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[targetTile]]
                            .addXgetTile,
                    DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[targetTile], 0, 0,
                    Map::Units::Instructions::UMSE_0);
            }
        }

    }
}
}
