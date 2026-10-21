#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/MissingResourceState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Audio/SFX/ResourceLackSFX.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"

namespace OpenSHC {
namespace Game {

    using Audio::SFX::ResourceLackSFX;
    using Commands::MappersEnum;
    using Map::Buildings::BuildingType;
    using WindowsHelper::Enums::BOOLEnum;

    // NOTE: buttonID = building Type

    // FUNCTION: STRONGHOLDCRUSADER 0x00457B80
    BOOLEnum GameStateStructures::checkRequiredResourcesForBuildingOrPlanToBuy(
        MappersEnum commandBuildingType, int playerID, BOOLEnum playResourceLackMsgUnk)
    {
        BOOLEnum result = TRUE;
        BOOLEnum isAI = FALSE;
        BuildingType const buildingType
            = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(commandBuildingType);
        int const requiredIron = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredIron_0x8;
        int const requiredPitch = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredPitch_0xc;
        int const requiredWood = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredWood;
        int requiredStone = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredStone_0x4;
        int const requiredGold = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredGold;
        if (DAT_GameCore::instance.solitaryAllBuildingsAreFree != FALSE
            || DAT_GameCore::instance.gameMode_2 == GM_EDITOR) {
            return TRUE;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == GM_SOLITARY) {
            if (commandBuildingType == Commands::M_MAPPER_KEEP1) {
                return TRUE;
            }
            if (commandBuildingType == Commands::M_MAPPER_KEEP2) {
                return TRUE;
            }
            if (commandBuildingType == Commands::M_MAPPER_KEEP3) {
                return TRUE;
            }
        } else if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1
            && DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
            isAI = TRUE;
        }
        if (MACRO_CALL_MEMBER(
                Map::Buildings::BuildingsState_Func::hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters,
                DAT_BuildingsState::ptr)(playerID, buildingType)
            != 0) {
            return TRUE;
        }
        if (requiredIron > this->playerDataArray[playerID].currentResources[6]) {
            result = FALSE;
            if (playResourceLackMsgUnk != FALSE) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_IRON);
            }
            if (isAI) {
                int const ironToBuy = requiredIron - this->playerDataArray[playerID].currentResources[6];
                if (ironToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[6]) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[6] = ironToBuy;
                }
            }
        } else if (requiredPitch > this->playerDataArray[playerID].currentResources[7]) {
            if (buildingType != Map::Buildings::BT_PITCHDITCH
                || this->playerDataArray[playerID].pitchDitchCounterTo4 == 0) {
                result = FALSE;
                if (playResourceLackMsgUnk != FALSE) {
                    MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, Audio::SFX::RLSFX_PITCH);
                }
                if (isAI) {
                    int const pitchToBuy = requiredPitch - this->playerDataArray[playerID].currentResources[7];
                    if (pitchToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[7]) {
                        this->playerDataArray[playerID].resourcesToAcquireArray[7] = pitchToBuy;
                    }
                }
            }
        } else if (requiredGold > this->playerDataArray[playerID].currentResources[0xf]) {
            result = FALSE;
            if (playResourceLackMsgUnk != FALSE) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_GOLD);
            }
        } else if (requiredWood > this->playerDataArray[playerID].currentResources[2]
            && requiredStone > this->playerDataArray[playerID].currentResources[4]) {
            result = FALSE;
            if (playResourceLackMsgUnk != FALSE) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_PARTIAL_STONEUnk);
            }
            if (isAI) {
                int woodToBuy = requiredWood - this->playerDataArray[playerID].currentResources[2];
                if (woodToBuy > 0 && woodToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[2]) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[2] = woodToBuy;
                }
                int stoneToBuyAsWell = requiredStone - this->playerDataArray[playerID].currentResources[4];
                if (stoneToBuyAsWell > 0
                    && stoneToBuyAsWell > this->playerDataArray[playerID].resourcesToAcquireArray[4]) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[4] = stoneToBuyAsWell;
                }
            }
        } else if (requiredWood > this->playerDataArray[playerID].currentResources[2]) {
            result = FALSE;
            if (playResourceLackMsgUnk != FALSE) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_WOOD);
            }
            if (isAI) {
                int woodShortage = requiredWood - this->playerDataArray[playerID].currentResources[2];
                if (woodShortage > 0 && woodShortage > this->playerDataArray[playerID].resourcesToAcquireArray[2]) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[2] = woodShortage;
                }
            }
        } else if (requiredStone > this->playerDataArray[playerID].currentResources[4]) {
            result = FALSE;
            if (playResourceLackMsgUnk != FALSE) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_STONE);
            }
            if (isAI) {
                int stoneToBuy = requiredStone - this->playerDataArray[playerID].currentResources[4];
                if (stoneToBuy > 0 && stoneToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[4]) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[4] = stoneToBuy;
                }
            }
        }
        return result;
    }

}
}
