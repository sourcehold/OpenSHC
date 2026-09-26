#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BFD0
        void BuildingsState::processPlacementResourceLossForBuildingType(
            int playerID, BuildingType buildingType, int param_3)
        {
            if (DAT_GameCore::instance.solitaryAllBuildingsAreFree != FALSE
                || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
                return;
            }
            // Keeps are free in solitary mode
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                && (buildingType == BT_MANORHOUSE || buildingType == BT_STONEKEEP || buildingType == BT_STRONGHOLD
                    || buildingType == BT_KEEPFOUR || buildingType == BT_KEEPFIVE)) {
                return;
            }
            // A woodcutter's hut is free if the player cannot afford one
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::
                                      hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters,
                    this)(playerID, buildingType)
                != 0) {
                return;
            }

            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                if (buildingType == BT_PITCHDITCH) {
                    return;
                }
            } else if (buildingType == BT_PITCHDITCH) {
                // Only every fourth pitch ditch tile costs pitch
                if (DAT_GameState::instance.playerDataArray[playerID].pitchDitchCounterTo4 == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(
                        playerID, OpenSHC::Game::Resources::RT_PITCH, 1, param_3);
                    if (param_3 != 0) {
                        return;
                    }
                    DAT_GameState::instance.playerDataArray[playerID].pitchDitchCounterTo4 = 1;
                    return;
                }
                if (param_3 != 0) {
                    return;
                }
                ++DAT_GameState::instance.playerDataArray[playerID].pitchDitchCounterTo4;
                if (DAT_GameState::instance.playerDataArray[playerID].pitchDitchCounterTo4 == 4) {
                    DAT_GameState::instance.playerDataArray[playerID].pitchDitchCounterTo4 = 0;
                }
                return;
            }

            int stone = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredStone_0x4;
            int wood = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredWood;
            int iron = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredIron_0x8;
            int pitch = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredPitch_0xc;
            int gold = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredGold;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                iron = 0;
                pitch = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::resourceGainForKillingPitAndPitchDitch,
                    this)(buildingType, &stone, &gold);
            } else if (wood != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(
                    playerID, OpenSHC::Game::Resources::RT_WOOD, wood, param_3);
            }
            if (stone != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(
                    playerID, OpenSHC::Game::Resources::RT_STONE, stone, param_3);
            }
            if (iron != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(
                    playerID, OpenSHC::Game::Resources::RT_IRON, iron, param_3);
            }
            if (pitch != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(
                    playerID, OpenSHC::Game::Resources::RT_PITCH, pitch, param_3);
            }
            if (gold != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, this)(
                    playerID, OpenSHC::Game::Resources::RT_GOLD, gold, param_3);
            }
        }

    }
}
}
