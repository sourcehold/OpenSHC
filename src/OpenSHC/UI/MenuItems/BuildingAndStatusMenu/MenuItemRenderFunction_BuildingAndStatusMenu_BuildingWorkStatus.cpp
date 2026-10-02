#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Map::Buildings::BuildingTypeShort;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004476B0
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_BuildingWorkStatus(int param_1, ...)
        {
            short* psVar5;
            uint uVar6;
            int _unit;
            int iVar7;
            int iVar8;
            if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_PEASANT) {}
            short sVar1 = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                              .currentEmployeeCount;
            bool bVar4 = true;
            if ((sVar1 == 0)
                && (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                        .currentlyNeededEmployeeCount
                    == 0)) {}
            if (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                    .buildingTypeBasedEmployeeCount
                < 1) {}
            BuildingTypeShort BVar2
                = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                      .buildingType;
            if ((0x27 < (short)BVar2) && ((short)BVar2 < 0x2d)) {}
            if ((0x23 < (short)BVar2) && ((short)BVar2 < 0x27)) {}
            if (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                    .hasAccessToKeep
                == 0) {
                /*
                  added by script: "No access to keep"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_IN_GENERAL_BUILDINGS, 9, (int)(DAT_ButtonX::instance + 0x96),
                    (int)(DAT_ButtonY::instance), OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
            }
            if (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].sleeping
                == false) {
                short sVar3
                    = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                          .currentlyNeededEmployeeCount;
                if (sVar3 != 0) {
                    if (sVar1 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_IN_GENERAL_BUILDINGS, (int)(sVar3 + 4),
                            (int)(DAT_ButtonX::instance + 0x96), (int)(DAT_ButtonY::instance), OpenSHC::Text::TTA_LEFT,
                            0, 0x12, FALSE);
                    }
                    /*
                      added by script: "No labour"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_IN_GENERAL_BUILDINGS, 3, (int)(DAT_ButtonX::instance + 0x96),
                        (int)(DAT_ButtonY::instance), OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
                }
                iVar7 = (int)sVar1;
                if (0 < iVar7) {
                    psVar5 = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                                 .workerID;
                    iVar8 = iVar7;
                    do {
                        _unit = (int)*psVar5;
                        if (DAT_UnitsState::instance.units[_unit].unitType == OpenSHC::Map::Units::UT_PEASANT) {
                            bVar4 = false;
                        }
                        psVar5 = psVar5 + 1;
                        iVar8 = iVar8 + -1;
                    } while (iVar8 != 0);
                    if (!bVar4) {
                        /*
                          added by script: "Peasant on his way"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_IN_GENERAL_BUILDINGS, 4, (int)(DAT_ButtonX::instance + 0x96),
                            (int)(DAT_ButtonY::instance), OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
                    }
                }
                switch (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                        .buildingType) {
                case OpenSHC::Map::Buildings::BT_IRONMINE:
                    _unit = (int)DAT_BuildingsState::instance
                                .buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                                .workerID[1];
                default:
                    /*
                      added by script: "Worker:"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_IN_GENERAL_BUILDINGS, 10, (int)(DAT_ButtonX::instance + 0x96),
                        (int)(DAT_ButtonY::instance + -0x14), OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderPeasantMenu_CurrentActionUnk)(
                        _unit, (int)(DAT_ButtonX::instance + 0x96), (int)(DAT_ButtonY::instance));
                    return;
                case OpenSHC::Map::Buildings::BT_FLETCHER:
                case OpenSHC::Map::Buildings::BT_BLACKSMITH:
                case OpenSHC::Map::Buildings::BT_POLETURNER:
                    /*
                      added by script: "Worker:"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_IN_GENERAL_BUILDINGS, 10, (int)(DAT_ButtonX::instance + 0x96),
                        (int)(DAT_ButtonY::instance + -10), OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderPeasantMenu_CurrentActionUnk)(
                        _unit, (int)(DAT_ButtonX::instance + 0x96), (int)(DAT_ButtonY::instance + 10));
                    return;
                case OpenSHC::Map::Buildings::BT_QUARRY:
                    /*
                      added by script: "Currently Functioning"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_IN_GENERAL_BUILDINGS, 2, (int)(DAT_ButtonX::instance + 0x96),
                        (int)(DAT_ButtonY::instance), OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
                    return;
                case OpenSHC::Map::Buildings::BT_MILL:
                    goto switchD_00447874_caseD_22;
                }
            }
            /*
              added by script: "Turned off"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_IN_GENERAL_BUILDINGS, 7, (int)(DAT_ButtonX::instance + 0x96),
                (int)(DAT_ButtonY::instance), OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
            return;
        switchD_00447874_caseD_22:
            /*
              Miller specific
             */
            uVar6 = 100;
            if (0 < iVar7) {
                psVar5 = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                             .workerID;
                do {
                    switch (DAT_UnitsState::instance.units[*psVar5].state.generic) {
                    case OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk:
                    case ((UnitState)2):
                    case OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk:
                    case OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk:
                        if (4 < uVar6) {
                            uVar6 = 4;
                        }
                        break;
                    case OpenSHC::Map::Units::States::US_IDLEUnk:
                        if (5 < uVar6) {
                            uVar6 = 5;
                        }
                        break;
                    case ((UnitState)3):
                        if (3 < uVar6) {
                            uVar6 = 3;
                        }
                        break;
                    case OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk:
                        if (2 < uVar6) {
                            uVar6 = 2;
                        }
                        break;
                    case OpenSHC::Map::Units::States::US_AIM_WEAPONUnk:
                        uVar6 = 0;
                        break;
                    case OpenSHC::Map::Units::States::US_STAND_UPUnk:
                        if (1 < uVar6) {
                            uVar6 = 1;
                        }
                    }
                    psVar5 = psVar5 + 1;
                    iVar7 = iVar7 + -1;
                } while (iVar7 != 0);
                if (uVar6 < 100) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_IN_MILL, (int)(uVar6 + 3), (int)(DAT_ButtonX::instance + 0x96),
                        (int)(DAT_ButtonY::instance), OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
                }
            }
        }

    }
}
}
