#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00421D70
        void BuildingsState::giveBackResourceForDestroyedBuilding(
            int buildingIDORIfNegResourceType, int playerID, int param_3)
        {
            // param_3 is the percentage of the costs that is given back
            if (param_3 == 0) {
                return;
            }
            int percentage = param_3;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                percentage = 100;
            }

            if (buildingIDORIfNegResourceType == -1) {
                // Stone of a wall
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    ++DAT_GameState::instance.playerDataArray[playerID]
                          .startResources[OpenSHC::Game::Resources::RT_STONE];
                    return;
                }
                DAT_GameState::instance.playerDataArray[playerID].stoneGainedFraction += percentage * 2 / 100;
                int stone = DAT_GameState::instance.playerDataArray[playerID].stoneGainedFraction / 4;
                DAT_GameState::instance.playerDataArray[playerID].stoneGainedFraction -= stone * 4;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, stone)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
                return;
            }
            if (buildingIDORIfNegResourceType == -2) {
                // Wood
                DAT_GameState::instance.playerDataArray[playerID].woodGainedFraction += percentage * 2 / 100;
                int wood = DAT_GameState::instance.playerDataArray[playerID].woodGainedFraction / 4;
                DAT_GameState::instance.playerDataArray[playerID].woodGainedFraction -= wood * 4;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_WOOD, wood)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
                return;
            }

            int pitch;
            int gold;
            if (buildingIDORIfNegResourceType == -3) {
                // Mangonel on a tower
                int wood = this->buildingCosts[BT_MANGONEL].requiredWood * percentage / 100;
                int stone = this->buildingCosts[BT_MANGONEL].requiredStone_0x4 * percentage / 100;
                int iron = this->buildingCosts[BT_MANGONEL].requiredIron_0x8 * percentage / 100;
                pitch = this->buildingCosts[BT_MANGONEL].requiredPitch_0xc * percentage / 100;
                gold = this->buildingCosts[BT_MANGONEL].requiredGold * percentage / 100;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_WOOD, wood)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, stone)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_IRON, iron)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
            } else if (buildingIDORIfNegResourceType == -4) {
                // Ballista on a tower
                int wood = this->buildingCosts[BT_BALLISTA].requiredWood * percentage / 100;
                int stone = this->buildingCosts[BT_BALLISTA].requiredStone_0x4 * percentage / 100;
                int iron = this->buildingCosts[BT_BALLISTA].requiredIron_0x8 * percentage / 100;
                pitch = this->buildingCosts[BT_BALLISTA].requiredPitch_0xc * percentage / 100;
                gold = this->buildingCosts[BT_BALLISTA].requiredGold * percentage / 100;
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_WOOD, wood)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, stone)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_IRON, iron)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
            } else {
                int buildingType = this->buildings[buildingIDORIfNegResourceType].buildingType;
                int wood = this->buildingCosts[buildingType].requiredWood * percentage / 100;
                int stone = this->buildingCosts[buildingType].requiredStone_0x4 * percentage / 100;
                int iron = this->buildingCosts[buildingType].requiredIron_0x8 * percentage / 100;
                pitch = this->buildingCosts[buildingType].requiredPitch_0xc * percentage / 100;
                gold = this->buildingCosts[buildingType].requiredGold * percentage / 100;
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::resourceGainForKillingPitAndPitchDitch, this)(
                        (BuildingType)this->buildings[buildingIDORIfNegResourceType].buildingType, &stone, &gold);
                    DAT_GameState::instance.playerDataArray[playerID].startResources[OpenSHC::Game::Resources::RT_STONE]
                        += stone;
                    DAT_GameState::instance.playerDataArray[playerID].startResources[OpenSHC::Game::Resources::RT_GOLD]
                        += gold;
                    return;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_WOOD, wood)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, stone)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_IRON, iron)
                    == FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                        DAT_GameState::ptr)(playerID);
                }
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_PITCH, pitch)
                == FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                    DAT_GameState::ptr)(playerID);
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                    DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_GOLD, gold)
                == FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::playSFXNoSpaceInTheStockPile,
                    DAT_GameState::ptr)(playerID);
            }
        }

    }
}
}
