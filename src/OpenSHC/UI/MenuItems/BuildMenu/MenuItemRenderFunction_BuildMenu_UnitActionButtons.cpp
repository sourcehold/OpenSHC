#include "../BuildMenu.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/GmDataIndex.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x00438BE0
        void BuildMenu::MenuItemRenderFunction_BuildMenu_UnitActionButtons(int mapperValue, ...)
        {
            if (!MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::isMapperAvailable, DAT_MapPropertiesState::ptr)(
                    (Commands::MappersEnum)mapperValue)) {
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            }
            DAT_ButtonUnknownZero::instance = FALSE;
            // A shown button breaks to the one render behind the switch, except where the render is written out.
            switch ((int)DAT_CurrentButtonGmDataIndex::instance) {
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_376_PIC_325:
                // == TRUE: a truth test loses the match
                if (DAT_UnitsState::instance.hasEngineerSelected == TRUE) {
                    MACRO_CALL(General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    return;
                }
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_374_PIC_315:
                DAT_00ee1094::instance = 291;
                if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR
                    || DAT_UnitsState::instance.hasEngineerSelected) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)()
                    != 0) {
                    break;
                }
                if (MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::countSelectedCatapultsAndTrebuchets, DAT_UnitsState::ptr)()
                    == 0) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                DAT_00ee1094::instance = 308;
                DAT_CurrentButtonGmDataIndex::instance = OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_377_PIC_414;
                break;
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_218_PIC_321:
                if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR
                    || DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT
                    || DAT_UnitsState::instance.hasEngineerSelected
                    || MACRO_CALL_MEMBER(
                           Map::Units::UnitsState_Func::getTunnelerIDOnlyIfFirstSelected, DAT_UnitsState::ptr)()
                        == 0) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                // written out behind one || test: a break or separate ifs lose the match
                MACRO_CALL(General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                DAT_ButtonUnknownZero::instance = FALSE;
                return;
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_220_PIC_305:
                if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR
                    || DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT
                    || (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
                        && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER
                        && DAT_GameState::instance.mapAndTime.skirmishNoCowThrowing != 0)
                    || DAT_UnitsState::instance.hasEngineerSelected
                    || MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getFirstSelectedUnitOfEitherType,
                           DAT_UnitsState::ptr)(Map::Units::UT_S_CATAPULT, Map::Units::UT_S_TREBUCHET)
                        == 0
                    || DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .availableCows
                        <= 0) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                MACRO_CALL(General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .availableCows,
                    DAT_ButtonX::instance + 2, DAT_ButtonY::instance + 2, OpenSHC::Rendering::Colors::COL_FFFFFF,
                    OpenSHC::Rendering::Colors::COL_000000, 19, FALSE);
                DAT_ButtonUnknownZero::instance = FALSE;
                return;
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_219_PIC_317:
                DAT_00ee1090::instance = 202;
                if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR
                    || DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT
                    || DAT_UnitsState::instance.hasEngineerSelected) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                if (MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsEngineersOnly, DAT_UnitsState::ptr)()) {
                    if (MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource, DAT_UnitsState::ptr)()
                        == 0) {
                        DAT_ButtonUnknownZero::instance = TRUE;
                        return;
                    }
                    DAT_CurrentButtonGmDataIndex::instance
                        = OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_210_PIC_319;
                    DAT_00ee1090::instance = 198;
                    break;
                }
                if (MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsTunnelersOnly, DAT_UnitsState::ptr)()) {
                    DAT_CurrentButtonGmDataIndex::instance
                        = OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_218_PIC_321;
                    DAT_00ee1090::instance = 201;
                    break;
                }
                if (MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getFirstSelectedUnitOfEitherType,
                        DAT_UnitsState::ptr)(Map::Units::UT_S_CATAPULT, Map::Units::UT_S_TREBUCHET)
                    != 0) {
                    DAT_CurrentButtonGmDataIndex::instance
                        = OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_375_PIC_323;
                    MACRO_CALL(General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::getMaxStoneAmmoInSelectedSiegeEngines, DAT_UnitsState::ptr)(),
                        DAT_ButtonX::instance + 2, DAT_ButtonY::instance + 2, OpenSHC::Rendering::Colors::COL_FFFFFF,
                        OpenSHC::Rendering::Colors::COL_000000, 19, FALSE);
                    DAT_ButtonUnknownZero::instance = FALSE;
                    return;
                }
                if (MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsRangedOnlyUnits, DAT_UnitsState::ptr)()) {
                    DAT_CurrentButtonGmDataIndex::instance
                        = OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_375_PIC_323;
                    // written out, not a break: a break here loses the match
                    MACRO_CALL(General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = FALSE;
                    return;
                }
                if (MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsLaddermenOnly, DAT_UnitsState::ptr)()
                    || MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::selectionContainsShieldmenOnly, DAT_UnitsState::ptr)()) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                // written out behind one || test, as in 218: a break or separate ifs lose the match
                MACRO_CALL(General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                DAT_ButtonUnknownZero::instance = FALSE;
                return;
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_370_PIC_309:
                if (MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)()
                    == Map::Units::UT_INVALID) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == Map::Units::Behavior::USE_STAND_GROUND) {
                    DAT_ButtonY::instance -= 5;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                } else {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                break;
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_371_PIC_311:
                if (MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)()
                    == Map::Units::UT_INVALID) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == Map::Units::Behavior::USE_DEFENSIVE) {
                    --DAT_ButtonY::instance;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                } else {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                break;
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_372_PIC_313:
                if (MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)()
                    == Map::Units::UT_INVALID) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                if (DAT_TribesState::instance.tribes[DAT_TribesState::instance.DAT_CurrentTribeID].unitStance
                    == Map::Units::Behavior::USE_AGGRESSIVE) {
                    --DAT_ButtonY::instance;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                } else {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                break;
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_216_PIC_301:
                if (DAT_UnitsState::instance.hasEngineerSelected
                    || MACRO_CALL_MEMBER(
                           Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)()
                        == Map::Units::UT_INVALID) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                if (DAT_TribesState::instance.patrolButtonPressed) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                }
                break;
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_211_PIC_327:
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_212_PIC_329:
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_213_PIC_331:
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_214_PIC_333:
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_215_PIC_335:
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_558_PIC_465:
                // != TRUE, as in 376: a truth test loses the match
                if (DAT_UnitsState::instance.hasEngineerSelected != TRUE
                    || MACRO_CALL_MEMBER(
                           Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)()
                        == 0) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                break;
            // default's body again: "case 217: default:" drops 217's own jump table entry
            case OpenSHC::Rendering::Enums::GDI_INTERFACE_ICONS_2_217_PIC_303:
                if (DAT_UnitsState::instance.hasEngineerSelected
                    || MACRO_CALL_MEMBER(
                           Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)()
                        == Map::Units::UT_INVALID) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                break;
            default:
                // one || test: as two ifs the match is lost
                if (DAT_UnitsState::instance.hasEngineerSelected
                    || MACRO_CALL_MEMBER(
                           Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)()
                        == Map::Units::UT_INVALID) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                break;
            }
            MACRO_CALL(General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            DAT_ButtonUnknownZero::instance = FALSE;
        }

    }
}
}
