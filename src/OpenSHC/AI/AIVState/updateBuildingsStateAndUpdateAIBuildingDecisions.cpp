#include "../AIVState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1860
    void AIVState::updateBuildingsStateAndUpdateAIBuildingDecisions()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            return;
        }

        if (DAT_GameState::instance.mapAndTime.startOfDay) {
            ++this->mapExtraInfo.algBuildingPlacementNudge;
            this->counter = 0;
            if (this->mapExtraInfo.algBuildingPlacementNudge > 31) {
                this->mapExtraInfo.algBuildingPlacementNudge = 0;
            }
            for (int player = 1; player < 9; ++player) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] == -1
                    && DAT_GameSynchronyState::instance.currentAIArray[player] == 0) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkKeepEnclosed, DAT_GameState::ptr)(player)) {
                    DAT_GameState::instance.playerDataArray[player].keepEnclosementRelatedCountdown = 5;
                    continue;
                }
                // warn the local player when he broke into an enemy castle
                if (DAT_GameState::instance.playerDataArray[player].keepEnclosementRelatedCountdown > 0 && --DAT_GameState::instance.playerDataArray[player].keepEnclosementRelatedCountdown == 0
                    && DAT_GameState::instance.playerDataArray[player].defensesDamagedByPlayer == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && DAT_GameState::instance.mapAndTime.playerTeams[player]
                        != DAT_GameState::instance.mapAndTime
                               .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    && DAT_GameCore::instance.genieVoiceActive) {
                    // "Once more unto the breach"
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(s_Genie_35_wav_005ab8b8);
                }
            }
        }

        if (DAT_GameState::instance.mapAndTime.monthChanged) {
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::recomputePlayerDataStocksBasedOnStorageBuildings,
                DAT_BuildingsState::ptr)();
        }
        MACRO_CALL_MEMBER(AICState_Func::updateAIBehaviour, DAT_AICState::ptr)();
        if (DAT_GameState::instance.mapAndTime.weekChanged) {
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(2);
            for (int player = 1; player < 9; ++player) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] == -1
                    && DAT_GameSynchronyState::instance.currentAIArray[player] != 0 && DAT_GameState::instance.playerDataArray[player].playerDeathRelated == 0
                    && DAT_GameState::instance.playerDataArray[player].lordKilledByPlayerID == 0 && DAT_GameState::instance.playerDataArray[player].someCount31 == 0) {
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateHeatmapBasedOnBuildingAccessibility,
                        DAT_BuildingsState::ptr)(player);
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::makeUnitsDisappearThatCannotReachTheKeep,
                        DAT_UnitsState::ptr)(player);
                }
            }
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(0);
        }

        // each AI player decides on its own tick of the day
        for (int player = 1; player < 9; ++player) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] == -1
                && DAT_GameSynchronyState::instance.currentAIArray[player] != 0 && DAT_GameState::instance.playerDataArray[player].playerDeathRelated == 0
                && DAT_GameState::instance.playerDataArray[player].lordKilledByPlayerID == 0 && DAT_GameState::instance.mapAndTime.dayTicks == player) {
                MACRO_CALL_MEMBER(AIVState_Func::aiDecideOnNewBuildings, this)(player);
                MACRO_CALL_MEMBER(AICState_Func::planToBuyWhenLowOnResourceAndSnoozeBuildings, DAT_AICState::ptr)(player);
            }
        }
        if (DAT_GameState::instance.mapAndTime.dayTicks == 8) {
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::applySnoozedStateBasedOnPlayerData,
                DAT_BuildingsState::ptr)();
        }
        if (DAT_GameState::instance.mapAndTime.monthTicks == 10) {
            MACRO_CALL_MEMBER(AIVState_Func::recomputeHeatmaps, this)(0);
        }
    }

}
}
