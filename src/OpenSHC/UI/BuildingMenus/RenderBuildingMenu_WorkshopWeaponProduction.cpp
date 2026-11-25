#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // The argument temporaries mirror the original's evaluation order: written inline in the calls,
    // the positions are loaded after the text lookup and the match drops (measured).
    // FUNCTION: STRONGHOLDCRUSADER 0x00439440
    void BuildingMenus::RenderBuildingMenu_WorkshopWeaponProduction()
    {
        int workerIDOrPosition;
        BOOLEnum paused;
        int _textNumInGroup;
        int xOrFontSize;
        TextAlignment alignment;
        BGR24 color;
        int fontSizeOrBlendStrength;
        int blendStrength;
        int buildingIDOrY = DAT_BuildingsState::instance.menuSelectedBuildingID;
        if ((((DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].buildingType
                  == OpenSHC::Map::Buildings::BT_FLETCHER)
                 && (workerIDOrPosition
                     = (int)DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                         .workerID[0],
                     workerIDOrPosition != 0))
                && (DAT_UnitsState::instance.units[workerIDOrPosition].state.generic
                    == OpenSHC::Map::Units::States::US_STAND_UPUnk))
            && (paused = MACRO_CALL(OpenSHC::Map::Units_Func::CheckUnitProductionPaused)(workerIDOrPosition),
                paused == FALSE)) {
            // "Not producing - No Wood"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 11, DAT_MenuHandlerState::instance.x + 175,
                DAT_MenuHandlerState::instance.y + 505, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE);
        } else if (((DAT_BuildingsState::instance.buildings[buildingIDOrY].buildingType
                        == OpenSHC::Map::Buildings::BT_POLETURNER)
                       && (workerIDOrPosition = (int)DAT_BuildingsState::instance.buildings[buildingIDOrY].workerID[0],
                           workerIDOrPosition != 0))
            && ((DAT_UnitsState::instance.units[workerIDOrPosition].state.generic
                    == OpenSHC::Map::Units::States::US_IDLEUnk
                && (paused = MACRO_CALL(OpenSHC::Map::Units_Func::CheckUnitProductionPaused)(workerIDOrPosition),
                    paused == FALSE)))) {
            // "Not producing - No Wood"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 11, DAT_MenuHandlerState::instance.x + 175,
                DAT_MenuHandlerState::instance.y + 505, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE);
        } else if (((DAT_BuildingsState::instance.buildings[buildingIDOrY].buildingType
                        == OpenSHC::Map::Buildings::BT_BLACKSMITH)
                       && (workerIDOrPosition = (int)DAT_BuildingsState::instance.buildings[buildingIDOrY].workerID[0],
                           workerIDOrPosition != 0))
            && ((DAT_UnitsState::instance.units[workerIDOrPosition].state.generic
                    == (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk)
                && (paused = MACRO_CALL(OpenSHC::Map::Units_Func::CheckUnitProductionPaused)(workerIDOrPosition),
                    paused == FALSE)))) {
            // "Not producing - No Iron"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 12, DAT_MenuHandlerState::instance.x + 175,
                DAT_MenuHandlerState::instance.y + 505, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE);
        } else {
            blendStrength = 0;
            paused = FALSE;
            fontSizeOrBlendStrength = 18;
            color = 0;
            alignment = OpenSHC::Text::TTA_LEFT;
            workerIDOrPosition = DAT_MenuHandlerState::instance.y + 505;
            xOrFontSize = DAT_MenuHandlerState::instance.x + 175;
            // "Producing:"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 3),
                xOrFontSize, workerIDOrPosition, alignment, color, fontSizeOrBlendStrength, paused, blendStrength);
            switch (DAT_BuildingsState::instance.buildings[buildingIDOrY].producedItemTypeNext) {
            case OpenSHC::Game::Resources::RT_SWORD:
                _textNumInGroup = 5;
                break;
            case OpenSHC::Game::Resources::RT_MACE:
                _textNumInGroup = 6;
                break;
            case OpenSHC::Game::Resources::RT_BOW:
                _textNumInGroup = 7;
                break;
            case OpenSHC::Game::Resources::RT_CROSSBOW:
                _textNumInGroup = 8;
                break;
            case OpenSHC::Game::Resources::RT_SPEAR:
                _textNumInGroup = 9;
                break;
            case OpenSHC::Game::Resources::RT_PIKE:
                _textNumInGroup = 10;
            }
            blendStrength = 0;
            paused = TRUE;
            fontSizeOrBlendStrength = 18;
            color = 0;
            alignment = OpenSHC::Text::TTA_LEFT;
            workerIDOrPosition = DAT_MenuHandlerState::instance.y + 505;
            xOrFontSize = DAT_MenuHandlerState::instance.x + 180;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, _textNumInGroup),
                xOrFontSize, workerIDOrPosition, alignment, color, fontSizeOrBlendStrength, paused, blendStrength);
        }
        blendStrength = 0;
        paused = FALSE;
        fontSizeOrBlendStrength = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        workerIDOrPosition = DAT_MenuHandlerState::instance.y + 530;
        xOrFontSize = DAT_MenuHandlerState::instance.x + 175;
        // "Next:"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, 4),
            xOrFontSize, workerIDOrPosition, alignment, color, fontSizeOrBlendStrength, paused, blendStrength);
        switch (DAT_BuildingsState::instance.buildings[buildingIDOrY].producedItemType) {
        case OpenSHC::Game::Resources::RT_SWORD:
            _textNumInGroup = 5;
            break;
        case OpenSHC::Game::Resources::RT_MACE:
            _textNumInGroup = 6;
            break;
        case OpenSHC::Game::Resources::RT_BOW:
            _textNumInGroup = 7;
            break;
        case OpenSHC::Game::Resources::RT_CROSSBOW:
            _textNumInGroup = 8;
            break;
        case OpenSHC::Game::Resources::RT_SPEAR:
            _textNumInGroup = 9;
            break;
        case OpenSHC::Game::Resources::RT_PIKE:
            _textNumInGroup = 10;
        }
        fontSizeOrBlendStrength = 0;
        paused = TRUE;
        xOrFontSize = 18;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        buildingIDOrY = DAT_MenuHandlerState::instance.y + 530;
        workerIDOrPosition = DAT_MenuHandlerState::instance.x + 180;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_BLACKSMITHS_WORKSHOP, _textNumInGroup),
            workerIDOrPosition, buildingIDOrY, alignment, color, xOrFontSize, paused, fontSizeOrBlendStrength);
    }

}
}
