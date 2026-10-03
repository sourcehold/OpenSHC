#include "../BuildMenu.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00ee1090.hpp"
#include "OpenSHC/Globals/DAT_00ee1094.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
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
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00438BE0
        void BuildMenu::MenuItemRenderFunction_BuildMenu_UnitActionButtons(int mapperValue, ...)
        {
            BOOLEnum BVar1;
            int iVar2;
            int yPosition;
            uint uVar3;
            UnitType UVar4;
            int xPosition;
            uint color2;
            int fontSize;
            BVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::isMapperAvailable,
                DAT_MapPropertiesState::ptr)((OpenSHC::Commands::MappersEnum)mapperValue);
            if (BVar1 == FALSE) {
                DAT_ButtonUnknownZero::instance = 1;
            }
            DAT_ButtonUnknownZero::instance = 0;
            if (0x22e < DAT_CurrentButtonGmDataIndex::instance) {
            switchD_00438c35_caseD_d9:
                if (DAT_UnitsState::instance.hasEngineerSelected != FALSE) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == ((UnitType)0xffffffff)) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                goto LAB_00438ec1;
            }
            if (DAT_CurrentButtonGmDataIndex::instance == 0x22e) {
            switchD_00438c35_caseD_d3:
                if (DAT_UnitsState::instance.hasEngineerSelected != TRUE) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                uVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)();
                if (uVar3 == 0) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
            LAB_00438ec1:
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                DAT_ButtonUnknownZero::instance = 0;
            }
            switch (DAT_CurrentButtonGmDataIndex::instance) {
            case 0xd3:
            case 0xd4:
            case 0xd5:
            case 0xd6:
            case 0xd7:
                goto switchD_00438c35_caseD_d3;
            case 0xd8:
                if (DAT_UnitsState::instance.hasEngineerSelected != FALSE) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == ((UnitType)0xffffffff)) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (DAT_TribesState::instance.patrolButtonPressed != FALSE) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = 0;
                }
                goto LAB_00438ec1;
            default:
                goto switchD_00438c35_caseD_d9;
            case 0xda:
                if (((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                        && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT))
                    && ((DAT_UnitsState::instance.hasEngineerSelected == FALSE
                        && (uVar3
                            = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getTunnelerIDOnlyIfFirstSelected,
                                DAT_UnitsState::ptr)(),
                            uVar3 != 0)))) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = 0;
                }
                break;
            case 0xdb:
                DAT_00ee1090::instance = 0xca;
                if (((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                        && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT))
                    && (DAT_UnitsState::instance.hasEngineerSelected == FALSE)) {
                    BVar1 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::selectionContainsEngineersOnly, DAT_UnitsState::ptr)();
                    if (BVar1 == FALSE) {
                        iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectionContainsTunnelersOnly,
                            DAT_UnitsState::ptr)();
                        if (iVar2 != 0) {
                            DAT_CurrentButtonGmDataIndex::instance = 0xda;
                            DAT_00ee1090::instance = 0xc9;
                            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                            DAT_ButtonUnknownZero::instance = 0;
                        }
                        uVar3
                            = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getFirstSelectedUnitOfEitherType,
                                DAT_UnitsState::ptr)(0x27, 0x28);
                        if (uVar3 != 0) {
                            DAT_CurrentButtonGmDataIndex::instance = 0x177;
                            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                            BVar1 = FALSE;
                            fontSize = 0x13;
                            color2 = 0;
                            uVar3 = 0xffffff;
                            yPosition = DAT_ButtonY::instance + 2;
                            xPosition = DAT_ButtonX::instance + 2;
                            iVar2 = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::getMaxStoneAmmoInSelectedSiegeEngines,
                                DAT_UnitsState::ptr)();
                            goto LAB_00438e95;
                        }
                        BVar1
                            = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectionContainsRangedOnlyUnits,
                                DAT_UnitsState::ptr)();
                        if (BVar1 != FALSE) {
                            DAT_CurrentButtonGmDataIndex::instance = 0x177;
                            goto LAB_00438ec1;
                        }
                        iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectionContainsLaddermenOnly,
                            DAT_UnitsState::ptr)();
                        if ((iVar2 == 0)
                            && (iVar2 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Units::UnitsState_Func::selectionContainsShieldmenOnly,
                                    DAT_UnitsState::ptr)(),
                                iVar2 == 0)) {
                            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                            DAT_ButtonUnknownZero::instance = 0;
                        }
                    } else {
                        uVar3 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource,
                            DAT_UnitsState::ptr)();
                        if (uVar3 != 0) {
                            DAT_CurrentButtonGmDataIndex::instance = 0xd2;
                            DAT_00ee1090::instance = 0xc6;
                            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                            DAT_ButtonUnknownZero::instance = 0;
                        }
                    }
                }
                break;
            case 0xdc:
                if (((((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                          && (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT))
                         && ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                             || ((DAT_GameSynchronyState::instance.currentGameMode
                                     == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                                 || (DAT_GameState::instance.mapAndTime.skirmishNoCowThrowing == 0))))))
                        && (DAT_UnitsState::instance.hasEngineerSelected == FALSE))
                    && ((uVar3
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getFirstSelectedUnitOfEitherType,
                            DAT_UnitsState::ptr)(0x27, 0x28),
                        uVar3 != 0
                            && (0 < DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .counter)))) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    BVar1 = FALSE;
                    yPosition = DAT_ButtonY::instance + 2;
                    xPosition = DAT_ButtonX::instance + 2;
                    fontSize = 0x13;
                    color2 = 0;
                    uVar3 = 0xffffff;
                    iVar2
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .counter;
                LAB_00438e95:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber, DAT_TextManagerObject::ptr)(
                        iVar2, xPosition, yPosition, uVar3, color2, fontSize, BVar1);
                    DAT_ButtonUnknownZero::instance = 0;
                }
                break;
            case 0x172:
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == ((UnitType)0xffffffff)) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == OpenSHC::Map::Units::Behavior::USE_STAND_GROUND) {
                    DAT_ButtonY::instance = DAT_ButtonY::instance + -5;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = 0;
                }
                goto LAB_00438f47;
            case 0x173:
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == ((UnitType)0xffffffff)) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == OpenSHC::Map::Units::Behavior::USE_DEFENSIVE) {
                    DAT_ButtonY::instance = DAT_ButtonY::instance + -1;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = 0;
                }
                goto LAB_00438f47;
            case 0x174:
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == ((UnitType)0xffffffff)) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE) {
                    DAT_ButtonY::instance = DAT_ButtonY::instance + -1;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = 0;
                }
            LAB_00438f47:
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                DAT_ButtonUnknownZero::instance = 0;
                return;
            case 0x176:
                DAT_00ee1094::instance = 0x123;
                if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                    && (DAT_UnitsState::instance.hasEngineerSelected == FALSE)) {
                    uVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)();
                    if (uVar3 != 0)
                        goto LAB_00438ec1;
                    iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::countSelectedCatapultsAndTrebuchets,
                        DAT_UnitsState::ptr)();
                    if (iVar2 != 0) {
                        DAT_00ee1094::instance = 0x134;
                        DAT_CurrentButtonGmDataIndex::instance = 0x179;
                        MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                        DAT_ButtonUnknownZero::instance = 0;
                    }
                }
                break;
            case 0x178:
                if (DAT_UnitsState::instance.hasEngineerSelected == TRUE) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                }
            }
            DAT_ButtonUnknownZero::instance = 1;
        }

    }
}
}
