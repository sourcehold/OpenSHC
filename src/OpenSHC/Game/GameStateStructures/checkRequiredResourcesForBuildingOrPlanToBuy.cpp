#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/MissingResourceState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Audio/SFX/ResourceLackSFX.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"

namespace OpenSHC {
namespace Game {

    using Commands::MappersEnum;
    using Map::Buildings::BuildingType;
    using WindowsHelper::Enums::BOOLEnum;


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
        if (DAT_GameCore::instance.solitaryAllBuildingsAreFree || DAT_GameCore::instance.gameMode_2 == GM_EDITOR) {
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
        if (requiredIron > this->playerDataArray[playerID].currentResources[Resources::RT_IRON]) {
            result = FALSE;
            if (playResourceLackMsgUnk) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_IRON);
            }
            if (isAI) {
                int const ironToBuy = requiredIron - this->playerDataArray[playerID].currentResources[Resources::RT_IRON];
                if (ironToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_IRON]) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_IRON] = ironToBuy;
                }
            }
        } else if (requiredPitch > this->playerDataArray[playerID].currentResources[Resources::RT_PITCH]) {
            if (buildingType != Map::Buildings::BT_PITCHDITCH
                || this->playerDataArray[playerID].pitchDitchCounterTo4 == 0) {
                result = FALSE;
                if (playResourceLackMsgUnk) {
                    MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, Audio::SFX::RLSFX_PITCH);
                }
                if (isAI) {
                    int const pitchToBuy = requiredPitch - this->playerDataArray[playerID].currentResources[Resources::RT_PITCH];
                    if (pitchToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_PITCH]) {
                        this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_PITCH] = pitchToBuy;
                    }
                }
            }
        } else if (requiredGold > this->playerDataArray[playerID].currentResources[Resources::RT_GOLD]) {
            result = FALSE;
            if (playResourceLackMsgUnk) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_GOLD);
            }
        } else if (requiredWood > this->playerDataArray[playerID].currentResources[Resources::RT_WOOD]
            && requiredStone > this->playerDataArray[playerID].currentResources[Resources::RT_STONE]) {
            result = FALSE;
            if (playResourceLackMsgUnk) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_PARTIAL_STONEUnk);
            }
            if (isAI) {
                int woodToBuy = requiredWood - this->playerDataArray[playerID].currentResources[Resources::RT_WOOD];
                if (woodToBuy > 0 && woodToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_WOOD]) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_WOOD] = woodToBuy;
                }
                int stoneToBuyAsWell = requiredStone - this->playerDataArray[playerID].currentResources[Resources::RT_STONE];
                if (stoneToBuyAsWell > 0
                    && stoneToBuyAsWell > this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_STONE]) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_STONE] = stoneToBuyAsWell;
                }
            }
        } else if (requiredWood > this->playerDataArray[playerID].currentResources[Resources::RT_WOOD]) {
            result = FALSE;
            if (playResourceLackMsgUnk) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_WOOD);
            }
            if (isAI) {
                int woodShortage = requiredWood - this->playerDataArray[playerID].currentResources[Resources::RT_WOOD];
                if (woodShortage > 0 && woodShortage > this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_WOOD]) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_WOOD] = woodShortage;
                }
            }
        } else if (requiredStone > this->playerDataArray[playerID].currentResources[Resources::RT_STONE]) {
            result = FALSE;
            if (playResourceLackMsgUnk) {
                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX, DAT_MissingResourceState::ptr)(
                    1, Audio::SFX::RLSFX_STONE);
            }
            if (isAI) {
                int stoneToBuy = requiredStone - this->playerDataArray[playerID].currentResources[Resources::RT_STONE];
                if (stoneToBuy > 0 && stoneToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_STONE]) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[Resources::RT_STONE] = stoneToBuy;
                }
            }
        }
        return result;
    }

}
}
