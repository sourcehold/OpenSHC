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
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using Audio::SFX::ResourceLackSFX;
        using Audio::SFX::SoundEffectID;
        using Commands::GameCommandType;
        using Commands::MappersEnum;
        using Game::GameMode;
        using Game::GameMode2;
        using Map::Buildings::BuildingType;
        using Map::Units::UnitType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        /*
          This includes stuff like the buildings to place, but also the unit stances for example.   -TheRedDaemon
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00444410
        void General::MenuItemActionHandler_General_ToolbarButtonPressed(MappersEnum buttonID)
        {
            BuildingType BVar1;
            BOOLEnum BVar2;
            int iVar3;
            UnitType UVar4;
            uint uVar5;
            undefined4 uVar6;
            if (DAT_GameSynchronyState::instance.syncStatus) {}
            if (DAT_GameSynchronyState::instance.saveRelated) {}
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .playerDeathRelated
                != 0) {
                if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {}
                if (DAT_GameState::instance.mapAndTime.gameOver
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {}
            }
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .lordKilledByPlayerID
                != 0) {}
            if (DAT_GameCore::instance.gamePausedLogical) {}
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_CRUSADER_TUTORIAL) {
                BVar1 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                    DAT_BuildingsState::ptr)(buttonID);
                BVar2 = MACRO_CALL(Game_Func::Tutorial_IsActionAllowed)(1, (int)(BVar1));
                if (!BVar2) {
                    MACRO_CALL(UI::Helpers_Func::SetTutorialHintActiveWithTimestamp)();
                }
                BVar1 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                    DAT_BuildingsState::ptr)(buttonID);
                MACRO_CALL(UI::Helpers_Func::SetTutorialBuildingActionState)(6, BVar1);
            }
            DAT_00b96110::instance = 0;
            if (0x11f < (int)buttonID) {
                switch (buttonID) {
                case Commands::M_MAPPER_STANCE_DEFENSIVE:
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::queueUnitStance, DAT_TribesState::ptr)(
                        DAT_TribesState::instance.DAT_CurrentTribeID, 1);
                    return;
                case Commands::M_MAPPER_STANCE_AGGRESSIVE:
                    uVar6 = 2;
                    goto LAB_00444927;
                default:
                    goto switchD_00444907_caseD_122;
                case Commands::M_MAPPER_ENGINEER_BUILD:
                    uVar5 = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)();
                    if (!uVar5) {
                        iVar3 = MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::countSelectedCatapultsAndTrebuchets, DAT_UnitsState::ptr)();
                        if (!iVar3) {
                            DAT_StopHandlingMenuItems::instance = 0;
                        }
                        if (iVar3 == 1) {
                            /*
                              Maybe refill catapult/tripok stones? - TheRedDaemon
                             */
                            if (DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .currentResources[4]
                                < 10) {
                                MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX,
                                    DAT_MissingResourceState::ptr)(1, Audio::SFX::RLSFX_STONE);
                            }
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                                = DAT_UnitsState::instance.field15_0x560;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 0;
                            MACRO_CALL_MEMBER(
                                Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                                (Commands::GameCommandType)(Commands::GCT_SEND_RESYNC_UNKNOWN2
                                    | Commands::GCT_MULTIPLAYER_INITIATE_ANNOUNCE_HOST));
                        }
                        if (iVar3 == 2) {
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                                = DAT_TribesState::instance.DAT_CurrentTribeID;
                            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = 1;
                            MACRO_CALL_MEMBER(
                                Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                                (Commands::GameCommandType)(Commands::GCT_SEND_RESYNC_UNKNOWN2
                                    | Commands::GCT_MULTIPLAYER_INITIATE_ANNOUNCE_HOST));
                        }
                    }
                    MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                    DAT_UnitsState::instance.hasEngineerSelected = TRUE;
                    return;
                case Commands::M_MAPPER_BUILD_BACK:
                    DAT_UnitsState::instance.hasEngineerSelected = FALSE;
                    return;
                case Commands::M_MAPPER_ARAB_BALLISTA:
                    goto switchD_00444907_caseD_166;
                }
            }
            if (buttonID == Commands::M_MAPPER_STANCE_STAND) {
                uVar6 = 0;
            LAB_00444927:
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::queueUnitStance, DAT_TribesState::ptr)(
                    DAT_TribesState::instance.DAT_CurrentTribeID, (undefined4)((int)(uVar6)));
            }
            switch (buttonID) {
            case Commands::M_MAPPER_WALL:
            case Commands::M_MAPPER_CRENAL:
            case Commands::M_MAPPER_STAIR:
            case Commands::M_MAPPER_WOODWALL:
                iVar3 = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getWallTilesThatCanBeBuilt,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 4);
                if (!iVar3) {
                    MACRO_CALL_MEMBER(Audio::MissingResourceState_Func::playResourceLackSFX,
                        DAT_MissingResourceState::ptr)(1, Audio::SFX::RLSFX_STONE);
                    DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                }
                break;
            case Commands::M_MAPPER_TOTEST:
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAP_EDITOR_LANDSCAPING, 0);
                return;
            case Commands::M_MAPPER_PATROL:
                UVar4 = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == (UnitType)0xffffffff) {}
                if (DAT_TribesState::instance.patrolButtonPressed) {
                    MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
                    DAT_TribesState::instance.rallyCount = 1;
                }
                MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(1);
                DAT_TribesState::instance.rallyCount = 1;
                return;
            case Commands::M_MAPPER_DELETE:
                DAT_TileMapState::instance.placementOnWall = 0;
                break;
            case Commands::M_MAPPER_STORES:
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 1);
                iVar3 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .stockpile.id;
                goto LAB_004445d7;
            case Commands::M_MAPPER_TUNNEL_CONSTRUCTION:
                uVar5 = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getTunnelerIDOnlyIfFirstSelected, DAT_UnitsState::ptr)();
                goto joined_r0x00444948;
            case Commands::M_MAPPER_TRADEPOST:
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 7);
                iVar3 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketplace.id;
                goto LAB_004445d7;
            case Commands::M_MAPPER_GRANARY:
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 2);
                iVar3 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .granary.id;
                goto LAB_004445d7;
            case Commands::M_MAPPER_ARMOURY:
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 3);
                iVar3 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .armory.id;
                goto LAB_004445d7;
            case Commands::M_MAPPER_BARRACKS_EURO:
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 0xb);
                iVar3 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .mercenaryPost.id;
                goto LAB_004445d7;
            case Commands::M_MAPPER_BARRACKS_ARAB:
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 5);
                iVar3 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .barracks.id;
                goto LAB_004445d7;
            case Commands::M_MAPPER_ENGINEERS_GUILD:
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 9);
                iVar3 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .engineersGuild.id;
                goto LAB_004445d7;
            case Commands::M_MAPPER_TUNNELERS_GUILD:
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::validateBuildingCategoryReference,
                    DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 10);
                iVar3 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .tunnelersGuild.id;
            LAB_004445d7:
                if ((iVar3)
                    && (uVar5 = DAT_BuildingsState::instance.buildings[iVar3].widthOrHeight,
                        (int)DAT_BuildingsState::instance.buildings[iVar3].surfaceAreaUnk != uVar5 * uVar5)) {
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::focusOnCoordinate,
                        DAT_ViewportRenderState::ptr)((short)DAT_BuildingsState::instance.buildings[iVar3].x + 1,
                        (int)((short)DAT_BuildingsState::instance.buildings[iVar3].y + 1));
                }
                break;
            case Commands::M_MAPPER_MOAT:
                if ((DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR)
                    || (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT)) {
                    buttonID = Commands::M_MAPPER_DUGMOAT;
                }
                break;
            case Commands::M_MAPPER_ANTIMOAT:
                if ((DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR)
                    || (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT)) {
                    buttonID = Commands::M_MAPPER_UNDUGMOAT;
                }
                break;
            case Commands::M_MAPPER_HEADS:
                DAT_TileMapState::instance.decorationVariantIndex = (int)SEC_RNG::instance.currentNumber1 % 7;
                MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber1, SEC_RNG::ptr)();
                break;
            case Commands::M_MAPPER_GATE_WOOD1A:
            case Commands::M_MAPPER_GATE_WOOD1B:
            case Commands::M_MAPPER_GATE_WOOD1C:
            case Commands::M_MAPPER_GATE_WOOD1D:
                uVar5 = DAT_TileMapState::instance.mapOrientation / 2 + -0x8c + buttonID & 0x80000003;
                if ((int)uVar5 < 0) {
                    uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
                }
                buttonID = (Commands::MappersEnum)(uVar5 + Commands::M_MAPPER_GATE_WOOD1A);
                break;
            case Commands::M_MAPPER_GATE_STONE1A:
            case Commands::M_MAPPER_GATE_STONE1B:
                buttonID = (Commands::MappersEnum)((DAT_TileMapState::instance.mapOrientation / 2 + buttonID & 1)
                    + Commands::M_MAPPER_GATE_STONE1A);
                break;
            case Commands::M_MAPPER_GATE_STONE2A:
            case Commands::M_MAPPER_GATE_STONE2B:
                buttonID = (Commands::MappersEnum)((DAT_TileMapState::instance.mapOrientation / 2 + buttonID & 1)
                    + Commands::M_MAPPER_GATE_STONE2A);
                break;
            case Commands::M_MAPPER_CATAPULT:
            case Commands::M_MAPPER_TREBUCHET:
            case Commands::M_MAPPER_SIEGE_TOWER:
            case Commands::M_MAPPER_BATTERING_RAM:
            case Commands::M_MAPPER_PORTABLE_SHIELD:
                goto switchD_00444907_caseD_166;
            }
        switchD_00444907_caseD_122:
            BVar1 = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                DAT_BuildingsState::ptr)(buttonID);
            if (BVar1 != (BuildingType)0) {
                MACRO_CALL_MEMBER(Game::GameStateStructures_Func::checkRequiredResourcesForBuildingOrPlanToBuy,
                    DAT_GameState::ptr)(buttonID, (int)(DAT_GameSynchronyState::instance.currentPlayerSlotID), TRUE);
            }
            DAT_TileMapState::instance.unitPlacementCount = 1;
            DAT_TileMapState::instance.currentMapperCommand = buttonID;
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(((SoundEffectID)0x87));
            if (buttonID != Commands::M_MAPPER_CATAPULT && buttonID != Commands::M_MAPPER_ARAB_BALLISTA
                && buttonID != Commands::M_MAPPER_TREBUCHET && buttonID != Commands::M_MAPPER_SIEGE_TOWER
                && buttonID != Commands::M_MAPPER_BATTERING_RAM && buttonID != Commands::M_MAPPER_PORTABLE_SHIELD
                && buttonID != Commands::M_MAPPER_TUNNEL_CONSTRUCTION
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINT1
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINT2
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINT3
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINT4
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINT5
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINT6
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINT7
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM1
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM2
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM3
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM4
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM5
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM6
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINTM7
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINTE1
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINTE2
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINTT1
                && DAT_TileMapState::instance.currentMapperCommand != Commands::M_MAPPER_PLACE_ASSEMBLY_POINTK1
                && DAT_GameCore::instance.activeMenuTab.tabType != DAT_GameCore::instance.field12_0x30) {
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = DAT_GameCore::instance.field12_0x30;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_BUILD_MENU, 0);
            }
            return;
        switchD_00444907_caseD_166:
            uVar5 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)();
        joined_r0x00444948:
            if (!uVar5) {
                DAT_StopHandlingMenuItems::instance = 0;
            }
            MACRO_CALL(UI::Helpers_Func::SetTribesPatrolButtonPressed)(0);
            goto switchD_00444907_caseD_122;
        }

    }
}
}
