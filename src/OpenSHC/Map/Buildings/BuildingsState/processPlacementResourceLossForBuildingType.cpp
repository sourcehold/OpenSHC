#include "../BuildingsState.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041BFD0
        void BuildingsState::processPlacementResourceLossForBuildingType(
            int playerID, BuildingType buildingType, int param_3)
        {
            if (DAT_GameCore::instance.solitaryAllBuildingsAreFree != 0) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {
                return;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == 0
                && (buildingType == BT_MANORHOUSE || buildingType == BT_STONEKEEP || buildingType == BT_STRONGHOLD
                    || buildingType == BT_KEEPFOUR || buildingType == BT_KEEPFIVE)) {
                return;
            }
            if (MACRO_CALL_MEMBER(BuildingsState_Func::hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters, this)(
                    playerID, buildingType)
                != 0) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                if (buildingType == BT_PITCHDITCH) {
                    return;
                }
            } else if (buildingType == BT_PITCHDITCH) {
                if (DAT_GameState::instance.playerDataArray[playerID].pitchDitchCounterTo4 == 0) {
                    MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, this)(
                        playerID, Game::Resources::RT_PITCH, 1, param_3);
                    if (param_3 == 0) {
                        DAT_GameState::instance.playerDataArray[playerID].pitchDitchCounterTo4 = 1;
                    }
                    return;
                }
                if (param_3 != 0) {
                    return;
                }
                DAT_GameState::instance.playerDataArray[playerID].pitchDitchCounterTo4 += 1;
                if (DAT_GameState::instance.playerDataArray[playerID].pitchDitchCounterTo4 == 4) {
                    DAT_GameState::instance.playerDataArray[playerID].pitchDitchCounterTo4 = 0;
                }
                return;
            }
            int const wood = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredWood;
            int stone = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredStone_0x4;
            int iron = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredIron_0x8;
            int pitch = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredPitch_0xc;
            int gold = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredGold;
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                iron = 0;
                pitch = 0;
                MACRO_CALL_MEMBER(BuildingsState_Func::resourceGainForKillingPitAndPitchDitch, this)(
                    buildingType, &stone, &gold);
            } else if (wood != 0) {
                MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, this)(
                    playerID, Game::Resources::RT_WOOD, wood, param_3);
            }
            if (stone != 0) {
                MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, this)(
                    playerID, Game::Resources::RT_STONE, stone, param_3);
            }
            if (iron != 0) {
                MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, this)(
                    playerID, Game::Resources::RT_IRON, iron, param_3);
            }
            if (pitch != 0) {
                MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, this)(
                    playerID, Game::Resources::RT_PITCH, pitch, param_3);
            }
            if (gold != 0) {
                MACRO_CALL_MEMBER(BuildingsState_Func::processResourceLoss, this)(
                    playerID, Game::Resources::RT_GOLD, gold, param_3);
            }
        }

    }
}
}
