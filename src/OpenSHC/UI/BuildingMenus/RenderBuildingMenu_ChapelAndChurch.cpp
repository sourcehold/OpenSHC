#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b98428.hpp"
#include "OpenSHC/Globals/DAT_00b9842c.hpp"
#include "OpenSHC/Globals/DAT_00b98430.hpp"
#include "OpenSHC/Globals/DAT_00b9843c.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_HusbandID.hpp"
#include "OpenSHC/Globals/DAT_HusbandUnitType.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WifeID.hpp"
#include "OpenSHC/Globals/DAT_WifeUnitType.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0043C1E0
    void BuildingMenus::RenderBuildingMenu_ChapelAndChurch()
    {
        BuildingTypeShort BVar2;
        char* pcVar3;
        int iVar4;
        int iVar5;
        TextAlignment TVar6;
        BGR24 BVar7;
        uint color;
        int iVar8;
        BOOLEnum BVar9;
        int iVar10;
        int blendStrength;
        int iVar11;
        iVar4 = DAT_BuildingsState::instance.menuSelectedBuildingID;
        BVar2
            = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].buildingType;
        if ((BVar2 == OpenSHC::Map::Buildings::BT_CHAPEL) || (BVar2 == OpenSHC::Map::Buildings::BT_CHURCH)
            || (BVar2 == OpenSHC::Map::Buildings::BT_CATHEDRAL)) {
            iVar5 = 0;
            if (BVar2 == OpenSHC::Map::Buildings::BT_CHURCH) {
                iVar5 = 3;
            }
            if (BVar2 == OpenSHC::Map::Buildings::BT_CATHEDRAL) {
                iVar5 = 4;
            }
            iVar11 = DAT_MenuHandlerState::instance.y + 0x1d3;
            iVar8 = DAT_MenuHandlerState::instance.x + 0x19;
            blendStrength = 0;
            BVar9 = FALSE;
            iVar10 = 0x10;
            BVar7 = 0;
            TVar6 = OpenSHC::Text::TTA_LEFT;
            /*
              added by script: "Cathedral"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_CHURCH, iVar5),
                iVar8, iVar11, TVar6, BVar7, iVar10, BVar9, blendStrength);
        }
        if (DAT_BuildingsState::instance.buildings[iVar4].currentEmployeeCount == 0) {
            iVar11 = 0;
            BVar9 = FALSE;
            iVar8 = 0x12;
            BVar7 = 0;
            TVar6 = OpenSHC::Text::TTA_LEFT;
            iVar4 = DAT_MenuHandlerState::instance.y + 0x205;
            iVar5 = DAT_MenuHandlerState::instance.x + 0xaf;
            /*
              added by script: "No Wedding this month"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, 0x22),
                iVar5, iVar4, TVar6, BVar7, iVar8, BVar9, iVar11);
        }
        if (DAT_GameState::instance.mapAndTime.month != DAT_RenderingDefinedData::instance.field1120_0x557e0) {
            DAT_RenderingDefinedData::instance.field1120_0x557e0 = DAT_GameState::instance.mapAndTime.month;
            DAT_00b9843c::instance = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::chooseHusbandAndWife,
                DAT_UnitsState::ptr)((int*)DAT_HusbandID::ptr, (int*)DAT_WifeID::ptr);
            if (DAT_00b9843c::instance == 0) {
                /* no wedding this month: render the notice and stop */
                iVar11 = 0;
                BVar9 = FALSE;
                iVar8 = 0x12;
                BVar7 = 0;
                TVar6 = OpenSHC::Text::TTA_LEFT;
                iVar4 = DAT_MenuHandlerState::instance.y + 0x205;
                iVar5 = DAT_MenuHandlerState::instance.x + 0xaf;
                /*
                added by script: "No Wedding this month"
                */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, 0x22),
                    iVar5, iVar4, TVar6, BVar7, iVar8, BVar9, iVar11);
                return;
            }
            DAT_HusbandUnitType::instance
                = (UnitTypeInt)(short)DAT_UnitsState::instance.units[DAT_HusbandID::instance].unitType;
            DAT_WifeUnitType::instance
                = (UnitTypeInt)(short)DAT_UnitsState::instance.units[DAT_WifeID::instance].unitType;
            if (DAT_WifeUnitType::instance == OpenSHC::Map::Units::UT_BREWER) {
                DAT_00b98428::instance = DAT_00b98428::instance + 1;
                if (9 < DAT_00b98428::instance) {
                    DAT_00b98428::instance = 0;
                }
            } else if (DAT_WifeUnitType::instance == OpenSHC::Map::Units::UT_TANNER) {
                DAT_00b9842c::instance = DAT_00b9842c::instance + 1;
                if (9 < DAT_00b9842c::instance) {
                    DAT_00b9842c::instance = 0;
                }
            } else {
                DAT_00b98430::instance = DAT_00b98430::instance + 1;
                if (9 < DAT_00b98430::instance) {
                    DAT_00b98430::instance = 0;
                }
            }
        }
        if (DAT_00b9843c::instance != 0) {
            if ((int)(short)DAT_UnitsState::instance.units[DAT_HusbandID::instance].unitType
                != DAT_HusbandUnitType::instance) {
                DAT_00b9843c::instance = 0;
            }
            if ((int)(short)DAT_UnitsState::instance.units[DAT_WifeID::instance].unitType
                == DAT_WifeUnitType::instance) {
                if (DAT_00b9843c::instance != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                        DAT_TextureRenderCoreObject::ptr)(
                        1, DAT_MenuHandlerState::instance.x + 0x173, DAT_MenuHandlerState::instance.y + 0x1e0);
                    iVar8 = 0;
                    iVar5 = 0x12;
                    color = 0;
                    iVar4 = 0x15e;
                    if (DAT_WifeUnitType::instance == OpenSHC::Map::Units::UT_BREWER) {
                        iVar11 = DAT_MenuHandlerState::instance.y + 0x22f;
                        iVar10 = DAT_MenuHandlerState::instance.x + 0xb4;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_MARRIAGE, DAT_00b98428::instance + 1),
                            iVar10, iVar11, iVar4, color, iVar5, iVar8);
                    } else if (DAT_WifeUnitType::instance == OpenSHC::Map::Units::UT_TANNER) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineTextUnk,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, DAT_00b9842c::instance + 0xc,
                            DAT_MenuHandlerState::instance.x + 0xb4, DAT_MenuHandlerState::instance.y + 0x22f, 0x15e, 0,
                            0x12, 0);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineTextUnk,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE,
                            DAT_00b98430::instance + 0x17, DAT_MenuHandlerState::instance.x + 0xb4,
                            DAT_MenuHandlerState::instance.y + 0x22f, 0x15e, 0, 0x12, 0);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    DAT_CurrentlyRenderedSpriteID::instance
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getPeasantGmID, DAT_UnitsState::ptr)(
                            DAT_HusbandID::instance);
                    DAT_RenderedUnitOwner::instance = 0;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        (OpenSHC::DE::SHCDE::eGM)DAT_CurrentlyRenderedSpriteID::instance, 3,
                        DAT_MenuHandlerState::instance.x + 0x82, DAT_MenuHandlerState::instance.y + 0x1c4);
                    DAT_CurrentlyRenderedSpriteID::instance
                        = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getPeasantGmID, DAT_UnitsState::ptr)(
                            DAT_WifeID::instance);
                    DAT_RenderedUnitOwner::instance = 0;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        (OpenSHC::DE::SHCDE::eGM)DAT_CurrentlyRenderedSpriteID::instance, 3,
                        DAT_MenuHandlerState::instance.x + 0x91, DAT_MenuHandlerState::instance.y + 0x1dd);
                    iVar4 = DAT_HusbandID::instance;
                    byte bVar1 = DAT_UnitsState::instance.units[DAT_HusbandID::instance].firstNameIndex;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    if ('\0' < (char)bVar1) {
                        iVar10 = 0;
                        BVar9 = FALSE;
                        iVar11 = 0x12;
                        BVar7 = 0;
                        TVar6 = OpenSHC::Text::TTA_LEFT;
                        iVar5 = DAT_MenuHandlerState::instance.y + 0x1ec;
                        iVar8 = DAT_MenuHandlerState::instance.x + 0xd7;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_PEASANT_NAMES, (int)((char)bVar1)),
                            iVar8, iVar5, TVar6, BVar7, iVar11, BVar9, iVar10);
                        bVar1 = DAT_UnitsState::instance.units[iVar4].rng1_to_70;
                        if (bVar1 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_PEASANT_SURNAMES, (int)((char)bVar1),
                                DAT_MenuHandlerState::instance.x + 0xdc, DAT_MenuHandlerState::instance.y + 0x1ec,
                                OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE);
                        }
                    }
                    iVar4 = DAT_WifeID::instance;
                    bVar1 = DAT_UnitsState::instance.units[DAT_WifeID::instance].firstNameIndex;
                    if ('\0' < (char)bVar1) {
                        iVar10 = 0;
                        BVar9 = FALSE;
                        iVar11 = 0x12;
                        BVar7 = 0;
                        TVar6 = OpenSHC::Text::TTA_LEFT;
                        iVar5 = DAT_MenuHandlerState::instance.y + 0x205;
                        iVar8 = DAT_MenuHandlerState::instance.x + 0xe6;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_PEASANT_NAMES, (int)((char)bVar1)),
                            iVar8, iVar5, TVar6, BVar7, iVar11, BVar9, iVar10);
                        bVar1 = DAT_UnitsState::instance.units[iVar4].rng1_to_70;
                        if (bVar1 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_PEASANT_SURNAMES, (int)((char)bVar1),
                                DAT_MenuHandlerState::instance.x + 0xeb, DAT_MenuHandlerState::instance.y + 0x205,
                                OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE);
                        }
                    }
                    if (DAT_00b9843c::instance != 0) {}
                }
            } else {
                DAT_00b9843c::instance = 0;
            }
        }
        iVar11 = 0;
        BVar9 = FALSE;
        iVar8 = 0x12;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        iVar4 = DAT_MenuHandlerState::instance.y + 0x205;
        iVar5 = DAT_MenuHandlerState::instance.x + 0xaf;
        /*
          added by script: "No Wedding this month"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, 0x22),
            iVar5, iVar4, TVar6, BVar7, iVar8, BVar9, iVar11);
    }

}
}
