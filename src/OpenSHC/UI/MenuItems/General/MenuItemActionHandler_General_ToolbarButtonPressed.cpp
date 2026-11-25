#include "../General.func.hpp"

#include "OpenSHC/Audio/MissingResourceState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Audio/SFX/ResourceLackSFX.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_00b96110.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MissingResourceState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::MappersEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00444410
        void General::MenuItemActionHandler_General_ToolbarButtonPressed(MappersEnum buttonID)
        {
            if (DAT_GameSynchronyState::instance.syncStatus != 0) {
                return;
            }
            if (DAT_GameSynchronyState::instance.saveRelated != 0) {
                return;
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .playerDeathRelated
                != 0) {
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    return;
                }
                if (DAT_GameState::instance.mapAndTime.gameOver
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    return;
                }
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .lordKilledByPlayerID
                != 0) {
                return;
            }
            if (DAT_GameCore::instance.gamePausedLogical != 0) {
                return;
            }
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL) {
                if (!MACRO_CALL(OpenSHC::Game_Func::Tutorial_IsActionAllowed)(1,
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                            DAT_BuildingsState::ptr)(buttonID))) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialHintActiveWithTimestamp)();
                    return;
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTutorialBuildingActionState)(6,
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                        DAT_BuildingsState::ptr)(buttonID));
            }
            DAT_00b96110::instance = 0;
            // cases in the original's block order, for the match
            switch (buttonID) {
            case OpenSHC::Commands::M_MAPPER_WALL:
            case OpenSHC::Commands::M_MAPPER_CRENAL:
            case OpenSHC::Commands::M_MAPPER_STAIR:
            case OpenSHC::Commands::M_MAPPER_WOODWALL:
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::getWallTilesThatCanBeBuilt, DAT_GameState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID, OpenSHC::Game::Resources::RT_STONE)
                    == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_STONE);
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                    return;
                }
                break;
            case OpenSHC::Commands::M_MAPPER_DELETE:
                DAT_TileMapState::instance.placementOnWall = 0;
                break;
            case OpenSHC::Commands::M_MAPPER_MOAT:
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                    || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    buttonID = OpenSHC::Commands::M_MAPPER_DUGMOAT;
                }
                break;
            case OpenSHC::Commands::M_MAPPER_ANTIMOAT:
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                    || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    buttonID = OpenSHC::Commands::M_MAPPER_UNDUGMOAT;
                }
                break;
            case OpenSHC::Commands::M_MAPPER_TOTEST:
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING, 0);
                return;
            case OpenSHC::Commands::M_MAPPER_PATROL:
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)()
                    == OpenSHC::Map::Units::UT_INVALID) {
                    return;
                }
                if (DAT_TribesState::instance.patrolButtonPressed) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTribesPatrolButtonPressed)(FALSE);
                    DAT_TribesState::instance.rallyCount = 1;
                    return;
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTribesPatrolButtonPressed)(TRUE);
                DAT_TribesState::instance.rallyCount = 1;
                return;
            // each building case has its own copy; MSVC merges them into the first, as the original has it
            case OpenSHC::Commands::M_MAPPER_GRANARY: {
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference, DAT_GameState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, OpenSHC::Game::Player::Enums::BEIE_GRANARY);
                int const buildingID
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_GRANARY]
                          .id;
                if (buildingID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].surfaceAreaUnk
                        != DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight
                            * DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                        DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 1,
                        DAT_BuildingsState::instance.buildings[buildingID].y + 1);
                }
                break;
            }
            case OpenSHC::Commands::M_MAPPER_STORES: {
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference, DAT_GameState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, OpenSHC::Game::Player::Enums::BEIE_STOCKPILE);
                int const buildingID
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_STOCKPILE]
                          .id;
                if (buildingID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].surfaceAreaUnk
                        != DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight
                            * DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                        DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 1,
                        DAT_BuildingsState::instance.buildings[buildingID].y + 1);
                }
                break;
            }
            case OpenSHC::Commands::M_MAPPER_ARMOURY: {
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference, DAT_GameState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, OpenSHC::Game::Player::Enums::BEIE_ARMORY);
                int const buildingID
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ARMORY]
                          .id;
                if (buildingID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].surfaceAreaUnk
                        != DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight
                            * DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                        DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 1,
                        DAT_BuildingsState::instance.buildings[buildingID].y + 1);
                }
                break;
            }
            case OpenSHC::Commands::M_MAPPER_BARRACKS_EURO: {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST);
                int const buildingID
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MERCENARYPOST]
                          .id;
                if (buildingID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].surfaceAreaUnk
                        != DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight
                            * DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                        DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 1,
                        DAT_BuildingsState::instance.buildings[buildingID].y + 1);
                }
                break;
            }
            case OpenSHC::Commands::M_MAPPER_BARRACKS_ARAB: {
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference, DAT_GameState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, OpenSHC::Game::Player::Enums::BEIE_BARRACKS);
                int const buildingID
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_BARRACKS]
                          .id;
                if (buildingID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].surfaceAreaUnk
                        != DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight
                            * DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                        DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 1,
                        DAT_BuildingsState::instance.buildings[buildingID].y + 1);
                }
                break;
            }
            case OpenSHC::Commands::M_MAPPER_ENGINEERS_GUILD: {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD);
                int const buildingID
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_ENGINEERSGUILD]
                          .id;
                if (buildingID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].surfaceAreaUnk
                        != DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight
                            * DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                        DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 1,
                        DAT_BuildingsState::instance.buildings[buildingID].y + 1);
                }
                break;
            }
            case OpenSHC::Commands::M_MAPPER_TUNNELERS_GUILD: {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD);
                int const buildingID
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_TUNNELERSGUILD]
                          .id;
                if (buildingID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].surfaceAreaUnk
                        != DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight
                            * DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                        DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 1,
                        DAT_BuildingsState::instance.buildings[buildingID].y + 1);
                }
                break;
            }
            case OpenSHC::Commands::M_MAPPER_TRADEPOST: {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE);
                int const buildingID
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_MARKETPLACE]
                          .id;
                if (buildingID != 0
                    && DAT_BuildingsState::instance.buildings[buildingID].surfaceAreaUnk
                        != DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight
                            * DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                        DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[buildingID].x + 1,
                        DAT_BuildingsState::instance.buildings[buildingID].y + 1);
                }
                break;
            }
            case OpenSHC::Commands::M_MAPPER_HEADS:
                DAT_TileMapState::instance.decorationVariantIndex = SEC_RNG::instance.currentNumber1 % 7;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                break;
            case OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION:
                if (!MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getTunnelerIDOnlyIfFirstSelected,
                        DAT_UnitsState::ptr)()) {
                    DAT_StopHandlingMenuItems::instance = 0;
                    return;
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTribesPatrolButtonPressed)(FALSE);
                break;
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1A:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1B:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1C:
            case OpenSHC::Commands::M_MAPPER_GATE_WOOD1D:
                buttonID = (MappersEnum)((DAT_TileMapState::instance.mapOrientation / 2
                                             - OpenSHC::Commands::M_MAPPER_GATE_WOOD1A + buttonID)
                        % 4
                    + OpenSHC::Commands::M_MAPPER_GATE_WOOD1A);
                break;
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE1B:
                buttonID = (MappersEnum)(((DAT_TileMapState::instance.mapOrientation / 2 + buttonID) & 1)
                    + OpenSHC::Commands::M_MAPPER_GATE_STONE1A);
                break;
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2A:
            case OpenSHC::Commands::M_MAPPER_GATE_STONE2B:
                buttonID = (MappersEnum)(((DAT_TileMapState::instance.mapOrientation / 2 + buttonID) & 1)
                    + OpenSHC::Commands::M_MAPPER_GATE_STONE2A);
                break;
            case OpenSHC::Commands::M_MAPPER_STANCE_STAND:
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::queueUnitStance, DAT_TribesState::ptr)(
                    DAT_TribesState::instance.DAT_CurrentTribeID, 0);
                return;
            case OpenSHC::Commands::M_MAPPER_STANCE_DEFENSIVE:
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::queueUnitStance, DAT_TribesState::ptr)(
                    DAT_TribesState::instance.DAT_CurrentTribeID, 1);
                return;
            case OpenSHC::Commands::M_MAPPER_STANCE_AGGRESSIVE:
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::queueUnitStance, DAT_TribesState::ptr)(
                    DAT_TribesState::instance.DAT_CurrentTribeID, 2);
                return;
            case OpenSHC::Commands::M_MAPPER_CATAPULT:
            case OpenSHC::Commands::M_MAPPER_TREBUCHET:
            case OpenSHC::Commands::M_MAPPER_SIEGE_TOWER:
            case OpenSHC::Commands::M_MAPPER_BATTERING_RAM:
            case OpenSHC::Commands::M_MAPPER_PORTABLE_SHIELD:
            case OpenSHC::Commands::M_MAPPER_ARAB_BALLISTA:
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)()) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTribesPatrolButtonPressed)(FALSE);
                    break;
                }
                DAT_StopHandlingMenuItems::instance = 0;
                return;
            case OpenSHC::Commands::M_MAPPER_ENGINEER_BUILD:
                if (!MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)()) {
                    int const siegeEngines
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::countSelectedCatapultsAndTrebuchets,
                            DAT_UnitsState::ptr)();
                    if (siegeEngines == 0) {
                        DAT_StopHandlingMenuItems::instance = 0;
                        return;
                    }
                    if (siegeEngines == 1) {
                        // one catapult or trebuchet: the command needs 10 stone
                        if (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .currentResources[OpenSHC::Game::Resources::RT_STONE]
                            < 10) {
                            MACRO_CALL_MEMBER(OpenSHC::Audio::MissingResourceState_Func::playResourceLackSFX,
                                DAT_MissingResourceState::ptr)(1, OpenSHC::Audio::SFX::RLSFX_STONE);
                            return;
                        }
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                            = DAT_UnitsState::instance.unitIDSelectedCatapultOrTrebuchet;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNKNOWN_86);
                        return;
                    }
                    if (siegeEngines == 2) {
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                            = DAT_TribesState::instance.DAT_CurrentTribeID;
                        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 1;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNKNOWN_86);
                        return;
                    }
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTribesPatrolButtonPressed)(FALSE);
                DAT_UnitsState::instance.hasEngineerSelected = TRUE;
                return;
            case OpenSHC::Commands::M_MAPPER_BUILD_BACK:
                DAT_UnitsState::instance.hasEngineerSelected = FALSE;
                return;
            }
            if (MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                    DAT_BuildingsState::ptr)(buttonID)
                != OpenSHC::Map::Buildings::BT_NONE) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                    DAT_GameState::ptr)(buttonID, DAT_GameSynchronyState::instance.currentPlayerSlotID, TRUE);
            }
            DAT_TileMapState::instance.currentMapperCommand = buttonID;
            DAT_TileMapState::instance.unitPlacementCount = 1;
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                OpenSHC::Audio::SFX::SEID_UNKNOWN_0x87);
            if (buttonID != OpenSHC::Commands::M_MAPPER_CATAPULT
                && buttonID != OpenSHC::Commands::M_MAPPER_ARAB_BALLISTA
                && buttonID != OpenSHC::Commands::M_MAPPER_TREBUCHET
                && buttonID != OpenSHC::Commands::M_MAPPER_SIEGE_TOWER
                && buttonID != OpenSHC::Commands::M_MAPPER_BATTERING_RAM
                && buttonID != OpenSHC::Commands::M_MAPPER_PORTABLE_SHIELD
                && buttonID != OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT1
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT2
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT3
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT4
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT5
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT6
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINT7
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM1
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM2
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM3
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM4
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM5
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM6
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM7
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTE1
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTE2
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTT1
                && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_PLACE_ASSEMBLY_POINTK1
                && DAT_GameCore::instance.activeMenuTab.tabType != DAT_GameCore::instance.field_0x30) {
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = DAT_GameCore::instance.field_0x30;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
            }
        }

    }
}
}
