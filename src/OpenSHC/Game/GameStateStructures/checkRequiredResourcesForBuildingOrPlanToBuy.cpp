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

    using OpenSHC::Audio::SFX::ResourceLackSFX;
    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      buttonID = building Type   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00457B80
    undefined4 GameStateStructures::checkRequiredResourcesForBuildingOrPlanToBuy(
        MappersEnum commandBuildingType, int playerID, BOOLEnum playResourceLackMsgUnk)
    {
        int result = 1;
        int isAI = 0;
        BuildingType buildingType
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(commandBuildingType);
        int requiredIron = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredIron_0x8;
        int requiredPitch = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredPitch_0xc;
        int requiredWood = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredWood;
        int requiredStone = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredStone_0x4;
        int requiredGold = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredGold;
        if ((DAT_GameCore::instance.solitaryAllBuildingsAreFree != FALSE)
            || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)) {
            return 1;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            if (commandBuildingType == OpenSHC::Commands::M_MAPPER_KEEP1) {
                return 1;
            }
            if (commandBuildingType == OpenSHC::Commands::M_MAPPER_KEEP2) {
                return 1;
            }
            if (commandBuildingType == OpenSHC::Commands::M_MAPPER_KEEP3) {
                return 1;
            }
        } else if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] == -1)
            && (DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0)) {
            isAI = 1;
        }
        if (MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters,
                DAT_BuildingsState::ptr)(playerID, buildingType)
            != 0) {
            return 1;
        }
        if (requiredIron > this->playerDataArray[playerID].currentResources[6]) {
            result = 0;
            if (playResourceLackMsgUnk != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                    DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_IRON);
            }
            if (isAI != 0) {
                int ironToBuy = requiredIron - this->playerDataArray[playerID].currentResources[6];
                if (ironToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[6]) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[6] = ironToBuy;
                }
            }
        } else if (requiredPitch > this->playerDataArray[playerID].currentResources[7]) {
            if ((buildingType != OpenSHC::Map::Buildings::BT_PITCHDITCH)
                || (this->playerDataArray[playerID].pitchDitchCounterTo4 == 0)) {
                result = 0;
                if (playResourceLackMsgUnk != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_PITCH);
                }
                if (isAI != 0) {
                    int pitchToBuy = requiredPitch - this->playerDataArray[playerID].currentResources[7];
                    if (pitchToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[7]) {
                        this->playerDataArray[playerID].resourcesToAcquireArray[7] = pitchToBuy;
                    }
                }
            }
        } else if (requiredGold > this->playerDataArray[playerID].currentResources[0xf]) {
            result = 0;
            if (playResourceLackMsgUnk != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                    DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_GOLD);
            }
        } else if ((requiredWood > this->playerDataArray[playerID].currentResources[2])
            && (requiredStone > this->playerDataArray[playerID].currentResources[4])) {
            result = 0;
            if (playResourceLackMsgUnk != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                    DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_PARTIAL_STONEUnk);
            }
            if (isAI != 0) {
                int woodToBuy = requiredWood - this->playerDataArray[playerID].currentResources[2];
                if ((woodToBuy > 0) && (woodToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[2])) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[2] = woodToBuy;
                }
                int stoneToBuyAsWell = requiredStone - this->playerDataArray[playerID].currentResources[4];
                if ((stoneToBuyAsWell > 0)
                    && (stoneToBuyAsWell > this->playerDataArray[playerID].resourcesToAcquireArray[4])) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[4] = stoneToBuyAsWell;
                }
            }
        } else if (requiredWood > this->playerDataArray[playerID].currentResources[2]) {
            result = 0;
            if (playResourceLackMsgUnk != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                    DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_WOOD);
            }
            if (isAI != 0) {
                int woodShortage = requiredWood - this->playerDataArray[playerID].currentResources[2];
                if ((woodShortage > 0) && (woodShortage > this->playerDataArray[playerID].resourcesToAcquireArray[2])) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[2] = woodShortage;
                }
            }
        } else if (requiredStone > this->playerDataArray[playerID].currentResources[4]) {
            result = 0;
            if (playResourceLackMsgUnk != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                    DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_STONE);
            }
            if (isAI != 0) {
                int stoneToBuy = requiredStone - this->playerDataArray[playerID].currentResources[4];
                if ((stoneToBuy > 0) && (stoneToBuy > this->playerDataArray[playerID].resourcesToAcquireArray[4])) {
                    this->playerDataArray[playerID].resourcesToAcquireArray[4] = stoneToBuy;
                }
            }
        }
        return result;
    }
}
}
