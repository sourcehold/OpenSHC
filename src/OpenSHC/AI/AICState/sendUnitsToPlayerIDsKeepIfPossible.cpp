#include "../AICState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE5F0
    void AICState::sendUnitsToPlayerIDsKeepIfPossible(int playerID1, int playerID2)
    {
        uint campfireX = DAT_GameState::instance.playerDataArray[playerID1].campground.xEntry;
        uint campfireY = DAT_GameState::instance.playerDataArray[playerID1].campground.yEntry;

        uint gatehouseX;
        uint gatehouseY;
        if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep, DAT_GameState::ptr)(
                playerID1, playerID2)
            == FALSE) {
            uint gatehouseTile = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findOwnedGatehouse,
                DAT_PathFindingState::ptr)(playerID2, campfireX, campfireY);
            if (gatehouseTile != 0) {
                gatehouseY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[gatehouseTile];
                gatehouseX = gatehouseTile - DAT_ViewportRenderState::instance.translationMatrix[gatehouseY].addXgetTile;
            } else {
                DAT_GameState::instance.playerDataArray[playerID1].requestStateUnk = 0;
                return;
            }
        }

        for (int i = 0; i < 11; i++) {
            int tribeTypeStart = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeType;
            int tribeCount = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[i].tribeCount;
            for (int j = 0; j < tribeCount; j++) {
                int tribeID = DAT_GameState::instance.playerDataArray[playerID1].aiTribeIDs[tribeTypeStart + j];
                if (tribeID == 0) {
                    continue;
                }
                if (DAT_TribesState::instance.tribes[tribeID].uid
                    != DAT_GameState::instance.playerDataArray[playerID1].aiTribeUIDs[j + tribeTypeStart]) {
                    continue;
                }

                DAT_TribesState::instance.tribes[tribeID].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

                if (MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::canNavigateFromKeepToKeep,
                        DAT_GameState::ptr)(playerID1, playerID2)
                    != FALSE) {
                    if (tribeTypeStart == 0xbe) {
                        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(tribeID, playerID2);
                    } else if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::selectionContainsHorses,
                                   DAT_TribesState::ptr)(tribeID)
                        != FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(tribeID, playerID2);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(tribeID, playerID2);
                    }
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                        tribeID, gatehouseX, gatehouseY, 0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);
                }
            }
        }
    }
}
}
