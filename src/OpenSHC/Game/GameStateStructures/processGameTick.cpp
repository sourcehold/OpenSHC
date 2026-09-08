#include "../GameStateStructures.func.hpp"

#include "OpenSHC/AI/AIVState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/WallAndPitchState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/HoveredState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_HoveredState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_RotateMapOrPullDownTerrain.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Game {
    // FUNCTION: STRONGHOLDCRUSADER 0x0045CD10
    void GameStateStructures::processGameTick()
    {
        // A call is not necessarily a clock step. Save/synchronization owns
        // the early paths; none of the world-update phase runs on those paths.
        DAT_RotateMapOrPullDownTerrain::instance = 0;
        if (DAT_GameSynchronyState::instance.saveRelated != 0) {
            if (DAT_GameSynchronyState::instance.isHost) {
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::checkGameLagStatusAndKickAccordingly,
                    DAT_GameSynchronyState::ptr)();
            }
            return;
        }
        if (DAT_GameSynchronyState::instance.syncStatus != 0) {
            if (DAT_GameSynchronyState::instance.isHost) {
                if (DAT_GameSynchronyState::instance.syncStatus == 10) {
                    MACRO_CALL_MEMBER(
                        Synchrony::GameSynchronyState_Func::checkLagAndSyncStatus, DAT_GameSynchronyState::ptr)();
                } else if (DAT_GameSynchronyState::instance.syncStatus == 1) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::broadcastDesyncResyncCommands,
                        DAT_GameSynchronyState::ptr)();
                } else if (DAT_GameSynchronyState::instance.syncStatus == 2) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::sendPendingResyncCommandsInBudget,
                        DAT_GameSynchronyState::ptr)();
                } else if (static_cast<int>(DAT_GameSynchronyState::instance.syncStatus) > 2) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::advanceSyncStatusAndKickLaggers,
                        DAT_GameSynchronyState::ptr)();
                }
            } else if (DAT_GameSynchronyState::instance.syncStatus == 10) {
                DAT_GameSynchronyState::instance.syncStatus = 11;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SHARE_GAME_STATE_PARTIAL_HASHES);
            } else if (DAT_GameSynchronyState::instance.syncStatus == 1) {
                DAT_GameSynchronyState::instance.syncStatus = 2;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SHARE_DESYNC_HASHES);
            } else if (DAT_GameSynchronyState::instance.syncStatus == 3) {
                DAT_GameSynchronyState::instance.syncStatus = 4;
                MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                    Commands::GCT_SEND_KEEP_ALIVE);
            }
            return;
        }

        if (DAT_GameSynchronyState::instance.quitGameVoteRelated != 0
            && timeGetTime() - DAT_GameSynchronyState::instance.quitGameVoteRequestTime > 11000u) {
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 2;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                Commands::GCT_SEND_QUIT_GAME_VOTE);
        }

        // Clock/RNG advancement has its own menu/pause gate. Map rotation may
        // bypass logical pause; a halting menu still prevents clock advancement.
        if (MACRO_CALL_MEMBER(GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
            if (DAT_GameCore::instance.gamePausedLogical != 0
                && static_cast<int>(DAT_TileMapState::instance.DAT_FutureMapOrientation) >= 8) {
                goto maintenance;
            }
            if (!MACRO_CALL_MEMBER(GameCore_Func::isGameHaltingMenuOpen, DAT_GameCore::ptr)()) {
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                ++DAT_GameCore::instance.mapTimeInTicks;
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::processSingleTimeTick, DAT_GameState::ptr)();
            }
        }
        if (static_cast<int>(DAT_TileMapState::instance.DAT_FutureMapOrientation) < 8) {
            DAT_RotateMapOrPullDownTerrain::instance = 1;
        }

    maintenance:
        // These owners run even when no clock increment occurred. A view
        // refresh can itself set the rotation flag consumed by the later gate.
        MACRO_CALL_MEMBER(Map::TileMapState_Func::processMapOrientationChange, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::updateShowHiLayerOrResetChangedLayer, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::rotateFearFactorBuildingVariations, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(
            Map::Buildings::BuildingsState_Func::updatePathLinkageForGatesKeepsSiegeTowers, DAT_BuildingsState::ptr)();
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updateSeparateAreaTileMap, DAT_PathFindingState::ptr)(
            0);
        MACRO_CALL_MEMBER(Map::TileMapState_Func::updateLogicalTileMapRelatedSections, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::updateMacroLayer, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::updateGfxLayer, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::updateGFXLayers, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(
            Map::Navigation::PathFindingState_Func::setChangedLayerZeroBasedOn40x40Layer, DAT_PathFindingState::ptr)(0);
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::subtractPitchAndMoatFromStartingGoldInSiegeThatMode,
            DAT_BuildingsState::ptr)();
        MACRO_CALL_MEMBER(UI::MinimapViewState_Func::clearOldSpawnMoment, DAT_MinimapViewState::ptr)();
        if (DAT_RotateMapOrPullDownTerrain::instance == 0) {
            if (static_cast<int>(DAT_GameCore::instance.gamePausedLogical) > 0) {
                return;
            }
            if (DAT_GameCore::instance.gamePausedLogical == 0) {
                if (MACRO_CALL_MEMBER(GameCore_Func::isGameHaltingMenuOpen, DAT_GameCore::ptr)()) {
                    return;
                }
            } else {
                DAT_GameCore::instance.gamePausedLogical = 0;
            }
        }
        if (DAT_GameCore::instance.gameMode_2 == GM_EDITOR && DAT_GameCore::instance.isTimeHalted2 != 0) {
            return;
        }
        if (!MACRO_CALL_MEMBER(GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
            return;
        }

        // Preserve dependency order: counters, buildings, AI, units, entities,
        // population and tribes. The calendar call above uses the global game
        // state; the statistics/economy calls below use this receiver.
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetCountsAndStatistics, this)();
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetBuildingsCurrentIndexCounter, this)();
        MACRO_CALL_MEMBER(Map::LandscapeState_Func::updateWind, DAT_LandscapeState::ptr)();
        DAT_PathFindingState::instance.field48_0x90 = 0;
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updateClimbData, DAT_PathFindingState::ptr)();
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateBuildings, DAT_BuildingsState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::updatePitchDitches, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(Map::LandscapeState_Func::updateTrees, DAT_LandscapeState::ptr)();
        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::processSingleplayerEvents, DAT_MapPropertiesState::ptr)();
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::checkSkirmishGameDefeat, DAT_GameSynchronyState::ptr)();
        MACRO_CALL_MEMBER(AI::AIVState_Func::updateBuildingsStateAndUpdateAIBuildingDecisions, DAT_AIVState::ptr)();
        MACRO_CALL_MEMBER(
            Map::Units::TroopValueState_Func::aiControlNonSkirmishUnitMovement, DAT_TroopValueState::ptr)();
        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::updateUnits, DAT_UnitsState::ptr)();
        MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::updateEntities, DAT_EntityState::ptr)();
        MACRO_CALL_MEMBER(
            Map::Units::UnitsState_Func::removeUnitsSameTileLinkageIfNoLongerApplicable, DAT_UnitsState::ptr)();
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::processFoodConsumption, this)();
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::computePopulationStatistics, this)();
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateTribeUnitAssignments, DAT_TribesState::ptr)();
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateTribes, DAT_TribesState::ptr)();
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::spawnQueuedReinforcementWaves, DAT_TribesState::ptr)();
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::respawnDeer, DAT_TribesState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::generateDustClouds, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::updateGameRelatedValue, DAT_TileMapState::ptr)();
        MACRO_CALL(Global_Func::DoNothing)();
        MACRO_CALL_MEMBER(
            Map::WallAndPitchState_Func::updateDestructionConfirmationCountdown, DAT_WallAndPitchState::ptr)();
        MACRO_CALL_MEMBER(UI::HoveredState_Func::clearInvalidatedHoverStates, DAT_HoveredState::ptr)();
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::computeArmySizeLimit, this)();
    }
}
}
