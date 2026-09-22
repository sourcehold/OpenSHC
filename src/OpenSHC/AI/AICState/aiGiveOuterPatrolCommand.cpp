#include "../AICState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D28B0
    void AICState::aiGiveOuterPatrolCommand(int playerID)
    {
        int aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (aiType == 0)
            return;
        int aicIndex = aiType - 1;
        int groupsCount = this->aics[aicIndex].OuterPatrolGroupsCount;
        if (groupsCount <= 0)
            return;

        DAT_GameState::instance.playerDataArray[playerID].outerPatrolRallyDelayTracker++;
        if (DAT_GameState::instance.playerDataArray[playerID].outerPatrolRallyDelayTracker
            < this->aics[aicIndex].OuterPatrolRallyDelay)
            return;
        DAT_GameState::instance.playerDataArray[playerID].outerPatrolRallyDelayTracker = 0;

        for (int i = 0; i < groupsCount; i++) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[170 + i];
            DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
            if (tribeID == 0)
                continue;
            if (DAT_TribesState::instance.tribes[tribeID].uid
                != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[i + 170])
                continue;
            if (DAT_TribesState::instance.tribes[tribeID].percentageMovingUnk > 10)
                continue;
            if (DAT_TribesState::instance.tribes[tribeID].percentageShootingUnk > 10)
                continue;
            if (DAT_TribesState::instance.tribes[tribeID].percentageAttackingUnk > 10)
                continue;

            int buildingID = 0;
            if (this->aics[aicIndex].OuterPatrolGroupsMove != 0)
                buildingID = MACRO_CALL_MEMBER(AICState_Func::getTargetableBuildingForPlayerID, this)(playerID, i);
            int tile;
            if (buildingID != 0) {
                tile = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX
                    + DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY]
                          .addXgetTile;
            } else {
                buildingID = MACRO_CALL_MEMBER(AICState_Func::selectBuildingFromAListOfBuildingTypes, this)(playerID);
                if (buildingID == 0)
                    continue;
                tile = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX
                    + DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY]
                          .addXgetTile;
            }
            if (tile == 0)
                continue;

            int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
            int x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
            if (MACRO_CALL_MEMBER(AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(tribeID, tile) != FALSE)
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(
                    tribeID, x, y, 0);
            else
                MACRO_CALL_MEMBER(AICState_Func::sendUnitsToCampfire, this)(tribeID, playerID);        }
    }
}
}
