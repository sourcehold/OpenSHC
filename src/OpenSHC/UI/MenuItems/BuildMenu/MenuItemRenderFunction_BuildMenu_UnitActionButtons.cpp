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

        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

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
            if (!BVar1) {
                DAT_ButtonUnknownZero::instance = 1;
                return;
            }
            DAT_ButtonUnknownZero::instance = 0;
            switch ((int)DAT_CurrentButtonGmDataIndex::instance) {
            case 376:
                // Without an engineer selected the button hides, as in the original (jne to the shared hide).
                if (DAT_UnitsState::instance.hasEngineerSelected == TRUE) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    return;
                }
                break;
            case 374:
                DAT_00ee1094::instance = 291;
                if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR)
                    && (!DAT_UnitsState::instance.hasEngineerSelected)) {
                    uVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)();
                    if (uVar3 != 0)
                        goto LAB_00438ec1;
                    iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::countSelectedCatapultsAndTrebuchets,
                        DAT_UnitsState::ptr)();
                    if (iVar2 != 0) {
                        DAT_00ee1094::instance = 308;
                        DAT_CurrentButtonGmDataIndex::instance = 377;
                        MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                        DAT_ButtonUnknownZero::instance = 0;
                        return;
                    }
                }
                break;
            case 218:
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
                    && !DAT_UnitsState::instance.hasEngineerSelected
                    && (uVar3
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getTunnelerIDOnlyIfFirstSelected,
                            DAT_UnitsState::ptr)(),
                        uVar3 != 0)) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = 0;
                    return;
                }
                break;
            case 220:
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
                    && (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                        || ((
                            DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                            || (DAT_GameState::instance.mapAndTime.skirmishNoCowThrowing == 0))))
                    && !DAT_UnitsState::instance.hasEngineerSelected
                    && (uVar3
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getFirstSelectedUnitOfEitherType,
                            DAT_UnitsState::ptr)(39, 40),
                        uVar3 != 0
                            && (0 < DAT_GameState::instance
                                    .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                    .availableCows))) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    BVar1 = FALSE;
                    yPosition = DAT_ButtonY::instance + 2;
                    xPosition = DAT_ButtonX::instance + 2;
                    fontSize = 19;
                    color2 = 0;
                    uVar3 = 16777215;
                    iVar2
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .availableCows;
                LAB_00438e95:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber, DAT_TextManagerObject::ptr)(
                        iVar2, xPosition, yPosition, uVar3, color2, fontSize, BVar1);
                    DAT_ButtonUnknownZero::instance = 0;
                    return;
                }
                break;
            case 219:
                DAT_00ee1090::instance = 202;
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT
                    && !DAT_UnitsState::instance.hasEngineerSelected) {
                    BVar1 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::UnitsState_Func::selectionContainsEngineersOnly, DAT_UnitsState::ptr)();
                    if (BVar1) {
                        uVar3 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource,
                            DAT_UnitsState::ptr)();
                        if (uVar3 != 0) {
                            DAT_CurrentButtonGmDataIndex::instance = 210;
                            DAT_00ee1090::instance = 198;
                            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                            DAT_ButtonUnknownZero::instance = 0;
                            return;
                        }
                    } else {
                        iVar2 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectionContainsTunnelersOnly,
                            DAT_UnitsState::ptr)();
                        if (iVar2 != 0) {
                            DAT_CurrentButtonGmDataIndex::instance = 218;
                            DAT_00ee1090::instance = 201;
                            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                            DAT_ButtonUnknownZero::instance = 0;
                            return;
                        }
                        uVar3
                            = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getFirstSelectedUnitOfEitherType,
                                DAT_UnitsState::ptr)(39, 40);
                        if (uVar3 != 0) {
                            DAT_CurrentButtonGmDataIndex::instance = 375;
                            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                            BVar1 = FALSE;
                            fontSize = 19;
                            color2 = 0;
                            uVar3 = 16777215;
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
                        if (BVar1) {
                            DAT_CurrentButtonGmDataIndex::instance = 375;
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
                            return;
                        }
                    }
                }
                break;
            case 370:
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == OpenSHC::Map::Units::UT_INVALID) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == OpenSHC::Map::Units::Behavior::USE_STAND_GROUND) {
                    DAT_ButtonY::instance -= 5;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = 0;
                    return;
                }
                goto LAB_00438f47;
            case 371:
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == OpenSHC::Map::Units::UT_INVALID) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == OpenSHC::Map::Units::Behavior::USE_DEFENSIVE) {
                    --DAT_ButtonY::instance;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = 0;
                    return;
                }
                goto LAB_00438f47;
            case 372:
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == OpenSHC::Map::Units::UT_INVALID) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE) {
                    --DAT_ButtonY::instance;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = 0;
                    return;
                }
            LAB_00438f47:
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                DAT_ButtonUnknownZero::instance = 0;
                return;
            case 216:
                if (DAT_UnitsState::instance.hasEngineerSelected) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == OpenSHC::Map::Units::UT_INVALID) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (DAT_TribesState::instance.patrolButtonPressed) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = 0;
                    return;
                }
                goto LAB_00438ec1;
            case 211:
            case 212:
            case 213:
            case 214:
            case 215:
            case 558:
                if (DAT_UnitsState::instance.hasEngineerSelected != TRUE) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                uVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)();
                if (uVar3 == 0) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                goto LAB_00438ec1;
            default:
                if (DAT_UnitsState::instance.hasEngineerSelected) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                UVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                if (UVar4 == OpenSHC::Map::Units::UT_INVALID) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
            LAB_00438ec1:
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                DAT_ButtonUnknownZero::instance = 0;
                return;
            }
            DAT_ButtonUnknownZero::instance = 1;
        }

    }
}
}
