#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

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
#include "OpenSHC/Globals/INT_0061824c.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Map::Buildings::BuildingTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043C1E0
    void BuildingMenus::RenderBuildingMenu_ChapelAndChurch()
    {
        int const buildingID = DAT_BuildingsState::instance.menuSelectedBuildingID;
        BuildingTypeShort const buildingType
            = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].buildingType;
        if (buildingType == OpenSHC::Map::Buildings::BT_CHAPEL) {
            int const titleY = DAT_MenuHandlerState::instance.y + 467;
            int const titleX = DAT_MenuHandlerState::instance.x + 25;
            // "Chapel"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_CHURCH, 0),
                titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 16, FALSE, 0);
        } else if (buildingType == OpenSHC::Map::Buildings::BT_CHURCH) {
            int const titleY = DAT_MenuHandlerState::instance.y + 467;
            int const titleX = DAT_MenuHandlerState::instance.x + 25;
            // "Church"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_CHURCH, 3),
                titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 16, FALSE, 0);
        } else if (buildingType == OpenSHC::Map::Buildings::BT_CATHEDRAL) {
            int const titleY = DAT_MenuHandlerState::instance.y + 467;
            int const titleX = DAT_MenuHandlerState::instance.x + 25;
            // "Cathedral"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_CHURCH, 4),
                titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 16, FALSE, 0);
        }

        if (DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount == 0) {
            int const noticeY = DAT_MenuHandlerState::instance.y + 517;
            int const noticeX = DAT_MenuHandlerState::instance.x + 175;
            // "No Wedding this month"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, 34),
                noticeX, noticeY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
            return;
        }
        // a new couple each month
        if (DAT_GameState::instance.mapAndTime.month != INT_0061824c::instance) {
            INT_0061824c::instance = DAT_GameState::instance.mapAndTime.month;
            DAT_00b9843c::instance = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::chooseHusbandAndWife,
                DAT_UnitsState::ptr)((int*)DAT_HusbandID::ptr, (int*)DAT_WifeID::ptr);
            if (DAT_00b9843c::instance == 0) {
                int const noticeY = DAT_MenuHandlerState::instance.y + 517;
                int const noticeX = DAT_MenuHandlerState::instance.x + 175;
                // "No Wedding this month"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, 34),
                    noticeX, noticeY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
                return;
            }
            DAT_HusbandUnitType::instance
                = (UnitTypeInt)(short)DAT_UnitsState::instance.units[DAT_HusbandID::instance].unitType;
            DAT_WifeUnitType::instance
                = (UnitTypeInt)(short)DAT_UnitsState::instance.units[DAT_WifeID::instance].unitType;
            // the trade of the wife picks the text; each trade walks through its own ten texts
            switch (DAT_WifeUnitType::instance) {
            case OpenSHC::Map::Units::UT_BREWER:
                ++DAT_00b98428::instance;
                if (DAT_00b98428::instance > 9) {
                    DAT_00b98428::instance = 0;
                }
                break;
            case OpenSHC::Map::Units::UT_TANNER:
                ++DAT_00b9842c::instance;
                if (DAT_00b9842c::instance > 9) {
                    DAT_00b9842c::instance = 0;
                }
                break;
            default:
                ++DAT_00b98430::instance;
                if (DAT_00b98430::instance > 9) {
                    DAT_00b98430::instance = 0;
                }
            }
        }
        if (DAT_00b9843c::instance != 0) {
            // the wedding is off when one of the two changed trade
            if ((short)DAT_UnitsState::instance.units[DAT_HusbandID::instance].unitType
                != DAT_HusbandUnitType::instance) {
                DAT_00b9843c::instance = 0;
            }
            if ((short)DAT_UnitsState::instance.units[DAT_WifeID::instance].unitType != DAT_WifeUnitType::instance) {
                DAT_00b9843c::instance = 0;
            }
            if (DAT_00b9843c::instance != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    1, DAT_MenuHandlerState::instance.x + 371, DAT_MenuHandlerState::instance.y + 480);
                if (DAT_WifeUnitType::instance != OpenSHC::Map::Units::UT_BREWER) {
                    if (DAT_WifeUnitType::instance == OpenSHC::Map::Units::UT_TANNER) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineTextUnk,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, DAT_00b9842c::instance + 12,
                            DAT_MenuHandlerState::instance.x + 180, DAT_MenuHandlerState::instance.y + 559, 350, 0, 18,
                            0);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineTextUnk,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, DAT_00b98430::instance + 23,
                            DAT_MenuHandlerState::instance.x + 180, DAT_MenuHandlerState::instance.y + 559, 350, 0, 18,
                            0);
                    }
                } else {
                    int const textY = DAT_MenuHandlerState::instance.y + 559;
                    int const textX = DAT_MenuHandlerState::instance.x + 180;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, DAT_00b98428::instance + 1),
                        textX, textY, 350, 0, 18, 0);
                }
                // the pictures of the couple
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                DAT_CurrentlyRenderedSpriteID::instance = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getPeasantGmID, DAT_UnitsState::ptr)(DAT_HusbandID::instance);
                DAT_RenderedUnitOwner::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_CurrentlyRenderedSpriteID::instance,
                    3, DAT_MenuHandlerState::instance.x + 130, DAT_MenuHandlerState::instance.y + 452);
                DAT_CurrentlyRenderedSpriteID::instance = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::UnitsState_Func::getPeasantGmID, DAT_UnitsState::ptr)(DAT_WifeID::instance);
                DAT_RenderedUnitOwner::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_CurrentlyRenderedSpriteID::instance,
                    3, DAT_MenuHandlerState::instance.x + 145, DAT_MenuHandlerState::instance.y + 477);
                // the names of the two
                int const husbandID = DAT_HusbandID::instance;
                char const husbandName = (char)DAT_UnitsState::instance.units[DAT_HusbandID::instance].firstNameIndex;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                if (husbandName > 0) {
                    int const nameY = DAT_MenuHandlerState::instance.y + 492;
                    int const nameX = DAT_MenuHandlerState::instance.x + 215;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_PEASANT_NAMES, husbandName),
                        nameX, nameY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
                    char const surname = (char)DAT_UnitsState::instance.units[husbandID].rng1_to_70;
                    if (surname != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_PEASANT_SURNAMES, surname, DAT_MenuHandlerState::instance.x + 220,
                            DAT_MenuHandlerState::instance.y + 492, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE);
                    }
                }
                int const wifeID = DAT_WifeID::instance;
                char const wifeName = (char)DAT_UnitsState::instance.units[DAT_WifeID::instance].firstNameIndex;
                if (wifeName > 0) {
                    int const nameY = DAT_MenuHandlerState::instance.y + 517;
                    int const nameX = DAT_MenuHandlerState::instance.x + 230;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_PEASANT_NAMES, wifeName),
                        nameX, nameY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
                    char const surname = (char)DAT_UnitsState::instance.units[wifeID].rng1_to_70;
                    if (surname != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_PEASANT_SURNAMES, surname, DAT_MenuHandlerState::instance.x + 235,
                            DAT_MenuHandlerState::instance.y + 517, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE);
                    }
                }
                // a wedding is on: no "No Wedding this month"
                if (DAT_00b9843c::instance != 0) {
                    return;
                }
            }
        }
        int const noticeY = DAT_MenuHandlerState::instance.y + 517;
        int const noticeX = DAT_MenuHandlerState::instance.x + 175;
        // "No Wedding this month"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MARRIAGE, 34),
            noticeX, noticeY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
    }

}
}
